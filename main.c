# include "game.h"
# include "tests.h"
# include "initialization.h"

// ************* DO NOT MODIFY **********//
// ***************** LAB 1 **************//
// Game start menu
void menu()
{
    printf("**************************\n");
    printf("***** 1. New game ********\n");
    printf("***** 0. Quit game  ******\n");
    printf("**************************\n");
}

// New game
void game(Character *players, int* selec)
{   
    const char* fp = "skills.json";
    char* jsonString = readFile (fp);

    if (jsonString == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return;
    }

    //Character* players = NULL;
    // int num_charcter;
    // characterInit(jsonString, &players, &num_charcter);

    // Select character and associate their skills
    // int selection;
    printf("Please select your one charcter:\n1. %s\n2. %s\n3. %s\n4. %s\n", 
        players[0].name, players[1].name, players[2].name, players[3].name);
    scanf("%d", selec);
    switch (*selec)
    {
        case 1:
            printf("Charcter info:\n");
            printf("Character name: %s\n", players[0].name);
            printf("hp: %d\n", players[0].hp);
            printf("atk: %d\n", players[0].atk);
            printf("def: %d\n", players[0].def);
            printf("Skills: \n");
            for (int i = 0; i < MAX_SKILL; i++)
            { 
                printf("Skill %d. %s\n", (i+1), players[0].skills[i].name);
                printf("    Description: %s\n", players[0].skills[i].description);
                printf("    Type: %s\n", players[0].skills->type);
                printf("    Duration: %d\n", players[0].skills->duration);
                printf("    Life points: %d\n", players[0].skills->hp);
                printf("    Attack points: %d\n", players[0].skills->atk);
                printf("    Defense points: %d\n", players[0].skills->def);
            }
            break;
        case 2: 
            printf("Character name: %s\n", players[1].name);
            printf("hp: %d\n", players[1].hp);
            printf("atk: %d\n", players[1].atk);
            printf("def: %d\n", players[1].def);
            printf("Skills: \n");
            for (int i = 0; i < MAX_SKILL; i++)
            {
                printf("Skill %d. %s\n", (i+1), players[1].skills[i].name);
                printf("   Description: %s\n", players[1].skills[i].description);
                printf("   Type: %s\n", players[1].skills->type);
                printf("   Duration: %d\n", players[1].skills->duration);
                printf("   Life points: %d\n", players[1].skills->hp);
                printf("   Attack points: %d\n", players[1].skills->atk);
                printf("   Defense points: %d\n", players[1].skills->def);
            }
            break;

        case 3: 
            printf("Character name: %s\n", players[2].name);
            printf("hp: %d\n", players[2].hp);
            printf("atk: %d\n", players[2].atk);
            printf("def: %d\n", players[2].def);
            printf("Skills: \n");
            for (int i = 0; i < MAX_SKILL; i++)
            {
                printf("Skill %d. %s\n", (i+1), players[2].skills[i].name);
                printf("    Description: %s\n", players[2].skills[i].description);
                printf("    Type: %s\n", players[2].skills->type);
                printf("    Duration: %d\n", players[2].skills->duration);
                printf("    Life points: %d\n", players[2].skills->hp);
                printf("    Attack points: %d\n", players[2].skills->atk);
                printf("    Defense points: %d\n", players[2].skills->def);
            }   
            break;

        case 4: 
            printf("Character name: %s\n", players[3].name);
            printf("hp: %d\n", players[3].hp);
            printf("atk: %d\n", players[3].atk);
            printf("def: %d\n", players[3].def);
            printf("Skills: \n");
            for (int i = 0; i < MAX_SKILL; i++)
            {
                printf("Skill %d. %s\n", (i+1), players[3].skills[i].name);
                printf("    Description: %s\n", players[3].skills[i].description);
                printf("    Type: %s\n", players[3].skills->type);
                printf("    Duration: %d\n", players[3].skills->duration);
                printf("    Life points: %d\n", players[3].skills->hp);
                printf("    Attack points: %d\n", players[3].skills->atk);
                printf("    Defense points: %d\n", players[3].skills->def);
            }
                //printf("%d. %s\n", (i+1), players[3].skills[i].name);
            break;

        default:
            do
            {
                printf("Wrong option, please select again\n");
                scanf("%d", selec);
            }while(*selec > 4 || *selec < 1);    
            break;
    }
    printf("Welcome to the new game!\n");
}

# if 1
int main()
{
    # if 1
    srand((unsigned)time(NULL));
    int selec_charac = -1;

    // *********** Initializations**********//
    // 1. Initialize character
    const char* fp = "skills.json";
    char* jsonString = readFile (fp);
    if (jsonString == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return -1;
    }

    Character* players = NULL;
    int num_characters;
    characterInit(jsonString, &players, &num_characters);

    // 2. Initialize scenarios
    const char* fp_sc = "scenario_config.json";
    char* jsonString_sc = readFile (fp_sc);
    if (jsonString_sc == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return -1;
    }

    Scenario* scenarios = NULL;
    int num_scenarios;
    scenarioInit(jsonString_sc, &scenarios, &num_scenarios);

    // 3. Initialize graph
    Graph* graph = graphInit();
    
    //***************New game**************//
    int input = 0;
    bool continueGame = true;
    menu();
    do
    {
        printf("Please select: 1 for New game; 0 for Quit game\n");
        scanf("%d", &input);  
        switch(input)
        {
            case 1: 
                game(players, &selec_charac);
                int selec;
                printf("Do you want to enter the game?\n 1. YES  2. NO\n");
                scanf("%d", &selec);
                switch (selec)
                {
                    case 1:
                        printf("welcome on board\n");
                        continueGame = false;
                        break;
                    case 2:
                        printf("Go back to Menu\n");
                        break;
                    default:
                        printf("Wrong option\n");
                        break;
                }          
                break;
            case 0:
                printf("Exit game\n"); 
                continueGame = false; 
                exit(0);
            default:
                printf("Wrong option, please select again\n");
                break;
        }
    }while(continueGame);
    
    // *********** Enter the game**********//
    
    //**********Add global path to the graphic**********//
    for (int i = 0; i < num_scenarios; i++) 
    {
        addScenario(graph, scenarios[i]);
    }

    int path01[] ={START_NODE_IDX, 1};  // S1 - S2, S1 is the start node
    int path02[] = {START_NODE_IDX, 2};
    int path03[] ={1, 2};   // S2-S3
    int path04[] ={2, 1};   // S3-S2
    int path05[] ={1, END_NODE_IX}; // S2 -S4, S4 is the end node
    int path06[] ={2, END_NODE_IX}; // S3 -S4
    addEdges(graph, path01[0], path01[1]);
    addEdges(graph, path02[0], path02[1]);
    addEdges(graph, path03[0], path03[1]);
    addEdges(graph, path04[0], path04[1]);
    addEdges(graph, path05[0], path05[1]);
    addEdges(graph, path06[0], path06[1]);

    navigateScenario (graph, 0, players, selec_charac-1);

    // Free all allocated memory spaces
    free(graph);
    // free(players);
    // free(scenarios);
    free(jsonString);
    free(jsonString_sc);
    # endif


    //*******************all tests**************//
    // test01(); 
    // test02();
    // test03();
    // test04();
    // test05();
    // test06();
    // test07();
    // test08();
    return 0;
}

// ************* DO NOT MODIFY **********//

# endif
