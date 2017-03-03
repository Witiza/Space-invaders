#include "Declarations.h"

Player* newPlayer(char* name)
{
    //TODO
	
	Player* newplayer = (Player*)malloc(sizeof(Player));

	int lenght = strlen(name);
	newplayer->name = (char*)malloc(sizeof(char)*(lenght+1));
	for (int i = 0; i <= lenght; i++)
	{
		newplayer->name[i] = *name;
		name++;
	}
	newplayer->lives = 3;
	newplayer->score = 0;
	newplayer->yPosition = 0;
	newplayer->bullets = (Bullet*)malloc(sizeof(Bullet)*NUM_SHOTS);
	for (int i = 0; i < NUM_SHOTS; i++)
	{
		newplayer->bullets[i].shot = false;
		newplayer->bullets[i].pos.x = 0;
		newplayer->bullets[i].pos.y = 0;
	}
	
	
	return newplayer;
}

void deletePlayer(Player* mPlayer)
{
    //TODO
	free(mPlayer->name);
	free(mPlayer->bullets);
	free(mPlayer);

}

void movePlayerUp(Player* mPlayer)
{
    //TODO
	if (mPlayer->yPosition > 0)
	{
		mPlayer->yPosition--;
	}
}

void movePlayerDown(Player* mPlayer)
{
    //TODO
	mPlayer->yPosition++;
	if (mPlayer->yPosition > 9)
	{
		mPlayer->yPosition = 9;
	}
}

void newShoot(Player* mPlayer)
{
    //TODO
	bool flag = false;
	for (int i = 0; i < NUM_SHOTS && flag == false; i++)
	{
		if (mPlayer->bullets[i].shot == false)
		{
			mPlayer->bullets[i].shot = true;
			mPlayer->bullets[i].pos.x = 1;
			mPlayer->bullets[i].pos.y = mPlayer->yPosition ;
			flag = true;
		}
		
}
	
}

void updateBulletsPositions(Player* mPlayer)
{
    //TODO
	for (int i = 0; i < NUM_SHOTS; i++)
	{
		if (mPlayer->bullets[i].shot == true)
		{
			mPlayer->bullets[i].pos.x ++;
			if (mPlayer->bullets[i].pos.x > 59)
			{
				mPlayer->bullets[i].shot = false;
			}
		}
	}
}

Enemy* newEnemy()
{
    //TODO
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	enemy->pos.y = rand() % 9;
	enemy->pos.x = 58;
    return enemy;
}

void deleteEnemy(Enemy* mEnemy)
{
    //TODO
	free(mEnemy);
}

void updateEnemyPosition(Enemy* mEnemy)
{
    //TODO
	mEnemy->pos.x--;
	if (mEnemy->pos.x < 0)
	{
		mEnemy->pos.x = 0;
	}
}

bool checkEnemyHit(Enemy* mEnemy)
{
    //TODO
	if (mEnemy->pos.x == 0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}