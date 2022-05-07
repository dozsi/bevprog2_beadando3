#include "gamemaster.h"
#include <vector>
#include <iostream>
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
                temp.push_back('e');
        }
        state_vector.push_back(temp);
        temp.clear();
    }
}
char GameMaster::get_state(int x, int y)
{
    return state_vector[y][x];
}
void GameMaster::set_state(int x, int y,char c)
{
    state_vector[y][x] = c;

}
