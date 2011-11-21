/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ExtrinsicMultiCameraAdjustment.cpp created in 12 2008.
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
 * External Includes
 */
#include <vector>
#include <map>
#include <math.h>
/*
 * Internal Includes
 */
#include <ProjectiveCamera.hpp>
#include <CameraCalibrationZhang.hpp>

#include <OpenKN/math/Quaternion.hpp>
#include <OpenKN/math/InverseMatrix.hpp>
#include <Homography.hpp>
#include <MultiCam3D2DCorrespondences.hpp>
#include <OpenKN/math/Vector.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Matrix4x4.hpp>
/*
 * Namespace
 */

namespace kn{

	typedef std::pair<unsigned int, unsigned int> Pair;
	typedef std::pair<double, double> Pairf;



	kn::Matrix4x4d IT2MT(kn::Vectord it){
		kn::Quaterniond q(it[0], it[1], it[2], it[3]);
		kn::Matrix4x4d res = q.getMatrix4();
		res(0,3) = it[4];
		res(1,3) = it[5];
		res(2,3) = it[6];
		return res;
	}


	kn::Vectord MT2IT(kn::Matrix4x4d mt){
		kn::Quaterniond q(mt);
		kn::Vector<double> res(7);
		res.fill(0.0);
		for(int i = 0; i < 4; i++)
			res[i] = q[i];
		for(int i = 0; i < 3; i++)
			res[i+4] = mt(i,3);
		return res;
	}



	kn::Vectord interpolate(kn::Vectord a, kn::Vectord b, unsigned int wa, unsigned int wb){
		if(wa <= 0) return b;
		if(wb <= 0) return a;
		kn::Quaterniond aq(a[0], a[1], a[2], a[3]);
		aq.normalize();
		kn::Quaterniond bq(b[0], b[1], b[2], b[3]);
		bq.normalize();
		double wA = (double)wa*1.0/(wa+wb);

		kn::Vector<double> res(7);
		res.fill(0.0);
		kn::Quaterniond resq = kn::slerp(aq,bq, wA);
		resq.normalize();
		for(int i = 0; i < 4; i++)
			res[i] = resq[i];

		for(int i = 4; i < 7; i++)
			res[i] = (a[i]*wa+b[i]*wb)*1.0/(wa+wb);
		return res;
	}



	double getVariation(kn::Matrix4x4d & A, kn::Matrix4x4d & B){
		const double* a = A.getMatrixArray();
		const double* b = B.getMatrixArray();
		double sum = 0.0;
		for(int i = 0; i < 12; i++){
			double v = a[i]-b[i];
			sum+=v>0.0?v:-v;
		}
		return sum;
	}



	std::vector< std::map < Pair, kn::Matrix4x4d> > computeMesures(std::vector< kn::ProjectiveCamera >& cameras,
																																 const kn::MultiCam3D2DCorrespondences & correspondences) {
		std::vector< std::map < Pair, kn::Matrix4x4d> > mesures;
		for(unsigned int k = 0; k < correspondences.getNb3DSequences(); k++){
			std::vector< kn::Vector4d > seq3D = correspondences.get3DSequence(k); // vector of 3d points
			std::vector<unsigned int> cams = correspondences.getInvolvedCameras(k); // vector of involved cameras
			std::map < unsigned int, kn::Matrix4x4d> absoluteMesure;

			//absolute mesure computation
			for(unsigned int j = 0; j < cams.size(); j++){
				unsigned int camNum = cams[j];
				std::vector< kn::Vector3d > seq2D = correspondences.getCorrespondingPoints(k, camNum);
				std::vector< std::pair<kn::Vector3d,kn::Vector3d> > correspondanceList;
				std::vector< kn::Vector4d >::iterator it3D = seq3D.begin(), end3D = seq3D.end();
				std::vector< kn::Vector3d >::iterator it2D = seq2D.begin();

				while(it3D!=end3D){
	 				kn::Vector3d pt;
					pt[0] = (*it3D)[0];
					pt[1] = (*it3D)[1];
					pt[2] = 1.0;
					correspondanceList.push_back(std::pair<kn::Vector3d,kn::Vector3d >(pt,*it2D));
					it3D++;
					it2D++;
				}

				kn::Matrix3x3d H = kn::computeHomographyNormalized(correspondanceList);

				computeExternalParametersZhang(H,cameras[camNum]);
				kn::Matrix3x3d r = cameras[camNum].R();
				kn::Vector4d c = cameras[camNum].C();

				kn::Vector3d t;
				t[0] = c[0]/c[3];
				t[1] = c[1]/c[3];
				t[2] = c[2]/c[3];
				t = -(r*t);

				kn::Matrix4x4d m;
				m.setIdentity();
				m.setSubMatrix (0, 0, r);
				m(0,3) = t[0];
				m(1,3) = t[1];
				m(2,3) = t[2];
				absoluteMesure[camNum] = m;
			}

			//relative mesure computing
			kn::Matrix4x4d zero(0.0);
			std::map < Pair, kn::Matrix4x4d> relativeMesure;
			for(unsigned int i = 0; i < cams.size(); i++){
				for(unsigned int j = i+1; j < cams.size(); j++){
					kn::Matrix4x4d mat = absoluteMesure[cams[i]]*kn::inverseMatrixSVD(absoluteMesure[cams[j]]);
					relativeMesure[Pair(cams[i],cams[j])] = mat;
					relativeMesure[Pair(cams[j],cams[i])] = kn::inverseMatrixSVD(mat);
				}
			}
			mesures.push_back(relativeMesure);
		}
		return mesures;
	}





