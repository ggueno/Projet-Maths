/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Maxtree.cpp created in 9 2009.
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
/*
 * Internal Includes
 */
#include "Maxtree.hpp"

/*
 * Namespace
 */
namespace kn{

	/*
	 * Functions definitions
	 */

		void Maxtree::hqueue_add(unsigned int h, unsigned int p){
			hqueue[h].push(p);
		}

		unsigned int Maxtree::hqueue_first(unsigned int h){
			unsigned int first = hqueue[h].front();
			hqueue[h].pop();
			return first;
		}

		bool Maxtree::hqueue_empty(unsigned int h){
			return hqueue[h].empty();
		}

		std::vector<unsigned int> Maxtree::neighbours(unsigned int p){
			std::vector<unsigned int>nb;
			unsigned int X = p%image->width();
			unsigned int Y = p/image->width();
			int xmin = X==0?0:-1;
			int xmax = X==(image->width()-1)?0:1;
			int ymin = Y==0?0:-1;
			int ymax = Y==(image->height()-1)?0:1;
			for(int x = xmin; x <= xmax; x++)
				for(int y = ymin; y <= ymax; y++){
					if(x==0 && y==0)continue;
					nb.push_back((unsigned int)((X+x)+(Y+y)*image->width()));
				}
			return nb;
		}


		unsigned int Maxtree::flood(unsigned int h){
//			std::cout<<"flooding du niveau "<<h<<std::endl;
			while(!hqueue_empty(h)){
				unsigned int p = hqueue_first(h);

				status[p] = number_nodes[h];
				if(components[h].size() <= number_nodes[h]){
					components[h].resize(number_nodes[h]+1);
					components[h][number_nodes[h]] = Component(h);
				}
				components[h][number_nodes[h]].addElement(p);
				std::vector<unsigned int>nb = neighbours(p);
				unsigned int orip = (*image)(p%image->width(),p/image->width());
//				std::cout<<"ORI(p)="<<orip<<std::endl;

//				std::cout<<nb.size()<<" voisins\n";
				std::vector<unsigned int>::iterator q = nb.begin(), end = nb.end();
				while(q!=end){
					if(status[*q] == notAnalyzed){
						unsigned int oriq = (*image)((*q)%image->width(),(*q)/image->width());
//						std::cout<<"ORI(q)="<<oriq<<std::endl;
						hqueue_add(oriq, *q);
						status[*q] = inTheQueue;
						node_at_level[oriq] = true;
						if(oriq > orip){
//							std::cout<<oriq<<">"<<orip<<std::endl;

							unsigned int m = oriq;
							do{
								 m = flood(m);
							}while(m!=h);
						}
					}
					q++;
				}
			}
//			std::cout<<"-> calcul d'affiliation"<<std::endl;

			number_nodes[h]++;
			tree[h].push_back(h+tree[h].size()*256);
			int m = h-1;
			while(m >= 0 && !node_at_level[m])
				m--;
			if(m>=0){
				unsigned int i = number_nodes[h]-1;
				unsigned int j = number_nodes[m];
				tree[h][i] = m+j*256;
			}
			node_at_level[h] = false;
//			std::cout<<"-> calcul d'affiliation terminé, m = "<<m<<std::endl;
			return m;
		}

		void Maxtree::compute(){
			unsigned char* buff = image->begin();
			unsigned int p = 0;
			unsigned int size = image->width()*image->height();
			unsigned char hmin = 255;
			unsigned minInd = 0;
			init();
			std::cout<<"recherche d'un pixel de valeur minimale\n";
			while(hmin != 0 && p < size){
				if(hmin >= buff[p]){
					minInd = p;
					hmin = buff[p];
				}
				p++;
			}
			std::cout<<"pixel de valeur minimale trouvé : val("<<minInd<<") = "<<(int)hmin<<"\n";
			node_at_level[hmin] = true;

			hqueue_add(hmin,minInd);
			flood(hmin);
			//total size computation
			for(int i = 255; i >= 0; i--){
				for(unsigned int j = 0; j < components[i].size(); j++){
					int level = tree[i][j];
					unsigned int nb = level/256;
					level%=256;
					if(level == i && nb == j)continue;
					components[level][nb].addSize(components[i][j].getSize());
				}
			}
			std::cout<<"finished state computation\n";
			std::queue<unsigned int> borders;
			unsigned int lastLine = size-image->width();
			for(unsigned int i = 0; i < image->width(); i++){
				borders.push(status[i]*256+(*image)(i,0));
				borders.push(status[lastLine+i]*256+(*image)(i,image->height()-1));
			}
			for(unsigned int j = 1; j < image->height()-1; j++){
				borders.push(status[j*image->width()]*256+(*image)(0,j));
				borders.push(status[(j+1)*(image->width())-1]*256+(*image)(image->width()-1,j));
			}

			while(!borders.empty()){
				unsigned int ind = borders.front();
				unsigned int nb = ind/256;
				unsigned int level= ind%256;
				borders.pop();

				if(!components[level][nb].isFinished())continue;
				components[level][nb].changeFinished(false);

				if(ind == tree[level][nb])continue;
				borders.push(tree[level][nb]);
			}

			std::cout<<"done\n";
		}


