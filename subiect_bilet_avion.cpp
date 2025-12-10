#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>

/*/*
    Se cere definirea clasei BiletAvion, care are următoarele câmpuri:

        - numarBilet      → întreg constant, generat automat crescător pe baza unui atribut static
        - numePasager     → șir de caractere ce nu poate fi vid
        - durataZbor      → durata zborului în ore (valoare întreagă, nu poate fi negativă)
        - distante        → vector alocat dinamic de valori double (distanțele trebuie să fie > 0)
        - numarSegmente   → întreg > 0, reprezintă numărul de elemente din vectorul distante

    Toate atributele clasei se definesc în zona privată.

    Clasa trebuie să conțină:
        - constructor cu parametrii: numePasager și durataZbor, în această ordine
        - destructor care să nu genereze memory leaks
        - constructor de copiere
        - setter pentru câmpurile distante și numarSegmente (metoda setDistante)

    Trebuie suprascrise:
        - operatorul = (atribuire), cu deep copy și fără memory leaks
        - operatorii >> și << (>> citește doar numePasager și durataZbor; << afișează toate câmpurile)
        - operatorul de cast explicit către double, care returnează distanța totală a zborului
        - operatorul += pentru adăugarea unui nou segment (o nouă distanță)
        - operatorul [] pentru accesarea și modificarea distanțelor, cu validarea indexului

    Se va implementa metoda DistantaTotala() care calculează suma tuturor distanțelor
    din vectorul distante.
*/

using namespace std;

class Bilet{
  private:
    static const int numarBilet;
    char*  numePasager;
    int durataZbor;
    double *distante;
    int numarSegmente;

    public:
     // constructorul cu parametrii

     Bilet(const char* numePasager, int durataZbor){
      if(numePasager != nullptr){
        this->numePasager = new char[strlen(numePasager) + 1];
        strcpy_s(this->numePasager, strlen(numePasager) + 1, numePasager);
      }
      else{
        this->numePasager = nullptr;
      }

      this->durataZbor = durataZbor;
     }

    //contructorul de copiere

    Bilet(const Bilet&  b){
     if(b.numePasager != nullptr){
       this->numePasager = new char[strlen(b.numePasager) + 1];
       strcpy_s(this->numePasager, strlen(b.numePasager) + 1, b.numePasager);
     }
     else{
       this->numePasager = nullptr;
     }
     this->durataZbor = b.durataZbor;
     this->distante = b.distante;
     this->numarSegmente = b.numarSegmente;
    }
};
