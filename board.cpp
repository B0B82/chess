#include "board.h"

Board::Board(): moveCounter(1), flag(false), bufferX(0), bufferY(0), bufferIsWhite(0), 
        bufferView("  "), bufferState(false) {};
Board::~Board() {};

bool Board::getIsWhite(int poition) {
    return this->isWhite[poition];
};

void Board::Board::setBoardCell( int position, std::string view, bool state, bool isWhite) {
    this->boardView[position] = view;
    this->boardState[position] = state;
    this->isWhite[position] = isWhite;
}

std::string Board::getBoardViev(int position) const {
    return this->boardView[position];
}

int Board::getX() {
    while( true ) {
        char x;
        std::cin >> x;
        
        if ( x >= 'a' && x <= 'h') {
            return x - 'a';
        // } else if ( std::cin.fail() ) {
        } else if ( x == '*' ) { 
            save();
            std::cout << "File saved" << std::endl;
        } else if ( x == '-' ) { 
            load();
            std::cout << "File loaded" << std::endl;
        } else {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Oops, that input is invalid.  Please try again." << std::endl;
        } 
    }
}

int Board::getY() {
        while( true ) {
        int y;
        std::cin >> y;

        if ( y > 0 && y < 9 ) {
            return y - 1;
        // } else if (std::cin.fail() ) {
        } else {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Oops, that input is invalid.  Please try again." << std::endl;
        }
    }
}

void Board::gameProcess() {
        while( std::cin ) {
            int x = getX();
            int y = getY();
            moveChesspiece(x, y);
        }
}

void Board::moveChesspiece(int x, int y) {
    Chesspiece ch;

    if ( getMoveCounter() % 2 == 1 ) {
        if ( !getBoardState(x + y*8) ) {
            refresh();
        }

        if ( flag ) {
            if ( !getIsWhite(x + y*8) ) { // black
                bufferView = getBoardViev(x + y*8);
                bufferState = getBoardState(x + y * 8);
                bufferX = x;
                bufferY = y;
                bufferIsWhite = getIsWhite(x + y*8);
                moveCounter++;
                flag = !flag;
            } else {
                refresh();
            }
        } else {
            if ( getIsWhite(x + y*8) ) { // white
                bufferView = getBoardViev(x + y*8);
                bufferState = getBoardState(x + y * 8);
                bufferX = x;
                bufferY = y;
                bufferIsWhite = getIsWhite(x + y*8);
                moveCounter++;
                flag = !flag;
            } else {
                refresh();
            }
        }
    } else {
        if ( bufferX == x && bufferY == y ) {
            moveCounter--;
            flag = !flag;
            refresh();
        }

        setBoardCell(bufferX + 8*bufferY);
        
         if ( bufferView == ch.br || bufferView == ch.wr ) { // ♜
             //if ( bufferX != x || bufferY != y ) {
             //    moveCounter--;
             //    flag = !flag;
             //    setBoardCell(bufferX + 8*bufferY, bufferView, bufferState, bufferIsWhite);
             //    refresh();
             //}

             if ( bufferX == x ) {
                 if ( bufferY < y ) {
                     for ( int i = y; i > bufferY; i-- ) {
                         if ( getBoardState(x + 8*i) ) {
                             moveCounter--;
                             flag = !flag;
                             setBoardCell(bufferX + 8*bufferY, bufferView, bufferState, bufferIsWhite);
                             refresh();
                         }
                     }
                 }

                 if ( bufferY > y ) {
                     for ( int i = y; i < bufferY; i++ ) {
                         if ( getBoardState(x + 8*i) ) {
                             moveCounter--;
                             flag = !flag;
                             setBoardCell(bufferX + 8*bufferY, bufferView, bufferState, bufferIsWhite);
                             refresh();
                         }
                     }
                 }
             }
             if ( bufferY == y ) {
                 if ( bufferX < x ) {
                     for ( int i = x; i > bufferX; i-- ) {
                         if ( getBoardState(i + 8*y) ) {
                             moveCounter--;
                             flag = !flag;
                             setBoardCell(bufferX + 8*bufferY, bufferView, bufferState, bufferIsWhite);
                             refresh();
                         }
                     }
                 }

                 if ( bufferX > x ) {
                     for ( int i = x; i < bufferX; i++ ) {
                         if ( getBoardState(i + 8*y) ) {
                             moveCounter--;
                             flag = !flag;
                             setBoardCell(bufferX + 8*bufferY, bufferView, bufferState, bufferIsWhite);
                             refresh();
                         }
                     }
                 }
             }


         }
        setBoardCell(x + y*8, bufferView, bufferState, flag);
        print();
        // std::cout << " ["<< bufferX+1 << bufferY+1 << "], ";
        // std::cout << " ["<< x+1 << y+1 << "] \n\t";
        moveCounter++;
    }
}

