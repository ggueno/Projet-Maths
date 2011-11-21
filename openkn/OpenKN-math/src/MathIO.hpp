/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * MathIO.hpp created in 04 2009.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/



/*
 * Anti-doublon
 */
#ifndef __OPENKN_MATH__MATH_IO_HPP__
#define __OPENKN_MATH__MATH_IO_HPP__

/*
 * External Includes
 */
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

#include <sstream>

/*
 * Internal Includes
 */
#include "Matrix.hpp"
#include "Vector.hpp"
#include "MathException.hpp"

/*
 * Namespace
 */
namespace kn {

	/**
		* \cond
		* \brief ignore the comments and read the header on a matrix file if specified; the user should not use this function.
		* \param matrixFile the input matrix ifstream
		* \return true if the matrix format is spefifyed, false otherwise
		* \throw MathException invalid format
		* \author Vincent
		*/
	bool readMatrixHeader(std::ifstream &matrixFile, unsigned int &row, unsigned int &column);
	/// \endcond

	/**
		* \cond
		* \brief ignore the comments and read the header on a matrix file if specified; the user should not use this function.
		* \param matrixFile the input matrix ifstream
		* \return true if the matrix format is spefifyed, false otherwise
		* \throw MathException invalid format
		*/
	bool readMatrixHeader(std::ifstream &matrixFile, unsigned int &mat);
	/// \endcond

	/**
		* \cond
		* \brief ignore the comments and read the header on a matrix file if specified; the user should not use this function.
		* \param vectorFile the input vector ifstream
		* \param vec the number of vector in the file
		* \return true if the vector format is spefifyed, false otherwise
		* \throw MathException invalid format
		*/
	bool readVectorHeader(std::ifstream &vectorFile, unsigned int &vec);
	/// \endcond

	/**
		* \cond
		* \brief ignore the comments and read the header on a matrix file if specified; the user should not use this function.
		* \param vectorFile the input vector ifstream
		* \param vec the number of vector in the file
		* \return true if the vector format is spefifyed, false otherwise
		* \throw MathException invalid format
		*/
	bool readVectorSubHeader(std::ifstream &vectorFile, unsigned int &length);
	/// \endcond

	/**
		* \brief Export a Matrix in a file. The format is : some optional comments begining by '#', a optional header writing "row " and the number of rows, in the next line, "column " and the number of columns, and then, line by line, the matrix content.
		* \param M the Matrix to be exported
		* \param fileName the name of the target file
		* \param headerMode if true, write the number of row and colums before the data, else write directly the data
		* \param comments add some comments at the begining of the file, the caracter "#" is automatically added
		* \throw MathException error opening file
		* \author Vincent
		*/
	template <class T>
		void saveMatrix(const Matrix<T> &M,
										const std::string &fileName,
										const bool &headerMode =  false,
										const std::string &comments = "") {
			// open the file
			std::ofstream matrixFile(fileName.c_str());
			if(!matrixFile.is_open()){
					throw MathException("error opening file : " + fileName);
			}

			// write comments
			if(comments != "")
				matrixFile << "# " << comments << std::endl;

			// write header
			if(headerMode)
				matrixFile << "row " << M.rows() << std::endl
							<< "col " << M.columns() << std::endl;

			// additional line
			if(comments != "" || headerMode)
				matrixFile << std::endl;

			// write matrix content
			for (int i=0; i<M.rows(); ++i)
				{
					for (int j=0; j<M.columns(); ++j)
				matrixFile << M[i][j] << " ";

					matrixFile << std::endl;
				}

			// close file
			matrixFile.close();
		}

