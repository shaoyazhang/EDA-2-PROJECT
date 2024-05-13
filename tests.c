#include "tests.h"

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
    for ( int i = 0; i < NUM_TURNS; i++)
    {
        if (q.front->enemy == NULL)
        {
            printf("%s\n", q.front->player->name);
        }
        else if(q.front->player == NULL)
        {
            printf("%s\n", q.front->enemy->name);
        }

        q.front = q.front->next;
    }
    printf("%d \n", q.size);
    
}



