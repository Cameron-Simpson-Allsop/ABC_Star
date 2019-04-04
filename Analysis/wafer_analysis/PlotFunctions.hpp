#include <iostream>
#include <string>
//#include "Data_vs_TID_EXT.hpp"

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
  std::vector<double> VCDfitp2;
  std::vector<double> VCDfitp3;
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
  std::vector<double> DRIVEfitp2;
  std::vector<double> DRIVEfitp3;
  std::vector<double> VBfitp0;
  std::vector<double> VBfitp1;
  std::vector<double> VBfitp2;
  std::vector<double> VBfitp3;
};

struct Data_vs_TID_INT
{
  std::vector<double> timeStamp;
  std::vector<double> MRad;
  std::vector<double> VDDA_vs_LDOA_disc_x;
  std::vector<double> VDDA_vs_LDOA_disc_y;
};


TGraph *Plot(std::vector<double> x, std::vector<double> y, TString xtitle, TString ytitle, TString title)
{
  TGraph *g = new TGraph(x.size(),&(x[0]),&(y[0]));g->GetXaxis()->SetTitle(xtitle);g->GetYaxis()->SetTitle(ytitle);g->SetTitle(title);g->SetMarkerStyle(20);g->SetMarkerSize(0.5);return g;
}

TCanvas *Draw_subpad_6pads(TString cantitle, TGraph *g1, TString cg1, TGraph *g2,TString cg2, TGraph2D *g3, TString cg3, TGraph *g4, TString cg4, TGraph *g5, TString cg5, TGraph2D *g6, TString cg6)
{
  TGaxis::SetMaxDigits(2);
  TCanvas *c = new TCanvas(cantitle,cantitle,1800,900);
  c->Divide(3,2);c->cd(1);g1->Draw(cg1);c->cd(2);g2->Draw(cg2);c->cd(3);g3->Draw(cg3);c->cd(4);g4->Draw(cg4);c->cd(5);g5->Draw(cg5);c->cd(6);g6->Draw(cg6);

  c->cd(3)->SetRightMargin(0.2);
  c->cd(6)->SetRightMargin(0.2);
  c->cd(1)->SetLeftMargin(0.12);
  c->cd(2)->SetLeftMargin(0.12);
  c->cd(3)->SetLeftMargin(0.12);
  c->cd(4)->SetLeftMargin(0.12);
  c->cd(5)->SetLeftMargin(0.12);
  c->cd(6)->SetLeftMargin(0.12);
  
  c->SaveAs("../Plots/wafer/"+cantitle+".root");c->SaveAs("../Plots/wafer/"+cantitle+".pdf");
  c->Close();
  return c;
}
TCanvas *Draw_subpad_3pads(TString cantitle, TGraph *g1, TString cg1, TGraph *g2, TString cg2, TGraph2D *g3, TString cg3)
{
  TGaxis::SetMaxDigits(2);
  TCanvas *c = new TCanvas(cantitle,cantitle,1800,900);
  c->Divide(3,1);c->cd(1);g1->Draw(cg1);c->cd(2);g2->Draw(cg2);c->cd(3);g3->Draw(cg3);

  c->cd(3)->SetRightMargin(0.15);
  c->cd(3)->SetLeftMargin(0.15);
  c->cd(2)->SetLeftMargin(0.15);
  c->cd(1)->SetLeftMargin(0.15);  
  
  c->SaveAs("../Plots/wafer/"+cantitle+".root");c->SaveAs("../Plots/wafer/"+cantitle+".pdf");
  c->Close();
  return c;
}
TCanvas *Draw_subpad_4pads(TString cantitle, TGraph *g1, TString cg1, TGraph *g2, TString cg2, TGraph *g3, TString cg3, TGraph *g4, TString cg4)
{
  TGaxis::SetMaxDigits(2);
  TCanvas *c = new TCanvas(cantitle,cantitle,1800,900);
  c->Divide(2,2);c->cd(1);g1->Draw(cg1);c->cd(2);g2->Draw(cg2);c->cd(3);g3->Draw(cg3);c->cd(4);g4->Draw(cg4);

  c->SaveAs("../Plots/wafer/"+cantitle+".root");c->SaveAs("../Plots/wafer/"+cantitle+".pdf");
  c->Close();
  return c;
}

