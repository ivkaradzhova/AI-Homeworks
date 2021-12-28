#include "NQueens.h"
#include "MinConflicts.h"
#include <iostream>
using namespace std;

int main() {
    int N = 10000;
    NQueens nq(N);
    vector<pair<int, int>> queens = nq.get_queens();
    for(int i = 0; i < N; i++) {
        cout << queens[i].first << " " << queens[i].second << endl;
    }
    
    MinConflicts(nq);
    
    return 0;
}