#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ProcessRootFile.hpp"
#include "Functions.hpp"

struct Data_vs_TID_EXT
{
  std::vector<double> VDDA_vs_LDOA_disc_x;
  std::vector<double> VDDA_vs_LDOA_disc_y;
  std::vector<double> VDDD_vs_LDOD_disc_x;
  std::vector<double> VDDD_vs_LDOD_disc_y;
  std::vector<double> timeStamp;
  std::vector<double> MRad;  
  std::vector<double> marker_xcoord;
  std::vector<double> marker_ycoord;
};

TGraph *Plot(std::vector<double> x, std::vector<double> y, TString xtitle, TString ytitle, TString title)
{
  TGraph *g = new TGraph(x.size(),&(x[0]),&(y[0]));g->GetXaxis()->SetTitle(xtitle);g->GetYaxis()->SetTitle(ytitle);g->SetTitle(title);g->SetMarkerStyle(20);return g;
}

TCanvas *Draw_EXT_subpad1(TString cantitle, TGraph *g1, TString cg1, TGraph *g2,TString cg2, TGraph2D *g3, TString cg3, TGraph *g4, TString cg4, TGraph *g5, TString cg5, TGraph2D *g6, TString cg6)
{
  TCanvas *c = new TCanvas(cantitle,cantitle,600,600);
  c->Divide(3,2);c->cd(1);g1->Draw(cg1);c->cd(2);g2->Draw(cg2);c->cd(3);g3->Draw(cg3);c->cd(4);g4->Draw(cg4);c->cd(5);g5->Draw(cg5);c->cd(6);g6->Draw(cg6);c->SaveAs("../Plots/wafer/"+cantitle+".root");return c;
}

TGraph2D *Plot2D(std::vector<double> xvec, std::vector<double> yvec, std::vector<double> zvec, TString xtitle, TString ytitle, TString ztitle, TString title)
{
  TGraph2D *g = new TGraph2D();g->SetTitle(title+";"+xtitle+";"+ytitle+";"+ztitle);Double_t x,y,z;for(int i{0}; i<xvec.size(); ++i){x=xvec[i];y=yvec[i];z=zvec[i];g->SetPoint(i,x,y,z);}return g;
}

