#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_
#include<time.h>
#include <iostream>
using namespace std;

#define NUM_SHOTS 10

/**Struct that represents an integer vector 2D.*/
struct Vector2D
{
    int     x;
    int     y;
};

/**Struct that represent a bullet.*/
struct Bullet {
    /**Boolean that indicates if this bullet has been shot.*/
    bool     shot;
    Vector2D pos;
};

/**Struct that represents a player.*/
struct Player
{
	char*       name;
    int         lives;
    int         score;
    int         yPosition;
    Bullet*     bullets;
};

/**Struct that represents an enemy.*/
struct Enemy
{
    Vector2D    pos;
};

/**
 *  Method to create a new player. The new player
 *  will be initialized with 3 lives, at position 0,
 *  with an array of NUM_SHOTS Bullets and a score of 0.
 *  The Bullets have to be initialized with the variable 
 *  shot set to false.
 *  @param  name    Name of the new player.
 *  @return New created player.
 */
Player* newPlayer(char* name);

/**
 *  Method to delete Player.
 *  @param  mPlayer Player to delete. 
 */
void deletePlayer(Player* mPlayer);

/**
 *  Method to move the player one position up. 
 *  Tip: It cannot have a negative position!
 *  @param  mPlayer Player to move.
 */
void movePlayerUp(Player* mPlayer);

/**
 *  Method to move the player one position down. 
 *  Tip: It cannot have a position greater than 9!
 *  @param  mPlayer Player to move.
 */
void movePlayerDown(Player* mPlayer);

/**
 *  Method to shoot a bullet. 
 *  Tip: You have to find a free bullet (one
 *  that has the shot variable with a value equal to
 *  false). If there are not free bullets, do not do anything.
 *  If you find a free bullet set the shot variable to true 
 *  and initilize it at the position of the player.
 *  @param  mPlayer Player that shoots.
 */
void newShoot(Player* mPlayer);

/**
 *  Method to update the position of the bullets. Since the bullets
 *  move from left to right, the x position of the bullet should
 *  increment by one. If the bullet arrives at the end of the board (60),
 *  it is marked again as a free bullet.
 *  @param  mPlayer Player owner of the bullets.
 */
void updateBulletsPositions(Player* mPlayer);

/**
 *  Method to create a new enemy at a random position.
 *  Tip: The position x has to be 59 and the y a random value.
 *  @return New enemy.
 */
Enemy* newEnemy();

/**
 *  Method to delete an enemy.
 */
void deleteEnemy(Enemy* mEnemy);

/**
 *  Method to update the position of the enemies. Since the enemies
 *  move from right to left, the x position of the bullet should
 *  decrement by one.
 *  @param  mEnemy  Enemy to update.
 */
void updateEnemyPosition(Enemy* mEnemy);

/**
 *  Method to check if an enemy hit the first column of the board (position 0).
 *  @param  mEnemy  Enemy.
 *  @return TRUE if the enemy hit the player.
 */
bool checkEnemyHit(Enemy* mEnemy);

#endif