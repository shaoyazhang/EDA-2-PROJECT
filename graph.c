# include "graph.h"
// Initialize graph
// Use array to build graph
void graphInit(Graph* graph)
{
    graph->num_nodes = 0;
}


// Insert a scenario to the graph
void addScenario (Graph* graph, Scenario scenario)
{
    if (graph->num_nodes >= MAX_SCENARIOS)
    {
        printf("Maximum scenario number has reached\n");
        return;
    }
    else
    {
        SN* node = &graph->nodes[graph->num_nodes++];
        node->scenario = scenario;
        node->num_adjacent = 0;
    }
}

//
void addEdges (Graph* graph, int srcIndex, int destIndex)
{
    if (srcIndex >= 0 && srcIndex < graph->num_nodes && destIndex >= 0 && destIndex < graph->num_nodes) {
        SN* srcNode = &graph->nodes[srcIndex];
        SN* destNode = &graph->nodes[destIndex];
        if (srcNode->num_adjacent < MAX_SCENARIOS)
            srcNode->adjacent[srcNode->num_adjacent++] = destNode;
    } else {
        printf("Invalid node index!\n");
    }
}


// Function to print the graph
void printGraph (Graph* graph)
{
    for (int i = 0; i < MAX_SCENARIOS; i++)
    {
        printf("Scenario %d: %s\n", i+1, graph->nodes[i].scenario.name);
        printf("    Description: %s\n", graph->nodes[i].scenario.description);
        printf("    Question: %s\n", graph->nodes[i].scenario.decision.question);
        for (int j = 0; j < MAX_DECISION; j++) 
        {
            printf("    Option %d: %s\n", j+1, graph->nodes[i].scenario.decision.options[j].response);
            printf("        Narrative: %s\n", graph->nodes[i].scenario.decision.options[j].narra_bf);
            printf("        Narrative: %s\n", graph->nodes[i].scenario.decision.options[j].narra_af);
        }
        printf("    Adjacent senarios: ");
        for (int j = 0; j < graph->nodes[i].num_adjacent; j++)
        {
            printf("%s ", graph->nodes[i].adjacent[j]->scenario.name);
        }
        printf("\n");
    }
    
}