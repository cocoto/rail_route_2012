#ifndef HEURE_H
#define HEURE_H
#include <ostream>
class Heure{
 private :
   int minutes;
public:
  //Constructeurs
 Heure();
 Heure(const int &h,const int &m);
 Heure(const int &m);
 Heure(const int &h,const int &m, const int &d);
 
 //Opérateur constants
 Heure operator+(const Heure &b) const;
 Heure operator-(const Heure &b) const;
 Heure operator+(const int &m) const;
 Heure operator-(const int &m) const;
 Heure& operator+=(const Heure &b);
 Heure& operator-=(const Heure &b);
 Heure& operator+=(const int &m);
 Heure& operator-=(const int &m);
 
 //Opérateurs de comparaison
 bool operator==(const Heure&b)const;
  bool operator<(const Heure&b)const;
  bool operator>(const Heure&b)const;
  bool operator<=(const Heure&b)const;
  bool operator>=(const Heure&b)const;
  bool operator!=(const Heure&b)const;
 
 //Accesseurs
 int jour() const;
 int heure()const;
 int minute()const;
 int value()const;
 void set(const int &h, const int &m);
};
#endif//HEURE_H
std::ostream& operator<<(std::ostream &flux, const Heure &heure);