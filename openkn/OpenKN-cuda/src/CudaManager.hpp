/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Cudamanager.hpp created in 11 2008.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the libIMAC-cuda.
 *
 * The libIMAC-cuda is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The libIMAC-cuda is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_CUDA__CUDAMANAGER_HPP__
#define __OPENKN_CUDA__CUDAMANAGER_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <vector>
#include <boost/thread.hpp>
#include <utility>
#include <map>

/*
 * Internal Includes
 */
#include "CudaProgram.hpp"


/*
 * Namespace
 */
namespace kn{

	/*
	 * Class definition
	 */

	/** \brief Manager for Cuda programs
	 *  this class is a Singleton
	 */
	class CudaManager {

		/*
		 * Constructor & destructors
		 */		 
	private:
		CudaManager() {stoppedFlag = true;}
		CudaManager(const CudaManager &) {stoppedFlag = true;}
	public:
		~CudaManager() {stop();}

		/*
		 * Singleton
		 */
	private :
		/* \brief Instance of singleton
		 */
		static CudaManager * instance;
	public :
		/* \brief getter/initializer for the instance of singleton
		   \return the instance of the singleton
		*/
		static CudaManager & getInstance() {if (instance==NULL) instance = new CudaManager; return *instance;}

		/*
		 * Cuda programs
		 */
	private:
		/* \brief container for CudaProgram
		 */
		std::vector<std::pair<CudaProgram *,unsigned int> > programs;
		static unsigned int taskIDCount;
	public:
		/* \brief Adding a task to the pool
		   \param program The CudaProgram to add
		*/
		unsigned int  addTask(CudaProgram & program);

		/*
		 * Process handling
		 */
	public :
		void run();
		void reset();
		void stop();
		void start();
		unsigned int waitEnd();
		bool inline isStopped() { return stoppedFlag;}

	private :
		boost::thread * thread;
		boost::mutex programsMutex;
		bool stoppedFlag;
		void stopThread();
		void startThread();
	};
			
	/* 
	 * Static members initializations
	 */
	CudaManager * CudaManager::instance = NULL;
		
	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
