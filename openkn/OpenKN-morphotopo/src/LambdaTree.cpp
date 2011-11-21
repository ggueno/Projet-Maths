/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * LambdaTree.cpp created in 9 2009.
 * Mail : biri@univ-mlv.fr
 *													   
 * This file is part of the OpenKraken-morphotopo.
 *
 * The OpenKraken-morphotopo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-morphotopo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

#include <algorithm>
#include <iostream>
#include <cmath>
/*
 * Internal Includes
 */
#include "LambdaTree.hpp"

//#define EUCLIDIAN_DIST
/*
 * Namespace
 */
namespace kn{

	/*
	 * Functions definitions
	 */

		
		
		std::vector<unsigned int> LambdaTree::neighbours(unsigned int p){
			std::vector<unsigned int>nb; 
			unsigned int X = p%image->width();
			unsigned int Y = p/image->width();
			if(connexity == CC8){
				int xmin = X==0?0:-1;
				int xmax = X==(image->width()-1)?0:1;
				int ymin = Y==0?0:-1;
				int ymax = Y==(image->height()-1)?0:1;
				for(int x = xmin; x <= xmax; x++)
					for(int y = ymin; y <= ymax; y++){
						if(x==0 && y==0)continue;
						nb.push_back((unsigned int)((X+x)+(Y+y)*image->width()));
					}
			}else{
				if(connexity != CCY){	
					if(X!=0)nb.push_back((unsigned int)((X-1)+(Y)*image->width()));
					if(X!=image->width()-1)nb.push_back((unsigned int)((X+1)+(Y)*image->width()));
				}
				if(connexity != CCX){			
					if(Y!=0)nb.push_back((unsigned int)((X)+(Y-1)*image->width()));
					if(Y!=image->height()-1)nb.push_back((unsigned int)((X)+(Y+1)*image->width()));
				}
			}
			return nb;
		}
		
		
		unsigned int LambdaTree::find(std::vector<unsigned int>& unionfind, unsigned int a){
			unsigned int root = a;
			while(unionfind[root]!=root)root=unionfind[root];
			unionfind[a] = root;
			return root;
		}
		
		void LambdaTree::link(std::vector<unsigned int>& unionfind, unsigned int a, unsigned int b){
			a = find(unionfind, a);
			b = find(unionfind, b);
			if(a < b)unionfind[b] = a;
			else unionfind[a] = b;
		}
		
