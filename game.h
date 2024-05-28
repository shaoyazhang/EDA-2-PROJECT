#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> 
#include "cJSON.h"


# ifndef _GAME_H
# define _GAME_H


//********** DO NOT MODIFY ********//
//*********** LAB 1 **************//
#define MAX_CHAR_NAME 60
#define MAX_SKILL_NAME 80
#define MAX_SCENARIO_NAME 80
#define MAX_SCENARIOS 4
#define MAX_DESCRIPTION 200
#define MAX_SKILL 4
#define MAX_QUESTION 100
#define MAX_ENEMIES 2
#define MAX_CHARACTS 4
#define NUM_TURNS 4
#define MAX_DECISION 2
#define MAX_ENEMY_SKILLS 8
#define MAX_BATTLE_TURNS 16
#define TABLE_SIZE 100

#define TEMP_MODIFIER 0
#define DIRECT_ATL 1

// 1. Skills
typedef struct
{
    char name[MAX_SKILL_NAME];
    char description[MAX_DESCRIPTION];
    char type[MAX_CHAR_NAME]; 
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

// 6. enemy
typedef struct
{
    char name[MAX_CHAR_NAME];
    int atk;
    int hp; 
    int def;
    Skill skills[MAX_SKILL];   
}Enemy;

// 3. Option
typedef struct
{
    char response[MAX_QUESTION];
    char narra_bf[MAX_QUESTION];
    int enemy_num;
    Enemy enemies[MAX_ENEMIES];
    char narra_af[MAX_QUESTION];
}Option;

// 4. Decision
typedef struct
{
    char question[MAX_QUESTION];
    Option options[MAX_DECISION];
    int option_num;
}Decision;


// 5. Scenario
typedef struct
{
    char name[MAX_SCENARIO_NAME];
    char description[MAX_DESCRIPTION];
    Decision decision;
}Scenario;

// 
typedef struct SkillCount {
    char skillName[50];
    int count;
    struct SkillCount* next;
} SkillCount;

 // aqui defino  la struct
typedef struct {
    SkillCount* table[TABLE_SIZE];
} HashTable;


void menu();
void game(Character *players, int* selec);
void applySkill (Character* player, Enemy* enemy, int input, int pcNum, int turnIdx);




//********** DO NOT MODIFY ********//

//************ LAB 2 **************//
//********** DO NOT MODIFY ********//

typedef struct Node
{
    char name[MAX_CHAR_NAME];
    struct Node* next;
}Node;

typedef struct queue
{
    Node* front; 
    Node* rear;
    int size;
}Queue;

void printCharacterSkill (Character* player);
int isEmpty (Queue* q);
Queue* queueInit ();
int hash(const char* skillName);
HashTable* createHashTable();
void incrementSkillCount(HashTable* ht, const char* skillName);
void printSkillCounts(HashTable* ht);
void freeHashTable(HashTable* ht);
void enqueue (Queue* q, const char* name);
void dequeue (Queue* q);
void enqueueTurns(Queue* q);
void freeQueue(Queue* q);
void printQueue(Queue* q);
void applySkill (Character* player, Enemy* enemy, int playerSkillIdx, int pcSkillIdx, int turnIdx);
bool fightFlow (Queue* q, Character player, Enemy enemy);
int winAllBattles(Character* player, Enemy* enemy);
//********** DO NOT MODIFY ********//
#endif