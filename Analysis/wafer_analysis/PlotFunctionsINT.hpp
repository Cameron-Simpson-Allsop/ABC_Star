#include <iostream>
#include <string>

struct Data_vs_TID_INT
{
  std::vector<double> timeStamp;
  std::vector<double> MRad;
  std::vector<double> VDDA_vs_LDOA_disc_x;
  std::vector<double> VDDA_vs_LDOA_disc_y;
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
}