		void LambdaTree::compute(){
			unsigned char* buff = image->begin();
			unsigned int width = image->width();
			unsigned int height = image->height();
			unsigned int size = width*height;
			unsigned int notAnalyzed = size+1;
			std::vector<std::queue<std::pair<unsigned int, unsigned int> > > links(256);
			std::vector<unsigned int> unionfind(size, notAnalyzed);
			components.resize(256);
			tree.resize(256);
			std::vector<std::vector<unsigned int> > cc(256);
			std::vector<unsigned int> id(size, notAnalyzed);
			unsigned int cpt = 0;
			//initial flooding
			std::cout<<"initial flooding\n";
			for(unsigned int i = 0; i < size; i++){
				if(unionfind[i] != notAnalyzed)continue;
				unionfind[i] = i;
				std::queue<unsigned int> fifo;
				fifo.push(i);
				id[i] = cpt++;
				kn::Component comp(lambdaMin);
				cc[lambdaMin].push_back(i); 
				while(!fifo.empty()){
					unsigned int element = fifo.front();
					fifo.pop();
					comp.addElement(element);
					std::vector<unsigned int> nb = neighbours(element);
					std::vector<unsigned int>::iterator it = nb.begin(), end = nb.end();
					while(it!=end){
						int lambda;
						if(image->nbChannel()==1){
							lambda = buff[element]-buff[*it];
							if(lambda<0)lambda=-lambda;
						}else{
#ifdef EUCLIDIAN_DIST
							int lambdaR = buff[element*3]-buff[(*it)*3];
							int lambdaG = buff[element*3+1]-buff[(*it)*3+1];
							int lambdaB = buff[element*3+2]-buff[(*it)*3+2];
							lambda = std::sqrt(lambdaR*lambdaR+lambdaB*lambdaB+lambdaG*lambdaG);
							
#else
							lambda = buff[element*3]-buff[(*it)*3];
							if(lambda<0)lambda=-lambda;
							int tmp = buff[element*3+1]-buff[(*it)*3+1];
							if(tmp<0)tmp=-tmp;
							if(tmp>lambda)lambda=tmp;
							tmp = buff[element*3+2]-buff[(*it)*3+2];
							if(tmp<0)tmp=-tmp;
							if(tmp>lambda)lambda=tmp;
#endif
						}

						if(lambda>lambdaMin){
							if(unionfind[*it] != notAnalyzed){
								links[lambda].push(std::make_pair(i, unionfind[*it]));
								
							}
						}else if(unionfind[*it] == notAnalyzed){
							unionfind[*it] = i;
							fifo.push(*it);
						}
						it++;
					}
				} 
				components[lambdaMin].push_back(comp);
			}

			

			//computation of mergings
			std::cout<<"computation of mergings\n";
			for(unsigned int lambda = lambdaMin+1; lambda < 256; lambda++){
				//merging
				if(cc[lambda-1].size()>0)
				while(!links[lambda].empty()){
					std::pair<unsigned int, unsigned int> l = links[lambda].front();
					links[lambda].pop();
					link(unionfind, l.first, l.second);
				}
				//computation of new level
				std::vector<unsigned int>::iterator it = cc[lambda-1].begin(), end = cc[lambda-1].end();
				cpt = 0;
				while(it!=end){
					unsigned int root = find(unionfind, *it);
					tree[lambda-1].push_back(root);
					if(*it == root){
						cc[lambda].push_back(root);
						id[root] = cpt++;
					}
					it++;
				}
				//relabeling parents
				for(unsigned int i = 0; i < tree[lambda-1].size(); i++){
					tree[lambda-1][i] = id[tree[lambda-1][i]];
				}
			}
			for(unsigned int i = 0; i < tree[254].size(); i++)
				tree[254][i] = 0;
			
			tree[255].resize(1,0);
			
			//computation of components size
			std::cout<<"computation of components size\n";
			for(unsigned int lambda = lambdaMin; lambda < 255; lambda++){
				components[lambda+1].resize(tree[lambda+1].size(), kn::Component(lambda+1));
				for(unsigned int c = 0; c < tree[lambda].size(); c++){
					unsigned int parent = tree[lambda][c]; 
					components[lambda+1][parent].addSize(components[lambda][c].getSize());	
				}
			} 
			std::cout<<"fin\n";
		}
	
		
		
		kn::RootedTree<kn::Component, bool>* LambdaTree::getLambdaTree(){
			std::cout<<"computation of rooted tree\n";
			unsigned int levelRoot = 255;
			while(tree[levelRoot-1].size()==1){
				levelRoot--;
			}
			std::cout<<"computation of children degree\n";
			
			std::vector< std::vector< unsigned int> > nbch(256);
			nbch[0].resize(components[0].size(),0);
			for(unsigned int l = 0; l < levelRoot;l++){
				nbch[l+1].resize(tree[l+1].size(),0);
				for(unsigned int v = 0; v < tree[l].size(); v++){
					nbch[l+1][tree[l][v]]++;
				}
			}

			
			unsigned int s = 0;
			std::vector< std::vector< unsigned int> > v(256);
			std::cout<<"vertices labeling\n";
			v[levelRoot].push_back(s++);
			std::vector<kn::Component> vdatas;
			vdatas.push_back(components[levelRoot][0]);
			for(int l = levelRoot-1; l >= (int)lambdaMin; l--){
				for(unsigned int i = 0; i < tree[l].size(); i++){
					if(nbch[l][i] == 1){
						v[l].push_back(notAnalyzed);
						continue;
					}
					v[l].push_back(s++);
					vdatas.push_back(components[l][i]);
				}
			}
			std::cout<<"edges computation\n";
			std::vector<bool> edatas(s-1,false);
			std::vector<std::pair<unsigned int, unsigned int> > edges;
			for(unsigned int l = lambdaMin; l < levelRoot; l++){
				for(unsigned int i = 0; i < tree[l].size(); i++){
					if(nbch[l][i] == 1)continue;
					unsigned int level = l+1;
					unsigned int cc = tree[l][i];
					while(level<levelRoot && nbch[level][cc] == 1){
						cc = tree[level][cc];
						level = level+1;
					}
					edges.push_back(std::make_pair(v[level][cc], v[l][i]));
				}
			}
			return new RootedTree<Component, bool>(s, vdatas, edges, edatas, kn::BISPARSE,false);
		}
		
		
		

		
  /*
   * End of Namespace
   */
}
