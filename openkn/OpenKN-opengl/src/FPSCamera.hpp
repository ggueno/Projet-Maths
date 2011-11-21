/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * FPSCamera.hpp created in 2 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKN-opengl.
 *
 * The OpenKN-opengl is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published yb
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKN-opengl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_FPS_CAMERA_HPP__
#define __OPENKN_FPS_CAMERA_HPP__

/*
 * External Includes
 */
#include <GL/glew.h>
#include <OpenKN/math/Vector.hpp>
#include <OpenKN/math/Matrix4x4.hpp>

/** \addtogroup Macros */
/*@{*/
/** \defgroup type_camera Types de camera */
/*@{*/
/** Perspective camera (classique). */
#define CAM_TYPE_PERSPEC	0
/** Orthographique camera */
#define CAM_TYPE_ORTHO		1
/*@}*/
/*@}*/

/*
 * Internal Includes
 */
#include "OpenglException.hpp"

/*
 * Namespace
 */
namespace kn {
	
	/**
	 * \brief FPS Camera management
	 * This class handles a FPS type camera and its moves
	 * \TODO Statute on projection
	 * \TODO Remove this parameter of orientation
	 * @author Venceslas Biri
	 */
	class FPSCamera {
	public:
		FPSCamera();
		FPSCamera(Vector3f pos_init,Vector3f dir_init,
							Vector3f top_init = Vector3f(0.0,1.0,0.0),
							Vector3f orient_init = Vector3f(0.0,0.0,0.0));
		~FPSCamera();

		/// OpenGL 2- : fixing projection matrix...
		/// \todo Implement this method ? It must include intrinsec parameter of the camera which is redondant from the OpenKN Vision camera
		void setProjectionGL();
		/** Setting OpenGL camera
			* This function set the OpenGL command directly : call the gluLookAt with correct parameters
			* \deprecated
			*/
		void setTransfoGL();
		/** \brief Reset position and orientation of camera
		 * Reset all the extrinsic parameters (position / orientation) of the camera and also init position/orientation
		 * \param pos_init initial position
		 * \param dir_init initial view direction
		 * \param top_init initial up vector
		 * \param orient_init initial angles of rotation
		 */
		void reinitPosCam(Vector3f pos_init,Vector3f dir_init,
											Vector3f top_init = Vector3f(0.0,1.0,0.0),
											Vector3f orient_init = Vector3f(0.0,0.0,0.0));

		/** \name Fonctions de déplacement générique (déplacement / orientation)
			*/
		//@{
		/** Moving forward
			* Move by \a step in the viewing direction
			* \param step moving distance
			*/
		void stepFront(float step);
		/** Moving backward
			* Move by - \a step in the viewing direction
			* \param step moving distance
			*/
		void stepBack(float step);
		/** Moving left
			* Move by \a step in the vector obtained by cross product from up and viewing direction
			* \param step moving distance
			*/
		void stepLeft(float step);
		/** Moving right
			* Move by - \a step in the vector obtained by cross product from up and viewing direction
			* \param step moving distance
			*/
		void stepRight(float step);
		/** Moving up
			* Move by \a step in the up direction
			* \param step moving distance
			*/
		void stepUp(float step);
		/** Moving up
			* Move by -\a step in the up direction
			* \param step moving distance
			*/
		void stepDown(float step);
		/** Incremental look at right
			* Change the orientation by a few \a angle (related to up axe)
			* \param angle incremental angle
			*/
		void lookRight(float angle);
		/** Incremental look at left
			* Change the orientation by a few - \a angle (related to up axe)
			* \param angle incremental angle
			*/
		void lookLeft(float angle);
		/** Incremental look up
			* Change the orientation by a few \a angle (related to vector up^view)
			* \param angle incremental angle
			*/
		void lookUp(float angle);
		/** Incremental look down
		 * Change the orientation by a few - \a angle (related to vector up^view)
		 * \param angle incremental angle
		 */
		void lookDown(float angle);
		//@}

		/** \brief Get Modelview Matrix
			* Return the view matrix as a Matrix 4x4 of float
			* \return modelview matrix
			*/
		Matrix4x4f getModelviewMatrix();

		/// Position of camera (related to the canonical OpenGL coordinate system)
		Vector3f position_cam;
		/// View vector of camera (related to the canonical OpenGL coordinate system)
		Vector3f view_dir_cam;
		/// Initial view vector of camera (related to the canonical OpenGL coordinate system)
		Vector3f dir_init_cam;
		/// Up vector of camera (related to the canonical OpenGL coordinate system)
		Vector3f top__dir_cam;
		/// Initial up vector of camera (related to the canonical OpenGL coordinate system)
		Vector3f top_init_cam;
		/// Orientation of camera regarding canonical axes x, y and z
		/// \todo Passer en quaternion...
		Vector3f orientat_cam;
		int type_cam; ///< Camera type (Orthographic / Perspective) \see type_cam
		Matrix4x4f modelview;
	private:
		/// Vectors reset after any rotation
		void reactuOrientation();
		void reactuPosModelview();
		void computeModelview();
	};
	
	/// Stream information
	extern std::ostream& operator<<(std::ostream& os,const kn::FPSCamera & src);
}

#endif

