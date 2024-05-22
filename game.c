# include "game.h"
# include "initialization.h"
// ********* LAB 1 ****************//
// ********* DO NOT MODIFY ********//

// Initialize charcters ---> function updated and cancelled
# if 0
void charcter_init(Character* players)
{   
    players = (Character*)realloc(players, sizeof(Character) * MAX_CHARACTS); 
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
    strcpy(players[0].skills[1].name, "high kick");
    strcpy(players[0].skills[2].name, "step back");
    strcpy(players[0].skills[3].name, "punch");

    // Player 2
    strcpy(players[1].skills[0].name, "launch star darts");
    strcpy(players[1].skills[1].name, "shielding");
    strcpy(players[1].skills[2].name, "step back");
    strcpy(players[1].skills[3].name, "roundhouse kick");

    // Player 3
    strcpy(players[2].skills[0].name, "stab");
    strcpy(players[2].skills[1].name, "wrestle");
    strcpy(players[2].skills[2].name, "step back");
    strcpy(players[2].skills[3].name, "punch");

    // Player 4
    strcpy(players[3].skills[0].name, "Move fast");
    strcpy(players[3].skills[1].name, "sneak attack");
    strcpy(players[3].skills[2].name, "step back");
    strcpy(players[3].skills[3].name, "punch");

}
# endif

// ********* DO NOT MODIFY ********//



// ************ LAB 2 *************//
// ********* DO NOT MODIFY ********//

// Show character's skill attributions
void printCharacterSkill (Character* player)
{
    printf("skill:\n1. %s\n2. %s\n3. %s\n4. %s\n", 
    player->skills[0].name,
    player->skills[1].name,
    player->skills[2].name,
    player->skills[3].name
    );
}

// Show enemy's skill attributions
void printEnemySkill (Enemy* enemy)
{
    printf("skill:\n1. %s\n2. %s\n3. %s\n4. %s\n",
    enemy->skills[0].name,
    enemy->skills[1].name,
    enemy->skills[2].name,
    enemy->skills[3].name
    );

}

// Initialize queue
Queue* queueInit ()
{   
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->front = newQueue->rear = NULL;
    newQueue->size = 0;
    return newQueue;
}

// 2. chek if queue is empty
int isEmpty (Queue* q)
{
    return (q->size == 0);
}

# if 0
// 3.1 Enque Character  ---> function cancelled
void enqueueCharacter (Queue* q, Character* player)
{
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->player = player;
    newNode->enemy = NULL;
    newNode->next = NULL;

    if (q->front == NULL)
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}
# endif

# if 0
// 3.2 Enque Enemy  ---> function cancelled
void enqueueEnemy (Queue* q, Enemy* enemy)
{
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->player = NULL;
    newNode->enemy = enemy;
    newNode->next = NULL;
    //
    if (q->rear == NULL)
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    
    q->size++;
}
# endif

// 3. Enqueue 
void enqueue (Queue* q, const char* name) // name is either "player" or "enemy"
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    if (q->rear == NULL && q->front == NULL)
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;

    } 
    q->size++;
    return;
}

// 4. Dequeue
void dequeue (Queue* q)
{
    if (isEmpty(q))
    {
        printf("No more turns\n");
        return;
    }
    
    Node* tmp = q->front;
    q->front = q->front->next;
    q->size--;
  
    // If front is NULL, change rear to NULL too
    if (q->front == NULL)
        q->rear = NULL;
    free(tmp);
    tmp = NULL;
}



# if 0
// 5. Generate queue-based turn   ---> function cancelled
void queueTurn (Queue* q, Character* player, Enemy* enemies)
{
    for ( int i = 0; i < NUM_TURNS; i++)
    {
        int ret = rand () % 2;
        if (ret == 0)
        {
            enqueueCharacter (q, player);
        }
        else if (ret == 1)
        {   
            enqueueEnemy (q, enemies);
        }
    }    
}

# endif

