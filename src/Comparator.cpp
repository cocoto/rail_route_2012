#include "Comparator.hpp"
  bool Comparator::operator()(const Etape &etape1, const Etape &etape2) const
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
  
  Comparator::Comparator(const float &i)
  {
    ratio=i;
  }