#include "../include/list.hpp"
#include <fstream>



void loadList(char * filename, kn::Vector<double> & list){
  std::ifstream ifile(filename);
  // If file doesn't exist
  if(!ifile)
  {
	  std::cout<<"Erreur\n\tLe fichier "<< filename <<" n'existe pas ou pose problème."<<std::endl;
	  std::cout<<"Fermeture du programme."<<std::endl;
	  exit(1);
  }
  
  
  std::string line ;
  double x,y,z ;
  size_t cpt = 0;
  
  while (getline(ifile,line))
  {
   cpt++; 
  }
  
  list = new kn::Vector<double>(cpt*3);
  //std::cout << "List size" << list.size()<< std::endl;
  
  ifile.clear();
  ifile.seekg(0);
  
  while(getline(ifile,line)){
    //for each element
    //getline(ifile,line);
    
    ifile >> x;
    ifile >> y;
    ifile >> z;
    
    //std::cout << list.size()<< "(x,y,z)="  <<"("<< x <<","<< y <<","<< z <<")"<<std::endl;
    list[cpt] = x;
    ++cpt;
    list[cpt] = y;
  }
  
  ifile.close();
}
