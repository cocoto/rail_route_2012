#ifndef _BDD_H
#define _BDD_H
#include "Ligne_bdd.hpp"
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <set>
class Bdd: public std::multimap< std::string,Ligne_Bdd > {
private:
  std::set<std::string> _gare_list;
public:
  Bdd(const std::string &filename1, const std::string &filename2);
  Bdd();
  std::list<Ligne_Bdd*> get_disponibles(const std::string &gare, const Heure &heure, const bool &multiday);
  void load_gares_file(const std::string &);
  void load_routes_file(const std::string &);
  std::set<std::string> gare_list() const;
  void effacer();
};

#endif