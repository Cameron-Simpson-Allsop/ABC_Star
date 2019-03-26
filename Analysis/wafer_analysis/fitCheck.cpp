#include <iostream>
#include <fstream>
#include <cmath>

void fitCheck()
{
  std::string ExtInt{""};
  std::string pol{""};
  std::string pad{""};
  TString gtitle{""};
  std::cout<<"Enter file type (EXT/INT)...";
  bool check = false;
  while(check == false)
    {
      std::cin>>ExtInt;
      if(ExtInt == "EXT" || ExtInt == "INT")
  	{
  	  check = true;
  	}
      else std::cout<<"Invalid input, please try again...";
    }
  check = false;
  std::cout<<"Enter subpad number (1-12)...";
  while(check == false)
    {
      std::cin>>pad;
      std::vector<TString> graphNames = {"Graph","Graph","gTRDAC","gVRef","gIRef","gR8B","gVCD","gCALLINE","gTHDAC","gVTHTEST","gCOM","gDRIVE","gVB","gVTHREF"};   
      if(pad == "1" || pad == "2" || pad == "3" || pad == "4" || pad == "5" || pad == "6" || pad == "8" || pad == "9" || pad == "11" || pad == "12")
  	{
	  int padnumber = std::stoi(pad);
	  gtitle = graphNames[padnumber-1];	    
	  check = true;
  	}
      else if(pad == "7")
	{
	  std::string input;
	  std::cout<<"Select graph (VCD,VB)...";
	  std::cin>>input;
	  if(input == "VCD" || input == "VB")
	    {
	      gtitle = "g"+input;
	      check = true;
	    }
	  else std::cout<<"Invalid input, please reselect subpad..."; 
	}
      else if(pad == "10")
	{
	  std::string input;
	  std::cout<<"Select graph (VTHTEST,VTHREF)...";
	  std::cin>>input;
	  if(input == "VTHTEST" || input == "VTHREF")
	    {
	      gtitle = "g"+input;
	      check = true;
	    }
	  else std::cout<<"Invalid input, please try again...";	      
	}

      else std::cout<<"Invalid input, please try again...";
    }
  check = false;
  std::cout<<"Enter polynomial order (1-6)...";
  while(check == false)
    {
      std::cin>>pol;
      if(pol == "1" || pol == "2" || pol == "3" || pol == "4" || pol == "5" || pol == "6")
  	{
  	  check = true;
  	}
      else std::cout<<"Invalid input, please try again...";
    }
  check = false;
  //std::cout<<gtitle<<std::endl;
  ifstream inFile;
  std::string line{""};
  int linecount{0};
  int processedfilecount{0};
  int filecount{0};
  inFile.open("../../wafer/FileList.txt");
  if(!inFile.good())
    {
      std::cout<<"Error opening file..."<<std::endl;
    }
  else if(inFile.good())
    {
      while(!inFile.eof())
	{
	  getline(inFile,line);
	  TString fileName = "../../wafer/"+line;
	  std::size_t filecheck1 = line.find(".root");
	  std::size_t filecheck2 = line.find(ExtInt);
	  if(filecheck1 != std::string::npos && filecheck2 != std::string::npos)
	    {	      
	      TFile *rfile = TFile::Open(fileName);
	      TCanvas *ADCScanCanvas = (TCanvas *)rfile->Get("ADCScanCanvas");
	      if(ADCScanCanvas == NULL){std::cout<<line<<"\tCanvas is null..."<<std::endl;}
	      TPad *mypad = (TPad*)ADCScanCanvas->GetPrimitive("pad_plot");
	      TString subpadname = "pad_plot_"+pad;
	      TPad *mysubpad = (TPad*)mypad->GetPrimitive(subpadname);
	      TGraphErrors *myTGraph = (TGraphErrors*)mysubpad->GetPrimitive(gtitle);
	      if(myTGraph == NULL){std::cout<<line<<"\tTGraphErrors is null..."<<std::endl;}

	      if(linecount/20 == (linecount*1.)/20. && myTGraph != NULL)
		{
		  std::vector<double> x,y;
		  for(int i{0}; i<myTGraph->GetN(); ++i)
		    {
		      double xpoint,ypoint,expoint,eypoint;
		      myTGraph->GetPoint(i,xpoint,ypoint);
		      x.push_back(xpoint);
		      y.push_back(ypoint);
		    }
		  TGraph *graph = new TGraph(x.size(),&(x[0]),&(y[0]));
		  TString polorder = "pol"+pol;
		  TF1 *fit = new TF1("fit",polorder,0,500);
		  fit->SetLineColor(kBlue);
		  TString cantitle = "c"+std::to_string(linecount);
		  TCanvas *canvas = new TCanvas(cantitle,cantitle,600,600);
		  TString Tline = line;
		  graph->SetTitle(Tline);
		  graph->SetMarkerStyle(20);
		  graph->SetMarkerSize(0.5);
		  graph->Fit(fit,"QRN");
		  graph->Draw("AP");		 
		  fit->Draw("same");		  
		  ++processedfilecount;
		}
	      rfile->Close();
	      ++filecount;
	    }
	  ++linecount;
	}
      inFile.close();
    }
  std::cout<<"\nlinecount = "<<linecount<<"\nfilecount = "<<filecount<<"\nprocessed filecount = "<<processedfilecount<<std::endl;
  std::cout<<"\nFile type: "<<ExtInt<<"\nSubpad: "<<pad<<"\nPolynomial order: "<<pol<<"\nGraph: "<<gtitle<<"\n"<<std::endl;
}