	/**
		* \brief Export a vector of Matrix in a file. The format is : some optional comments begining by '#', an optional header writing "mat " and the number of matrix, an optional header writing "row " and the number of rows, in the next line, "column " and the number of columns, and then, line by line, the matrix content.
		* \param M the vector of Matrix to be exported
		* \param fileName the name of the target file
		* \param headerMode if true, write the number of row and colums before the data, else write directly the data
		* \param comments add some comments at the begining of the file, the caracter "#" is automatically added
		* \throw MathException error opening file
		*/
	template <class T>
		void saveMatrixList(const std::vector< Matrix<T> > &M,
												const std::string &fileName,
												const bool &headerMode =  false,
												const std::string &comments = ""){
			// open the file
			std::ofstream matrixFile(fileName.c_str());
			if(!matrixFile.is_open()){
					throw MathException("error opening file : " + fileName);
			}

			// write comments and an empty line after
			if(comments != "")
				matrixFile << "# " << comments << std::endl;

			if(headerMode)
					matrixFile << "mat " << M.size() << std::endl;

			if(comments != "" || headerMode)
				matrixFile<< std::endl;

			for(unsigned int c=0;c<M.size();c++){
				// write header and an empty line after
				if(headerMode)
					matrixFile << "row " << M.at(c).rows() << std::endl << "col " << M.at(c).columns() << std::endl;

				// write matrix content
				for (int i=0; i<M.at(c).rows(); ++i){
					for (int j=0; j<M.at(c).columns(); ++j){
						matrixFile << M.at(c).at(i,j) << " ";
					}
					matrixFile << std::endl;
				}
				matrixFile << std::endl;
			}
			// close file
			matrixFile.close();
		}


	/**
		* \brief Export a Vector in a file. The format is : some optional comments begining by '#', an optional header writing "length " and the size of the vector before each vector, and then, the vector content.
		* \param V the vector of vector to be exported
		* \param fileName the name of the target file
		* \param headerMode if true, write the number of value before the data, else write directly the data
		* \param comments add some comments at the begining of the file, the caracter "#" is automatically added
		* \throw MathException error opening file
		*/
	template <class T>
		void saveVector(const Vector<T> &V,
										const std::string &fileName,
										const bool &headerMode =  false,
										const std::string &comments = ""){
			// open the file
			std::ofstream vectorFile(fileName.c_str());
			if(!vectorFile.is_open()){
				throw MathException("error opening file : " + fileName);
			}

			// write comments and an empty line after
			if(comments != "")
				vectorFile << "# " << comments << std::endl;
			//write header
			if(headerMode){
				vectorFile << "length " << V.size() << std::endl;
			}

			if(comments != "" || headerMode){
				vectorFile<< std::endl;
			}

			//write vector content
			for (int i=0; i<V.size(); ++i){
				vectorFile << V.at(i) << " ";
			}
			vectorFile << std::endl;

			// close file
			vectorFile.close();
		}



	/**
		* \brief Export a vector of Vector in a file. The format is : some optional comments begining by '#', an optional header writing "vector " and the number of vector, an optional header writing "length " and the size of the vector before each vector, and then, the vector content.
		* \param V the vector of vector to be exported
		* \param fileName the name of the target file
		* \param headerMode if true, write the number of value before the data, else write directly the data
		* \param comments add some comments at the begining of the file, the caracter "#" is automatically added
		* \throw MathException error opening file
		*/
	template <class T>
		void saveVectorList(const std::vector< Vector<T> > &V,
												const std::string &fileName,
												const bool &headerMode =  false,
												const std::string &comments = "") {
			// open the file
			std::ofstream vectorFile(fileName.c_str());
			if(!vectorFile.is_open()){
				throw MathException("error opening file : " + fileName);
			}

			// write comments and an empty line after
			if(comments != "")
				vectorFile << "# " << comments << std::endl;

			if(headerMode)
				vectorFile << "vector " << V.size() << std::endl;

			if(comments != "" || headerMode)
				vectorFile<< std::endl;

			if(headerMode){

				for(unsigned int c=0;c<V.size();c++){
					// write header and an empty line after
					vectorFile << "length " << V.at(c).size() << std::endl;

					// write vector content
					for (int i=0; i<V.at(c).size(); ++i){
			vectorFile << V.at(c).at(i) << " ";
					}
					vectorFile << std::endl;
				}
			}else{
				vectorFile << V;
			}
			// close file
			vectorFile.close();
		}


