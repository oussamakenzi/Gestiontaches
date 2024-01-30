#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum priorite {
    HAUTE,
    MOYENNE,
    BASSE
};

struct dateEcheance {
    unsigned annee;
    unsigned mois;
    unsigned jour;
};

struct informationsTache {
    char description[100];
    struct dateEcheance date;
    enum priorite priorite;
};

struct tache {
    char nomDeTache[50];
    int length;
    struct informationsTache *taches;
};

void ajouterUneTache(struct tache *tache) {
    printf("Entrer le nom de la tache : \n");
    scanf("%s", tache->nomDeTache);
    getchar();
    printf("Entrer la description de la tache : \n");
    fgets(tache->taches[tache->length].description, sizeof(tache->taches[tache->length].description), stdin);
    printf("Ajouter l'annee de creation, le mois et le jour : \n");
    scanf("%u %u %u", &tache->taches[tache->length].date.annee, &tache->taches[tache->length].date.mois, &tache->taches[tache->length].date.jour);
    printf("Entrer la priorite (0: HAUTE, 1: MOYENNE, 2: BASSE) : ");
    scanf("%d", (int *)&tache->taches[tache->length].priorite);

    tache->length++;
}

void afficherLesTaches(struct tache *Tache) {
    int i;
    for (i = 0; i < Tache->length; i++) {
        printf("Tache %d :\n", i + 1);
        printf("__________________________________________________________\n");
        printf("Nom de la tache: %s\n", Tache->nomDeTache);
        printf("Description: %s\n", Tache->taches[i].description);
        printf("Date d'echeance: %u-%u-%u\n", Tache->taches[i].date.annee, Tache->taches[i].date.mois, Tache->taches[i].date.jour);
        printf("proprite est : ");
        switch (Tache->taches[i].priorite){
    case 0:  printf("HAUTE\n");
             break;
    case 1 : printf("MOYENNE\n");
             break;
    case 2:  printf("BASSE\n");break;
    default:
            printf("erreur\n");}
            printf("_______________________________________________________\n");
    }
}

void supprimerUneTache(struct tache *tache, const char *nomDeTache) {
    int i, index = -1;
    for (i = 0; i < tache->length; i++) {
        if (strcmp(tache->nomDeTache, nomDeTache) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (i = index; i < tache->length - 1; i++) {
            tache->taches[i] = tache->taches[i + 1];
        }
        tache->length--;
    }
}
void ordonnerTaches(struct tache *tache) {
    int i, j;
    for (i = 0; i < tache->length; i++) {
        for (j = 0; j < tache->length - i - 1; j++) {
            if (tache->taches[j].date.annee > tache->taches[j + 1].date.annee ||
                (tache->taches[j].date.annee == tache->taches[j + 1].date.annee &&
                 (tache->taches[j].date.mois > tache->taches[j + 1].date.mois ||
                  (tache->taches[j].date.mois == tache->taches[j + 1].date.mois &&
                   tache->taches[j].date.jour > tache->taches[j + 1].date.jour)))) {
                struct informationsTache temp = tache->taches[j];
                tache->taches[j] = tache->taches[j + 1];
                tache->taches[j + 1] = temp;
            }
        }
    }
}
void modifierUneTache(struct tache *tache){


}


int main() {
    struct tache Tache;
    Tache.length = 0;
    Tache.taches = malloc(50 * sizeof(struct informationsTache));







    unsigned choix;

    do {

        printf("---------------------------------------------------------\n");
        printf("---------------   1  ajouter une tache ------------------\n");
        printf("---------------   2  afficher les taches ----------------\n");
        printf("----------------  3  supprimer une tache ----------------\n");
        printf("----------------  4  ordonner les taches-----------------\n");
        printf("----------------  5  quitter-----------------------------\n");
        printf("---------------------------------------------------------\n");

        printf("entrer votre choix : \n");
        if (scanf("%u", &choix) != 1) {
            // Handle invalid input (non-numeric)
            printf("Invalid input. Please enter a number.\n");
            // Clear the input buffer
            while (getchar() != '\n');
            continue;
        }

        switch (choix) {
            case 1:
                ajouterUneTache(&Tache);
                break;

            case 2:
                afficherLesTaches(&Tache);
                break;

            case 3:
                {
                    char nomTache[50];
                    printf("Entrer le nom de la tache à supprimer : ");
                    scanf("%s", nomTache);
                    supprimerUneTache(&Tache, nomTache);
                }
                break;
            case 4 :
                         ordonnerTaches(&Tache);
                         printf("les tache a trier : ");
                         afficherLesTaches(&Tache);

                         break;
        }

    } while (choix < 5);

    free(Tache.taches);

    return 0;
}



