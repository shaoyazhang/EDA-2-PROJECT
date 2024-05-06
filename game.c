# include "game.h"

// Initialize charcters
void charcter_init(Character* players)
{
    // Initialize characters' name
    strcpy(players[0].name, "night walker");
    strcpy(players[1].name, "snow flier");
    strcpy(players[2].name, "sword wanderer");
    strcpy(players[3].name, "shadowless");

    // Initialize points
    for ( int i = 0; i < MAX_CHARACTS; i++)
    {
            players[i].atk = 10;
            players[i].def = 10;
            players[i].hp = 10;
    }

    // Initialize skills 
    // Player 1
    strcpy(players[0].skills[0].name, "jump high");
    strcpy(players[0].skills[1].name, "kick");
    strcpy(players[0].skills[2].name, "step back");
    strcpy(players[0].skills[3].name, "punch");

    // Player 2
    strcpy(players[1].skills[0].name, "launch star darts");
    strcpy(players[1].skills[1].name, "kick");
    strcpy(players[1].skills[2].name, "step back");
    strcpy(players[1].skills[3].name, "punch");

    // Player 3
    strcpy(players[2].skills[0].name, "Stab");
    strcpy(players[2].skills[1].name, "kick");
    strcpy(players[2].skills[2].name, "step back");
    strcpy(players[2].skills[3].name, "punch");

    // Player 4
    strcpy(players[3].skills[0].name, "Move fast");
    strcpy(players[3].skills[1].name, "kick");
    strcpy(players[3].skills[2].name, "step back");
    strcpy(players[3].skills[3].name, "punch");

}

// Run game
void game(Character players[])
{   
    // Initialize structures 
    charcter_init(players);
    printf("1. %s\n2. %s\n3. %s\n4. %s\n",
        players[0].name, players[1].name, players[2].name, players[3].name);
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
            printf("Wrong option, please select again\n");
            break;
    }
}