#include<iostream>
#include "State.h"
#include "Resolvable.h"

int merge(vector<int>& arr, vector<int>& temp, int left, int mid,
          int right)
{
    int i, j, k;
    int inv_count = 0;
 
    i = left; 
    j = mid; 
    k = left;
    while ((i <= mid - 1) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
            inv_count = inv_count + (mid - i);
        }
    }

    while (i <= mid - 1)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];
 
    for (i = left; i <= right; i++)
        arr[i] = temp[i];
 
    return inv_count;
}

int _mergeSort(vector<int>& arr, vector<int>& temp, int left, int right)
{
    int mid, inv_count = 0;
    if (right > left) {
        mid = (right + left) / 2;
 
        inv_count += _mergeSort(arr, temp, left, mid);
        inv_count += _mergeSort(arr, temp, mid + 1, right);
 
        inv_count += merge(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}

int get_inversions(State state)
{
    int arr_size = state.get_num();
    vector<int> arr(arr_size, 0);
    int board_size = state.get_board_size();
    vector<vector<int>> board = state.get_board();
    int offset = 0;
    for(int i = 0; i < board_size; i++) {
        for(int j = 0; j < board_size; j++) {
            if ( board[i][j] != 0) {
                arr[i*board_size + j + offset] = board[i][j];
            }
            else  {
                offset = -1;
            }
        }
    }
    vector<int> temp(arr_size, 0);
    return _mergeSort(arr, temp, 0, arr_size - 1);
}

bool state_is_resolvable(State state) {
    int inversions = get_inversions(state);
     return ( state.get_board_size() % 2 == 0 && (state.empty_space.first + inversions) % 2 == 1 )||
            ( state.get_board_size() % 2 == 1 && inversions % 2 == 0);
}

