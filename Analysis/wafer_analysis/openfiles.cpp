#include <fstream>

void openfiles()
{
  ifstream fileList;
  std::string option;
  std::string fileName;
  std::string line{""};
  std::string Directory{""};
  std::cout<<"Accepted/Rejected files?(0/1)...";
  bool loop = false;
  while(loop == false)
    {
      std::cin>>option;
      if(option == "0")
	{
	  fileName = "Accepted_EXT_Files.txt";
	  Directory = "Accepted/";
	  std::cout<<fileName<<std::endl;
	  loop = true;
	}
      else if(option == "1")
	{
	  fileName = "Rejected_EXT_Files.txt";
	  Directory = "Rejected/";
	  std::cout<<fileName<<std::endl;
	  loop = true;
	}
      else std::cout<<"Invalid input, please try again..."<<std::endl;
    }  
  fileList.open(fileName);
  if(fileList.good())
    {
      while(true)
	{
	  getline(fileList,line);
	  line.erase(line.size()-5,5);
	  TString filePrefix = "../../wafer/";
	  TString fileSuffix = ".root";
	  TString filePath = filePrefix+line+fileSuffix;
	  if(fileList.eof()){break;}
	  TFile *file = TFile::Open(filePath);
	  TCanvas *ADCScanCanvas = (TCanvas *)file->Get("ADCScanCanvas");
	  TString savePath = "Canvases/"+Directory+line+".pdf";
	  ADCScanCanvas->SaveAs(savePath);
	  file->Close();
	}
    }
  fileList.close();
}