TCanvas *Draw_subpad_8pads(TString cantitle, TGraph *g1, TString cg1, TGraph *g2, TString cg2, TGraph *g3, TString cg3, TGraph *g4, TString cg4, TGraph *g5, TString cg5, TGraph *g6, TString cg6, TGraph *g7, TString cg7, TGraph *g8, TString cg8)
{
  TGaxis::SetMaxDigits(2);
  TCanvas *c = new TCanvas(cantitle,cantitle,1800,900);
  c->Divide(4,2);c->cd(1);g1->Draw(cg1);c->cd(2);g2->Draw(cg2);c->cd(3);g3->Draw(cg3);c->cd(4);g4->Draw(cg4);c->cd(5);g1->Draw(cg5);c->cd(6);g1->Draw(cg6);c->cd(7);g1->Draw(cg7);c->cd(8);g1->Draw(cg8);

  c->cd(1)->SetLeftMargin(0.15);
  c->cd(2)->SetLeftMargin(0.15);
  c->cd(3)->SetLeftMargin(0.15);
  c->cd(4)->SetLeftMargin(0.15);
  c->cd(5)->SetLeftMargin(0.15);
  c->cd(6)->SetLeftMargin(0.15);
  c->cd(7)->SetLeftMargin(0.15);
  c->cd(8)->SetLeftMargin(0.15);  
  
  c->SaveAs("../Plots/wafer/"+cantitle+".root");c->SaveAs("../Plots/wafer/"+cantitle+".pdf");
  c->Close();
  return c;
}

TGraph2D *Plot2D(std::vector<double> xvec, std::vector<double> yvec, std::vector<double> zvec, TString xtitle, TString ytitle, TString ztitle, TString title)
{
  TGraph2D *g = new TGraph2D();g->SetTitle(title+";"+xtitle+";"+ytitle+";"+ztitle);Double_t x,y,z;for(int i{0}; i<xvec.size(); ++i){x=xvec[i];y=yvec[i];z=zvec[i];g->SetPoint(i,x,y,z);}return g;
}

