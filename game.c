# include "game.h"
# include "initialization.h"
// ********* LAB 1 ****************//
// ********* DO NOT MODIFY ********//

//*****All the initialized functions moved to initialization.c files*******//

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

# if 1
// Enqueue by turn 50-50 odds
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

// Free queue
void freeQueue(Queue* q) {
    // Traverse the queue and free each node
    while (q->front != NULL) {
        Node* temp = q->front;
        q->front = q->front->next;
        free(temp);
    }

    // After freeing all nodes, set front, rear, and size to NULL/0
    q->rear = NULL;
    q->size = 0;
}


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
            player->atk += player->skills[playerSkillIdx].atk;
            player->def += player->skills[playerSkillIdx].def;
            player->hp += player->skills[playerSkillIdx].hp;
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
bool fightFlow (Queue* q, Character player, Enemy enemy)
{
    printf("Player HP: %d, ATK: %d, DEF: %d\n", player.hp, player.atk, player.def);
    printf("Enemy HP: %d, ATK: %d, DEF: %d\n", enemy.hp, enemy.atk, enemy.def);
    printf("\n");
    HashTable* ht = createHashTable();
    while (!isEmpty(q))
    {
        int turnIdx = -1;
        if (strcmp(q->front->name, "player") == 0)
        {
            printf("Your turn, please select skill:\n" );

            turnIdx = 1;
            int playerInput;
            bool validInput = false;  
            // while loop to make sure player can reselect in case of invalid selection
            while (!validInput) 
            {
                printCharacterSkill(&player);
                scanf("%d", &playerInput);
                playerInput--; // to match array index

                // It is a valid option only if it is a "Direct attack",
                // or "Temporary modifier" type's durations is greater than 0
                if (playerInput >= 0 && playerInput < MAX_SKILL &&
                    (strcmp(player.skills[playerInput].type, "Direct attack") == 0 || 
                    (strcmp(player.skills[playerInput].type, "Temporary modifier") == 0 && 
                    player.skills[playerInput].duration > 0))) 
                {
                    applySkill(&player, &enemy, playerInput, -1, turnIdx);
                    incrementSkillCount(ht, player.skills[playerInput].name);
                    validInput = true;
                } else {
                    printf("Invalid skill or skill duration is 0. Please select again.\n");
                }
            }     
            
        }
        else if (strcmp(q->front->name, "enemy") ==0)
        {
            printf("Enemy's turn: ");
            turnIdx = 2;

            // Control of available skills in case of temporary modifier
            int availableSkills[MAX_SKILL];
            int availableSkillCount = 0; 
            for (int i = 0; i < MAX_SKILL; i++) {
                if (enemy.skills[i].duration > 0) {
                    availableSkills[availableSkillCount++] = i;
                }
            }

            // Collect available skills
            for (int i = 0; i < MAX_SKILL; i++) 
            {
                if (strcmp(enemy.skills[i].type, "Direct attack") == 0 || (strcmp(enemy.skills[i].type, "Temporary modifier") == 0
                    && enemy.skills[i].duration > 0)) 
                {
                    availableSkills[availableSkillCount++] = i;
                }
            }

            if (availableSkillCount > 0) 
            {
                int skillIdx = availableSkills[rand() % availableSkillCount];
                printf("%s\n", enemy.skills[skillIdx].name);
                applySkill(&player, &enemy, -1, skillIdx, turnIdx);
                incrementSkillCount(ht, enemy.skills[skillIdx].name);
            } 
            else 
            {
                printf("Enemy has no available skills to use.\n");
            }
        }

        dequeue (q);
        printf("\n");
        printf("Player HP: %d, ATK: %d, DEF: %d\n", player.hp, player.atk, player.def);
        printf("Enemy HP: %d, ATK: %d, DEF: %d\n", enemy.hp, enemy.atk, enemy.def);
        printf("\n");
        // check if player wins or looses
        int result = winAllBattles(&player, &enemy);
        if (result == 1) 
        {
            printSkillCounts(ht);
            freeHashTable(ht);
            return true; // return true if player wins      
        }
        // 
        else if(result == 0) 
        {
            printSkillCounts(ht);
            freeHashTable(ht);
            return false; // return false if player looses          
        }        
    }
    printSkillCounts(ht);
    freeHashTable(ht);
    printf("Fight turns are over, you need to restart the fight again\n");
    return false;
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
    for (int i = 0; strlen(enemy->skills[i].name) >0; i++)
    {
        printf("Skill %d: %s\n", i+1, enemy->skills[i].name);
        printf("    Skill detail: %s\n", enemy->skills[i].description);
        printf("    Type: %s\n", enemy->skills[i].type);
        printf("    Duration: %d\n", enemy->skills[i].duration);
        printf("    Life points: %d\n", enemy->skills[i].hp);
        printf("    Attack points: %d\n", enemy->skills[i].atk);
        printf("    Defense points: %d\n", enemy->skills[i].def);
    }
}

// 8. Hash table system
// Hash value
int hash(const char* skillName) {
    unsigned int hashValue = 0;
    while (*skillName) {
        hashValue = (hashValue << 5) + *skillName++;
    }
    return hashValue % TABLE_SIZE;
}


// Initialize hash table
HashTable* createHashTable() 
{
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Count system
void incrementSkillCount(HashTable* ht, const char* skillName) 
{
    unsigned int index = hash(skillName);
    SkillCount* entry = ht->table[index];
    SkillCount* prev = NULL;

    // Search for the skill name in the linked list
    while (entry != NULL) 
    {
        if (strcmp(entry->skillName, skillName) == 0) {
            // If found, increment the count and return
            entry->count++;
            return;
        }
        prev = entry;
        entry = entry->next;
    }

    // If the skill name is not found, create a new node
    SkillCount* newEntry = (SkillCount*)malloc(sizeof(SkillCount));
    if (newEntry == NULL) {
        // Handle memory allocation failure
        return;
    }
    strcpy(newEntry->skillName, skillName);
    newEntry->count = 1;
    newEntry->next = NULL;

    // Insert the new node at the beginning of the linked list
    if (prev == NULL) {
        ht->table[index] = newEntry;  // Update the head of the list
    } else {
        prev->next = newEntry;         // Insert after the previous node
    }
}

// Print table
void printSkillCounts(HashTable* ht) 
{
    printf("Skill usage stats:\n");
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        SkillCount* entry = ht->table[i];
        while (entry != NULL) {
            printf("Skill: %s, Count: %d\n", entry->skillName, entry->count);
            entry = entry->next;

        }
    }
}

// free hash table
void freeHashTable(HashTable* ht) 
{
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        SkillCount* entry = ht->table[i];
        while (entry != NULL) 
        {
            SkillCount* tmp = entry;
            entry = entry->next;
            free(tmp);
        }
    }
    free(ht);
}
// ********* DO NOT MODIFY ********//

