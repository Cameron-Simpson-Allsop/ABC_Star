#include <iostream>
#include <vector>
#include <fstream>

struct Data
{
  std::vector<double> TID,eTRDAC,eVREF,eIREF,eR8B,eVCD,eVB,eVBG,eCALIN,eTHDAC,eVTTES,eVTREF,eGNDA,eCOM,eVDRAW,eVDREG,eVAREG;  
};

Data ProcessFile(std::string filePath)
{
  Data data;
  std::string errorMsg{"Error opening file '"+filePath+"'..."};
  std::string successMsg{"File '"+filePath+"' succesfully processed..."};
  std::string fileLine{""};
  int linecount{0};
  std::string weekday,month,day,timestamp,year;
  double TID,eTRDAC,iTRDAC,eVREF,iVREF,eIREF,iIREF,eR8B,iR8B,eVCD,iVCD,eVB,iVB,eVBG,iVBG,eCALIN,iCALIN,eTHDAC,iTHDAC,eVTTES,iVTTES,eVTREF,iVTREF,eGNDA,iGNDA,eCOM,iCOM,eVDRAW,iVDRAW,eVDREG,iVDREG,eVAREG,iVAREG;
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
      ss >> weekday >> month >> day >> timestamp >> year >> TID >> eTRDAC >> iTRDAC >> eVREF >> iVREF >> eIREF >> iIREF >> eR8B >> iR8B >> eVCD >> iVCD >> eVB >> iVB >> eVBG >> iVBG >> eCALIN >> iCALIN >> eTHDAC >> iTHDAC >> eVTTES >> iVTTES >> eVTREF >> iVTREF >> eGNDA >> iGNDA >> eCOM >> iCOM >> eVDRAW >> iVDRAW >> eVDREG >> iVDREG >> eVAREG >> iVAREG;
      
      // std::cout << weekday << "\t" << month << "\t" << day << "\t" << timestamp << "\t" << year << "\t" << TID << "\t" << eTRDAC << "\t" << iTRDAC << "\t" << eVREF << "\t" << iVREF << "\t" << eIREF << "\t" << iIREF << "\t" << eR8B << "\t" << iR8B << "\t" << eVCD << "\t" << iVCD << "\t" << eVB << "\t" << iVB << "\t" << eVBG << "\t" << iVBG << "\t" << eCALIN << "\t" << iCALIN << "\t" << eTHDAC << "\t" << iTHDAC << "\t" << eVTTES << "\t" << iVTTES << "\t" << eVTREF << "\t" << iVTREF << "\t" << eGNDA << "\t" << iGNDA << "\t" << eCOM << "\t" << iCOM << "\t" << eVDRAW << "\t" << iVDRAW << "\t" << eVDREG << "\t" << iVDREG << "\t" << eVAREG << "\t" << iVAREG << "\n" << std::endl;

      data.TID.push_back(TID); data.eTRDAC.push_back(eTRDAC); data.eVREF.push_back(eVREF); data.eIREF.push_back(eIREF); data.eR8B.push_back(eR8B); data.eVCD.push_back(eVCD); data.eVB.push_back(eVB); data.eVBG.push_back(eVBG); data.eCALIN.push_back(eCALIN); data.eTHDAC.push_back(eTHDAC); data.eVTTES.push_back(eVTTES); data.eVTREF.push_back(eVTREF); data.eGNDA.push_back(eGNDA); data.eCOM.push_back(eCOM); data.eVDRAW.push_back(eVDRAW); data.eVDREG.push_back(eVDREG); data.eVAREG.push_back(eVAREG);

    }  
  // for(int i{0}; i < 5; ++i)
  // {
  //   std::cout << data.TID[i] << "\t" << data.eTRDAC[i] << "\t" << data.eVREF[i] << "\t" << data.eIREF[i] << "\t" << data.eR8B[i] << "\t" << data.eVCD[i] << "\t" << data.eVB[i] << "\t" << data.eVBG[i] << "\t" << data.eCALIN[i] << "\t" << data.eTHDAC[i] << "\t" << data.eVTTES[i] << "\t" << data.eVTREF[i] << "\t" << data.eGNDA[i] << "\t" << data.eCOM[i] << "\t" << data.eVDRAW[i] << "\t" << data.eVDREG[i] << "\t" << data.eVAREG[i] << std::endl; 
  // } 

  std::cout<<successMsg<<std::endl;
  return data;
}

