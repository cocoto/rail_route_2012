#ifndef _H_GTK_MAIN_
#define _H_GTK_MAIN_
#include "Bdd.hpp"
#include "gtk_Fenetre.hpp"
#include "Solver.hpp"
class Gtk_main_gui
{
private:
  Bdd *_bdd;
  Fenetre *_fenetre;
public:
  Gtk_main_gui(Bdd *bdd, Fenetre *fenetre);
  void load_file(std::string file);
  void load_file_ville(std::string file);
  void clear_problem();
  void rechercher();
};

#endif