	/**
		* \brief Export a vector of Vector3 in a file. The format is : some optional comments begining by '#', an optional header writing "vector " and the number of vector, an optional header writing "length " and the size of the vector before each vector, and then, the vector content.
		* \param V the vector of vector to be exported
		* \param fileName the name of the target file
		* \param headerMode if true, write the number of value before the data, else write directly the data
		* \param comments add some comments at the begining of the file, the caracter "#" is automatically added
		* \throw MathException error opening file
		*/
	template <class T>
		void saveVectorList(const std::vector< Vector<T,StaticStorePolicy<T,3> > > &V,
												const std::string &fileName,
												const bool &headerMode =  false,
												const std::string &comments = ""){
			// open the file
			std::ofstream vectorFile(fileName.c_str());
			if(!vectorFile.is_open()){
				throw MathException("error opening file : " + fileName);
			}

			// write comments and an empty line after
			if(comments != "")
				vectorFile << "# " << comments << std::endl;

			if(headerMode)
				vectorFile << "vector " << V.size() << std::endl;

			if(comments != "" || headerMode)
				vectorFile<< std::endl;

			if(headerMode){

				for(unsigned int c=0;c<V.size();c++){
					// write header and an empty line after
					vectorFile << "length " << V.at(c).size() << std::endl;

					// write vector content
					for (int i=0; i<V.at(c).size(); ++i){
						vectorFile << V.at(c).at(i) << " ";
					}
					vectorFile << std::endl;
				}
			}
			else {
				vectorFile << V;
			}
			// close file
			vectorFile.close();
		}

	/**
		* \brief Load a Matrix from a file. The format is : some optional comments begining by '#', a optional header writing "row " and the number of rows, in the next line, "column " and the number of columns, and then, line by line, the matrix content.
		* \param M the Matrix to be loaded
		* \param fileName the name of the file to open
		* \throw MathException matrix size is incorrect / error opening file / invalid format
		* \author Vincent
		*/
	template <class T>
		void loadMatrix(Matrix<T> &M, const std::string &fileName){
			// open the file
			std::ifstream matrixFile(fileName.c_str());
			if(!matrixFile.is_open()){
				throw MathException("error opening file : " + fileName);
			}

			// read header
			unsigned int row    = 0;
			unsigned int column = 0;
			bool header = readMatrixHeader(matrixFile,row,column);

			// read the data
			if(header) readMatrixFromHeader(M,matrixFile,row,column);
			else readMatrix(M,matrixFile);

			// close
			matrixFile.close();
		}

	/**
		* \brief Load a vector Matrix from a file. The format is : some optional comments begining by '#', an optional header writing "mat " and the number of matrix, an optional header writing "row " and the number of rows, in the next line, "column " and the number of columns, and then, line by line, the matrix content.
		* \param M the vector of Matrix to be loaded
		* \param fileName the name of the file to open
		* \throw MathException matrix size is incorrect / error opening file / invalid format
		*/
	template <class T>
		void loadMatrixList(std::vector< Matrix<T> > &M, const std::string &fileName){

			// open the file
			std::ifstream matrixFile(fileName.c_str());
			if(!matrixFile.is_open()){
				throw MathException("error opening file : " + fileName);
			}

			// read header
			unsigned int mat    = 0;
			bool header = readMatrixHeader(matrixFile,mat);

			// read the data
			if(header){
				M.resize(mat);
				unsigned int row    = 0;
				unsigned int column = 0;
				for(unsigned int c=0;c<mat;c++){
					if(!readMatrixHeader(matrixFile,row,column)){
						throw MathException("error : missing header for the matrix "+c);
					}
					readMatrixFromHeader(M.at(c),matrixFile,row,column);
				}
			}
			else{
				M.resize(0);
				while(!matrixFile.eof()){
					kn::Matrix<T> tmpM;
					readMatrix(tmpM,matrixFile);
					if(tmpM.rows()!=0 && tmpM.columns()!=0)
						M.push_back(tmpM);
				}
			}

			// close
			matrixFile.close();
		}



	/**
		* \brief Load a Vector from a file. The format is : some optional comments begining by '#', an optional header writing "length " and the size of the vector before each vector, and then, the vector content.
		* \param V the Vector to be loaded
		* \param fileName the name of the file to open
		* \throw MathException matrix size is incorrect / error opening file / invalid format
		*/
	template <class T>
		void loadVector(Vector<T> &V, const std::string &fileName){

			// open the file
			std::ifstream vectorFile(fileName.c_str());
			if(!vectorFile.is_open()){
				throw MathException("error opening file : " + fileName);
			}

			// read header
			unsigned int len = 0;
			bool header = readVectorSubHeader(vectorFile,len);

			// read the data
			if(header){readVectorFromHeader(V,vectorFile,len);}
			else{readVector(V,vectorFile);}

			// close
			vectorFile.close();
		}

