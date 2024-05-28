

#include "game.h"
#include "initialization.h"

# ifndef _GRAPH_H
# define ___GRAPH_H

//************ LAB 2 **************//
//********** DO NOT MODIFY ********//
#define START_NODE_IDX 0
#define END_NODE_IX 3

typedef struct SNode {
    Scenario scenario;
    struct SNode* adjacent[MAX_SCENARIOS-1];
    int num_adjacent;
}SN;

typedef struct graph
{
    SN nodes[MAX_SCENARIOS];
    int num_nodes;
}Graph;



//************************//
// void graphInit(Graph* graph);
Graph* graphInit();
void addScenario (Graph* graph, Scenario Scenario);
void addEdges (Graph* graph, int srcIndex, int destIndex);
void drawGraphic(Graph* graph);
void printGraph (Graph* graph);
void printSenario (Scenario scenario);
void navigateScenario(Graph* graph, int curScenarioIdx, Character* player, int CharacterIdx); 
void makeDecision(Graph* graph, int currScenarioIdx, int decision_index);
void printEnemySkillDetail (Enemy* enemy);

# endif