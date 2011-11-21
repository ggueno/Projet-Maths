/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * HomeomorphicAlignment.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-graph.
 *
 * The OpenKraken-graph is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-graph is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_GRAPH__HOMEOMORPHIC_ALIGNMENT_HPP__
#define __OPENKN_GRAPH__HOMEOMORPHIC_ALIGNMENT_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4996)
#endif

/*
 * External Includes
 */

#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <limits>
/*
 * Internal Includes
 */
#include "GraphException.hpp"
#include "Graph.hpp"
#include "UndirectedGraph.hpp"
#include "RootedTree.hpp"
#include "HATreeInfos.hpp"
#include "HAOperators.hpp"
#include "HARootedTreeInfos.hpp"
#include "HAUnrootedTreeInfos.hpp"
#include "EdgeConstraint.hpp"
#include "Subset.hpp"

#define FUSION_COMPLETE 0
#define FUSION_DISABLE 1

/*
 * Namespace
 */
namespace kn{
	
		
		/*
		 * Class definition
		 */

		/** \brief 
		
		 */
		template<typename V, typename E>
		class HomeomorphicAlignment{
		
		private :
			Graph<V,E>* pattern;
			Graph<V,E>* data;
			HATreeInfos<V,E>* patternInfos;
			HATreeInfos<V,E>* dataInfos;
			
			unsigned int patternFusion;
			unsigned int dataFusion;
			
			HAOperators<V,E>* operators;
			
			std::vector<double> treeDistances;
			std::vector<double> forestDistances;
			std::vector<double> patternTreeDeletion;
			std::vector<double> patternForestDeletion;
			std::vector<double> dataTreeDeletion;
			std::vector<double> dataForestDeletion;
			unsigned int pSize;
			unsigned int dSize;
			unsigned int pSubsetSize;
			unsigned int dSubsetSize;
			
			double HADistance;
			/*
			 * Constructor & destructors
			 */
		public :
			 HomeomorphicAlignment(UndirectedGraph<V,E>* pattern, UndirectedGraph<V,E>* data, HAOperators<V,E>* operators, 
			 		unsigned int patternFusion = FUSION_COMPLETE, unsigned int dataFusion = FUSION_COMPLETE);
			 
			 HomeomorphicAlignment(UndirectedGraph<V,E>* pattern, RootedTree<V,E>* data, HAOperators<V,E>* operators, 
			 		unsigned int patternFusion = FUSION_COMPLETE, unsigned int dataFusion = FUSION_COMPLETE);
			 
			 HomeomorphicAlignment(RootedTree<V,E>* pattern, RootedTree<V,E>* data, HAOperators<V,E>* operators, 
			 		unsigned int patternFusion = FUSION_COMPLETE, unsigned int dataFusion = FUSION_COMPLETE);
			 
			 HomeomorphicAlignment(RootedTree<V,E>* pattern, UndirectedGraph<V,E>* data, HAOperators<V,E>* operators, 
			 		unsigned int patternFusion = FUSION_COMPLETE, unsigned int dataFusion = FUSION_COMPLETE);
			 	
			inline ~HomeomorphicAlignment(){
			 	if(patternInfos != NULL){
					delete patternInfos;	
				}
				if(dataInfos != NULL){
					delete dataInfos;	
				}
			 }
			
		private :
			inline void init(unsigned int patternFusion, unsigned int dataFusion){
				patternInfos = NULL;
				dataInfos = NULL;
				this->patternFusion = patternFusion;
				this->dataFusion = dataFusion;
			}
	
			inline void initPatternDistancesArrays(){
				pSize = pattern->size();
				patternTreeDeletion = std::vector<double>(pSize*pSize, -1.0);
				pSubsetSize = std::pow(2.0, int(patternInfos->degree()));
				patternForestDeletion = std::vector<double>((int)(pSize*pSubsetSize),-1.0);
			}
			
			
			inline void initDataDistancesArrays(){
				dSize = data->size();
				dataTreeDeletion = std::vector<double>(dSize*dSize, -1.0);
				dSubsetSize = std::pow(2.0, int(dataInfos->degree()));
				dataForestDeletion = std::vector<double>((int)(dSize*dSubsetSize),-1.0);
			}
			
