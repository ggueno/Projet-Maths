#include <iostream>
#include <cstdlib>
#include <cmath>
#include <OpenKN/util/Profiler.hpp>

int main(int argc, char** argv){
	/* Creating the instance of Profiler
	   Report is saved when the instance is destroyed
	 */
	kn::Profiler p("report.txt");	
	kn::Profiler::start("main");

	kn::Profiler::start("pow");
	for (long i = 0; i <1000000; i++)  {
		double b = pow(i,3);
	}
	kn::Profiler::stop("pow");

	kn::Profiler::start("pow 2");
	for (long i = 0; i <2000000; i++)  {
		double a = pow(i,2);
	}
	kn::Profiler::stop("pow 2");
		
	sleep(1);
	
	kn::Profiler::stop("main");
	return EXIT_SUCCESS;
}
