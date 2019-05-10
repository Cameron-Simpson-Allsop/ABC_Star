#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "TID_Data.hpp"

TID_Data EXT_VDOAvsLDOA_VDDDvsLDOD(Data data)
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

TID_Data EXT_TRDAC_CALLINE_THDAC(Data data)
{
  TID_Data TID;
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  TID.redfitp0 = data.redfitp0;
  TID.redfitp1 = data.redfitp1;;
  TID.init_check = data.init_check;
  return TID;
}

TID_Data EXT_Ref_R8B_COM(Data data)
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

TID_Data EXT_VTHTEST(Data data)
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

TID_Data EXT_VCD_DRIVE_VB(Data data)
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

TID_Data INT_VDDAvsLDOA_VDDDvsLDOD(Data data, TString fileName)
{
  TID_Data TID;
  TID.fileName = fileName;
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  double y1,y2,y3,y4,y5;
  for(int n{0}; n<data.x.size()-4; ++n)
    {
      y1 = data.y[n];
      y2 = data.y[n+1];
      y3 = data.y[n+2];
      y4 = data.y[n+3];
      y5 = data.y[n+4];
      float tol{10.};
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
      if(TID.disc_x < 20. && TID.disc_x > 0.000001 && TID.disc_y <5000. && TID.disc_y > 1000. )
	{
	  g->Fit(fitlower,"QRN");
	  g->Fit(fitupper,"QRN");
	}
      else
	{
	  data.init_check = false;
	}
      double xint = (fitupper->GetParameter(0)-fitlower->GetParameter(0))/(fitlower->GetParameter(1)-fitupper->GetParameter(1));
      double yint = (fitlower->GetParameter(0)*fitupper->GetParameter(1)-fitlower->GetParameter(1)*fitupper->GetParameter(0))/(fitupper->GetParameter(1)-fitlower->GetParameter(1));
      if(xint<20. && xint>0. && yint<5000. && yint>0.)
  	{
  	  TID.disc_x = xint;
  	  TID.disc_y = yint;
  	}
    }
  TID.init_check = data.init_check;
  return TID;
}

TID_Data INT_TRDAC_VRef(Data data, TString fileName)
{
  TID_Data TID;
  TID.fileName = fileName;
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  TGraph *g = new TGraph(data.x.size(),&(data.x[0]),&(data.y[0]));
  TF1 *fit = new TF1("fit","pol1",0,40);
  g->Fit(fit,"QRN");
  TID.redfitp0 = fit->GetParameter(0);
  TID.redfitp1 = fit->GetParameter(1);
  if(TID.redfitp0<100 || TID.redfitp1<3){TID.init_check = false;}
  else TID.init_check = data.init_check;
  // if(TID.init_check == false)
  //   {
  //     std::cout<<TID.redfitp0<<"\t"<<TID.redfitp1<<"\t"<<TID.init_check<<"\t"<<TID.timeStamp<<"\t"<<TID.MRad<<std::endl;
  //   }
  return TID;
}

TID_Data Functions(Data data, int function, std::string EXTINT, TString fileName)
{
  TID_Data TID;
  if(EXTINT == "EXT")
    {
      switch(function)
	{
	case 0: TID = EXT_VDOAvsLDOA_VDDDvsLDOD(data); break;
	case 1: TID = EXT_VDOAvsLDOA_VDDDvsLDOD(data); break;
	case 2: TID = EXT_TRDAC_CALLINE_THDAC(data); break;
	case 3: TID = EXT_Ref_R8B_COM(data); break;
	case 4: TID = EXT_Ref_R8B_COM(data); break;
	case 5: TID = EXT_Ref_R8B_COM(data); break;
	case 6: TID = EXT_VCD_DRIVE_VB(data); break;
	case 7: TID = EXT_TRDAC_CALLINE_THDAC(data); break;
	case 8: TID = EXT_TRDAC_CALLINE_THDAC(data); break;
	case 9: TID = EXT_VTHTEST(data); break;
	case 10: TID = EXT_Ref_R8B_COM(data); break;
	case 11: TID = EXT_VCD_DRIVE_VB(data); break;
	case 12: TID = EXT_VCD_DRIVE_VB(data); break;
	}
    }
  else if(EXTINT == "INT")
    {
      switch(function)
	{
	case 0: TID = INT_VDDAvsLDOA_VDDDvsLDOD(data,fileName); break;
	case 1: TID = INT_VDDAvsLDOA_VDDDvsLDOD(data,fileName); break;
	case 2: TID = INT_TRDAC_VRef(data,fileName); break;
	case 3: TID = INT_TRDAC_VRef(data,fileName); break;
	}
    }
  else std::cout<<"Invalid function input..."<<std::endl;
  
  return TID;
}
