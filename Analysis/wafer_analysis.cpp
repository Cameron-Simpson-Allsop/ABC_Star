#include <iostream>
#include <fstream>
#include <string>
#include "ProcessRootFile.cpp"

void wafer_analysis()
{
  TString filePrefix = "../wafer/";
  TString fileSuffix = ".root";  
  TString fileName = "VJCVPXH_009_MUX_EXT_data_20190107_000627";
  TString filePath = filePrefix+fileName+fileSuffix;
  TString padName = "pad_plot_3";
  TString graphName = "gTRDAC";

  TFile *inFile = new TFile(filePath);
  if(inFile->IsZombie()){}
  else if(!inFile->IsZombie())
    {
      ProcessRootFile(fileName,padName,graphName);
    }
}
//std::vector<TString> graphName = {"Graph","Graph","gTRDAC","gVRef","gIRef","gR8B","gVCD","gCALLINE","gTHDAC","gVTHTEST","gCOM","gDRIVE"}; //gVB(same pad as gVCD) gVTHREF(same pad as gVTHTEST)
