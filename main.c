#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    FEU,
    EAU,
    PLANTE
} Type;

typedef struct {
    char nom[50];
    int pvMax;
    int pv;
    int attaque;
    Type type;
} Pokemon;

Pokemon creerPokemon(const char *nom, int pvMax, int attaque, Type type)
{
    Pokemon pokemon = {0};

    snprintf(pokemon.nom, sizeof(pokemon.nom), "%s", nom);
    pokemon.pvMax = pvMax;
    pokemon.pv = pvMax;
    pokemon.attaque = attaque;
    pokemon.type = type;

    return pokemon;
}

int calculerDegats(Pokemon attaquant, Pokemon cible) {
    int degats = attaquant.attaque;

    if (
        (attaquant.type == FEU && cible.type == PLANTE) ||
        (attaquant.type == EAU && cible.type == FEU) ||
        (attaquant.type == PLANTE && cible.type == EAU)
    ) {
        degats *= 2;
    }
    else if (
        (attaquant.type == FEU && cible.type == EAU) ||
        (attaquant.type == EAU && cible.type == PLANTE) ||
        (attaquant.type == PLANTE && cible.type == FEU)
    ) {
        degats /= 2;
    }
    return degats;
}

bool attaquer(Pokemon *attaquant, Pokemon *cible) {
    if (attaquant -> pv <= 0 || cible -> pv <= 0) {
        return false;
    }
    int degats = calculerDegats(*attaquant, *cible);
    cible->pv -= degats;
    if (cible->pv < 0) {
        cible->pv = 0;
    }
    return true;
}

char *combat(Pokemon *pokemon1, Pokemon *pokemon2) {
    printf("Combat entre %s et %s !\n", pokemon1->nom, pokemon2->nom);
    printf("%s (PV: %d) vs %s (PV: %d)\n", pokemon1->nom, pokemon1->pvMax, pokemon2->nom, pokemon2->pvMax);
    bool tourPremier = true;
    while (pokemon1->pv > 0 && pokemon2->pv > 0) {
        printf("%s attaque %s !\n", tourPremier ? pokemon1->nom : pokemon2->nom, tourPremier ? pokemon2->nom : pokemon1->nom);
        if (tourPremier) {
            attaquer(pokemon1, pokemon2);
        } else {
            attaquer(pokemon2, pokemon1);
        }
        tourPremier = !tourPremier;
        printf("%s (PV: %d) vs %s (PV: %d)\n", pokemon1->nom, pokemon1->pv, pokemon2->nom, pokemon2->pv);
    }
        if (pokemon1->pv <= 0) {
        return pokemon2->nom;
    } else {
        return pokemon1->nom;
    }
}
int main(void)
{
    Pokemon carapuce = creerPokemon("Carapuce", 50, 10, EAU);
    Pokemon salameche = creerPokemon("Salameche", 60, 15, FEU);

    char *gagnant = combat(&carapuce, &salameche);
    printf("Le gagnant est : %s\n", gagnant);

    return 0;
}