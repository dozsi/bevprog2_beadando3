#include "gamemaster.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct GameMaster::MiniMaxResult
{
public:
    int x;
    int y;
    int score;
};

GameMaster::GameMaster()
{
}
void GameMaster::init(char c)
{
    vector<char> temp;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(i == 3 && j == 3)
                temp.push_back('x');
            else if(i == 3 && j == 4)
                temp.push_back('o');
            else if(i == 4 && j == 4)
                temp.push_back('x');
            else if(i == 4 && j == 3)
                temp.push_back('o');
            else
                temp.push_back(' ');
        }
        state_vector.push_back(temp);
        temp.clear();
    }
    available(c);
    ///Mi vagyunk a fidesz ---> x
    current = c;
}
char GameMaster::get_state(int x, int y)
{
    return state_vector[x][y];
}
void GameMaster::color(int x,int y,bool prediction)
{
    if(prediction)
    {
        int counter = 0;
        for(int i = -1;i <= 1;i++)
        {
            for(int j = -1;j <= 1;j++)
            {
                counter =  get_available(x,y,i,j);
                //cout << counter << endl;
                for(int k = 1; k <= counter;k++)
                {
                        state_vector[x+(i*k)][y+(j*k)] = 'p';
                }
            }
        }
    }
    else
    {
        for(int k = 0; k < 8; k++)
        {
            for(int l = 0; l < 8; l++)
            {
                if(state_vector[k][l] == 'p')
                    state_vector[k][l] = current;
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
        if(state_vector[_x][_y] != 'o' && state_vector[_x][_y] != 'x')
        {
            ok1 = false;
            break;
        }
        else if(state_vector[_x][_y] == state_vector[x][y])
        {
            //cout << "talalt veget" << endl;
            ok2 = true;
            break;
        }
        else
        {
            counter++;
        }
    }
    //cout << "ok1: " << ok1 << " ok2: " << ok2 << " ok3: " << ok3 << endl;
    if(ok1 && ok2 && ok3)
    {
        //cout << "ok1: " << ok1 << " ok2: " << ok2 << " ok3: " << ok3 << endl;
        return counter;
    }
    else
    {
        return 0;
    }
}
void GameMaster::available(char c)
{
    for(int k = 0; k < 8; k++)
        for(int l = 0; l < 8; l++)
            if(state_vector[k][l] == ' ')
            {
                state_vector[k][l] = c;
                for(int i = -1;i <= 1;i++)
                    for(int j = -1;j <= 1;j++)
                        if(get_available(k,l,i,j) > 0)
                            state_vector[k][l] = 'a';
                if(state_vector[k][l] == c)
                    state_vector[k][l] = ' ';
            }
}
void GameMaster::reset_available()
{
    for(int k = 0; k < 8; k++)
    {
        for(int l = 0; l < 8; l++)
        {
            if(state_vector[k][l] == 'a')
            {
                state_vector[k][l] = ' ';
            }
            if(state_vector[k][l] == 'p')
            {
                if(current == 'o')
                    state_vector[k][l] = 'x';
                else
                    state_vector[k][l] = 'o';

            }
        }
    }
}
void GameMaster::counter()
{
    e_counter = 0;
    o_counter = 0;
    x_counter = 0;
    a_counter = 0;
    p_counter = 0;
    for(const vector<char> &cv : state_vector)
    {
        for(char c: cv)
        {
            if( c == ' ')
                e_counter++;
            else if( c == 'o')
                o_counter++;
            else if( c == 'x')
                x_counter++;
            else if( c == 'p')
                p_counter++;
            else
                a_counter++;
        }
    }
}
bool GameMaster::check_end(char c)
{
    reset_available();
    available(c);
    counter();
    return(a_counter == 0);
}

bool GameMaster::set_state(int x, int y,char c)
{
    if(state_vector[x][y] == 'a' )
    {
        current = c;
        state_vector[x][y] = c;
        color(x,y,false);
        return true;
    }
    else
    {
        return false;
    }
}
bool GameMaster::slayer_move(int x, int y,char c)
{
    if(state_vector[x][y] == 'a' )
    {
        MiniMaxResult result;
        set_state(x,y,'o');
        result = minimize(0,0,10);
        state_vector[result.x][result.y] = 'x';
        color(result.x,result.y,false);
        cout << result.x << " " << result.y << endl;
        return true;
    }
    return false;
}

void GameMaster::predict_state(int x, int y,char c)
{
    if(state_vector[x][y] == 'a' )
    {
        current = c;
        state_vector[x][y] = c;
        color(x,y,true);
        state_vector[x][y] ='a';
    }
}

GameMaster::MiniMaxResult GameMaster::minimize(int x, int y,int dpt)
{
    int _a_counter = a_counter;
    int _e_counter = e_counter;
    int _x_counter = x_counter;
    int _o_counter = o_counter;
    int _p_counter = p_counter;
    std::vector<std::vector<char>> _state_vector = state_vector;
    MiniMaxResult result;
    MiniMaxResult result2;
    result.score = INT32_MAX;
    counter();
    if(dpt >0)
    for(int k = 0; k < 8; k++)
    {
        for(int l = 0; l < 8; l++)
        {
            if(state_vector[k][l] == 'a')
            {
                //state_vector[k][l] = 'o';
                set_state(k,l,'o');
                MiniMaxResult result1 = maximize(k,l,dpt-1);
                if(result1.score < result.score)
                    result = result1;
                state_vector[k][l] = 'a';
            }
        }
    }
    if(result.score == INT32_MAX)
    {
        if(o_counter == p_counter)
            result2={x,y,0};
        if(o_counter > p_counter)
           result2= {x,y,o_counter};
        else
           result2= {x,y,-p_counter};
    }
    else
        result2=result;
     a_counter = _a_counter;
     e_counter = _e_counter;
     x_counter = _x_counter;
     o_counter = _o_counter;
     p_counter = _p_counter;
     state_vector = _state_vector;
     return result2;
}

GameMaster::MiniMaxResult GameMaster::maximize(int x, int y,int dpt)
{
    int _a_counter = a_counter;
    int _e_counter = e_counter;
    int _x_counter = x_counter;
    int _o_counter = o_counter;
    int _p_counter = p_counter;
    std::vector<std::vector<char>> _state_vector = state_vector;
    MiniMaxResult result;
    MiniMaxResult result2;
    result.score = INT32_MAX;
    counter();
    if(dpt >0)
    for(int k = 0; k < 8; k++)
    {
        for(int l = 0; l < 8; l++)
        {
            if(state_vector[k][l] == 'a')
            {
                //state_vector[k][l] = 'o';
                set_state(k,l,'x');
                MiniMaxResult result1 = minimize(k,l,dpt-1);
                if(result1.score > result.score)
                    result = result1;
                state_vector[k][l] = 'a';
            }
        }
    }
    if(result.score == INT32_MAX)
    {
        if(p_counter == o_counter)
            result2={x,y,0};
        if(p_counter > o_counter)
           result2= {x,y,p_counter};
        else
           result2= {x,y,-o_counter};
    }
    else
        result2=result;
     a_counter = _a_counter;
     e_counter = _e_counter;
     x_counter = _x_counter;
     o_counter = _o_counter;
     p_counter = _p_counter;
     state_vector = _state_vector;
     return result2;
}
