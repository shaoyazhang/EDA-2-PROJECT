# include "game.h"

//************ LAB 2 **************//
//********** DO NOT MODIFY ********//

typedef struct SNode {
    Scenario scenario;
    struct SNode* adjacent[MAX_SCENARIOS];
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