#include "Comparator_Etape.hpp"
bool Comparator_Etape::operator()(const Etape& etape1,const Etape &etape2)
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
  Comparator_Etape::Comparator_Etape(const float &i)
  {
    ratio=i;
  }