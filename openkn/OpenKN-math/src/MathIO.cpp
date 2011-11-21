/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * MathIO.cpp created in 04 2009.
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
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Internal Includes
 */
#include "MathIO.hpp"


/*
 * External Includes
 */
#include <cstdlib>

/*
 * Namespace
 */
namespace kn {

      /// \cond
      //matrix
      template void loadMatrix(Matrix<double>&, const std::string &);
      template void loadMatrix(Matrix<float>&, const std::string &);
      template void loadMatrix(Matrix<int>&, const std::string &);

      template void saveMatrix(const Matrix<double>&, const std::string &, const bool &, const std::string &);
      template void saveMatrix(const Matrix<float>&, const std::string &, const bool &, const std::string &);
      template void saveMatrix(const Matrix<int>&, const std::string &, const bool &, const std::string &);

      template void loadMatrixList(std::vector< Matrix<double> >&, const std::string &);
      template void loadMatrixList(std::vector< Matrix<float> >&, const std::string &);
      template void loadMatrixList(std::vector< Matrix<int> >&, const std::string &);

      template void saveMatrixList(const std::vector< Matrix<double> >&, const std::string &, const bool &, const std::string &);
      template void saveMatrixList(const std::vector< Matrix<float> >&, const std::string &, const bool &, const std::string &);
      template void saveMatrixList(const std::vector< Matrix<int> >&, const std::string &, const bool &, const std::string &);

      //vector
      template void loadVector(Vector<double>&, const std::string &);
      template void loadVector(Vector<float>&, const std::string &);
      template void loadVector(Vector<int>&, const std::string &);

      template void saveVector(const Vector<double>&, const std::string &, const bool &, const std::string &);
      template void saveVector(const Vector<float>&, const std::string &, const bool &, const std::string &);
      template void saveVector(const Vector<int>&, const std::string &, const bool &, const std::string &);

      template void loadVectorList(std::vector< Vector<double> >&, const std::string &);
      template void loadVectorList(std::vector< Vector<float> >&, const std::string &);
      template void loadVectorList(std::vector< Vector<int> >&, const std::string &);

      template void saveVectorList(const std::vector< Vector<double> >&, const std::string &, const bool &, const std::string &);
      template void saveVectorList(const std::vector< Vector<float> >&, const std::string &, const bool &, const std::string &);
      template void saveVectorList(const std::vector< Vector<int> >&, const std::string &, const bool &, const std::string &);

      template void loadVectorList(std::vector< Vector<double,StaticStorePolicy<double,3> > >&, const std::string &);
      template void loadVectorList(std::vector< Vector<float,StaticStorePolicy<float,3> > >&, const std::string &);
      template void loadVectorList(std::vector< Vector<int,StaticStorePolicy<int,3> > >&, const std::string &);

      template void saveVectorList(const std::vector< Vector<double,StaticStorePolicy<double,3> > >&, const std::string &, const bool &, const std::string &);
      template void saveVectorList(const std::vector< Vector<float,StaticStorePolicy<float,3> > >&, const std::string &, const bool &, const std::string &);
      template void saveVectorList(const std::vector< Vector<int,StaticStorePolicy<int,3> > >&, const std::string &, const bool &, const std::string &);


      /// \endcond

     /*
      * \brief read successive empty lines (ie. a line that contains only spaces and tabs) from a std::ifstream.
      * \param matrixFile the input matrix ifstream
      * \return true if an empty line has been read
      */
      bool skipEmptyLines(std::ifstream &dataFile){

	  std::streampos currentPos;
	  std::string data;
	  bool stillEmpty;
	  bool emptyLineRead = false; // true if an empty line has been read

	  do{ // read a line
	    currentPos = dataFile.tellg();
	    std::getline(dataFile,data);

	    // read space or tabs
	    stillEmpty = true;
	    unsigned int i = 0;
	    while(i<data.size()){
	      if(data[i]!=' ' && data[i]!='\t'){
		stillEmpty = false;
		i = data.size();
	      }
	      ++i;
	    }

	  if(stillEmpty) emptyLineRead = true; // at least a line has bee read
	  } while (stillEmpty);

	  // rewind to the begining of the last line read
	  dataFile.seekg(currentPos); // rewind

	  return emptyLineRead;
      }


     /*
      * \brief read successive comment lines (ie. a line that starts with a '#') from a std::ifstream.
      * \param matrixFile the input matrix ifstream
      * \return true if a comment has been read
      */
      bool skipComments(std::ifstream &dataFile){

	  std::streampos currentPos;
	  std::string comments;
	  bool stillComment;
	  bool commentsRead = false; // true if a comment has been read
	  do{
	    // read a comment
	    currentPos = dataFile.tellg();
	    std::getline(dataFile,comments);

	    // read space or tabs
	    unsigned int i = 0;
	    while( (comments[i]==' ' || comments[i]=='\t') &&  i<comments.size()) // man isblank
	      ++i;

	    // detect comment line
	    stillComment = false;
	    if(comments[i]=='#'){
	      stillComment = true;
	      commentsRead = true; // at least a comment has bee read
	    }
	  } while (stillComment);

	  // rewind to the first line after the comments
	  dataFile.seekg(currentPos); // rewind

	  return commentsRead;
      }


