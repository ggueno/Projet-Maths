/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Subset.cpp created in 10 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-math.
 *
 * The OpenKraken-Subset is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-Subset is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

#include "Subset.hpp"
#include <vector>
#include <cmath>
#include <iostream>
/*
 * Namespace
 */
namespace kn {

			Subset::Subset(unsigned int maxStored){
				this->maxStored = maxStored;
				unsigned int max = std::pow(2.0, (int)maxStored)+1;
				subsets.resize(max);		
				for(unsigned int i = 0; i < max; i++){
					subsets[i] = getSubset(i);
				}
			}
			
			Subset::~Subset(){
				
			}
			 
			const std::vector<unsigned char> Subset::getSubset(unsigned int index){
				if(index < subsets.size() &&  subsets[index].size()>0)
					return subsets[index];
				std::vector<unsigned char> subset;
				unsigned int mask = 1;
				unsigned char val = 0;
				while(mask <= index){
					if(index & mask)
						subset.push_back(val);
					mask <<= 1;
					val++;
				}
				return subset;
			}
			
			bool Subset::isSubset(unsigned int subset, unsigned int set){
				return subset == (subset&set);
			}
			
			unsigned int Subset::nextSubsetIndex(unsigned int subset, unsigned int set){
				if(subset >= set)return set+1;
				subset++;
				while(!isSubset(subset, set))subset++;
				return subset;
			}
			
			unsigned int Subset::complement(unsigned int subset, unsigned int set){
				return (~subset)&set;
			}
			
			unsigned int Subset::set(unsigned char size){
				unsigned int s = 0;
				unsigned int mask = 1;
				for(unsigned char i = 0; i < size; i++){
					s|=mask;
					mask<<=1;
				}
				return s;				
			}
			unsigned int Subset::setWithoutParia(unsigned int set, unsigned char paria){
				unsigned int mask = 1;
				mask <<= paria;
				if(set&mask)return set-mask;
				return set;
			}
			
			char Subset::getNextElement(char element, unsigned int set){
				unsigned int mask = 1;
				element++;
				mask<<=element;
				while(!(set & mask) && mask <= set){
					element++;
					mask<<=1;
				}
				if(mask>set)return -1;
				return element;
			}
  /*
   * End of Namespace
   */
}

