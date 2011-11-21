#include <iostream>
#include <cstdlib>


#include <OpenKN/cuda/CudaManager.hpp>

#include "MatrixMulProgram.hpp"


int main(int argc, char** argv){
	MatrixMulProgram p;
	
	kn::CudaManager::getInstance().start();

	
	kn::CudaManager::getInstance().addTask(p);
	kn::CudaManager::getInstance().addTask(p);
	kn::CudaManager::getInstance().addTask(p);
	kn::CudaManager::getInstance().addTask(p);
	kn::CudaManager::getInstance().addTask(p);

	
	kn::CudaManager::getInstance().waitEnd();

	return EXIT_SUCCESS;
}
