/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * ioEPS_sample.cpp created in 04 2010.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-image.
 *
 * The OpenKraken-image is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-image is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * External Includes
 */

/*
 * Internal Includes
 */
#include <OpenKN/image/ioEPS.hpp>




int main()
{
  kn::ioEPS my_eps(300,300);


  my_eps.drawCircle(100,240,40, 1.0,0.0,0.0);
  my_eps.drawSquare(160,200, 240,280, 0.0,0.0,1.0,2);
  my_eps.drawCircleFilled(150,50,35, 0.0,1.0,0.0);
  my_eps.drawSquareFilled(115,50, 185,190, 1.0,1.0,0.0);
  my_eps.drawLine(150,15, 150,35, 1.0,0.0,0.5, 3);

  my_eps.saveEPS("outputData/epsTest.eps");

  return 0;
}
