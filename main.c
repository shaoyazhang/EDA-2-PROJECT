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

// Run game
void game(Character *players)
{   
    // Initialize Character structures 
    // charcter_init(players);
    // printf("1. %s\n2. %s\n3. %s\n4. %s\n",
    //     players[0].name, players[1].name, players[2].name, players[3].name);

    const char* fp = "skills.json";
    char* jsonString = readFile (fp);

    if (jsonString == NULL)
    {
        fprintf(stderr, "Failed to read JSON file\n");
        return;
    }

    //Character* players = NULL;
    int num_charcter;
    characterInit(jsonString, &players, &num_charcter);

    // Select character and associate their skills
    int selection;
    printf("Please select your one charcter:\n1. %s\n2. %s\n3. %s\n4. %s\n", 
        players[0].name, players[1].name, players[2].name, players[3].name);
    scanf("%d", &selection);
    switch (selection)
    {
        case 1:
            printf("Charcter info:\n");
            printf("Character name: %s\n", players[0].name);
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
                scanf("%d", &selection);
            }while(selection > 4 || selection < 1);    
            break;
    }
    printf("Welcome to the new game!\n");
}


int main()
{
    # if 0
    Character players[MAX_CHARACTS];
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
                game(players);
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
                break;
            default:
                printf("Wrong option, please select again\n");
                break;
        }
    }while(continueGame);
    # endif

    // test01(); // test queue 
    // test02();
    // test03();
    test04();
    // test05();
    // test06 ();
    // test07 ();
    // test08();
    return 0;
}

// ************* DO NOT MODIFY **********//