#include<iostream>
#include "Solver.hpp"



int main(int argc, char** argv)
{
  (void)argc;
  std::string fichier_trajets(argv[1]), fichier_gares(argv[2]);
  Bdd bdd(fichier_trajets,fichier_gares);
  std::cout<<"scan terminé\n";
  std::set<Etape, Comparator_Etape> resultat=Calcul_trajet("Paris Montparnasse","Marseille SaintCharles",Heure(8,0),0.999,bdd);
  std::cout<<resultat.size()<<" trajets ont étés trouvés :\n";
  
  std::list<Ligne_Bdd*>::const_iterator it;
  std::set<Etape, Comparator_Etape>::reverse_iterator rit=resultat.rbegin();
  while(rit!=resultat.rend())
  {
    //Affichage de la solution
    std::cout<<"=================================\nHeure d'arrivée : "<<(*rit).heure<<" coût : "<<(*rit).prix_total<<"\n-------------\n";
    it=((*rit).trajets_effectues.begin());
    while(it!=(*rit).trajets_effectues.end())
    {
      if((*it)->est_pieton())
      {
	std::cout<<"Se rendre à pied à "<<(*it)->gare_arrivee()<<" (env."<<(*it)->h_arrivee().value()<<" minutes)\n";
      }
      else
      {
	std::cout<<"Prendre le train de "<<(*it)->h_depart()<<" en direction de "<<(*it)->gare_arrivee()<<" (arrivée à "<<(*it)-> h_arrivee()<<")\n";
      }
      it++;
    }
    std::cout<<"=================================\n";
    
    rit++;
  }
    return 0;
}