     /*
      * \brief read a keyword (ie 'row' or 'column') and the corresponding value (ie 'row 15')
      * \param dataFile : the input data ifstream
      * \param keyword : the keyword to read, before its corresponding value
      * \param value : the value to be read
      * \return true if the keyword and value have been successfully read, else false
      */
      bool readSize(std::ifstream &dataFile, const std::string &keyword, double &value){

	  // remember the curent position
	  std::streampos currentPos = dataFile.tellg();

	  // read a line
 	  std::string data;
	  std::getline(dataFile,data);

	  // read the keyword
	  if(data.compare(0,keyword.size(),keyword) != 0){
	    dataFile.seekg(currentPos);
	    return false;
	  }

	  // read the value
	  data = data.substr(keyword.size()+1,data.size()-(keyword.size()+1));
	  const char *nptr = data.c_str();
	  char *endptr = 0;
	  value = strtod(nptr,&endptr);
	  if(endptr == nptr || endptr == 0){
	    dataFile.seekg(currentPos);
	    return false;
	  }

	  // success
	  return true;
      }


     /*
      * \brief ignore the comments and read the header on a matrix file if specified; the user should not use this function.
      * \param matrixFile the input matrix ifstream
      * \return true if the matrix format is spefifyed, false otherwise
      * \throw MathException invalid format
      */
      bool readMatrixHeader(std::ifstream &matrixFile, unsigned int &row, unsigned int &column){

	  // read comments
	  while(skipComments(matrixFile) || skipEmptyLines(matrixFile));

	  // read row
	  double value = 0.0;
	  if(!readSize(matrixFile,"row",value))
	     return false;
	  row = (unsigned int) value;

	  // read comments
	  while(skipComments(matrixFile) || skipEmptyLines(matrixFile));

	  // read column
	  if(!readSize(matrixFile,"col",value))
	     throw MathException("readMatrixHeader : invalid format : 'col' expected");
	  column = (unsigned int) value;

	  // read comments
	  while(skipComments(matrixFile) || skipEmptyLines(matrixFile));

	  return true;
      }

      /**
      * \cond
      * \brief ignore the comments and read the header on a matrix file if specified; the user should not use this function.
      * \param matrixFile the input matrix ifstream
      * \param mat the number of matrix in the file
      * \return true if the matrix format is spefifyed, false otherwise
      * \throw MathException invalid format
      */
      bool readMatrixHeader(std::ifstream &matrixFile, unsigned int &mat){

	  // read comments
	  while(skipComments(matrixFile) || skipEmptyLines(matrixFile));

	  // read mat
	  double value = 0.0;
	  if(!readSize(matrixFile,"mat",value))
	     return false;
	  mat = (unsigned int) value;

	  // read comments
	  while(skipComments(matrixFile) || skipEmptyLines(matrixFile));

	  return true;
      }
      /// \endcond


      /**
      * \cond
      * \brief ignore the comments and read the header on a matrix file if specified; the user should not use this function.
      * \param vectorFile the input vector ifstream
      * \param vec the number of vector in the file
      * \return true if the vector format is spefifyed, false otherwise
      * \throw MathException invalid format
      */
      bool readVectorHeader(std::ifstream &vectorFile, unsigned int &vec){

	  // read comments
	  while(skipComments(vectorFile) || skipEmptyLines(vectorFile));

	  // read mat
	  double value = 0.0;
	  if(!readSize(vectorFile,"vector",value))
	     return false;
	  vec = (unsigned int) value;

	  // read comments
	  while(skipComments(vectorFile) || skipEmptyLines(vectorFile));

	  return true;
      }
      /// \endcond


      /**
      * \cond
      * \brief ignore the comments and read the header on a matrix file if specified; the user should not use this function.
      * \param vectorFile the input vector ifstream
      * \param vec the number of vector in the file
      * \return true if the vector format is spefifyed, false otherwise
      * \throw MathException invalid format
      */
      bool readVectorSubHeader(std::ifstream &vectorFile, unsigned int &length){

	  // read comments
	  while(skipComments(vectorFile) || skipEmptyLines(vectorFile));

	  // read mat
	  double value = 0.0;
	  if(!readSize(vectorFile,"length",value))
	     return false;
	  length = (unsigned int) value;

	  // read comments
	  while(skipComments(vectorFile) || skipEmptyLines(vectorFile));

	  return true;
      }
      /// \endcond


  /*
   * End of Namespace
   */
}

