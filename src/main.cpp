#include <iostream>
#include <string.h>
#include <OpenKN/math/Vector.hpp>

#include <OpenKN/image/Image.hpp>
#include <OpenKN/image/ImageRGB.hpp>
#include <OpenKN/image/ioJPG.hpp>


using namespace std;

int main(int argc, char * argv[]){
  
  // Prints each argument on the command line.
  int i = 0;
  string filename;
  
  kn::ImageRGB<unsigned char> image1;
  kn::ImageRGB<unsigned char> image2;
  
  kn::Vector<double> list1;
  kn::Vector<double> list2;
  
  if(argc>1){
    while( i < argc )
    {
      //cout<<"Argument : "<<argv[i]<<endl;
      // option -l : a list to read
      if(strcmp(argv[i],"-l")==0){
	i++;
	cout<<"List Loading : "<<argv[i]<<endl;
	//verify if the file exist
	
	//(optional) if file doesn't exist start pointListProgram
	cout<<"List Loading : "<<argv[i]<<endl;
	filename=argv[i];
	//loadList(filename,list1);
	++i;
	
	cout<<"List Loading : "<<argv[i]<<endl;
	filename=argv[i];
	//loadList(filename,list2);
	
      }
      
      //option -i : an image to read
      else if(strcmp(argv[i],"-i")==0){
	//load the image
	++i;
	cout<<"Images Loading : "<<argv[i]<<endl;
	
	
	//first image
	filename=argv[i];
	// (optional) find the extension
	kn::loadJPG(image1,filename);
	
	//second image 
	++i;
	cout<<"Images Loading : "<<argv[i]<<endl;
	filename=argv[i];
	kn::loadJPG(image2,filename);
	
	cout<<"Images Loading. Done !"<<endl;
	
      }else{
	 //error :  unknow argument
      }
      
      i++;
      
    }
  }
  
  return 0;
}
