#include "Comparator.hpp"
/*
 * Opérateur de priorisation de traitement d'une étape par rapport à une autre
 * Dans l'implémentation actuelle on traite en priorité les étapes possédants les plus petites valeurs (selon le critère de l'utilisateur)
 * Cela s'apparente à un parcourt en "largeur" (type dijkstra)
 * Une meilleure méta-heuristique permettrait de rapidement trouver X bonnes solution pour rapidement élaguer les branches
 */
  bool Comparator::operator()(const Etape &etape1, const Etape &etape2) const
  {
    float res=(float)etape2.heure.value()*ratio+(float)etape2.prix_total*(1.0-ratio)-(float)etape1.heure.value()*ratio-(float)etape1.prix_total*(1-ratio);
    if(res==0)
    {
      return etape1.trajets_effectues<etape2.trajets_effectues;
    }
    else
    {
      return res<0;
    }
  }
  
  /*
   * Constructeur
   */
  Comparator::Comparator(const float &i)
  {
    ratio=i;
  }