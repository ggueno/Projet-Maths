/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Cudamanager.cpp created in 11 2008.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * External includes
 */
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <time.h>

/*
 * Internal Includes
 */
#include "CudaManager.hpp"



/*
 * Namespace
 */
namespace kn{
	  
	/*
	 * static variables
	 */	  
	unsigned int CudaManager::taskIDCount = 0;

	/*
	 * Functions definitions
	 */

	void CudaManager::stop() {
		stopThread();
	}

	void CudaManager::start() {
		startThread();
	}

	void CudaManager::reset () {
		stop();
		start();
	}

	void CudaManager::run(){
		struct timespec delay;
		delay.tv_sec = 0;
		delay.tv_nsec = 1000000;
		while(!stoppedFlag) {
			while(programs.size()) {
				CudaProgram * currentTask = programs.back().first;
				currentTask->init();
				currentTask->run();
				currentTask->release();
				boost::mutex::scoped_lock lk(programsMutex);
				programs.pop_back();
			}
			nanosleep(&delay,NULL);
		}
	}

	void CudaManager::startThread() { 
		if (isStopped()) {
			this->stoppedFlag = false;
			thread = new boost::thread(boost::bind(&CudaManager::run, this));
		}
	}

	unsigned int CudaManager::waitEnd() {
		thread->join(); 
		return EXIT_SUCCESS;
	}
	  
	void CudaManager::stopThread() {
		if (!isStopped()) {
			stoppedFlag = true; 
			thread->join();
			delete thread;
		}
	}

	unsigned int  CudaManager::addTask(CudaProgram & program) {
		boost::mutex::scoped_lock lk(programsMutex);
		taskIDCount++;
		programs.push_back(std::pair<CudaProgram *,unsigned int>(&program,taskIDCount));
		return taskIDCount;
	}

	/*
	 * End of Namespace
	 */
}
