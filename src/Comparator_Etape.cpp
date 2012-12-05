#include "Etape.hpp"
class Comparator_Etape{
public:
  int ratio;
  bool operator()(const Etape& etape1,const Etape &etape2)
  {
    return etape2.heure.value()*ratio+etape2.prix_total*(1-ratio)<etape1.heure.value()*ratio+etape1.prix_total*(1-ratio);
  }
  Comparator_Etape(const int &i)
  {
    ratio=i;
  }
}