#include <iostream>
#include <cstring>  // pentru strlen, strcpy
using namespace std;

class Carte {
private:
    char* titlu;           // titlul cartii
    char* autor;           // autorul cartii
    int anPublicatie;      // anul publicatiei
    char* isbn;            // codul ISBN al cartii

    // Atribut 1 in plus:
    int idCarte;           // ID unic pentru carte (de ex. in baza de date/biblioteca)

    // Atribut 2 in plus:
    string editura;        // numele editurii care a publicat cartea

public:
    // Constructor fara parametri
    Carte() {
        // titlu default
        this->titlu = new char[strlen("Necunoscut") + 1];
        strcpy(this->titlu, "Necunoscut");

        // autor default
        this->autor = new char[strlen("Necunoscut") + 1];
        strcpy(this->autor, "Necunoscut");

        // anPublicatie – punem o valoare "sigura"
        this->anPublicatie = 2000;

        // isbn default
        this->isbn = new char[strlen("Necunoscut") + 1];
        strcpy(this->isbn, "Necunoscut");

        // idCarte – 0 inseamna "neinitializat"
        this->idCarte = 0;

        // editura – string, nu trebuie alocat dinamic
        this->editura = "Necunoscuta";
    }

    // Constructor cu parametri + VALIDARI
    Carte(const char* titlu, const char* autor,
          int anPublicatie, const char* isbn,
          int idCarte, const string& editura) {

        // VALIDARE pentru titlu
        if (titlu != nullptr && strlen(titlu) > 0) {
            this->titlu = new char[strlen(titlu) + 1];
            strcpy(this->titlu, titlu);
        } else {
            this->titlu = new char[strlen("Necunoscut") + 1];
            strcpy(this->titlu, "Necunoscut");
        }

        // VALIDARE pentru autor
        if (autor != nullptr && strlen(autor) > 0) {
            this->autor = new char[strlen(autor) + 1];
            strcpy(this->autor, autor);
        } else {
            this->autor = new char[strlen("Necunoscut") + 1];
            strcpy(this->autor, "Necunoscut");
        }

        // VALIDARE pentru anPublicatie (interval rezonabil)
        if (anPublicatie < 1450 || anPublicatie > 2100) {
            this->anPublicatie = 2000;  // valoare default
        } else {
            this->anPublicatie = anPublicatie;
        }

        // VALIDARE pentru isbn (sa nu fie sir gol)
        if (isbn != nullptr && strlen(isbn) > 0) {
            this->isbn = new char[strlen(isbn) + 1];
            strcpy(this->isbn, isbn);
        } else {
            this->isbn = new char[strlen("Necunoscut") + 1];
            strcpy(this->isbn, "Necunoscut");
        }

        // VALIDARE pentru idCarte (id > 0)
        if (idCarte > 0) {
            this->idCarte = idCarte;
        } else {
            this->idCarte = 0;
        }

        // VALIDARE pentru editura (daca e goala punem ceva default)
        if (!editura.empty()) {
            this->editura = editura;
        } else {
            this->editura = "Necunoscuta";
        }
    }

    // Constructor de copiere (deep copy)
    Carte(const Carte& c) {
        // titlu
        this->titlu = new char[strlen(c.titlu) + 1];
        strcpy(this->titlu, c.titlu);

        // autor
        this->autor = new char[strlen(c.autor) + 1];
        strcpy(this->autor, c.autor);

        // anPublicatie
        this->anPublicatie = c.anPublicatie;

        // isbn
        this->isbn = new char[strlen(c.isbn) + 1];
        strcpy(this->isbn, c.isbn);

        // atributele in plus
        this->idCarte = c.idCarte;
        this->editura = c.editura;
    }

    // Destructor – eliberam ce am alocat cu new[]
    ~Carte() {
        if (this->titlu != nullptr) {
            delete[] this->titlu;
        }
        if (this->autor != nullptr) {
            delete[] this->autor;
        }
        if (this->isbn != nullptr) {
            delete[] this->isbn;
        }
    }

    // Operator= (fara memory leaks + fara auto-atribuire)
    Carte& operator=(const Carte& c) {
        if (this != &c) {
            // eliberam ce avem deja
            if (this->titlu != nullptr) {
                delete[] this->titlu;
            }
            if (this->autor != nullptr) {
                delete[] this->autor;
            }
            if (this->isbn != nullptr) {
                delete[] this->isbn;
            }

            // copiem titlu
            this->titlu = new char[strlen(c.titlu) + 1];
            strcpy(this->titlu, c.titlu);

            // copiem autor
            this->autor = new char[strlen(c.autor) + 1];
            strcpy(this->autor, c.autor);

            // copiem anPublicatie
            this->anPublicatie = c.anPublicatie;

            // copiem isbn
            this->isbn = new char[strlen(c.isbn) + 1];
            strcpy(this->isbn, c.isbn);

            // copiem atributele in plus
            this->idCarte = c.idCarte;
            this->editura = c.editura;
        }
        return *this;
    }

    // GETTERI ceruti: pentru cele 2 atribute in plus + anPublicatie
    int getAnPublicatie() const {
        return this->anPublicatie;
    }

    int getIdCarte() const {
        return this->idCarte;
    }

    string getEditura() const {
        return this->editura;
    }

    // SETTERI cu validare
    void setAnPublicatie(int an) {
        if (an >= 1450 && an <= 2100) {
            this->anPublicatie = an;
        }
        // altfel nu modificam nimic (sau am putea pune o valoare default)
    }

    void setIdCarte(int id) {
        if (id > 0) {
            this->idCarte = id;
        }
    }

    void setEditura(const string& e) {
        if (!e.empty()) {
            this->editura = e;
        }
    }

    // (optional) o metoda ca sa vezi rapid valorile – pentru debug
    void afiseazaInfo() const {
        cout << "Titlu: " << this->titlu << endl;
        cout << "Autor: " << this->autor << endl;
        cout << "An publicatie: " << this->anPublicatie << endl;
        cout << "ISBN: " << this->isbn << endl;
        cout << "ID carte: " << this->idCarte << endl;
        cout << "Editura: " << this->editura << endl;
    }
};

int main() {
    // Test constructor fara parametri
    Carte c1;
    cout << "Carte c1 (constructor fara parametri):" << endl;
    c1.afiseazaInfo();
    cout << endl;

    // Test constructor cu parametri
    Carte c2("Ion", "Liviu Rebreanu", 1920, "978-973-460-123-4", 1, "Humanitas");
    cout << "Carte c2 (constructor cu parametri):" << endl;
    c2.afiseazaInfo();
    cout << endl;

    // Test constructor de copiere
    Carte c3 = c2;
    cout << "Carte c3 (copie dupa c2):" << endl;
    c3.afiseazaInfo();
    cout << endl;

    // Test operator=
    Carte c4;
    c4 = c2;
    cout << "Carte c4 (operator= cu c2):" << endl;
    c4.afiseazaInfo();
    cout << endl;

    // Test setteri + getteri
    c1.setAnPublicatie(2024);
    c1.setIdCarte(10);
    c1.setEditura("Polirom");

    cout << "Dupa setteri, c1 are:" << endl;
    cout << "An publicatie: " << c1.getAnPublicatie() << endl;
    cout << "ID carte: " << c1.getIdCarte() << endl;
    cout << "Editura: " << c1.getEditura() << endl;

    return 0;
};
