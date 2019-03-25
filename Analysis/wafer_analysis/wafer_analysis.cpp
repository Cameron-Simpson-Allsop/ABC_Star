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
  std::vector<double> marker_xcoord_VDDD;
  std::vector<double> marker_ycoord_VDDD;  
  std::vector<double> marker_xcoord_VDDA;
  std::vector<double> marker_ycoord_VDDA;  
  std::vector<double> marker_xcoord_VRef;
  std::vector<double> marker_ycoord_VRef; 
  std::vector<double> marker_xcoord_IRef;
  std::vector<double> marker_ycoord_IRef; 
  std::vector<double> marker_xcoord_R8B;
  std::vector<double> marker_ycoord_R8B;
  std::vector<double> marker_xcoord_COM;
  std::vector<double> marker_ycoord_COM;
  std::vector<double> TRDACfitp0;
  std::vector<double> TRDACfitp1;
  std::vector<double> VReffitp0;
  std::vector<double> VReffitp1;
  std::vector<double> IReffitp0;
  std::vector<double> IReffitp1;
  std::vector<double> R8Bfitp0;
  std::vector<double> R8Bfitp1;
  std::vector<double> VCDfitp0;
  std::vector<double> VCDfitp1;
  std::vector<double> CALLINEfitp0;
  std::vector<double> CALLINEfitp1;
  std::vector<double> THDACfitp0;
  std::vector<double> THDACfitp1;
  std::vector<double> VTHTESTfitp0;
  std::vector<double> VTHTESTfitp1;
  std::vector<double> VTHTESTfitp2;
  std::vector<double> VTHTESTfitp3;
  std::vector<double> COMfitp0;
  std::vector<double> COMfitp1;
  std::vector<double> DRIVEfitp0;
  std::vector<double> DRIVEfitp1;
};

TGraph *Plot(std::vector<double> x, std::vector<double> y, TString xtitle, TString ytitle, TString title)
{
  TGraph *g = new TGraph(x.size(),&(x[0]),&(y[0]));g->GetXaxis()->SetTitle(xtitle);g->GetYaxis()->SetTitle(ytitle);g->SetTitle(title);g->SetMarkerStyle(20);g->SetMarkerSize(0.5);return g;
}

