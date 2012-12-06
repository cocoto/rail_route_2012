#include "Comparator_Etape.hpp"
/*
 * Opérateur permettant de comparer la qualité de deux solution selon le critère de l'utilisateur (temps, coût)
 */
bool Comparator_Etape::operator()(const Etape& etape1,const Etape &etape2)
  {
    //On affecte un coefficient x{0..1} pour l'heure d'arrivée, et un coefficient y=1-x pour le cout
    float res=(float)etape2.heure.value()*ratio+(float)etape2.prix_total*(1.0-ratio)-(float)etape1.heure.value()*ratio-(float)etape1.prix_total*(1-ratio);
    //Si les deux trajets sont aussi interessants
    if(res==0)
    {
      //On les différencie par leur adresse mémoire (pour obtenir une comparaison totale)
      return etape1.trajets_effectues<etape2.trajets_effectues;
    }
    else
    {
      return res<0;
    }
  }
  
  /*
   * Constructeur de la classe
   */
  Comparator_Etape::Comparator_Etape(const float &i)
  {
    ratio=i;
  }