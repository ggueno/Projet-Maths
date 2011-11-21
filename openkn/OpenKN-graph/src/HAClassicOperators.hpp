/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * HAOperators.hpp created in 09 2008.
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
#ifndef __OPENKN_GRAPH__HACLASSICOPERATORS_HPP__
#define __OPENKN_GRAPH__HACLASSICOPERATORS_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4996)
#endif

/*
 * External Includes
 */

#include <cmath>


/*
 * Internal Includes
 */

#include "HAOperators.hpp"
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
		class HAClassicOperators : public HAOperators<V,E>{
		
		
		private :
			bool _patternCut;
			bool _dataCut;
		
			/*
			 * Constructor & destructors
			 */
		public :
			inline HAClassicOperators(bool patternCut = false, bool dataCut = true){
				_patternCut = patternCut;
				_dataCut    = dataCut;
			}
			 
			inline ~HAClassicOperators(){
			 
			}
			
			
		public : 
			
			inline double deletion(E weight){
				if((double)weight<0)return 1000000.0;
				return std::abs(double(weight));
			}
			
			inline double resize(E patternWeight, E dataWeight){
				if((double)patternWeight<0){
					if((double)dataWeight<0){
						return 0.0;
					}
					return 1000000.0;
				}
				else if((double)dataWeight<0)return 1000000.0;
				return std::abs(double(patternWeight-dataWeight));
			}
			
			inline bool patternCut(){
			 	return _patternCut;
			}
			
			inline bool dataCut(){
				return _dataCut;
			}
			
		};

	
	
		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
