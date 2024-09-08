#ifndef SNAKE_H
#define SNAKE_H

#include <windows.h>
#include <vector>

#define WIDTH 50
#define HEIGHT 25
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
using namespace std;

class Snake
{
    private:
        COORD pos;
        int vel;
        char dir;
        int len;
        vector<COORD> body;

    public:
        Snake(COORD pos, int vel);

        void grow();
        void move_snake();
        void direction(char dir);

        vector<COORD> get_body();

        bool collided();
        bool eaten(COORD food);

        COORD get_pos();
};

#endif // SNAKE_H