			inline void initCommonDistancesArrays(){
				treeDistances = std::vector<double>(dataTreeDeletion.size()*patternTreeDeletion.size(),-1.0);
				forestDistances = std::vector<double>(dataForestDeletion.size()*patternForestDeletion.size(),-1.0);
			}
			
			inline double getPatternTreeDeletion(unsigned int vertex, unsigned int root){
				return patternTreeDeletion[root*pSize+vertex];
			}
			
			inline double getDataTreeDeletion(unsigned int vertex, unsigned int root){
				return dataTreeDeletion[root*dSize+vertex];
			}
			
			inline double getPatternForestDeletion(unsigned int vertex, unsigned int subset){
				return patternForestDeletion[vertex*pSubsetSize+subset];
			}
			
			inline double getDataForestDeletion(unsigned int vertex, unsigned int subset){
				return dataForestDeletion[vertex*dSubsetSize+subset];
			}
			
			inline double getTreeDistance(unsigned int pvertex, unsigned int proot,unsigned int dvertex, unsigned int droot){
				return treeDistances[(proot*pSize+pvertex)*dataTreeDeletion.size()+droot*dSize+dvertex];
			}
			
			inline double getForestDistance(unsigned int pvertex, unsigned int psubset,unsigned int dvertex, unsigned int dsubset){
				if(psubset == 0)
					return getDataForestDeletion(dvertex, dsubset);
				if(dsubset == 0)
					return getPatternForestDeletion(pvertex, psubset); 
				return forestDistances[(pvertex*pSubsetSize+psubset)*dataForestDeletion.size()+dvertex*dSubsetSize+dsubset];
			}
			inline void setPatternTreeDeletion(unsigned int vertex, unsigned int root, double distance){
				 patternTreeDeletion[root*pSize+vertex] = distance;
			}
			
			inline void setDataTreeDeletion(unsigned int vertex, unsigned int root, double distance){
				 dataTreeDeletion[root*dSize+vertex] = distance;
			}
			
			inline void setPatternForestDeletion(unsigned int vertex, unsigned int subset, double distance){
				 patternForestDeletion[vertex*pSubsetSize+subset] = distance;
			}
			
			inline void setDataForestDeletion(unsigned int vertex, unsigned int subset, double distance){
				 dataForestDeletion[vertex*dSubsetSize+subset] = distance;
			}
			
			inline void setTreeDistance(unsigned int pvertex, unsigned int proot,unsigned int dvertex, unsigned int droot, double distance){
				 treeDistances[(proot*pSize+pvertex)*dataTreeDeletion.size()+droot*dSize+dvertex] = distance;
			}
			
			inline void setForestDistance(unsigned int pvertex, unsigned int psubset,unsigned int dvertex, unsigned int dsubset, double distance){
				forestDistances[(pvertex*pSubsetSize+psubset)*dataForestDeletion.size()+dvertex*dSubsetSize+dsubset] = distance;
				 
			}
			
			inline unsigned int childrenSet(std::vector<unsigned int>& children, unsigned int parent, Subset& set, bool rooted){
				unsigned int chSet = set.set(children.size());
				if(!rooted){
					for(unsigned int paria = 0; paria < children.size(); paria++){
						if(children[paria]==parent){
							chSet = set.setWithoutParia(chSet, paria);
							break;
						}	
					}
				}
				return chSet;
			}
			 
			inline bool fusionDistancePCheck(unsigned int vertex, unsigned int root){
				if(patternFusion == FUSION_COMPLETE)return true;
				return patternInfos->pathSize(root, vertex)<= patternFusion;
			}
			inline bool fusionDistanceDCheck(unsigned int vertex, unsigned int root){
				if(dataFusion == FUSION_COMPLETE)return true;
				return dataInfos->pathSize(root, vertex)<= dataFusion;
			}
			
			double computePrunedTreeDistance(unsigned int pcur, unsigned int panc, 
							 unsigned int pSet, std::vector<unsigned int>& pchildren, 
							 unsigned int dcur, unsigned int danc, 
							 unsigned int dSet, std::vector<unsigned int>& dchildren, Subset& set);

			double computeForestDistance(unsigned int pcur, unsigned int pSubset, 
						     std::vector<unsigned int>& pchildren, 
						     unsigned int dcur, unsigned int dSubset, 
						     std::vector<unsigned int>& dchildren, Subset& set);

			void computeDeletions(std::vector<std::pair<unsigned int, unsigned int> >& patternOrder,
					      std::vector<std::pair<unsigned int, unsigned int> >& dataOrder,
					      Subset& set);


