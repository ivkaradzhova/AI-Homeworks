#include <cmath>
#include <queue>
#include <set>
#include "IDA.h"

class Compare
{
public:
    bool operator()(State a, State b)
    {
        return a.get_f() > b.get_f();
    }
};

State create_goal_state(int num)
{
    int board_size = sqrt(num + 1);
    vector<vector<int>> numbers(board_size, vector<int>());
    for (int i = 0; i < board_size; i++)
    {

        vector<int> row(board_size, 0);

        for (int j = 0; j < board_size; j++)
        {
            row[j] = i * board_size + j + 1;
        }
        numbers[i] = row;
    }
    numbers[board_size - 1][board_size - 1] = 0;

    return State(num, numbers, make_pair(board_size - 1, board_size - 1));
}

bool path_contains_state(vector<State> path, State state)
{
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == state)
        {
            return true;
        }
    }
    return false;
}

void print_board(State st) {
    for(int j = 0; j< st.get_board().size(); j++) {
        for(int k = 0; k < st.get_board()[j].size(); k++) {
            cout << st.get_board()[j][k] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void print_commands(State final_state) { 
    State* current = &final_state;
    while(current != nullptr) {
        print_board(*current);
        switch ((*current).get_direction()) {
            case 'l':
                cout << "left" << endl;
                break;
            case 'r':
                cout << "right" << endl;
                break;
            case 'u':
                cout << "up" << endl;
                break;
            case 'd':
                cout << "down" << endl;
                break;
            case 'x':
                cout << "start state" << endl;
                break;
        }
        current = (*current).get_parent();
    }      
}

bool search_for_goal(vector<State>& path, int threshold, int &min_f)
{
    State current = path.back();

    if (current.get_f() > threshold) {
        min_f = current.get_f();
        return false;
    }

    if (current == create_goal_state(current.get_num())) {
        print_commands(current);
        return true;
    }

    vector<State> next_states = current.get_next_states();
    int current_min_f = INT_LEAST32_MAX;

    for (int i = 0; i < next_states.size(); i++) {
        next_states[i].set_depth(current.get_depth() + 1);
        next_states[i].set_parent(&current);
        if (!path_contains_state(path, next_states[i]))
        {
            path.push_back(next_states[i]);
            if (search_for_goal(path, threshold, min_f))
            {
                return true;
            }
            
            if (min_f < current_min_f)
            {
                current_min_f = min_f;                
            }

            path.erase(path.end());
        }
    }
    min_f = current_min_f;
    return false;
}

//only solvable boards
void IterativeDeepeningAStar(State start_state)
{
    start_state.set_depth(0);
    int threshold = start_state.get_manhatan_sum();
    vector<State> path;
    path.push_back(start_state);
    int min_path_length = start_state.get_f();
    while (!path.empty())
    {
        cout << path.size() << endl;
        if (search_for_goal(path, threshold, min_path_length))
        {
            cout << "Goal state was reached" << endl;
            cout << "path length: " << min_path_length << endl;
            return;
        }
        threshold = min_path_length;
        cout << "conntinue search with new threshold " << threshold << endl;
    }
}