// 5. Function to make character and enemy apply their skills and update their points
void applySkill (Character* player, Enemy* enemy, int playerSkillIdx, int pcSkillIdx, int turnIdx)
{
    if (turnIdx == 1) // players turn
    {
        // update points after player applies a skill
        if (strcmp(player->skills[playerSkillIdx].type, "Direct attack") == 0)
        {
            // if it is a direct attack, we update enemy's points
            enemy->hp += player->skills[playerSkillIdx].hp;
            enemy->atk += player->skills[playerSkillIdx].atk;
            enemy->def += player->skills[playerSkillIdx].def;
        }
        else if ((strcmp(player->skills[playerSkillIdx].type, "Temporary modifier") == 0) &&
            player->skills[playerSkillIdx].duration)
        {
            // if it is a temporary modifier, we update player's points
            player->skills[playerSkillIdx].duration--;
            player->atk = player->skills[playerSkillIdx].atk;
            player->def = player->skills[playerSkillIdx].def;
            player->hp = player->skills[playerSkillIdx].hp;
        }
    }
    else if (turnIdx == 2) // enemy's turn
    {
        // update points after enemy applies a skill
        if (strcmp(enemy->skills[pcSkillIdx].type, "Direct attack") == 0)
        {   
            // if it is a direct attack, we update player's points 
            player->atk += enemy->skills[pcSkillIdx].atk; 
            player->def += enemy->skills[pcSkillIdx].def;
            player->hp += enemy->skills[pcSkillIdx].hp;
        }
        else if (strcmp(enemy->skills[pcSkillIdx].type, "Temporary modifier") == 0 &&
            enemy->skills[pcSkillIdx].duration > 0)
        {
            // if it is a temporary modifier, we update enemy's points
            
            enemy->atk += enemy->skills[pcSkillIdx].atk;
            enemy->def += enemy->skills[pcSkillIdx].def;
            enemy->hp += enemy->skills[pcSkillIdx].hp;
        }
    }
}

# if 0
// 6. Fight flow ---> cancelled
// void fightFlow (Queue* q)
// {
//     if (isEmpty(q))
//     {
//         printf("Combat turns are over\n");
//         return;
//     }

//     if (q->front->enemy == NULL)
//     {
//         printf("Your turn, please select skill:\n" );
//         printCharacterSkill (q->front->player);
//         int playerInput;
//         scanf ("%d", &playerInput);
//         switch (playerInput)
//         {
//             case 1:
//                 applySkill (q->front->player, , playerInput, turnIdx)
//         }
            
//     }
//     else if (q->front->player == NULL)
//     {
//         printf("Select skill:\n" );
//         printEnemySkill (q->front->enemy);
//         dequeue (q);
//         return;
//     }
//     dequeue (q);
//     return;
// }
# endif

// 6. Fight flow design
void fightFlow (Queue* q, Character* player, Enemy* enemy)
{
    if (isEmpty(q))
    {
        printf("Combat turns are over\n");
        return;
    }
    int turnIdx = -1;
    if (strcmp(q->front->name, "player"))
    {
        printf("Your turn, please select skill:\n" );
        printCharacterSkill (player);
        turnIdx = 1;
        int playerInput;
        scanf ("%d", &playerInput);

        // Added while condition in case player inputs wrong number
        // so they can select again
        while (playerInput < 1 || playerInput > MAX_SKILL)
        {
            printf("Invalid option, please select again\n");
            scanf ("%d", &playerInput);
        } 
        // Apply skill according to the option of player  
        applySkill(player, enemy, playerInput - 1, -1, turnIdx);       
    }
    else if (strcmp(q->front->name, "enemy"))
    {
        printf("Enemy's turn:\n");
        // printCharacterSkill (player->skills);
        turnIdx = 2;
        int enemyInput = rand() % MAX_SKILL; 
        printf("%s\n", enemy->skills[enemyInput].name);     
        applySkill (player, enemy, -1, enemyInput, turnIdx);
    }
    dequeue (q);
    return;
}

// 7. Print enemy skill's details
void printEnemySkillDetail (Enemy* enemy)
{
    if (enemy == NULL) {
        printf("Enemy not found.\n");
        return;
    }

    printf("Name: %s\n", enemy->name);
    printf("Life points: %d\n", enemy->hp);
    printf("Attack points: %d\n", enemy->atk);
    printf("Defense points: %d\n", enemy->def);
    for (int i = 0; i < MAX_SKILL; i++)
    {
        printf("Skill %d: %s\n", i+1, enemy->skills[0].name);
        printf("    Skill detail: %s\n", enemy->skills[0].description);
        printf("    Type: %s\n", enemy->skills[0].type);
        printf("    Duration: %d\n", enemy->skills[0].duration);
        printf("    Life points: %d\n", enemy->skills[0].hp);
        printf("    Attack points: %d\n", enemy->skills[0].atk);
        printf("    Defense points: %d\n", enemy->skills[0].def);
    }
}
// ********* DO NOT MODIFY ********//

