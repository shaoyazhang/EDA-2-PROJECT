#include "tests.h"

// test for loading characters' data
void test01()
{
    const char* fp = "skills.json";
    char* jsonString = readFile (fp);

    if (jsonString == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return;
    }

    Character* players = NULL;
    int num_charcter;
    characterInit(jsonString, &players, &num_charcter);
 
    for (int i = 0; i < MAX_CHARACTS; i++)
    {   
        printf("Player %d name: %s\n", i+1, players[i].name);
        for (int j = 0; j < MAX_SKILL; j++)
        { 
            printf("skill %d name: %s\n", j+1, players[i].skills[j].name);
            printf("    Description: %s\n", players[i].skills[j].description);
            printf("    type: %s\n", players[i].skills[j].type);
            printf("    duration: %d\n", players[i].skills[j].duration);
            printf("    atk: %d\n", players[i].skills[j].atk);
            printf("    hp: %d\n", players[i].skills[j].hp);
            printf("    def: %d\n", players[i].skills[j].def);
        }       
   }  
}

// test for loading secenarios' data
# if 1
void test02()
{   
    const char* fp = "scenario_config.json";
    char* jsonString = readFile (fp);

    if (jsonString == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return;
    }

    Scenario* scenarios = NULL;
    int num_scenarios;
    scenarioInit(jsonString, &scenarios, &num_scenarios);
    for ( int i = 0; i < num_scenarios; i++)
    {
        printf("Scenario name: %s\n", scenarios[i].name);
        printf("Description: %s\n", scenarios[i].description);
        printf("Decision: %d\n", scenarios[i].decision.option_num);
        printf("Decision ->Options :\n");
        for (int j = 0; j < MAX_DECISION; j++)
        {
            printf("    Response: %s\n", scenarios[i].decision.options[j].response);
            printf("    Narrative before: %s\n", scenarios[i].decision.options[j].narra_bf);
            printf("    Narrative after: %s\n", scenarios[i].decision.options[j].narra_af);
            printf("    Enemies:\n");
            for (int k = 0; k < MAX_ENEMIES; k++)
            {   
                if(strlen(scenarios[i].decision.options[j].enemies[k].name) > 0)
                {
                    printf("    %s\n", scenarios[i].decision.options[j].enemies[k].name);
                    for (int m = 0; m < MAX_SKILL; m++)
                    {
                        if(strlen(scenarios[i].decision.options[j].enemies[k].skills[m].name) > 0)
                            printf("        Skill %d %s\n", m+1, scenarios[i].decision.options[j].enemies[k].skills[m].name);
                    }
                }
                
                

            }
        }
    }
    free(scenarios);
    free(jsonString);
}
# endif

// test for queue 
# if 1
void test03()
{
    srand((unsigned)time(NULL));
    Queue* q = queueInit ();
    int q_num = 0;
    int count = 0;
    while (q_num< MAX_BATTLE_TURNS)
    {
        enqueue (q, "player");
        q_num++;
        count++;
        enqueue (q, "enemy");
        q_num++;
        count++;
    }
    printf("Enqued number: %d\n", count);
    
    dequeue(q); 
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    printf("Queue size: %d", q->size);

}
# endif 

// test for queue turn && fight flow
void test04()
{

    srand((unsigned)time(NULL));
    //Queue* q = NULL;
    Queue* q = queueInit ();
    enqueueTurns(q);
    printf("Head: %s\n", q->front->name);
    printQueue(q);
    // while(q->size)
    // {
    //     printf("%s\n", q->front->name);
    //     printf("%p\n", q->front->next);
    //     dequeue(q);
    // }

    // while (q->size) {
    //     printf("Dequeuing: %s\n", q->front->name);
    //     dequeue(q);
    //     if (!isEmpty(q)) {
    //         printf("Next front: %s\n", q->front->name);
    //     } else {
    //         printf("Queue is now empty.\n");
    //     }
    // }

    // Load scenarios
    const char* fp = "scenario_config.json";
    char* jsonString = readFile (fp);
    if (jsonString == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return;
    }
    Scenario* scenarios = NULL;
    int num_escenario;
    scenarioInit(jsonString, &scenarios, &num_escenario);
    
    // Load charcter's data
    const char* fp01 = "skills.json";
    char* jsonString1 = readFile (fp01);

    if (jsonString1 == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return;
    }

    Character* players = NULL;
    int num_charcter;
    characterInit(jsonString1, &players, &num_charcter);
    
    //********** fight flow after modified******//
    while (1)
    {
    bool gameResult = fightFlow(q, &players[1], &(scenarios[1].decision.options[0].enemies[1]));
        if (gameResult)
            break;
        if(gameResult == false)
            break;
    }
}


