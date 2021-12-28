#pragma once
#include <vector>
#include <utility>
using namespace std;


class NQueens {
    private:
        int N;
        vector<pair<int, int>> queens; //row-column

        vector<int> column;
        vector<int> upper_diagonal;
        vector<int> lower_diagonal;
        vector<int> reverse_diagonal;
        
    public:
        NQueens(int N);
        int get_N();
        int get_queen_conflicts(int queen);
        int get_num_conflicts(int exclude_row);
        int get_max_conflicts_queen();
        void min_conflicts();
        void move_queen(int queen, int col);
        void print_board();

        vector<pair<int, int>> get_queens();
        
};