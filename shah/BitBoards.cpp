//
//  BitBoards.cpp
//  csc180game
//
//  Created by arash parnia on 3/18/15.
//  Copyright (c) 2015 arash. All rights reserved.
//

#include "BitBoards.h"
/*
std::stack<int> parseBitBoard(BITBOARD b){
    std::stack<int> board;
    for (int i = 0; i < 64 ; i++){
        if ((b & 1ULL) == 1){ board.push(i);}
        b = b >> 1ULL;
    }
    return board;
}
void printBitBoard(BITBOARD board) {
    printf("BITBOARD\n");
    for(int i = 8; i >0 ; i--){
        for (int j = 8; j>0 ; j--){
            if ( 1ULL & board )printf("1");else printf("0");
            board = board >>1ULL;
        }
        printf("\n");
    }
    printf("\n");
}


BITBOARD boardToBitBoard(BOARD *b){
    BITBOARD bitboard = 0ULL;
    for (int i=0; i < 12;i++) bitboard = (bitboard | (1ULL << b->PIECES[i].position));
    return bitboard;
}

void generateKingMoves(BOARD *b,PIECE *p,std::stack<MOVE> *moves){
    BITBOARD mask = 0x00070507;
    BITBOARD position =(1ULL<<(p->position-1));
    BITBOARD lefttrim = 0x0101010101010101;
    BITBOARD righttrim = 0x8080808080808080;
    BITBOARD toptrim = 0XFF00000000000000;
    //printf("POSITION IS AT :%d",p->position);
    if (p->position < 10) mask >>= (10 - p->position);
    if (p->position > 10) mask <<= ( p->position- 10) ;
    
    //showState(b);
    //printBitBoard(mask);
    
    if ((position &  lefttrim) != 0) mask =  (mask | righttrim)^ righttrim  ;
    if ((position &  righttrim) != 0) mask =  (mask | lefttrim)^lefttrim ;
    mask =  (mask | toptrim)^toptrim;
    //printBitBoard(mask);
    
    stack<int> topositions;
    topositions =  parseBitBoard(mask);
    
    while (!topositions.empty()) {
        MOVE move;
        move.from = p->position;
        move.to = topositions.top();
        moves->push(move);
        topositions.pop();
    }
    /*
     10000000
     10000000
     10000000
     10000000
     10000000
     10000000
     10000000
     10000000
     */
    // for bitboard at position 10
    /*
     00000000
     00000000
     00000000
     00000000
     00000000
     00000111
     000001K1
     00000111
     */
//}
/*
void generateKnightMoves(BOARD *b,PIECE *p,std::stack<MOVE> *moves){
    BITBOARD mask = 0xA1100110A;
    BITBOARD position =(1ULL<<(p->position-1));
    BITBOARD lefttrim = 0x3030303030303;
    BITBOARD righttrim = 0xC0C0C0C0C0C0C0;
    BITBOARD toptrim = 0XFF00000000000000;
    //printf("POSITION IS AT :%d",p->position);
    if (p->position < 19) mask >>= (19 - p->position);
    if (p->position > 19) mask <<= ( p->position- 19) ;
    
    //showState(b);
    //printBitBoard(mask);
    
    if ((position &  lefttrim) != 0) mask =  (mask | righttrim)^ righttrim  ;
    if ((position &  righttrim) != 0) mask =  (mask | lefttrim)^lefttrim ;
    mask =  (mask | toptrim)^toptrim;
    //printBitBoard(mask);
    
    stack<int> topositions;
    topositions =  parseBitBoard(mask);
    
    while (!topositions.empty()) {
        MOVE move;
        move.from = p->position;
        move.to = topositions.top();
        moves->push(move);
        topositions.pop();
    }
    /*
     10000000
     10000000
     10000000
     10000000
     10000000
     10000000
     10000000
     10000000
     */
    // for bitboard at position 19
    /*
     00000000
     00000000
     00001010
     00010001
     00000X00
     00010001
     00001010
     */
//}
