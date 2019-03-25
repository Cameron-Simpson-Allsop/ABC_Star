#include <iostream>
#include <fstream>

void fitCheck()
{
  ifstream inFile;
  std::string line{""};
  inFile.open("../../wafer/FileList.txt")
    if(!inFile.good())
      {
	std::cout<<"Error opening file..."<<std::endl;
      }
    else if(inFile.good())
      {
	while(!inFile.eof())
	  {
	    
	  }
      }
}
