#pragma once
#include <utility>
using namespace std;
class TicTacToe {
    private:
        char board[3][3];

        bool hasEmptySpaces();
        int evaluate();
        int minimax(int depth, int alpha, int beta);
    
    public:
        //bot is maximazing and plays with 'x'
        bool isBotsTurn;

        TicTacToe(bool botIsFirst);
        pair<int,int> findBestMove();
        void playMove(int x, int y);
        bool isGameOver();
        void printBoard();
};