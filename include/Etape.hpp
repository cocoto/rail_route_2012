#ifndef _H_ETAPE
#define _H_ETAPE
#include <iostream>
#include <set>
#include "Ligne_bdd.hpp"
class Etape{
public:
  Heure heure;
  std::string ville;
  std::list<Ligne_Bdd*> trajets_effectues;
  std::set<std::string> gares_traverses;
  float prix_total;  
};

#endif