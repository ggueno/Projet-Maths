#You need to define these environment variables
CUDA_DIR=/usr/local/cuda/
CUDA_SDK_DIR=/home/biri/Recherche/Project/Tools/Nvidia_cuda_SDK/

CUDA_DEBUG= #-D_DEBUG -> debug cuda
EMU=  -deviceemu #-deviceemu -> software emulation

all: matrixMul

matrixMul:  main.o MatrixMulProgram.o matrixMul.cu_o matrixMul_gold.cpp_o 
	g++ -fPIC -o matrixMul main.o MatrixMulProgram.o matrixMul_gold.cpp_o  matrixMul.cu_o -L${CUDA_DIR}/lib  -lcudart -lGL -lGLU -lglut -L ${CUDA_SDK_DIR}lib/  -lcutil -lIMAC-cuda -lboost_thread

main.o : main.cpp
	g++ -c  main.cpp -o main.o  -I../../../libIMAC-cuda/src -I.

MatrixMulProgram.o: MatrixMulProgram.cpp MatrixMulProgram.hpp 
	g++  -c MatrixMulProgram.cpp -o MatrixMulProgram.o -I../../../libIMAC-cuda/src -I.

matrixMul.cu_o: matrixMul.cu matrixMul.h matrixMul_kernel.cu
	nvcc  -o matrixMul.cu_o -c matrixMul.cu  --compiler-options -fno-strict-aliasing  ${EMU} ${CUDA_DEBUG} -I.  -I${CUDA_DIR}/include -I${CUDA_SDK_DIR}common/inc/  -DUNIX -O3 

matrixMul_gold.cpp_o: matrixMul_gold.cpp
	g++ -W -Wall  -fno-strict-aliasing -D__DEVICE_EMULATION__   -I. -I${CUDA_DIR}/include -DUNIX -O3  -o matrixMul_gold.cpp_o -c matrixMul_gold.cpp

clean :
	rm -f *_o *.o *~ matrixMul
