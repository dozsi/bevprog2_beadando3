#ifndef GAMEMASTER_H
#define GAMEMASTER_H
#include <vector>

class GameMaster
{
public:
    GameMaster();
    std::vector<std::vector<char>> state_vector; ///b,w,e
    void init();
    char get_state(int x, int y);
    void set_state(int x, int y,char c);
};

#endif // GAMEMASTER_H