			double findMinDistance(Subset& set);

		public : 
			inline void changePattern(UndirectedGraph<V,E>* pattern, bool initArrays = true){
				if(patternInfos != NULL){
					delete patternInfos;	
				}
				patternInfos = new HAUnrootedTreeInfos<V,E>(pattern);
				this->pattern = pattern;
				if(initArrays){
					initPatternDistancesArrays();
					initCommonDistancesArrays();
				}
			}
			
			inline void changePattern(RootedTree<V,E>* pattern, bool initArrays = true){
				if(patternInfos != NULL){
					delete patternInfos;	
				}
				patternInfos = new HARootedTreeInfos<V,E>(pattern);
				this->pattern = pattern;
				if(initArrays){
					initPatternDistancesArrays();
					initCommonDistancesArrays();
				}
			}
			
			inline void changeData(UndirectedGraph<V,E>* data, bool initArrays = true){
				if(dataInfos != NULL){
					delete dataInfos;	
				}
				dataInfos = new HAUnrootedTreeInfos<V,E>(data);
				this->data = data;
				if(initArrays){
					initDataDistancesArrays();
					initCommonDistancesArrays();
				}
			}
			
			inline void changeData(RootedTree<V,E>* data, bool initArrays = true){
				if(dataInfos != NULL){
					delete dataInfos;	
				}
				dataInfos = new HARootedTreeInfos<V,E>(data);
				this->data = data;
				if(initArrays){
					initDataDistancesArrays();
					initCommonDistancesArrays();
				}
			}
			
			double compute();
			
			template<typename D>
			double compute(std::map<std::pair<unsigned int, unsigned int>, EdgeConstraint<D>* >& constraints, std::vector<D>& datas, bool leafAlignment=false);
			
			unsigned int getBestMatch(unsigned int vertex);
			
			std::vector<unsigned int> getBestMatches(unsigned int vertex);
			
			inline void setPatternFusionDistance(unsigned int distance){
				patternFusion = distance;
			}
			
			inline void setDataFusionDistance(unsigned int distance){
				dataFusion = distance;
			}
			
			
		};








		template<typename V, typename E>
		HomeomorphicAlignment<V,E>::HomeomorphicAlignment(UndirectedGraph<V,E>* pattern, 
								  UndirectedGraph<V,E>* data, 
								  HAOperators<V,E>* operators, 
								  unsigned int patternFusion, 
								  unsigned int dataFusion){
			init(patternFusion, dataFusion);
			changePattern(pattern,false);
			changeData(data,false);
			this->operators = operators;
			initPatternDistancesArrays();
			initDataDistancesArrays();
			initCommonDistancesArrays();					  
		}
			 
		template<typename V, typename E>
		HomeomorphicAlignment<V,E>::HomeomorphicAlignment(UndirectedGraph<V,E>* pattern, 
								  RootedTree<V,E>* data, 
								  HAOperators<V,E>* operators, 
			 					  unsigned int patternFusion, 
			 					  unsigned int dataFusion){
			init(patternFusion, dataFusion);
			changePattern(pattern,false);
			changeData(data,false);
			this->operators = operators;
			initPatternDistancesArrays();
			initDataDistancesArrays();
			initCommonDistancesArrays();					  
		}
		
		template<typename V, typename E>
		HomeomorphicAlignment<V,E>::HomeomorphicAlignment(RootedTree<V,E>* pattern, 
								  RootedTree<V,E>* data, 
								  HAOperators<V,E>* operators,
								  unsigned int patternFusion, 
								  unsigned int dataFusion){
			init(patternFusion, dataFusion);
			changePattern(pattern,false);
			changeData(data,false);
			this->operators = operators;
			initPatternDistancesArrays();
			initDataDistancesArrays();
			initCommonDistancesArrays();					  
		}
		
		template<typename V, typename E>
		HomeomorphicAlignment<V,E>::HomeomorphicAlignment(RootedTree<V,E>* pattern, 
								  UndirectedGraph<V,E>* data, 
								  HAOperators<V,E>* operators, 
						 		  unsigned int patternFusion, 
						 		  unsigned int dataFusion){
			init(patternFusion, dataFusion);
			changePattern(pattern,false);
			changeData(data,false);
			this->operators = operators;
			initPatternDistancesArrays();
			initDataDistancesArrays();
			initCommonDistancesArrays();
		}
		
		
		
