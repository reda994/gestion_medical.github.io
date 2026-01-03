#include "Medical.h"

// ===================== DATE =====================
Date::Date(int a, int m, int j) : annee(a), mois(m), jour(j) {}

Date Date::operator+(int jours) const {
    return Date(annee, mois, jour + jours);                 //J’ai surchargé l’opérateur + pour pouvoir ajouter un nombre de jours à une date.
}

bool Date::operator==(const Date& d) const {
    return annee == d.annee && mois == d.mois && jour == d.jour;                  // opérateur permet de comparer deux dates afin de vérifier si une consultation est programmée le même jour.
}  

bool Date::operator<(const Date& d) const {                                          //J’ai utilisé cet opérateur pour comparer deux dates dans les recherches par période.
    if (annee != d.annee) return annee < d.annee;
    if (mois != d.mois) return mois < d.mois;
    return jour < d.jour;
}

ostream& operator<<(ostream& out, const Date& d) {                                   //J’ai surchargé l’opérateur << pour faciliter l’affichage des dates.
    out << d.jour << "/" << d.mois << "/" << d.annee;
    return out;
}

// ===================== MEDECIN =====================
Medecin::Medecin(string n, string s, int e) : nom(n), specialite(s), experience(e) {}           

bool Medecin::operator==(const Medecin& m) const {                                  //J’ai défini l’égalité entre deux médecins pour vérifier la disponibilité et les statistiques.
    return nom == m.nom && specialite == m.specialite;
}

ostream& operator<<(ostream& out, const Medecin& m) {                                     //Cet opérateur améliore la lisibilité lors de l’affichage dans le menu.
    out << "Dr " << m.nom << " | " << m.specialite << " | Exp: " << m.experience << " ans";
    return out;
}

// ===================== PATIENT =====================
Patient::Patient(string n, int a, string s, int num)                             
    : nom(n), age(a), sexe(s), numeroDossier(num) {
}

bool Patient::operator==(const Patient& p) const {                          /*Le numéro de dossier permet d’identifier un patient de manière unique.*/
    return numeroDossier == p.numeroDossier;                 
}

ostream& operator<<(ostream& out, const Patient& p) {                      // Cela facilite l’affichage lors des consultations.
    out << "Patient: " << p.nom << " | Age: " << p.age
        << " | Sexe: " << p.sexe << " | Dossier: " << p.numeroDossier;
    return out;
}

// ===================== CONSULTATION =====================
Consultation::Consultation(Medecin m, Patient p, Date d, string diag)
    : medecin(m), patient(p), date(d), diagnostic(diag) {
}

bool Consultation::operator==(const Consultation& c) const {                  //Cet opérateur évite les doublons de consultations.
    return medecin == c.medecin && patient == c.patient && date == c.date;
}

ostream& operator<<(ostream& out, const Consultation& c) {                     //Il permet un affichage clair et structuré.
    out << c.date << " | " << c.medecin << " | " << c.patient
        << " | Diagnostic: " << c.diagnostic;
    return out;
}

// ===================== FONCTIONS ===================== 
bool medecinDisponible(const vector<Consultation>& cons, Medecin m, Date d) {                                 //Vérifie si un médecin est libre à une date donnée.      
    for (auto& c : cons)
        if (c.medecin == m && c.date == d)
            return false;
    return true;
}
 
void afficherMedecinsParDate(const vector<Consultation>& cons, Date d) {                                      //Afficher tous les médecins ayant une consultation à une date donnée.                                    
    for (auto& c : cons)
        if (c.date == d)
            cout << c.medecin << endl;
}

void consultationsParPatient(const vector<Consultation>& cons, Patient p, Date d1, Date d2) {                 //Afficher toutes les consultations d’un patient dans une période donnée.
    for (auto& c : cons)
        if (c.patient == p && !(c.date < d1) && !(d2 < c.date))
            cout << c << endl;
}

void consultationsParMedecinParMois(const vector<Consultation>& cons, Medecin m, int mois) {                   //Afficher toutes les consultations d’un médecin pendant un mois donné.
    for (auto& c : cons)
        if (c.medecin == m && c.date.mois == mois)
            cout << c << endl;
}

void patientsParDate(const vector<Consultation>& cons, Date d) {                           //Afficher tous les patients ayant une consultation à une date donnée.
    for (auto& c : cons)
        if (c.date == d)
            cout << c.patient << endl;
}

void patientsCardioPlus50(const vector<Consultation>& cons) {                      //Afficher les patients de plus de 50 ans ayant consulté un cardiologue.
    for (auto& c : cons)
        if (c.patient.age > 50 && c.medecin.specialite == "Cardiologie")
            cout << c.patient << endl;
}

void statistiquesConsultations(const vector<Consultation>& cons) {            //  Afficher le nombre total de consultations par médecin.
    vector<Medecin> meds;
    vector<int> count;

    for (auto& c : cons) {
        bool found = false;
        for (size_t i = 0; i < meds.size(); i++) {
            if (meds[i] == c.medecin) {
                count[i]++;
                found = true;
            }
        }
        if (!found) {
            meds.push_back(c.medecin);
            count.push_back(1);
        }
    }

    for (size_t i = 0; i < meds.size(); i++)
        cout << meds[i] << " -> " << count[i] << " consultations" << endl;
}
