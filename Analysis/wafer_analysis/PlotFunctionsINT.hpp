#include <iostream>
#include <string>

struct Data_vs_TID_INT
{
  std::vector<double> timeStamp;
  std::vector<double> MRad;
  std::vector<double> VDDA_vs_LDOA_disc_x;
  std::vector<double> VDDA_vs_LDOA_disc_y;
  std::vector<double> VDDD_vs_LDOD_disc_x;
  std::vector<double> VDDD_vs_LDOD_disc_y;
  std::vector<double> TRDACfitp0;
  std::vector<double> TRDACfitp1;  
};

TGraph *PlotINT(std::vector<double> x, std::vector<double> y, TString xtitle, TString ytitle, TString title)
{
  TGraph *g = new TGraph(x.size(),&(x[0]),&(y[0]));g->GetXaxis()->SetTitle(xtitle);g->GetYaxis()->SetTitle(ytitle);g->SetTitle(title);g->SetMarkerStyle(20);g->SetMarkerSize(0.5);return g;
}

TCanvas *Draw_subpad_INT_6pads(TString cantitle, TGraph *g1, TString cg1, TGraph *g2,TString cg2, TGraph2D *g3, TString cg3, TGraph *g4, TString cg4, TGraph *g5, TString cg5, TGraph2D *g6, TString cg6)
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
TCanvas *Draw_subpad_INT_3pads(TString cantitle, TGraph *g1, TString cg1, TGraph *g2, TString cg2, TGraph2D *g3, TString cg3)
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
TCanvas *Draw_subpad_INT_4pads(TString cantitle, TGraph *g1, TString cg1, TGraph *g2, TString cg2, TGraph *g3, TString cg3, TGraph *g4, TString cg4)
{
  TGaxis::SetMaxDigits(2);
  TCanvas *c = new TCanvas(cantitle,cantitle,1800,900);
  c->Divide(2,2);c->cd(1);g1->Draw(cg1);c->cd(2);g2->Draw(cg2);c->cd(3);g3->Draw(cg3);c->cd(4);g4->Draw(cg4);

  c->SaveAs("../Plots/wafer/"+cantitle+".root");c->SaveAs("../Plots/wafer/"+cantitle+".pdf");
  c->Close();
  return c;
}

TCanvas *Draw_subpad_INT_8pads(TString cantitle, TGraph *g1, TString cg1, TGraph *g2, TString cg2, TGraph *g3, TString cg3, TGraph *g4, TString cg4, TGraph *g5, TString cg5, TGraph *g6, TString cg6, TGraph *g7, TString cg7, TGraph *g8, TString cg8)
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

TGraph2D *PlotINT2D(std::vector<double> xvec, std::vector<double> yvec, std::vector<double> zvec, TString xtitle, TString ytitle, TString ztitle, TString title)
{
  TGraph2D *g = new TGraph2D();g->SetTitle(title+";"+xtitle+";"+ytitle+";"+ztitle);Double_t x,y,z;for(int i{0}; i<xvec.size(); ++i){x=xvec[i];y=yvec[i];z=zvec[i];g->SetPoint(i,x,y,z);}return g;
}

