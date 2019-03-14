#include <vector>

struct TID_Data
{
  double VDDA_vs_LDOA_disc_x;
  double VDDA_vs_LDOA_disc_y;
  double VDDD_vs_LDOD_disc_x;
  double VDDD_vs_LDOD_disc_y;
  double timeStamp;
  double MRad;
  double marker_xcoord_VDDD;
  double marker_ycoord_VDDD;  
  double marker_xcoord_VDDA;
  double marker_ycoord_VDDA;
  double TRDACfitp0;
  double TRDACfitp1;

  bool init_check;
};
