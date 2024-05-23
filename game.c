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
    for (int i = 0; i < MAX_SKILL; i++) 
    {
        if ((player->skills[i].duration > 0 && strcmp(player->skills[i].type, "Temporary modifier") == 0) ||
            strcmp(player->skills[i].type, "Direct attack") == 0) 
        { // Make sure only the available skills are printed
            printf("%d. %s \n", i + 1, player->skills[i].name);
        }
    }
    
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
// void initQueue(Queue* q) {
//     q->front = NULL;
//     q->rear = NULL;
//     q->size = 0;
// }
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
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(newNode->name, name);
    newNode->next = NULL;
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

// Enqueue by turn 50-50 odds
# if 1
void enqueueTurns(Queue* q) {
 
    for ( int i = 0; i < MAX_BATTLE_TURNS; i++)
    {
        int ret = rand () % 2;
        if (ret == 0)
        {
            enqueue(q, "player");
        }
        else if (ret == 1)
        {   
            enqueue(q, "enemy");
        } 
    }
    printf("%d\n", q->size);
}
# endif


// Print queue
void printQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    
    Node* current = q->front;
    printf("Queue: ");
    while (current != NULL) {
        printf("%s ", current->name);
        current = current->next;
    }
    printf("\n");
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
            player->skills[playerSkillIdx].duration >0)
        {
            // if it is a temporary modifier, we update player's points
            player->atk = player->skills[playerSkillIdx].atk;
            player->def = player->skills[playerSkillIdx].def;
            player->hp = player->skills[playerSkillIdx].hp;
            player->skills[playerSkillIdx].duration--;
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
            enemy->skills[pcSkillIdx].duration--;
        }
    }
}

// 6. Fight flow design
# if 1
bool fightFlow (Queue* q, Character* player, Enemy* enemy)
{
    while (!isEmpty(q))
    {
        int turnIdx = -1;
        if (strcmp(q->front->name, "player") == 0)
        {
            printf("Your turn, please select skill:\n" );

            turnIdx = 1;
            int playerInput;
            bool validInput = false; // 
            // while loop to make sure player can reselect in case of invalid selection
            while (!validInput) {
                printCharacterSkill(player);
                scanf("%d", &playerInput);
                playerInput--; // to match array index

                if (playerInput >= 0 && playerInput < MAX_SKILL &&
                    (strcmp(player->skills[playerInput].type, "Direct attack") == 0 || 
                    (strcmp(player->skills[playerInput].type, "Temporary modifier") == 0 && 
                    player->skills[playerInput].duration > 0))) 
                {
                    applySkill(player, enemy, playerInput, -1, turnIdx);
                    validInput = true;
                } else {
                    printf("Invalid skill or skill duration is 0. Please select again.\n");
                }
            }     
            
        }
        else if (strcmp(q->front->name, "enemy") ==0)
        {
            printf("Enemy's turn:\n");
            // printCharacterSkill (player->skills);
            turnIdx = 2;

            // Control of available skills in case of temporary
            int availableSkills[MAX_SKILL];
            int availableSkillCount = 0; 
            for (int i = 0; i < MAX_SKILL; i++) {
                if (enemy->skills[i].duration > 0) {
                    availableSkills[availableSkillCount++] = i;
                }
            }

            // Collect available skills
            for (int i = 0; i < MAX_SKILL; i++) 
            {
                if (strcmp(enemy->skills[i].type, "Direct attack") == 0 || (strcmp(enemy->skills[i].type, "Temporary modifier") == 0
                    && enemy->skills[i].duration > 0)) 
                {
                    availableSkills[availableSkillCount++] = i;
                }
            }

            if (availableSkillCount > 0) 
            {
                int skillIdx = availableSkills[rand() % availableSkillCount];
                printf("%s\n", enemy->skills[skillIdx].name);
                applySkill(player, enemy, -1, skillIdx, turnIdx);
            } 
            else 
            {
                printf("Enemy has no available skills to use.\n");
            }
        }
    

        // check if player wins or looses
        if (winAllBattles(player, enemy)) 
        {
            return true; // return true if player wins 
        }
        dequeue (q);
    }
    return false; // return false if player looses
}
# endif
# if 0
bool fightFlow(Queue* q, Character* player, Enemy* enemy) {
    while (!isEmpty(q)) 
    {
        int turnIdx = -1;
        if (strcmp(q->front->name, "player") == 0) {
            printf("Your turn, please select skill:\n");

            turnIdx = 1;
            int playerInput;
            bool validInput = false; 
            // while loop to make sure player can reselect in case of invalid selection
            while (!validInput) {
                printCharacterSkill(player);
                scanf("%d", &playerInput);
                playerInput--; // to match array index

                if (playerInput >= 0 && playerInput < MAX_SKILL &&
                    (strcmp(player->skills[playerInput].type, "Direct attack") == 0 || 
                    (strcmp(player->skills[playerInput].type, "Temporary modifier") == 0 && 
                    player->skills[playerInput].duration > 0))) {
                    applySkill(player, enemy, playerInput, -1, turnIdx);
                    validInput = true;
                } else {
                    printf("Invalid skill or skill duration is 0. Please select again.\n");
                }
            }

        } else if (strcmp(q->front->name, "enemy") == 0) {
            printf("Enemy's turn:\n");
            turnIdx = 2;

            // Collect available skills
            int availableSkills[MAX_SKILL];
            int availableSkillCount = 0;
            for (int i = 0; i < MAX_SKILL; i++) {
                if (strcmp(enemy->skills[i].type, "Direct attack") == 0 || 
                    (strcmp(enemy->skills[i].type, "Temporary modifier") == 0 && 
                    enemy->skills[i].duration > 0)) {
                    availableSkills[availableSkillCount++] = i;
                }
            }

            if (availableSkillCount > 0) {
                int skillIdx = availableSkills[rand() % availableSkillCount];
                printf("%s\n", enemy->skills[skillIdx].name);
                applySkill(player, enemy, -1, skillIdx, turnIdx);
            } else {
                printf("Enemy has no available skills to use.\n");
            }
        }

        // Check if player wins or loses
        if (winAllBattles(player, enemy)) {
            return true; // return true if player wins 
        } else if (player->hp <= 0) {
            printf("You lost the battle. Game over.\n");
            return false; // return false if player loses
        }

        dequeue(q);
    }
    printf("Battle over\n");
    return false; // return false if the queue is empty (end of fight)
}
# endif
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

