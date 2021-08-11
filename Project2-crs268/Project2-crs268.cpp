#include <iostream>

using namespace std;

static const int EV1 = 0;
static const int EV2 = 1;
static const int EV3 = 2;
static const int EV4 = 3;

static const int MIN = -1000;
static const int MAX = 1000;
static const int SIZE = 3;
char p1 = 'x', p2 = 'o', open = '_';
char gameBoard[3][3] = {{open, open, open}, {open, open, open}, {open, open, open}};

struct Move {
    int row = -1;
    int col = -1;
};

struct Choice {
    int value = 0;
    int pathLen = 0;
    int nodes = 0;
    Move nextMove;
};

//Heuristic evaluator that values end state
int evaluator(char (&board)[3][3], int evalNum) {
    int ret = 0;
    switch (evalNum) {
        case 0: //values win states
        for (int r = 0; r < SIZE; r++) {
            if (board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
                if (board[r][0] == p1) {
                    return 10;
                }
                else if (board[r][0] == p2) {
                    return -10;
                }
            }
        }

        for (int c = 0; c < SIZE; c++) {
            if (board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
                if (board[0][c] == p1) {
                    return 10;
                }
                else if (board[0][c] == p2) {
                    return -10;
                }
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == p1) {
                return 10;
            }
            else if (board[0][0] == p2) {
                return -10;
            }
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == p1) {
                return 10;
            }
            else if (board[0][2] == p2) {
                return -10;
            }
        }
        return 0;
        break;

        case 1: //values how many in a row
        //rows
        for (int r = 0; r < SIZE; r++) {
            if (board[r][0] == p1 && board[r][1] == p2 && board[r][2] == p2) {
                ret += 10;
                ret -= 20;
            }
            else if (board[r][0] == p2 && board[r][1] == p1 && board[r][2] == p2) {
                ret += 10;
                ret -= 20;
            }
            else if (board[r][0] == p2 && board[r][1] == p2 && board[r][2] == p1) {
                ret += 10;
                ret -= 20;
            }
            else if (board[r][0] == p2 && board[r][1] == p1 && board[r][2] == p1) {
                ret += 20;
                ret -= 10;
            }
            else if (board[r][0] == p1 && board[r][1] == p2 && board[r][2] == p1) {
                ret += 20;
                ret -= 10;
            }
            else if (board[r][0] == p1 && board[r][1] == p1 && board[r][2] == p2) {
                ret += 20;
                ret -= 10;
            }
            else if (board[r][0] == p1 && board[r][1] == p1 && board[r][2] == p1) {
                ret += 30;
            }
            else if (board[r][0] == p2 && board[r][1] == p2 && board[r][2] == p2) {
                ret -= 30;
            }
        }
        //columns
        for (int c = 0; c < SIZE; c++) {
            if (board[0][c] == p1 && board[1][c] == p2 && board[2][c] == p2) {
                ret += 10;
                ret -= 20;
            }
            else if (board[0][c] == p2 && board[1][c] == p1 && board[2][c] == p2) {
                ret += 10;
                ret -= 20;
            }
            else if (board[0][c] == p2 && board[1][c] == p2 && board[2][c] == p1) {
                ret += 10;
                ret -= 20;
            }
            else if (board[0][c] == p2 && board[1][c] == p1 && board[2][c] == p1) {
                ret += 20;
                ret -= 10;
            }
            else if (board[0][c] == p1 && board[1][c] == p2 && board[2][c] == p1) {
                ret += 20;
                ret -= 10;
            }
            else if (board[0][c] == p1 && board[1][c] == p1 && board[2][c] == p2) {
                ret += 20;
                ret -= 10;
            }
            else if (board[0][c] == p1 && board[1][c] == p1 && board[2][c] == p1) {
                ret += 30;
            }
            else if (board[0][c] == p2 && board[1][c] == p2 && board[2][c] == p2) {
                ret -= 30;
            }
        }
        //first diagonal
        if (board[0][0] == p1 && board[1][1] == p2 && board[2][2] == p2) {
            ret += 10;
            ret -= 20;
        }
        else if (board[0][0] == p2 && board[1][1] == p1 && board[2][2] == p2) {
            ret += 10;
            ret -= 20;
        }
        else if (board[0][0] == p2 && board[1][1] == p2 && board[2][2] == p1) {
            ret += 10;
            ret -= 20;
        }
        else if (board[0][0] == p2 && board[1][1] == p1 && board[2][2] == p1) {
            ret += 20;
            ret -= 10;
        }
        else if (board[0][0] == p1 && board[1][1] == p2 && board[2][2] == p1) {
            ret += 20;
            ret -= 10;
        }
        else if (board[0][0] == p1 && board[1][1] == p1 && board[2][2] == p2) {
            ret += 20;
            ret -= 10;
        }
        else if (board[0][0] == p1 && board[1][1] == p1 && board[2][2] == p1) {
            ret += 30;
        }
        else if (board[0][0] == p2 && board[1][1] == p2 && board[2][2] == p2) {
            ret -= 30;
        }
        //other diagonal
        if (board[0][2] == p1 && board[1][1] == p2 && board[2][0] == p2) {
            ret += 10;
            ret -= 20;
        }
        else if (board[0][2] == p2 && board[1][1] == p1 && board[2][0] == p2) {
            ret += 10;
            ret -= 20;
        }
        else if (board[0][2] == p2 && board[1][1] == p2 && board[2][0] == p1) {
            ret += 10;
            ret -= 20;
        }
        else if (board[0][2] == p2 && board[1][1] == p1 && board[2][0] == p1) {
            ret += 20;
            ret -= 10;
        }
        else if (board[0][2] == p1 && board[1][1] == p2 && board[2][0] == p1) {
            ret += 20;
            ret -= 10;
        }
        else if (board[0][2] == p1 && board[1][1] == p1 && board[2][0] == p2) {
            ret += 20;
            ret -= 10;
        }
        else if (board[0][2] == p1 && board[1][1] == p1 && board[2][0] == p1) {
            ret += 30;
        }
        else if (board[0][2] == p2 && board[1][1] == p2 && board[2][0] == p2) {
            ret -= 30;
        }
        return ret;
        break;

        case 2: //prioritizes blocking
        for (int r = 0; r < SIZE; r++) {
            if (board[r][0] == board[r][1] && board[r][1] != board[r][2]) {
                if (board[r][2] == p1) {
                    return 10;
                }
                else if (board[r][2] == p2) {
                    return -10;
                }
            }
            if (board[r][0] != board[r][1] && board[r][1] == board[r][2]) {
                if (board[r][0] == p1) {
                    return 10;
                }
                else if (board[r][0] == p2) {
                    return -10;
                }
            }
            if (board[r][0] != board[r][1] && board[r][1] != board[r][2] && board[r][0] == board[r][2]) {
                if (board[r][1] == p1) {
                    return 10;
                }
                else if (board[r][1] == p2) {
                    return -10;
                }
            }
        }

        for (int c = 0; c < SIZE; c++) {
            if (board[0][c] == board[1][c] && board[1][c] != board[2][c]) {
                if (board[2][c] == p1) {
                    return 10;
                }
                else if (board[2][c] == p2) {
                    return -10;
                }
            }
            if (board[0][c] != board[1][c] && board[1][c] == board[2][c]) {
                if (board[0][c] == p1) {
                    return 10;
                }
                else if (board[0][c] == p2) {
                    return -10;
                }
            }
            if (board[0][c] != board[1][c] && board[1][c] != board[2][c] && board[0][c] == board[2][c]) {
                if (board[1][c] == p1) {
                    return 10;
                }
                else if (board[1][c] == p2) {
                    return -10;
                }
            }
        }

        if (board[0][0] != board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == p1) {
                return 10;
            }
            else if (board[0][0] == p2) {
                return -10;
            }
        }
        if (board[0][0] == board[1][1] && board[1][1] != board[2][2]) {
            if (board[2][2] == p1) {
                return 10;
            }
            else if (board[2][2] == p2) {
                return -10;
            }
        }
        if (board[0][0] != board[1][1] && board[1][1] != board[2][2] && board[0][0] == board[2][2]) {
            if (board[1][1] == p1) {
                return 10;
            }
            else if (board[1][1] == p2) {
                return -10;
            }
        }

        if (board[0][2] != board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == p1) {
                return 10;
            }
            else if (board[0][2] == p2) {
                return -10;
            }
        }
        if (board[0][2] == board[1][1] && board[1][1] != board[2][0]) {
            if (board[2][0] == p1) {
                return 10;
            }
            else if (board[2][0] == p2) {
                return -10;
            }
        }
        if (board[0][2] != board[1][1] && board[1][1] != board[2][0] && board[0][2] == board[2][0]) {
            if (board[1][1] == p1) {
                return 10;
            }
            else if (board[1][1] == p2) {
                return -10;
            }
        }
        return 0;
        break;

        case 3: //values diagonals more than rows or columns
        for (int r = 0; r < SIZE; r++) {
            if (board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
                if (board[r][0] == p1) {
                    ret += 0;
                }
                else if (board[r][0] == p2) {
                    ret -= 0;
                }
            }
        }

        for (int c = 0; c < SIZE; c++) {
            if (board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
                if (board[0][c] == p1) {
                    ret += 0;
                }
                else if (board[0][c] == p2) {
                    ret -= 0;
                }
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == p1) {
                return 10;
            }
            else if (board[0][0] == p2) {
                return -10;
            }
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == p1) {
                return 10;
            }
            else if (board[0][2] == p2) {
                return -10;
            }
        }
        return 0;
        break;

        default:
        return 0;
        break;
    }    

    return 0;
}

