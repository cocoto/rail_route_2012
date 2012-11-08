#ifndef HEURE_H
#define HEURE_H

class Heure{
 private :
   unsigned int minutes;
public:
  //Constructeurs
 Heure();
 Heure(const int &h,const int &m);
 Heure(const int &m);
 
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
 int heure()const;
 int minute()const;
 int value()const;
 int set(const int &h, const int &m);
};
#endif//HEURE_H