		template<typename V, typename E>
		double HomeomorphicAlignment<V,E>::computePrunedTreeDistance(unsigned int pcur, unsigned int panc, 
									     unsigned int pSet, std::vector<unsigned int>& pchildren,
									     unsigned int dcur, unsigned int danc, 
									     unsigned int dSet, std::vector<unsigned int>& dchildren, Subset& set){
			double minDist = std::numeric_limits<double>::max();
			//case 1
			double dist = 0.0;
			if(!operators->patternCut())
				dist += getPatternTreeDeletion(pcur, panc);
			if(!operators->dataCut())
				dist += getDataTreeDeletion(dcur, danc);
			minDist = std::min(dist, minDist);
			
			//case 2
			dist = operators->resize(patternInfos->pathWeight(panc, pcur), 
						 dataInfos->pathWeight(danc, dcur))
			      + getForestDistance(pcur, pSet, dcur, dSet);
			minDist = std::min(dist, minDist);
			
			//case 3
			for(char delement = set.getNextElement(-1,dSet); delement != -1; 
				delement=set.getNextElement(delement,dSet)){
				if(dchildren[delement] == danc 
						|| !fusionDistanceDCheck(dchildren[delement], danc))continue;
				dist = getTreeDistance(pcur, panc, dchildren[delement], danc);
				if(!operators->dataCut()){
					unsigned int s = set.setWithoutParia(dSet, delement);
					dist += getDataForestDeletion(dcur, s); 
				}
				minDist = std::min(dist, minDist);
			}
			
			//case 4
			for(char pelement = set.getNextElement(-1,pSet); pelement != -1; 
				pelement=set.getNextElement(pelement,pSet)){
				if(pchildren[pelement] == panc 
					|| !fusionDistancePCheck(pchildren[pelement], panc))continue;
				dist = getTreeDistance(pchildren[pelement], panc, dcur, danc);
				if(!operators->patternCut()){
					unsigned int s = set.setWithoutParia(pSet, pelement);
					dist += getPatternForestDeletion(pcur, s); 
				}
				minDist = std::min(dist, minDist);
			}
			setTreeDistance(pcur, panc, dcur, danc, minDist);
			return minDist;
		}
		
		
		template<typename V, typename E>
		double HomeomorphicAlignment<V,E>::computeForestDistance(unsigned int pcur, unsigned int pSubset, 
									     std::vector<unsigned int>& pchildren,
									     unsigned int dcur, unsigned int dSubset, 
									     std::vector<unsigned int>& dchildren, Subset& set){
			double minDist = std::numeric_limits<double>::max();
			//case 1
			for(char element = set.getNextElement(-1,dSubset); element != -1; 
				element=set.getNextElement(element,dSubset)){
				unsigned int s = set.setWithoutParia(dSubset, element);
				double dist = getForestDistance(pcur, pSubset, dcur, s);
				if(!operators->dataCut())
					dist += getDataTreeDeletion(dchildren[element], dcur);
				minDist = std::min(dist, minDist);
				
				//case 5
				std::vector<unsigned int> echildren = dataInfos->children(dchildren[element]);
				unsigned int eSet = childrenSet(echildren, dcur, set, dataInfos->isRooted());
				for(unsigned int pSubsubset = 0; pSubsubset <= pSubset; 
					pSubsubset = set.nextSubsetIndex(pSubsubset,pSubset)){
					unsigned int ps = set.complement(pSubsubset, pSubset);
					dist = getForestDistance(pcur, ps, dcur, s)
					     + getForestDistance(pcur, pSubsubset, dchildren[element], eSet)
					     + operators->deletion(dataInfos->pathWeight(dcur, dchildren[element]));
					minDist = std::min(dist, minDist);
				}
			}								
			
			//case 2
			for(char element = set.getNextElement(-1,pSubset); element != -1; 
				element=set.getNextElement(element,pSubset)){
				unsigned int s = set.setWithoutParia(pSubset, element);
				double dist = getForestDistance(pcur, s, dcur, dSubset);
				if(!operators->patternCut())
					dist += getPatternTreeDeletion(pchildren[element], pcur);
				minDist = std::min(dist, minDist);
				
				//case 3
				for(char delement = set.getNextElement(-1,dSubset); delement != -1; 
				delement=set.getNextElement(delement,dSubset)){
					unsigned int ds = set.setWithoutParia(dSubset, delement);
					dist = getForestDistance(pcur, s, dcur, ds)
						+ getTreeDistance(pchildren[element], pcur, 
								  dchildren[delement], dcur);
				minDist = std::min(dist, minDist);
				}
				
				//case 4
				std::vector<unsigned int> echildren = patternInfos->children(pchildren[element]);
				unsigned int eSet = childrenSet(echildren, pcur, set, patternInfos->isRooted());
				for(unsigned int dSubsubset = 0; dSubsubset <= dSubset; 
					dSubsubset = set.nextSubsetIndex(dSubsubset,dSubset)){
					unsigned int ds = set.complement(dSubsubset, dSubset);
					dist = getForestDistance(pcur, s, dcur, ds)
					     + getForestDistance(pchildren[element], eSet, dcur, dSubsubset)
					     + operators->deletion(patternInfos->pathWeight(pcur, pchildren[element]));
				minDist = std::min(dist, minDist);
				}
			}
			setForestDistance(pcur,pSubset, dcur,dSubset, minDist);
			return minDist;
		}

			


	
		template<typename V, typename E>
		void HomeomorphicAlignment<V,E>::computeDeletions(std::vector<std::pair<unsigned int, unsigned int> >& patternOrder,
								  std::vector<std::pair<unsigned int, unsigned int> >& dataOrder,
								  Subset& set){
			std::vector<std::pair<unsigned int, unsigned int> >::iterator pit, pend, dit, dend;
			pit = patternOrder.begin();
			pend = patternOrder.end();
			//compute pattern deletions
			for(;pit!=pend;pit++){
				unsigned int cur = pit->first;
				unsigned int root = pit->second;
				//compute pattern forest deletion
				std::vector<unsigned int> children = patternInfos->children(cur);
				unsigned int chSet = childrenSet(children, root, set,patternInfos->isRooted());
				double dist = 0.0;
				for(unsigned int chSubset = 0; chSubset <= chSet; chSubset = set.nextSubsetIndex(chSubset,chSet)){
					dist = 0.0;
					if(!operators->patternCut()){
						for(char element = set.getNextElement(-1,chSubset); element != -1; 
								element=set.getNextElement(element,chSubset)){
								dist+=getPatternTreeDeletion(children[element], cur);		
						}
					}
					setPatternForestDeletion(cur, chSubset, dist);
				}
				//compute pattern tree deletion
				for(unsigned int v = 0; v < pSize; v++){
					if(patternInfos->parent(cur, v) != root || !fusionDistancePCheck(cur,v))continue;
					if(operators->patternCut())
						setPatternTreeDeletion(cur, v, 0.0);
					else 
						setPatternTreeDeletion(cur, v, dist+operators->deletion(patternInfos->pathWeight(v,cur)));
				}
			}
			dit = dataOrder.begin();
			dend = dataOrder.end();
			//compute data deletions
			for(;dit!=dend;dit++){
				unsigned int cur = dit->first;
				unsigned int root = dit->second;
			
				//compute data forest deletion
				std::vector<unsigned int> children = dataInfos->children(cur);
				unsigned int chSet = childrenSet(children, root, set,dataInfos->isRooted());
				double dist = 0.0;
				for(unsigned int chSubset = 0; chSubset <= chSet; chSubset = set.nextSubsetIndex(chSubset,chSet)){
					dist = 0.0;
					if(!operators->dataCut()){
						for(char element = set.getNextElement(-1,chSubset); element != -1; 
								element=set.getNextElement(element,chSubset)){
								dist+=getDataTreeDeletion(children[element], cur);		
						}
					}
					setDataForestDeletion(cur, chSubset, dist);
				}
				//compute data tree deletion
				for(unsigned int v = 0; v < dSize; v++){
					if(dataInfos->parent(cur, v) != root || !fusionDistanceDCheck(cur,v))continue;
					if(operators->dataCut())
						setDataTreeDeletion(cur, v, 0.0);
					else
						setDataTreeDeletion(cur, v, dist+operators->deletion(dataInfos->pathWeight(v,cur)));
				}
			}
		}






