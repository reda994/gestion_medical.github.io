#include <iostream>
#include <vector>
#include "Medical.h"

using namespace std;

int main() {
    vector<Consultation> consultations;
    vector<Medecin> medecins;
    vector<Patient> patients;

    //medcines
    medecins.push_back(Medecin("Ali", "Cardiologie", 10));
    medecins.push_back(Medecin("Sara", "Pediatrie", 5));
    medecins.push_back(Medecin("Omar", "Neurologie", 7));
    medecins.push_back(Medecin("abdelmoumen", "Neurologie", 9));

    // Patients
    patients.push_back(Patient("Ahmed", 55, "M", 101));
    patients.push_back(Patient("Fatima", 30, "F", 102));
    patients.push_back(Patient("Youssef", 65, "M", 103));

    // Consultations
    consultations.push_back(Consultation(medecins[0], patients[0], Date(2025, 12, 20), "Hypertension"));
    consultations.push_back(Consultation(medecins[1], patients[1], Date(2025, 12, 21), "Rhinite"));
    consultations.push_back(Consultation(medecins[0], patients[2], Date(2025, 12, 22), "Cardiopathie"));
    consultations.push_back(Consultation(medecins[2], patients[0], Date(2025, 12, 23), "Migraine"));


    int choix;

    do {
        cout << "\n=========== MENU PRINCIPAL ===========\n";
        cout << "1. Gestion Medecins\n";
        cout << "2. Gestion Patients\n";
        cout << "3. Gestion Consultations\n";
        cout << "0. Quitter\n";
        cout << "Choix : ";
        cin >> choix;

        switch (choix) {

            // ================== MENU MEDECINS ==================
        case 1: {
            int sousChoix;
            do {
                cout << "\n--- Gestion Medecins ---\n";
                cout << "1. Ajouter medecin\n";
                cout << "2. Afficher tous les medecins\n";
                cout << "3. Afficher medecins par date\n";
                cout << "4. Verifier disponibilite\n";
                cout << "0. Retour\n";
                cout << "Choix : ";
                cin >> sousChoix;

                switch (sousChoix) {
                case 1: {
                    string nom, spec;
                    int exp;
                    cout << "Nom medecin : "; cin >> nom;
                    cout << "Specialite : "; cin >> spec;
                    cout << "Experience : "; cin >> exp;
                    medecins.push_back(Medecin(nom, spec, exp));
                    cout << "Medecin ajoute.\n";
                    break;
                }
                case 2:
                    for (size_t i = 0; i < medecins.size(); i++)
                        cout << i << ": " << medecins[i] << endl;
                    break;

                case 3: {
                    int j, mo, a;
                    cout << "Date (jour mois annee): "; cin >> j >> mo >> a;
                    afficherMedecinsParDate(consultations, Date(a, mo, j));
                    break;
                }

                case 4: {
                    int m, j, mo, a;
                    cout << "Indice medecin : "; cin >> m;
                    cout << "Date (jour mois annee) : "; cin >> j >> mo >> a;
                    if (medecinDisponible(consultations, medecins[m], Date(a, mo, j)))
                        cout << "Medecin disponible.\n";
                    else
                        cout << "Medecin indisponible.\n";
                    break;
                }
                }

            } while (sousChoix != 0);
            break;
        }

              // ================== MENU PATIENTS ==================
        case 2: {
            int sousChoix;
            do {
                cout << "\n--- Gestion Patients ---\n";
                cout << "1. Ajouter patient\n";
                cout << "2. Afficher tous les patients\n";
                cout << "3. Modifier informations patient\n";
                cout << "4. Patients +50 ans en cardiologie\n";
                cout << "0. Retour\n";
                cout << "Choix : ";
                cin >> sousChoix;

                switch (sousChoix) {
                case 1: {
                    string nom, sexe;
                    int age, num;
                    cout << "Nom patient : "; cin >> nom;
                    cout << "Age : "; cin >> age;
                    cout << "Sexe : "; cin >> sexe;
                    cout << "Numero dossier : "; cin >> num;
                    patients.push_back(Patient(nom, age, sexe, num));
                    cout << "Patient ajoute.\n";
                    break;
                }
                case 2:
                    for (size_t i = 0; i < patients.size(); i++)
                        cout << i << ": " << patients[i] << endl;
                    break;

                case 3: {
                    int p;
                    cout << "Indice patient : "; cin >> p;
                    cout << "Nouveau nom : "; cin >> patients[p].nom;
                    cout << "Nouvel age : "; cin >> patients[p].age;
                    cout << "Modification effectuee.\n";
                    break;
                }

                case 4:
                    patientsCardioPlus50(consultations);
                    break;
                }

            } while (sousChoix != 0);
            break;
        }

              // ================== MENU CONSULTATIONS ==================
        case 3: {
            int sousChoix;
            do {
                cout << "\n--- Gestion Consultations ---\n";
                cout << "1. Reserver une consultation\n";
                cout << "2. Afficher toutes les consultations\n";
                cout << "3. Rechercher consultations par patient (periode)\n";
                cout << "4. Consultations d'un medecin par mois\n";
                cout << "5. Patients ayant une consultation a une date\n";
                cout << "6. Verifier inscription d'un patient\n";
                cout << "7. Statistiques consultations\n";
                cout << "0. Retour\n";
                cout << "Choix : ";
                cin >> sousChoix;

                switch (sousChoix) {
                case 1: {
                    if (medecins.empty() || patients.empty()) {
                        cout << "Ajoutez medecins et patients d'abord.\n";
                        break;
                    }

                    int m, p, j, mo, a;
                    string diag;
                    cout << "Indice medecin : "; cin >> m;
                    cout << "Indice patient : "; cin >> p;
                    cout << "Date (jour mois annee) : "; cin >> j >> mo >> a;

                    Date d(a, mo, j);
                    if (medecinDisponible(consultations, medecins[m], d)) {
                        cout << "Diagnostic : "; cin >> diag;
                        consultations.push_back(Consultation(medecins[m], patients[p], d, diag));
                        cout << "Consultation reservee.\n";
                    }
                    else {
                        cout << "Medecin indisponible.\n";
                    }
                    break;
                }

                case 2:
                    for (auto& c : consultations)
                        cout << c << endl;
                    break;

                case 3: {
                    int p;
                    cout << "Indice patient : "; cin >> p;
                    Date d1, d2;
                    cout << "Date debut (j m a) : "; cin >> d1.jour >> d1.mois >> d1.annee;
                    cout << "Date fin (j m a) : "; cin >> d2.jour >> d2.mois >> d2.annee;
                    for (auto& c : consultations)
                        if (c.patient == patients[p] && !(c.date < d1) && !(d2 < c.date))
                            cout << c << endl;
                    break;
                }

                case 4: {
                    int m, mois;
                    cout << "Indice medecin : "; cin >> m;
                    cout << "Mois : "; cin >> mois;
                    for (auto& c : consultations)
                        if (c.medecin == medecins[m] && c.date.mois == mois)
                            cout << c << endl;
                    break;
                }

                case 5: {
                    int j, mo, a;
                    cout << "Date (j m a) : "; cin >> j >> mo >> a;
                    for (auto& c : consultations)
                        if (c.date == Date(a, mo, j))
                            cout << c.patient << endl;
                    break;
                }

                case 6: {
                    int p, m, j, mo, a;
                    cout << "Indice patient : "; cin >> p;
                    cout << "Indice medecin : "; cin >> m;
                    cout << "Date (j m a) : "; cin >> j >> mo >> a;

                    bool trouve = false;
                    for (auto& c : consultations)
                        if (c.patient == patients[p] &&
                            c.medecin == medecins[m] &&
                            c.date == Date(a, mo, j))
                            trouve = true;

                    if (trouve)
                        cout << "Patient inscrit.\n";
                    else
                        cout << "Aucune consultation trouvee.\n";
                    break;
                }

                case 7:
                    statistiquesConsultations(consultations);
                    break;
                }

            } while (sousChoix != 0);
            break;
        }

        } 

    } while (choix != 0);

    return 0;
}
