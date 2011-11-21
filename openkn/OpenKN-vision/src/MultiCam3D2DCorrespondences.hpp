/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * MultiCam3D2DCorrespondences.hpp created in 09 2008.
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
 /**
   * \author Benjamin Raynal
   */

/*
 * Anti-doublon
 */
#ifndef __OPENKN_VISION__MULTICAM3D2DCORRESPONDENCES_HPP__
#define __OPENKN_VISION__MULTICAM3D2DCORRESPONDENCES_HPP__


/*
 * External Includes
 */
#include <vector>
#include <map>

/*
 * Internal Includes
 */
#include <OpenKN/math/Vector3.hpp>
#include <OpenKN/math/Vector4.hpp>
#include "VisionException.hpp"

namespace kn{

	/*
	 * Class definition
	 */

	/**
	 * \brief 2D points correspondences of 3D points, used for multi-cameras systems.
	*/
  class MultiCam3D2DCorrespondences{


	/*
	 * class variables
	 */
    protected:
	/**
	 * \brief vector of sequences of 3D points.
		Each sequence represents a 3D landmark (chessboard, for example)
	 */
	std::vector<std::vector<kn::Vector4d > > points3D;

	/**
	 * \brief vector of corresponding sequences of 2D points.
		Each key of a given map is the index of the camera where is projected the point.
	 */
	std::vector<std::map < unsigned int, std::vector<kn::Vector3d > > > points2D;


    public:

      /**
       * \brief Default constructor
       * Create a MultiCam3D2DCorrespondences
       */
      MultiCam3D2DCorrespondences(void){ }

      /**
       * \brief Destructor
       */
      ~MultiCam3D2DCorrespondences(void){}


    public:
      /**
       * \brief Add a sequence of 3D points
       * \param sequence the sequence of 3D points
       * \return the index of the sequence
       */
	unsigned int add3DPointsSequence(std::vector<kn::Vector4d >& sequence);

	/**
       * \brief Add a sequence of 2D points from a given camera matching with a given sequence of 3D points
       * \param sequence the sequence of 2D points
       * \param index3D the index of the sequence of 3D points
       * \param indexCam the index of the camera
       */
	void addCorresponding2DPointsSequence(unsigned int index3D, unsigned int indexCam, std::vector<kn::Vector3d >& sequence);

	/**
       * \brief Add a sequence of 2D points from a given camera matching with the last sequence of 3D points
       * \param sequence the sequence of 2D points
       * \param indexCam the index of the camera
       */
	inline void addCorresponding2DPointsSequence(unsigned int indexCam, std::vector<kn::Vector3d >& sequence){
		addCorresponding2DPointsSequence(points3D.size()-1, indexCam, sequence);
	}

	/**
       * \brief Return the number of sequences of 3D points
       * \return the number of sequences of 3D points
       */
	inline unsigned int getNb3DSequences()const {
		return points3D.size();
	}

	/**
       * \brief Return the sequence of 3D points at the given index
       * \param index the index of 3D points sequence
       * \return the sequence of 3D points at the given index
       */
	inline const std::vector<kn::Vector4d >& get3DSequence(unsigned int index) const{
		if(index >= points3D.size())
			throw VisionException("index out of bounds");
		return points3D[index];
	}


	/**
       * \brief Return the indices of cameras which have 2D points correspondences for the given 3D points sequence
       * \param index the index of 3D points sequence
       * \return vector of cameras indices
       */
	inline std::vector<unsigned int> getInvolvedCameras(unsigned int index) const {
		if(index >= points3D.size())
			throw VisionException("index out of bounds");
		std::vector<unsigned int> cams;
		std::map < unsigned int, std::vector<kn::Vector3d > > pts = points2D[index];
		std::map < unsigned int, std::vector<kn::Vector3d > >::iterator it = pts.begin(), end = pts.end();
		while(it!=end){
			cams.push_back(it->first);
			it++;
		}
		return cams;
	}



	/**
       * \brief Return the sequence of corresponding 2D points from a given camera for a given sequence of 3D points
       * \param sequenceIndex the index of 3D points sequence
       * \param cameraIndex the index of the camera
       * \return the sequence of 2D points
       */
	inline const std::vector<kn::Vector3d> getCorrespondingPoints(unsigned int sequenceIndex, unsigned int cameraIndex) const {
		if(sequenceIndex >= points2D.size())
			throw VisionException("index out of bounds");
		std::map < unsigned int, std::vector<kn::Vector3d > > ref = points2D[sequenceIndex];
		if(ref.count(cameraIndex)<1)
			throw VisionException("camera not involved");
		return ref[cameraIndex];
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