		void Maxtree::areaFilter(ImageGS8u& res, unsigned int delta){
			unsigned char* buffer = new unsigned char [image->size()];
			std::vector<unsigned int>::iterator it, end;
			for(int i = 255; i >= 0; i--){
				for(unsigned int j = 0; j < components[i].size(); j++){
					int level = i;
					unsigned int comp = j;
					while(components[level][comp].getSize()<delta){
						level = tree[level][comp];
						comp = level/256;
						level%=256;
						if(level == i && comp == j)break;
					}
					std::vector<unsigned int> pixels = components[i][j].getElements();
					for(it = pixels.begin(),end = pixels.end();it != end; it++){
						buffer[*it] = level;
					}
				}
			}
			res = kn::ImageGS8u(image->width(), image->height(), buffer);
		}






		RootedTree<Component, double> Maxtree::getAreaMaxtree(){
			std::vector<std::vector<unsigned int> > id;
			id.resize(256);
			std::cout<<"creation des identifiants\n";

			unsigned int s = 0;
			for(int i = 0; i < 256; i++){
				if(tree[i].size()==0)continue;
				id[i].resize(tree[i].size());
				for(unsigned int j = 0; j < tree[i].size();j++)
					id[i][j] = s++;
			}
			std::cout<<"creation des données des sommets\n";

			std::vector<Component> vdatas;
			for(unsigned int i = 0; i < 256; i++){
				vdatas.insert(vdatas.end(), components[i].begin(), components[i].end());
			}

			std::cout<<"creation des données des aretes\n";

			std::vector<double> edatas;
			std::vector<std::pair<unsigned int, unsigned int> > edges;

			for(int i = 255; i >= 0; i--){
				for(unsigned int j = 0; j < components[i].size(); j++){
					int level = tree[i][j];
					unsigned int nb = level/256;
					level%=256;
					if(level == i && nb == j)continue;
					unsigned int par = id[level][nb];
					unsigned int cur = id[i][j];
					edges.push_back(std::make_pair(par, cur));
					edatas.push_back(vdatas[cur].getSize()*1.0/vdatas[par].getSize());
				}
			}
			std::cout<<"creation du RootedTree\n";
			RootedTree<Component, double> rt(s, vdatas, edges, edatas, kn::BISPARSE);
			std::cout<<"fin\n";

			return rt;
		}


		RootedTree<Component, double> Maxtree::getAreaMaxtree(double delta){
			std::vector<std::vector<unsigned int> > id;
			id.resize(256);
			std::cout<<"creation des identifiants\n";

			unsigned int s = 0;
			std::vector<Component> vdatas;
			for(int i = 0; i < 256; i++){
				if(tree[i].size()==0)continue;
				id[i].resize(tree[i].size());
				for(unsigned int j = 0; j < tree[i].size();j++)
					if(components[i][j].getSize()>=delta){
						id[i][j] = s++;
						vdatas.push_back(components[i][j]);
					}
			}
			std::cout<<"creation des données des aretes\n";

			std::vector<double> edatas;
			std::vector<std::pair<unsigned int, unsigned int> > edges;

			for(int i = 255; i >= 0; i--){
				for(unsigned int j = 0; j < components[i].size(); j++){
					if(components[i][j].getSize()<delta)continue;
					int level = tree[i][j];
					unsigned int nb = level/256;
					level%=256;
					if(level == i && nb == j)continue;
					unsigned int par = id[level][nb];
					unsigned int cur = id[i][j];
					edges.push_back(std::make_pair(par, cur));
					edatas.push_back(vdatas[cur].getSize()*1.0/vdatas[par].getSize());
				}
			}
			std::cout<<"creation du RootedTree\n";
			RootedTree<Component, double> rt(s, vdatas, edges, edatas, kn::BISPARSE);
			std::cout<<"fin\n";

			return rt;
		}
		RootedTree<Component, double> Maxtree::getVolumeMaxtree(){
			std::vector<std::vector<unsigned int> > id;
			id.resize(256);
			std::cout<<"creation des identifiants\n";

			unsigned int s = 0;
			for(int i = 0; i < 256; i++){
				if(tree[i].size()==0)continue;
				id[i].resize(tree[i].size());
				for(unsigned int j = 0; j < tree[i].size();j++)
					id[i][j] = s++;
			}
			std::cout<<"creation des données des sommets\n";

			std::vector<Component> vdatas;
			for(unsigned int i = 0; i < 256; i++){
				vdatas.insert(vdatas.end(), components[i].begin(), components[i].end());
			}

			std::cout<<"creation des données des aretes\n";

			std::vector<double> edatas;
			std::vector<std::pair<unsigned int, unsigned int> > edges;

			for(int i = 255; i >= 0; i--){
				for(unsigned int j = 0; j < components[i].size(); j++){
					int level = tree[i][j];
					unsigned int nb = level/256;
					level%=256;
					if(level == i && nb == j)continue;
					unsigned int par = id[level][nb];
					unsigned int cur = id[i][j];
					edges.push_back(std::make_pair(par, cur));
					edatas.push_back((vdatas[cur].getLevel()-vdatas[par].getLevel())*vdatas[cur].getSize()*1.0/vdatas[par].getSize());
				}
			}
			std::cout<<"creation du RootedTree\n";
			RootedTree<Component, double> rt(s, vdatas, edges, edatas, kn::BISPARSE);
			std::cout<<"fin\n";

			return rt;
		}


