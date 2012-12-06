#include "gtk_Fenetre.hpp"
#include <gtkmm/label.h>
#include <gtkmm/expander.h>
Fenetre::Fenetre():
/*
 * Construction de la fenêtre de base (aucun constructeur)
 */
Gtk::Window(),_ouvrir_instance(Gtk::Stock::OPEN),_ouvrir_villes(Gtk::Stock::OPEN),_reset_probleme(Gtk::Stock::DELETE),_frame_recherche("Recherche"),_frame_resultats("Résultats"),_boite_recherche(4,2,false),_gare_depart("Gare de Départ"),_gare_arrivee("Gare d'Arrivée"),_prem_classe(_radio_groupe,"Première classe"),_sec_classe(_radio_groupe,"Seconde Classe"),_ajustement_heure_d(Gtk::Adjustment::create(8.0,0.0,23.0,1.0)),_ajustement_minute_d(Gtk::Adjustment::create(0.0,0.0,59.0,1.0)),_heure_depart(_ajustement_heure_d),_minute_depart(_ajustement_minute_d),_check_ar("Aller-Retour"),_ajustement_heure_a(Gtk::Adjustment::create(8.0,0.0,23.0,1.0)),_ajustement_minute_a(Gtk::Adjustment::create(0.0,0.0,59.0,1.0)),_heure_arrivee(_ajustement_heure_a),_minute_arrivee(_ajustement_minute_a),_box_scale(false),_rapport(1,99,0.01),_label_coeff("Trier les résultats par "),_label_prix("Prix"),_label_temps("Heure d'arrivée"),_bouton_recherche("Rechercher"){
  
    std::ostringstream oss;
    
    //Mise à jour de l'icone et du titre
    set_title("Rail route 2012");
    set_icon_from_file("images/picto_train.gif");
    resize(800, 600);
    set_position(Gtk::WIN_POS_CENTER);    
    
    /*
     * Ajout des boutons de la barre d'action
     */
    _ouvrir_instance.set_tooltip_text("Charger une instance de trains");
    _ouvrir_villes.set_tooltip_text("Charger la liste des trajets piétons");
    _reset_probleme.set_tooltip_text("Supprimer l'instance actuelle");
    _toolbar.append(_ouvrir_instance);
    _toolbar.append(_ouvrir_villes);
    _toolbar.append(_reset_probleme);
    
    /*
     * Ajout de la frame résultat
     */
    _frame_resultats.add(_barresDeDefilement_resultat);
    _barresDeDefilement_resultat.add(_box_resultats);
    _box_resultats.pack_start(_label_resultat);
    _panneau_principal.add2(_frame_resultats);
    
    /*
     * Constitution de la fenetre en ammont : une barre d'action et un paneau
     */
    _boitev.pack_start(_toolbar,Gtk::PACK_SHRINK);
    _boitev.pack_start(_panneau_principal);
    
    /*
     * Ajout du module de recherche
     * */
    _panneau_principal.add1(_frame_recherche);

    
    _frame_recherche.add(_boite_recherche);
    
    /*
     * Ajout des champs de selection des gares départ et arrivée
     */
    _boite_recherche.attach(_gare_depart,0,1,0,1);
    _boite_recherche.attach(_gare_arrivee,0,1,1,2);
    _boite_recherche.attach(_liste_gare_depart,1,2,0,1);
    _boite_recherche.attach(_liste_gare_arrivee,1,2,1,2);

    /*
     * Ajout des infos de départ
     */
    _boite_recherche.attach(_depart_box,0,1,2,3);
    //Selection de la classe
    _depart_box.pack_start(_radio_box);
    _radio_box.pack_start(_prem_classe);
    _radio_box.pack_start(_sec_classe);
    
    //Selection de la date et heure
    _depart_box.pack_start(_calendrier_depart);
    _depart_box.pack_start(_box_heure_depart);
    _box_heure_depart.pack_start(_heure_depart);
     _box_heure_depart.pack_start(_minute_depart);

     /*
      * Ajout des éléments de retour (aller_retour)
      */
    _boite_recherche.attach(_arrivee_box,1,2,2,3);
    _arrivee_box.pack_start(_check_ar);
    _check_ar.set_active(true);
    _arrivee_box.pack_start(_calendrier_arrivee);
    _arrivee_box.pack_start(_box_heure_arrivee);
    _box_heure_arrivee.pack_start(_heure_arrivee);
    _box_heure_arrivee.pack_start(_minute_arrivee);

    /*
     * Ajout de la selection du critère (slide)
     */
     _box_scale.pack_start(_label_prix,false,false,0);
     _box_scale.pack_start(_rapport);
      _box_scale.pack_start(_label_temps,false,false,0);
      _boite_recherche.attach(_box_scale,0,1,3,4);
      _boite_recherche.attach(_bouton_recherche,1,2,3,4);
     _rapport.set_draw_value(false);
 
     _boite_recherche.set_row_spacings(20);
     _boite_recherche.set_col_spacings(20);
     
     /*
      * Connection des signaux aux fonctions de la classe
      */
    _ouvrir_instance.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::ouvrir_fichier));
    _ouvrir_villes.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::ouvrir_fichier_ville));
    _reset_probleme.signal_clicked().connect(sigc::mem_fun(*this,&Fenetre::clear_instances));
    _bouton_recherche.signal_clicked().connect(sigc::mem_fun(*this,&Fenetre::rechercher));
    _check_ar.signal_toggled().connect(sigc::mem_fun(*this,&Fenetre::activer_retour));
    add(_boitev);
    show_all();
}

