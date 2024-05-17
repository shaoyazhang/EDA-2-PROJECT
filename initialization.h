#include "game.h"

char* readFile (const char* filename);
void loadScenario (const char*jsonString, Scenario** scenarios, int *num_sce);
void loadSkills (const char* jsonString, Character** players, int* num_charac);
void loadEnemySkills (const char* jsonString, Enemy** enemies, int* num_enemy);