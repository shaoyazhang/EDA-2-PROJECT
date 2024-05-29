# include "graph.h"

// 1. Initialize graph
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
        if (srcNode->num_adjacent < MAX_SCENARIOS)
            srcNode->adjacent[srcNode->num_adjacent++] = destNode;
    } else {
        printf("Invalid node index!\n");
    }
}


// 4. Function to print the graph ---> Function only used at test at the end, cancelled
# if 1 
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
            printf("        Adjacent senarios:");
            for (int k = 0; k < graph->nodes[j].num_adjacent; k++)
            {
                printf("    %s ", graph->nodes[j].adjacent[k]->scenario.name);
            }
        }
    }  
}
# endif

// 5. Function to print one scenario
void printSenario (Scenario scenario)
{
    printf("Details for Scenario: %s\n", scenario.name);
    printf("    Description: %s\n", scenario.description);
    printf("    Question: %s\n", scenario.decision.question);
    for (int j = 0; j < MAX_DECISION; j++) 
        {
            printf("    Option %d: %s\n", j+1, scenario.decision.options[j].response);
            printf("        %s\n", scenario.decision.options[j].narra_bf); // Narrative before
            //printf("        Narrative after: %s\n", scenario.decision.options[j].narra_af);
        }
}

// 6. Check if player wins the game
int winAllBattles(Character* player, Enemy* enemy) 
{
    
    // Check if the player has won
    if (player->hp > 0 && enemy->hp <= 0) 
    {
        // printf("Congratulations, you win the battle!!\n");
        return 1;
    }

    // Check if the enemy is defeated due to lack of attack and defense power
    if (enemy->atk == 0 && enemy->def == 0) 
    {
        if (player->atk > 0 || player->def > 0 || player->hp > 0) 
        {
            // printf("Congratulations, you win the battle!!\n");
            return 1;
        }
    }

    // Check if player loses
    if (enemy->hp > 0 &&  player->hp <= 0) 
    {
        return 0;
    }

    if (player->def == 0 && player->atk == 0) 
    {
        if (enemy->atk > 0 || enemy->def > 0 || enemy->hp > 0) 
        {
            // printf("Sorry, you lost. Game over.\n");
            return 0; // changed from 1 to 0
        }
    }

    // A tie situation, player still need to refight again
    if (player->def == 0 && player->atk == 0 && enemy->def == 0 && enemy->atk == 0 && player->hp == 0 && enemy->hp== 0) 
    {
        printf("It's a tie!\n");
        return 0;
    }
    // return -1 in case of any other than the above cases;
    return -1;
}

// 7. Traverse scenarios by its adjancency
void navigateScenario(Graph* graph, int curScenarioIdx, Character* players, int CharacterIdx) 
{
    int countDefeat = 0;
    bool completedScenario2 = false;
    bool completedScenario3 = false;
    while (countDefeat < 4) 
    {
        Scenario currentScenario = graph->nodes[curScenarioIdx].scenario;
        printf("You are now in %s\n", currentScenario.name);
        printSenario(currentScenario);

        // Let the player choose a decision path
        int decisionIndex = -1;
        if (currentScenario.decision.option_num > 1 && decisionIndex <= currentScenario.decision.option_num) {
            printf("Please choose your path:\n");
            for (int i = 0; i < currentScenario.decision.option_num; i++) {
                printf("%d. %s\n", i + 1, currentScenario.decision.options[i].response);
            }
            scanf("%d", &decisionIndex);
            while (decisionIndex < 1 || decisionIndex > currentScenario.decision.option_num) {
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
        for (int i = 0; i < currentScenario.decision.options[decisionIndex].enemy_num; i++) 
        {
            Queue* q = queueInit();
            enqueueTurns(q);
            printf("\n");
            printf("You are fighting against: %s\n", currentScenario.decision.options[decisionIndex].enemies[i].name);
            printf("\n");
            if (! fightFlow(q, players[CharacterIdx], currentScenario.decision.options[decisionIndex].enemies[i])) {
                battleResult = false;
                break;
            }
            else // if ( fightFlow(q, players[CharacterIdx], currentScenario.decision.options[decisionIndex].enemies[i]))
            {
                printf("\n");
                printf("You have defeated the enemy\n");
                printf("\n");
                freeQueue(q);
            }
            
        }

        if (battleResult) 
        {
            printf("\n");
            printf("You have won all battles in this base.\n");
            printf("\n");
            printf("%s\n", currentScenario.decision.options[decisionIndex].narra_af); // Narrative after 

            // Check if player has won the battles in both of these two scenarios
            if (curScenarioIdx == 1) {
                completedScenario2 = true;
            } else if (curScenarioIdx == 2) {
                completedScenario3 = true;
            }

            if (graph->nodes[curScenarioIdx].num_adjacent == 0) {
                printf("\n");
                printf("Congratulations!! You win the game\n");
                printf("\n");
                printf("Now you have got the secret book after thousands of tough but brave fights, you have proved that you"
                    "are the real warrior. May you be a great leader in the martial world\n");
                return;
            }

            // List available adjacent scenarios
            printf("*************************************\n");
            printf("You can navigate to next base:\n");
            int validOptions = 0; 
            int* adjScenarioIndices = (int*)malloc(graph->nodes[curScenarioIdx].num_adjacent * sizeof(int));

            for (int i = 0; i < graph->nodes[curScenarioIdx].num_adjacent; i++) 
            {
                int adjScenarioIdx = graph->nodes[curScenarioIdx].adjacent[i] - graph->nodes;
                if (adjScenarioIdx  == END_NODE_IX && (!completedScenario2 || !completedScenario3)) 
                {
                    continue; // Skip the end scenario if prerequisites are not met
                }
                printf("%d. %s\n", i + 1, graph->nodes[curScenarioIdx].adjacent[i]->scenario.name);
                adjScenarioIndices[validOptions] = adjScenarioIdx;
                validOptions++;
            }

            printf("Please select one base you want to navigate:\n");
            int option;
            scanf("%d", &option);
            while (option < 1 || option > validOptions) 
            {
                printf("Invalid choice, please select again.\n");
                scanf("%d", &option);
            }
            // Update curScenarioIdx to the index of the selected adjacent scenario
            curScenarioIdx = adjScenarioIndices[option - 1];
            free(adjScenarioIndices);
        } else {
            countDefeat++;
            printf("\n");
            printf("You lost the battle. Try again from this scenario. You have %d chances left\n", (4-countDefeat));
            printf("\n");
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
}
// ******************* LAB 3 ********************//