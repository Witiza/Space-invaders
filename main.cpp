#include "Declarations.h"
#include<time.h>
#include <windows.h>
#include <vector>
using namespace std;

vector<Enemy*> mEnemies;
vector<Vector2D> mExplosions;

unsigned int elapsedFrames = 0;
unsigned int elapsedFramesSinceLastShot = 0;

void initFrame()
{
    mExplosions.clear();
}

void checkInput(Player* mPlayer)
{
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        movePlayerUp(mPlayer);
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        movePlayerDown(mPlayer);
    }

    if (GetKeyState(VK_SPACE) & 0x8000)
    {
        if (elapsedFramesSinceLastShot > 5) {
            newShoot(mPlayer);
            elapsedFramesSinceLastShot = 0;
        }
    }
}

bool checkBulletEnemyHit(Player* mPlayer, Enemy* mEnemy)
{
    bool result = false;
    for (int i = 0; i < NUM_SHOTS; ++i)
    {
        if (mPlayer->bullets[i].shot) {
            if (mPlayer->bullets[i].pos.y == mEnemy->pos.y) {
                int difference = mEnemy->pos.x - mPlayer->bullets[i].pos.x;
                if (difference < 3 && difference > 0) {
                    mPlayer->bullets[i].shot = false;
                    result = true;
                }
            }
        }
    }
    return result;
}

void updateState(Player* mPlayer)
{
    //Create enemy.
    elapsedFramesSinceLastShot += 1;
    elapsedFrames += 1;
    if (elapsedFrames > 12) {
        Enemy* mEnem = newEnemy();
        if (mEnem) {
            mEnemies.push_back(mEnem);
        }
        elapsedFrames = 0;
    }

    //Check for bullet-enemy hits
    int offset = 0;
    for (int i = 0; i < mEnemies.size(); ++i)
    {
        mEnemies[i - offset] = mEnemies[i];
        if (checkBulletEnemyHit(mPlayer, mEnemies[i])) {
            mExplosions.push_back(mEnemies[i]->pos);
            deleteEnemy(mEnemies[i]);
            offset++;
            mPlayer->score += 5;
        }
    }
    while (offset) {
        mEnemies.pop_back();
        offset--;
    }

    //Update Bullets positions.
    updateBulletsPositions(mPlayer);

    //Update enemies position
    offset = 0;
    for (int i = 0; i < mEnemies.size(); ++i)
    {
        mEnemies[i - offset] = mEnemies[i];
        updateEnemyPosition(mEnemies[i]);
        if (mEnemies[i]->pos.x < 0) {
            deleteEnemy(mEnemies[i]);
            offset++;
        }
    }
    while (offset) {
        mEnemies.pop_back();
        offset--;
    }

    //Check for player-enemy hits
    offset = 0;
    for (int i = 0; i < mEnemies.size(); ++i)
    {
        mEnemies[i - offset] = mEnemies[i];
        if (checkEnemyHit(mEnemies[i])) {
            mExplosions.push_back(mEnemies[i]->pos);
            deleteEnemy(mEnemies[i]);
            mPlayer->lives -= 1;
            offset++;
        }
    }
    while (offset) {
        mEnemies.pop_back();
        offset--;
    }
}

void clearScreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void printBoard(Player* mPlayer)
{
    //Clear console.
    clearScreen();

    //Paint top border
    char border[63];
    memset(border, 61, sizeof(char) * 63);
    border[62] = '\0';
    cout << border << endl;

    //Fill the board.
    char board[10][60];
    memset(board, 32, sizeof(char) * 10*60);

    //Fill the player position.
    board[mPlayer->yPosition][0] = '@';
    
    //Fill the bullets.
    for (int i = 0; i < NUM_SHOTS; ++i)
    {
        if (mPlayer->bullets[i].shot) {
            board[mPlayer->bullets[i].pos.y][mPlayer->bullets[i].pos.x] = '>';
        }
    }

    //Fill the enemies.
    for (int i = 0; i < mEnemies.size(); ++i)
    {
        board[mEnemies[i]->pos.y][mEnemies[i]->pos.x] = 'O';
    }

    //Fill the explosions.
    for (int i = 0; i < mExplosions.size(); ++i)
    {
        board[mExplosions[i].y][mExplosions[i].x] = '*';
    }

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 10; ++i)
    {
        cout << "=";
        for (int j = 0; j < 60; ++j)
        {
            switch (board[i][j])
            {
                case '@':
                    SetConsoleTextAttribute(hOut, 11);
                    break;
                case '>':
                    SetConsoleTextAttribute(hOut, 10);
                    break;
                case '*':
                    SetConsoleTextAttribute(hOut, 12);
                    break;
                case 'O':
                    SetConsoleTextAttribute(hOut, 14);
                    break;
                default:
                    SetConsoleTextAttribute(hOut, 15);
                    break;
            }
            cout << board[i][j];
        }
        cout << "=" << endl;
    }

    //Paint bottom border and caption
    cout << border << endl;
    cout << "Player: " << mPlayer->name << endl;
    cout << "Lives: " << mPlayer->lives << endl;
    cout << "Score: " << mPlayer->score << endl;
}


int main()
{
	srand(time(NULL));
    char name[32];
    cout << "Type your name: ";
    cin >> name;

    Player* currPlayer = newPlayer(name);

    if (currPlayer) {
        system("cls");
        while (currPlayer->lives > 0)
        {
            initFrame();
            checkInput(currPlayer);
            updateState(currPlayer);
            printBoard(currPlayer);
            Sleep(50);
        }

        system("cls");
        cout << "GAME OVER" << endl;
        cout << "Score: " << currPlayer->score << endl;
        
        for (int i = 0; i < mEnemies.size(); ++i)
        {
            deleteEnemy(mEnemies[i]);
        }
        mEnemies.clear();
        deletePlayer(currPlayer);

        
        system("pause");
    }
    return 0;
}