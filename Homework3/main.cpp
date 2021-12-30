#include "Tic-tac-toe.h"
#include <iostream>
#include <utility>
using namespace std;

int main() {
    cout << "Chose first player:\n0 for player\n1 for bot" << endl;
    int botIsFirst;
    cin >> botIsFirst;

    TicTacToe game(botIsFirst);
    game.printBoard();
    
    while(!game.isGameOver()) {
        if (game.isBotsTurn) {
            pair<int, int> move = game.findBestMove();
            game.playMove(move.first, move.second);
            cout << "Bot played " << endl;
            game.printBoard();
        }
        else {
            cout << "It is your turn. Input position. " << endl;
            int x, y;
            cin >> x >> y;
            game.playMove(x, y);
            game.printBoard();
        }
    }
    
    cout << "Game over " << endl;
    
}