#pragma once
#include "game.h"

char* readFile (const char* filename);
void scenarioInit (const char*jsonString, Scenario** scenarios, int *num_sce);
void characterInit (const char* jsonString, Character** players, int* num_charac);
void enemyInit (const char* jsonString, Enemy** enemies, int* num_enemy);