/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Maxtree.hpp created in 9 2009.
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

/*
 * Anti-doublon
 */
#ifndef __OPENKN_MORPHOTOPO__MAXTREE_HPP__
#define __OPENKN_MORPHOTOPO__MAXTREE_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <OpenKN/image/ImageGS.hpp>
#include <OpenKN/graph/RootedTree.hpp>
/*
 * Internal Includes
 */

/*
 * Namespace
 */
namespace kn{	

	class Component{
		private :
			bool finished;
			unsigned char level;
			unsigned int size;
			std::vector<unsigned int> elements;
		
		public : 
		inline Component(unsigned char level){
			finished = true;
			size = 0;
			this->level = level;
		}
		inline Component(){
			finished = true;
			size = 0;
			level = 0;
		}
		
		inline Component(const Component& component){
			this->finished = component.finished;
			this->level = component.level;
			this->size = component.size;
			this->elements = component.elements;
		}
		
		inline ~Component(){
		}
		
		inline void addElement(unsigned int element){
			elements.push_back(element);
			size++;
		}
		
		inline void addSize(unsigned int size){
			this->size += size;
		}
		
		inline void setSize(unsigned int size){
			this->size = size;
		}

		inline void changeFinished(bool state){
			finished = state;
		}

		inline bool isFinished(){
			return finished;
		}

		inline unsigned int getSize(){
			return size;
		}
		
		inline unsigned char getLevel(){
			return level;
		}
		
		inline std::vector<unsigned int>& getElements(){
			return elements;
		}
	};




	/*
	 * Class definition
	 */
	
	class Maxtree  {

		/*
		 * Constructor & destructors
		 */		 
	public:
		inline Maxtree(ImageGS8u& image){
			changeImage(image);
		}
	  
	  	inline ~Maxtree(){
	  	
	  	}
	  
	private :
		std::vector<unsigned int> status;
		std::vector<std::queue<unsigned int> > hqueue;
		std::vector<unsigned int> number_nodes;
		std::vector<std::vector<unsigned int> > tree;
		std::vector<std::vector<Component> > components;
		std::vector<bool> node_at_level;
		unsigned int notAnalyzed;
		unsigned int inTheQueue;
		ImageGS8u* image;
		
	private :
		void hqueue_add(unsigned int h, unsigned int p);
		
		unsigned int hqueue_first(unsigned int h);
	
		bool hqueue_empty(unsigned int h);
		
		std::vector<unsigned int> neighbours(unsigned int p);
		
		
		
		inline void init(){
			unsigned int size = image->width()*image->height();
			notAnalyzed = size+1;
			inTheQueue = size+2;
			status = std::vector<unsigned int>(size,notAnalyzed);
			hqueue =  std::vector<std::queue<unsigned int> >(256);
			number_nodes = std::vector<unsigned int>(256);
			tree = std::vector<std::vector<unsigned int> >(256);
			components = std::vector<std::vector<Component> > (256);
			node_at_level = std::vector<bool> (256, false);
		}
		
		unsigned int flood(unsigned int h);
		
		void compute();
		
	public :
		
		inline void changeImage(ImageGS8u& image){
			this->image = &image;
			compute();
		}
		

		RootedTree<Component, double> getAreaMaxtree();
		
		RootedTree<Component, double> getAreaMaxtree(double delta);
		
		RootedTree<Component, double> getVolumeMaxtree();
		
		RootedTree<Component, double> getVolumeMaxtree(double delta);
		
		RootedTree<Component, bool>* getFinishedCCMaxtree();
		
		void areaFilter(ImageGS8u& res, unsigned int delta);
		
	};


	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