//recursive minimax function that uses alpha-beta pruning to evaluate choices
Choice minimaxAB(char (&board)[SIZE][SIZE], int depth, bool maxPlayer, int a, int b, int evalNum, int path, int numNodes) {
    Choice bestMove;
    bestMove.value = 0;
    bestMove.pathLen = path;
    bestMove.nodes = numNodes;
    Choice newMove;
    int best;
    int val;
    //int len = SIZE * SIZE;
    int largest = 1;
    
    //if leaf node
    if (depth == largest) {
        bestMove.value = evaluator(board, evalNum);
        return bestMove;
    }

    //if max player
    if (maxPlayer == 1) {
        best = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) { 
                if (board[i][j] == open) {
                    board[i][j] = p1;
                    newMove = minimaxAB(board, depth + 1, !maxPlayer, a, b, evalNum, path, numNodes);
                    bestMove.nodes++;
                    board[i][j] = open;
                    if (best < newMove.value) {
                        best = newMove.value;
                        bestMove.pathLen++;
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
        bestMove.value = best;
        return bestMove;
    }

    //if min player
    else {
        best = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == open) {
                    board[i][j] = p2;
                    newMove = minimaxAB(board, depth + 1, !maxPlayer, a, b, evalNum, path, numNodes);
                    bestMove.nodes++;
                    board[i][j] = open;

                    if (best > newMove.value) {
                        best = newMove.value;
                        bestMove.pathLen++;
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
        bestMove.value = best;
        return bestMove;
    }
}

//function that calls minimax and evaluates which move is the best
Choice findBest(char (&board)[3][3], bool maxPlayer, int evalNum) {
    Choice bestMove;
    Choice newMove;

    //if max player
    if (maxPlayer) {
        bestMove.nextMove.row = -1;
        bestMove.nextMove.col = -1;
        bestMove.value = -10000;

        cout << "Player 1\n";
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == open) {
                    board[i][j] = p1;
                    
                    newMove = minimaxAB(board, 0, maxPlayer, MIN, MAX, evalNum, 0, 0);

                    board[i][j] = open;

                    if (newMove.value > bestMove.value) {
                        bestMove.nextMove.row = i;
                        bestMove.nextMove.col = j;
                        bestMove.value = newMove.value;
                        bestMove.pathLen = newMove.pathLen;
                        bestMove.nodes = newMove.nodes;
                    }
                }
            }
        }
    }

    //if min player
    else {
        bestMove.nextMove.row = -1;
        bestMove.nextMove.col = -1;
        bestMove.value = 10000;

        cout << "Player 2\n";
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == open) {
                    board[i][j] = p2;
                    
                    newMove = minimaxAB(board, 0, maxPlayer, MIN, MAX, evalNum, 0, 0);

                    board[i][j] = open;

                    if (newMove.value < bestMove.value) {
                        bestMove.nextMove.row = i;
                        bestMove.nextMove.col = j;
                        bestMove.value = newMove.value;
                        bestMove.pathLen = newMove.pathLen;
                        bestMove.nodes = newMove.nodes;
                    }
                }
            }
        }
    }

    return bestMove;
}

