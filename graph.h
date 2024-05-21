#include "game.h"


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


void graphInit(Graph* graph);
void addScenario (Graph* graph, Scenario Scenario);
void addEdges (Graph* graph, int srcIndex, int destIndex);
void printGraph (Graph* graph);
void navigateScenario (Graph* graph, int currentScenarioIndex, bool winAllBattles);
//Enemy* makeDecision(Graph* graph, int currScenarioIdx, int decision_index);
