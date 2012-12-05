#ifndef _LIGNE_BDD_H
#define _LIGNE_BDD_H
#include "Heure.hpp"
#include <iostream>
class Ligne_Bdd{
private:
  std::string _gare_depart, _gare_arrivee;
  Heure _h_depart, _h_arrivee;
  int _prix;
  bool _pieton;
public:
  std::string gare_depart() const;
  std::string gare_arrivee() const;
  Heure h_depart() const;
  Heure h_arrivee() const;
  int prix() const;
  Ligne_Bdd(const std::string &gare_depart, const std::string &gare_arrivee, const Heure &h_depart, const Heure &h_arrivee, const int &prix);
  Ligne_Bdd();
  void h_depart(const Heure &h);
  void h_arrivee(const Heure &h);
  void prix(const int &p);
  void gare_arrivee(const std::string &gare);
  void gare_depart(const std::string gare);
  bool disponible(const std::string &gare, const Heure &h) const;
  bool est_pieton()const;
  void est_pieton(const bool &res);
};



#endif