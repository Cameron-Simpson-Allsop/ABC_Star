#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

struct Data
{
  std::vector<double> x;
  std::vector<double> y;
  TString padName;
  TString graphName;
  double timeStamp;
  double MRad;  
  double marker_xcoord;
  double marker_ycoord;
  double redfitp0;
  double redfitp1;

  bool init_check;
};

Data ProcessRootFile(TString fileName, TString padName, TString graphName, int i)
{
  Data data;
  //Define file path
  TString filePrefix = "../../wafer/";
  TString fileSuffix = ".root";
  TString filePath = filePrefix+fileName+fileSuffix;

  //Open file and draw
  TFile *file = TFile::Open(filePath);
  TCanvas *ADCScanCanvas = (TCanvas *)file->Get("ADCScanCanvas");
  if(ADCScanCanvas == NULL){std::cout<<"Canvas is null..."<<std::endl; return data;}
  //ADCScanCanvas->Draw();
  //if(i==0){ADCScanCanvas->ls();}
  
  //Extract TGraph values from pad 		      
  TPad *mypad = (TPad*)ADCScanCanvas->GetPrimitive("pad_plot");
  TPad *mysubpad = (TPad*)mypad->GetPrimitive(padName);
  //mysubpad1->ls();
  TGraphErrors *myTGraph = (TGraphErrors*)mysubpad->GetPrimitive(graphName);	      
  for(int i = 0; i < myTGraph->GetN();++i)
    {
      double x,y;
      myTGraph->GetPoint(i,x,y);
      data.x.push_back(x);
      data.y.push_back(y);
      //std::cout<<x<<"\t"<<y<<std::endl;
    }

  //Extract header from pad
  TPad *header = (TPad*)ADCScanCanvas->GetPrimitive("pad_header");
  TPaveText *headerpave = (TPaveText*)header->GetPrimitive("TPave");
  auto headertext = headerpave->GetLine(0);
  std::string padTitle = headertext->GetTitle();

  //Extract Marker from pad
  TMarker *marker = (TMarker*)mysubpad->GetPrimitive("TMarker");
  
  //std::cout<<padTitle;//<<std::endl;

  //Extract timestamp and TID from header
  std::size_t Time = padTitle.find("Time");
  std::size_t MRad = padTitle.find("MRad");

  if(Time != std::string::npos && MRad != std::string::npos && marker != NULL)
    {
      data.timeStamp = std::stod(padTitle.substr(Time+5,6));
      data.MRad = std::stod(padTitle.substr(MRad-7,6));
      data.marker_xcoord = marker->GetX();
      data.marker_ycoord = marker->GetY();

      data.init_check = true;
      if(padName == "pad_plot_1")
	{
	  //std::cout<<"time stamp = " << data.timeStamp<<"\t"<<data.MRad<<" MRad"<<std::endl;
	}
    }
  if((Time != std::string::npos && MRad == std::string::npos) || marker == NULL)
    {
      data.init_check = false;
    }

  //std::cout<<padName<<"\t"<<graphName;
  //Fit graph (if relevant)
  TH1F *fitcheck = (TH1F*)mysubpad->GetPrimitive("vhisto");
  if(fitcheck == NULL)
    {
      //std::cout<<": (No fit applied)";//<<std::endl;
    }
  else if(fitcheck != NULL)
    { 
      TF1 *fit = new TF1("fit","pol1",0,500);
      myTGraph->Fit(fit,"QRN");
      data.redfitp0 = fit->GetParameter(0);
      data.redfitp1 = fit->GetParameter(1);
    }
  
  if(padName == "pad_plot_3" && Time != std::string::npos && MRad != std::string::npos && data.redfitp1 > 0.001 && data.redfitp0 > 0.001)
    {
      data.init_check = true;
    }
  
  std::string failreason = "";
  if(MRad == std::string::npos){failreason = "No TID data";}
  if(marker == NULL){failreason = "Anomalous data";}
  if(MRad == std::string::npos && marker == NULL){failreason = "No TID data, and data is anomalous";}
  if(data.init_check == true)
    {
      //std::cout<<"\t\t | Pass"<<std::endl;
    }
  else if(data.init_check == false)
    {
      //std::cout<<"\t\t\t\t\t | Fail: "<<failreason<<std::endl;
    }
  
  data.padName = padName;
  data.graphName = graphName;
  ADCScanCanvas->Close();
  file->Close();	      
  return data;
}
