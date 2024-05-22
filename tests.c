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
    
    // const char* fp = "scenarios_config.json";
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
    //printf("%s", scenarios[0].decision.options[0].enemies[0].skills[0].name);
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
    // dequeue(q); 
    // dequeue(q);
    // dequeue(q);
    // dequeue(q);
    // dequeue(q);

}
# endif 

// test for queue turn && fight flow
void test04()
{
    srand((unsigned)time(NULL));
    Queue* q = queueInit ();
    int q_num = 0;
    while (q_num< MAX_BATTLE_TURNS)
    {
        enqueue (q, "player");
        q_num++;
        enqueue (q, "enemy");
        q_num++;
    }
    
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
    while(q->size)
    {
        fightFlow(q, &players[1], &(scenarios[1].decision.options[0].enemies[1]));
    }
    winAllBattles(&players[1], &(scenarios[1].decision.options[0].enemies[1]));
}

// test for enemies' data ---> This function has been merged to scenarioInit()
# if 0
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
    Graph graph;
    graphInit(&graph);
    //const char* fp = "scenario_config.json";
    const char* fp = "scenarios_config.json";
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

    for (int i = 0; i < MAX_SCENARIOS; i++)
    {
        for (int j = 0; j < MAX_SCENARIOS; j++)
        {   if (i != j)
                addEdges(&graph, i, j);
        }
    }
    printGraph (&graph);

}
# endif


// test for scenario navigation
# if 1
void test07()
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

    for (int i = 0; i < MAX_SCENARIOS; i++)
    {
        for (int j = 0; j < MAX_SCENARIOS; j++)
        {   if (i != j)
                addEdges(&graph, i, j);
        }
    }

    bool winAllBattles = true;
    navigateScenario (&graph, 2, winAllBattles);
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