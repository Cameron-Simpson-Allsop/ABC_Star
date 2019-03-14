#include <vector>

struct TID_Data
{
  double VDDA_vs_LDOA_disc_x;
  double VDDA_vs_LDOA_disc_y;
  double VDDD_vs_LDOD_disc_x;
  double VDDD_vs_LDOD_disc_y;
  double timeStamp;
  double MRad;
  double marker_xcoord;
  double marker_ycoord;

  bool init_check;
};
