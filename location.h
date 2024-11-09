

#ifndef LOCATION_H
#define LOCATION_H


struct Date {
  int jour;
  int mois;
  int annee;
};

struct Location {
  struct Vehicule *vehicule;
  struct Client *client;
 struct Date date_debut;
  struct Date date_fin;
  float prix_total;
  float montant_avance;

};

struct EnsembleLocation {
  struct Location *locations;
  int nbr_locations;
};

int comparer_dates(struct Date date1, struct Date date2);
void saisir_location(struct Location *location, struct Parc *parc, struct EnsembleLocation *ensemble_locations);
void fin_location(struct EnsembleLocation *ensemble_locations);
void consulter_vehicules_loues(struct EnsembleLocation *ensemble_locations);
void consulter_vehicules_par_client(struct EnsembleLocation *ensemble_locations, int cin_client);
void menu_gestion_locations(struct EnsembleLocation *ensemble_locations, struct Parc *parc);


#endif
