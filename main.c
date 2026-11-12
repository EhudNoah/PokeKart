#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main(void)
{
    Pokemon carapuce = creerPokemon("Carapuce", 50, 10, EAU);

    printf("%s : %d/%d PV\n",carapuce.nom, carapuce.pv, carapuce.pvMax);

    return 0;
}