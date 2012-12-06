#ifndef _BDD_H
#define _BDD_H
#include "Ligne_bdd.hpp"
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <set>

/*
 * Classe de stockage de trajets journaliers de trains
 * Chaque feuille est décomposée en différents trajets
 * Implémentée sous la forme d'une MULTImap dont les clés correspondent aux villes de départ
 */
class Bdd: public std::multimap< std::string,Ligne_Bdd > {
private:
  std::set<std::string> _gare_list; //Liste des gares du problème
public:
  
  Bdd(const std::string &filename1, const std::string &filename2);
  Bdd();
  
  //Fonction retournant la liste des trajets disponibles à partir d'une gare [et d'une heure (lorque multiday=false)]
  std::list<Ligne_Bdd*> get_disponibles(const std::string &gare, const Heure &heure, const bool &multiday);
  
  //Fonction de chargement de fichierS dans la base
  void load_gares_file(const std::string &);
  void load_routes_file(const std::string &);
  
  //Accesseurs
  std::set<std::string> gare_list() const;
  void effacer();
};

#endif