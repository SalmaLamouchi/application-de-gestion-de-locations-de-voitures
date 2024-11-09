

#ifndef CLIENT_H
#define CLIENT_H


struct Client {
  int cin;
  char nom[20];
  char prenom[20];
  char adresse[20];
};

void mettre_a_jour_nom(struct Client *client, const char *nouveau_nom);
void mettre_a_jour_prenom(struct Client *client, const char *nouveau_prenom);
void mettre_a_jour_adresse(struct Client *client, const char *nouvelle_adresse);
void saisir_client(struct Client *client);
void afficher_client(const struct Client *client);

#endif
