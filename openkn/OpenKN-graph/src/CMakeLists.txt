#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# CMakeLists.txt created in 6 2009.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-graph.
#
# The OpenKraken-graph is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-graph is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-graph src/


#Includes
include_directories (${OpenKN-graph_SOURCE_DIR}/src ${OpenKN-graph_BINARY_DIR}/src)


#Cpp Files
SET(CPP_FILES GraphException.cpp GraphStruct.cpp DenseGraphStruct.cpp SparseGraphStruct.cpp BiSparseGraphStruct.cpp MutableGraphStruct.cpp Graph.cpp DirectedGraph.cpp UndirectedGraph.cpp MutableGraph.cpp MutableDirectedGraph.cpp MutableUndirectedGraph.cpp RootedTree.cpp RootingInfo.cpp HARootedTreeInfos.cpp HAUnrootedTreeInfos.cpp HAClassicOperators.cpp Subset.cpp HomeomorphicAlignment.cpp)
add_library (OpenKN-graph SHARED ${CPP_FILES})
add_library (OpenKN-graph-static STATIC ${CPP_FILES})

#Header Files
SET(HPP_FILES GraphException.hpp GraphStruct.hpp DenseGraphStruct.hpp SparseGraphStruct.hpp BiSparseGraphStruct.hpp MutableGraphStruct.hpp Graph.hpp DirectedGraph.hpp UndirectedGraph.hpp MutableGraph.hpp MutableDirectedGraph.hpp MutableUndirectedGraph.hpp RootedTree.hpp RootingInfo.hpp HATreeInfos.hpp HARootedTreeInfos.hpp HAUnrootedTreeInfos.hpp HAOperators.hpp HAClassicOperators.hpp Subset.hpp HomeomorphicAlignment.hpp EdgeConstraint.hpp)

#Install
install (TARGETS OpenKN-graph DESTINATION lib)
install (TARGETS OpenKN-graph-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/graph)


#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-graph-static PROPERTIES OUTPUT_NAME "OpenKN-graph")
SET_TARGET_PROPERTIES(OpenKN-graph PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-graph-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
