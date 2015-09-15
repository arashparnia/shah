//
//  Data.h
//  csc180game
//
//  Created by arash parnia on 3/18/15.
//  Copyright (c) 2015 arash. All rights reserved.
//

#ifndef gt_h
#define gt_h


#endif



/*
 # define A8  56 # define B8  57 # define C8  58 # define D8  59 # define E8  60 # define F8  61 # define G8 62 # define H8  63
 # define A7  48 # define B7  49 # define C7  50 # define D7  51 # define E7  52 # define F7  53 # define G7  54 # define H7  55
 # define A6  40 # define B6  41 # define C6  42 # define D6  43 # define E6  44 # define F6  45 # define G6  46 # define H6  47
 # define A5  32 # define B5  33 # define C5  34 # define D5  35 # define E5  36 # define F5  37 # define G5  38 # define H5  39
 # define A4  24 # define B4  25 # define C4  26 # define D4  27 # define E4  28 # define F4  29 # define G4  30 # define H4  31
 # define A3  16 # define B3  17 # define C3  18 # define D3  19 # define E3  20 # define F3  21 # define G3  22 # define H3  23
 # define A2  8  # define B2  9  # define C2  10 # define D2  11 # define E2  12 # define F2  13 # define G2  14 # define H2  15
 # define A1  0  # define B1  1  # define C1  2  # define D1  3  # define E1  4  # define F1  5  # define G1  6  # define H1  7

 //=======================BOARD ARRAY REPRESENTATION=====================
 typedef long long int BITBOARD; //BITBOARD DATA STRUCTURE
 #define FR2SQ(f,r) (( 21+ (f))+((r)*10)) //file and rank convertor


 */

#define BOARDSIZE 110


#define START_FEN "1nbqkbn1/8/8/8/8/8/1NBQKBN1 w KQkq - 0 1"

/*
 0000 0000 0000 0111 1111 -> From 0x7F
 0000 0011 1111 1000 0000 -> To >> 7, 0x7F
 0011 1100 0000 0000 0000 -> Captured >> 14, 0xF

 #define FROM(m) ((m) & 0x7F)
 #define TO(m) (((m)>>7) & 0x7F)
 #define CAPTURED(m) (((m)>>14) & 0xF)
 */


#define FR2SQ(f,r) (( 21+ (f))+((r)*10)) //file and rank convertor


enum { FILE_A , FILE_B , FILE_C , FILE_D , FILE_E , FILE_F , FILE_G , FILE_H , FILE_NONE };
enum { RANK_1 , RANK_2, RANK_3 , RANK_4 , RANK_5 , RANK_6 , RANK_7 , RANK_NONE};
enum { WHITE, BLACK, BOTH};
enum { COMPUTER, HUMAN};

enum {EMPTY,WhiteKnightLeft,WhiteBishopLeft,WhiteQueen,WhiteKing,WhiteBishopRight,WhiteKnightRight,
    BlackKnightLeft,BlackBishopLeft,BlackQueen,BlackKing,BlackBishopRight,BlackKnightRight,};
int pieceValue[13]= {0,300,300,900,5000,300,300,-300,-300,-900,-5000,-300,-300};
bool COLOR[] =  {   WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK, };
bool SIDE[] =   {   COMPUTER,COMPUTER,COMPUTER,COMPUTER,COMPUTER,COMPUTER,COMPUTER,HUMAN,HUMAN,HUMAN,HUMAN,HUMAN,HUMAN};
#define COLOR(c) (COLOR[c])
#define SIDE(s) (SIDE[s])

enum {
    A1 = 21, B1 , C1 , D1 , E1 , F1 , G1 , H1 ,
    A2 = 31, B2 , C2 , D2 , E2 , F2 , G2 , H2 ,
    A3 = 41, B3 , C3 , D3 , E3 , F3 , G3 , H3 ,
    A4 = 51, B4 , C4 , D4 , E4 , F4 , G4 , H4 ,
    A5 = 61, B5 , C5 , D5 , E5 , F5 , G5 , H5 ,
    A6 = 71, B6 , C6 , D6 , E6 , F6 , G6 , H6 ,
    A7 = 81, B7 , C7 , D7 , E7 , F7 , G7 , H7, OFFBOARD=99
};
enum {FALSE, TRUE};
enum {UNKNOWN,NOTHING,FRIENDLY_CAPTURE,ENEMY_CAPTURE,OUT_OF_GAS};

char piece2Char[] = ".NBQKBNnbqkbn";
char gas2Char[]="0123";
char SQtoFILE[]         =".....................ABCDEFGH..ABCDEFGH..ABCDEFGH..ABCDEFGH..ABCDEFGH..ABCDEFGH..ABCDEFGH..";
char SQtoFILECOMPUTER[] =".....................ABCDEFGH..ABCDEFGH..ABCDEFGH..ABCDEFGH..ABCDEFGH..ABCDEFGH..ABCDEFGH..";
#define SQtoRANK(sq) (9-(sq/10))
#define SQtoRANKCOMPUTER(sq) ((sq/10)-1)
#define SQtoFILE(sq) SQtoFILE[sq]
#define SQtoFILECOMPUTER(sq) SQtoFILECOMPUTER[sq]

typedef struct{
    int POS ;
    int TYPE ;
    int GAS ;
    bool captured;
}PIECE;

typedef struct{
    int FROM ;
    int TO ;
    int EFFECT ;
    PIECE CAPTURED;
    int GASHISTORY;
}MOVE;

typedef struct {
    int POS[BOARDSIZE];
    PIECE PEICES[13];
    //MOVE HISTORY[150];
}BOARD;

typedef struct {
    int score;
    MOVE move;
}BEST;

MOVE MOVES[10][13][18];// DEPTH PEICE MOVES
MOVE SortedComputerMoveList[10][150];
MOVE SortedHumanMoveList[10][150];

#define RESET           0
#define BRIGHT          1
#define DIM             2
#define UNDERLINE       3
#define BLINK           4
#define REVERSE         7
#define HIDDEN          8
#define BLACK           0
#define RED             1
#define GREEN           2
#define YELLOW          3
#define BLUE            4
#define MAGENTA         5
#define CYAN            6
#define WHITE           7




void resetMOVES();
void setup(BOARD *b);
void printBoard(BOARD *b);
void generateKnightMoves(BOARD *b,int p,int depth);
void generateKingMoves(BOARD *b,int p,int depth);
void generateBishopMoves(BOARD *b,int p,int depth);
void generateQueenMoves(BOARD *b,int p,int depth);
void generateMoves(BOARD *b,int p,int depth);
void generateHumanMoves(BOARD *b,int depth);
void generateComputerMoves(BOARD *b,int depth);
void doMove(BOARD *b,MOVE *m);
void undoMove(BOARD *b,MOVE *m);
bool IsLegal(BOARD *b,MOVE m);
void printMove(MOVE m);
void printComputerMove(MOVE m);
void printMoveCompact(MOVE m);
void evaluateMove(BOARD *b,MOVE *m);
void getamove(BOARD *b) ;
int EvaluateBoard(BOARD *b);
int IsGameOver(BOARD *b);
int Max(BOARD *b,int depth,int alpha,int beta);
int Min(BOARD *b,int depth,int alpha,int beta);
BEST MiniMax(BOARD *b);
void textcolor(int attr, int fg, int bg);
int main();







