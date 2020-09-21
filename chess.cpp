#include <iostream>

bool boardState[7][7];
bool bufferFlag;
int moveCounter = 0;
std::string boardView[7][7];
std::string buffer;


class Chesspiece {
    public:
        std::string wk, wq, wb, wn, wr, wp, bk, bq, bb, bn, br, bp;
        Chesspiece() : wk{ "♔ " }, wq{ "♕ " }, wb{ "♗ " }, wn{ "♘ " }, wr{ "♖ " }, wp{ "♙ " }, 
                    bk{ "♚ " }, bq{ "♛ " }, bb{ "♝ " }, bn{ "♞ " }, br{ "♜ " }, bp{ "♟ " } {};
        ~Chesspiece() {};
};

void print() {
    system("clear");
    std::cout << "\t   Console chess\n\n";
    std::cout << "\t a b c d e f g h\n";

    for ( int i = 0; i < 8; i++ ) {
        std::cout << "\t" << i + 1;
        for ( int j = 0; j < 8; j++ ) { std::cout << boardView[0][j + i*8]; }
        std::cout << i + 1 << "\n";
    }
    std::cout << "\t a b c d e f g h\n";
    std::cout << "\n\n";

    if ( moveCounter % 2 ) {
        std::cout << "\tBlack's move:\n";
    } else {
        std::cout << "\tWhite's move:\n";
    }

};

void defaultPosition() {
    Chesspiece cp;

    for ( int i = 16; i < 56; i++ ) {
        boardView[0][i] = "* ";
    }
    for ( int i = 8; i < 16; i++ ) {
        boardView[0][i] = cp.bp;
        boardState[0][i] = true;
        boardView[0][i + 40] = cp.wp;
        boardState[0][i + 40] = true;
    }

    print();
}

int main() {
    defaultPosition();
    return 0;
};

