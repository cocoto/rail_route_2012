#ifndef _H_COMPARATOR
#define _H_COMPARATOR
#include "Etape.hpp"
#include <list>
class Comparator{
private:
  float ratio;
public:
  Comparator(const float &i);
  bool operator()(const Etape &etape1, const Etape &etape2) const; 
};

#endif