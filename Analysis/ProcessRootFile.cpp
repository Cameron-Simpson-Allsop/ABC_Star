#include <iostream>
#include <fstream>
#include <string>

void ProcessRootFile(TString fileName, TString padName, TString graphName)
{
  //Define file path
  TString filePrefix = "../wafer/";
  TString fileSuffix = ".root";
  TString filePath = filePrefix+fileName+fileSuffix;

  //Open file and draw
  TFile *file = TFile::Open(filePath);
  TCanvas *ADCScanCanvas = (TCanvas *)file->Get("ADCScanCanvas");
  if(ADCScanCanvas == NULL){std::cout<<"Canvas is null..."<<std::endl; return;}
  ADCScanCanvas->Draw();
  ADCScanCanvas->ls();

  //Extract TGraph values from pad
 		      
  TPad *mypad = (TPad*)ADCScanCanvas->GetPrimitive("pad_plot");
  TPad *mysubpad = (TPad*)mypad->GetPrimitive(padName);
  //mysubpad1->ls();
  TGraphErrors *myTGraph = (TGraphErrors*)mysubpad->GetPrimitive(graphName);
  std::cout<<"==============================="<<std::endl;
  std::cout<<padName<<"\t"<<graphName<<std::endl;
  std::cout<<"==============================="<<std::endl;
  for(int i = 0; i < myTGraph->GetN();++i)
    {
      double x,y;
      myTGraph->GetPoint(i,x,y);	
      std::cout<<x<<"\t"<<y<<std::endl;
    }
  // auto myGraphClone = (TGraphErrors*)myTGraph->Clone();
  // TCanvas *clone = new TCanvas("clone","clone",600,600);
  // myGraphClone->Draw();
  ADCScanCanvas->Close();
}
