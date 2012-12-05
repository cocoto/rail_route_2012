#ifndef _H_COMPARATOR
#define _H_COMPARATOR
#include <iostream>
#include "Bdd.hpp"
#include "Etape.hpp"
class Comparator{
private:
  int type_of_comparison;
public:
  Comparator(const int &type);
  Comparator();
  bool operator()(const Etape &etape1, const Etape &etape2) const;
  
  
  
};

#endif