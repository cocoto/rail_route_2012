#include "Etape.hpp"
class Comparator_Etape{
public:
 float ratio;
  bool operator()(const Etape& etape1,const Etape &etape2)
  {
    float res=(float)etape2.heure.value()*ratio+(float)etape2.prix_total*(1.0-ratio)-(float)etape1.heure.value()*ratio-(float)etape1.prix_total*(1-ratio);
    if(res==0)
    {
      return etape1.trajets_effectues<etape2.trajets_effectues;
    }
    else
    {
      return res<0;
    }
  }
  Comparator_Etape(const float &i)
  {
    ratio=i;
  }
};