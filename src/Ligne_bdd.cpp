#include "Ligne_bdd.hpp"
  Ligne_Bdd::Ligne_Bdd(const std::string &gare_depart, const std::string &gare_arrivee, const Heure &h_depart, const Heure &h_arrivee, const int &prix):_gare_depart(gare_depart),_gare_arrivee(gare_arrivee),_h_depart(h_depart),_h_arrivee(h_arrivee),_prix(prix),_pieton(false){}
  
  std::string Ligne_Bdd::gare_depart() const{
    return _gare_depart;
  }
  std::string Ligne_Bdd::gare_arrivee() const
  {
    return _gare_arrivee;
  }
  Heure Ligne_Bdd::h_depart() const{
    return _h_depart;
  }
  Heure Ligne_Bdd::h_arrivee() const
  {
    return _h_arrivee;
  }
  int Ligne_Bdd::prix() const
  {
    return _prix;
  }
  
  void Ligne_Bdd::h_depart(const Heure &h)
  {
    _h_depart=h;
  }
  void Ligne_Bdd::h_arrivee(const Heure &h)
  {
    _h_arrivee=h;
  }
  void Ligne_Bdd::prix(const int &p)
  {
    _prix=p;
  }
  void Ligne_Bdd::gare_arrivee(const std::string &gare)
  {
    _gare_arrivee=gare;
  }
  void Ligne_Bdd::gare_depart(const std::string gare)
  {
    _gare_depart=gare;
  }
  
  bool Ligne_Bdd::disponible(const std::string &gare, const Heure &h, const bool &multiday) const
  {
    if(!multiday)
    {
     return !(_gare_depart!=gare || h>_h_depart || (_pieton && h+_h_arrivee<h)); 
    }
    else
    {
      return !(_gare_depart!=gare);
    }
  }
  
  Ligne_Bdd::Ligne_Bdd():_pieton(false){}
  
  bool Ligne_Bdd::est_pieton()const
  {
    return _pieton;
  }
  void Ligne_Bdd::est_pieton(const bool &res)
  {
    _pieton=res;
  }