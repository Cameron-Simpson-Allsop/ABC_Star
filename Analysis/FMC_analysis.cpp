#include <iostream>
#include <vector>
#include <fstream>

struct Data
{
  std::vector<double> TID,IDDD,IDDA,VDDD,VDDA,VD_RAW,VA_RAW,VD_REG,VA_REG,GND,GNDD,GNDA,NTC0,NTC1,TESTRES;
};

Data ProcessFile(std::string filePath)
{
  Data data;
  std::string errorMsg{"Error opening file '"+filePath+"'..."};
  std::string successMsg{"File '"+filePath+"' succesfully processed..."};
  std::string fileLine{""};
  int linecount{0};
  std::string weekday,month,day,timestamp,year;
  double TID,IDDD,IDDA,VDDD,VDDA,VD_RAW,VA_RAW,VD_REG,VA_REG,GND,GNDD,GNDA,NTC0,NTC1,TESTRES;

  ifstream inFile;
  std::cout<<"\n\n Beginning file '"+filePath+"'..."<<"\n\n"<<std::endl;
  inFile.open(filePath);
  if(!inFile.good())
    {
      std::cout<<errorMsg<<std::endl;
      return data;
    }
  getline(inFile,fileLine);
  while(!inFile.eof())
    {
      getline(inFile,fileLine);
      stringstream ss(fileLine);
      ss >> weekday >> month >> day >> timestamp >> year >> TID >> IDDD >> IDDA >> VDDD >> VDDA >> VD_RAW >> VA_RAW >> VD_REG >> VA_REG >> GND >> GNDD >> GNDA >> NTC0 >> NTC1 >> TESTRES;

      data.TID.push_back(TID); data.IDDD.push_back(IDDD); data.IDDA.push_back(IDDA); data.VDDD.push_back(VDDD); data.VDDA.push_back(VDDA); data.VD_RAW.push_back(VD_RAW); data.VA_RAW.push_back(VA_RAW); data.VD_REG.push_back(VD_REG); data.VA_REG.push_back(VA_REG); data.GND.push_back(GND); data.GNDD.push_back(GNDD); data.GNDA.push_back(GNDA); data.NTC0.push_back(NTC0); data.NTC1.push_back(NTC1); data.TESTRES.push_back(TESTRES);
    }

  std::cout<<successMsg<<std::endl;
  return data;
}

void PlotSettings(TGraph *g,TString xtitle,TString ytitle)
{
  g->SetTitle("");
  g->GetXaxis()->SetTitle(xtitle);
  g->GetYaxis()->SetTitle(ytitle);
}

void Plotter(Data data, TString cantitle)
{
  TGraph *g_IDDD = new TGraph(data.TID.size(),&(data.TID[0]),&(data.IDDD[0]));
  TGraph *g_IDDA = new TGraph(data.TID.size(),&(data.TID[0]),&(data.IDDA[0]));
  TGraph *g_VDDD = new TGraph(data.TID.size(),&(data.TID[0]),&(data.VDDD[0]));
  TGraph *g_VDDA = new TGraph(data.TID.size(),&(data.TID[0]),&(data.VDDA[0]));
  TGraph *g_VD_RAW = new TGraph(data.TID.size(),&(data.TID[0]),&(data.VD_RAW[0]));
  TGraph *g_VA_RAW = new TGraph(data.TID.size(),&(data.TID[0]),&(data.VA_RAW[0]));
  TGraph *g_VD_REG = new TGraph(data.TID.size(),&(data.TID[0]),&(data.VD_REG[0]));
  TGraph *g_VA_REG = new TGraph(data.TID.size(),&(data.TID[0]),&(data.VA_REG[0]));
  TGraph *g_GND = new TGraph(data.TID.size(),&(data.TID[0]),&(data.GND[0]));
  TGraph *g_GNDD = new TGraph(data.TID.size(),&(data.TID[0]),&(data.GNDD[0]));
  TGraph *g_GNDA = new TGraph(data.TID.size(),&(data.TID[0]),&(data.GNDA[0]));
  TGraph *g_NTC0 = new TGraph(data.TID.size(),&(data.TID[0]),&(data.NTC0[0]));
  TGraph *g_NTC1 = new TGraph(data.TID.size(),&(data.TID[0]),&(data.NTC1[0]));
  TGraph *g_TESTRES = new TGraph(data.TID.size(),&(data.TID[0]),&(data.TESTRES[0]));

  PlotSettings(g_IDDD,"TID [MRad]","IDDD [mA]");
  PlotSettings(g_IDDA,"TID [MRad]","IDDA");
  PlotSettings(g_VDDD,"TID [MRad]","VDDD");
  PlotSettings(g_VDDA,"TID [MRad]","VDDA");
  PlotSettings(g_VD_RAW,"TID [MRad]","VD_RAW");
  PlotSettings(g_VA_RAW,"TID [MRad]","VA_RAW");
  PlotSettings(g_VD_REG,"TID [MRad]","VD_REG");
  PlotSettings(g_VA_REG,"TID [MRad]","VA_REG");
  PlotSettings(g_GND,"TID [MRad]","GND");
  PlotSettings(g_GNDD,"TID [MRad]","GNDD");
  PlotSettings(g_GNDA,"TID [MRad]","GNDA");
  PlotSettings(g_NTC0,"TID [MRad]","NTC0");
  PlotSettings(g_NTC1,"TID [MRad]","NTC1");
  PlotSettings(g_TESTRES,"TID [MRad]","TESTRES");

  TCanvas *canvas = new TCanvas(cantitle,cantitle,600,600);
  canvas->Divide(4,4);
  canvas->cd(1); g_IDDD->Draw("AL"); canvas->cd(2); g_IDDA->Draw("AL"); canvas->cd(3); g_VDDD->Draw("AL"); canvas->cd(4); g_VDDA->Draw("AL"); canvas->cd(5); g_VD_RAW->Draw("AL"); canvas->cd(6); g_VA_RAW->Draw("AL"); canvas->cd(7); g_VD_REG->Draw("AL"); canvas->cd(8); g_VA_REG->Draw("AL"); canvas->cd(9); g_GND->Draw("AL"); canvas->cd(10); g_GNDD->Draw("AL"); canvas->cd(11); g_GNDA->Draw("AL"); canvas->cd(12); g_NTC0->Draw("AL"); canvas->cd(13); g_NTC1->Draw("AL"); canvas->cd(14); g_TESTRES->Draw("AL");

  TString can1title = cantitle + "_IDDD";
  TCanvas *canvas1 = new TCanvas(can1title,can1title,600,600);
  g_IDDD->GetXaxis()->SetRangeUser(0,10);
  g_IDDD->Draw("AL");
  canvas1->SaveAs("Plots/FMC/"+can1title+".pdf"); 
  
}

void FMC_analysis()
{
  Data FMC_190;
  Data FMC_204;
  FMC_190 = ProcessFile("../logs/FMC_monitoring_190.txt");
  FMC_204 = ProcessFile("../logs/FMC_monitoring_204.txt");
  Plotter(FMC_190,"FMC_190");
  Plotter(FMC_204, "FMC_204");  
}
