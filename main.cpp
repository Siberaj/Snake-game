#include <iostream>
#include <conio.h>
#include <ctime>

#include "Snake.h"
#include "Food.h"

#define WIDTH 50
#define HEIGHT 25
#define HL 196
#define VL 179
#define LT 218
#define RT 191
#define LB 192
#define RB 217

using namespace std;

Snake snake({WIDTH/2, HEIGHT/2}, 1);
Food food;

int score;

void board()
{
    COORD snake_pos = snake.get_pos();
    COORD food_pos = food.get_pos();

    vector<COORD> snake_body = snake.get_body();

    cout << "SCORE : " << score << "\n\n";

    for(int i = 0,j=0; i < HEIGHT; i++)
    {
        if(i==0)
            cout << "\t\t"<<char(LT);
        else if(i==HEIGHT-1)
            cout << "\t\t"<<char(LB);
        else
            cout << "\t\t"<<char(VL);
        for( j = 0; j < WIDTH - 2; j++)
        {
            if(i == 0 || i == HEIGHT-1) cout << char(HL);

            else if(i == snake_pos.Y && j+1 == snake_pos.X) cout << '0';
            else if(i == food_pos.Y && j+1 == food_pos.X) cout << '@';

            else
            {
                bool isBodyPart = false;
                for(int k = 0; k < snake_body.size()-1; k++)
                {
                    if(i == snake_body[k].Y && j+1 == snake_body[k].X)
                    {
                        cout << 'o';
                        isBodyPart = true;
                        break;
                    }
                }

                if(!isBodyPart) cout << ' ';
            }
        }
        if(i==0)
            cout << char(RT)<<"\n";
        else if(i==HEIGHT-1)
            cout << char(RB)<<"\n";
        else
        cout << char(VL)<<"\n";
    }
}

int main()
{
    score = 0;
    srand(time(NULL));

    food.gen_food();

    char game_over = false;

    while(!game_over)
    {
        board();

        if(kbhit())
        {
            switch(getch())
            {
                case UP: snake.direction('u'); break;
                case LEFT: snake.direction('l'); break;
                case DOWN: snake.direction('d'); break;
                case RIGHT: snake.direction('r'); break;
            }
        }

        if(snake.collided()) game_over = true;

        if(snake.eaten(food.get_pos()))
        {
            food.gen_food();
            snake.grow();
            score = score + 10;
        }

        snake.move_snake();

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    }
}
