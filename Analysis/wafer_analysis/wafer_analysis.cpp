#include <iostream>
#include <fstream>
#include <string>
#include "EXT_analysis.cpp"

void wafer_analysis()
{
  //TString fileSuffix = ".root";  
  //TString padPrefix = "pad_plot_";  
  //Find list of files
  int filetotal{0};
  ifstream fileList;
  fileList.open("../../wafer/FileList.txt");
  if(!fileList.good())
    {
      std::cout<<"Error fetching files..."<<std::endl;
    }
  std::string line{""};

  std::vector<TString> EXTfiles;
  std::vector<TString> INTfiles;
  TString EXTname;
  TString INTname;
  
  while(true)
    {
      getline(fileList,line);
      if(fileList.eof()){break;}
      std::size_t EXT = line.find("EXT");
      std::size_t INT = line.find("INT");
      if(EXT != std::string::npos && INT == std::string::npos)
	{
	  EXTname = line;
	  EXTfiles.push_back(EXTname);
	}
      else if(EXT == std::string::npos && INT != std::string::npos)
	{
	  INTname = line;
	  INTfiles.push_back(INTname);
	}
      else std::cout<<"Error categorising file '"+line+"'..."<<std::endl;
      ++filetotal;
    }
  EXT_analysis(EXTfiles);
  //std::cout<<"================================================================================================"<<std::endl;
  std::cout<<"Total file count = "<<filetotal<<std::endl;
  std::cout<<"================================================================================================"<<std::endl;
  fileList.close();
}
