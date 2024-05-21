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

void printSenario (Scenario* scenario)
{
    printf("Details for Scenario: %s\n", scenario->name);
    printf("    Description: %s\n", scenario->description);
    printf("    Question: %s\n", scenario->decision.question);
    for (int j = 0; j < MAX_DECISION; j++) 
        {
            printf("    Option %d: %s\n", j+1, scenario->decision.options[j].response);
            printf("        Narrative before: %s\n", scenario->decision.options[j].narra_bf);
            printf("        Narrative after: %s\n", scenario->decision.options[j].narra_af);
        }
}

// navigate scenarios
void navigateScenario (Graph* graph, int curScenarioIdx, bool winAllBattles)
{
    if (winAllBattles)
    {
        if (graph->nodes[curScenarioIdx].num_adjacent == 0) 
        {
        printf("The next base will not be available until you win this battle.\n");
        return;
        }
        else
        {
            printf("You can navigate to these bases:\n");
            for (int i = 0; i < graph->nodes[curScenarioIdx].num_adjacent; i++) 
            {
                printf("%d. %s\n", i + 1, graph->nodes[curScenarioIdx].adjacent[i]->scenario.name);
            }
        }
        printf("Please select one base you want to navigate:\n");
        int option;
        scanf("%d", &option);
        if (option < 1 || option > graph->nodes[curScenarioIdx].num_adjacent) 
        {
            printf("Invalid choice.\n");
            return;
        }
        int nextScenarioIdx = option - 1;
        printf("Navigating to %s\n", graph->nodes[curScenarioIdx].adjacent[nextScenarioIdx]->scenario.name);
        printSenario (&graph->nodes[curScenarioIdx].adjacent[nextScenarioIdx]->scenario);
        // printf("    Adjacent senarios: ");
        // for (int j = 0; j < graph->nodes[nextScenarioIdx].num_adjacent; j++)
        // {
        //     printf("%s ", graph->nodes[nextScenarioIdx].adjacent[j]->scenario.name);
        // }
        // printf("\n");
    }
}

// ********* LAB 3 DO NOT MODIFY*********// 
void makeDecision(Graph* graph, int currScenarioIdx, int decision_index) 
{
    if (decision_index >= 0 && decision_index < graph->nodes[currScenarioIdx].scenario.decision.option_num) 
    {
        // Get the enemy array
        Enemy* enemies = graph->nodes[currScenarioIdx].scenario.decision.options[decision_index].enemies;
        
        // Loop through the enemy array and print their names
        for (int i = 0; i < MAX_ENEMIES; i++) 
        {
            // Check if the enemy name is not empty to avoid printing uninitialized data
            if (strlen(enemies[i].name) > 0) 
            {
                printEnemySkillDetail(&enemies[i]);
            }
        }
    }
    else 
    {
        printf("Invalid decision index\n");
    }
}
// ********* LAB 3 *********//