		template<typename V, typename E>
		double HomeomorphicAlignment<V,E>::findMinDistance(Subset& set){
			std::vector<unsigned int> proots = patternInfos->possibleRoots();
			std::vector<unsigned int> droots = dataInfos->possibleRoots();
			std::vector<unsigned int>::iterator dit2,dend2 = droots.end(), pit2,pend2 = proots.end();
			double minDist = std::numeric_limits<double>::max();
							
			for(pit2 = proots.begin();pit2!=pend2;pit2++){
				unsigned int proot = *pit2;
				std::vector<unsigned int> pchildren = patternInfos->children(proot);
				unsigned int pSet = set.set(pchildren.size());
				for(dit2 = droots.begin();dit2!=dend2;dit2++){
					unsigned int droot = *dit2;
					std::vector<unsigned int> dchildren = dataInfos->children(droot);
					unsigned int dSet = set.set(dchildren.size());
					double dist = getForestDistance(proot, pSet, droot, dSet);
					minDist = std::min(dist, minDist);
				}
			}
			return minDist;
		}






		template<typename V, typename E>
		double HomeomorphicAlignment<V,E>::compute(){
			int maxDegree = std::max(patternInfos->degree(),dataInfos->degree());
			Subset set(std::min(maxDegree,20)); 
			
			std::vector<std::pair<unsigned int, unsigned int> > patternOrder = patternInfos->navigationOrder();
			std::vector<std::pair<unsigned int, unsigned int> > dataOrder = dataInfos->navigationOrder();
			std::vector<std::pair<unsigned int, unsigned int> >::iterator pit, pend, dit, dend;
			//compute deletions
			computeDeletions(patternOrder, dataOrder, set);

			//compute common Distances
			pit = patternOrder.begin();
			pend = patternOrder.end();
			dend = dataOrder.end();
			for(;pit!=pend;pit++){
				unsigned int pcur = pit->first;
				unsigned int proot = pit->second;
				std::vector<unsigned int> pchildren = patternInfos->children(pcur);
				unsigned int pSet = childrenSet(pchildren, proot, set,patternInfos->isRooted());
					
				dit = dataOrder.begin();
				for(;dit!=dend;dit++){
					unsigned int dcur = dit->first;
					unsigned int droot = dit->second;
					std::vector<unsigned int> dchildren = dataInfos->children(dcur);
					unsigned int dSet = childrenSet(dchildren, droot, set,dataInfos->isRooted());
					//compute forest distances
					for(unsigned int pSubset = 0; pSubset <= pSet; pSubset = set.nextSubsetIndex(pSubset,pSet)){
						for(unsigned int dSubset = 0; dSubset <= dSet; dSubset = set.nextSubsetIndex(dSubset,dSet)){
							if(getForestDistance(pcur,pSubset, dcur,dSubset) != -1)continue;
							computeForestDistance(pcur, pSubset, pchildren, dcur, dSubset, dchildren, set);
						}
					}
					
					//compute tree distances
					if(pcur == proot || dcur == droot) continue;
					for(unsigned int panc = 0; panc < pSize; panc++){
						if(pcur == panc || patternInfos->parent(pcur, panc) != proot 
							|| !fusionDistancePCheck(pcur, panc))continue;
						for(unsigned int danc = 0; danc < dSize; danc++){
							if(dcur == danc || dataInfos->parent(dcur, danc) != droot 
								|| !fusionDistanceDCheck(dcur, danc))continue;
								computePrunedTreeDistance(pcur, panc, pSet, pchildren, dcur, danc, dSet, dchildren, set);
						}
					}
				}
			}
			return HADistance = findMinDistance(set);
		}
		