bool Board::getBoardState(int position) const {
    return this->boardState[position];
}

int Board::getMoveCounter() const {
    return this->moveCounter;
};

void Board::print() {
    system("clear");
    std::cout << "\t   Console chess\n\n";
    std::cout << "\t a b c d e f g h\n";

    for ( int i = 0; i < 8; i++ ) {
        std::cout << "\t" << i + 1;
        for ( int j = 0; j < 8; j++ ) { std::cout << getBoardViev(j + i*8); }
        std::cout << i + 1 << "\n";
    }
    std::cout << "\t a b c d e f g h\n";
    std::cout << "\n\n";

    if ( !flag ) {
        std::cout << "\tWhite's move: ";
    } else {
        std::cout << "\tBlack's move: ";
    }

    std::cout << "move: [" << moveCounter << "], flag: [" << flag << "], bufferIsWhite: [" << bufferIsWhite
        << "], bufferView: [" << bufferView << "], bufferX: [" << bufferX << "], bufferY: [" << bufferY << "], bufferState: [" << bufferState << "]\n\t"; 
};

void Board::defaultPosition() {
    Chesspiece cp;

    for ( int i = 16; i < 56; i++ ) {
        setBoardCell(i);
    }

    for ( int i = 8; i < 16; i++ ) {
        setBoardCell(i, cp.wp, true, true);
        setBoardCell(i + 40, cp.bp, true);
    }

    setBoardCell(0, cp.wr, true, true);
    setBoardCell(7, cp.wr, true, true);
    setBoardCell(1, cp.wn, true, true);
    setBoardCell(6, cp.wn, true, true);
    setBoardCell(2, cp.wb, true, true);
    setBoardCell(5, cp.wb, true, true);
    setBoardCell(3, cp.wq, true, true);
    setBoardCell(4, cp.wk, true, true);

    setBoardCell(56, cp.br, true);
    setBoardCell(63, cp.br, true);
    setBoardCell(57, cp.bn, true);
    setBoardCell(62, cp.bn, true);
    setBoardCell(58, cp.bb, true);
    setBoardCell(61, cp.bb, true);
    setBoardCell(60, cp.bq, true);
    setBoardCell(59, cp.bk, true);
}

void Board::save() {
    std::ofstream fout;
    fout.open("file.txt", std::ofstream::trunc);
    if ( !fout.is_open() ) {
        throw ErrorFileException();
    } else {
        for ( int i = 0; i < 64; i++ ) {
            fout << boardView[i];
        }
        for (int i = 0; i < 64; i++) {
            fout << boardState[i];
        }
        for (int i = 0; i < 64; i++) {
            fout << isWhite[i];
        }
        fout << moveCounter;
        fout << flag;
        fout << bufferIsWhite;
        fout << bufferView;
        fout << bufferX;
        fout << bufferY;
        fout << bufferState;
    }
    fout.close();
}

void Board::load() {
    std::ifstream fin;
    fin.open("file.txt");
    if ( !fin.is_open() ) {
        throw ErrorFileException();
    } else {
        std::string str;
        std::getline(fin, str);
        for ( int i = 0, j = 128, k = 192; i < 128 && j < 192 && k < 256;
            i += 2, j++, k++) {
            setBoardCell(i/2, std::string{str[i], str[i+1]},
                (str[j] > 0) ? true: false, (str[k] > 0) ? true : false);
        }
        moveCounter = int(str[256] - 48);
        flag = (str[257] > 0)? true : false;
        if (getMoveCounter() % 2 == 0) {
            flag = (str[257] > 0) ? true : false;
            bufferIsWhite = (str[258] > 0) ? true : false;
            bufferView = std::string{ str[259], str[260] };
            bufferX = int(str[261] - 48);
            bufferY = int(str[262] - 48);
            bufferState = (str[263] > 0) ? true : false;
        }


        print();
        std::cout << "Saved data, move: [" << moveCounter << "], flag: [" << flag << "], bufferIsWhite: [" << bufferIsWhite
        << "], bufferView: [" << bufferView << "], bufferX: [" << bufferX << "], bufferY: [" << bufferY << "], bufferState: [" << bufferState << "]\n\t";

        // refresh();
    }
    fin.close();
}

void Board::refresh() {
    print();
    gameProcess();
    return;
}