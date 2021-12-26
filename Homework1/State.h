#pragma once
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class State {
    public:
        int manhatan_sum;
        int number_count;
        int board_size;
        pair<int, int> empty_space;
        vector< vector<int> > board;
        int depth;
        //x - root state
        //l - moved a plate to the left
        //r - moved a plate to the right
        //u - moved a plate up
        //d - moved a plate down
        char direction; 

        void find_next_states();
        void calculate_manhatan_sum();
        
    public:
        State(int num, vector <vector <int> > numbers, pair<int, int> empty_space_coordinates);
        int get_num();
        int get_manhatan_sum();
        int get_depth();
        int get_f();
        char get_direction();
        void set_direction(char direction);
        void set_depth(int dep);
        vector<State> get_next_states();
        vector<vector<int>> get_board();
        bool operator == (State other);
};