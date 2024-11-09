

#ifndef PARC_H
#define PARC_H

struct Parc {
  struct Vehicule **vehicules;
  int nbr_emplacements;
  int nbr_vehicules;
};
void ajouter_vehicule(struct Parc *parc);
void modifier_etat_vehicule(struct Parc *parc, char *matricule, char *nouvel_etat);
void supprimer_vehicule(struct Parc *parc, char *matricule);
void afficher_parc(struct Parc *parc);
void menu_gestion_parc(struct Parc *parc);

#endif