	void extrinsicMultiCameraAdjustment(std::vector< kn::ProjectiveCamera >& cameras, const kn::MultiCam3D2DCorrespondences & correspondences){
		std::vector<std::map <Pair, kn::Matrix4x4d> > mesures = computeMesures(cameras, correspondences);
		std::map<Pair, kn::Vectord> avgExp;
		std::map<Pair, unsigned int>   nbExp;
		std::map<Pair, kn::Vectord> avgIt;
		std::map<Pair, unsigned int>   nbIt;
		std::map<Pair, kn::Matrix4x4d> values;
		double epsilon = 0.0001;
		unsigned int maxIterations = 10000;
		//experimental average matrix computation
		for(unsigned int i = 0; i < cameras.size(); i++){
			for(unsigned int j = 0; j < cameras.size(); j++){
				if(i == j)continue;
				unsigned int count = 0;
				std::vector<std::map<Pair,kn::Matrix4x4d> >::iterator it = mesures.begin(), end = mesures.end();
				kn::Vectord sum(7);
				sum.fill(0.0);

				while(it != end){
					std::map<Pair, kn::Matrix4x4d> mesure = (*it);
					if(mesure.count(Pair(i,j)) != 0){
						sum = interpolate(sum,MT2IT(mesure[Pair(i,j)]), count,1);
						count++;
						for(unsigned int k = 0; k < cameras.size(); k++){
							if(k == i || k == j || it->count(Pair(i,k)) == 0 || it->count(Pair(k,j)) == 0)continue;
							sum = interpolate(sum,MT2IT((mesure[Pair(i,k)]) * (mesure[Pair(k,j)])),count,1);
							count++;
						}
					}
					it++;
				}
				nbExp[Pair(i,j)] = count;
				avgExp.insert(std::pair<Pair,kn::Vectord>(Pair(i,j),sum));
			}
		}

		//iterative average matrix initialization
		kn::Vector<double> initiZero(7);
		initiZero.fill(0.0);
		for(unsigned int i = 0; i < cameras.size(); i++){
			for(unsigned int j = 0; j < cameras.size(); j++){
				avgIt.insert(std::pair<Pair,kn::Vectord>(Pair(i,j), initiZero));
				nbIt[Pair(i,j)] = 0;
			}
		}

		bool loop = false;
		unsigned int iterations = 0;
		do{
			loop = false;
			//new values computation
			for(unsigned int i = 0; i < cameras.size(); i++){
				for(unsigned int j = i+1; j < cameras.size(); j++){
					if(i == j)continue;
					Pair key = Pair(i,j);
					if(nbExp[key]==0 && nbIt[key]==0)continue;
					kn::Vector<double> sum(7);
					sum.fill(0.0);
					
					sum=interpolate(avgExp[key],avgIt[key],nbExp[key],nbIt[key]);
					kn::Matrix4x4d matTrans = IT2MT(sum);
					double var = getVariation(matTrans, values[key]);
					if(var > epsilon)
						loop = true;
					values[key] = matTrans;
					key = Pair(j,i);
					values[key] = kn::inverseMatrixSVD(matTrans);
				}
			}


			//new iteration computation
			for(unsigned int i = 0; i < cameras.size(); i++){
				for(unsigned int j = 0; j < cameras.size(); j++){
					if(i == j)continue;
					Pair key = Pair(i,j);
					unsigned int count = nbIt[key];
					kn::Vectord sum = avgIt[key];
					if(values.count(Pair(i,j)) != 0){
					 	sum=interpolate(sum,MT2IT(values[key]), count,1);
						count++;
					}
					for(unsigned int k = 0; k < cameras.size(); k++){
						if(k == i || k == j || values.count(Pair(i,k)) == 0 || values.count(Pair(k,j)) == 0) continue;
						sum=interpolate(sum,MT2IT(values[Pair(i,k)]*values[Pair(k,j)]), count,1);
						count++;
					}
				nbIt[key] = count;
				avgIt[key] = sum;
				}
			}
		}while(loop && ++iterations<maxIterations);

		//final relative cameras extrinsic parameters matrix filling
		std::vector<kn::ProjectiveCamera>::iterator it = cameras.begin(), end = cameras.end();
		kn::Matrixd id(3,4,0.0);
		id(0,0) = id(1,1) = id(2,2) = 1.0;
		it->updateRC(id);
		it++;
		int cpt = 1;
		while(it!=end){
			kn::Matrix4x4d res = values[Pair(cpt,0)];
			const double* buff = res.getMatrixArray();
			kn::Matrixd P(3,4, const_cast<double*>(buff));
			it->updateRC(P);
			cpt++;
			it++;
		}
	}



	/*
	 * End of Namespace
	 */
}
