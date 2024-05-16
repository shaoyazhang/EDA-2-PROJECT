#include "game.h"

char* readFile (const char* filename);
void loadScenario (const char*jsonString, Scenario** scenarios, int *num_sce);
void loadSkills (const char* jsonString, Skill** skills, int* num_skill);