# include "graph.h"

// 1. Initialize graph
// void graphInit(Graph* graph)
// {   
//     graph = (Graph*)malloc(sizeof(Graph));
//     graph->num_nodes = 0;
// }

Graph* graphInit()
{   
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_nodes = 0;
    return graph;
}

// 2. Insert a scenario to the graph
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

// 3. Implement adjacent matrix to build directed graph
void addEdges (Graph* graph, int srcIndex, int destIndex)
{
    if (srcIndex >= 0 && srcIndex < graph->num_nodes && destIndex >= 0 && destIndex < graph->num_nodes) {
        SN* srcNode = &graph->nodes[srcIndex];
        SN* destNode = &graph->nodes[destIndex];
        if (srcNode->num_adjacent < (MAX_SCENARIOS-1))
            srcNode->adjacent[srcNode->num_adjacent++] = destNode;
    } else {
        printf("Invalid node index!\n");
    }
}

// Draw graphic
void drawGraphic(Graph* graph)
{
    int path01[] ={START_NODE_IDX, 1};  // S1 - S2, S1 is the start node
    int path02[] = {START_NODE_IDX, 2};
    int path03[] ={1, 2};   // S2-S3
    int path04[] ={2, 1};   // S3-S2
    int path05[] ={1, END_NODE_IX}; // S3 -S4, S4 is the end node
    int path06[] ={2, END_NODE_IX}; 
    addEdges(graph, path01[0], path01[1]);
    addEdges(graph, path02[0], path02[1]);
    addEdges(graph, path03[0], path03[1]);
    addEdges(graph, path04[0], path04[1]);
    addEdges(graph, path05[0], path05[1]);
    addEdges(graph, path06[0], path06[1]);
}
// 4. Function to print the graph
void printGraph (Graph* graph)
{
    for (int i = 0; i < MAX_SCENARIOS; i++)
    {
        printf("Scenario %d: %s\n", i+1, graph->nodes[i].scenario.name);
        printf("    Description: %s\n", graph->nodes[i].scenario.description);
        // printf("    Question: %s\n", graph->nodes[i].scenario.decision.question);
        // for (int j = 0; j < MAX_DECISION; j++) 
        // {
        //     printf("    Option %d: %s\n", j+1, graph->nodes[i].scenario.decision.options[j].response);
        //     printf("        Narrative: %s\n", graph->nodes[i].scenario.decision.options[j].narra_bf);
        //     printf("        Narrative: %s\n", graph->nodes[i].scenario.decision.options[j].narra_af);
        // }
        printf("    Adjacent senarios: ");
        if (graph->nodes[i].num_adjacent <= 0)
        {
            printf("None\n");
        }
        else
        {
            for (int j = 0; j < graph->nodes[i].num_adjacent; j++)
            {
                printf("%s ", graph->nodes[i].adjacent[j]->scenario.name);   
            }
        }  
        printf("\n");
    }  
}

// 5. Function to print one scenario
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


// 6. Check if player wins the game
bool winAllBattles(Character* player, Enemy* enemy) {
    // Print the current status for debugging
    printf("Player HP: %d, ATK: %d, DEF: %d\n", player->hp, player->atk, player->def);
    printf("Enemy HP: %d, ATK: %d, DEF: %d\n", enemy->hp, enemy->atk, enemy->def);

    // Check if the player has won
    if (player->hp > 0 && enemy->hp <= 0) 
    {
        printf("Congratulations, you win the battle!!\n");
        return true;
    }

    // Check if the enemy is defeated due to lack of attack and defense power
    if (enemy->atk == 0 && enemy->def == 0) 
    {
        if (player->atk > 0 || player->def > 0 || player->hp > 0) 
        {
            printf("Congratulations, you win the battle!!\n");
            return true;
        }
    }

    // Check if player loses
    if (enemy->hp > 0 &&  player->hp <= 0) 
    {
        printf("Sorry, you lost. Game over.\n");
        return false;
    }

    if (enemy->def == 0 && enemy->atk == 0) 
    {
        if (enemy->atk > 0 || enemy->def > 0 || enemy->hp > 0) 
        {
            printf("Sorry, you lost. Game over.\n");
            return false;
        }
    }
    return false;
}

