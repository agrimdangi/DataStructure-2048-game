#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

int board[SIZE][SIZE];

// Function prototypes
void initializeBoard();
void printBoard();
void addRandomTile();
int moveTiles(char direction);
void slideLeft();
void slideRight();
void slideUp();
void slideDown();
int checkWin();
int checkGameOver();

int main() {
    char command;
    initializeBoard();
    
    while (1) {
        printBoard();

        // Check if the player has won
        if (checkWin()) {
            printf("Congratulations! You reached 2048!\n");
            break;
        }
        
        // Check if the game is over
        if (checkGameOver()) {
            printf("Game Over! No more moves possible.\n");
            break;
        }

        printf("Enter move (w: up, s: down, a: left, d: right): ");
        scanf(" %c", &command);

        if (command == 'w' || command == 's' || command == 'a' || command == 'd') {
            if (moveTiles(command)) {
                addRandomTile(); // Add a random tile if move is valid
            }
        } else {
            printf("Invalid command! Try again.\n");
        }
    }

    return 0;
}

// Initialize the board with two random tiles
void initializeBoard() {
    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
    addRandomTile();
    addRandomTile();
}

// Print the current state of the board
void printBoard() {
    printf("\n2048 Game:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                printf(".\t");
            else
                printf("%d\t", board[i][j]);
        }
        printf("\n");
    }
}

// Add a random tile (2 or 4) to an empty spot on the board
void addRandomTile() {
    int emptyTiles[SIZE * SIZE][2], count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                emptyTiles[count][0] = i;
                emptyTiles[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0) {
        int randomIndex = rand() % count;
        int randomValue = (rand() % 2 + 1) * 2; // Randomly add 2 or 4
        board[emptyTiles[randomIndex][0]][emptyTiles[randomIndex][1]] = randomValue;
    }
}

// Move tiles in the specified direction (returns 1 if move was successful, 0 if not)
int moveTiles(char direction) {
    int moved = 0;
    switch (direction) {
        case 'a': slideLeft(); moved = 1; break;
        case 'd': slideRight(); moved = 1; break;
        case 'w': slideUp(); moved = 1; break;
        case 's': slideDown(); moved = 1; break;
    }
    return moved;
}

// Slide and merge tiles to the left
void slideLeft() {
    for (int i = 0; i < SIZE; i++) {
        int pos = 0;
        for (int j = 1; j < SIZE; j++) {
            if (board[i][j] != 0) {
                if (board[i][pos] == board[i][j]) {
                    board[i][pos] *= 2;
                    board[i][j] = 0;
                    pos++;
                } else if (board[i][pos] == 0) {
                    board[i][pos] = board[i][j];
                    board[i][j] = 0;
                } else {
                    pos++;
                    if (pos != j) {
                        board[i][pos] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
}

// Slide and merge tiles to the right
void slideRight() {
    for (int i = 0; i < SIZE; i++) {
        int pos = SIZE - 1;
        for (int j = SIZE - 2; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (board[i][pos] == board[i][j]) {
                    board[i][pos] *= 2;
                    board[i][j] = 0;
                    pos--;
                } else if (board[i][pos] == 0) {
                    board[i][pos] = board[i][j];
                    board[i][j] = 0;
                } else {
                    pos--;
                    if (pos != j) {
                        board[i][pos] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
}

// Slide and merge tiles up
void slideUp() {
    for (int j = 0; j < SIZE; j++) {
        int pos = 0;
        for (int i = 1; i < SIZE; i++) {
            if (board[i][j] != 0) {
                if (board[pos][j] == board[i][j]) {
                    board[pos][j] *= 2;
                    board[i][j] = 0;
                    pos++;
                } else if (board[pos][j] == 0) {
                    board[pos][j] = board[i][j];
                    board[i][j] = 0;
                } else {
                    pos++;
                    if (pos != i) {
                        board[pos][j] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
}

// Slide and merge tiles down
void slideDown() {
    for (int j = 0; j < SIZE; j++) {
        int pos = SIZE - 1;
        for (int i = SIZE - 2; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (board[pos][j] == board[i][j]) {
                    board[pos][j] *= 2;
                    board[i][j] = 0;
                    pos--;
                } else if (board[pos][j] == 0) {
                    board[pos][j] = board[i][j];
                    board[i][j] = 0;
                } else {
                    pos--;
                    if (pos != i) {
                        board[pos][j] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
}

// Check if any tile is 2048
int checkWin() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 2048) return 1;
        }
    }
    return 0;
}

// Check if no moves are possible
int checkGameOver() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) return 0;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return 0;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return 0;
        }
    }
    return 1;
}