//function that decides if the game is over
bool endGame(char (&board)[3][3], bool maxPlayer) {
    if (maxPlayer) {
       for (int i = 0; i < SIZE; i++) {
            bool rowWin = true;
            bool colWin = true;
            for (int j = 0; j < SIZE; j++) {
               rowWin &= board[i][j] == p1;
               colWin &= board[j][i] == p1;
            }
            if (rowWin || colWin) {
                return true;
            }
        }
        
        if (board[0][0] == p1 && board[1][1] == p1 && board[2][2] == p1) {
            return true;
        }
        if (board[0][2] == p1 && board[1][1] == p1 && board[2][0] == p1) {
            return true;
        }
    }
    else {
        for (int i = 0; i < SIZE; i++) {
            bool rowWin = true;
            bool colWin = true;
            for (int j = 0; j < SIZE; j++) {
               rowWin &= board[i][j] == p2;
               colWin &= board[j][i] == p2;
            }
            if (rowWin || colWin) {
                return true;
            }
        }
        
        if (board[0][0] == p2 && board[1][1] == p2 && board[2][2] == p2) {
            return true;
        }
        if (board[0][2] == p2 && board[1][1] == p2 && board[2][0] == p2) {
            return true;
        }
    }
    return false;
}

//function that prints the game board
void print(char (&board)[3][3]) {
    cout << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |\n";
    cout << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |\n";
    cout << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |\n\n";
}

