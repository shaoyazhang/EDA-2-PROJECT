#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "cJSON.h"


# ifndef _GAME_H
# define _GAME_H


//********** DO NOT MODIFY ********//
//*********** LAB 1 **************//
#define MAX_CHAR_NAME 20
#define MAX_SKILL_NAME 20
#define MAX_SCENARIO_NAME 20
#define SCE_NUM 4
#define MAX_DESCRIPTION 200
#define MAX_SKILL 4
#define MAX_QUESTION 100
#define MAX_ENEMIES 3
#define MAX_CHARACTS 4
#define NUM_TURNS 4
#define MAX_DECISION 2

// 1. Skills
typedef struct
{
    char name[MAX_SKILL_NAME];
    char description[MAX_DESCRIPTION];
    int type; // 0 means temporary modifier; 1 means direct attack
    int duration;
    int atk;
    int hp; 
    int def;
}Skill;

// 2. characters
typedef struct
{
    char name[MAX_CHAR_NAME];
    int hp;
    int atk;
    int def; 
    Skill skills[MAX_SKILL];
}Character;

// 3. options
typedef struct
{
    char response[MAX_QUESTION];
    char narra_bf[MAX_QUESTION];
    char enemies[MAX_ENEMIES][MAX_CHAR_NAME];
    char narra_af[MAX_QUESTION];
}Option;

// 4. Decisions
typedef struct
{
    char question[MAX_QUESTION];
    Option options;
    int option_num;
}Decision;


// 5. 4 Scenarios
typedef struct
{
    char name[MAX_SCENARIO_NAME];
    char description[MAX_DESCRIPTION];
    Decision decisions[MAX_DECISION];
}Scenario;


// 6. enemy
typedef struct
{
    char name[MAX_CHAR_NAME];
    int atk;
    int hp; 
    int def;
    Skill skills[MAX_SKILL];   
}Enemy;

// Initializations
// void skill_init(Skill* skills);
void charcter_init(Character* players); 
void scenarioInit(Scenario* scenarios);
void decision_init(Decision* decisions);
void option_init(Option* options);
void enemy_init(Enemy* enemies);
void game(Character *players);



//********** DO NOT MODIFY ********//

//************ LAB 2 **************//
//********** DO NOT MODIFY ********//

typedef struct Node
{
    Character* player;
    Enemy* enemy;
    struct Node* next;
}Node;

typedef struct queue
{
    Node* front; 
    Node* rear;
    int size;
}Queue;

void printCharacter (Character* player);
int isEmpty (Queue* q);
Queue* queueInit ();
void enqueueCharacter (Queue* q, Character* player);
void enqueueEnemy (Queue* q, Enemy* enemy);
void dequeue (Queue* q);
void queueTurn (Queue* q, Character* player, Enemy* enemies);
void fightFlow (Queue* q);



//********** DO NOT MODIFY ********//
#endif