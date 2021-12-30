#include <iostream>

#include "Tic-tac-toe.h"


TicTacToe::TicTacToe(bool botIsFirst) {
    this->isBotsTurn = botIsFirst;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            this->board[i][j] = '_';
        }
    }
}

bool TicTacToe::hasEmptySpaces() {
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (this->board[i][j] == '_') {
                return true;
            }
        }
    }
    return false;
}

int TicTacToe::evaluate() {

    //check columns
    for (int i = 0; i < 3; i++) {
        if (this->board[0][i] == this->board[1][i] &&
            this->board[1][i] == this->board[2][i]) {
            if (this->board[0][i] == 'x')
                return +10;
 
            else if (this->board[0][i] == 'o')
                return -10;
        }
    }

    //check rows
    for (int i = 0; i < 3; i++) {
        if (this->board[i][0] == this->board[i][1] &&
            this->board[i][1] == this->board[i][2]) {
            if (this->board[i][0] == 'x')
                return +10;
            else if (this->board[i][0] == 'o')
                return -10;
        }
    }

    //check diagonals
    if (this->board [0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2])
    {
        if (this->board[0][0] == 'x')
            return +10;
        else if (this->board[0][0] == 'o')
            return -10;
    }
 
    if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0])
    {
        if (this->board[0][2] == 'x')
            return +10;
        else if (this->board[0][2] == 'o')
            return -10;
    }
 
    // Else if none of them have won then return 0
    return 0;
}

int TicTacToe::minimax(int depth, int alpha, int beta)
{
    int score = this->evaluate();
 
    if (score == 10) {
        return score - depth;
    }

    if (score == -10) {
        return score + depth;
    }
 
    if (!this->hasEmptySpaces()){
        return 0;
    }

    //max player
    if (this->isBotsTurn) {
        int best = INT32_MIN;
 
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++) {
                
                if (this->board[i][j]=='_')
                {
                    this->board[i][j] = 'x';
                    this->isBotsTurn = false;

                    best = max(best, this->minimax(depth + 1, alpha, beta) - depth - 1);
                    alpha = max(best, alpha);
           
                    this->isBotsTurn = true;
                    board[i][j] = '_';

                    if(beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return best;

    } else {
        int best = INT32_MAX;
 
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (this->board[i][j]=='_') {
                    this->board[i][j] = 'o';
                    this->isBotsTurn = true;
    
                    best = min(best, this->minimax(depth+1, alpha, beta) + depth + 1);
                    beta = min(beta, best);

                    board[i][j] = '_';
                    this->isBotsTurn = false;
                    
                    if(beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return best;
    }
}

pair<int, int> TicTacToe::findBestMove() {

    int bestVal = INT32_MIN;
    int bestRow = -1;
    int bestCol = -1;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(this->board[i][j] == '_') {
                this->board[i][j] = 'x';
                this->isBotsTurn = false;

                int curVal = minimax(0, INT32_MIN, INT32_MAX);
                
                //undo move
                this->isBotsTurn = true;
                this->board[i][j] = '_';


                if (curVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = curVal;
                }
            }
        }
    }
    return make_pair(bestRow, bestCol);

}

bool TicTacToe::isGameOver() {
    int val = this->evaluate();
    return !this->hasEmptySpaces() || val == 10 || val == -10;
}

void TicTacToe::playMove(int x, int y) {
    if (this->isBotsTurn) {
        this->board[x][y] = 'x';
        this->isBotsTurn = false;
    } else {
        this->board[x][y] = 'o';

        this->isBotsTurn = true;
    }
}

void TicTacToe::printBoard() {
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << this->board[i][j] << " ";
        }
        cout << endl;
    }
}