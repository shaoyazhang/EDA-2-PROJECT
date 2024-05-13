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


// ********* DO NOT MODIFY ********//

// ********* LAB 1 ****************//
// ********* DO NOT MODIFY ********//

// 1. Initialize queue
void queueInit (Queue* q)
{
    q->front = q->rear = NULL;
    q->size = 0;
}

// 2. chek if queue is empty
int isEmpty (Queue* q)
{
    return q->size == 0;
}


// 3. Enqueue
void enqueue (Queue* q, void* rol)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->rol = rol;
    newNode->next = NULL;

    if (isEmpty(q))
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
    else
    {
        Node* tmp = q->front;
        q->front = q->front->next;
        free(tmp);
        tmp = NULL;
        q->size--;
    }
}


// 5. Generate queue-based turn
void queueTurn (Queue* q, Character* player, Enemy* enemies)
{
    for ( int i = 0; i < NUM_TURNS; i++)
    {
        int ret = rand () % 2;
        if (ret == 0)
        {
            enqueue (q, player);
        }
        else 
        {
            enqueue (q, enemies);
        }
    }    
}

void test01()
{
    srand((unsigned)time(NULL));
    Queue q;
    queueInit(&q);

    Skill playerSkills[4] = {
        {"skill 1", "skill 1", 0, 0, 0, 0, 0},
        {"skill 2", "skill 2", 0, 0, 0, 0, 0},

    };

    Character player = {"Player", 100, 20, 10, {playerSkills[0],playerSkills[1], playerSkills[2], playerSkills[3]}};

    Skill enemySkills[4] = {
       {"Eskill 1", "Eskill 1", 0, 0, 0, 0, 0},
        {"Eskill 2", "Eskill 2", 0, 0, 0, 0, 0},
    };
    Enemy enemy = {"Enemy", 30, 50, 5, {enemySkills[0], enemySkills[1], enemySkills[2], enemySkills[3]}};
    queueTurn (&q, &player, &enemy);
    queueTurn (&q, &player, &enemy);
    queueTurn (&q, &player, &enemy);
    queueTurn (&q, &player, &enemy);
    printf("%s ", q.front->rol);
    printf("%s ", q.rear->next->rol);
}