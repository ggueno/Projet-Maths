/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * LambdaTree.hpp created in 9 2009.
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
#ifndef __OPENKN_MORPHOTOPO__LambdaTree_HPP__
#define __OPENKN_MORPHOTOPO__LambdaTree_HPP__

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
#include "Maxtree.hpp"
/*
 * Namespace
 */
namespace kn{	 
 
	/*
	 * Class definition
	 */
	
	class LambdaTree  {

		/*
		 * Constructor & destructors
		 */		 
	public:
		
	  	enum Connexity{CC8,CC4,CCX,CCY};

		inline LambdaTree(kn::Image<unsigned char>& image, Connexity connexity=CC4, unsigned char lambdaMin=0){
			this->lambdaMin = lambdaMin;
			this->connexity = connexity;
			changeImage(image);
		}
	  
	  	inline ~LambdaTree(){
	  	
	  	}
	
	private :
		std::vector<std::vector<unsigned int> > tree;
		std::vector<std::vector<Component> > components;
		unsigned char lambdaMin;
		unsigned int notAnalyzed;
		Connexity connexity;	
		kn::Image<unsigned char>* image;
		
	private :
		unsigned int find(std::vector<unsigned int>& unionfind, unsigned int a);
		
		void link(std::vector<unsigned int>& unionfind, unsigned int a, unsigned int b);
		
		std::vector<unsigned int> neighbours(unsigned int p);
		
		void compute();
		
	public :
		
		inline void changeImage(kn::Image<unsigned char>& image){
			this->image = &image;
			compute();
		}
		
		kn::RootedTree<kn::Component, bool>* getLambdaTree();


	};


	

	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
