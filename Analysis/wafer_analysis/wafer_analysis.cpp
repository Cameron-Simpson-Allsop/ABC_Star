#include <iostream>
#include <fstream>
#include <string>
#include "ProcessRootFile.hpp"
#include "Functions.hpp"
#include "PlotFunctions.hpp"
#include "EXT_analysis.hpp"
#include "INT_analysis.hpp"

void wafer_analysis()
{
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

  std::cout<<"EXT or INT? (0/1)...";
  std::string input;
  bool check = false;
  while(check == false)
    {
      std::cin>>input;
      if(input == "0")
	{
	  std::cout<<"Processing EXT files..."<<std::endl;
	  EXT_analysis(EXTfiles);
	  check = true;
	}
      else if(input == "1")
	{
	  std::cout<<"Processing INT files..."<<std::endl;
	  INT_analysis(INTfiles);
	  check = true;
	}
      else std::cout<<"Invalid input, please try again...";
    }
  std::cout<<"Total file count = "<<filetotal<<std::endl;
  std::cout<<"================================================================================================"<<std::endl;
  fileList.close();
}
