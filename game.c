# include "game.h"


// ********* LAB 1 ****************//
// ********* DO NOT MODIFY ********//

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

void enemy_init(Enemy* enemies)
{
    // Initialize enemies' names
    strcpy(enemies[0].name, "Rock-troll"); // first scenario
    strcpy(enemies[1].name, "Stone_guardian"); // second scenario
    strcpy(enemies[2].name, "Rock_Golem"); // third scenario
    strcpy(enemies[3].name, "water_wizard"); // fourth scenario

    // Initialize points
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].atk = 10; // es un ejemplo
        enemies[i].def = 10; // ejemplo
        enemies[i].hp = 10;  // ejemplo
    }

    // Initialize skills for each enemy
    // Enemy 1
    strcpy(enemies[0].skills[0].name, "Bite");
    strcpy(enemies[0].skills[1].name, "Scratch");
    strcpy(enemies[0].skills[2].name, "Charge");
    strcpy(enemies[0].skills[3].name, "Roar");

    // Enemy 2
    strcpy(enemies[1].skills[0].name, "Axe Swing");
    strcpy(enemies[1].skills[1].name, "Smash");
    strcpy(enemies[1].skills[2].name, "Fury");
    strcpy(enemies[1].skills[3].name, "Rage");

    // Enemy 3
    strcpy(enemies[2].skills[0].name, "Dark Slash");
    strcpy(enemies[2].skills[1].name, "Shadow Strike");
    strcpy(enemies[2].skills[2].name, "Guard Break");
    strcpy(enemies[2].skills[3].name, "Sword Slam");

    // Enemy 4
    strcpy(enemies[3].skills[0].name, "Fire Breath");
    strcpy(enemies[3].skills[1].name, "Tail Swipe");
    strcpy(enemies[3].skills[2].name, "Wing Gust");
    strcpy(enemies[3].skills[3].name, "Dragon Roar");
}

// ********* DO NOT MODIFY ********//

// ********* LAB 1 ****************//
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

// 1. Initialize queue

// void queueInit (Queue* q)
// {
//     q->front = q->rear = NULL;
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

// 3. Enqueue
// void enqueue (Queue* q, void* rol)
// {
    
//     Node* newNode = (Node*)malloc(sizeof(Node));
//     newNode->rol = rol;
//     newNode->next = NULL;

//     if (isEmpty(q))
//     {
//         q->front = newNode;
//         q->rear = newNode;
//     }
//     else
//     {
//         q->rear->next = newNode;
//         q->rear = newNode;
//     }
//     q->size++;
// }

// 3.1 Enque Character
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


// 3.2 Enque Enemy
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


// 5. Generate queue-based turn 
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

// 6. Fight flow
void fightFlow (Queue* q)
{
    if (isEmpty(q))
    {
        printf("Combat turns are over\n");
        return;
    }

    if (q->front->enemy == NULL)
    {
        printf("Select skill:\n" );
        printCharacterSkill (q->front->player);
        dequeue (q);  
        return;          
    }
    else if (q->front->player == NULL)
    {
        printf("Select skill:\n" );
        printEnemySkill (q->front->enemy);
        dequeue (q);
        return;
    }
}

// ********* DO NOT MODIFY ********//