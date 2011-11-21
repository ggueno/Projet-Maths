/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Profiler.hpp created in 03 2009.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-util.
 *
 * The OpenKraken-util is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-util is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_UTIL__PROFILER_HPP__
#define __OPENKN_UTIL__PROFILER_HPP__

/*
 * External Includes
 */
#include <stdexcept>
#include <sys/time.h>
#include <map>
#include <sstream>
#include <fstream>
#include <cstdarg>
#include <ctime>

/*
 * Internal Includes
 */

/*
 * Predeclarations
 */

/*
 * Namespace
 */
namespace kn{

    /** Class for profiling performances
     * 
     */
    class Profiler {	

	public:
	
		Profiler(const std::string & fileName="") : _fileName(fileName) {};
		~Profiler() { save();}

		/** Subclass for profiling data
		 * 
		 */
		class Profile {
	    public :
	    
			Profile(){callCount = 0; minTime = 1e10; maxTime = 0.0; avTime = 0.0; minTick = 1e10; maxTick = 0.0; avTick = 0.0;}
			~Profile(){}

			unsigned int callCount;
			double avTime;
			double maxTime;
			double minTime;
	    private :
			struct timeval newtime;
			struct timeval firsttime;
			clock_t firsttick;
			clock_t newtick;
			double minTick;
			double avTick;
			double maxTick;

	    
	    public :
	    
			void start(){ callCount++; gettimeofday(&firsttime,NULL); firsttick = std::clock();}
	    
			void stop() {
				gettimeofday(&newtime,NULL);					
				newtick = std::clock();
				struct timeval difftime;
				timersub(&newtime,&firsttime,&difftime);
				clock_t difftick = newtick - firsttick;
				double tick = (double) difftick;// / (double) CLOCKS_PER_SEC;
				double time = difftime.tv_sec + ((double) difftime.tv_usec / 1000000L);
				if(time < minTime) minTime = time;
				if(time > maxTime) maxTime = time;
				avTime += (double) time;
				if(tick < minTick) minTick = tick;
				if(tick > maxTick) maxTick = tick;
				avTick += (double) tick;
			}
	    
	    public :
	    
			std::string save() { 
				avTime /= (double) callCount;
				std::stringstream s; s << "Callcount : " << callCount << std::endl; 
				s << "Average call time : " << avTime << std::endl; 
				s << "Min call time : " << minTime << std::endl; 
				s << "Max call time : " << maxTime << std::endl; 
				s << "Average call tick : " << avTick << std::endl; 
				s << "Min call tick : " << minTick << std::endl; 
				s << "Max call tick : " << maxTick << std::endl; 
				return s.str();
			}
		};

	private :	
		Profiler(const Profiler & );
		static std::map<std::string, Profiler::Profile> profiles;
		typedef std::map<std::string, Profiler::Profile>::iterator PMapIterator;
		
	public :
	
		static void start(const std::string profile){profiles[profile].start();}
		static void stop(const std::string profile){profiles[profile].stop();} 

	private : 
	
		std::string _fileName;

	public :    
		void save() { 
			if (_fileName !="")	{ 
				std::fstream f(_fileName.c_str(),std::ios::out); 
				for(PMapIterator it = profiles.begin(); it != profiles.end(); it++) {
					f << "**********************************" << std::endl;
					f << "" << it->first << " " << std::endl;			
					f << "----------------------------------" << std::endl;
					f << it->second.save();
					f << "**********************************" << std::endl;
					f << std::endl;
				}
				f.close();
			}
		}
	
	public :
		inline const std::string & fileName() const {return _fileName;}
		inline std::string & fileName() {return _fileName;}
		inline const Profiler::Profile &  profile(const std::string & profileName) {return profiles[profileName];}

	};

	template<typename T>
	std::string toString( const T & Value ) {
	    std::ostringstream oss;
	    oss << Value;
	    return oss.str();
	}

	/*
	 * Definition of static variable
	 */
	std::map<std::string, Profiler::Profile> Profiler::profiles;


	/*
	 * End of Namespace
	 */
}

/*
 * End Anti-doublon
 */
#endif

