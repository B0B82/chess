#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>

class Chesspiece {
    public:
        std::string wk, wq, wb, wn, wr, wp, bk, bq, bb, bn, br, bp;
        Chesspiece() : wk{ "wk" }, wq{ "wq" }, wb{ "wb" }, wn{ "wn" }, wr{ "wr" }, wp{ "wp" }, 
                    bk{ "bk" }, bq{ "bq" }, bb{ "bb" }, bn{ "bn" }, br{ "br" }, bp{ "bp" } {};
        ~Chesspiece() {};
};

#endif //CHESSPIECE
