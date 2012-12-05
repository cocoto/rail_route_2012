#include "gtk_Fenetre.hpp"
#include <gtkmm/label.h>
#include <gtkmm/expander.h>
Fenetre::Fenetre(): Gtk::Window(),_ouvrir_instance(Gtk::Stock::OPEN),_ouvrir_villes(Gtk::Stock::OPEN),_reset_probleme(Gtk::Stock::DELETE),_frame_recherche("Recherche"),_frame_resultats("Résultats"),_boite_recherche(5,3,false),_heure_depart(true),_minute_depart(true),_rapport(1,99,0.01),_gare_depart("Gare de Départ"),_gare_arrivee("Gare d'Arrivée"),_label_hdepart("Heure de départ"),_label_coeff("Trier les résultats par "),_label_prix("Prix"), _label_temps("Heure d'arrivée"),_box_scale(false),_bouton_recherche("Rechercher"){
    int i;
    std::ostringstream oss;
    set_title("Rail route 2012");
    set_icon_from_file("images/picto_train.gif");
    resize(640, 480);
    set_position(Gtk::WIN_POS_CENTER);    
    
    _ouvrir_instance.set_tooltip_text("Charger une instance de trains");
    _ouvrir_villes.set_tooltip_text("Charger la liste des trajets piétons");
    _reset_probleme.set_tooltip_text("Supprimer l'instance actuelle");
    _toolbar.append(_ouvrir_instance);
    _toolbar.append(_ouvrir_villes);
    _toolbar.append(_reset_probleme);
    
    _frame_resultats.add(_barresDeDefilement_resultat);
    _barresDeDefilement_resultat.add(_box_resultats);
    _box_resultats.pack_start(_label_resultat);
    
    _boitev.pack_start(_toolbar,Gtk::PACK_SHRINK);
    _boitev.pack_start(_frame_recherche,Gtk::PACK_SHRINK);
    _boitev.pack_start(_frame_resultats);
    
    _frame_recherche.add(_boite_recherche);
    _boite_recherche.attach(_gare_depart,0,1,0,1);
    _boite_recherche.attach(_gare_arrivee,0,1,1,2);
    _boite_recherche.attach(_liste_gare_depart,1,3,0,1);
    _boite_recherche.attach(_liste_gare_arrivee,1,3,1,2);
     
     _boite_recherche.attach(_heure_depart,1,2,2,3);
     _boite_recherche.attach(_minute_depart,2,3,2,3);
     _boite_recherche.attach(_label_hdepart,0,1,2,3);
     
     //_boite_recherche.attach(_rapport,1,3,3,4);
     _box_scale.pack_start(_label_prix,false,false,0);
     _box_scale.pack_start(_rapport);
     _box_scale.pack_start(_label_temps,false,false,0);
     _boite_recherche.attach(_box_scale,1,3,3,4);
     _boite_recherche.attach(_label_coeff,0,1,3,4);
     _boite_recherche.attach(_bouton_recherche,2,3,4,5);
    _rapport.set_draw_value(false);
    for(i=0;i<=23;i++)
    {
      if(i<10)oss<<"0";
      oss<<i;
      _heure_depart.append(oss.str());
      oss.str("");
    }
    for(i=0;i<=59;i++)
    {
      if(i<10)oss<<"0";
      oss<<i;
      _minute_depart.append(oss.str());
      oss.str("");
    }
    _heure_depart.set_active_text("00");
    _minute_depart.set_active_text("00");
    _ouvrir_instance.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::ouvrir_fichier));
    _ouvrir_villes.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::ouvrir_fichier_ville));
    _reset_probleme.signal_clicked().connect(sigc::mem_fun(*this,&Fenetre::clear_instances));
    _bouton_recherche.signal_clicked().connect(sigc::mem_fun(*this,&Fenetre::rechercher));
    add(_boitev);
    show_all();
}

void Fenetre::ouvrir_fichier()
{
  Gtk::FileChooserDialog dialogue("Ouverture d'un fichier");
  //dialogue.set_current_folder(Glib::get_home_dir());
  dialogue.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialogue.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
  dialogue.run();
  _signal_file_selected.emit(dialogue.get_filename());
}
void Fenetre::ouvrir_fichier_ville()
{
  Gtk::FileChooserDialog dialogue("Ouverture d'un fichier");
  //dialogue.set_current_folder(Glib::get_home_dir());
  dialogue.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialogue.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
  dialogue.run();
  _signal_file_ville_selected.emit(dialogue.get_filename());
}
sigc::signal<void,std::string> Fenetre::signal_file_selected(){
  return _signal_file_selected;
}
sigc::signal<void,std::string> Fenetre::signal_file_ville_selected(){
  return _signal_file_ville_selected;
}
sigc::signal<void> Fenetre::signal_clear_instances(){
  return _signal_clear_instances;
}
sigc::signal<void,std::string,std::string,int,int,float> Fenetre::signal_rechercher(){
  return _signal_rechercher;
}
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
void Fenetre::set_resultats(const std::string &res)
{
  _label_resultat.set_label(res);
}

  void Fenetre::vider_ville()
  {
    _liste_gare_arrivee.remove_all();
    _liste_gare_depart.remove_all();
    _label_resultat.set_label("");
  }
  void Fenetre::clear_instances()
  {
    _signal_clear_instances.emit();
  }
  void Fenetre::rechercher()
  {
    _signal_rechercher.emit(_liste_gare_depart.get_active_text(),_liste_gare_arrivee.get_active_text(),atoi(_heure_depart.get_active_text().c_str()),atoi(_minute_depart.get_active_text().c_str()),_rapport.get_value()/100);
  }