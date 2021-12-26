#include "IDA.h"
#include "Resolvable.h"

int main() {
    int nums[3][3] = {{3,8,5},{2,0,4},{7,6,1}};
    
    vector<vector<int>> numbers;
    for (int i = 0; i < 3; i++) {
        vector<int> a(nums[i], nums[i] + 3);
        numbers.push_back(a);
    }

    State st(8, numbers, make_pair(1,1));
    vector<State> next_states = st.get_next_states();

    IterativeDeepeningAStar(st);    
}   