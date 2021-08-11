#include <iostream>

using namespace std;

static const int MIN = -1000;
static const int MAX = 1000;
static const int SIZE = 3;
char gameBoard[3][3] = {{'_', '_', '_'}, {'_', '_', '_'}, {'_', '_', '_'}};

char p1 = 'x', p2 = 'o', open = '_';
struct Move {
    int row = -1;
    int col = -1;
};

struct Choice {
    int value;
    Move nextMove;
};

Move genMoves(char board[3][3]) {
    Move moves[9];
    Move temp;
    int count;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == open) {
                temp.row = i;
                temp.col = j;
                moves[count] = temp;
                count++;
            }
        }
    }
    return *moves;
}

int evaluator(char (&board)[3][3], int evalNum) {
    switch (evalNum) {
        case 0: //values x and o with equal magnitude
        for (int r = 0; r < SIZE; r++) {
            if (board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
                if (board[r][0] == p1) {
                    return +10;
                }
                else if (board[r][0] == p2) {
                    return -10;
                }
            }
        }

        for (int c = 0; c < SIZE; c++) {
            if (board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
                if (board[0][c] == p1) {
                    return +10;
                }
                else if (board[0][c] == p2) {
                    return -10;
                }
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == p1) {
                return +10;
            }
            else if (board[0][0] == p2) {
                return -10;
            }
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == p1) {
                return +10;
            }
            else if (board[0][2] == p2) {
                return -10;
            }
        }
        break;

        case 1: //values x more than o
        for (int r = 0; r < SIZE; r++) {
            if (board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
                if (board[r][0] == p1) {
                    return +20;
                }
                else if (board[r][0] == p2) {
                    return -10;
                }
            }
        }

        for (int c = 0; c < SIZE; c++) {
            if (board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
                if (board[0][c] == p1) {
                    return +20;
                }
                else if (board[0][c] == p2) {
                    return -10;
                }
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == p1) {
                return +20;
            }
            else if (board[0][0] == p2) {
                return -10;
            }
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == p1) {
                return +20;
            }
            else if (board[0][2] == p2) {
                return -10;
            }
        }
        break;

        case 2: //values o more than x
        for (int r = 0; r < SIZE; r++) {
            if (board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
                if (board[r][0] == p1) {
                    return +10;
                }
                else if (board[r][0] == p2) {
                    return -20;
                }
            }
        }

        for (int c = 0; c < SIZE; c++) {
            if (board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
                if (board[0][c] == p1) {
                    return +10;
                }
                else if (board[0][c] == p2) {
                    return -20;
                }
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == p1) {
                return +10;
            }
            else if (board[0][0] == p2) {
                return -20;
            }
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == p1) {
                return +10;
            }
            else if (board[0][2] == p2) {
                return -20;
            }
        }
        break;

        case 3: //values diagonals more than rows or columns
        for (int r = 0; r < SIZE; r++) {
            if (board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
                if (board[r][0] == p1) {
                    return +10;
                }
                else if (board[r][0] == p2) {
                    return -10;
                }
            }
        }

        for (int c = 0; c < SIZE; c++) {
            if (board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
                if (board[0][c] == p1) {
                    return +10;
                }
                else if (board[0][c] == p2) {
                    return -10;
                }
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == p1) {
                return +100;
            }
            else if (board[0][0] == p2) {
                return -100;
            }
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == p1) {
                return +100;
            }
            else if (board[0][2] == p2) {
                return -100;
            }
        }
        break;

        default:
        return 0;
        break;
    }    

    return 0;
}

int minimaxAB(char (&board)[SIZE][SIZE], int depth, int node, bool maxPlayer, int a, int b, int evalNum) {
    int best;
    int val;
    int len = SIZE * SIZE;
    int largest = 3;

   /*  Move successors[len];
    Move tempMove;
    tempMove.row = -1;
    tempMove.col = -1; */

    /* for (int i = 0; i < len; i++) {
        successors[i] = tempMove;
    } */
    
    if (depth = largest) {
        best = evaluator(board, evalNum);
        return best;
    }

    /* int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == open) {
                tempMove.row = i;
                tempMove.col = j;
                successors[count] = temp;
                count++;
            }
        }
    }

    if (successors[0].row == -1 || successors[0].col == -1) {
        score = evaluator(board, evalNum);
        return score;
    } */

    if (maxPlayer == 1) {
        best = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) { 
                if (board[i][j] == open) {
                    board[i][j] = p1;
                    val = minimaxAB(board, depth + 1, node * 2 + i, false, a, b, evalNum);
                    board[i][j] = open;
                    if (best < val) {
                        best = val;
                    }
                    if (a < best) {
                        a = best;
                    }

                    if (b <= a) {
                        break;
                    }
                }
            }

            if (b <= a) {
                break;
            }
        }
        return best;
    }

    else {
        best = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == open) {
                    board[i][j] = p2;
                    val = minimaxAB(board, depth + 1, node * 2 + i, false, a, b, evalNum);
                    board[i][j] = open;

                    if (best > val) {
                        best = val;
                    }
                    if (b > best) {
                        b = best;
                    }

                    if (b <= a) {
                        break;
                    }
                }
            }

            if (b <= a) {
                break;
            }
        }
        return best;
    }
}

Choice findBest(char (&board)[3][3], bool maxPlayer, int evalNum) {
    Choice bestMove;
    int moveValue;

    bestMove.nextMove.row = -1;
    bestMove.nextMove.col = -1;
    bestMove.value = -1000;

    if (maxPlayer) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == open) {
                    board[i][j] = p1;
                    
                    moveValue = minimaxAB(board, 0, 0, maxPlayer, MIN, MAX, evalNum);

                    board[i][j] = open;

                    if (moveValue > bestMove.value) {
                        bestMove.nextMove.row = i;
                        bestMove.nextMove.col = j;
                        bestMove.value = moveValue;
                    }
                }
            }
        }
    }

    else {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == open) {
                    board[i][j] = p2;
                    
                    moveValue = minimaxAB(board, 0, 0, maxPlayer, MIN, MAX, evalNum);

                    board[i][j] = open;

                    if (moveValue < bestMove.value) {
                        bestMove.nextMove.row = i;
                        bestMove.nextMove.col = j;
                        bestMove.value = moveValue;
                    }
                }
            }
        }
    }

    return bestMove;
}

bool movesLeft(char (&board)[3][3]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == open) {
                return true;
            }
        }
    }
    return false;
}

void print(char (&board)[3][3]) {
    cout << "_______\n";
    cout << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |\n";
    cout << "_______\n";
    cout << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |\n";
    cout << "_______\n";
    cout << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |\n";
    cout << "_______\n";
}

int main() {
    bool endState = false;
    bool player = true;

    print(gameBoard);

    //while(!endState) {


        //if (!movesLeft()) {
        //    endState = true;
        //}
   // }

    return 0;
}









