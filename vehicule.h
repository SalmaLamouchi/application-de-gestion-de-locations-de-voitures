
#ifndef VEHICULE_H
#define VEHICULE_H

struct Vehicule {
  char matricule[10];
  char constructeur[20];
  char marque[20];
  char etat[10];
};

void mettre_a_jour_constructeur(struct Vehicule *vehicule, const char *nouveau_constructeur);
void mettre_a_jour_marque(struct Vehicule *vehicule, const char *nouvelle_marque);
void mettre_a_jour_etat(struct Vehicule *vehicule, const char *nouvel_etat);
void saisir_vehicule(struct Vehicule *vehicule);
void afficher_vehicule(const struct Vehicule *vehicule);
#endif

