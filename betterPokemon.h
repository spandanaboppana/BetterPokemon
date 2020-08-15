/*
 * betterPokemon.h
 *
 *  Created on: Nov 16, 2016
 *      Author: Spandana
 */



#ifndef BETTERPOKEMON_BETTERPOKEMON_H
#define BETTERPOKEMON_BETTERPOKEMON_H
//============================================================================
// Name        : betterPokemon.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <float.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

typedef struct pokemon_
{
    int x,y;

    // type supports pokemon or a pokeystop
    int type;

    int wall;


    // Type of pokemon in case of pokemon.
    // Number of pokeyballs in case of pokestop.
    int entity;
} pokemon;

enum {
    e_pokeystop=0,
    e_pokemon
};

enum {
    NO_WALL=0,
    WALL
};

enum {
    haunter,
    genzar,
    jigglypuff,
    ditto,
    cubone,
    psyduck,
    pikachu,
    squirtie,
    eevee,
    snorlax
} pokemonNames;

static const char * PokemonStrings[] = {
        "Haunter",
        "genzar",
        "jigglypuff",
        "ditto",
        "cubone",
        "psyduck",
        "pikachu",
        "squirtie",
        "eevee",
        "snorlax"
};
const char * getPokemonString( int enumVal )
{
    return PokemonStrings[enumVal];
}

#endif //BETTERPOKEMON_BETTERPOKEMON_H