void wafer_analysis()
{
  TString filePrefix = "../../wafer/";
  TString fileSuffix = ".root";  
  TString padPrefix = "pad_plot_";
  Data_vs_TID_EXT datavTID_EXT_8;
  Data_vs_TID_EXT datavTID_EXT_9;
  
  //Find list of files
  fstream fileList;
  fileList.open("../../wafer/FileList.txt");
  if(!fileList.good()){std::cout<<"Error fetching files..."<<std::endl;}
  std::string line{""};  
  int filecount{0};
  int processedfilecount{0};

  //For each file...
  while(!fileList.eof())
    {
      getline(fileList,line);
      std::size_t EXT = line.find("EXT");
      std::size_t INT = line.find("INT");
      if(EXT != std::string::npos && INT == std::string::npos)
	{
	  //Cut filename to practical size
	  line.erase(line.size()-5,5);
	  TString fileName = line;
	  
	  TString filePath = filePrefix+fileName+fileSuffix;  
	  TString padName;

	  //Define graph names for each pad
	  std::vector<TString> graphName = {"Graph","Graph","gTRDAC","gVRef","gIRef","gR8B","gVCD","gCALLINE","gTHDAC","gVTHTEST","gCOM","gDRIVE","gVB","gVTHREF"}; //gVB(same pad as gVCD) gVTHREF(same pad as gVTHTEST)

	  TFile *inFile = new TFile(filePath);
	  if(inFile->IsZombie()){}
	  else if(!inFile->IsZombie())
	    {
	      ++filecount;
	      std::cout<<"================================================================================================"<<std::endl;
	      std::cout<<fileName+fileSuffix<<std::endl;
	      //Extract data from file
	      for(int i{0}; i<2; ++i)
		{	 
		  Data data;
		  TID_Data TID;
		  padName = padPrefix + std::to_string(i+1);
		  if(i<graphName.size()-2)
		    {
		      data = ProcessRootFile(fileName,padName,graphName[i],i);
		    }
		  else if(i == graphName.size()-2)
		    {
		      padName = "pad_plot_7";
		      data = ProcessRootFile(fileName,padName,graphName[i],i);
		    }
		  else if(i == graphName.size()-1)
		    {
		      padName = "pad_plot_10";
		      data = ProcessRootFile(fileName,padName,graphName[i],i);
		    }
		  // TCanvas *canvas = new TCanvas(graphName[i]+" "+padName, graphName[i]+" "+padName,600,600);
		  // TGraph *g = new TGraph(data.x.size(),&(data.x[0]),&(data.y[0]));
		  // g->SetTitle("");
		  // g->SetMarkerStyle(20);
		  // g->Draw("AP");

		  //Manipulate data for each pad
		  std::size_t chip008 = line.find("008");
		  std::size_t chip009 = line.find("009");
		  switch(i)
		    {
		    case 0:
		      TID = Functions(graphName[i],padName,fileName,data,i);
		      //limits to ignore any uninitialised variables (Some files have no TID data)
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.VDDA_vs_LDOA_disc_x.push_back(TID.VDDA_vs_LDOA_disc_x);
			  datavTID_EXT_8.VDDA_vs_LDOA_disc_y.push_back(TID.VDDA_vs_LDOA_disc_y);
			  datavTID_EXT_8.timeStamp.push_back(TID.timeStamp);
			  datavTID_EXT_8.MRad.push_back(TID.MRad);
			  datavTID_EXT_8.marker_xcoord.push_back(TID.marker_xcoord);
			  datavTID_EXT_8.marker_ycoord.push_back(TID.marker_ycoord);
			  //std::cout<<"Chip 008"<<std::endl;
			  ++processedfilecount;
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.VDDA_vs_LDOA_disc_x.push_back(TID.VDDA_vs_LDOA_disc_x);
			  datavTID_EXT_9.VDDA_vs_LDOA_disc_y.push_back(TID.VDDA_vs_LDOA_disc_y);
			  datavTID_EXT_9.timeStamp.push_back(TID.timeStamp);
			  datavTID_EXT_9.MRad.push_back(TID.MRad);
			  datavTID_EXT_9.marker_xcoord.push_back(TID.marker_xcoord);
			  datavTID_EXT_9.marker_ycoord.push_back(TID.marker_ycoord);
			  //std::cout<<"Chip 009"<<std::endl;
			  ++processedfilecount;
			}
		      else
			{
			  std::cout<<"Error processing file '"+line+"'..."<<std::endl;
			}
		      break;

		    case 1:
		      //TID = Functions()
		      break;
		    }
		}
	      std::cout<<"================================================================================================"<<std::endl;	      
	    }
	}
      else if(INT != std::string::npos && EXT == std::string::npos)
	{
	  //++filecount;
	}
    }

  // TGraph *time_vs_TID_EXT = new TGraph(datavTID_EXT.timeStamp.size(), &(datavTID_EXT.timeStamp[0]), &(datavTID_EXT.MRad[0]));
  // time_vs_TID_EXT->GetXaxis()->SetTitle("Time stamp");
  // time_vs_TID_EXT->GetYaxis()->SetTitle("TID [MRad]");
  // time_vs_TID_EXT->SetTitle("");
  // time_vs_TID_EXT->SetMarkerStyle(20);
  // TCanvas *time_vs_TID_canvas = new TCanvas("Time_vs_TID_EXT","Time_vs_TID_EXT",600,600);
  // time_vs_TID_EXT->Draw("AP");

  //EXT subpad 1 chip 008
  TGraph *VDDA_vs_LDOA_disc_x_8;
  TGraph *VDDA_vs_LDOA_disc_y_8;
  TGraph2D *VDDA_vs_LDOA_disc_8;
  TGraph *marker_x_8;
  TGraph *marker_y_8;
  TGraph2D *marker_8;  
  VDDA_vs_LDOA_disc_x_8 = Plot(datavTID_EXT_8.VDDA_vs_LDOA_disc_x, datavTID_EXT_8.MRad, "VDDA vs LDOA Discontinuity [LDOA Setting]","TID [MRAD]", "VDDA vs LDOA Discontinuity [LDOA setting]");
  VDDA_vs_LDOA_disc_y_8 = Plot(datavTID_EXT_8.VDDA_vs_LDOA_disc_y, datavTID_EXT_8.MRad, "VDDA vs LDOA Discontinuity [Measured Voltage [V]]","TID [MRAD]", "VDDA vs LDOA Discontinuity [Measured Voltage [V]]");
  VDDA_vs_LDOA_disc_8 = Plot2D(datavTID_EXT_8.VDDA_vs_LDOA_disc_x, datavTID_EXT_8.VDDA_vs_LDOA_disc_y, datavTID_EXT_8.MRad, "VDDA vs LDOA Discontinuity [LDOA Setting]","VDDA vs LDOA Discontinuity [Measured Voltage [V]]","TID [MRad]", "VDDA vs LDOA Discontinuity");
  marker_x_8 = Plot(datavTID_EXT_8.marker_xcoord,datavTID_EXT_8.MRad,"LDOA Setting","TID [MRad]", "Marker LDOA Setting");
  marker_y_8 = Plot(datavTID_EXT_8.marker_ycoord,datavTID_EXT_8.MRad,"Measured Voltage [V]","TID [MRad]", "Marker Measured Voltage [V]");
  marker_8 = Plot2D(datavTID_EXT_8.marker_xcoord,datavTID_EXT_8.marker_ycoord,datavTID_EXT_8.MRad,"LDOA Setting","Measured Voltage [V]","TID [MRad]", "Marker Position");
  TCanvas *EXT_subpad_1_chip_008 = Draw_EXT_subpad1("EXT_subpad_1_chip_008",VDDA_vs_LDOA_disc_x_8,"AP",VDDA_vs_LDOA_disc_y_8,"AP",VDDA_vs_LDOA_disc_8,"colz",marker_x_8,"AP",marker_y_8,"AP",marker_8,"colz");
  
  
  //EXTsubpad 1 chip 009
  TGraph *VDDA_vs_LDOA_disc_x_9;
  TGraph *VDDA_vs_LDOA_disc_y_9;
  TGraph2D *VDDA_vs_LDOA_disc_9;
  TGraph *marker_x_9;
  TGraph *marker_y_9;
  TGraph2D *marker_9;  
  VDDA_vs_LDOA_disc_x_9 = Plot(datavTID_EXT_9.VDDA_vs_LDOA_disc_x, datavTID_EXT_9.MRad, "VDDA vs LDOA Discontinuity [LDOA Setting]","TID [MRAD]", "VDDA vs LDOA Discontinuity [LDOA setting]");
  VDDA_vs_LDOA_disc_y_9 = Plot(datavTID_EXT_9.VDDA_vs_LDOA_disc_y, datavTID_EXT_9.MRad, "VDDA vs LDOA Discontinuity [Measured Voltage [V]]","TID [MRAD]", "VDDA vs LDOA Discontinuity [Measured Voltage [V]]");
  VDDA_vs_LDOA_disc_9 = Plot2D(datavTID_EXT_9.VDDA_vs_LDOA_disc_x, datavTID_EXT_9.VDDA_vs_LDOA_disc_y, datavTID_EXT_9.MRad, "VDDA vs LDOA Discontinuity [LDOA Setting]","VDDA vs LDOA Discontinuity [Measured Voltage [V]]","TID [MRad]", "VDDA vs LDOA Discontinuity");
  marker_x_9 = Plot(datavTID_EXT_9.marker_xcoord,datavTID_EXT_9.MRad,"LDOA Setting","TID [MRad]", "Marker LDOA Setting");
  marker_y_9 = Plot(datavTID_EXT_9.marker_ycoord,datavTID_EXT_9.MRad,"Measured Voltage [V]","TID [MRad]", "Marker Measured Voltage [V]");
  marker_9 = Plot2D(datavTID_EXT_9.marker_xcoord,datavTID_EXT_9.marker_ycoord,datavTID_EXT_9.MRad,"LDOA Setting","Measured Voltage [V]","TID [MRad]", "Marker Position");
  TCanvas *EXT_subpad_1_chip_009 = Draw_EXT_subpad1("EXT_subpad_1_chip_009",VDDA_vs_LDOA_disc_x_9,"AP",VDDA_vs_LDOA_disc_y_9,"AP",VDDA_vs_LDOA_disc_9,"colz",marker_x_9,"AP",marker_y_9,"AP",marker_9,"colz");
  
  std::cout<<"================================================================================================\n"<<std::endl;	      
  std::cout<<"Total number of files read = "<<filecount<<std::endl;
  std::cout<<"Total number of files processed = "<<processedfilecount<<std::endl;
  std::cout<<"Total number of files rejected  = "<<filecount-processedfilecount<<std::endl;
  std::cout<<"\n";
}
