/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Vector.cpp created in 10 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-math.
 *
 * The OpenKraken-math is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-math is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

#include "Vector.hpp"

/*
 * Namespace
 */
namespace kn{

  template class Vector<float,DynamicStorePolicy<float> >;
  template class Vector<int,DynamicStorePolicy<int> >;
  template class Vector<double,DynamicStorePolicy<double> >;

  template class Vector<float,StaticStorePolicy<float,2> >;
  template class Vector<double,StaticStorePolicy<double,2> >;
  template class Vector<float,StaticStorePolicy<float,3> >;
  template class Vector<double,StaticStorePolicy<double,3> >;
  template class Vector<float,StaticStorePolicy<float,4> >;
  template class Vector<double,StaticStorePolicy<double,4> >;

	/*
  template class Vector<float,3>;
  template class Vector<int,3>;
  template class Vector<double,3>;
	*/

  /*
   * End of Namespace
   */
}
