# include "game.h"
#include "tests.h"

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
    charcter_init(players);
    printf("1. %s\n2. %s\n3. %s\n4. %s\n",
        players[0].name, players[1].name, players[2].name, players[3].name);
    
    // Select character and associate their skills
    int selection;
    printf("Please select your charcter\n");
    scanf("%d", &selection);
    switch (selection)
    {
        case 1:
            printf("Character name: %s\n", players[0].name);
            printf("Skills: \n");
            for (int i = 0; i < MAX_SKILL; i++)
                printf("%d. %s\n", (i+1), players[0].skills[i].name);
            break;
 
        case 2: 
            printf("Character name: %s\n", players[1].name);
            printf("Skills: \n");
            for (int i = 0; i < MAX_SKILL; i++)
                printf("%d. %s\n", (i+1), players[1].skills[i].name);
            break;

        case 3: 
            printf("Character name: %s\n", players[2].name);
            printf("Skills: \n");
            for (int i = 0; i < MAX_SKILL; i++)
                printf("%d. %s\n", (i+1), players[2].skills[i].name);
            break;

        case 4: 
            printf("Character name: %s\n", players[3].name);
            printf("Skills: \n");
            for (int i = 0; i < MAX_SKILL; i++)
                printf("%d. %s\n", (i+1), players[3].skills[i].name);
            break;

        default:
            do
            {
                printf("Wrong option, please select again\n");
                scanf("%d", &selection);
            }while(selection > 4 || selection < 1);    
            break;
    }

}


int main()
{
    # if 0
    Character players[MAX_CHARACTS];
    int input = 0;
    menu();
    do
    {
        printf("Please select: 1 for New game; 0 for Quit game\n");
        scanf("%d", &input);  
        switch(input)
        {
            case 1: 
                game(players);         
                break;
            case 0:
                printf("Exit game\n");  
                break;
            default:
                printf("Wrong option, please select again\n");
                break;
        }
    }while(input);
    # endif
    test02();
    return 0;
}

// ************* DO NOT MODIFY **********//