TCanvas *Draw_EXT_subpad_6pads(TString cantitle, TGraph *g1, TString cg1, TGraph *g2,TString cg2, TGraph2D *g3, TString cg3, TGraph *g4, TString cg4, TGraph *g5, TString cg5, TGraph2D *g6, TString cg6)
{
  TGaxis::SetMaxDigits(2);
  TCanvas *c = new TCanvas(cantitle,cantitle,600,600);
  c->Divide(3,2);c->cd(1);g1->Draw(cg1);c->cd(2);g2->Draw(cg2);c->cd(3);g3->Draw(cg3);c->cd(4);g4->Draw(cg4);c->cd(5);g5->Draw(cg5);c->cd(6);g6->Draw(cg6);c->SaveAs("../Plots/wafer/"+cantitle+".root");c->SaveAs("../Plots/wafer/"+cantitle+".pdf");return c;
}
TCanvas *Draw_EXT_subpad_3pads(TString cantitle, TGraph *g1, TString cg1, TGraph *g2, TString cg2, TGraph2D *g3, TString cg3)
{
  TGaxis::SetMaxDigits(2);
  TCanvas *c = new TCanvas(cantitle,cantitle,600,600);
  c->Divide(3,1);c->cd(1);g1->Draw(cg1);c->cd(2);g2->Draw(cg2);c->cd(3);g3->Draw(cg3);c->SaveAs("../Plots/wafer/"+cantitle+".root");c->SaveAs("../Plots/wafer/"+cantitle+".pdf");return c;
}
TCanvas *Draw_EXT_subpad_4pads(TString cantitle, TGraph *g1, TString cg1, TGraph *g2, TString cg2, TGraph *g3, TString cg3, TGraph *g4, TString cg4)
{
  TGaxis::SetMaxDigits(2);
  TCanvas *c = new TCanvas(cantitle,cantitle,600,600);
  c->Divide(2,2);c->cd(1);g1->Draw(cg1);c->cd(2);g2->Draw(cg2);c->cd(3);g3->Draw(cg3);c->cd(4);g4->Draw(cg4);c->SaveAs("../Plots/wafer/"+cantitle+".root");c->SaveAs("../Plots/wafer/"+cantitle+".pdf");return c;
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
  if(!fileList.good())
    {
      std::cout<<"Error fetching files..."<<std::endl;
    }
  std::string line{""};  
  int filecount{0};
  int processedfilecount{0};
  int padcount{0};
  int processedpadcount{0};

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

	  //Define graph names for each pad
	  std::vector<TString> graphName = {"Graph","Graph","gTRDAC","gVRef","gIRef","gR8B","gVCD","gCALLINE","gTHDAC","gVTHTEST","gCOM","gDRIVE","gVB","gVTHREF"}; //gVB(same pad as gVCD) gVTHREF(same pad as gVTHTEST)

	  TFile *inFile = new TFile(filePath);
	  if(inFile->IsZombie()){}
	  else if(!inFile->IsZombie())
	    {
	      ++filecount;
	      //std::cout<<"================================================================================================"<<std::endl;
	      //std::cout<<fileName+fileSuffix<<std::endl;
	      //Extract data from file
	      for(int i{0}; i<graphName.size()-2; ++i)
		{
		  ++padcount;
		  Data data;
		  TID_Data TID;
		  TString padName;
		  if(i<graphName.size()-2) 
		    {
		      padName = padPrefix + std::to_string(i+1);
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
			  datavTID_EXT_8.VDDA_vs_LDOA_disc_x.push_back(TID.disc_x);
			  datavTID_EXT_8.VDDA_vs_LDOA_disc_y.push_back(TID.disc_y);
			  datavTID_EXT_8.timeStamp.push_back(TID.timeStamp);
			  datavTID_EXT_8.MRad.push_back(TID.MRad);
			  datavTID_EXT_8.marker_xcoord_VDDA.push_back(TID.marker_xcoord);
			  datavTID_EXT_8.marker_ycoord_VDDA.push_back(TID.marker_ycoord);
			  ++processedfilecount;
			  ++processedpadcount;
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.VDDA_vs_LDOA_disc_x.push_back(TID.disc_x);
			  datavTID_EXT_9.VDDA_vs_LDOA_disc_y.push_back(TID.disc_y);
			  datavTID_EXT_9.timeStamp.push_back(TID.timeStamp);
			  datavTID_EXT_9.MRad.push_back(TID.MRad);
			  datavTID_EXT_9.marker_xcoord_VDDA.push_back(TID.marker_xcoord);
			  datavTID_EXT_9.marker_ycoord_VDDA.push_back(TID.marker_ycoord);
			  ++processedfilecount;
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;

		    case 1:
		      TID = Functions(graphName[i],padName,fileName,data,i);
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.VDDD_vs_LDOD_disc_x.push_back(TID.disc_x);
			  datavTID_EXT_8.VDDD_vs_LDOD_disc_y.push_back(TID.disc_y);
			  datavTID_EXT_8.marker_xcoord_VDDD.push_back(TID.marker_xcoord);
			  datavTID_EXT_8.marker_ycoord_VDDD.push_back(TID.marker_ycoord);
			  //std::cout<<"Chip 008"<<std::endl;
			  ++processedpadcount;			  
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.VDDD_vs_LDOD_disc_x.push_back(TID.disc_x);
			  datavTID_EXT_9.VDDD_vs_LDOD_disc_y.push_back(TID.disc_y);
			  datavTID_EXT_9.marker_xcoord_VDDD.push_back(TID.marker_xcoord);
			  datavTID_EXT_9.marker_ycoord_VDDD.push_back(TID.marker_ycoord);
			  //std::cout<<"Chip 009"<<std::endl;
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;

		    case 2:
		      TID = Functions(graphName[i],padName,fileName,data,i);
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.TRDACfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_8.TRDACfitp1.push_back(TID.redfitp1);
			  ++processedpadcount;			  
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.TRDACfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_9.TRDACfitp1.push_back(TID.redfitp1);
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;

		    case 3:
		      TID = Functions(graphName[i],padName,fileName,data,i);
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.VReffitp0.push_back(TID.redfitp0);
			  datavTID_EXT_8.VReffitp1.push_back(TID.redfitp1);
			  datavTID_EXT_8.marker_xcoord_VRef.push_back(TID.marker_xcoord);
			  datavTID_EXT_8.marker_ycoord_VRef.push_back(TID.marker_ycoord);
			  ++processedpadcount;			  
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.VReffitp0.push_back(TID.redfitp0);
			  datavTID_EXT_9.VReffitp1.push_back(TID.redfitp1);
			  datavTID_EXT_9.marker_xcoord_VRef.push_back(TID.marker_xcoord);
			  datavTID_EXT_9.marker_ycoord_VRef.push_back(TID.marker_ycoord);
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;

		    case 4:
		      TID = Functions(graphName[i],padName,fileName,data,i);
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.IReffitp0.push_back(TID.redfitp0);
			  datavTID_EXT_8.IReffitp1.push_back(TID.redfitp1);
			  datavTID_EXT_8.marker_xcoord_IRef.push_back(TID.marker_xcoord);
			  datavTID_EXT_8.marker_ycoord_IRef.push_back(TID.marker_ycoord);
			  ++processedpadcount;			  
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.IReffitp0.push_back(TID.redfitp0);
			  datavTID_EXT_9.IReffitp1.push_back(TID.redfitp1);
			  datavTID_EXT_9.marker_xcoord_IRef.push_back(TID.marker_xcoord);
			  datavTID_EXT_9.marker_ycoord_IRef.push_back(TID.marker_ycoord);
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;

		    case 5:
		      TID = Functions(graphName[i],padName,fileName,data,i);
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.R8Bfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_8.R8Bfitp1.push_back(TID.redfitp1);
			  datavTID_EXT_8.marker_xcoord_R8B.push_back(TID.marker_xcoord);
			  datavTID_EXT_8.marker_ycoord_R8B.push_back(TID.marker_ycoord);
			  ++processedpadcount;			  
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.R8Bfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_9.R8Bfitp1.push_back(TID.redfitp1);
			  datavTID_EXT_9.marker_xcoord_R8B.push_back(TID.marker_xcoord);
			  datavTID_EXT_9.marker_ycoord_R8B.push_back(TID.marker_ycoord);
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;

		    case 6:
		      TID = Functions(graphName[i],padName,fileName,data,i);
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.VCDfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_8.VCDfitp1.push_back(TID.redfitp1);
			  ++processedpadcount;			  
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.VCDfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_9.VCDfitp1.push_back(TID.redfitp1);
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;

		    case 7:
		      TID = Functions(graphName[i],padName,fileName,data,i);
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.CALLINEfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_8.CALLINEfitp1.push_back(TID.redfitp1);
			  ++processedpadcount;
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.CALLINEfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_9.CALLINEfitp1.push_back(TID.redfitp1);
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;

		    case 8:
		      TID = Functions(graphName[i],padName,fileName,data,i);
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.THDACfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_8.THDACfitp1.push_back(TID.redfitp1);
			  ++processedpadcount;
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.THDACfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_9.THDACfitp1.push_back(TID.redfitp1);
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;

		    case 9:
		       TID = Functions(graphName[i],padName,fileName,data,i);
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.VTHTESTfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_8.VTHTESTfitp1.push_back(TID.redfitp1);
			  datavTID_EXT_8.VTHTESTfitp2.push_back(TID.redfitp2);
			  datavTID_EXT_8.VTHTESTfitp3.push_back(TID.redfitp3);
			  ++processedpadcount;
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{			  
			  datavTID_EXT_9.VTHTESTfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_9.VTHTESTfitp1.push_back(TID.redfitp1);
			  datavTID_EXT_9.VTHTESTfitp2.push_back(TID.redfitp2);
			  datavTID_EXT_9.VTHTESTfitp3.push_back(TID.redfitp3);
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;

		    case 10:
		      TID = Functions(graphName[i],padName,fileName,data,i);
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.COMfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_8.COMfitp1.push_back(TID.redfitp1);
			  datavTID_EXT_8.marker_xcoord_COM.push_back(TID.marker_xcoord);
			  datavTID_EXT_8.marker_ycoord_COM.push_back(TID.marker_ycoord);
			  ++processedpadcount;			  
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.COMfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_9.COMfitp1.push_back(TID.redfitp1);
			  datavTID_EXT_9.marker_xcoord_COM.push_back(TID.marker_xcoord);
			  datavTID_EXT_9.marker_ycoord_COM.push_back(TID.marker_ycoord);
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;

		    case 11:
		      TID = Functions(graphName[i],padName,fileName,data,i);
		      if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
			{
			  datavTID_EXT_8.DRIVEfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_8.DRIVEfitp1.push_back(TID.redfitp1);
			  ++processedpadcount;			  
			}
		      else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
			{
			  datavTID_EXT_9.DRIVEfitp0.push_back(TID.redfitp0);
			  datavTID_EXT_9.DRIVEfitp1.push_back(TID.redfitp1);
			  ++processedpadcount;
			}
		      else
			{
			  //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
			}
		      break;
		    }
		}
	      //std::cout<<"================================================================================================"<<std::endl;	      
	    }
	}
      else if(INT != std::string::npos && EXT == std::string::npos)
	{
	  //++filecount;
	}
    }

  std::cout<<"================================================================================================"<<std::endl;
  
  //EXT timestamp vs TID
  TGraph *timestamp_TID_8 = new TGraph(datavTID_EXT_8.timeStamp.size(),&(datavTID_EXT_8.timeStamp[0]),&(datavTID_EXT_8.MRad[0]));
  timestamp_TID_8->SetMarkerStyle(20);
  timestamp_TID_8->SetMarkerSize(0.5);
  timestamp_TID_8->SetMarkerColor(kRed);
  timestamp_TID_8->SetLineColor(kRed);
  TGraph *timestamp_TID_9 = new TGraph(datavTID_EXT_9.timeStamp.size(),&(datavTID_EXT_9.timeStamp[0]),&(datavTID_EXT_9.MRad[0]));
  timestamp_TID_9->SetMarkerStyle(20);
  timestamp_TID_9->SetMarkerSize(0.5);
  timestamp_TID_9->SetMarkerColor(kBlue);
  timestamp_TID_9->SetLineColor(kBlue);
  TMultiGraph *timestamp_TID = new TMultiGraph();
  timestamp_TID->GetXaxis()->SetTitle("Time Stamp");
  timestamp_TID->GetYaxis()->SetTitle("TID [MRad]");
  timestamp_TID->SetTitle("");
  timestamp_TID->Add(timestamp_TID_8,"p");
  timestamp_TID->Add(timestamp_TID_9,"p");
  TLegend *timestamp_TID_leg = new TLegend(0.3,0.3,0.45,0.45);
  timestamp_TID_leg->AddEntry(timestamp_TID_8,"chip 008","lp");
  timestamp_TID_leg->AddEntry(timestamp_TID_9,"chip 009","lp");
  TCanvas *timestamp_TID_can = new TCanvas("timestamp_TID","timestamp_TID",600,600);
  TGaxis::SetMaxDigits(2);
  timestamp_TID_leg->SetBorderSize(0);
  timestamp_TID_leg->SetFillColor(0);
  timestamp_TID_leg->SetTextSize(0.02);
  timestamp_TID_leg->SetFillStyle(1000);
  timestamp_TID_leg->SetTextFont(42);
  timestamp_TID_leg->SetNColumns(1);
  timestamp_TID->Draw("AP");
  //timestamp_TID_leg->Draw("same");
  //timestamp_TID_can->SaveAs("../Plots/wafer/EXT_timestamp_vs_TID.root");
  //timestamp_TID_can->SaveAs("../Plots/wafer/EXT_timestamp_vs_TID.pdf");
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  //EXT subpad 1 chip 008
  TGraph *VDDA_vs_LDOA_disc_x_8;
  TGraph *VDDA_vs_LDOA_disc_y_8;
  TGraph2D *VDDA_vs_LDOA_disc_8;
  TGraph *marker_x_8_VDDA;
  TGraph *marker_y_8_VDDA;
  TGraph2D *marker_8_VDDA;  
  VDDA_vs_LDOA_disc_x_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VDDA_vs_LDOA_disc_x,"TID [MRAD]","VDDA vs LDOA Discontinuity [LDOA Setting]","VDDA vs LDOA Discontinuity [LDOA setting]");
  VDDA_vs_LDOA_disc_y_8 = Plot( datavTID_EXT_8.MRad, datavTID_EXT_8.VDDA_vs_LDOA_disc_y,"TID [MRAD]","VDDA vs LDOA Discontinuity [Measured Voltage [V]]","VDDA vs LDOA Discontinuity [Measured Voltage [V]]");
  VDDA_vs_LDOA_disc_8 = Plot2D(datavTID_EXT_8.VDDA_vs_LDOA_disc_x, datavTID_EXT_8.VDDA_vs_LDOA_disc_y, datavTID_EXT_8.MRad, "VDDA vs LDOA Discontinuity [LDOA Setting]","VDDA vs LDOA Discontinuity [Measured Voltage [V]]","TID [MRad]", "VDDA vs LDOA Discontinuity");
  marker_x_8_VDDA = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_xcoord_VDDA,"TID [MRad]", "LDOA Setting","Marker LDOA Setting");
  marker_y_8_VDDA = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_ycoord_VDDA,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_8_VDDA = Plot2D(datavTID_EXT_8.marker_xcoord_VDDA,datavTID_EXT_8.marker_ycoord_VDDA,datavTID_EXT_8.MRad,"LDOA Setting","Measured Voltage [V]","TID [MRad]", "Marker Position");
  TCanvas *EXT_subpad_1_chip_008 = Draw_EXT_subpad_6pads("EXT_subpad_1_chip_008",VDDA_vs_LDOA_disc_x_8,"AP",VDDA_vs_LDOA_disc_y_8,"AP",VDDA_vs_LDOA_disc_8,"colz",marker_x_8_VDDA,"AP",marker_y_8_VDDA,"AP",marker_8_VDDA,"colz");  
  //EXT subpad 1 chip 009
  TGraph *VDDA_vs_LDOA_disc_x_9;
  TGraph *VDDA_vs_LDOA_disc_y_9;
  TGraph2D *VDDA_vs_LDOA_disc_9;
  TGraph *marker_x_9_VDDA;
  TGraph *marker_y_9_VDDA;
  TGraph2D *marker_9_VDDA;
  VDDA_vs_LDOA_disc_x_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VDDA_vs_LDOA_disc_x,"TID [MRAD]","VDDA vs LDOA Discontinuity [LDOA Setting]","VDDA vs LDOA Discontinuity [LDOA setting]");
  VDDA_vs_LDOA_disc_y_9 = Plot( datavTID_EXT_9.MRad, datavTID_EXT_9.VDDA_vs_LDOA_disc_y,"TID [MRAD]","VDDA vs LDOA Discontinuity [Measured Voltage [V]]","VDDA vs LDOA Discontinuity [Measured Voltage [V]]");
  VDDA_vs_LDOA_disc_9 = Plot2D(datavTID_EXT_9.VDDA_vs_LDOA_disc_x, datavTID_EXT_9.VDDA_vs_LDOA_disc_y, datavTID_EXT_9.MRad, "VDDA vs LDOA Discontinuity [LDOA Setting]","VDDA vs LDOA Discontinuity [Measured Voltage [V]]","TID [MRad]", "VDDA vs LDOA Discontinuity");
  marker_x_9_VDDA = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_xcoord_VDDA,"TID [MRad]", "LDOA Setting","Marker LDOA Setting");
  marker_y_9_VDDA = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_ycoord_VDDA,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_9_VDDA = Plot2D(datavTID_EXT_9.marker_xcoord_VDDA,datavTID_EXT_9.marker_ycoord_VDDA,datavTID_EXT_9.MRad,"LDOA Setting","Measured Voltage [V]","TID [MRad]", "Marker Position");
  TCanvas *EXT_subpad_1_chip_009 = Draw_EXT_subpad_6pads("EXT_subpad_1_chip_009",VDDA_vs_LDOA_disc_x_9,"AP",VDDA_vs_LDOA_disc_y_9,"AP",VDDA_vs_LDOA_disc_9,"colz",marker_x_9_VDDA,"AP",marker_y_9_VDDA,"AP",marker_9_VDDA,"colz");

  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  //EXT subpad 2 chip 008
  TGraph *VDDD_vs_LDOD_disc_x_8;
  TGraph *VDDD_vs_LDOD_disc_y_8;
  TGraph2D *VDDD_vs_LDOD_disc_8;
  TGraph *marker_x_8_VDDD;
  TGraph *marker_y_8_VDDD;
  TGraph2D *marker_8_VDDD;
  VDDD_vs_LDOD_disc_x_8 = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.VDDD_vs_LDOD_disc_x,"TID [MRAD]","VDDD vs LDOD Discontinuity [LDOD Setting]", "VDDD vs LDOD Discontinuity [LDOD setting]");
  VDDD_vs_LDOD_disc_y_8 = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.VDDD_vs_LDOD_disc_y, "TID [MRAD]","VDDD vs LDOD Discontinuity [Measured Voltage [V]]", "VDDD vs LDOD Discontinuity [Measured Voltage [V]]");
  VDDD_vs_LDOD_disc_8 = Plot2D(datavTID_EXT_8.VDDD_vs_LDOD_disc_x, datavTID_EXT_8.VDDD_vs_LDOD_disc_y, datavTID_EXT_8.MRad, "VDDD vs LDOD Discontinuity [LDOD Setting]","VDDD vs LDOD Discontinuity [Measured Voltage [V]]","TID [MRad]", "VDDD vs LDOD Discontinuity");
  marker_x_8_VDDD = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_xcoord_VDDD,"TID [MRad]","LDOD Setting","Marker LDOD Setting");
  marker_y_8_VDDD = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_ycoord_VDDD,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_8_VDDD = Plot2D(datavTID_EXT_8.marker_xcoord_VDDD,datavTID_EXT_8.marker_ycoord_VDDD,datavTID_EXT_8.MRad,"LDOD Setting","Measured Voltage [V]","TID [MRad]", "Marker Position");
  TCanvas *EXT_subpad_2_chip_008 = Draw_EXT_subpad_6pads("EXT_subpad_2_chip_008",VDDD_vs_LDOD_disc_x_8,"AP",VDDD_vs_LDOD_disc_y_8,"AP",VDDD_vs_LDOD_disc_8,"colz",marker_x_8_VDDD,"AP",marker_y_8_VDDD,"AP",marker_8_VDDD,"colz");  
  //EXT subpad 2 chip 009
  TGraph *VDDD_vs_LDOD_disc_x_9;
  TGraph *VDDD_vs_LDOD_disc_y_9;
  TGraph2D *VDDD_vs_LDOD_disc_9;
  TGraph *marker_x_9_VDDD;
  TGraph *marker_y_9_VDDD;
  TGraph2D *marker_9_VDDD;
  VDDD_vs_LDOD_disc_x_9 = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.VDDD_vs_LDOD_disc_x,"TID [MRAD]","VDDD vs LDOD Discontinuity [LDOD Setting]", "VDDD vs LDOD Discontinuity [LDOD setting]");
  VDDD_vs_LDOD_disc_y_9 = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.VDDD_vs_LDOD_disc_y, "TID [MRAD]","VDDD vs LDOD Discontinuity [Measured Voltage [V]]", "VDDD vs LDOD Discontinuity [Measured Voltage [V]]");
  VDDD_vs_LDOD_disc_9 = Plot2D(datavTID_EXT_9.VDDD_vs_LDOD_disc_x, datavTID_EXT_9.VDDD_vs_LDOD_disc_y, datavTID_EXT_9.MRad, "VDDD vs LDOD Discontinuity [LDOD Setting]","VDDD vs LDOD Discontinuity [Measured Voltage [V]]","TID [MRad]", "VDDD vs LDOD Discontinuity");
  marker_x_9_VDDD = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_xcoord_VDDD,"TID [MRad]","LDOD Setting","Marker LDOD Setting");
  marker_y_9_VDDD = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_ycoord_VDDD,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_9_VDDD = Plot2D(datavTID_EXT_9.marker_xcoord_VDDD,datavTID_EXT_9.marker_ycoord_VDDD,datavTID_EXT_9.MRad,"LDOD Setting","Measured Voltage [V]","TID [MRad]", "Marker Position");
  TCanvas *EXT_subpad_2_chip_009 = Draw_EXT_subpad_6pads("EXT_subpad_2_chip_009",VDDD_vs_LDOD_disc_x_9,"AP",VDDD_vs_LDOD_disc_y_9,"AP",VDDD_vs_LDOD_disc_9,"colz",marker_x_9_VDDD,"AP",marker_y_9_VDDD,"AP",marker_9_VDDD,"colz");  

  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  //EXT subpad 3 chip 008
  TGraph *TRDAC_p0_8;
  TGraph *TRDAC_p1_8;
  TGraph2D *TRDAC_8;
  TRDAC_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.TRDACfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","TRDAC p0");
  TRDAC_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.TRDACfitp1, "TID [MRad]","Parameter p1 [Gradieent]","TRDAC p1");
  TRDAC_8 = Plot2D(datavTID_EXT_8.TRDACfitp0, datavTID_EXT_8.TRDACfitp1, datavTID_EXT_8.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","TRDAC Parameters");
  TCanvas *EXT_subpad_3_chip_008 = Draw_EXT_subpad_3pads("EXT_subpad_3_chip_008",TRDAC_p0_8,"AP",TRDAC_p1_8,"AP",TRDAC_8,"colz");
  //EXT subpad 3 chip 009
  TGraph *TRDAC_p0_9;
  TGraph *TRDAC_p1_9;
  TGraph2D *TRDAC_9;
  TRDAC_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.TRDACfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","TRDAC p0");
  TRDAC_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.TRDACfitp1, "TID [MRad]","Parameter p1 [Gradieent]","TRDAC p1");
  TRDAC_9 = Plot2D(datavTID_EXT_9.TRDACfitp0, datavTID_EXT_9.TRDACfitp1, datavTID_EXT_9.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","TRDAC Parameters");
  TCanvas *EXT_subpad_3_chip_009 = Draw_EXT_subpad_3pads("EXT_subpad_3_chip_009",TRDAC_p0_9,"AP",TRDAC_p1_9,"AP",TRDAC_9,"colz");

  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  //EXT subpad 4 chip 008
  TGraph *VRef_p0_8;
  TGraph *VRef_p1_8;
  TGraph2D *VRef_8;
  TGraph *marker_x_8_VRef;
  TGraph *marker_y_8_VRef;
  TGraph2D *marker_8_VRef;
  VRef_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VReffitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","VRef p0");
  VRef_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VReffitp1, "TID [MRad]","Parameter p1 [Gradieent]","VRef p1");
  VRef_8 = Plot2D(datavTID_EXT_8.VReffitp0, datavTID_EXT_8.VReffitp1, datavTID_EXT_8.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","VRef Parameters");
  marker_x_8_VRef = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_xcoord_VRef,"TID [MRad]","Variable Setting","Marker Variable Setting");
  marker_y_8_VRef = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_ycoord_VRef,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_8_VRef = Plot2D(datavTID_EXT_8.marker_xcoord_VRef,datavTID_EXT_8.marker_ycoord_VRef,datavTID_EXT_8.MRad,"Variable Setting","Measured Voltage [V]","TID [MRad]", "Marker Position (Null)");
  TCanvas *EXT_subpad_4_chip_008 = Draw_EXT_subpad_6pads("EXT_subpad_4_chip_008",VRef_p0_8,"AP",VRef_p1_8,"AP",VRef_8,"colz",marker_x_8_VRef,"AP",marker_y_8_VRef,"AP",marker_8_VRef,"AP");  
  //EXT subpad 4 chip 009
  TGraph *VRef_p0_9;
  TGraph *VRef_p1_9;
  TGraph2D *VRef_9;
  TGraph *marker_x_9_VRef;
  TGraph *marker_y_9_VRef;
  TGraph2D *marker_9_VRef;
  VRef_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VReffitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","VRef p0");
  VRef_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VReffitp1, "TID [MRad]","Parameter p1 [Gradieent]","VRef p1");
  VRef_9 = Plot2D(datavTID_EXT_9.VReffitp0, datavTID_EXT_9.VReffitp1, datavTID_EXT_9.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","VRef Parameters");
  marker_x_9_VRef = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_xcoord_VRef,"TID [MRad]","Variable Setting","Marker Variable Setting");
  marker_y_9_VRef = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_ycoord_VRef,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_9_VRef = Plot2D(datavTID_EXT_9.marker_xcoord_VRef,datavTID_EXT_9.marker_ycoord_VRef,datavTID_EXT_9.MRad,"Variable Setting","Measured Voltage [V]","TID [MRad]", "Marker Position (Null)");
  TCanvas *EXT_subpad_4_chip_009 = Draw_EXT_subpad_6pads("EXT_subpad_4_chip_009",VRef_p0_9,"AP",VRef_p1_9,"AP",VRef_9,"colz",marker_x_9_VRef,"AP",marker_y_9_VRef,"AP",marker_9_VRef,"AP");

  //////////////////////////////////////////////////////////////////////////////////////////////////

  //EXT subpad 5 chip 008
  TGraph *IRef_p0_8;
  TGraph *IRef_p1_8;
  TGraph2D *IRef_8;
  TGraph *marker_x_8_IRef;
  TGraph *marker_y_8_IRef;
  TGraph2D *marker_8_IRef;
  IRef_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.IReffitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","IRef p0");
  IRef_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.IReffitp1, "TID [MRad]","Parameter p1 [Gradieent]","IRef p1");
  IRef_8 = Plot2D(datavTID_EXT_8.IReffitp0, datavTID_EXT_8.IReffitp1, datavTID_EXT_8.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","IRef Parameters");
  marker_x_8_IRef = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_xcoord_IRef,"TID [MRad]","Variable Setting","Marker Variable Setting");
  marker_y_8_IRef = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_ycoord_IRef,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_8_IRef = Plot2D(datavTID_EXT_8.marker_xcoord_IRef,datavTID_EXT_8.marker_ycoord_IRef,datavTID_EXT_8.MRad,"Variable Setting","Measured Voltage [V]","TID [MRad]", "Marker Position (Null)");
  TCanvas *EXT_subpad_5_chip_008 = Draw_EXT_subpad_6pads("EXT_subpad_5_chip_008",IRef_p0_8,"AP",IRef_p1_8,"AP",IRef_8,"colz",marker_x_8_IRef,"AP",marker_y_8_IRef,"AP",marker_8_IRef,"AP");  
  //EXT subpad 5 chip 009
  TGraph *IRef_p0_9;
  TGraph *IRef_p1_9;
  TGraph2D *IRef_9;
  TGraph *marker_x_9_IRef;
  TGraph *marker_y_9_IRef;
  TGraph2D *marker_9_IRef;
  IRef_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.IReffitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","IRef p0");
  IRef_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.IReffitp1, "TID [MRad]","Parameter p1 [Gradieent]","IRef p1");
  IRef_9 = Plot2D(datavTID_EXT_9.IReffitp0, datavTID_EXT_9.IReffitp1, datavTID_EXT_9.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","IRef Parameters");
  marker_x_9_IRef = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_xcoord_IRef,"TID [MRad]","Variable Setting","Marker Variable Setting");
  marker_y_9_IRef = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_ycoord_IRef,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_9_IRef = Plot2D(datavTID_EXT_9.marker_xcoord_IRef,datavTID_EXT_9.marker_ycoord_IRef,datavTID_EXT_9.MRad,"Variable Setting","Measured Voltage [V]","TID [MRad]", "Marker Position (Null)");
  TCanvas *EXT_subpad_5_chip_009 = Draw_EXT_subpad_6pads("EXT_subpad_5_chip_009",IRef_p0_9,"AP",IRef_p1_9,"AP",IRef_9,"colz",marker_x_9_IRef,"AP",marker_y_9_IRef,"AP",marker_9_IRef,"AP");

  //////////////////////////////////////////////////////////////////////////////////////////////////

  //EXT subpad 6 chip 008
  TGraph *R8B_p0_8;
  TGraph *R8B_p1_8;
  TGraph2D *R8B_8;
  TGraph *marker_x_8_R8B;
  TGraph *marker_y_8_R8B;
  TGraph2D *marker_8_R8B;
  R8B_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.R8Bfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","R8B p0");
  R8B_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.R8Bfitp1, "TID [MRad]","Parameter p1 [Gradieent]","R8B p1");
  R8B_8 = Plot2D(datavTID_EXT_8.R8Bfitp0, datavTID_EXT_8.R8Bfitp1, datavTID_EXT_8.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","R8B Parameters");
  marker_x_8_R8B = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_xcoord_R8B,"TID [MRad]","Variable Setting","Marker Variable Setting");
  marker_y_8_R8B = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_ycoord_R8B,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_8_R8B = Plot2D(datavTID_EXT_8.marker_xcoord_R8B,datavTID_EXT_8.marker_ycoord_R8B,datavTID_EXT_8.MRad,"Variable Setting","Measured Voltage [V]","TID [MRad]", "Marker Position (Null)");
  TCanvas *EXT_subpad_6_chip_008 = Draw_EXT_subpad_6pads("EXT_subpad_6_chip_008",R8B_p0_8,"AP",R8B_p1_8,"AP",R8B_8,"colz",marker_x_8_R8B,"AP",marker_y_8_R8B,"AP",marker_8_R8B,"AP");  
  //EXT subpad 6 chip 009
  TGraph *R8B_p0_9;
  TGraph *R8B_p1_9;
  TGraph2D *R8B_9;
  TGraph *marker_x_9_R8B;
  TGraph *marker_y_9_R8B;
  TGraph2D *marker_9_R8B;
  R8B_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.R8Bfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","R8B p0");
  R8B_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.R8Bfitp1, "TID [MRad]","Parameter p1 [Gradieent]","R8B p1");
  R8B_9 = Plot2D(datavTID_EXT_9.R8Bfitp0, datavTID_EXT_9.R8Bfitp1, datavTID_EXT_9.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","R8B Parameters");
  marker_x_9_R8B = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_xcoord_R8B,"TID [MRad]","Variable Setting","Marker Variable Setting");
  marker_y_9_R8B = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_ycoord_R8B,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_9_R8B = Plot2D(datavTID_EXT_9.marker_xcoord_R8B,datavTID_EXT_9.marker_ycoord_R8B,datavTID_EXT_9.MRad,"Variable Setting","Measured Voltage [V]","TID [MRad]", "Marker Position (Null)");
  TCanvas *EXT_subpad_6_chip_009 = Draw_EXT_subpad_6pads("EXT_subpad_6_chip_009",R8B_p0_9,"AP",R8B_p1_9,"AP",R8B_9,"colz",marker_x_9_R8B,"AP",marker_y_9_R8B,"AP",marker_9_R8B,"AP");

  //////////////////////////////////////////////////////////////////////////////////////////////////

  //EXT subpad 7 chip 008
  TGraph *VCD_p0_8;
  TGraph *VCD_p1_8;
  TGraph2D *VCD_8;
  VCD_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VCDfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","VCD p0");
  VCD_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VCDfitp1, "TID [MRad]","Parameter p1 [Gradieent]","VCD p1");
  VCD_8 = Plot2D(datavTID_EXT_8.VCDfitp0, datavTID_EXT_8.VCDfitp1, datavTID_EXT_8.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","VCD Parameters");
  TCanvas *EXT_subpad_7_chip_008 = Draw_EXT_subpad_3pads("EXT_subpad_7_chip_008",VCD_p0_8,"AP",VCD_p1_8,"AP",VCD_8,"colz");
  //EXT subpad 7 chip 009
  TGraph *VCD_p0_9;
  TGraph *VCD_p1_9;
  TGraph2D *VCD_9;
  VCD_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VCDfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","VCD p0");
  VCD_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VCDfitp1, "TID [MRad]","Parameter p1 [Gradieent]","VCD p1");
  VCD_9 = Plot2D(datavTID_EXT_9.VCDfitp0, datavTID_EXT_9.VCDfitp1, datavTID_EXT_9.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","VCD Parameters");
  TCanvas *EXT_subpad_7_chip_009 = Draw_EXT_subpad_3pads("EXT_subpad_7_chip_009",VCD_p0_9,"AP",VCD_p1_9,"AP",VCD_9,"colz");

  //////////////////////////////////////////////////////////////////////////////////////////////////

  //EXT subpad 8 chip 008
  TGraph *CALLINE_p0_8;
  TGraph *CALLINE_p1_8;
  TGraph2D *CALLINE_8;
  CALLINE_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.CALLINEfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","CALLINE p0");
  CALLINE_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.CALLINEfitp1, "TID [MRad]","Parameter p1 [Gradieent]","CALLINE p1");
  CALLINE_8 = Plot2D(datavTID_EXT_8.CALLINEfitp0, datavTID_EXT_8.CALLINEfitp1, datavTID_EXT_8.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","CALLINE Parameters");
  TCanvas *EXT_subpad_8_chip_008 = Draw_EXT_subpad_3pads("EXT_subpad_8_chip_008",CALLINE_p0_8,"AP",CALLINE_p1_8,"AP",CALLINE_8,"colz");
  //EXT subpad 8 chip 009
  TGraph *CALLINE_p0_9;
  TGraph *CALLINE_p1_9;
  TGraph2D *CALLINE_9;
  CALLINE_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.CALLINEfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","CALLINE p0");
  CALLINE_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.CALLINEfitp1, "TID [MRad]","Parameter p1 [Gradieent]","CALLINE p1");
  CALLINE_9 = Plot2D(datavTID_EXT_9.CALLINEfitp0, datavTID_EXT_9.CALLINEfitp1, datavTID_EXT_9.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","CALLINE Parameters");
  TCanvas *EXT_subpad_8_chip_009 = Draw_EXT_subpad_3pads("EXT_subpad_8_chip_009",CALLINE_p0_9,"AP",CALLINE_p1_9,"AP",CALLINE_9,"colz");

  //////////////////////////////////////////////////////////////////////////////////////////////////

  //EXT subpad 9 chip 008
  TGraph *THDAC_p0_8;
  TGraph *THDAC_p1_8;
  TGraph2D *THDAC_8;
  THDAC_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.THDACfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","THDAC p0");
  THDAC_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.THDACfitp1, "TID [MRad]","Parameter p1 [Gradieent]","THDAC p1");
  THDAC_8 = Plot2D(datavTID_EXT_8.THDACfitp0, datavTID_EXT_8.THDACfitp1, datavTID_EXT_8.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","THDAC Parameters");
  TCanvas *EXT_subpad_9_chip_008 = Draw_EXT_subpad_3pads("EXT_subpad_9_chip_008",THDAC_p0_8,"AP",THDAC_p1_8,"AP",THDAC_8,"colz");
  //EXT subpad 9 chip 009
  TGraph *THDAC_p0_9;
  TGraph *THDAC_p1_9;
  TGraph2D *THDAC_9;
  THDAC_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.THDACfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","THDAC p0");
  THDAC_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.THDACfitp1, "TID [MRad]","Parameter p1 [Gradieent]","THDAC p1");
  THDAC_9 = Plot2D(datavTID_EXT_9.THDACfitp0, datavTID_EXT_9.THDACfitp1, datavTID_EXT_9.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","THDAC Parameters");
  TCanvas *EXT_subpad_9_chip_009 = Draw_EXT_subpad_3pads("EXT_subpad_9_chip_009",THDAC_p0_9,"AP",THDAC_p1_9,"AP",THDAC_9,"colz");

  //////////////////////////////////////////////////////////////////////////////////////////////////
 
  //EXT subpad 10 chip 008
  TGraph *VTHTEST_p0_8;
  TGraph *VTHTEST_p1_8;
  TGraph *VTHTEST_p2_8;
  TGraph *VTHTEST_p3_8;
  VTHTEST_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VTHTESTfitp0, "TID [MRad]","Parameter p0", "VTHTEST p0");
  VTHTEST_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VTHTESTfitp1, "TID [MRad]","Parameter p1", "VTHTEST p1");
  VTHTEST_p2_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VTHTESTfitp2, "TID [MRad]","Parameter p2", "VTHTEST p2");
  VTHTEST_p3_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VTHTESTfitp3, "TID [MRad]","Parameter p3", "VTHTEST p3");
  TCanvas *EXT_subpad_10_chip_008 = Draw_EXT_subpad_4pads("EXT_subpad_10_chip_008",VTHTEST_p0_8,"AP",VTHTEST_p1_8,"AP",VTHTEST_p2_8,"AP",VTHTEST_p3_8,"AP");
  //EXT subpad 10 chip 009
  TGraph *VTHTEST_p0_9;
  TGraph *VTHTEST_p1_9;
  TGraph *VTHTEST_p2_9;
  TGraph *VTHTEST_p3_9;
  VTHTEST_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VTHTESTfitp0, "TID [MRad]","Parameter p0", "VTHTEST p0");
  VTHTEST_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VTHTESTfitp1, "TID [MRad]","Parameter p1", "VTHTEST p1");
  VTHTEST_p2_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VTHTESTfitp2, "TID [MRad]","Parameter p2", "VTHTEST p2");
  VTHTEST_p3_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VTHTESTfitp3, "TID [MRad]","Parameter p3", "VTHTEST p3");
  TCanvas *EXT_subpad_10_chip_009 = Draw_EXT_subpad_4pads("EXT_subpad_10_chip_009",VTHTEST_p0_9,"AP",VTHTEST_p1_9,"AP",VTHTEST_p2_9,"AP",VTHTEST_p3_9,"AP");

  //////////////////////////////////////////////////////////////////////////////////////////////////

  //EXT subpad 11 chip 008
  TGraph *COM_p0_8;
  TGraph *COM_p1_8;
  TGraph2D *COM_8;
  TGraph *marker_x_8_COM;
  TGraph *marker_y_8_COM;
  TGraph2D *marker_8_COM;
  COM_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.COMfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","COM p0");
  COM_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.COMfitp1, "TID [MRad]","Parameter p1 [Gradieent]","COM p1");
  COM_8 = Plot2D(datavTID_EXT_8.COMfitp0, datavTID_EXT_8.COMfitp1, datavTID_EXT_8.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","COM Parameters");
  marker_x_8_COM = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_xcoord_COM,"TID [MRad]","Variable Setting","Marker Variable Setting");
  marker_y_8_COM = Plot(datavTID_EXT_8.MRad,datavTID_EXT_8.marker_ycoord_COM,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_8_COM = Plot2D(datavTID_EXT_8.marker_xcoord_COM,datavTID_EXT_8.marker_ycoord_COM,datavTID_EXT_8.MRad,"Variable Setting","Measured Voltage [V]","TID [MRad]", "Marker Position (Null)");
  TCanvas *EXT_subpad_11_chip_008 = Draw_EXT_subpad_6pads("EXT_subpad_11_chip_008",COM_p0_8,"AP",COM_p1_8,"AP",COM_8,"colz",marker_x_8_COM,"AP",marker_y_8_COM,"AP",marker_8_COM,"AP");
  //EXT subpad 11 chip 009
  TGraph *COM_p0_9;
  TGraph *COM_p1_9;
  TGraph2D *COM_9;
  TGraph *marker_x_9_COM;
  TGraph *marker_y_9_COM;
  TGraph2D *marker_9_COM;
  COM_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.COMfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","COM p0");
  COM_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.COMfitp1, "TID [MRad]","Parameter p1 [Gradieent]","COM p1");
  COM_9 = Plot2D(datavTID_EXT_9.COMfitp0, datavTID_EXT_9.COMfitp1, datavTID_EXT_9.MRad,"Parameter p0 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","COM Parameters");
  marker_x_9_COM = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_xcoord_COM,"TID [MRad]","Variable Setting","Marker Variable Setting");
  marker_y_9_COM = Plot(datavTID_EXT_9.MRad,datavTID_EXT_9.marker_ycoord_COM,"TID [MRad]","Measured Voltage [V]","Marker Measured Voltage [V]");
  marker_9_COM = Plot2D(datavTID_EXT_9.marker_xcoord_COM,datavTID_EXT_9.marker_ycoord_COM,datavTID_EXT_9.MRad,"Variable Setting","Measured Voltage [V]","TID [MRad]", "Marker Position (Null)");
  TCanvas *EXT_subpad_11_chip_009 = Draw_EXT_subpad_6pads("EXT_subpad_11_chip_009",COM_p0_9,"AP",COM_p1_9,"AP",COM_9,"colz",marker_x_9_COM,"AP",marker_y_9_COM,"AP",marker_9_COM,"AP");

  //////////////////////////////////////////////////////////////////////////////////////////////////

  //EXT subpad 12 chip 008
  TGraph *DRIVE_p0_8;
  TGraph *DRIVE_p1_8;
  TGraph2D *DRIVE_8;
  DRIVE_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.DRIVEfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","DRIVE p0");
  DRIVE_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.DRIVEfitp1, "TID [MRad]","Parameter p1 [Gradieent]","DRIVE p1");
  DRIVE_8 = Plot2D(datavTID_EXT_8.DRIVEfitp0, datavTID_EXT_8.DRIVEfitp1, datavTID_EXT_8.MRad,"Parameter p0 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","DRIVE Parameters");
  TCanvas *EXT_subpad_12_chip_008 = Draw_EXT_subpad_3pads("EXT_subpad_12_chip_008",DRIVE_p0_8,"AP",DRIVE_p1_8,"AP",DRIVE_8,"colz");
  //EXT subpad 12 chip 009
  TGraph *DRIVE_p0_9;
  TGraph *DRIVE_p1_9;
  TGraph2D *DRIVE_9;
  DRIVE_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.DRIVEfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","DRIVE p0");
  DRIVE_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.DRIVEfitp1, "TID [MRad]","Parameter p1 [Gradieent]","DRIVE p1");
  DRIVE_9 = Plot2D(datavTID_EXT_9.DRIVEfitp0, datavTID_EXT_9.DRIVEfitp1, datavTID_EXT_9.MRad,"Parameter p0 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","DRIVE Parameters");
  TCanvas *EXT_subpad_12_chip_009 = Draw_EXT_subpad_3pads("EXT_subpad_12_chip_009",DRIVE_p0_9,"AP",DRIVE_p1_9,"AP",DRIVE_9,"colz");

  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  std::cout<<"================================================================================================\n"<<std::endl;	      
  std::cout<<"Total number of files read = "<<filecount<<std::endl;
  std::cout<<"Total number of files processed = "<<processedfilecount<<std::endl;
  std::cout<<"Total number of files rejected  = "<<filecount-processedfilecount<<std::endl;
  std::cout<<"\n";
  std::cout<<"Total number of pads read = "<<padcount<<std::endl;
  std::cout<<"Total number of pads processed = "<<processedpadcount<<std::endl;
  std::cout<<"Total number of pads rejected = "<<padcount-processedpadcount<<std::endl;
  std::cout<<"\n";
  std::cout<<"Ratio pads:files read = " << (padcount*1.)/(filecount*1.)<<std::endl;
  std::cout<<"Ratio pads:files processed = " << (processedpadcount*1.)/(processedfilecount*1.)<<std::endl;
  std::cout<<"Ratio pads:files rejected = " << ((padcount-processedpadcount)*1.)/((filecount-processedfilecount)*1.)<<std::endl;
  std::cout<<"\n";
}
