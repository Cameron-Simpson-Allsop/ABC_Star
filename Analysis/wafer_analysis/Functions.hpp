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
  
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  TID.marker_xcoord_VDDA = data.marker_xcoord;
  TID.marker_ycoord_VDDA = data.marker_ycoord;
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
  
  TID.timeStamp = data.timeStamp;
  TID.MRad = data.MRad;
  TID.marker_xcoord_VDDD = data.marker_xcoord;
  TID.marker_ycoord_VDDD = data.marker_ycoord;
  TID.init_check = data.init_check;	      
  return TID;
}

TID_Data TRDAC(Data data)
  {
    TID_Data TID;
    TID.timeStamp = data.timeStamp;
    TID.MRad = data.MRad;
    TID.TRDACfitp0 = data.TRDACfitp0;
    TID.TRDACfitp1 = data.TRDACfitp1;
    TID.init_check = data.init_check;
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
    }

  return TID;
}
