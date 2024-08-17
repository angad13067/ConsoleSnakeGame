#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

int lives = 3;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;                                              // in order to run for loop to print tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };    //Each name corresponds to unique const integer value
eDirection dir;                                         //can hold any of the values defined in eNum

void getScore()
{
    cout << "Your Score: " << score << endl;
    cout << "Your Lives: " << lives << endl;
    cout << "Press 'x' to end game" << endl;
}

void Freeze()
{
    Sleep(500);
    dir = STOP;
}

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width; //to spawn fruit within borders of map
    fruitY = rand() % height;
    score = 0;

}

void Draw()
{
    system("cls"); //clear console window
    for (int i = 0; i < width+2; i++) //print top wall
        cout << "#";

cout << endl;

for (int i = 0; i < height; i++)
{
    for (int j = 0; j < width; j++)
    {
        if (j == 0)
            cout << "#";
       
        if (i == y && j == x)
            cout << "O";
        else if (i == fruitY && j == fruitX)
            cout << "+";
        else
        {
            bool print = false;
            for (int k = 0; k < nTail; k++) //going thru every element of tail and drawing it
            {
                
                if (tailX[k] == j && tailY[k] == i)
                {
                    cout << "o";
                    print = true;
                }
                
            }
            if (!print)
                cout << " ";
        }
            
          
       
            

        if (j == width - 1)
            cout << "#";

    }
    cout << endl;
   
    }

    for (int i = 0; i < width+2; i++) //print sides
        cout << "#";
    cout << endl;
}

//Movement input for arrow keys and wasd keys
void  Input()
{
    if (_kbhit()) //returns positive number if keyboard press
    {
        int key = _getch();

        if (key == 224)
        {
            key = _getch();


            switch (key)
            {
            case 72:
                dir = UP;
                break;
            case 80:
                dir = DOWN;
                break;
            case 75:
                dir = LEFT;
                break;
            case 77:
                dir = RIGHT;
                break;
            }
        }

        else
        {
            switch (key)
            {
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }
}

void Logic()
{  
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
            x--;
            break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN: 
        y++;
        break;
    default:
        break;

    }
    //Wrap around if snake passes border
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y > +height)y = 0; else if (y < 0)y = height - 1;    
   
    //Check if snake turns on itself 
    //This can be used to remove a life if snake turns on itself
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
        {
            /*lives--;
            if (lives == 0)
            {
                gameOver = true;
            }
            else
            {
                nTail = 0;
                x = width / 2;
                y = height / 2;
                dir = STOP;
            }
            break;*/
        }

    
    if (x == fruitX && y == fruitY)
    {
   
        score += 10;
        fruitX = rand() % width; //to spawn fruit within borders of map
        fruitY = rand() % height;
        nTail++;
    }

}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        getScore();
        Sleep(130); //130 slow
        
           
    }
    
}


