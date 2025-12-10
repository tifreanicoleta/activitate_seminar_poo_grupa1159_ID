#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <limits>

using namespace std;

/* Se consideră o aplicaţie pentru gestionarea petițiilor primite în cadrul unei localități. Definiți o clasă care
modelează o astfel de solicitare. Se vor urmări atribute specifice, precum: data depunerii, numele şi prenumele
solicitantului, categoria în care se încadrează petiția, descrierea solicitării etc.Datele membre sunt private şi
sunt puse la dispoziție metode de acces. Clasa conține cel puțin patru câmpuri, dintre care unul este alocat
dinamic, constructori, metodele specifice claselor cu membri alocați dinamic şi operatorul de afişare. Folosiţi
un membru static sau const
- Se va defini operatorul! pentru indica dacă o petiţie nu are răspuns şi a depăşit termenul legal (30 de
zile).
- Se va defini operatorul - pentru schimba starea unei petiții (deschisă -> rezolvată).
- Definiţi operatorii << şi >> pentru scrierea/citirea în/din fişiere text.
- Specializați clasa definită şi exemplificatți conceptul de virtualizare.
- Propuneţi un container STL care permite gruparea petiţiilor după categorii şi regăsirea cu uşurință a
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

  //constructorul fara parametrii, initializeaza petitia cu valori default

  Petitie(){
    this->dataDepunerii = "";
    this->numePrenume = "";
    this->categorie = "";
    this->descriere = nullptr;
    this->status = false;
    this->zileDeLaDepunere = 0;
    nrPetitii++;
  }

  //constructorul cu parametrii

   Petitie(string dataDepunerii, string numePrenume, string categorie, const char* descriere, bool status, int zileDeLaDepunere){
     this->dataDepunerii = dataDepunerii;
     this->numePrenume = numePrenume;
     this->categorie = categorie;
     
     //deep copy
     if (descriere != nullptr){
       this->descriere = new char[strlen (descriere) + 1];
       strcpy_s(this->descriere, strlen(descriere) + 1, descriere);
     }else {
       this->descriere = nullptr;
     }

     this->status = status;
     this->zileDeLaDepunere = zileDeLaDepunere;
     nrPetitii++;
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
     nrPetitii++;
   }

   //destructorul
   ~Petitie(){
    if(this->descriere != nullptr){
      delete[] this->descriere;
    }
    nrPetitii--;
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

   //getteri

    string getCategorie() const {
        return categorie;
    }

    bool getStatus() const {
        return status;
    }

    int getZileDeLaDepunere() const {
        return zileDeLaDepunere;
    }

    static int getNrPetitii() {
        return nrPetitii;
    }

    //setteri
    void setZileDeLaDepunere(int zile) {
        if (zile >= 0) {
            this->zileDeLaDepunere = zile;
        }
    }

   //operatorul ! - pentru termen depasit si fara raspuns, verificam daca petitia este nerezolvata si a depasit termenul

   bool operator!() const{
    if (status == false && zileDeLaDepunere > termen_legal){
      return true; //devine true daca petitia este inca deschisa si a depasit termenul legal
    }
    else{
      return false;
    }
   }

   //functie virtuala, exemplu de virtualizare
   //calculeaza prioritatea petitiei in functie de termenul legal si categorie

   virtual float calculeazaPrioritate() const {
    float baza = 1.0f;
    if (!(*this)) {        // daca a depasit termenul si e deschisa
        baza += 2.0f;
    }
    if (categorie == "Urgent") {
        baza += 1.0f;
    }
    return baza;
  } 

   // operatorul - 

   Petitie& operator-(){
    if (status == false){
      this->status = true; //petitia devine rezolvata
    }
    return *this;
   } 

  

   // atributul friends

   friend ostream& operator<<(ostream& out, const Petitie &p);
   friend istream& operator>>(istream &in, Petitie &p);
};

//initializam atributul static din clasa petitie

int Petitie::nrPetitii = 0;

   //operatorul << scrie o petitie in stream consola/fisier text

   ostream& operator <<(ostream& out, const Petitie& p){
     out << p.dataDepunerii << "\n";
     out << p.numePrenume << "\n";
     out << p.categorie << "\n";

     if(p.descriere != NULL){
       out << p.descriere << "\n";
     }
     else{
       out << "-\n"; //fara descriere
     }
     out << p.status << "\n";
     out << p.zileDeLaDepunere << "\n";

     return out;
   }

   //operatorul >>  citeste o petitie in stream

   istream& operator>>(istream& in, Petitie& p){
     string buffer;

     //stergem descrierea veche

     if(p.descriere != NULL){
       delete[] p.descriere;
       p.descriere = NULL;
     }
      
     //citirea liniilor pt campuri de tip string
     getline(in, p.dataDepunerii);
     getline(in, p.numePrenume);
     getline(in, p.categorie);

     getline(in, buffer);
     if(buffer != "-"){
       p.descriere = new char[buffer.size() + 1];
       strcpy_s(p.descriere, buffer.size() + 1, buffer.c_str());
     }
     //citirea statusului si a nr de zile
     in >> p.status;
     in >> p.zileDeLaDepunere;

     in.ignore(numeric_limits<streamsize>::max(), '\n');

     return in;
   }


// Specializați clasa definită şi exemplificați conceptul de virtualizare.

class PetitieOnline : public Petitie{
private:
  string email;
  string platforma;

public:
  PetitieOnline() : Petitie(), email(""), platforma("") {}

  PetitieOnline(string dataDepunerii,
                string numePrenume,
                string categorie,
                const char *descriere,
                bool status,
                int zileDeLaDepunere,
                string email,
                string platforma)
      : Petitie(dataDepunerii, numePrenume, categorie, descriere, status, zileDeLaDepunere)
  {
    this->email = email;
    this->platforma = platforma;
  }
//supradefinire fct virtuala, petitiile online vor primi prioritate mai mare
  float calculeazaPrioritate() const override
  {
    float p = Petitie::calculeazaPrioritate();
    return p + 0.5f;
    }
};

//container stl pentru a grupa petitiile dupa categorie

map<string, vector<Petitie>> petitiiPeCategorii;

void adaugaPetitieInContainer(const Petitie& p){
  petitiiPeCategorii[p.getCategorie()].push_back(p);
}


int main() {
    Petitie p1("01.12.2025", "Ion Popescu", "Urbanism","Repararea drumului", false, 40);

    Petitie p2("05.12.2025", "Ana Ionescu", "Urbanism", "Trotuar deteriorat", true, 10);

    PetitieOnline p3("10.12.2025", "Marius Georgescu", "Iluminat","Bec ars pe Splaiul Unirii", false, 5,"marius@mail.com", "site");

    adaugaPetitieInContainer(p1);
    adaugaPetitieInContainer(p2);
    adaugaPetitieInContainer(p3);

    string cat = "Urbanism";
    cout << "Numar petitii in categoria " << cat << ": " << petitiiPeCategorii[cat].size() << endl;

    return 0;
}