	/**
		* \brief Load a vector of Vector from a file. The format is : some optional comments begining by '#', an optional header writing "vector " and the number of vector, an optional header writing "length " and the size of the vector before each vector, and then, the vector content.
		* \param V the vector of Vector to be loaded
		* \param fileName the name of the file to open
		* \throw MathException matrix size is incorrect / error opening file / invalid format
		*/
	template <class T>
		void loadVectorList(std::vector< Vector<T> > &V, const std::string &fileName){

			// open the file
			std::ifstream vectorFile(fileName.c_str());
			if(!vectorFile.is_open()){
				throw MathException("error opening file : " + fileName);
			}

			// read header
			unsigned int vec = 0;
			bool header = readVectorHeader(vectorFile,vec);

			// read the data
			if(header){
				V.resize(0);
				for(unsigned int c=0;c<vec;c++){
					unsigned int len=0;
					if(!readVectorSubHeader(vectorFile,len)){
						throw MathException("error : missing sub header for the vector "+c);
					}
					kn::Vector<T,DynamicStorePolicy<T> > tmpV(len);
					readVectorFromHeader(tmpV,vectorFile,len);
					V.push_back(tmpV);
				}
			}
			else{
				V.resize(0);
				while(!vectorFile.eof()){
					kn::Vector<T,DynamicStorePolicy<T> > tmpV;
					readVector(tmpV,vectorFile);
					if(tmpV.size()!=0)
						V.push_back(tmpV);
				}
			}
			// close
			vectorFile.close();
		}


	/**
		* \brief Load a vector of Vector from a file. The format is : some optional comments begining by '#', an optional header writing "vector " and the number of vector, an optional header writing "length " and the size of the vector before each vector, and then, the vector content.
		* \param V the vector of Vector to be loaded
		* \param fileName the name of the file to open
		* \throw MathException matrix size is incorrect / error opening file / invalid format
		*/
	template <class T>
		void loadVectorList(std::vector< Vector<T,StaticStorePolicy<T,3> > > &V, const std::string &fileName){

			// open the file
			std::ifstream vectorFile(fileName.c_str());
			if(!vectorFile.is_open()){
				throw MathException("error opening file : " + fileName);
			}

			// read header
			unsigned int vec = 0;
			bool header = readVectorHeader(vectorFile,vec);

			// read the data
			V.resize(0);
			if(header){
				for(unsigned int c=0;c<vec;c++){
					unsigned int len=0;
					if(!readVectorSubHeader(vectorFile,len)){
						throw MathException("error : missing sub header for the vector "+c);
					}
					if(len!=3){
						throw MathException("error : Vector size must be 3 "+c);
					}
					kn::Vector<T,StaticStorePolicy<T,3> > tmpV;
					readVector3(tmpV,vectorFile);
					V.push_back(tmpV);
				}
			}
			else{
				while(true){
					kn::Vector<T,StaticStorePolicy<T,3> > tmpV;
					readVector3(tmpV,vectorFile);
					if(vectorFile.eof())break;
					V.push_back(tmpV);
				}
			}
			// close
			vectorFile.close();
		}



	/**
		* \cond
		* \brief read the content of a Matrix from the header information (row,col); the user should not use this function.
		* \param M the Matrix to be filled
		* \param matrixFile the input matrix ifstream
		* \param row the expected matrix row number
		* \param column the expected matrix column number
		* \throw MathException incompatible matrix size
		* \author Vincent
		*/
	template <class T>
		void readMatrixFromHeader(Matrix<T> &M,
															std::ifstream &matrixFile,
															const unsigned int &row,
															const unsigned int &column) {
			// if the matrix is not build yet
			if(M.rows() == 0 && M.columns() == 0)
				M = Matrix<T>(row,column);

			// if the matrix is already build
			if(M.rows() != row || M.columns() != column)
				throw MathException("readMatrixFromHeader : incompatible matrix size");

			// read the matrix
			for(unsigned int i=0; i<row; ++i)
				for(unsigned int j=0; j<column; ++j)
					matrixFile >> M[i][j];
		}
	/// \endcond