# if 0
// test for enemies' data ---> This function has been merged to scenarioInit()
void test05 ()
{
    const char* fp = "enemy_skills.json";
    char* jsonString = readFile (fp);

    if (jsonString == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return;
    }

    Enemy* enemies = NULL;
    int num_enemies;
    enemyInit(jsonString, &enemies, &num_enemies);
    for (int i = 0; i < 8; i++)
    {
        printf("enemy: %d\n", i+1);
        for (int j = 0; j < MAX_SKILL; j++)
        {
            printf("name: %s\n", enemies[i].skills[j].name);
            printf("    Description: %s\n", enemies[i].skills[j].description);
            printf("    type: %s\n", enemies[i].skills[j].type);
            printf("    duration: %d\n", enemies[i].skills[j].duration);
            printf("    atk: %d\n", enemies[i].skills[j].atk);
            printf("    hp: %d\n", enemies[i].skills[j].hp);
            printf("    def: %d\n", enemies[i].skills[j].def);
        }
    }
}
# endif

// test graph
# if 1
void test06 ()
{
    // Graph* graph = NULL;
    // graphInit(graph);

    Graph* graph = graphInit();
    //const char* fp = "scenario_config.json";
    const char* fp = "scenario_config.json";
    char* jsonString = readFile (fp);

    if (jsonString == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return;
    }

    Scenario* scenarios = NULL;
    int num_scenarios;
    scenarioInit(jsonString, &scenarios, &num_scenarios);
    for (int i = 0; i < num_scenarios; i++) {
        addScenario(graph, scenarios[i]);
    }

    // for (int i = 0; i < MAX_SCENARIOS; i++)
    // {
    //     for (int j = 0; j < MAX_SCENARIOS; j++)
    //     {   if (i != j)
    //             addEdges(&graph, i, j);
    //     }
    // }

    //**********Add global path to the graphic**********//
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

    // printf("adj num S1: %s\n", graph.nodes[3].adjacent[0]->scenario.name);
    // printf("adj num S1: %s\n", graph.nodes[3].adjacent[0]->scenario.name);
    printGraph (graph);


}
# endif

// test for scenarios navigation
# if 1
void test07()
{
    Graph* graph = graphInit();
    
    const char* fp = "scenario_config.json";
    char* jsonString = readFile (fp);
    if (jsonString == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return;
    }
    Scenario* scenarios = NULL;
    int num_scenarios;
    scenarioInit(jsonString, &scenarios, &num_scenarios);
    for (int i = 0; i < num_scenarios; i++) {
        addScenario(graph, scenarios[i]);
    }

    for (int i = 0; i < MAX_SCENARIOS; i++)
    {
        for (int j = 0; j < MAX_SCENARIOS; j++)
        {   if (i != j)
                addEdges(graph, i, j);
        }
    }

    const char* fp_charc = "skills.json";
    char* jsonString_charc = readFile (fp_charc);
    if (jsonString == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return;
    }

    Character* players = NULL;
    int num_characters;
    characterInit(jsonString_charc, &players, &num_characters);

    // bool winAllBattles = true;
    navigateScenario (graph, 0, &(players[1]));
}

# endif

// test for decision make
void test08()
{
    Graph graph;
    graphInit(&graph);
    const char* fp = "scenario_config.json";
    char* jsonString = readFile (fp);

    if (jsonString == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return;
    }

    Scenario* scenarios = NULL;
    int num_scenarios;
    scenarioInit(jsonString, &scenarios, &num_scenarios);
    for (int i = 0; i < num_scenarios; i++) {
        addScenario(&graph, scenarios[i]);
    }

    makeDecision(&graph, 1, 1);
   
}