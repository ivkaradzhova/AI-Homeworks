#include "NQueens.h"
#include<random>
#include <cmath>
#include <iostream>
using namespace std;
//each queen will be on a seperate row
NQueens::NQueens(int N) {
    this->N = N;

    vector<pair<int, int>> queens;
    for(int i = 0; i < N; i++) {
        int column = rand() % N;
        queens.push_back(make_pair(i, column));
    }

    this->queens = queens;
}

int NQueens::get_N() {
    return this->N;
}

vector<pair<int, int>> NQueens::get_queens() {
    return this->queens;
}


int NQueens::get_num_conflicts(int exclude_row) {
    this->upper_diagonal = vector<int>(N, 0);
    this->lower_diagonal= vector<int>(N, 0);
    this->column = vector<int>(N,0);
    this->reverse_diagonal = vector<int> (N*2, 0);

    for(int i = 0; i < this->N; i++) {
        if(i == exclude_row) {
            continue;
        }
        this->column[this->queens[i].second]++;
        int diagonal = this->queens[i].first - this->queens[i].second;
        int rev_diagonal = this->queens[i].first + this->queens[i].second;
        
        if(diagonal < 0) {
            this->lower_diagonal[-diagonal]++; 
        } else {
            this->upper_diagonal[diagonal]++;
        }
    
        this->reverse_diagonal[rev_diagonal]++;
    }

    int conflicts = 0;
    for(int i = 0; i < this->N*2 - 1; i++) {
        if(i < this->N) {
            conflicts += this->column[i] * (this->column[i] - 1) / 2;
            conflicts += this->upper_diagonal[i] * (this->upper_diagonal[i] - 1) / 2;
            conflicts += this->lower_diagonal[i] * (this->lower_diagonal[i] - 1) / 2;
        }
        conflicts += this->reverse_diagonal[i] * (this->reverse_diagonal[i] - 1) / 2;
    }
    return conflicts;
}

int NQueens::get_max_conflicts_queen() {
    int max_conflicts = 0;
    vector<int> max_conflicts_queens;

    for(int i = 0; i < this->N; i++) {
        int conflicts = 0;
        conflicts += this->column[this->queens[i].second] * (this->column[this->queens[i].second] - 1) / 2;
        int diagonal = this->queens[i].first - this->queens[i].second;
        int reverse_diagonal = this->queens[i].first + this->queens[i].second;
        if (diagonal < 0) {
            conflicts += this->lower_diagonal[-diagonal] * (this->lower_diagonal[-diagonal] - 1) / 2;
        } else {
            conflicts += this->upper_diagonal[diagonal] * (this->upper_diagonal[diagonal] - 1) / 2;
        }
        conflicts += this->reverse_diagonal[reverse_diagonal] * (this->reverse_diagonal[reverse_diagonal] - 1) / 2;

        if(conflicts > max_conflicts) {
            max_conflicts = conflicts;
            max_conflicts_queens.clear();
            max_conflicts_queens.push_back(i);
        } else if(conflicts == max_conflicts){
            max_conflicts_queens.push_back(i);
        }
    }
    if (max_conflicts_queens.size() == 0) {
        cout << max_conflicts << endl;
        cout << "num conf" << this->get_num_conflicts(-1) << endl;
    }
    return max_conflicts_queens[rand() % max_conflicts_queens.size()];
}

void NQueens::min_conflicts() {
    int queen = this->get_max_conflicts_queen();
    
    this->get_num_conflicts(queen);

    int min_conflicts = INT32_MAX;
    vector<int> min_conflicts_columns;

    for(int i = 0; i < this->N; i++) {
        int conflicts = 0;
        conflicts += this->column[i] * (this->column[i] + 1) / 2;
        int diagonal = this->queens[queen].first - i;
        int reverse_diagonal = this->queens[queen].first + i;
        if (diagonal < 0) {
            conflicts += this->lower_diagonal[-diagonal] * (this->lower_diagonal[-diagonal] + 1) / 2;
        } else {
            conflicts += this->upper_diagonal[diagonal] * (this->upper_diagonal[diagonal] + 1) / 2;
        }
        conflicts += this->reverse_diagonal[reverse_diagonal] * (this->reverse_diagonal[reverse_diagonal] + 1) / 2;

        if(conflicts < min_conflicts) {
            min_conflicts = conflicts;
            min_conflicts_columns.clear();
            min_conflicts_columns.push_back(i);
        } else if(conflicts == min_conflicts) {
            min_conflicts_columns.push_back(i);
        }
    }
    this->move_queen(queen, min_conflicts_columns[rand() % min_conflicts_columns.size()]);
}

void NQueens::move_queen(int queen, int col) {
    this->queens[queen].second = col;
}


void NQueens::print_board() {
    vector< vector<char> > board(this->N, vector<char>(this->N, '_'));
    for (int i = 0; i < this->N; i++) {
        board[this->queens[i].first][this->queens[i].second] = '*';
        for (int j = 0; j < this->N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}