void PlotFunctionsINT(Data_vs_TID_INT datavTID_INT_8, Data_vs_TID_INT datavTID_INT_9)
{
  //INT timestamp vs TID
  TGraph *timestamp_TID_INT_8 = new TGraph(datavTID_INT_8.timeStamp.size(),&(datavTID_INT_8.timeStamp[0]),&(datavTID_INT_8.MRad[0]));
  timestamp_TID_INT_8->SetMarkerStyle(20);
  timestamp_TID_INT_8->SetMarkerSize(0.5);
  timestamp_TID_INT_8->SetMarkerColor(kRed);
  timestamp_TID_INT_8->SetLineColor(kRed);
  TGraph *timestamp_TID_INT_9 = new TGraph(datavTID_INT_9.timeStamp.size(),&(datavTID_INT_9.timeStamp[0]),&(datavTID_INT_9.MRad[0]));
  timestamp_TID_INT_9->SetMarkerStyle(20);
  timestamp_TID_INT_9->SetMarkerSize(0.5);
  timestamp_TID_INT_9->SetMarkerColor(kBlue);
  timestamp_TID_INT_9->SetLineColor(kBlue);
  TMultiGraph *timestamp_TID_INT = new TMultiGraph();
  timestamp_TID_INT->GetXaxis()->SetTitle("Time Stamp");
  timestamp_TID_INT->GetYaxis()->SetTitle("TID [MRad]");
  timestamp_TID_INT->SetTitle("");
  timestamp_TID_INT->Add(timestamp_TID_INT_8,"p");
  timestamp_TID_INT->Add(timestamp_TID_INT_9,"p");
  TLegend *timestamp_TID_INT_leg = new TLegend(0.3,0.3,0.45,0.45);
  timestamp_TID_INT_leg->AddEntry(timestamp_TID_INT_8,"chip 008","lp");
  timestamp_TID_INT_leg->AddEntry(timestamp_TID_INT_9,"chip 009","lp");
  TCanvas *timestamp_TID_INT_can = new TCanvas("timestamp_TID","timestamp_TID",600,600);
  TGaxis::SetMaxDigits(2);
  timestamp_TID_INT_leg->SetBorderSize(0);
  timestamp_TID_INT_leg->SetFillColor(0);
  timestamp_TID_INT_leg->SetTextSize(0.02);
  timestamp_TID_INT_leg->SetFillStyle(1000);
  timestamp_TID_INT_leg->SetTextFont(42);
  timestamp_TID_INT_leg->SetNColumns(1);
  timestamp_TID_INT->Draw("AP");
  //timestamp_TID_INT_leg->Draw("same");
  timestamp_TID_INT_can->SaveAs("../Plots/wafer/INT_timestamp_vs_TID.root");
  //timestamp_TID_INT_can->SaveAs("../Plots/wafer/INT_timestamp_vs_TID.pdf");
  timestamp_TID_INT_can->Close();

  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  //INT subpad 1 chip 008
  TGraph *VDDA_vs_LDOA_disc_x_8;
  TGraph *VDDA_vs_LDOA_disc_y_8;
  TGraph2D *VDDA_vs_LDOA_disc_8;
  VDDA_vs_LDOA_disc_x_8 = PlotINT(datavTID_INT_8.MRad, datavTID_INT_8.VDDA_vs_LDOA_disc_x, "TID [MRad]", "VDDA vs LDOA Discontinuity [LDOA setting]", "VDDA vs LDOA Discontinuity [LDOA setting]");
  VDDA_vs_LDOA_disc_y_8 = PlotINT(datavTID_INT_8.MRad, datavTID_INT_8.VDDA_vs_LDOA_disc_y, "TID [MRad]", "VDDA vs LDOA Discontinuity [Measured Voltage [V]]", "VDDA vs LDOA Discontinuity [Measured Voltage [V]]");
  VDDA_vs_LDOA_disc_8 = PlotINT2D(datavTID_INT_8.VDDA_vs_LDOA_disc_x, datavTID_INT_8.VDDA_vs_LDOA_disc_y, datavTID_INT_8.MRad, "VDDA vs LDOA Discontinuity [LDOA setting]","VDDA vs LDOAD Discontinuity [Measured Voltage [V]]", "TID [MRad]","VDDA vs LDOA Discontinuity");
  TCanvas *INT_subpad_1_chip_008 = Draw_subpad_INT_3pads("INT_subpad_1_chip_008",VDDA_vs_LDOA_disc_x_8,"AP",VDDA_vs_LDOA_disc_y_8,"AP",VDDA_vs_LDOA_disc_8,"colz");
  //INT subpad 1 chip 009
  TGraph *VDDA_vs_LDOA_disc_x_9;
  TGraph *VDDA_vs_LDOA_disc_y_9;
  TGraph2D *VDDA_vs_LDOA_disc_9;
  VDDA_vs_LDOA_disc_x_9 = PlotINT(datavTID_INT_9.MRad, datavTID_INT_9.VDDA_vs_LDOA_disc_x, "TID [MRad]", "VDDA vs LDOA Discontinuity [LDOA setting]", "VDDA vs LDOA Discontinuity [LDOA setting]");
  VDDA_vs_LDOA_disc_y_9 = PlotINT(datavTID_INT_9.MRad, datavTID_INT_9.VDDA_vs_LDOA_disc_y, "TID [MRad]", "VDDA vs LDOA Discontinuity [Measured Voltage [V]]", "VDDA vs LDOA Discontinuity [Measured Voltage [V]]");
  VDDA_vs_LDOA_disc_9 = PlotINT2D(datavTID_INT_9.VDDA_vs_LDOA_disc_x, datavTID_INT_9.VDDA_vs_LDOA_disc_y, datavTID_INT_9.MRad, "VDDA vs LDOA Discontinuity [LDOA setting]","VDDA vs LDOAD Discontinuity [Measured Voltage [V]]", "TID [MRad]","VDDA vs LDOA Discontinuity");
  TCanvas *INT_subpad_1_chip_009 = Draw_subpad_INT_3pads("INT_subpad_1_chip_009",VDDA_vs_LDOA_disc_x_9,"AP",VDDA_vs_LDOA_disc_y_9,"AP",VDDA_vs_LDOA_disc_9,"colz");

  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  //INT subpad 2 chip 008
  TGraph *VDDD_vs_LDOD_disc_x_8;
  TGraph *VDDD_vs_LDOD_disc_y_8;
  TGraph2D *VDDD_vs_LDOD_disc_8;
  VDDD_vs_LDOD_disc_x_8 = PlotINT(datavTID_INT_8.MRad, datavTID_INT_8.VDDD_vs_LDOD_disc_x, "TID [MRad]", "VDDD vs LDOD Discontinuity [LDOD setting]", "VDDD vs LDOD Discontinuity [LDOD setting]");
  VDDD_vs_LDOD_disc_y_8 = PlotINT(datavTID_INT_8.MRad, datavTID_INT_8.VDDD_vs_LDOD_disc_y, "TID [MRad]", "VDDD vs LDOD Discontinuity [Measured Voltage [V]]", "VDDD vs LDOD Discontinuity [Measured Voltage [V]]");
  VDDD_vs_LDOD_disc_8 = PlotINT2D(datavTID_INT_8.VDDD_vs_LDOD_disc_x, datavTID_INT_8.VDDD_vs_LDOD_disc_y, datavTID_INT_8.MRad, "VDDD vs LDOD Discontinuity [LDOD setting]","VDDD vs LDODD Discontinuity [Measured Voltage [V]]", "TID [MRad]","VDDD vs LDOD Discontinuity");
  TCanvas *INT_subpad_2_chip_008 = Draw_subpad_INT_3pads("INT_subpad_2_chip_008",VDDD_vs_LDOD_disc_x_8,"AP",VDDD_vs_LDOD_disc_y_8,"AP",VDDD_vs_LDOD_disc_8,"colz");
  //INT subpad 2 chip 009
  TGraph *VDDD_vs_LDOD_disc_x_9;
  TGraph *VDDD_vs_LDOD_disc_y_9;
  TGraph2D *VDDD_vs_LDOD_disc_9;
  VDDD_vs_LDOD_disc_x_9 = PlotINT(datavTID_INT_9.MRad, datavTID_INT_9.VDDD_vs_LDOD_disc_x, "TID [MRad]", "VDDD vs LDOD Discontinuity [LDOD setting]", "VDDD vs LDOD Discontinuity [LDOD setting]");
  VDDD_vs_LDOD_disc_y_9 = PlotINT(datavTID_INT_9.MRad, datavTID_INT_9.VDDD_vs_LDOD_disc_y, "TID [MRad]", "VDDD vs LDOD Discontinuity [Measured Voltage [V]]", "VDDD vs LDOD Discontinuity [Measured Voltage [V]]");
  VDDD_vs_LDOD_disc_9 = PlotINT2D(datavTID_INT_9.VDDD_vs_LDOD_disc_x, datavTID_INT_9.VDDD_vs_LDOD_disc_y, datavTID_INT_9.MRad, "VDDD vs LDOD Discontinuity [LDOD setting]","VDDD vs LDODD Discontinuity [Measured Voltage [V]]", "TID [MRad]","VDDD vs LDOD Discontinuity");
  TCanvas *INT_subpad_2_chip_009 = Draw_subpad_INT_3pads("INT_subpad_2_chip_009",VDDD_vs_LDOD_disc_x_9,"AP",VDDD_vs_LDOD_disc_y_9,"AP",VDDD_vs_LDOD_disc_9,"colz");
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  //INT subpad 3 chip 008
  TGraph *TRDACredfitp0_8;
  TGraph *TRDACredfitp1_8;
  TGraph2D *TRDACredfit_8;
  TRDACredfitp0_8 = PlotINT(datavTID_INT_8.MRad, datavTID_INT_8.VDDD_vs_LDOD_disc_x, "TID [MRad]", "TRDAC fit p0 [ADC Reading]", "TRDAC fit p0 [ADC Reading]");
  TRDACredfitp1_8 = PlotINT(datavTID_INT_8.MRad, datavTID_INT_8.VDDD_vs_LDOD_disc_y, "TID [MRad]", "TRDAC fit p1", "TRDAC fit p1");
  TRDACredfit_8 = PlotINT2D(datavTID_INT_8.VDDD_vs_LDOD_disc_x, datavTID_INT_8.VDDD_vs_LDOD_disc_y, datavTID_INT_8.MRad, "TRDAC fit p0","TRDAC fit p1", "TID [MRad]","TRDAC fit");
  TCanvas *INT_subpad_3_chip_008 = Draw_subpad_INT_3pads("INT_subpad_3_chip_008",TRDACredfitp0_8,"AP",TRDACredfitp1_8,"AP",TRDACredfit_8,"colz");
  //INT subpad 3 chip 009
  TGraph *TRDACredfitp0_9;
  TGraph *TRDACredfitp1_9;
  TGraph2D *TRDACredfit_9;
  TRDACredfitp0_9 = PlotINT(datavTID_INT_9.MRad, datavTID_INT_9.VDDD_vs_LDOD_disc_x, "TID [MRad]", "TRDAC fit p0 [ADC Reading]", "TRDAC fit p0 [ADC Reading]");
  TRDACredfitp1_9 = PlotINT(datavTID_INT_9.MRad, datavTID_INT_9.VDDD_vs_LDOD_disc_y, "TID [MRad]", "TRDAC fit p1", "TRDAC fit p1");
  TRDACredfit_9 = PlotINT2D(datavTID_INT_9.VDDD_vs_LDOD_disc_x, datavTID_INT_9.VDDD_vs_LDOD_disc_y, datavTID_INT_9.MRad, "TRDAC fit p0","TRDAC fit p1", "TID [MRad]","TRDAC fit");
  TCanvas *INT_subpad_3_chip_009 = Draw_subpad_INT_3pads("INT_subpad_3_chip_009",TRDACredfitp0_9,"AP",TRDACredfitp1_9,"AP",TRDACredfit_9,"colz");
  
}