void PlotSettings(TGraph *g,TString xtitle,TString ytitle)
{
  g->SetTitle("");
  g->GetXaxis()->SetTitle(xtitle);
  g->GetYaxis()->SetTitle(ytitle);
}

void Plotter(Data chipdata, TString cantitle)
{
  TGraph *g_eTRDAC = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eTRDAC[0]));
  TGraph *g_eVREF = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eVREF[0]));
  TGraph *g_eIREF = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eIREF[0]));
  TGraph *g_eR8B = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eR8B[0]));
  TGraph *g_eVCD = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eVCD[0]));
  TGraph *g_eVB = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eVB[0]));
  TGraph *g_eVBG = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eVBG[0]));
  TGraph *g_eCALIN = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eCALIN[0]));
  TGraph *g_eTHDAC = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eTHDAC[0]));
  TGraph *g_eVTTES = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eVTTES[0]));
  TGraph *g_eVTREF = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eVTREF[0]));
  TGraph *g_eGNDA = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eGNDA[0]));
  TGraph *g_eCOM = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eCOM[0]));
  TGraph *g_eVDRAW = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eVDRAW[0]));
  TGraph *g_eVDREG = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eVDREG[0]));
  TGraph *g_eVAREG = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.eVAREG[0]));

  PlotSettings(g_eTRDAC,"TID [MRad]","eTRDAC");
  PlotSettings(g_eVREF,"TID [MRad]","eVREF");
  PlotSettings(g_eIREF,"TID [MRad]","eIREF");
  PlotSettings(g_eR8B,"TID [MRad]","eR8B");
  PlotSettings(g_eVCD,"TID [MRad]","eVCD");
  PlotSettings(g_eVB,"TID [MRad]","eVB");
  PlotSettings(g_eVBG,"TID [MRad]","eVBG");
  PlotSettings(g_eCALIN,"TID [MRad]","eCALIN");
  PlotSettings(g_eTHDAC,"TID [MRad]","eTHDAC");
  PlotSettings(g_eVTTES,"TID [MRad]","eVTTES");
  PlotSettings(g_eVTREF,"TID [MRad]","eVTREF");
  PlotSettings(g_eGNDA,"TID [MRad]","eGNDA");
  PlotSettings(g_eCOM,"TID [MRad]","eCOM");
  PlotSettings(g_eVDRAW,"TID [MRad]","eVDRAW");
  PlotSettings(g_eVDREG,"TID [MRad]","eVDREG");
  PlotSettings(g_eVAREG,"TID [MRad]","eVAREG");

  TCanvas *canvas = new TCanvas(cantitle,cantitle,600,600);
  canvas->Divide(4,4);
  canvas->cd(1);
  g_eTRDAC->Draw("AL");
  canvas->cd(2);
  g_eVREF->Draw("AL");
  canvas->cd(3);
  g_eIREF->Draw("AL");
  canvas->cd(4);
  g_eR8B->Draw("AL");
  canvas->cd(5);
  g_eVCD->Draw("AL");
  canvas->cd(6);
  g_eVB->Draw("AL");
  canvas->cd(7);
  g_eVBG->Draw("AL");
  canvas->cd(8);
  g_eCALIN->Draw("AL");
  canvas->cd(9);
  g_eTHDAC->Draw("AL");
  canvas->cd(10);
  g_eVTTES->Draw("AL");
  canvas->cd(11);
  g_eVTREF->Draw("AL");
  canvas->cd(12);
  g_eGNDA->Draw("AL");
  canvas->cd(13);
  g_eCOM->Draw("AL");
  canvas->cd(14);
  g_eVDRAW->Draw("AL");
  canvas->cd(15);
  g_eVDREG->Draw("AL");
  canvas->cd(16);
  g_eVAREG->Draw("AL");
  canvas->SaveAs("Plots/MUX/"+cantitle+"_all.root");
}

void MUX_analysis()
{
  Data MUX_190;
  Data MUX_204;
  MUX_190 = ProcessFile("../logs/MUX_monitoring_190.txt");
  MUX_204 = ProcessFile("../logs/MUX_monitoring_204.txt");
  Plotter(MUX_190,"MUX_190");
  Plotter(MUX_204, "MUX_204");  
}