//function that clears the game board
void reset() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            gameBoard[i][j] = open;
        }
    }

    print(gameBoard);
}

int main() {
    bool endState = false;
    bool player = true;
    int winP1 = 0;
    int winP2 = 0;

    int gamePath1 = 0;
    int gamePath2 = 0;
    int gamePath3 = 0;
    int gamePath4 = 0;
    int gamePath5 = 0;
    int gamePath6 = 0;

    int gameNodes1 = 0;
    int gameNodes2 = 0;
    int gameNodes3 = 0;
    int gameNodes4 = 0;
    int gameNodes5 = 0;
    int gameNodes6 = 0;

    Choice move;
    move.nextMove.row = -1;
    move.nextMove.col = -1;

    cout << "Starting Trial 1: \n";
    reset();

    while(!endState) {
        if (player) {
            move = findBest(gameBoard, player, EV1);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = p1;
        }
        else {
            move = findBest(gameBoard, player, EV2);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = 'o';
        }

        gamePath1 += move.pathLen;
        gameNodes1 += move.nodes;

        print(gameBoard);
        cout << "Path length: " << move.pathLen << "\n";
        cout << "Total nodes: " << move.nodes << "\n\n";

        if (endGame(gameBoard, player)) {
            endState = true;
        }
        player = !player;
    }

    if (move.value > 0) {
        cout << "Player 1 (X) wins!!!\n";
        winP1++;
    } 
    else if (move.value < 0) {
        cout << "Player 2 (O) wins!!!\n";
        winP2++;
    }
    else {
        cout << "Tie Game\n";
    }

    cout << "Total game path length: " << gamePath1 << "\n";
    cout << "Total game node count: " << gameNodes1 << "\n\n";

    endState = false;

    cout << "Starting Trial 2: \n";
    reset();

    while(!endState) {
        if (player) {
            move = findBest(gameBoard, player, EV1);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = p1;
        }
        else {
            move = findBest(gameBoard, player, EV3);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = 'o';
        }

        gamePath2 += move.pathLen;
        gameNodes2 += move.nodes;

        print(gameBoard);
        cout << "Path length: " << move.pathLen << "\n";
        cout << "Total nodes: " << move.nodes << "\n\n";

        if (endGame(gameBoard, player)) {
            endState = true;
        }
        player = !player;
    }

    if (move.value > 0) {
        cout << "Player 1 (X) wins!!!\n";
        winP1++;
    } 
    else if (move.value < 0) {
        cout << "Player 2 (O) wins!!!\n";
        winP2++;
    }
    else {
        cout << "Tie Game\n";
    }

    cout << "Total game path length: " << gamePath2 << "\n";
    cout << "Total game node count: " << gameNodes2 << "\n\n";

    endState = false;

    cout << "Starting Trial 3: \n";
    reset();

    while(!endState) {
        if (player) {
            move = findBest(gameBoard, player, EV1);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = p1;
        }
        else {
            move = findBest(gameBoard, player, EV2);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = 'o';
        }

        gamePath3 += move.pathLen;
        gameNodes3 += move.nodes;

        print(gameBoard);
        cout << "Path length: " << move.pathLen << "\n";
        cout << "Total nodes: " << move.nodes << "\n\n";

        if (endGame(gameBoard, player)) {
            endState = true;
        }
        player = !player;
    }

    if (move.value > 0) {
        cout << "Player 1 (X) wins!!!\n";
        winP1++;
    } 
    else if (move.value < 0) {
        cout << "Player 2 (O) wins!!!\n";
        winP2++;
    }
    else {
        cout << "Tie Game\n";
    }

    cout << "Total game path length: " << gamePath3 << "\n";
    cout << "Total game node count: " << gameNodes3 << "\n\n";

    endState = false;

    cout << "Starting Trial 4: \n";
    reset();

    while(!endState) {
        if (player) {
            move = findBest(gameBoard, player, EV2);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = p1;
        }
        else {
            move = findBest(gameBoard, player, EV3);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = 'o';
        }

        gamePath4 += move.pathLen;
        gameNodes4 += move.nodes;

        print(gameBoard);
        cout << "Path length: " << move.pathLen << "\n";
        cout << "Total nodes: " << move.nodes << "\n\n";

        if (endGame(gameBoard, player)) {
            endState = true;
        }
        player = !player;
    }

    if (move.value > 0) {
        cout << "Player 1 (X) wins!!!\n";
        winP1++;
    } 
    else if (move.value < 0) {
        cout << "Player 2 (O) wins!!!\n";
        winP2++;
    }
    else {
        cout << "Tie Game\n";
    }

    cout << "Total game path length: " << gamePath4 << "\n";
    cout << "Total game node count: " << gameNodes4 << "\n\n";

    endState = false;

    cout << "Starting Trial 5: \n";
    reset();

    while(!endState) {
        if (player) {
            move = findBest(gameBoard, player, EV2);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = p1;
        }
        else {
            move = findBest(gameBoard, player, EV4);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = 'o';
        }

        gamePath5 += move.pathLen;
        gameNodes5 += move.nodes;

        print(gameBoard);
        cout << "Path length: " << move.pathLen << "\n";
        cout << "Total nodes: " << move.nodes << "\n\n";

        if (endGame(gameBoard, player)) {
            endState = true;
        }
        player = !player;
    }

    if (move.value > 0) {
        cout << "Player 1 (X) wins!!!\n";
        winP1++;
    } 
    else if (move.value < 0) {
        cout << "Player 2 (O) wins!!!\n";
        winP2++;
    }
    else {
        cout << "Tie Game\n";
    }

    cout << "Total game path length: " << gamePath5 << "\n";
    cout << "Total game node count: " << gameNodes5 << "\n\n";

    endState = false;

    cout << "Starting Trial 6: \n";
    reset();

    while(!endState) {
        if (player) {
            move = findBest(gameBoard, player, EV3);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = p1;
        }
        else {
            move = findBest(gameBoard, player, EV4);
            cout << "Move at R:" << move.nextMove.row << " C:" << move.nextMove.col << "\n";
            gameBoard[move.nextMove.row][move.nextMove.col] = 'o';
        }

        gamePath6 += move.pathLen;
        gameNodes6 += move.nodes;

        print(gameBoard);
        cout << "Path length: " << move.pathLen << "\n";
        cout << "Total nodes: " << move.nodes << "\n\n";

        if (endGame(gameBoard, player)) {
            endState = true;
        }
        player = !player;
    }

    if (move.value > 0) {
        cout << "Player 1 (X) wins!!!\n";
        winP1++;
    } 
    else if (move.value < 0) {
        cout << "Player 2 (O) wins!!!\n";
        winP2++;
    }
    else {
        cout << "Tie Game\n";
    }

    cout << "Total game path length: " << gamePath6 << "\n";
    cout << "Total game node count: " << gameNodes6 << "\n\n";

    float p1WL = winP1 / winP2;
    float p2WL = winP2 / winP1;
    cout << "P1 W/L ratio: " << p1WL << "\n";
    cout << "P2 W/L ratio: " << p2WL << "\n";

    endState = false;

    return 0;
}









