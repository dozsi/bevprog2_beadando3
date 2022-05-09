#ifndef GAMEMASTER_H
#define GAMEMASTER_H
#include <vector>

class GameMaster
{
public:
    GameMaster();
    std::vector<std::vector<char>> state_vector; ///b,w
    void init();
    char get_state(int x, int y);
    bool set_state(int x, int y,char c);
    int get_available(int x,int y, int ix, int iy);
    void color(int x,int y);
    void available();
};

#endif // GAMEMASTER_H
