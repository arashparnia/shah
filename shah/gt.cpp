
// SHAH
//  GasTank.cpp
//  csc180game
//
//  Created by arash parnia on 3/16/15.
//  Copyright (c) 2015 arash. All rights reserved.
//
#ifndef gt_cpp
#define gt_cpp


#endif


#include "gt.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <stack>
#include "Timer.h"
#include "ctype.h"
using namespace std;
timer t;
int MAXTIME ;
int MAXDEPTH ;
int evaluationcounter;
bool colorDisplay ;



void resetMOVES(){
    for (int i = 0; i<10; i++) {
        for (int j = 0; j<12; j++) {
            for (int k = 0; k<20; k++) {
                MOVES[i][j][k].FROM = OFFBOARD;
                MOVES[i][j][k].TO = OFFBOARD;
                MOVES[i][j][k].EFFECT = UNKNOWN;
            }
        }

        for (int l = 0; l < 99; l++) {
            SortedComputerMoveList[i][l].FROM=0;
            SortedComputerMoveList[i][l].TO=0;
            SortedComputerMoveList[i][l].EFFECT=0;
            SortedHumanMoveList[i][l].FROM=0;
            SortedHumanMoveList[i][l].TO=0;
            SortedHumanMoveList[i][l].EFFECT=0;
        }
    }
}
void resetMOVES(int depth,int side){
    for (int i = 0; i<99; i++) {
        if (side == COMPUTER) {
            SortedComputerMoveList[depth][i].FROM = 0;
            SortedComputerMoveList[depth][i].TO = 0;
            SortedComputerMoveList[depth][i].EFFECT = 0;
        }else {
            SortedHumanMoveList[depth][i].FROM = 0;
            SortedHumanMoveList[depth][i].TO = 0;
            SortedHumanMoveList[depth][i].EFFECT = 0;
        }
    }
    for (int j = 0; j<12; j++) {
        for (int k = 0; k<20; k++) {
            MOVES[depth][j][k].FROM = OFFBOARD;
            MOVES[depth][j][k].TO = OFFBOARD;
            MOVES[depth][j][k].EFFECT = UNKNOWN;
        }
    }
}
void setup(BOARD *b){
    resetMOVES();
    for (int i = 0; i < BOARDSIZE;i++) {b->POS[i]=OFFBOARD;}
    for (int i = 0;i<13;i++){
        b->PEICES[i].POS = OFFBOARD;
        b->PEICES[i].GAS = -1;
        b->PEICES[i].captured = false;
    }
    //    for (int i = 0;i<BOARDSIZE;i++){
    //        savedboardstate.POS[i] = b->POS[i];
    //    }
    //    for (int i = 1;i<13;i++){
    //        savedboardstate.PEICES[i].POS       = b->PEICES[i].POS;
    //        savedboardstate.PEICES[i].GAS       = b->PEICES[i].GAS;
    //        savedboardstate.PEICES[i].captured  = b->PEICES[i].captured;
    //    }
    b->POS[21]=EMPTY;   b->POS[22]=EMPTY;  b->POS[23]=WhiteBishopLeft;  b->POS[24]=WhiteQueen;          b->POS[25]=WhiteKing;   b->POS[26]=WhiteBishopRight;    b->POS[27]=EMPTY;   b->POS[28]=EMPTY;
    b->POS[31]=EMPTY;   b->POS[32]=EMPTY;  b->POS[33]=EMPTY;            b->POS[34]=WhiteKnightLeft;     b->POS[35]=EMPTY;       b->POS[36]=WhiteKnightRight;    b->POS[37]=EMPTY;   b->POS[38]=EMPTY;
    b->POS[41]=EMPTY;   b->POS[42]=EMPTY;  b->POS[43]=EMPTY;            b->POS[44]=EMPTY;               b->POS[45]=EMPTY;       b->POS[46]=EMPTY;               b->POS[47]=EMPTY;   b->POS[48]=EMPTY;
    b->POS[51]=EMPTY;   b->POS[52]=EMPTY;  b->POS[53]=EMPTY;            b->POS[54]=EMPTY;               b->POS[55]=EMPTY;       b->POS[56]=EMPTY;               b->POS[57]=EMPTY;   b->POS[58]=EMPTY;
    b->POS[61]=EMPTY;   b->POS[62]=EMPTY;  b->POS[63]=EMPTY;            b->POS[64]=EMPTY;               b->POS[65]=EMPTY;       b->POS[66]=EMPTY;               b->POS[67]=EMPTY;   b->POS[68]=EMPTY;
    b->POS[71]=EMPTY;   b->POS[72]=EMPTY;  b->POS[73]=EMPTY;            b->POS[74]=BlackKnightLeft;     b->POS[75]=EMPTY;       b->POS[76]=BlackKnightRight;    b->POS[77]=EMPTY;   b->POS[78]=EMPTY;
    b->POS[81]=EMPTY;   b->POS[82]=EMPTY;  b->POS[83]=BlackBishopLeft;  b->POS[84]=BlackQueen;          b->POS[85]=BlackKing;   b->POS[86]=BlackBishopRight;    b->POS[87]=EMPTY;   b->POS[88]=EMPTY;

    b->PEICES[WhiteKnightLeft].POS= 34;     b->PEICES[WhiteKnightLeft].GAS=3;   b->PEICES[WhiteKnightLeft].captured=false;
    b->PEICES[WhiteBishopLeft].POS=23;      b->PEICES[WhiteBishopLeft].GAS=3;   b->PEICES[WhiteBishopLeft].captured=false;
    b->PEICES[WhiteQueen].POS = 24;         b->PEICES[WhiteQueen].GAS=3;        b->PEICES[WhiteQueen].captured=false;
    b->PEICES[WhiteKing].POS = 25;          b->PEICES[WhiteKing].GAS=3;         b->PEICES[WhiteKing].captured=false;
    b->PEICES[WhiteBishopRight].POS = 26;   b->PEICES[WhiteBishopRight].GAS=3;  b->PEICES[WhiteBishopRight].captured=false;
    b->PEICES[WhiteKnightRight].POS = 36;   b->PEICES[WhiteKnightRight].GAS=3;  b->PEICES[WhiteKnightRight].captured=false;


    b->PEICES[BlackKnightLeft].POS=74;      b->PEICES[BlackKnightLeft].GAS=3;   b->PEICES[BlackKnightLeft].captured=false;
    b->PEICES[BlackBishopLeft].POS=83;      b->PEICES[BlackBishopLeft].GAS=3;   b->PEICES[BlackBishopLeft].captured=false;
    b->PEICES[BlackQueen].POS=84;           b->PEICES[BlackQueen].GAS=3;        b->PEICES[BlackQueen].captured=false;
    b->PEICES[BlackKing].POS=85;            b->PEICES[BlackKing].GAS=3;         b->PEICES[BlackKing].captured=false;
    b->PEICES[BlackBishopRight].POS=86;     b->PEICES[BlackBishopRight].GAS=3;  b->PEICES[BlackBishopRight].captured=false;
    b->PEICES[BlackKnightRight].POS=76;     b->PEICES[BlackKnightRight].GAS=3;  b->PEICES[BlackKnightRight].captured=false;


    blacknightmask = 72056494526300160;
//    11111111
//    11111111
//    11111111
//    00000000
//    00000000
//    00000000
//    00000000
//    00000000

    blackbishopmask = 556223496192;
//    00000000
//    00000000
//    00000000
//    10000001
//    10000001
//    10000001
//    00000000
//    00000000

    blackqueenmask= 29014469057249280;

//        00000000
//        01100111
//        00010100
//        10000001
//        10000001
//        10000001
//        00000000
//        00000000


    whiteknightmask = 4294967040;

//        00000000
//        00000000
//        00000000
//        00000000
//        11111111
//        11111111
//        11111111
//        00000000

    whitebishopmask = 36452663046438912;
//    00000000
//    10000001
//    10000001
//    10000001
//    00000000
//    00000000
//    00000000
//    00000000

    whitequeenmask = 36452667341340672;

//        00000000
//        10000001
//        10000001
//        10000001
//        11111111
//        11111111
//        00000000
//        00000000


}
void Display(BOARD *b){

    char displayBoard[31][53] = {

        {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'A', ' ', ' ', ' ', ' ', ' ', 'B', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', 'D', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', 'F', ' ', ' ', ' ', ' ', ' ', 'G', ' ', ' ', ' ', ' ', ' ', 'H', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', '7', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#'},
        {' ', ' ', '6', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#'},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', '5', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#'},
        {' ', ' ', '4', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#'},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', '3', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#'},
        {' ', ' ', '2', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#'},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', '1', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'A', ' ', ' ', ' ', ' ', ' ', 'B', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', 'D', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', 'F', ' ', ' ', ' ', ' ', ' ', 'G', ' ', ' ', ' ', ' ', ' ', 'H', ' ', ' ', ' '},
    };


    int index = 21;
    for (int i = 3; i <29 ; i = i+ 4){
        for (int j = 7;j<50;j=j+6){

            int piece = b->POS[index];
            int piecegas = b->PEICES[piece].GAS;

            if (piece != 0) displayBoard[i][j] = piece2Char[piece];


            if (piecegas > 0 )displayBoard[i+1][j] = gas2Char[piecegas];


            if (index%10 ==0) index++;
            else if (index%10 == 8)index+=2;
            index++;
        }
    }

    for(int i = 0; i < 31; i++){

        cout<<endl;

        for(int j = 0; j < 53; j++){
            if (colorDisplay){
                if(displayBoard[i][j]== '.') textcolor(BRIGHT,WHITE,GREEN);
                //else if (displayBoard[i][j]== ' ') textcolor(BRIGHT,BLACK,WHITE);
                else textcolor(RESET,WHITE,BLACK);
            }
            cout<<displayBoard[i][j]; //printf("%c",displayBoard[i][j]);

        }
    }

    cout<<endl<<endl;




}

void textcolor(int attr, int fg, int bg)
{ char command[13];
    sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
    printf("%s", command);
}

void printBoard(BOARD *b){
    int rank;int file;int sq;bool black = false;
    for(rank = RANK_1;rank <= RANK_7;++rank){
        printf("%d ",7-rank);
        for (file = FILE_A; file <= FILE_H;++file){
            sq = FR2SQ(file, rank);
            if (b->POS[sq]!= EMPTY){
                printf(" %1d",b->PEICES[b->POS[sq]].GAS);
                printf("%1c ",piece2Char[b->POS[sq]]);
            } else {
                if (black) printf(" ## ");
                else printf(" -- ");
            }
            if (black) black=false; else black = true;
        }
        //black =  ~black;
        if (black) black=false; else black = true;
        printf("\n\n");
    }
    printf("    A   B   C   D   E   F   G   H  \n");
}

void printBoardLarge(BOARD *b){
    int rank;int file;int sq;bool black = false;
    for(rank = RANK_1;rank <= RANK_7;++rank){
        printf("%d ",7-rank);
        for (file = FILE_A; file <= FILE_H;++file){
            sq = FR2SQ(file, rank);
            if (b->POS[sq]!= EMPTY){
                printf(" %1d",b->PEICES[b->POS[sq]].GAS);
                printf("%1c ",piece2Char[b->POS[sq]]);
            } else {
                if (black) printf(" ## ");
                else printf(" -- ");
            }
            if (black) black=false; else black = true;
        }
        //black =  ~black;
        if (black) black=false; else black = true;
        printf("\n\n");
    }
    printf("    A   B   C   D   E   F   G   H  \n");
}


void generateKnightMoves(BOARD *b,int p,int depth){
    for (int i = 0; i<18; i++) {
        MOVES[depth][p][i].FROM = OFFBOARD;
        MOVES[depth][p][i].TO = OFFBOARD;
    }
    if ((b->PEICES[p].GAS>0 && b->PEICES[p].GAS < 4) && !b->PEICES[p].captured){
        MOVE m;m.FROM=OFFBOARD;m.TO=OFFBOARD;m.EFFECT=0;int moveindex=0;
        m.FROM = b->PEICES[p].POS;
        bool side = SIDE(p);
        signed int KnightPsitions[8]={-21,-19,-12,-8,8,12,19,21};

        for (int i = 0; i<8; i++) {
            int t_pos =b->PEICES[p].POS;
            t_pos = t_pos + KnightPsitions[i];
            if (b->POS[t_pos]!=OFFBOARD){
                if (b->POS[t_pos]!= EMPTY){
                    if (COLOR(b->POS[t_pos])==side) {
                        m.TO= t_pos;
                        m.EFFECT = FRIENDLY_CAPTURE;
                        MOVES[depth][p][moveindex] = m;
                        moveindex++;
                        //printf("knight FRIENDLY CAPTURE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                    } else {
                        m.TO= t_pos;
                        m.EFFECT = ENEMY_CAPTURE;
                        MOVES[depth][p][moveindex] = m;
                        moveindex++;
                        //printf("knight ENEMY CAPTURE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                    }
                } else {
                    m.TO= t_pos;
                    m.EFFECT = NOTHING;
                    if(b->PEICES[p].GAS == 1) m.EFFECT = OUT_OF_GAS;
                    MOVES[depth][p][moveindex] = m;
                    moveindex++;
                    //printf("knight MOVE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                }
            }
        }
    }
    /*
     0000000000
     0000000000
     0000000000
     0000010100
     0000100010
     000000N000
     0000100010
     0000010100
     */
}
void generateKingMoves(BOARD *b,int p,int depth){
    for (int i = 0; i<18; i++) {
        MOVES[depth][p][i].FROM = OFFBOARD;
        MOVES[depth][p][i].TO = OFFBOARD;
    }
    if ((b->PEICES[p].GAS>0 && b->PEICES[p].GAS < 4) && !b->PEICES[p].captured){
        MOVE m;m.FROM=OFFBOARD;m.TO=OFFBOARD;m.EFFECT=0;int moveindex=0;
        m.FROM = b->PEICES[p].POS;
        bool side = SIDE(p);

        signed int KingPsitions[8]={-11,-10,-9,-1,1,9,10,11};

        for (int i = 0; i<8; i++) {
            int t_pos= b->PEICES[p].POS;
            t_pos = t_pos + KingPsitions[i];
            if (b->POS[t_pos]!=OFFBOARD){
                if (b->POS[t_pos]!= EMPTY){
                    if (COLOR(b->POS[t_pos])==side) {
                        m.TO= t_pos;
                        m.EFFECT = FRIENDLY_CAPTURE;
                        MOVES[depth][p][moveindex] = m;
                        moveindex++;
                        //printf("King FRIENDLY CAPTURE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                    } else {
                        m.TO= t_pos;
                        m.EFFECT = ENEMY_CAPTURE;
                        MOVES[depth][p][moveindex] = m;
                        moveindex++;
                        //printf("King ENEMY CAPTURE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                    }
                }else{
                    m.TO= t_pos;
                    m.EFFECT = NOTHING;
                    if(b->PEICES[p].GAS == 1) m.EFFECT = OUT_OF_GAS;
                    MOVES[depth][p][moveindex] = m;
                    moveindex++;
                    //printf("King MOVE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                }
            }
        }
    }
    /*
     00000000
     00000000
     00000000
     00011100
     0001K100
     00011100
     00000000
     00000000
     */
}

void generateBishopMoves(BOARD *b,int p,int depth){
    for (int i = 0; i<18; i++) {
        MOVES[depth][p][i].FROM = OFFBOARD;
        MOVES[depth][p][i].TO = OFFBOARD;
    }
    if ((b->PEICES[p].GAS>0 && b->PEICES[p].GAS < 4) && !b->PEICES[p].captured){
        MOVE m;int moveindex=0;
        m.FROM = b->PEICES[p].POS;
        bool side = SIDE(p);

        signed int BishopDirection[4]={11,9,-11,-9};
        for (int i = 0; i<4; i++) {
            int t_pos = b->PEICES[p].POS;
            t_pos = t_pos + BishopDirection[i];
            while (b->POS[t_pos]!=OFFBOARD) {
                if (b->POS[t_pos]!= EMPTY){
                    if (COLOR(b->POS[t_pos])==side) {
                        m.TO= t_pos;
                        m.EFFECT = FRIENDLY_CAPTURE;
                        MOVES[depth][p][moveindex] = m;
                        moveindex++;
                        //printf("Bishop FRIENDLY CAPTURE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                    } else {
                        m.TO= t_pos;
                        m.EFFECT = ENEMY_CAPTURE;
                        MOVES[depth][p][moveindex] = m;
                        moveindex++;
                        //printf("Bishop ENEMY CAPTURE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                    }
                    break;
                } else {
                    m.TO= t_pos;
                    m.EFFECT = NOTHING;
                    if(b->PEICES[p].GAS == 1) m.EFFECT = OUT_OF_GAS;
                    MOVES[depth][p][moveindex] = m;
                    moveindex++;
                    //printf("Bishop MOVE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                }
                t_pos = t_pos + BishopDirection[i];
            }
        }
    }
    /*
     0100000001
     0010000010
     0001000100
     0000101000
     00000B0000
     0000101000
     0001000100
     0010000010
     0100000001
     */
}

void generateQueenMoves(BOARD *b,int p,int depth){
    for (int i = 0; i<18; i++) {
        MOVES[depth][p][i].FROM = OFFBOARD;
        MOVES[depth][p][i].TO = OFFBOARD;
    }
    if ((b->PEICES[p].GAS>0 && b->PEICES[p].GAS < 4)&& !b->PEICES[p].captured){
        MOVE m;
        m.FROM=OFFBOARD;
        m.TO=OFFBOARD;
        m.EFFECT=0;
        int moveindex=0;
        m.FROM = b->PEICES[p].POS;
        bool side = SIDE(p);


        int KnightPsitions[8]={-21,-19,-12,-8,8,12,19,21};

        for (int i = 0; i<8; i++) {
            int t_pos = b->PEICES[p].POS;
            t_pos = t_pos + KnightPsitions[i];
            if (b->POS[t_pos]!=OFFBOARD){
                if (b->POS[t_pos]!= EMPTY){
                    if (COLOR(b->POS[t_pos])==side) {
                        m.TO= t_pos;
                        m.EFFECT = FRIENDLY_CAPTURE;
                        MOVES[depth][p][moveindex] = m;
                        moveindex++;
                        //printf("knight FRIENDLY CAPTURE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                    } else {
                        m.TO= t_pos;
                        m.EFFECT = ENEMY_CAPTURE;
                        MOVES[depth][p][moveindex] = m;
                        moveindex++;
                        //printf("knight ENEMY CAPTURE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                    }
                } else {
                    m.TO= t_pos;
                    m.EFFECT = NOTHING;
                    if(b->PEICES[p].GAS == 1) m.EFFECT = OUT_OF_GAS;
                    MOVES[depth][p][moveindex] = m;
                    moveindex++;
                    //printf("knight MOVE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                }
            }
        }
        int BishopDirection[4]={11,9,-11,-9};

        for (int j = 0; j<4; j++) {
            int tt_pos = 0;
            tt_pos = b->PEICES[p].POS;
            tt_pos = tt_pos + BishopDirection[j];
            while (b->POS[tt_pos]!=OFFBOARD) {
                if (b->POS[tt_pos]!= EMPTY){
                    if (COLOR(b->POS[tt_pos])==side) {
                        m.TO= tt_pos;
                        m.EFFECT = FRIENDLY_CAPTURE;
                        MOVES[depth][p][moveindex] = m;
                        moveindex++;
                        //printf("Bishop FRIENDLY CAPTURE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                    } else {
                        m.TO= tt_pos;
                        m.EFFECT = ENEMY_CAPTURE;
                        MOVES[depth][p][moveindex] = m;
                        moveindex++;
                        //printf("Bishop ENEMY CAPTURE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                    }
                    break;
                } else {
                    m.TO= tt_pos;
                    m.EFFECT = NOTHING;
                    if(b->PEICES[p].GAS == 1) m.EFFECT = OUT_OF_GAS;
                    MOVES[depth][p][moveindex] = m;
                    moveindex++;
                    //printf("Bishop MOVE TO %c%d \n",SQtoFILE(t_pos),SQtoRANK(t_pos));
                }
                tt_pos = tt_pos + BishopDirection[j];
            }
        }


    }
    /*
     0100000001
     0010000010
     0001101100
     0001101100
     00000Q0000
     0001101100
     0001101100
     0010000010
     0100000001

     01000001
     00110110
     00110110
     0000q000
     00110110
     00110110
     01000001
     */
}
void generateMoves(BOARD *b,int p,int depth){
    if (!b->PEICES[p].captured){
        switch (p){
            case BlackKnightLeft:   generateKnightMoves(b, p, depth);break;
            case BlackBishopLeft:   generateBishopMoves(b, p, depth);break;
            case BlackQueen:        generateQueenMoves(b, p, depth);break;
            case BlackKing:         generateKingMoves(b, p, depth);break;
            case BlackBishopRight:  generateBishopMoves(b, p, depth);break;
            case BlackKnightRight:  generateKnightMoves(b, p, depth);break;
            case WhiteKnightLeft:   generateKnightMoves(b, p, depth);break;
            case WhiteBishopLeft:   generateBishopMoves(b, p, depth);break;
            case WhiteQueen:        generateQueenMoves(b, p, depth);break;
            case WhiteKing:         generateKingMoves(b, p, depth);break;
            case WhiteBishopRight:  generateBishopMoves(b, p, depth);break;
            case WhiteKnightRight:  generateKnightMoves(b, p, depth);break;
            default:{printf("WRONG PIECE ERROR \n");break;}
        }
    }
}
void generateHumanMoves(BOARD *b,int depth){
    if (!b->PEICES[BlackKnightLeft].captured && b->PEICES[BlackKnightLeft].GAS >0)
        generateKnightMoves(b, BlackKnightLeft,depth);
    if (!b->PEICES[BlackBishopLeft].captured && b->PEICES[BlackBishopLeft].GAS >0)
        generateBishopMoves(b, BlackBishopLeft,depth);
    if (!b->PEICES[BlackQueen].captured && b->PEICES[BlackQueen].GAS >0)
        generateQueenMoves(b, BlackQueen,depth);
    if (!b->PEICES[BlackKing].captured && b->PEICES[BlackKing].GAS >0)
        generateKingMoves(b, BlackKing,depth);
    if (!b->PEICES[BlackBishopRight].captured && b->PEICES[BlackBishopRight].GAS >0)
        generateBishopMoves(b, BlackBishopRight,depth);
    if (!b->PEICES[BlackKnightRight].captured && b->PEICES[BlackKnightRight].GAS >0)
        generateKnightMoves(b, BlackKnightRight,depth);
    for (int i = 0; i < 99; i++) {
        SortedHumanMoveList[depth][i].FROM=0;
        SortedHumanMoveList[depth][i].TO=0;
        SortedHumanMoveList[depth][i].EFFECT=0;
    }
    int index = 0;
    ////    MOVE MOVES[30][13][18];// DEPTH PEICE MOVES
    ////    MOVE SortedComputerMoveList[30][50];
    ////    MOVE SortedHumanMoveList[30][50];
    //
    //    int j=0,i=0;MOVE m;
    //    for ( j = 7; j < 13; j++){
    //        for ( i = 0; i < 18; i++) {
    //            m = MOVES[depth][j][i];
    //            if (b->PEICES[b->POS[m.FROM]].GAS >0 && b->PEICES[b->POS[m.FROM]].GAS < 4){
    //                SortedHumanMoveList[depth][index] = m;
    //                index++;
    //            }
    //        }
    //    }

    for (int j = 7; j < 13; j++){
        for (int i = 0; i < 20; i++) {
            MOVE m = MOVES[depth][j][i];
            if ((m.TO != m.FROM)
                && b->PEICES[b->POS[m.FROM]].GAS >0
                && b->PEICES[b->POS[m.FROM]].GAS < 4
                && (m.EFFECT == ENEMY_CAPTURE)){
                SortedHumanMoveList[depth][index] = m;
                index++;
            }
        }
    }
    for (int j = 7; j < 13; j++){
        for (int i = 0; i < 20; i++) {
            MOVE m = MOVES[depth][j][i];
            if ((m.TO != m.FROM)
                && b->PEICES[b->POS[m.FROM]].GAS >0
                && b->PEICES[b->POS[m.FROM]].GAS < 4
                && ((m.EFFECT == NOTHING)||(m.EFFECT == UNKNOWN))){
                SortedHumanMoveList[depth][index] = m;
                index++;
            }
        }
    }

    for (int j = 7; j < 13; j++){
        for (int i = 0; i < 20; i++) {
            MOVE m = MOVES[depth][j][i];
            if ((m.TO != m.FROM)
                && b->PEICES[b->POS[m.FROM]].GAS >0
                && b->PEICES[b->POS[m.FROM]].GAS < 4
                && (m.EFFECT  == OUT_OF_GAS)){
                SortedHumanMoveList[depth][index] = m;
                index++;
            }
        }
    }
   // if(b->PEICES[BlackKing].GAS==1){
        for (int j = 7; j < 13; j++){
            for (int i = 0; i < 20; i++) {
                MOVE m = MOVES[depth][j][i];
                if ((m.TO != m.FROM)
                    && b->PEICES[b->POS[m.FROM]].GAS >0
                    && b->PEICES[b->POS[m.FROM]].GAS < 4
                    && (m.EFFECT  == FRIENDLY_CAPTURE)
                    && (m.TO != b->PEICES[BlackKing].POS)){
                    SortedHumanMoveList[depth][index] = m;
                    index++;
                }
            }
        }
    //}

}
void generateComputerMoves(BOARD *b,int depth){

    if (!b->PEICES[WhiteKnightLeft].captured && b->PEICES[WhiteKnightLeft].GAS >0)
        generateKnightMoves (b, WhiteKnightLeft,depth);
    if (!b->PEICES[WhiteBishopLeft].captured && b->PEICES[WhiteBishopLeft].GAS >0)
        generateBishopMoves (b, WhiteBishopLeft,depth);
    if (!b->PEICES[WhiteQueen].captured && b->PEICES[WhiteQueen].GAS >0)
        generateQueenMoves  (b, WhiteQueen,depth);
    if (!b->PEICES[WhiteKing].captured && b->PEICES[WhiteKing].GAS >0)
        generateKingMoves   (b, WhiteKing,depth);
    if (!b->PEICES[WhiteBishopRight].captured && b->PEICES[WhiteBishopRight].GAS >0)
        generateBishopMoves (b, WhiteBishopRight,depth);
    if (!b->PEICES[WhiteKnightRight].captured && b->PEICES[WhiteKnightRight].GAS >0)
        generateKnightMoves (b, WhiteKnightRight,depth);
    for (int i = 0; i < 99; i++) {
        SortedComputerMoveList[depth][i].FROM=0;
        SortedComputerMoveList[depth][i].TO=0;
        SortedComputerMoveList[depth][i].EFFECT=0;
    }
    int index = 0;

    ////    MOVE MOVES[30][13][18];// DEPTH PEICE MOVES
    ////    MOVE SortedComputerMoveList[30][50];
    ////    MOVE SortedHumanMoveList[30][50];
    //
    //    int j=0,i=0;MOVE m;
    //    for ( j = 1; j < 7; j++){
    //        for ( i = 0; i < 18; i++) {
    //            m = MOVES[depth][j][i];
    //            if (b->PEICES[b->POS[m.FROM]].GAS >0 && b->PEICES[b->POS[m.FROM]].GAS < 4){
    //                SortedComputerMoveList[depth][index] = m;
    //                index++;
    //            }
    //        }
    //    }

    for (int j = 1; j < 7; j++){
        for (int i = 0; i < 20; i++) {
            MOVE m = MOVES[depth][j][i];
            if ((m.TO != m.FROM)
                && (m.EFFECT == ENEMY_CAPTURE)
                && b->PEICES[b->POS[m.FROM]].GAS >0
                && b->PEICES[b->POS[m.FROM]].GAS < 4){
                SortedComputerMoveList[depth][index] = m;
                index++;
            }
        }
    }
    for (int j = 1; j < 7; j++){
        for (int i = 0; i < 20; i++) {
            MOVE m = MOVES[depth][j][i];
            if ((m.TO != m.FROM)
                && b->PEICES[b->POS[m.FROM]].GAS >0
                && b->PEICES[b->POS[m.FROM]].GAS < 4
                && ((m.EFFECT == NOTHING)||(m.EFFECT == UNKNOWN))){
                SortedComputerMoveList[depth][index] = m;
                index++;
            }
        }
    }

    for (int j = 1; j < 7; j++){
        for (int i = 0; i < 20; i++) {
            MOVE m = MOVES[depth][j][i];
            if ((m.TO != m.FROM)
                && b->PEICES[b->POS[m.FROM]].GAS >0
                && b->PEICES[b->POS[m.FROM]].GAS < 4
                && (m.EFFECT  == OUT_OF_GAS)){
                SortedComputerMoveList[depth][index] = m;
                index++;
            }
        }
    }
   // if(b->PEICES[WhiteKing].GAS==1){
        for (int j = 1; j < 7; j++){
            for (int i = 0; i < 20; i++) {
                MOVE m = MOVES[depth][j][i];
                if ((m.TO != m.FROM)
                    && b->PEICES[b->POS[m.FROM]].GAS >0
                    && b->PEICES[b->POS[m.FROM]].GAS < 4
                    && (m.EFFECT  == FRIENDLY_CAPTURE)
                    && (m.TO != b->PEICES[WhiteKing].POS)){
                    SortedComputerMoveList[depth][index] = m;
                    index++;
                }
            }
        }
   // }

}

void saveBoardState(BOARD *b,BOARD *savedboardstate){
    for (int i = 0;i<BOARDSIZE;i++){
        savedboardstate->POS[i] = b->POS[i];
    }
    for (int i = 1;i<13;i++){
        savedboardstate->PEICES[i].POS      = b->PEICES[i].POS;
        savedboardstate->PEICES[i].GAS      = b->PEICES[i].GAS;
        savedboardstate->PEICES[i].captured = b->PEICES[i].captured;
    }
}
void restoreBoardState(BOARD *savedboardstate,BOARD *b){
    for (int i = 0;i<BOARDSIZE;i++){
        b->POS[i] = savedboardstate->POS[i]  ;
    }
    for (int i = 1;i<13;i++){
        b->PEICES[i].POS        = savedboardstate->PEICES[i].POS  ;
        b->PEICES[i].GAS        = savedboardstate->PEICES[i].GAS  ;
        b->PEICES[i].captured   = savedboardstate->PEICES[i].captured  ;
    }
}
void doMove(BOARD *b,MOVE m){
    if (b->PEICES[b->POS[m.FROM]].GAS !=0
        && b->POS[m.FROM] != OFFBOARD
        && b->POS[m.TO] != OFFBOARD){

        if (b->POS[m.TO]!=EMPTY) {
            b->PEICES[b->POS[m.TO]].captured=true;
            b->PEICES[b->POS[m.FROM]].GAS = 3;
        } else {
            b->PEICES[b->POS[m.FROM]].GAS -= 1;
        }

        b->PEICES[b->POS[m.FROM]].POS = m.TO;
        b->POS[m.TO] = b->POS[m.FROM];
        b->POS[m.FROM] = EMPTY;


    }else printf("ERROR in DO MOVE ");
}

bool IsLegal(BOARD *b,MOVE *m){
    bool legal = false;
    if(b->PEICES[b->POS[m->FROM]].GAS > 0){
        int piece = b->POS[m->FROM];
        generateMoves(b, piece, 0);
        for (int i=0;i<20;i++){
            if (MOVES[0][piece][i].TO == m->TO){
                legal = true;
                break;
            }
        }
        for(int i = 0 ; i<20;i++){
            MOVES[0][piece][i].FROM = OFFBOARD;
            MOVES[0][piece][i].TO = OFFBOARD;
        }
    }
    return legal;
}
void printMove(MOVE m){
    //enum {NOTHING,FRIENDLY_CAPTURE,ENEMY_CAPTURE,OUT_OF_GAS};
    char fromfile = SQtoFILE(m.FROM);
    int fromrank = SQtoRANK(m.FROM);
    char tofile = SQtoFILE(m.TO);
    int torank = SQtoRANK(m.TO);
    printf("MOVE from %c%d to %c%d",fromfile,fromrank,tofile,torank);
    if          (m.EFFECT == FRIENDLY_CAPTURE) printf(" with EFFECT: FRIENDLY CAPTURE \n");
    else  if    (m.EFFECT == ENEMY_CAPTURE) printf(" with EFFECT: ENEMY CAPTURE \n");
    else  if    (m.EFFECT == OUT_OF_GAS) printf(" with EFFECT: OUT OF GAS \n");
    else  if    (m.EFFECT == NOTHING) printf(" with EFFECT: NOTHING \n");
    else  printf("\n");
}
void printComputerMove(MOVE m){
    char fromfile = SQtoFILE(m.FROM);
    int fromrank = SQtoRANK(m.FROM);
    char tofile = SQtoFILE(m.TO);
    int torank = SQtoRANK(m.TO);
    char cfromfile = SQtoFILECOMPUTER(m.FROM);
    int cfromrank = SQtoRANKCOMPUTER(m.FROM);
    char ctofile = SQtoFILECOMPUTER(m.TO);
    int ctorank = SQtoRANKCOMPUTER(m.TO);
    printf("MOVE from %c%d to %c%d [from %c%d to %c%d]",fromfile,fromrank,tofile,torank,cfromfile,cfromrank,ctofile,ctorank);
    if          (m.EFFECT == FRIENDLY_CAPTURE) printf(" with EFFECT: FRIENDLY CAPTURE \n");
    else  if    (m.EFFECT == ENEMY_CAPTURE) printf(" with EFFECT: ENEMY CAPTURE \n");
    else  if    (m.EFFECT == OUT_OF_GAS) printf(" with EFFECT: OUT OF GAS \n");
    else  if    (m.EFFECT == NOTHING) printf(" with EFFECT: NOTHING \n");
    else  printf("\n");
}
void printMoveCompact(MOVE m){
    char fromfile = SQtoFILE(m.FROM);
    int fromrank = SQtoRANK(m.FROM);
    char tofile = SQtoFILE(m.TO);
    int torank = SQtoRANK(m.TO);
    printf("[%c%d to %c%d] ",fromfile,fromrank,tofile,torank);
}
void evaluateMove(BOARD *b,MOVE *m){
    int piece = b->POS[m->FROM];
    bool side = SIDE(piece);

    if (b->POS[m->TO] != EMPTY) {
        int capturedpiece = b->POS[m->TO];
        if (SIDE(capturedpiece) == side) {
            m->EFFECT = FRIENDLY_CAPTURE;
        }
        else if (SIDE(capturedpiece) != side){
            m->EFFECT = ENEMY_CAPTURE;
        }
    } else {
        if (b->PEICES[piece].GAS <= 1)m->EFFECT= OUT_OF_GAS;
        else m->EFFECT = NOTHING;
    }
}
void getamove(BOARD *b) {
    bool legal = false;
    char x1,x2;
    int y1,y2;
    int xx1 = 0;
    int xx2 = 0;
    int yy1 = 0;
    int yy2 = 0;
    while (!legal) {
        cin.clear();
        cout << "Enter your move:  ";
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 =='q') {printf("\n***********QUIT REQUESTED***********\n***********EXITING PROGRAM***********\n");exit(-1);}

        if (x1 == 'a' || x1 == 'A') xx1 = FILE_A;
        if (x1 == 'b' || x1 == 'B') xx1 = FILE_B;
        if (x1 == 'c' || x1 == 'C') xx1 = FILE_C;
        if (x1 == 'd' || x1 == 'D') xx1 = FILE_D;
        if (x1 == 'e' || x1 == 'E') xx1 = FILE_E;
        if (x1 == 'f' || x1 == 'F') xx1 = FILE_F;
        if (x1 == 'g' || x1 == 'G') xx1 = FILE_G;
        if (x1 == 'h' || x1 == 'H') xx1 = FILE_H;

        if (x2 == 'a' || x2 == 'A') xx2 = FILE_A;
        if (x2 == 'b' || x2 == 'B') xx2 = FILE_B;
        if (x2 == 'c' || x2 == 'C') xx2 = FILE_C;
        if (x2 == 'd' || x2 == 'D') xx2 = FILE_D;
        if (x2 == 'e' || x2 == 'E') xx2 = FILE_E;
        if (x2 == 'f' || x2 == 'F') xx2 = FILE_F;
        if (x2 == 'g' || x2 == 'G') xx2 = FILE_G;
        if (x2 == 'h' || x2 == 'H') xx2 = FILE_H;
        yy1 = 9- y1 ;
        yy2 = 9- y2 ;
        int from = xx1+yy1*10+1;
        int to = xx2+yy2*10+1;
        // cout << from << " "<<to;
        MOVE m;
        m.FROM = from;
        m.TO = to;
        m.EFFECT= NOTHING;
        //if (!isalpha(x1) || !isdigit(y1) || !isalpha(x2) || !isdigit(y2)){
        //  printf("\nILLIGAL INPUT!!! %c%d to %c%d\n",x1,y1,x2,y2);
        //}
        //else
        if (IsLegal(b,&m)) {
            legal= true;
            evaluateMove(b, &m);
            doMove(b,m);
            printf("HUMAN: ");
            printMove(m);
            //printf("\nMOVED from %c%d to %c%d\n",x1,y1,x2,y2);
        } else printf("\nILLIGAL MOVE!!! %c%d to %c%d\n",x1,y1,x2,y2);
    }
}

int inCheck(BOARD *b){
    int incheck = 0;
    generateComputerMoves(b, 0);
    generateHumanMoves(b, 0);
    for (int i = 0; i<99 ;i++){
        if (b->POS[SortedComputerMoveList[0][i].TO] == BlackKing) incheck += 55;
        if (b->POS[SortedHumanMoveList[0][i].TO] == WhiteKing) incheck += -55;
    }
    return incheck;
}
int EvaluateBoard(BOARD *b){
    int score =0;

    for (int i =1;i<13;i++) {
        if(!b->PEICES[i].captured
           && b->PEICES[i].GAS>0
           && b->PEICES[i].GAS < 4) {
            score+=(pieceValue[i]-b->PEICES[i].GAS);
        }
    }

    bitboard WhiteBishopLeftPOS = 1 << board2bitboard[b->PEICES[WhiteBishopLeft].POS];
    bitboard WhiteBishopRightPOS = 1 << board2bitboard[b->PEICES[WhiteBishopRight].POS];
    bitboard WhiteKnightLeftPOS = 1 << board2bitboard[b->PEICES[WhiteKnightLeft].POS];
    bitboard WhiteKnightRightPOS = 1 << board2bitboard[b->PEICES[WhiteKnightRight].POS];
    bitboard WhiteQueenPOS = 1 << board2bitboard[b->PEICES[WhiteQueen].POS];

    bitboard BlackBishopLeftPOS = 1 << board2bitboard[b->PEICES[BlackBishopLeft].POS];
    bitboard BlackBishopRightPOS = 1 << board2bitboard[b->PEICES[BlackBishopRight].POS];
    bitboard BlackKnightLeftPOS = 1 << board2bitboard[b->PEICES[BlackKnightLeft].POS];
    bitboard BlackKnightRightPOS = 1 << board2bitboard[b->PEICES[BlackKnightRight].POS];
    bitboard BlackQueenPOS = 1 << board2bitboard[b->PEICES[BlackQueen].POS];

    if ((WhiteKnightLeftPOS & whiteknightmask) == 1) score += 50;
    if ((WhiteKnightRightPOS & whiteknightmask) == 1) score += 50;
    if ((WhiteBishopLeftPOS & whitebishopmask) == 1) score += 50;
    if ((WhiteBishopRightPOS & whitebishopmask) == 1) score += 50;
    if ((WhiteQueenPOS & whitequeenmask) == 1) score += 50;

    if ((BlackKnightLeftPOS & blacknightmask) == 1) score -= 50;
    if ((BlackKnightRightPOS & blacknightmask) == 1) score -= 50;
    if ((BlackBishopLeftPOS & blackbishopmask) == 1) score -= 50;
    if ((BlackBishopRightPOS & blackbishopmask) == 1) score -= 50;
    if ((BlackQueenPOS & blackqueenmask) == 1) score -= 50;


    evaluationcounter++;
    //score += inCheck(b);
    //printf(" %d ",score);
    return score;
}
int IsGameOver(BOARD *b){
    int score= 0;bool whitelost = true,blacklost = true;


    for (int i = 1; i <7 ;i++) if (!b->PEICES[i].captured && b->PEICES[i].GAS >0) whitelost = false;
    for (int i = 7; i <13 ;i++) if (!b->PEICES[i].captured && b->PEICES[i].GAS >0) blacklost = false;

    if (b->PEICES[WhiteKing].captured || whitelost) score = -99999;
    if (b->PEICES[BlackKing].captured || blacklost) score = 99999;

    return score;
}
int quiesce(BOARD *b,int depth,int alpha, int beta) {
    int score;
    score = EvaluateBoard(b);
    if (score >= beta || t.GetTicks() >MAXTIME) return score;
    for (int i =0;i<99;i++){
        MOVE q_m;
        q_m.FROM = SortedComputerMoveList[depth][i].FROM;
        q_m.TO = SortedComputerMoveList[depth][i].TO;
        q_m.EFFECT = SortedComputerMoveList[depth][i].EFFECT;
        if ((b->PEICES[b->POS[q_m.FROM]].GAS > 0 && b->PEICES[b->POS[q_m.FROM]].GAS < 4 )&& q_m.EFFECT == ENEMY_CAPTURE ){
            BOARD savedstate;
            saveBoardState(b,&savedstate);
            doMove(b,q_m);
            score = -(quiesce(b,depth,-beta,-alpha));
            restoreBoardState(&savedstate,b);
        }
        if (score >= alpha) {
            alpha = score;
            if (score >= beta) break;
        }
    }
    return score;
}

int Max(BOARD *b,int depth,int alpha,int beta){
    if (IsGameOver(b) < 0) return (-99999) - (99 - depth);
    if (depth > MAXDEPTH || t.GetTicks() >MAXTIME) return EvaluateBoard(b);
    int t_score;
    generateComputerMoves(b, depth);
    for (int i =0;i<99;i++){
        MOVE t_m;
        t_m.FROM = SortedComputerMoveList[depth][i].FROM;
        t_m.TO = SortedComputerMoveList[depth][i].TO;
        t_m.EFFECT = SortedComputerMoveList[depth][i].EFFECT;
        if (b->PEICES[b->POS[t_m.FROM]].GAS > 0 && b->PEICES[b->POS[t_m.FROM]].GAS < 4) {
            BOARD savedstate;
            saveBoardState(b,&savedstate);
            doMove(b,t_m);
            t_score = Min(b,depth+1,alpha, beta);
            restoreBoardState(&savedstate,b);
            if( t_score >= beta ) return beta;   // fail hard beta-cutoff
            else
                if( t_score > alpha ) alpha = t_score;
            //if (t_score > best.score)best.score = t_score;
        }
    }
    return alpha;
}
int Min(BOARD *b,int depth,int alpha,int beta){
    if (IsGameOver(b) > 0 ) return 99999 + (99 - depth);
    if(depth > MAXDEPTH || t.GetTicks() >MAXTIME ) return /*EvaluateBoard(b);*/quiesce(b,depth,alpha,beta);
    int t_score;
    generateHumanMoves(b, depth);
    for (int i =0;i<99;i++){
        MOVE t_m;
        t_m.FROM = SortedHumanMoveList[depth][i].FROM;
        t_m.TO = SortedHumanMoveList[depth][i].TO;
        t_m.EFFECT = SortedHumanMoveList[depth][i].EFFECT;
        if (b->PEICES[b->POS[t_m.FROM]].GAS > 0 && b->PEICES[b->POS[t_m.FROM]].GAS < 4) {
            BOARD savedstate;
            saveBoardState(b,&savedstate);
            doMove(b,t_m);
            t_score = Max(b,depth+1,alpha, beta);
            restoreBoardState(&savedstate,b);
            if( t_score <= alpha )return alpha; // fail hard alpha-cutoff
            else
                if( t_score < beta )beta = t_score;
            //if (t_score < best.score) best.score = t_score;
        }
    }
    return beta;
}
BEST MiniMax(BOARD *b){
    t.Start();
    resetMOVES();
    int depth = 1,alpha=-999999,beta=999999;
    BEST best;best.score=-999999;best.move.FROM=OFFBOARD;best.move.TO=OFFBOARD;best.move.EFFECT = UNKNOWN;
    BEST highest; highest.score = -999999; highest.move.FROM=OFFBOARD;highest.move.TO=OFFBOARD;highest.move.EFFECT=UNKNOWN;
    int t_score;
    MAXDEPTH = 5;
    while (MAXDEPTH <99) {
        best.score=-999999; alpha=-999999,beta=999999;
        best.move.FROM = OFFBOARD;
        best.move.TO = OFFBOARD;
        best.move.EFFECT = UNKNOWN;

        generateComputerMoves(b, depth);
        for (int i =0;i<99;i++){
            MOVE t_m;
            t_m.FROM = SortedComputerMoveList[depth][i].FROM;
            t_m.TO = SortedComputerMoveList[depth][i].TO;
            t_m.EFFECT = SortedComputerMoveList[depth][i].EFFECT;
            if (b->PEICES[b->POS[t_m.FROM]].GAS > 0
                && b->PEICES[b->POS[t_m.FROM]].GAS < 4 ) {
                BOARD savedstate;
                saveBoardState(b,&savedstate);
                doMove(b,t_m);
                t_score = Min(b,depth+1,alpha,beta);
                restoreBoardState(&savedstate,b);
                if (t_score > best.score ) {
                    best.score = t_score;
                    best.move.FROM = t_m.FROM;
                    best.move.TO = t_m.TO;
                    best.move.EFFECT = t_m.EFFECT;
                }
            }
        }
        MAXDEPTH += 1;
        printf("\nDEPTH %d SCORE %d in %lu m/sec with %d evaluations\n",MAXDEPTH,best.score,t.GetTicks()/1000,evaluationcounter);
        printf("Possible: ");
        printComputerMove(best.move);
        if (t.GetTicks() < MAXTIME ) {
            highest.score = best.score;
            highest.move.FROM = best.move.FROM;
            highest.move.TO = best.move.TO;
            highest.move.EFFECT = best.move.EFFECT;
            best.score=-999999; alpha=-999999,beta=999999;
            best.move.FROM = OFFBOARD;
            best.move.TO = OFFBOARD;
            best.move.EFFECT = UNKNOWN;
        }
        if (t.GetTicks() > MAXTIME || IsGameOver(b)!=0  ) break;
    }
    //printf("\nDEPTH %d SCORE %d in %lu m/sec with %d evaluations\n",MAXDEPTH,highest.score,t.GetTicks()/1000,evaluationcounter);
    evaluationcounter=0;
    t.Reset();
    return highest;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";



    BOARD board;
    setup(&board);
    resetMOVES();

    MAXTIME = 5  * 1000000;
    MAXDEPTH =1;
    evaluationcounter=0;
    colorDisplay = false;


    printf("Do you want to see the board in color? y/n : ");
    char cyn;
    cin >> cyn;
    if (cyn == 'y') colorDisplay = true;
    printf("\n\n\n            SHAH the GasTank Chess           \n\n");
    bool gameover = false;


    Display(&board);
    //printBoard(&board);
    printf("Do you want to go first? y/n : ");
    char yn;
    cin >> yn;
    printf("\n");
    BEST best;
    if (yn == 'n') {best = MiniMax(&board);
        doMove(&board, best.move) ;
        printf("===============================================================================\n");
        printf("COMPUTER: ");
        printComputerMove(best.move);
        printf("===============================================================================\n");
    }
    while (!gameover) {
        Display(&board);
        //printBoard(&board);
        /*
         generateHumanMoves(&board, 0);
         for (int i = 0 ; i<99; i++) {
         MOVE m =SortedHumanMoveList[0][i];
         if (m.TO != m.FROM) printMoveCompact(m);
         }
         */
        printf("\n");
        getamove(&board);
        //BEST testbest; testbest = MiniMax(&board);doMove(&board, &testbest.move);
        Display(&board);
        //printBoard(&board);

        if (IsGameOver(&board) == 0) {
            best = MiniMax(&board);
            doMove(&board, best.move) ;
            printf("===============================================================================\n");
            printf("COMPUTER: ");
            printComputerMove(best.move);
            printf("===============================================================================\n");

        }
        if(IsGameOver(&board) < 0) {
            printf("\n\n HUMAN WINS \n\n");
            Display(&board);
            gameover=true;
            char q;
            printf("\n\n Q to exit \n\n");
            cin >> q;
        }
        else if(IsGameOver(&board) > 0) {
            printf("\n\n COMPUTER WINS \n\n");
            Display(&board);
            gameover=true;
            char q;
            printf("\n\n Q to exit \n\n");
            cin >> q;
        }


    }



    //    BOARD board;
    //    setup(&board);
    //
    //    Display(&board);
    //
    //    generateComputerMoves(&board, 0);
    //    for (int i =0;i<99;i++){
    //        MOVE t_m;
    //        t_m.FROM = SortedComputerMoveList[0][i].FROM;
    //        t_m.TO = SortedComputerMoveList[0][i].TO;
    //        t_m.EFFECT = SortedComputerMoveList[0][i].EFFECT;
    //        printf("GAS: %d ",board.PEICES[board.POS[t_m.FROM]].GAS);
    //        printMove(t_m);
    //
    //    }


    //    generateBishopMoves(&board,BlackBishopLeft,0);
    //    for (int i = 0 ; i <18; i ++){
    //        MOVE m= MOVES[0][BlackBishopLeft][i];
    //        printMove(m);
    //
    //    }

    //            MOVE m ;
    //            m.FROM= 84; m.TO = 51;
    //            saveBoardState(&board);
    //            doMove(&board, m);
    //            printf("gas: %d\n", board.PEICES[BlackQueen].GAS);
    //            //restoreBoardState(&board);
    //            //printf("gas: %d\n", board.PEICES[BlackQueen].GAS);
    //
    //            //Display(&board);
    //            m.FROM= 51; m.TO = 84;
    //            //saveBoardState(&board);
    //            doMove(&board, m);
    //            printf("gas: %d\n", board.PEICES[BlackQueen].GAS);
    //            //restoreBoardState(&board);
    //
    //            m.FROM= 84; m.TO = 51;
    //            //saveBoardState(&board);
    //            doMove(&board, m);
    //            printf("gas: %d\n", board.PEICES[BlackQueen].GAS);
    //            //restoreBoardState(&board);
    //            //printf("gas: %d\n", board.PEICES[BlackQueen].GAS);
    //
    //
    //            m.FROM= 51; m.TO = 84;
    //            //saveBoardState(&board);
    //            doMove(&board, m);
    //            printf("gas: %d\n", board.PEICES[BlackQueen].GAS);
    //            restoreBoardState(&board);
    //            printf("gas: %d\n", board.PEICES[BlackQueen].GAS);




    /*


     int counter = 0;
     timer t;
     t.Start();
     for (int i = 0;i<1000000000;i++){
     //generateBishopMoves(&board,WhiteBishopLeft,0);
     //generateKnightMoves(&board,WhiteKnightLeft,0);
     generateKingMoves(&board,WhiteKing,0);
     counter++;
     if (t.GetTicks() > 5999999) break;
     }
     printf("\nDONE counter %d\n", counter);




     std::stack<int> POSs = parseBitBoard(b);
     while (!POSs.empty()) {
     printf("%d ",POSs.top());
     //printf("\n");
     POSs.pop();
     }



     showState(&board);
     printBitBoard(boardToBitBoard(&board));
     MOVE m;
     m.from = 3;
     m.to = 11;
     doMove(&board, m);
     showState(&board);
     printBitBoard(boardToBitBoard(&board));
     undoMove(&board, m);
     showState(&board);
     printBitBoard(boardToBitBoard(&board));


     stack<MOVE> moves;
     generateKnightMoves(&board, &board.PIECES[3], &moves);
     m.from = E1;
     m.to = 9;
     doMove(&board, m);
     
     
     int counter = 0;
     timer t;
     t.Start();
     for (int i = 0;i<1000000000;i++){
     generateKingMoves(&board,WhiteKing,0);
     counter++;
     if (t.GetTicks() > 5999999) break;
     }
     printf("\nDONE counter %d\n", counter);
     */
    /*
     00000000
     00000000
     00000000
     00000000
     00000000
     00000111
     00000101
     00000111
     */
    
    return 0;
}







