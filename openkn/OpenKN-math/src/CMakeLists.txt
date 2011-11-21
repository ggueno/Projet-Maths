#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# CMakeLists.txt created in 09 2008.
# Mail : biri@univ-mlv.fr
#
# This file is part of the OpenKraken-math.
#
# The OpenKraken-math is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-math is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-math src/


#Includes
include_directories (${OpenKN-math_SOURCE_DIR}/src ${OpenKN-math_BINARY_DIR}/src)


#Cpp Files
SET(CPP_FILES MathException.cpp Vector.cpp Matrix.cpp Matrix4x4.cpp Matrix3x3.cpp SVD.cpp Solver.cpp InverseMatrix.cpp Determinant.cpp RQDecomposition.cpp CholeskyDecomposition.cpp MathIO.cpp Rank.cpp GaussianElimination.cpp Quaternion.cpp EulerAngles.cpp)
add_library (OpenKN-math SHARED ${CPP_FILES})
add_library (OpenKN-math-static STATIC ${CPP_FILES})

#Header Files
SET(HPP_FILES MathException.hpp Vector.hpp Vector2.hpp Vector3.hpp Vector4.hpp VectorStaticStoragePolicy.hpp VectorDynamicStoragePolicy.hpp Matrix.hpp Matrix3x3.hpp Matrix4x4.hpp MathTools.hpp SVD.hpp Solver.hpp InverseMatrix.hpp Determinant.hpp RQDecomposition.hpp CholeskyDecomposition.hpp MathIO.hpp Rank.hpp GaussianElimination.hpp Quaternion.hpp EulerAngles.hpp)

#Install
install (TARGETS OpenKN-math DESTINATION lib)
install (TARGETS OpenKN-math-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/math)


#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-math-static PROPERTIES OUTPUT_NAME "OpenKN-math")
SET_TARGET_PROPERTIES(OpenKN-math PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-math-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
