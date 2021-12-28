#include "IDA.h"
#include "Resolvable.h"
#include<cmath>

int main() {
    int num;
    pair<int, int> empty_pos;
    vector<vector<int>> numbers;
    cin >> num;
    int board_size = sqrt(num + 1);

    for (int  i = 0; i < board_size; i++) {
        vector<int> row(board_size, 0);
        for(int j = 0; j < board_size; j++) {
            cin >> row[j];
            if (row[j] == 0) {
                empty_pos.first = i;
                empty_pos.second = j;
            }
        }
        numbers.push_back(row);
    }

    State st(num, numbers, empty_pos);
    IterativeDeepeningAStar(st);    
}   