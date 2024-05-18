#include "tests.h"
# include "initialization.h"

// test queue
void test01()
{
    srand((unsigned)time(NULL));
    Queue* q = queueInit ();

    Skill playerSkills[4] = {
        {"skill 1", "skill 1", 1, 2, 3, 4, 5},
        {"skill 2", "skill 2", 1, 2, 3, 4, 5},
        {"skill 3", "skill 2", 1, 2, 3, 4, 5},
        {"skill 4", "skill 2", 1, 2, 3, 4, 5}
    };

    Character player = {"Player", 100, 20, 10, {playerSkills[0],playerSkills[1], playerSkills[2], playerSkills[3]}};

    Skill enemySkills[4] = {
        {"Eskill 1", "Eskill 1", 1, 2, 3, 4, 5},
        {"Eskill 2", "Eskill 2", 1, 2, 3, 4, 5},
        {"Eskill 3", "Eskill 2", 1, 2, 3, 4, 5},
        {"Eskill 4", "Eskill 2", 1, 2, 3, 4, 5}
    };
    Enemy enemy = {"Enemy", 30, 50, 5, {enemySkills[0], enemySkills[1], enemySkills[2], enemySkills[3]}};
    queueTurn (q, &player, &enemy);

    Node* tmp = q->front;
    for ( int i = 0; i < NUM_TURNS; i++)
    {
        if (tmp->enemy == NULL)
        {
            printf("%s\n", tmp->player->name);
        }
        else if(tmp->player == NULL)
        {
            printf("%s\n", tmp->enemy->name);
        }

        tmp = tmp->next;  
    }
    printf("%d \n", q->size);

    // printf("%p ", q->front);
    
    // while (q->size)
    // {
    //     printf("%p\n", q->front);
    //     if(q->front->player == NULL)
    //     {
    //         printf("%s\n", q->front->enemy->name);
    //     }
    //     else if (q->front->enemy == NULL)
    //     {
    //         printf("%s\n", q->front->player->name);
    //     }

    //     printf("%d\n", q->size);
    //     dequeue(q);
        
    // }
    dequeue(q); 
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);

}


void test02()
{
    srand((unsigned)time(NULL));
    Queue* q = queueInit ();
    
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

    // printf("%s ", enemies[1].name);
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

    printf("%s\n", players[1].name);
    queueTurn (q, &players[1], &enemies[1]);
    fightFlow(q);
}


void test03()
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
                printf("    -%s\n", scenarios[i].decision.options[j].enemies[k]);
            }
        }
    }
    free(scenarios);
    free(jsonString);
}


void test04 ()
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
    for (int i = 0; i < MAX_SKILL; i++)
    {   
        printf("skill %d:\n", (i+1));
        for (int j = 0; j < MAX_DECISION; j++)
        { 
            printf("name: %s\n", players[i].skills[j].name);
            printf("    Description: %s\n", players[i].skills[j].description);
            printf("    type: %d\n", players[i].skills[j].type);
            printf("    duration: %d\n", players[i].skills[j].duration);
            printf("    atk: %d\n", players[i].skills[j].atk);
            printf("    hp: %d\n", players[i].skills[j].hp);
            printf("    def: %d\n", players[i].skills[j].def);
        }       
   }  
}

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
            printf("    type: %d\n", enemies[i].skills[j].type);
            printf("    duration: %d\n", enemies[i].skills[j].duration);
            printf("    atk: %d\n", enemies[i].skills[j].atk);
            printf("    hp: %d\n", enemies[i].skills[j].hp);
            printf("    def: %d\n", enemies[i].skills[j].def);
        }
    }
}

// test graph
void test06 ()
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
    // addEdges(&graph, 0, 1);
    // addEdges(&graph, 0, 2);
    // addEdges(&graph, 0, 3);
    // addEdges(&graph, 1, 0);
    // addEdges(&graph, 1, 2);
    // addEdges(&graph, 1, 3);

    for (int i = 0; i < MAX_SCENARIOS; i++)
    {
        for (int j = 0; j < MAX_SCENARIOS; j++)
        {   if (i != j)
                addEdges(&graph, i, j);
        }
    }
    printGraph (&graph);

}

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
    // addEdges(&graph, 0, 1);
    // addEdges(&graph, 0, 2);
    // addEdges(&graph, 0, 3);
    // addEdges(&graph, 1, 0);
    // addEdges(&graph, 1, 2);
    // addEdges(&graph, 1, 3);

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
