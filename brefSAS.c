
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
    char nomDeTache[50];
    char description[100];
    struct dateEcheance date;
    enum priorite priorite;
};

struct tache {
    int length;
    struct informationsTache taches[50];  // Tableau de tâches sans pointeurs
};

void ajouterUneTache(struct tache *tache) {
    printf("Entrer le nom de la tache : \n");
    scanf("%s", tache->taches[tache->length].nomDeTache);
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
        printf("Nom de la tache: %s\n", Tache->taches[i].nomDeTache);
        printf("Description: %s\n", Tache->taches[i].description);
        printf("Date d echeance: %u-%02u-%02u\n", Tache->taches[i].date.annee, Tache->taches[i].date.mois, Tache->taches[i].date.jour);
        printf("priorite est : ");
        switch (Tache->taches[i].priorite) {
            case 0:
                printf("HAUTE\n");
                break;
            case 1:
                printf("MOYENNE\n");
                break;
            case 2:
                printf("BASSE\n");
                break;
            default:
                printf("erreur\n");
        }
        printf("_______________________________________________________\n");
    }
}

void supprimerUneTache(struct tache *tache, char *nomDeTache) {
    int i, index = -1;
    for (i = 0; i < tache->length; i++) {
        if (strcmp(tache->taches[i].nomDeTache, nomDeTache) == 0) {
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

void modifierUneTache(struct tache *tache, char *nomDuneTache) {
    int i, mod;
    for (i = 0; i < tache->length; i++) {
        if (strcmp(tache->taches[i].nomDeTache, nomDuneTache) == 0) {
            printf("entrez ce que vous voulez modifier (0: nom de la tache, 1: description, 2: date, 3: priorite): ");
            scanf("%d", &mod);

            switch (mod) {
                case 0:
                    printf("Entrer le nom de la tache : \n");
                    scanf("%s", tache->taches[i].nomDeTache);
                    break;
                case 1:
                    getchar();
                    printf("Entrer la description de la tache : \n");
                    fgets(tache->taches[i].description, sizeof(tache->taches[i].description), stdin);
                    break;
                case 2:
                    printf("entrez la nouvelle date : \n");
                    scanf("%u %u %u", &tache->taches[i].date.annee,
                          &tache->taches[i].date.mois, &tache->taches[i].date.jour);
                    break;
                case 3:
                    printf("Entrer le nouveau priorite (0: HAUTE, 1: MOYENNE, 2: BASSE) : ");
                    scanf("%d", (int *)&tache->taches[i].priorite);
                    break;
                default:
                    printf("Choix non disponible.\n");
            }

            break;
        }
    }
}

void filtrerTaches(struct tache *tache, int priorite) {
    int i;
    for (i = 0; i < tache->length; i++) {
        if (tache->taches[i].priorite == priorite) {
            printf("                                                ");
            printf("Nom de la tache: %s\n", tache->taches[i].nomDeTache);
            printf("Description: %s\n", tache->taches[i].description);
            printf("Date d echeance: %u-%u-%u\n", tache->taches[i].date.annee, tache->taches[i].date.mois, tache->taches[i].date.jour);
            printf("                                             ");
        }
    }
}

int main() {
    struct tache Tache;
    Tache.length = 0;
    char nomTache[50];
    char nomDeTache[50];
    int priorite;
    unsigned choix;

    do {
        printf("-----------   MENU:        -------------------------------\n");
        printf("                  1.   ajouter une tache                   \n");
        printf("                  2.   afficher les taches                 \n");
        printf("                  3.   supprimer une tache                 \n");
        printf("                  4.   ordonner les taches                 \n");
        printf("                  5.   modifier une tache                  \n");
        printf("                  6.   filtrer des taches                  \n");
        printf("                  7.   quitter                             \n");
        printf("---------------------------------------------------------\n");
        printf("entrer votre choix : \n");
        if (scanf("%u", &choix) != 1) {
            printf("non valide.\n");
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
                printf("Entrer le nom de la tache  a supprimer : ");
                scanf("%s", nomTache);
                supprimerUneTache(&Tache, nomTache);
                break;

            case 4:
                ordonnerTaches(&Tache);
                printf("les tache a trier : ");
                afficherLesTaches(&Tache);
                break;

            case 5:
                printf("entrez le nom de tache tu veux modifier : ");
                scanf("%s", nomDeTache);
                modifierUneTache(&Tache, nomDeTache);
                break;

            case 6:
                printf("entrez la priorite : ");
                scanf("%d", &priorite);
                filtrerTaches(&Tache, priorite);
                break;

            case 7:
                exit(0);
        }

    } while (choix < 7);

    return 0;
}
