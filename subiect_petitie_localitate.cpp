#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

/* Se consideră o aplicaţie pentru gestionarea petițiilor primite în cadrul unei localități. Definiți o clasă care
modelează o astfel de solicitare. Se vor urmări atribute specifice, precum: data depunerii, numele şi prenumele
solicitantului, categoria în care se încadrează petiția, descrierea solicitării etc.Datele membre sunt private şi
sunt puse la dispoziție metode de acces. Clasa conține cel puțin patru câmpuri, dintre care unul este alocat
dinamic, constructori, metodele specifice claselor cu membri alocați dinamic şi operatorul de afişare. Folosiţi
un membru static sau const.
(1p) Se va defini operatorul! pentru indica dacă o petiţie nu are răspuns şi a depăşit termenul legal (30 de
zile).
(1p) Se va defini operatorul - pentru schimba starea unei petiții (deschisă -> rezolvată).
(2p) Definiţi operatorii << şi >> pentru scrierea/citirea în/din fişiere text.
(2p) Specializați clasa definită şi exemplificatți conceptul de virtualizare.
(1p) Propuneţi un container STL care permite gruparea petiţiilor după categorii şi regăsirea cu uşurință a
acestorа.*/

class Petitie{
  private:
    string dataDepunerii;
    string numePrenume;
    string categorie;
    char *descriere;
    bool status;
    int zileDeLaDepunere;

    static int nrPetitii;
    static const int termen_legal = 30;

  public: 

  //constructorul fara parametrii

  Petitie(){
    this->dataDepunerii = "";
    this->numePrenume = "";
    this->categorie = "";
    this->descriere = nullptr;
    this->status = false;
    this->zileDeLaDepunere = 0;
  }

  //constructorul cu parametrii

   Petitie(string dataDepunerii, string numePrenume, string categorie, const char* descriere, bool status, int zileDeLaDepunere){
     this->dataDepunerii = dataDepunerii;
     this->numePrenume = numePrenume;
     this->categorie = categorie;
     
     if (descriere != nullptr){
       this->descriere = new char[strlen (descriere) + 1];
       strcpy_s(this->descriere, strlen(descriere) + 1, descriere);
     }else {
       this->descriere = nullptr;
     }

     this->status = status;
     this->zileDeLaDepunere = zileDeLaDepunere;
   }

   //constructorul de copiere
   Petitie(const Petitie &p ){
     dataDepunerii = p.dataDepunerii;
     numePrenume = p.numePrenume;
     categorie = p.categorie;

     if(p.descriere !=nullptr){
       descriere = new char[strlen(p.descriere)+1];
       strcpy_s(this->descriere, strlen(p.descriere) + 1, p.descriere);
     } else{
       this->descriere = nullptr;
     }
     status = p.status;
     zileDeLaDepunere = p.zileDeLaDepunere;
   }

   //destructorul
   ~Petitie(){
    if(this->descriere != nullptr){
      delete[] this->descriere;
    }
   }

   //operatorul = se apeleaza cand un obiect existent primeste valorile altui obiect

   Petitie& operator=(const Petitie &p){
    //self-assignement verificam daca deja avem un obiect de acest fel
    if (this == &p){
      return *this;
    }

    if(this->descriere != nullptr){
      delete[] this->descriere;
    }
    //copiem atributele simple
    this->dataDepunerii = p.dataDepunerii;
    this->numePrenume = p.numePrenume;
    this->categorie = p.categorie;
    this->status = p.status;
    this->zileDeLaDepunere = p.zileDeLaDepunere;
    //deep copy pentru descriere
    if(p.descriere != nullptr){
      this->descriere = new char[strlen(p.descriere) + 1];
      strcpy_s(this->descriere, strlen(p.descriere) + 1, p.descriere);
    }else{
      this->descriere = nullptr;
    }
    return *this;
   }

   //operatorul ! - pentru teste logice

   bool operator!() const{
    if (status == false && zileDeLaDepunere > termen_legal){
      return true;
    }
    else{
      return false;
    }
   }

};