/*
 * Action répondant au clique sur le bouton "charger une instance"
 */
void Fenetre::ouvrir_fichier()
{
  Gtk::FileChooserDialog dialogue("Ouverture d'un fichier");
  //dialogue.set_current_folder(Glib::get_home_dir());
  dialogue.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialogue.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
  dialogue.run();
  _signal_file_selected.emit(dialogue.get_filename());
}

/*
 * Action répondant au clique sur le bouton "charger une liste de trajets piétons"
 */
void Fenetre::ouvrir_fichier_ville()
{
  Gtk::FileChooserDialog dialogue("Ouverture d'un fichier");
  dialogue.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialogue.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
  dialogue.run();
  _signal_file_ville_selected.emit(dialogue.get_filename());
}

/*Accesseurs des signaux externes
 */
sigc::signal<void,std::string> Fenetre::signal_file_selected(){
  return _signal_file_selected;
}
sigc::signal<void,std::string> Fenetre::signal_file_ville_selected(){
  return _signal_file_ville_selected;
}
sigc::signal<void> Fenetre::signal_clear_instances(){
  return _signal_clear_instances;
}
sigc::signal<void> Fenetre::signal_rechercher(){
  return _signal_rechercher;
}

/*
 * Fonction de remplissage de la liste des gares
 */
void Fenetre::set_gares(const std::set<std::string> &liste)
  {
    _liste_gare_arrivee.remove_all();
    _liste_gare_depart.remove_all();
    std::set<std::string>::iterator it=liste.begin();
    while(it!=liste.end())
    {
      _liste_gare_arrivee.append(*it);
      _liste_gare_depart.append(*it);
      it++;
    }
    _liste_gare_arrivee.set_active_text(*liste.begin());
    _liste_gare_depart.set_active_text(*liste.begin());
  }
  
  /*
   * Fonction d'affichage dans la fenetre des réusltats
   */
void Fenetre::set_resultats(const std::string &res)
{
  _label_resultat.set_label(res);
}

/*
 * Fonction de vidage de la liste des villes et de la fenêtre résultat
 * (vidage de la Bdd)
 */
  void Fenetre::vider_ville()
  {
    _liste_gare_arrivee.remove_all();
    _liste_gare_depart.remove_all();
    _label_resultat.set_label("");
  }
  
  /*
   * Fonction répondant au signal de clique sur la suppression de la bdd
   */
  void Fenetre::clear_instances()
  {
    _signal_clear_instances.emit();
  }
  
  /*
   * Fonction répondant au signal de clique sur le bouton recherche
   */
  void Fenetre::rechercher()
  {
    _signal_rechercher.emit();
  }
  
  /*
   * Fonction répondant au clique sur la checkbox (aller-retour)
   */
  void Fenetre::activer_retour()
  {
    if(!_check_ar.get_active())
    {
      _calendrier_arrivee.hide();
      _box_heure_arrivee.hide();
    }
    else
    {
      _calendrier_arrivee.show();
      _box_heure_arrivee.show();
    }
  }
  
  /*
   * Accesseurs d'informations sur la fenêtre
   */
  bool Fenetre::is_ar(){return _check_ar.get_active();}
  int Fenetre::travel_class(){
    if(_prem_classe.get_active())
    {
      return 1;
    }
    else if(_sec_classe.get_active())
    {
      return 2;
    }
    else return 2;
    
  }
  int Fenetre::day_d(){
    Glib::Date date;
    _calendrier_depart.get_date(date);
    return date.get_julian();
  }
  int Fenetre::day_a()
  {
    Glib::Date date;
    _calendrier_arrivee.get_date(date);
    return date.get_julian();
  }
  int Fenetre::h_d(){return _heure_depart.get_value();}
  int Fenetre::h_a(){return _heure_arrivee.get_value();}
  int Fenetre::m_a(){return _minute_arrivee.get_value();}
  int Fenetre::m_d(){return _minute_depart.get_value();}
  std::string Fenetre::gare_d(){return _liste_gare_depart.get_active_text();}
  std::string Fenetre::gare_a(){return _liste_gare_arrivee.get_active_text();}
  float Fenetre::rapport(){return _rapport.get_value()/100;}