	/**
		* \cond
		* \brief read the content of a Matrix without any size information (row,col); the user should not use this function.
		* \param M the Matrix to be filled
		* \param matrixFile the input matrix ifstream
		* \throw MathException incompatible matrix size / invalid matrix file
		* \author Vincent
		*/
	template <class T>
		void readMatrix(Matrix<T> &M, std::ifstream &matrixFile){

			unsigned int row = 0;
			int column = -1; 	// unknown while you didn't read a line

			std::vector<T> content;
			std::string stringContent;

			// first read the matrix in a std::vector to check the consistency of the data
			do{ // for every line
				std::getline(matrixFile,stringContent);
				std::istringstream readContent(stringContent, std::istringstream::in);
				unsigned int index = 0;
				while(!readContent.eof()){ // for every element of a line
					T value;
					readContent >> value;
					content.push_back(value);
					index++;
				}
				// remove the eof
				content.erase(content.end()-1);
				index--;

				if(column == -1 && index != 0){   // 1st line : find 'column'
					column = index;
					row++;
				}
				else{
					if(index != 0){ // check empty line or invalid column
						if(column != index) throw MathException("readMatrix : invalid matrix file");
						else  row++;
					}
					else{
						//Matrix reading complete (empty line found)
						break;
					}
				}
			}
			while(!matrixFile.eof());

			if(row==0 && column==-1)return;

			// if the matrix is not build yet
			if(M.rows() == 0 && M.columns() == 0)
				M = Matrix<T>(row,column);

			// if the matrix is already build
			if(M.rows() != row || M.columns() != column)
				throw MathException("incompatible matrix size");

			// copy the data
			std::copy(content.begin(), content.end(), M.begin());
		}
		/// \endcond


	/**
		* \cond
		* \brief read the content of a Vector; the user should not use this function.\n
		* From the header information (length)  \n
		* \param V the Vector to be filled
		* \param vectorFile the input vector ifstream
		* \param length the expected vector size
		* \throw MathException incompatible vector size
		*/
	template <class T>
		void readVectorFromHeader(Vector<T> &V,
															std::ifstream &vectorFile,
															const unsigned int &length){
			// if the vector is not build yet
			if(V.size() == 0)
				V = Vector<T,DynamicStorePolicy<T> >(length);

			// if the matrix is already build
			if(V.size() != length)
				throw MathException("readVectorFromHeader : incompatible vector size");

			// read the vector
			for(unsigned int i=0; i<length; ++i)
				vectorFile >> V[i];
		}
		/// \endcond

	/**
		* \cond
		* \brief read the content of a Vector; the user should not use this function.\n
		* Without information \n
		* \param V the Vector to be filled
		* \param vectorFile the input vector ifstream
		* \throw MathException incompatible vector size
		*/
	template <class T>
		void readVector(Vector<T> &V,std::ifstream &vectorFile) {

			std::vector<T> content;
			std::string stringContent;

			// read the vector in a std::vector to check the consistency of the data
			std::getline(vectorFile,stringContent);
			std::istringstream readContent(stringContent, std::istringstream::in);
			unsigned int length = -1;
			while(!readContent.eof()){ // for every element of the line
				T value;
				readContent >> value;
				content.push_back(value);
				length++;
			}

			// remove the eof
			content.erase(content.end()-1);

			if(length==0)return;

			// if the vector is not build yet
			if(V.size() == 0)
				V = Vector<T,DynamicStorePolicy<T> >(length);

			// if the matrix is already build
			if(V.size() != length)
				throw MathException("readVector : incompatible vector size");

			// copy the data
			std::copy(content.begin(), content.end(),(T*)V.begin());
		}
		/// \endcond

	/**
		* \cond
		* \brief read the content of a Vector3; the user should not use this function.\n
		* \param V the Vector to be filled
		* \param vectorFile the input vector ifstream
		* \throw MathException incompatible vector size
		*/
	template <class T>
		void readVector3(Vector<T,StaticStorePolicy<T,3> > &V,std::ifstream &vectorFile) {
			// read the vector
			for(unsigned int i=0; i<3; ++i)
				vectorFile >> V[i];
		}
		/// \endcond

	/*
	 * End of Namespace
	 */
}


/*
 * End of Anti-doublon
 */
#endif



