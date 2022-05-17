#ifndef GAMEMASTER_H
#define GAMEMASTER_H
#include <vector>

class GameMaster
{
protected:
public:
    struct MiniMaxResult;
    GameMaster();
    int a_counter;
    int e_counter;
    int x_counter;
    int o_counter;
    int p_counter;
    char current;
    std::vector<std::vector<char>> state_vector; ///b,w
    void init(char c);
    char get_state(int x, int y);
    bool set_state(int x, int y,char c);
    int get_available(int x,int y, int ix, int iy);
    void color(int x,int y, bool prediction);
    void available(char c);
    void reset_available();
    void counter();
    bool check_end(char c);
    void predict_state(int x, int y,char c);
    MiniMaxResult minimize(int x, int y,int dpt);
    MiniMaxResult maximize(int x, int y,int dpt);
    bool slayer_move(int x, int y,char c);
};

#endif // GAMEMASTER_H
