#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "TID_Data.hpp"

TID_Data VDOA_vs_LDOA(TString graphName, TString padName, TString fileName, Data data)
{
  TID_Data TID;
  double y1,y2,y3,y4,y5;
  for(int n{0}; n<data.x.size()-4; ++n)
    {
      y1 = data.y[n];
      y2 = data.y[n+1];
      y3 = data.y[n+2];
      y4 = data.y[n+3];
      y5 = data.y[n+4];
      //std::cout<<n<<"\t"<<y1<<"\t"<<y2<<"\t"<<y3<<"\t"<<y4<<"\t"<<y5<<std::endl;
      float tol{0.01};
      if(y5<y4<y3<y2<y1 && abs(y5-y4) > tol && abs(y4-y3) > tol && abs(y3-y2) > tol && abs(y2-y1) > tol)
	{
	  //std::cout<<graphName+" "+padName+" VDDA vs LDOA discontinuity " /*<< fileName*/ << " = " <<data.x[n]<<std::endl;
	  TID.VDDA_vs_LDOA_disc_x = data.x[n];
	  TID.VDDA_vs_LDOA_disc_y = data.y[n];
	  n=data.x.size()-4;
	}
    }
  if(data.init_check == true && (padName == "pad_plot_1" || padName == "pad_plot_2"))
    {
      TF1 *fitlower = new TF1("fitlower","pol1",0,TID.VDDA_vs_LDOA_disc_x);
      TF1 *fitupper = new TF1("fitupper","pol1",TID.VDDA_vs_LDOA_disc_x,20);
      TGraph *g = new TGraph(data.x.size(),&(data.x[0]),&(data.y[0]));
      g->Fit(fitlower,"QRN");
      g->Fit(fitupper,"QRN");
      double xint = (fitupper->GetParameter(0)-fitlower->GetParameter(0))/(fitlower->GetParameter(1)-fitupper->GetParameter(1));
      double yint = (fitlower->GetParameter(0)*fitupper->GetParameter(1)-fitlower->GetParameter(1)*fitupper->GetParameter(0))/(fitupper->GetParameter(1)-fitlower->GetParameter(1));
      if(xint<12 && xint>0 && yint<2 && yint>1)
	{
	  TID.VDDA_vs_LDOA_disc_x = xint;
	  TID.VDDA_vs_LDOA_disc_y = yint;
	}
    }
  
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  TID.marker_xcoord = data.marker_xcoord;
  TID.marker_ycoord = data.marker_ycoord;
  TID.init_check = data.init_check;	      
  return TID;
}

TID_Data VDDD_vs_LDOD(TString graphName, TString padName, TString fileName, Data data)
{
  TID_Data TID;
  double y1,y2,y3,y4,y5;
  for(int n{0}; n<data.x.size()-4; ++n)
    {
      y1 = data.y[n];
      y2 = data.y[n+1];
      y3 = data.y[n+2];
      y4 = data.y[n+3];
      y5 = data.y[n+4];
      //std::cout<<n<<"\t"<<y1<<"\t"<<y2<<"\t"<<y3<<"\t"<<y4<<"\t"<<y5<<std::endl;
      float tol{0.01};
      if(y5<y4<y3<y2<y1 && abs(y5-y4) > tol && abs(y4-y3) > tol && abs(y3-y2) > tol && abs(y2-y1) > tol)
	{
	  //std::cout<<graphName+" "+padName+" VDDD vs LDOD discontinuity " /*<< fileName*/ << " = " <<data.x[n]<<std::endl;
	  TID.VDDD_vs_LDOD_disc_x = data.x[n];
	  TID.VDDD_vs_LDOD_disc_y = data.y[n];
	  n=data.x.size()-4;
	}
    }

  if(data.init_check == true && (padName == "pad_plot_1" || padName == "pad_plot_2"))
    {
      TF1 *fitlower = new TF1("fitlower","pol1",0,TID.VDDD_vs_LDOD_disc_x);
      TF1 *fitupper = new TF1("fitupper","pol1",TID.VDDD_vs_LDOD_disc_x,20);
      TGraph *g = new TGraph(data.x.size(),&(data.x[0]),&(data.y[0]));
      g->Fit(fitlower,"QRN");
      g->Fit(fitupper,"QRN");
      double xint = (fitupper->GetParameter(0)-fitlower->GetParameter(0))/(fitlower->GetParameter(1)-fitupper->GetParameter(1));
      double yint = (fitlower->GetParameter(0)*fitupper->GetParameter(1)-fitlower->GetParameter(1)*fitupper->GetParameter(0))/(fitupper->GetParameter(1)-fitlower->GetParameter(1));
      if(xint<12 && xint>0 && yint<2 && yint>1)
	{
	  TID.VDDD_vs_LDOD_disc_x = xint;
	  TID.VDDD_vs_LDOD_disc_y = yint;
	}
    }
  
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  TID.marker_xcoord = data.marker_xcoord;
  TID.marker_ycoord = data.marker_ycoord;
  TID.init_check = data.init_check;	      
  return TID;
}

TID_Data TRDAC(Data data)
  {
    TID_Data TID;
    TID.timeStamp = data.timeStamp;
    TID.MRad = data.MRad;
    TID.redfitp0 = data.redfitp0;
    TID.redfitp1 = data.redfitp1;
    TID.init_check = data.init_check;
    return TID;
  }

TID_Data VRef(Data data)
  {
    TID_Data TID;
    TID.timeStamp = data.timeStamp;
    TID.MRad = data.MRad;
    TID.redfitp0 = data.redfitp0;
    TID.redfitp1 = data.redfitp1;
    TID.init_check = data.init_check;
    TID.marker_xcoord = data.marker_xcoord;
    TID.marker_ycoord = data.marker_ycoord;    
    return TID;
  }

TID_Data Functions(TString graphName, TString padName, TString fileName, Data data, int function)
{
  TID_Data TID;
  switch(function)
    {
    case 0: TID = VDOA_vs_LDOA(graphName, padName, fileName, data); break;
    case 1: TID = VDDD_vs_LDOD(graphName,padName, fileName, data); break;
    case 2: TID = TRDAC(data); break;
    case 3: TID = VRef(data); break;
    }

  return TID;
}