void PlotFunctions(Data_vs_TID_EXT datavTID_EXT_8, Data_vs_TID_EXT datavTID_EXT_9)
{
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
  timestamp_TID_can->Close();
  
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
  TCanvas *EXT_subpad_1_chip_008 = Draw_subpad_6pads("EXT_subpad_1_chip_008",VDDA_vs_LDOA_disc_x_8,"AP",VDDA_vs_LDOA_disc_y_8,"AP",VDDA_vs_LDOA_disc_8,"colz",marker_x_8_VDDA,"AP",marker_y_8_VDDA,"AP",marker_8_VDDA,"colz");  
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
  TCanvas *EXT_subpad_1_chip_009 = Draw_subpad_6pads("EXT_subpad_1_chip_009",VDDA_vs_LDOA_disc_x_9,"AP",VDDA_vs_LDOA_disc_y_9,"AP",VDDA_vs_LDOA_disc_9,"colz",marker_x_9_VDDA,"AP",marker_y_9_VDDA,"AP",marker_9_VDDA,"colz");

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
  TCanvas *EXT_subpad_2_chip_008 = Draw_subpad_6pads("EXT_subpad_2_chip_008",VDDD_vs_LDOD_disc_x_8,"AP",VDDD_vs_LDOD_disc_y_8,"AP",VDDD_vs_LDOD_disc_8,"colz",marker_x_8_VDDD,"AP",marker_y_8_VDDD,"AP",marker_8_VDDD,"colz");  
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
  TCanvas *EXT_subpad_2_chip_009 = Draw_subpad_6pads("EXT_subpad_2_chip_009",VDDD_vs_LDOD_disc_x_9,"AP",VDDD_vs_LDOD_disc_y_9,"AP",VDDD_vs_LDOD_disc_9,"colz",marker_x_9_VDDD,"AP",marker_y_9_VDDD,"AP",marker_9_VDDD,"colz");  

  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  //EXT subpad 3 chip 008
  TGraph *TRDAC_p0_8;
  TGraph *TRDAC_p1_8;
  TGraph2D *TRDAC_8;
  TRDAC_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.TRDACfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","TRDAC p0");
  TRDAC_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.TRDACfitp1, "TID [MRad]","Parameter p1 [Gradieent]","TRDAC p1");
  TRDAC_8 = Plot2D(datavTID_EXT_8.TRDACfitp0, datavTID_EXT_8.TRDACfitp1, datavTID_EXT_8.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","TRDAC Parameters");
  TCanvas *EXT_subpad_3_chip_008 = Draw_subpad_3pads("EXT_subpad_3_chip_008",TRDAC_p0_8,"AP",TRDAC_p1_8,"AP",TRDAC_8,"colz");
  //EXT subpad 3 chip 009
  TGraph *TRDAC_p0_9;
  TGraph *TRDAC_p1_9;
  TGraph2D *TRDAC_9;
  TRDAC_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.TRDACfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","TRDAC p0");
  TRDAC_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.TRDACfitp1, "TID [MRad]","Parameter p1 [Gradieent]","TRDAC p1");
  TRDAC_9 = Plot2D(datavTID_EXT_9.TRDACfitp0, datavTID_EXT_9.TRDACfitp1, datavTID_EXT_9.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","TRDAC Parameters");
  TCanvas *EXT_subpad_3_chip_009 = Draw_subpad_3pads("EXT_subpad_3_chip_009",TRDAC_p0_9,"AP",TRDAC_p1_9,"AP",TRDAC_9,"colz");

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
  TCanvas *EXT_subpad_4_chip_008 = Draw_subpad_6pads("EXT_subpad_4_chip_008",VRef_p0_8,"AP",VRef_p1_8,"AP",VRef_8,"colz",marker_x_8_VRef,"AP",marker_y_8_VRef,"AP",marker_8_VRef,"AP");  
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
  TCanvas *EXT_subpad_4_chip_009 = Draw_subpad_6pads("EXT_subpad_4_chip_009",VRef_p0_9,"AP",VRef_p1_9,"AP",VRef_9,"colz",marker_x_9_VRef,"AP",marker_y_9_VRef,"AP",marker_9_VRef,"AP");

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
  TCanvas *EXT_subpad_5_chip_008 = Draw_subpad_6pads("EXT_subpad_5_chip_008",IRef_p0_8,"AP",IRef_p1_8,"AP",IRef_8,"colz",marker_x_8_IRef,"AP",marker_y_8_IRef,"AP",marker_8_IRef,"AP");  
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
  TCanvas *EXT_subpad_5_chip_009 = Draw_subpad_6pads("EXT_subpad_5_chip_009",IRef_p0_9,"AP",IRef_p1_9,"AP",IRef_9,"colz",marker_x_9_IRef,"AP",marker_y_9_IRef,"AP",marker_9_IRef,"AP");

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
  TCanvas *EXT_subpad_6_chip_008 = Draw_subpad_6pads("EXT_subpad_6_chip_008",R8B_p0_8,"AP",R8B_p1_8,"AP",R8B_8,"colz",marker_x_8_R8B,"AP",marker_y_8_R8B,"AP",marker_8_R8B,"AP");  
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
  TCanvas *EXT_subpad_6_chip_009 = Draw_subpad_6pads("EXT_subpad_6_chip_009",R8B_p0_9,"AP",R8B_p1_9,"AP",R8B_9,"colz",marker_x_9_R8B,"AP",marker_y_9_R8B,"AP",marker_9_R8B,"AP");

  //////////////////////////////////////////////////////////////////////////////////////////////////

  //EXT subpad 7 chip 008
  TGraph *VCD_p0_8;
  TGraph *VCD_p1_8;
  TGraph *VCD_p2_8;
  TGraph *VCD_p3_8;
  TGraph *VB_p0_8;
  TGraph *VB_p1_8;
  TGraph *VB_p2_8;
  TGraph *VB_p3_8;
  VCD_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VCDfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","VCD p0");
  VCD_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VCDfitp1, "TID [MRad]","Parameter p1 [Gradieent]","VCD p1");
  VCD_p2_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VCDfitp2, "TID [MRad]","Parameter p2 [Gradieent]","VCD p2");
  VCD_p3_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VCDfitp3, "TID [MRad]","Parameter p3 [Gradieent]","VCD p3");  
  VB_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VBfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","VB p0");
  VB_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VBfitp1, "TID [MRad]","Parameter p1 [Gradieent]","VB p1");
  VB_p2_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VBfitp2, "TID [MRad]","Parameter p2 [Gradieent]","VB p2");
  VB_p3_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.VBfitp3, "TID [MRad]","Parameter p3 [Gradieent]","VB p3");
  TCanvas *EXT_subpad_7_chip_008 = Draw_subpad_8pads("EXT_subpad_7_chip_008",VCD_p0_8,"AP",VCD_p1_8,"AP",VCD_p2_8,"AP",VCD_p3_8,"AP",VB_p0_8,"AP",VB_p1_8,"AP",VB_p2_8,"AP",VB_p3_8,"AP");
  //EXT subpad 7 chip 009
  TGraph *VCD_p0_9;
  TGraph *VCD_p1_9;
  TGraph *VCD_p2_9;
  TGraph *VCD_p3_9;
  TGraph *VB_p0_9;
  TGraph *VB_p1_9;
  TGraph *VB_p2_9;
  TGraph *VB_p3_9;
  VCD_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VCDfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","VCD p0");
  VCD_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VCDfitp1, "TID [MRad]","Parameter p1 [Gradieent]","VCD p1");
  VCD_p2_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VCDfitp2, "TID [MRad]","Parameter p2 [Gradieent]","VCD p2");
  VCD_p3_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VCDfitp3, "TID [MRad]","Parameter p3 [Gradieent]","VCD p3");  
  VB_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VBfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","VB p0");
  VB_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VBfitp1, "TID [MRad]","Parameter p1 [Gradieent]","VB p1");
  VB_p2_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VBfitp2, "TID [MRad]","Parameter p2 [Gradieent]","VB p2");
  VB_p3_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VBfitp3, "TID [MRad]","Parameter p3 [Gradieent]","VB p3");
  TCanvas *EXT_subpad_7_chip_009 = Draw_subpad_8pads("EXT_subpad_7_chip_009",VCD_p0_9,"AP",VCD_p1_9,"AP",VCD_p2_9,"AP",VCD_p3_9,"AP",VB_p0_9,"AP",VB_p1_9,"AP",VB_p2_9,"AP",VB_p3_9,"AP");

  //////////////////////////////////////////////////////////////////////////////////////////////////

  //EXT subpad 8 chip 008
  TGraph *CALLINE_p0_8;
  TGraph *CALLINE_p1_8;
  TGraph2D *CALLINE_8;
  CALLINE_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.CALLINEfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","CALLINE p0");
  CALLINE_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.CALLINEfitp1, "TID [MRad]","Parameter p1 [Gradieent]","CALLINE p1");
  CALLINE_8 = Plot2D(datavTID_EXT_8.CALLINEfitp0, datavTID_EXT_8.CALLINEfitp1, datavTID_EXT_8.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","CALLINE Parameters");
  TCanvas *EXT_subpad_8_chip_008 = Draw_subpad_3pads("EXT_subpad_8_chip_008",CALLINE_p0_8,"AP",CALLINE_p1_8,"AP",CALLINE_8,"colz");
  //EXT subpad 8 chip 009
  TGraph *CALLINE_p0_9;
  TGraph *CALLINE_p1_9;
  TGraph2D *CALLINE_9;
  CALLINE_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.CALLINEfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","CALLINE p0");
  CALLINE_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.CALLINEfitp1, "TID [MRad]","Parameter p1 [Gradieent]","CALLINE p1");
  CALLINE_9 = Plot2D(datavTID_EXT_9.CALLINEfitp0, datavTID_EXT_9.CALLINEfitp1, datavTID_EXT_9.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","CALLINE Parameters");
  TCanvas *EXT_subpad_8_chip_009 = Draw_subpad_3pads("EXT_subpad_8_chip_009",CALLINE_p0_9,"AP",CALLINE_p1_9,"AP",CALLINE_9,"colz");

  //////////////////////////////////////////////////////////////////////////////////////////////////

  //EXT subpad 9 chip 008
  TGraph *THDAC_p0_8;
  TGraph *THDAC_p1_8;
  TGraph2D *THDAC_8;
  THDAC_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.THDACfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","THDAC p0");
  THDAC_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.THDACfitp1, "TID [MRad]","Parameter p1 [Gradieent]","THDAC p1");
  THDAC_8 = Plot2D(datavTID_EXT_8.THDACfitp0, datavTID_EXT_8.THDACfitp1, datavTID_EXT_8.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","THDAC Parameters");
  TCanvas *EXT_subpad_9_chip_008 = Draw_subpad_3pads("EXT_subpad_9_chip_008",THDAC_p0_8,"AP",THDAC_p1_8,"AP",THDAC_8,"colz");
  //EXT subpad 9 chip 009
  TGraph *THDAC_p0_9;
  TGraph *THDAC_p1_9;
  TGraph2D *THDAC_9;
  THDAC_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.THDACfitp0, "TID [MRad]","Parameter p0 [Measured Voltage [V]]","THDAC p0");
  THDAC_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.THDACfitp1, "TID [MRad]","Parameter p1 [Gradieent]","THDAC p1");
  THDAC_9 = Plot2D(datavTID_EXT_9.THDACfitp0, datavTID_EXT_9.THDACfitp1, datavTID_EXT_9.MRad,"Parameter p1 [Measured Voltage [V]]","Parameter p1 [Gradient]","TID [MRad]","THDAC Parameters");
  TCanvas *EXT_subpad_9_chip_009 = Draw_subpad_3pads("EXT_subpad_9_chip_009",THDAC_p0_9,"AP",THDAC_p1_9,"AP",THDAC_9,"colz");

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
  TCanvas *EXT_subpad_10_chip_008 = Draw_subpad_4pads("EXT_subpad_10_chip_008",VTHTEST_p0_8,"AP",VTHTEST_p1_8,"AP",VTHTEST_p2_8,"AP",VTHTEST_p3_8,"AP");
  //EXT subpad 10 chip 009
  TGraph *VTHTEST_p0_9;
  TGraph *VTHTEST_p1_9;
  TGraph *VTHTEST_p2_9;
  TGraph *VTHTEST_p3_9;
  VTHTEST_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VTHTESTfitp0, "TID [MRad]","Parameter p0", "VTHTEST p0");
  VTHTEST_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VTHTESTfitp1, "TID [MRad]","Parameter p1", "VTHTEST p1");
  VTHTEST_p2_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VTHTESTfitp2, "TID [MRad]","Parameter p2", "VTHTEST p2");
  VTHTEST_p3_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.VTHTESTfitp3, "TID [MRad]","Parameter p3", "VTHTEST p3");
  TCanvas *EXT_subpad_10_chip_009 = Draw_subpad_4pads("EXT_subpad_10_chip_009",VTHTEST_p0_9,"AP",VTHTEST_p1_9,"AP",VTHTEST_p2_9,"AP",VTHTEST_p3_9,"AP");

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
  TCanvas *EXT_subpad_11_chip_008 = Draw_subpad_6pads("EXT_subpad_11_chip_008",COM_p0_8,"AP",COM_p1_8,"AP",COM_8,"colz",marker_x_8_COM,"AP",marker_y_8_COM,"AP",marker_8_COM,"AP");
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
  TCanvas *EXT_subpad_11_chip_009 = Draw_subpad_6pads("EXT_subpad_11_chip_009",COM_p0_9,"AP",COM_p1_9,"AP",COM_9,"colz",marker_x_9_COM,"AP",marker_y_9_COM,"AP",marker_9_COM,"AP");

  //////////////////////////////////////////////////////////////////////////////////////////////////

  //EXT subpad 12 chip 008
  TGraph *DRIVE_p0_8;
  TGraph *DRIVE_p1_8;
  TGraph *DRIVE_p2_8;
  TGraph *DRIVE_p3_8;      
  DRIVE_p0_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.DRIVEfitp0, "TID [MRad]","Parameter p0","DRIVE p0");
  DRIVE_p1_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.DRIVEfitp1, "TID [MRad]","Parameter p1","DRIVE p1");
  DRIVE_p2_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.DRIVEfitp2, "TID [MRad]","Parameter p2","DRIVE p2");
  DRIVE_p3_8 = Plot(datavTID_EXT_8.MRad, datavTID_EXT_8.DRIVEfitp3, "TID [MRad]","Parameter p3","DRIVE p3");
  TCanvas *EXT_subpad_12_chip_008 = Draw_subpad_4pads("EXT_subpad_12_chip_008",DRIVE_p0_8,"AP",DRIVE_p1_8,"AP",DRIVE_p2_8,"AP",DRIVE_p3_8,"AP");
  //EXT subpad 12 chip 009
  TGraph *DRIVE_p0_9;
  TGraph *DRIVE_p1_9;
  TGraph *DRIVE_p2_9;
  TGraph *DRIVE_p3_9;      
  DRIVE_p0_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.DRIVEfitp0, "TID [MRad]","Parameter p0","DRIVE p0");
  DRIVE_p1_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.DRIVEfitp1, "TID [MRad]","Parameter p1","DRIVE p1");
  DRIVE_p2_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.DRIVEfitp2, "TID [MRad]","Parameter p2","DRIVE p2");
  DRIVE_p3_9 = Plot(datavTID_EXT_9.MRad, datavTID_EXT_9.DRIVEfitp3, "TID [MRad]","Parameter p3","DRIVE p3");
  TCanvas *EXT_subpad_12_chip_009 = Draw_subpad_4pads("EXT_subpad_12_chip_009",DRIVE_p0_9,"AP",DRIVE_p1_9,"AP",DRIVE_p2_9,"AP",DRIVE_p3_9,"AP");

  //////////////////////////////////////////////////////////////////////////////////////////////////
}
