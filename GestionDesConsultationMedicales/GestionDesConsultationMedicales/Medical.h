

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ===================== CLASSE DATE =====================
class Date {
public:
    int annee, mois, jour;

    Date(int a = 2025, int m = 1, int j = 1);     

    Date operator+(int jours) const;  
    bool operator==(const Date& d) const;
    bool operator<(const Date& d) const;

    friend ostream& operator<<(ostream& out, const Date& d);
};

// ===================== CLASSE MEDECIN =====================
class Medecin {
public:
    string nom;
    string specialite;
    int experience;

    Medecin(string n = "", string s = "", int e = 0);

    bool operator==(const Medecin& m) const;

    friend ostream& operator<<(ostream& out, const Medecin& m);
};

// ===================== CLASSE PATIENT =====================
class Patient {
public:
    string nom;
    int age;
    string sexe;
    int numeroDossier;

    Patient(string n = "", int a = 0, string s = "", int num = 0);

    bool operator==(const Patient& p) const;

    friend ostream& operator<<(ostream& out, const Patient& p);
};

// ===================== CLASSE CONSULTATION =====================
class Consultation {
public:
    Medecin medecin;
    Patient patient;
    Date date;
    string diagnostic;

    Consultation(Medecin m, Patient p, Date d, string diag);

    bool operator==(const Consultation& c) const;

    friend ostream& operator<<(ostream& out, const Consultation& c);
};

// ===================== FONCTIONS =====================
bool medecinDisponible(const vector<Consultation>& cons, Medecin m, Date d);
void afficherMedecinsParDate(const vector<Consultation>& cons, Date d);
void consultationsParPatient(const vector<Consultation>& cons, Patient p, Date d1, Date d2);
void consultationsParMedecinParMois(const vector<Consultation>& cons, Medecin m, int mois);
void patientsParDate(const vector<Consultation>& cons, Date d);
void patientsCardioPlus50(const vector<Consultation>& cons);
void statistiquesConsultations(const vector<Consultation>& cons);


