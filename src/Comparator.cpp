#include "Comparator.hpp"
  Comparator::Comparator(const int &type):type_of_comparison(type){ }
  Comparator::Comparator():type_of_comparison(1){}
  bool Comparator::operator()(const Etape &etape1, const Etape &etape2) const
  {
    (void)etape1;(void)etape2;
    if(type_of_comparison==1)
    {
      return false;
    }
    else if(type_of_comparison==2)
    {
      return false;
    }
    else if(type_of_comparison==3)
    {
      return false;
    }
    else
    {
      return true;
    }
  }