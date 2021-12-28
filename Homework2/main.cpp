#include "NQueens.h"
#include "MinConflicts.h"
#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    NQueens nq(N);
    
    MinConflicts(nq);
    
    return 0;
}