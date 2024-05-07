# ifndef _GAME_H
# define _GAME_H

#include <stdio.h>
#include <string.h>

//********** DO NOT MODIFY ********//
//*********** LAB 1 **************//
#define MAX_CHAR_NAME 50
#define MAX_SKILL_NAME 80
#define MAX_SCENARIO_NAME 80
#define MAX_DESCRIPTION 200
#define MAX_SKILL 4
#define MAX_QUESTION 100
#define MAX_ENEMIES 4
#define MAX_CHARACTS 4

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
    char enemies[MAX_ENEMIES];
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
    Decision decisions;
}Scenario;


// 6. enemy
typedef struct
{
    char name[MAX_CHAR_NAME];
    int atk;
    int hp; 
    int def;   
}Enemy;

// Initializations
void skill_init(Skill* skills);
void charcter_init(Character* players); 
void scenario_init(Scenario* scenarios);
void decision_init(Decision* decisions);
void option_init(Option* options);
void enemy_init(Enemy* enemies);
void game(Character *players);

#endif

// ********* DO NOT MODIFY ********//