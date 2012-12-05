#ifndef _H_COMPARATOR_ETAPE_
#define _H_COMPARATOR_ETAPE_
#include "Etape.hpp"
#include <list>
class Comparator_Etape{
private:
 float ratio;
public:
 bool operator()(const Etape& etape1,const Etape &etape2);
  Comparator_Etape(const float &i);
};
#endif