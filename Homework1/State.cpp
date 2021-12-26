#include "State.h"
#include <cmath>

State::State(int num, vector <vector <int> > numbers, pair<int, int> empty_space_coordinates) {
    this->number_count = num;
    this->empty_space = empty_space_coordinates;
    this->board = numbers;
    this->parent = nullptr;
    this->direction = 'x';
    this->board_size = sqrt(num + 1);
    this->calculate_manhatan_sum();
}


bool State::operator==(State other) {
    if (this->board_size != other.board_size) {
        return false;
    }
    vector< vector<int>> this_board = this->get_board();
    vector< vector<int>> other_board = other.get_board();

    for(int i = 0; i < this->board_size; i++) {
        for (int j = 0; j< this->board_size; j++) {
            if (this_board[i][j] != other_board[i][j]) {
                return false;
            }
        }
    }

    return true;
}

int State::get_num() {
    return this->number_count;
}


int State::get_depth() {
    return this->depth;
}

vector<vector<int>> State::get_board() {
    return this->board;
}

char State::get_direction() {
    return this->direction;
}

void State::set_direction(char direction) {
    this->direction = direction;
}

void State::set_depth(int dep) {
    this->depth = dep;
}

int State::get_f() {
    return this->manhatan_sum + this->depth;
}

State* State::get_parent(){
    return this->parent;
}

int State::get_manhatan_sum(){
    return this->manhatan_sum;
}
void State::calculate_manhatan_sum() {
    int sum = 0;
    for(int i = 0; i < this->board_size; i++) {
        for(int j = 0; j < this->board_size; j++) {
            int number = this->board[i][j];
            if (number != 0) {
                //here!!
                int x_goal, y_goal;
                if (number % this->board_size == 0 ) {
                    x_goal = number / this->board_size - 1;
                    y_goal = this->board_size - 1;

                } else {
                    x_goal = number / this->board_size;
                    y_goal = number % this->board_size - 1;
                }
                
                int current_manhatan_dist = abs(x_goal - i) + abs(y_goal - j);
                //cout << current_manhatan_dist << " ";
                sum += current_manhatan_dist;
            }
        }
    }
    //cout << endl;
    this->manhatan_sum = sum;
}


void State::set_parent(State* pr) {
    this->parent = pr;
}

vector<State> State::get_next_states() {
    vector <State> new_states;
    char direction;
    // Switch with upper plate
    if(this->empty_space.first >= 1) {
        vector< vector <int> > new_board(this->board);
        swap(new_board[this->empty_space.first][this->empty_space.second], 
             new_board[this->empty_space.first - 1][this->empty_space.second]);
        State new_state(this->number_count, new_board, make_pair(this->empty_space.first - 1, this->empty_space.second));
        new_state.set_direction('d');
        new_states.push_back(new_state);
    }

    // Switch with under plate
    if(this->empty_space.first < this->board_size - 1) {
        vector< vector <int> > new_board(this->board);
        swap(new_board[this->empty_space.first][this->empty_space.second], 
             new_board[this->empty_space.first + 1][this->empty_space.second]);
        State new_state(this->number_count, new_board, make_pair(this->empty_space.first + 1, this->empty_space.second));
        new_state.set_direction('u');
        new_states.push_back(new_state);
    }
    
    // Switch with right plate
    if(this->empty_space.second < this->board_size - 1) {
        vector< vector <int> > new_board(this->board);
        swap(new_board[this->empty_space.first][this->empty_space.second], 
             new_board[this->empty_space.first][this->empty_space.second + 1]);
        State new_state(this->number_count, new_board, make_pair(this->empty_space.first, this->empty_space.second + 1));
        new_state.set_direction('l');
        new_states.push_back(new_state);
    }

    // Switch with left plate
    if(this->empty_space.second >= 1) {
        direction = 'r';
        vector< vector <int> > new_board(this->board);
        swap(new_board[this->empty_space.first][this->empty_space.second], 
             new_board[this->empty_space.first][this->empty_space.second - 1]);
        State new_state(this->number_count, new_board, make_pair(this->empty_space.first, this->empty_space.second - 1));
        new_state.set_direction('r');
        new_states.push_back(new_state);
    }
    return new_states;
}