		RootedTree<Component, double> Maxtree::getVolumeMaxtree(double delta){
			std::vector<std::vector<unsigned int> > id;
			id.resize(256);
			std::cout<<"creation des identifiants\n";

			unsigned int s = 0;
			std::vector<Component> vdatas;
			for(int i = 0; i < 256; i++){
				if(tree[i].size()==0)continue;
				id[i].resize(tree[i].size());
				for(unsigned int j = 0; j < tree[i].size();j++)
					if(components[i][j].getSize()>=delta){
						id[i][j] = s++;
						vdatas.push_back(components[i][j]);
					}
			}
			std::cout<<"creation des données des aretes\n";

			std::vector<double> edatas;
			std::vector<std::pair<unsigned int, unsigned int> > edges;

			for(int i = 255; i >= 0; i--){
				for(unsigned int j = 0; j < components[i].size(); j++){
					if(components[i][j].getSize()<delta)continue;
					int level = tree[i][j];
					unsigned int nb = level/256;
					level%=256;
					if(level == i && nb == j)continue;
					unsigned int par = id[level][nb];
					unsigned int cur = id[i][j];
					edges.push_back(std::make_pair(par, cur));
					edatas.push_back((vdatas[cur].getLevel()-vdatas[par].getLevel())*vdatas[cur].getSize()*1.0/vdatas[par].getSize());
				}
			}
			std::cout<<"creation du RootedTree\n";
			RootedTree<Component, double> rt(s, vdatas, edges, edatas, kn::BISPARSE);
			std::cout<<"fin\n";

			return rt;
		}

		RootedTree<Component, bool>* Maxtree::getFinishedCCMaxtree(){
			std::vector<std::vector<unsigned int> > id;
			id.resize(256);
			std::cout<<"creation des identifiants\n";

			unsigned int s = 0;
			std::vector<Component> vdatas;
			for(int i = 0; i < 256; i++){
				if(tree[i].size()==0)continue;
				id[i].resize(tree[i].size());
				for(unsigned int j = 0; j < tree[i].size();j++)
					if(components[i][j].isFinished() || s == 0){
						id[i][j] = s++;
						vdatas.push_back(components[i][j]);
					}
			}
			std::cout<<"creation des aretes\n";

			std::vector<bool> edatas;
			std::vector<std::pair<unsigned int, unsigned int> > edges;
			int exlevel;
			for(int i = 255; i >= 0; i--){
				for(unsigned int j = 0; j < components[i].size(); j++){
					if(!components[i][j].isFinished())continue;
					int level = tree[i][j];
					unsigned int nb = level/256;
					level%=256;
					if(level == i && nb == j)continue;
					while(!components[level][nb].isFinished()){
						exlevel = level;
						level = tree[level][nb];
						nb = level/256;
						level%=256;
						if(level == exlevel)break;
					}
					unsigned int par = id[level][nb];
					unsigned int cur = id[i][j];
					edges.push_back(std::make_pair(par, cur));
					edatas.push_back(false);
				}
			}
			std::cout<<"creation du RootedTree\n";

			std::cout<<"fin\n";

			return new RootedTree<Component, bool>(s, vdatas, edges, edatas, kn::BISPARSE);
		}

  /*
   * End of Namespace
   */
}