		template<typename V, typename E>template< typename D>
		double HomeomorphicAlignment<V,E>::compute(std::map<std::pair<unsigned int, unsigned int>, EdgeConstraint<D>* >& constraints, std::vector<D>& datas, bool leafAlignment){
			int maxDegree = std::max(patternInfos->degree(),dataInfos->degree());
			Subset set(std::min(maxDegree,20)); 
			std::vector<std::pair<unsigned int, unsigned int> > patternOrder = patternInfos->navigationOrder();
			std::vector<std::pair<unsigned int, unsigned int> > dataOrder = dataInfos->navigationOrder();
			std::vector<std::pair<unsigned int, unsigned int> >::iterator pit, pend, dit, dend;
			//compute deletions
			computeDeletions(patternOrder, dataOrder, set);

			//compute common Distances
			pit = patternOrder.begin();
			pend = patternOrder.end();
			dend = dataOrder.end();
			for(;pit!=pend;pit++){
				unsigned int pcur = pit->first;
				unsigned int proot = pit->second;
				std::vector<unsigned int> pchildren = patternInfos->children(pcur);
				unsigned int pSet = childrenSet(pchildren, proot, set,patternInfos->isRooted());
					
				dit = dataOrder.begin();
				for(;dit!=dend;dit++){
					unsigned int dcur = dit->first;
					unsigned int droot = dit->second;
					std::vector<unsigned int> dchildren = dataInfos->children(dcur);
					unsigned int dSet = childrenSet(dchildren, droot, set,dataInfos->isRooted());
					//compute forest distances					
					if(leafAlignment && (pchildren.size()==1 || dchildren.size()==1) && pchildren.size()!=dchildren.size())
						for(unsigned int pSubset = 0; pSubset <= pSet; pSubset = set.nextSubsetIndex(pSubset,pSet)){
							for(unsigned int dSubset = 0; dSubset <= dSet; dSubset = set.nextSubsetIndex(dSubset,dSet)){
								setForestDistance(pcur,pSubset, dcur,dSubset, 10000.0);
							}
						}
					else
						for(unsigned int pSubset = 0; pSubset <= pSet; pSubset = set.nextSubsetIndex(pSubset,pSet)){
							for(unsigned int dSubset = 0; dSubset <= dSet; dSubset = set.nextSubsetIndex(dSubset,dSet)){
								if(getForestDistance(pcur,pSubset, dcur,dSubset) != -1)continue;
								computeForestDistance(pcur, pSubset, pchildren, dcur, dSubset, dchildren, set);
							}
						}
					
					//compute tree distances
					if(pcur == proot || dcur == droot) continue;
					for(unsigned int panc = 0; panc < pSize; panc++){
						if(pcur == panc || patternInfos->parent(pcur, panc) != proot 
							|| !fusionDistancePCheck(pcur, panc))continue;
						for(unsigned int danc = 0; danc < dSize; danc++){
							if(dcur == danc || dataInfos->parent(dcur, danc) != droot 
								|| !fusionDistanceDCheck(dcur, danc))continue;
							std::pair<unsigned int , unsigned int > key = std::make_pair(pcur, panc);
							std::pair<unsigned int , unsigned int > invkey = std::make_pair(panc, pcur);
							
							if(constraints.find(key) != constraints.end() 
							&& !(((constraints.find(key))->second)->isOk(datas[dcur], datas[danc])))
								setTreeDistance(pcur, panc, dcur, danc, 10000.0);
							else if(constraints.find(invkey) != constraints.end() 
							&& !(((constraints.find(invkey))->second)->isOk(datas[danc], datas[dcur])))
								setTreeDistance(pcur, panc, dcur, danc, 10000.0);
							else
								computePrunedTreeDistance(pcur, panc, pSet, pchildren, dcur, danc, dSet, dchildren, set);
						}
					}
				}
			}
			return HADistance = findMinDistance(set);
		}

		
		template<typename V, typename E>
		unsigned int HomeomorphicAlignment<V,E>::getBestMatch(unsigned int vertex){
			Subset set(0);
			std::vector<unsigned int> pchildren = patternInfos->children(vertex);
			unsigned int pSet = set.set(pchildren.size());
			unsigned int res=0;
			for(unsigned int v = 0; v < dSize; v++){
					std::vector<unsigned int> dchildren = dataInfos->children(v);
					unsigned int dSet = set.set(dchildren.size());
					double dist = getForestDistance(vertex, pSet, v, dSet);
					if(dist==HADistance){
						res = v;
					}
			}
			return res;
		}
		
		template<typename V, typename E>
		std::vector<unsigned int> HomeomorphicAlignment<V,E>::getBestMatches(unsigned int vertex){
			Subset set(0);
			std::vector<unsigned int> pchildren = patternInfos->children(vertex);
			unsigned int pSet = set.set(pchildren.size());
			std::vector<unsigned int> res;
			for(unsigned int v = 0; v < dSize; v++){
					std::vector<unsigned int> dchildren = dataInfos->children(v);
					unsigned int dSet = set.set(dchildren.size());
					double dist = getForestDistance(vertex, pSet, v, dSet);
					if(dist<=HADistance*1.0001){
						res.push_back(v);
					}
			}
			return res;
		}
		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
