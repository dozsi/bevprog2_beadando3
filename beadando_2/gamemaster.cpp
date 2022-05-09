#include "gamemaster.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

GameMaster::GameMaster()
{
}
void GameMaster::init()
{
    vector<char> temp;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(i == 3 && j == 3)
                temp.push_back('b');
            else if(i == 3 && j == 4)
                temp.push_back('w');
            else if(i == 4 && j == 4)
                temp.push_back('b');
            else if(i == 4 && j == 3)
                temp.push_back('w');
            else
                temp.push_back(' ');
        }
        state_vector.push_back(temp);
        temp.clear();
    }
}
char GameMaster::get_state(int x, int y)
{
    return state_vector[x][y];
}
void GameMaster::color(int x,int y)
{
    int counter = 0;
    for(int i = -1;i <= 1;i++)
    {
        for(int j = -1;j <= 1;j++)
        {
            counter =  get_available(x,y,i,j);
            for(int k = 1; k <= counter;k++)
            {
                state_vector[x+(i*k)][y+(j*k)] = state_vector[x][y];
            }
        }
    }
}
int GameMaster::get_available(int x,int y, int ix, int iy)
{
    bool ok1 = true;
    bool ok2 = false;
    bool ok3 = true;
    int counter = 0;
    int _x = x;
    int _y = y;
    while(ok3)
    {
        if(_x+ix < 8 && _x+ix >= 0 && _y+iy < 8 && _y+iy >= 0)
        {
            _x+=ix;
            _y+=iy;
        }
        else
        {
            ok3 = false;
            break;
        }
        if(state_vector[_x][_y] == ' ')
        {
            ok1 = false;
            //cout << "nemjo" << endl;
            break;
        }
        else if(state_vector[_x][_y] == state_vector[x][y])
        {
            ok2 = true;
            //cout << "jo" << endl;
            break;
        }
        else
        {
            counter++;
        }
    }
    if(ok1 && ok2 && ok3)
        return counter;
    else
        return 0;
}
void GameMaster::available()
{
    for(int k = 0; k < 8; k++)
    {
        for(int l = 0; l < 8; l++)
        {
            if(state_vector[k][l] == ' ')
            {
                for(int i = -1;i <= 1;i++)
                {
                    for(int j = -1;j <= 1;j++)
                    {
                        if(get_available(k,l,i,j) > 0)
                        {
                            state_vector[k][l] = 'a';
                        }
                    }
                }
            }
        }
    }
}
bool GameMaster::set_state(int x, int y,char c)
{
    if(state_vector[x][y] != ' ')
    {
        return false;
    }
    else
    {
        state_vector[x][y] = c;
        color(x,y);
        //get_available();
        return true;
    }
}
