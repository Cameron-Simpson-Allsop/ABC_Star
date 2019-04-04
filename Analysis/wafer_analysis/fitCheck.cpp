#include <iostream>
#include <fstream>
#include <cmath>


double disc(std::vector<double> x, std::vector<double> y, double tol)
{
  double y1,y2,y3,y4,y5,disc_x;
  for(int n{0}; n<x.size()-4; ++n)
    {
      y1 = y[n];
      y2 = y[n+1];
      y3 = y[n+2];
      y4 = y[n+3];
      y5 = y[n+4];
      if(y5<y4<y3<y2<y1 && abs(y5-y4) > tol && abs(y4-y3) > tol && abs(y3-y2) > tol && abs(y2-y1) > tol)
	{
	  disc_x = x[n];
	  n=x.size()-4;
	}
    }
  return disc_x;  
}

double altdisc(std::vector<double> x, std::vector<double> y, double tol)
{
  double y1,y2,y3,y4,y5,disc_x;
  for(int n{0}; n<x.size()-4; ++n)
    {
      y1 = y[n];
      y2 = y[n+1];
      y3 = y[n+2];
      y4 = y[n+3];
      y5 = y[n+4];
      if(abs(y5-y4) < tol && abs(y4-y3) < tol && abs(y3-y2) < tol && abs(y2-y1) < tol)
  	{
  	  disc_x = x[n];
  	  n=x.size()-4;
  	}
    }
  return disc_x;
}

void fitCheck()
{
  std::string ExtInt{""};
  std::string pol{""};
  std::string pad{""};
  double tol{0.};
  TString gtitle{""};
  std::cout<<"Enter file type (EXT/INT)...";
  bool check = false;
  std::vector<TString> graphNameEXT = {"Graph","Graph","gTRDAC","gVRef","gIRef","gR8B","gVCD","gCALLINE","gTHDAC","gVTHTEST","gCOM","gDRIVE","gVB","gVTHREF"};
  std::vector<TString> graphNameINT = {"Graph","Graph","gTRDAC","gVRef","gVCD","gCALLINE","gTHDAC","gVTHTEST","gCOM","Graph","Graph","Graph","gIRef","gR8B","gVB","Graph","Graph","Graph"};
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
  if(ExtInt == "EXT")
    {
      while(check == false)
	{
	  std::cin>>pad;
	  if(pad == "1" || pad == "2" || pad == "3" || pad == "4" || pad == "5" || pad == "6" || pad == "8" || pad == "9" || pad == "11" || pad == "12")
	    {
	      int padnumber = std::stoi(pad);
	      gtitle = graphNameEXT[padnumber-1];	    
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
      std::cout<<"Enter polynomial order (1-6 or disc)...";
      while(check == false)
	{
	  std::cin>>pol;
	  if(pol == "1" || pol == "2" || pol == "3" || pol == "4" || pol == "5" || pol == "6")
	    {
	      check = true;
	    }
	  else if(pol == "disc")
	    {
	      std::cout<<"Enter tolerance for discrepancy calulation (double)...";
	      cin>>tol;
	      check = true;
	    }
	  else std::cout<<"Invalid input, please try again...";
	}
    }
  check = false;
  if(ExtInt == "INT")
    {
      while(check == false)
	{
	  std::cin>>pad;
	  if(pad == "1" || pad == "2" || pad == "3" || pad == "6" || pad == "7" || pad == "9" || pad == "11" || pad == "12")
	    {
	      int padnumber = std::stoi(pad);
	      gtitle = graphNameINT[padnumber-1];	    
	      check = true;
	    }	  
	  else if(pad == "4")
	    {
	      std::string input;
	      std::cout<<"Select graph (VRef,IRef,R8B)...";
	      std::cin>>input;
	      if(input == "VRef" || input == "IRef" || input == "R8B")
		{
		  gtitle = "g"+input;
		  check = true;
		}
	      else std::cout<<"Invalid input, please reselect subpad..."; 
	    }
	  else if(pad == "5")
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
	  else if(pad == "8")
	    {
	      std::string input;
	      std::cout<<"Select graph (VTHTEST,VTHREF)...";
	      std::cin>>input;
	      if(input == "VTHTEST" || input == "VTHREF")
		{
		  gtitle = "g"+input;
		  check = true;
		}
	      else std::cout<<"Invalid input, please reselect subpad..."; 
	    }
	  else std::cout<<"Invalid input, please try again...";
	}
      check = false;
      std::cout<<"Enter polynomial order (1-6, disc or altdisc)...";
      while(check == false)
	{
	  std::cin>>pol;
	  if(pol == "1" || pol == "2" || pol == "3" || pol == "4" || pol == "5" || pol == "6")
	    {
	      check = true;
	    }
	  else if(pol == "disc")
	    {
	      std::cout<<"Enter tolerance for discrepancy calulation (double)...";
	      cin>>tol;
	      check = true;
	    }
	  else if(pol == "altdisc")
	    {
	      std::cout<<"Enter tolerance for discrepancy calulation (double)...";
	      cin>>tol;
	      check = true;
	    }
	  else std::cout<<"Invalid input, please try again...";
	}
    }
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
		  

		  TString cantitle = "c"+std::to_string(linecount);
		  TCanvas *canvas = new TCanvas(cantitle,cantitle,600,600);
		  TString Tline = line;
		  graph->SetTitle(Tline);
		  graph->SetMarkerStyle(20);
		  graph->SetMarkerSize(0.5);
		  graph->Draw("AP");
		  if(pol != "disc" && pol !="altdisc")
		    {
		      TString polorder = "pol"+pol;
		      TF1 *fit = new TF1("fit",polorder,0,500);
		      fit->SetLineColor(kBlue);		      
		      graph->Fit(fit,"QRN");
		      fit->Draw("same");
		    }
		  else if(pol == "disc")
		    {
		      double discrep = disc(x,y,tol);
		      if(discrep < 1000000000. && discrep > 0.000001)
			{
			  TF1 *fit1 = new TF1("fit1","pol1",0.,discrep);
			  fit1->SetParameter(1,0.);
			  TF1 *fit2 = new TF1("fit2","pol1",discrep,500.);
			  graph->Fit(fit1,"QRN");
			  graph->Fit(fit2,"QRN");
			  fit1->Draw("same");
			  fit2->Draw("same");
			}
		    }
		  else if(pol == "altdisc")
		    {
		      double discrep = altdisc(x,y,tol);
		      if(discrep < 1000000000. && discrep > 0.000001)
		      	{
 		      	  TF1 *fit3 = new TF1("fit1","pol1",0.,discrep);
		      	  TF1 *fit4 = new TF1("fit2","pol1",discrep,500.);
		      	  fit4->SetParameter(1,0.);
		      	  graph->Fit(fit3,"QRN");
		      	  graph->Fit(fit4,"QRN");
		      	  fit3->Draw("same");
		      	  fit4->Draw("same");
		      }
		    }
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
  std::cout<<"\nFile type: "<<ExtInt<<"\nSubpad: "<<pad<<"\nPolynomial order: "<<pol<<std::endl;
  if(pol=="disc" || pol == "altdisc"){std::cout<<"tolerance: "<<tol<<std::endl;}
  std::cout<<"Graph: "<<gtitle<<"\n"<<std::endl;
}