// 7. Traverse scenarios by its adjancency
# if 0
void navigateScenario (Graph* graph, int curScenarioIdx, bool winAllBattles)
{
    if (winAllBattles)
    {
        printf("The next base will not be available until you win all battles from this base.\n");
        if (graph->nodes[curScenarioIdx].num_adjacent == 0) 
        {
            printf("Congratulations!! You win the game\n");
            return;
        }

        // Makde decision to choose the path
        int input = 0;
        printf("Please choose your path: 1.%s 2.%s", 
            graph->nodes[curScenarioIdx].scenario.decision.options[0].enemies[0].name,
            graph->nodes[curScenarioIdx].scenario.decision.options[1].enemies[0].name
        );
        scanf("%d", &input);
        while (input < 1 || input > 2)
        {
            printf("Invalid option, please select again\n");
            scanf("%d", &input);
        }
        input--;
        makeDecision(graph, curScenarioIdx, input);

        printf("*************************************\n");
            printf("You can navigate to these bases:\n");
            for (int i = 0; i < graph->nodes[curScenarioIdx].num_adjacent; i++) 
            {
                printf("%d. %s\n", i + 1, graph->nodes[curScenarioIdx].adjacent[i]->scenario.name);
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
    }
}
# endif
void navigateScenario(Graph* graph, int curScenarioIdx, Character* player) {
    while (true) {
        Scenario* currentScenario = &graph->nodes[curScenarioIdx].scenario;
        printf("You are now in %s\n", currentScenario->name);
        printSenario(currentScenario);

        // Let the player choose a decision path
        int decisionIndex = -1;
        if (currentScenario->decision.option_num > 1) {
            printf("Please choose your path:\n");
            for (int i = 0; i < currentScenario->decision.option_num; i++) {
                printf("%d. %s\n", i + 1, currentScenario->decision.options[i].enemies[0].name);
            }
            scanf("%d", &decisionIndex);
            while (decisionIndex < 1 || decisionIndex > currentScenario->decision.option_num) {
                printf("Invalid option, please select again\n");
                scanf("%d", &decisionIndex);
            }
            decisionIndex--;
        } else {
            decisionIndex = 0;
        }

        // Engage in battle with the chosen enemies
        Queue* q = queueInit();
        enqueueTurns(q);
        bool battleResult = true;
        for (int i = 0; strlen(currentScenario->decision.options[decisionIndex].enemies[i].name) >0 ; i++) {
            if (!fightFlow(q, player, &currentScenario->decision.options[decisionIndex].enemies[i])) {
                battleResult = false;
                break;
            }
        }

        if (battleResult) {
            printf("You have won all battles in this scenario.\n");

            if (graph->nodes[curScenarioIdx].num_adjacent == 0) {
                printf("Congratulations!! You win the game\n");
                return;
            }

            // List available adjacent scenarios
            printf("*************************************\n");
            printf("You can navigate to these bases:\n");
            for (int i = 0; i < graph->nodes[curScenarioIdx].num_adjacent; i++) {
                printf("%d. %s\n", i + 1, graph->nodes[curScenarioIdx].adjacent[i]->scenario.name);
            }
            printf("Please select one base you want to navigate:\n");
            int option;
            scanf("%d", &option);
            while (option < 1 || option > graph->nodes[curScenarioIdx].num_adjacent) {
                printf("Invalid choice, please select again.\n");
                scanf("%d", &option);
            }
            curScenarioIdx = option - 1;
        } else {
            printf("You lost the battle. Try again from this scenario.\n");
        }
    }
}

// ********* LAB 3 DO NOT MODIFY*********//

// 8. Decision that affects the enemies that faces
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
// ********************** LAB 3 ***********************//