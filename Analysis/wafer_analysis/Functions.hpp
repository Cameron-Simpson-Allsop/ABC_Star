#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "TID_Data.hpp"

TID_Data VDOAvsLDOA_VDDDvsLDOD(Data data)
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
      float tol{0.01};
      if(y5<y4<y3<y2<y1 && abs(y5-y4) > tol && abs(y4-y3) > tol && abs(y3-y2) > tol && abs(y2-y1) > tol)
	{
	  TID.disc_x = data.x[n];
	  TID.disc_y = data.y[n];
	  n=data.x.size()-4;
	}
    }
  if(data.init_check == true)
    {
      TF1 *fitlower = new TF1("fitlower","pol1",0,TID.disc_x);
      TF1 *fitupper = new TF1("fitupper","pol1",TID.disc_x,20);
      TGraph *g = new TGraph(data.x.size(),&(data.x[0]),&(data.y[0]));
      g->Fit(fitlower,"QRN");
      g->Fit(fitupper,"QRN");
      double xint = (fitupper->GetParameter(0)-fitlower->GetParameter(0))/(fitlower->GetParameter(1)-fitupper->GetParameter(1));
      double yint = (fitlower->GetParameter(0)*fitupper->GetParameter(1)-fitlower->GetParameter(1)*fitupper->GetParameter(0))/(fitupper->GetParameter(1)-fitlower->GetParameter(1));
      if(xint<12 && xint>0 && yint<2 && yint>1)
	{
	  TID.disc_x = xint;
	  TID.disc_y = yint;
	}
    }
  
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  TID.marker_xcoord = data.marker_xcoord;
  TID.marker_ycoord = data.marker_ycoord;
  TID.init_check = data.init_check;	      
  return TID;
}

TID_Data TRDAC_CALLINE_THDAC(Data data)
{
  TID_Data TID;
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  TID.redfitp0 = data.redfitp0;
  TID.redfitp1 = data.redfitp1;;
  TID.init_check = data.init_check;
  return TID;
}

TID_Data Ref_R8B_COM(Data data)
{
  TID_Data TID;
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  TID.redfitp0 = data.redfitp0;
  TID.redfitp1 = data.redfitp1;;
  TID.init_check = data.init_check;
  TID.marker_xcoord = data.marker_xcoord;
  TID.marker_ycoord = data.marker_ycoord;    
  return TID;
}

TID_Data VTHTEST(Data data)
{
  TID_Data TID;
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  TGraph *g = new TGraph(data.x.size(),&(data.x[0]),&(data.y[0]));
  TF1 *fit = new TF1("fit","pol3",0,500);
  g->Fit(fit,"QRN");
  TID.redfitp0 = fit->GetParameter(0);
  TID.redfitp1 = fit->GetParameter(1);
  TID.redfitp2 = fit->GetParameter(2);
  TID.redfitp3 = fit->GetParameter(3);  
  TID.init_check = data.init_check;
  return TID;
}

TID_Data VCD_DRIVE(Data data)
{
  TID_Data TID;
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  TGraph *g = new TGraph(data.x.size(),&(data.x[0]),&(data.y[0]));
  TF1 *fit = new TF1("fit","pol3",0,10);
  g->Fit(fit,"QRN");
  TID.redfitp0 = fit->GetParameter(0);
  TID.redfitp1 = fit->GetParameter(1);
  TID.redfitp2 = fit->GetParameter(2);
  TID.redfitp3 = fit->GetParameter(3);
  TID.init_check = data.init_check;
  return TID;
}

TID_Data Functions(TString graphName, TString padName, TString fileName, Data data, int function)
{
  TID_Data TID;
  switch(function)
    {
    case 0: TID = VDOAvsLDOA_VDDDvsLDOD(data); break;
    case 1: TID = VDOAvsLDOA_VDDDvsLDOD(data); break;
    case 2: TID = TRDAC_CALLINE_THDAC(data); break;
    case 3: TID = Ref_R8B_COM(data); break;
    case 4: TID = Ref_R8B_COM(data); break;
    case 5: TID = Ref_R8B_COM(data); break;
    case 6: TID = VCD_DRIVE(data); break;
    case 7: TID = TRDAC_CALLINE_THDAC(data); break;
    case 8: TID = TRDAC_CALLINE_THDAC(data); break;
    case 9: TID = VTHTEST(data); break;
    case 10: TID = Ref_R8B_COM(data); break;
    case 11: TID = VCD_DRIVE(data); break;
    }

  return TID;
}
