#include <stdio.h>
#define MAX_NAME 120
#define MAX_SKILL 200
typedef struct{
char name[MAX_NAME];
int hp ;
int atk;
int def; 
int skill;
}Character;

typedef struct{
char sword_attack[MAX_SKILL];
char kick[MAX_SKILL];
char wrestle[MAX_SKILL];

}Skill;

typedef struct{

}Scenario;

typedef struct{

}Enemy;

typedef struct{

}Decision;

typedef struct{

}Option;