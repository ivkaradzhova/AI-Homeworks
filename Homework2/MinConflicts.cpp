#include "NQueens.h"
#include <random>
#include <iostream>
#include <chrono>
using namespace std::chrono;

using namespace std;

void MinConflicts(NQueens nq) {
    //Start timer
    auto start = high_resolution_clock::now();
    int timer = 50;
    int count = 0;
    int N = nq.get_N();
    int num_conflicts = nq.get_num_conflicts(-1);
    

    while(num_conflicts != 0 ) {
        nq.min_conflicts();
        int new_num_conflicts = nq.get_num_conflicts(-1);

        if (new_num_conflicts == num_conflicts) {
            //move random queen
            nq.move_queen(rand() % N, rand() % N);
        }
        num_conflicts = new_num_conflicts;
        count++;
    }
    //Stop the timer befor printing the result
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Time: " << duration.count() << " seconds" << endl;
            
    if( nq.get_num_conflicts(-1) == 0 ) {
        cout << "succes" << endl;
    }
    //nq.print_board();
}