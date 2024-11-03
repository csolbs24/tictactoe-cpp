#include <iostream>
using namespace std;

class TicTacToe {
public:
    int turnNumber = 0;
    char board[3][3]{};
    void printBoard() {
        // Print the top of the board
        cout << "|---|---|---|\n";

        // Loop through each row of the board
        for (int i = 0; i < 3; i++) {

            // Print "| " to start each row
            cout << "| ";

            // Loop through each column in the row
            for (int j = 0; j < 3; j++) {

                // If the current location hasn't been played on yet, print the index of the board location instead
                if (board[i][j] == ' ') {
                    cout << i * 3 + j + 1;
                }
                // Otherwise print either the X or the O stored here
                else {
                    cout << board[i][j];
                }

                // Build the rest of the grid for this row
                cout << " | ";
            }

            // Create a new line
            cout << "\n";

            // If it's the final row, end the grid
            if (i == 2) {
                cout << "|---|---|---|\n";
            }
            // Otherwise print a middle grid section
            else {
                cout << "|---|---|---|\n";
            }
        }
    }
    void updateBoard(int boardIndex) {
        // Update the proper index with O on an even turn and X on an odd turn
        board[boardIndex / 3][boardIndex % 3] = ((turnNumber % 2 == 0) ? 'O' : 'X');
    }
    char getBoardValueAtIndex(int index) {
        return board[index / 3][index % 3];
    }
    int getPlayerInput() {
        // Initialize playIndex and playIndexChar
        int playIndex;
        char playIndexChar;

        // Print to the console the current player's turn and ask where they want to play
        cout << ((turnNumber % 2 == 0) ? "O" : "X");
        cout << "\'s turn. Type index of where you want to play: ";

        // Get input from the player
        cin >> playIndexChar;

        // chars are stored in c++ as an index of what char they are, subtracting '1' will give us the exact int that we want.
        playIndex = playIndexChar - '1';

        // If playIndex is out of the acceptable range, or is an already used index, then ask the user for input again
        while (
            (playIndex < 0) ||
            (playIndex > 8) ||
            (getBoardValueAtIndex(playIndex) != ' '))
        {
            cout << "That was not a valid move. Try again: ";

            // Get input from the player
            cin >> playIndexChar;

            // chars are stored in c++ as an index of what char they are, subtracting '1' will give us the exact int that we want.
            playIndex = playIndexChar - '1';
        }

        return playIndex;
    }
    bool didWin() {
        // Check across each row
        for (int i = 0; i < 3; i++) {
            if (
                (board[i][0] == board[i][1]) &&
                (board[i][0] == board[i][2]) &&
                (board[i][0] != ' ')
            )
                return true;
        }

        // Check across each column
        for (int i = 0; i < 3; i++) {
            if (
                (board[0][i] == board[1][i]) &&
                (board[0][i] == board[2][i]) &&
                (board[0][i] != ' ')
            )
                return true;
        }

        // Check the diagonals
        if (
            (board[0][0] == board[1][1]) &&
            (board[0][0] == board[2][2]) &&
            (board[0][0] != ' ')
        )
            return true;
        if (
            (board[0][2] == board[1][1]) &&
            (board[0][2] == board[2][0]) &&
            (board[0][2] != ' ')
        )
            return true;

        // Default means no match
        return false;
    }
    TicTacToe() {
        // Loop through each index and initialize it to ' '
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ' ';
            }
        }
    }
};

int main() {
    // Initialize the TicTacToe object
    TicTacToe ticTacToe = TicTacToe();

    // Initialize a variable to hold the index of where the player wants to play
    int playIndex;

    // Loop through the game logic until a player wins
    do {
        // Check for a stalemate and return early
        if (ticTacToe.turnNumber > 8) {
            cout << "You stalemate. You bad. Try again??";
            return 0;
        }

        // Print the current state of the board
        ticTacToe.printBoard();

        // Increment the turnNumber to keep track of which player's turn it is and to know when a stalemate occurs
        ticTacToe.turnNumber++;

        // Ask the player where they want to play and get their input
        playIndex = ticTacToe.getPlayerInput();

        // Update the board where the current player is playing
        ticTacToe.updateBoard(playIndex);
    }
    while (!ticTacToe.didWin());

    ticTacToe.printBoard();

    cout << "Congratulations! " << ((ticTacToe.turnNumber % 2 == 0) ? "O" : "X") << " has won!!!";

    return 0;
}