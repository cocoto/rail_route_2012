#include<iostream>
#include "Solver.hpp"



int main(int argc, char** argv)
{
  (void)argc;
  std::string fichier_trajets(argv[1]), fichier_gares(argv[2]);
  Bdd bdd(fichier_trajets,fichier_gares);
  std::cout<<"scan terminé\n";

  std::string depart, destination;
  std::set<std::string> list_gare=bdd.gare_list();
  std::set<std::string>::iterator it_gare;
  it_gare=list_gare.begin();
  int cpt=1;
  int i,num,h_dep,jour_dep,h_arr,jour_arr,type_trajet,classe;
  float preference;

  while(it_gare!=list_gare.end())
  {
    std::cout<<cpt<<". "<<*it_gare<<"\n";
    it_gare++;
    cpt++;
  }

  do
  {
     std::cout<<"\n";
     std::cout<<"Quelle est votre gare de départ?\n";
     std::cin>>num;

      if(num<1 || num>=cpt)
      {
         std::cout<<"Choix non valide.\n";
      }
  }while(num<1 || num>=cpt);

  it_gare=list_gare.begin();
  for(i=1;i<num;i++)
  {
      it_gare++;
  }

  depart=*it_gare;
  cpt=1;

    list_gare.erase(depart);

  it_gare=list_gare.begin();


  while(it_gare!=list_gare.end())
  {
    std::cout<<cpt<<". "<<*it_gare<<"\n";
    cpt++;
    it_gare++;
  }
    std::cout<<"\n";

  do
  {
     std::cout<<"\n";
     std::cout<<"Quelle est votre destination?\n";
     std::cin>>num;
      if(num<1 || num>=cpt)
      {
         std::cout<<"Choix non valide.\n";
      }
  }while(num<1 || num>=cpt);

  it_gare=list_gare.begin();
  for(i=1;i<num;i++)
  {
      if(*it_gare!=depart)
      {
          it_gare++;
      }
  }
  destination=*it_gare;

    do
    {
       std::cout<<"\n";
       std::cout<<"1. Aller simple\n";
       std::cout<<"2. Aller-retour\n";
       std::cin>>type_trajet;
        if(type_trajet!=1 && type_trajet!=2)
        {
           std::cout<<"Choix non valide.\n";
        }
    }while(type_trajet!=1 && type_trajet!=2);

    do
    {
       std::cout<<"\n"<<"Quel jour souhaitez-vous partir? (nous sommes le jour 0)\n";
       std::cin>>jour_dep;
        if(jour_dep<0 || jour_dep>31)
        {
           std::cout<<"Erreur : choisissez un jour entre 0 et 100\n";
        }
    }while(jour_dep<0 || jour_dep>31);


    do
    {
       std::cout<<"\n";
       std::cout<<"A partir de quelle heure souhaitez-vous partir?\n";
       std::cin>>h_dep;
        if(h_dep<0 || h_dep>=24)
        {
           std::cout<<"Erreur : choisissez une heure entre 0 et 23 \n";
        }
    }while(h_dep<0 || h_dep>=24);

    if(type_trajet==2)
    {
        do
        {
           std::cout<<"\n"<<"Quel jour souhaitez-vous revenir? (nous sommes le jour 0)\n";
           std::cin>>jour_arr;
            if(jour_arr<0 || jour_arr>100 || jour_arr<jour_dep)
            {
               std::cout<<"Erreur : choisissez un jour entre 0 et 100 à partir du jour "<<jour_dep<<" (jour de départ)\n";
            }
        }while(jour_arr<0 || jour_arr>100 || jour_arr<jour_dep);


        do
        {
           std::cout<<"\n";
           std::cout<<"A partir de quelle heure souhaitez-vous revenir?\n";
           std::cin>>h_arr;
            if(h_arr<0 || h_arr>=24)
            {
               std::cout<<"Erreur : choisissez une heure entre 0 et 23 \n";
            }
        }while(h_arr<0 || h_arr>=24);
    }

    do
    {
       std::cout<<"Souhaitez-vous privilégier le temps de trajet ou le prix du trajet?\n";
       std::cout<<"1. Le temps\n";
       std::cout<<"2. Le prix\n";
       std::cout<<"3. Mixte des deux\n";
       std::cin>>preference;
        if(preference!=1 && preference!=2 && preference!=3)
        {
           std::cout<<"Choix non valide : indiquez un chiffre entre 1 et 3\n";
        }
    }while(preference!=1 && preference!=2 && preference!=3);
    if(preference==1)
    {
        preference=0.99999999;
    }
    else
    if(preference==2)
    {
        preference=0.0000001;
    }
    else
    if(preference==3)
    {
        preference=0.5;
    }

    std::cout<<"Préférez-vous voyager en 1ère ou en 2nd classe? (1 ou 2)\n";
    do
    {
        std::cin>>classe;
        if(classe!=1 && classe!=2)
        {
            std::cout<<"Erreur : entrez 1 pour la 1ère classe ou 2 pour la 2nd.\n";
        }
    }while(classe!=1 && classe!=2);


    if(type_trajet==1)
    {
        std::cout<<"Récapitulatif :\n "<<"Vous souhaitez vous rendre à "<<destination<<" en partant de "<<depart<<" à partir de "<<h_dep<<"h00 le "<<jour_dep<<"\n";

        std::set<Etape, Comparator_Etape> resultat=Calcul_trajet(depart,destination,Heure(h_dep,0,jour_dep),preference,bdd,false,Heure(0),classe);
        std::cout<<resultat.size()<<"trajets ont été trouvés :\n";

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

    }
    else
    {

        std::cout<<"Récapitulatif :\n"<<"Vous souhaitez vous rendre à "<<destination<<" en partant de "<<depart<<" à partir de "<<h_dep<<"h00 le "<<jour_dep;
        std::cout<<" et revenir à "<<depart<<" le "<<jour_arr<<" à partir de "<<h_arr<<"h00\n\n";


        std::set<Etape, Comparator_Etape> resultat=Calcul_trajet(depart,destination,Heure(h_dep,0,jour_dep),preference,bdd,true,Heure(h_arr,0,jour_arr),classe);
        std::cout<<resultat.size()<<" trajets ont été trouvés :\n";

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

    }

    return 0;
}
