/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Triangulation.hpp created in 12 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-vision.
 *
 * The OpenKraken-vision is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-vision is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_VISION__TRIANGULATION_HPP__
#define __OPENKN_VISION__TRIANGULATION_HPP__

/*
 * External Includes
 */
#include <vector>

/*
 * Internal Includes
 */
#include <OpenKN/math/Vector.hpp>
#include <OpenKN/math/Matrix.hpp>

/*
 * Namespace
 */
namespace kn{

	/**
	 * \brief Compute the triangulation from 2 cameras : the pixel x1 in camera P1 and the pixel x2 from camera P2, cf : Multiple view geometry (2nd ed): cahpter 12.2 page 312
	 * \param P1 : a 3x4 projection matrix
	 * \param P2 : a 3x4 projection matrix
	 * \param x1 : a 3-vector in homogeneous coordinates
	 * \param x2 : a 3-vector in homogeneous coordinates
	 * \return the triangulated point (4-vector in homogeneous coordinates)
	 * \throw VisionException invalite matrix size
	 */
	kn::Vector4d linearTriangulation(const kn::Matrix<double>  & P1,
						const kn::Matrix<double>  & P2,
						const kn::Vector3d & x1,
						const kn::Vector3d & x2);


	/**
	 * \brief Compute the triangulation from n cameras (n>1), cf : Multiple view geometry (2nd ed): cahpter 12.2 page 312
	 * \param P : a list of 3x4 projection matrices
	 * \param x : a list of pixel (3-vector in homogeneous coordinates)
	 * \return the triangulated point (4-vector in homogeneous coordinates).
	 * \throw VisionException invalite matrix size
	 */
	kn::Vector4d linearTriangulation(const std::vector<kn::Matrix<double> >   & P,
						const std::vector<kn::Vector3d >  & x);


	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
