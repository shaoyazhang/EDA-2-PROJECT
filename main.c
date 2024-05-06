# include "game.h"

// Game start menu
void menu()
{
    printf("**************************\n");
    printf("***** 1. New game ********\n");
    printf("***** 0. Quit game  ******\n");
    printf("**************************\n");
}


int main()
{
    Character players[MAX_CHARACTS];
    int input = 0;
    menu();
    do
    {
        printf("Please select: 1 for New game; 2 for Quit game\n");
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
                printf("Wrong selection, please select again\n");
                break;
        }
    }while(input != 0);

    return 0;
}
