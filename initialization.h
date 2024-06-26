#include "game.h"

# ifndef _INITIALIZATION_H
# define __INITIALIZATION_H

char* readFile (const char* filename);
void scenarioInit (const char*jsonString, Scenario** scenarios, int *num_sce);
void characterInit (const char* jsonString, Character** players, int* num_charac);
void enemyInit (const char* jsonString, Enemy** enemies, int* num_enemy);

#endif