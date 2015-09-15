//
//  main.cpp
//  csc180game
//
//  Created by arash parnia on 3/11/15.
//  Copyright (c) 2015 arash. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <stdio.h>      /* printf */
#include <math.h>
#include "Timer.h"

using namespace std;
#define BOARDSIZE 110

enum { EMPTY , wN , wB , wQ , wK , bN , bB , bQ , bK };
enum { FILE_A , FILE_B , FILE_C , FILE_D , FILE_E , FILE_F , FILE_G , FILE_H , FILE_NONE };
enum { RANK_1 , RANK_2, RANK_3 , RANK_4 , RANK_5 , RANK_6 , RANK_7 , RANK_NONE};
enum { WHITE, BLACK, BOTH};
enum {
    A1 = 21, B1 , C1 , D1 , E1 , F1 , G1 , H1 ,
    A2 = 31, B2 , C2 , D2 , E2 , F2 , G2 , H2 ,
    A3 = 41, B3 , C3 , D3 , E3 , F3 , G3 , H3 ,
    A4 = 51, B4 , C4 , D4 , E4 , F4 , G4 , H4 ,
    A5 = 61, B5 , C5 , D5 , E5 , F5 , G5 , H5 ,
    A6 = 71, B6 , C6 , D6 , E6 , F6 , G6 , H6 ,
    A7 = 81, B7 , C7 , D7 , E7 , F7 , G7 , H7 , NO_SQ , OFFBOARD
};
enum {FALSE, TRUE};




typedef long long int bitboard; //BITBOARD DATA STRUCTURE
// BOARD STRUCTURE ---------------------------------------
typedef struct{
    int pieces[BOARDSIZE];
    int knights[2];
    int bishops[2];
    int queen[2];
    int king[2];
    int gas;
    int side;
    int pceNum[9];
    
    int bigPce[2];
    int majPce[2];
    int minPce[2];
    int material[2];
    //piecelist
    int plist[9][2]; // example: pList[wN][0] = E1;
} S_BOARD;
#define START_FEN "1nbqkbn1/8/8/8/8/8/1NBQKBN1 w KQkq - 0 1"
//MOVE STRUCTURE ------------------------------------
//                             7    F
// 0000 0000 0000 0000 0000 0111 1111 -> from 0x7F
// 0000 0000 0000 0011 1111 1000 0000 -> to >> 7 ,0x7F
// 0000 0000 0011 1100 0000 0000 0000 -> capture >> 14 , 0xF
// 0000 0000 0100 0000 0000 0000 0000 -> useless
// 0000 0000 1000 0000 0000 0000 0000 -> useless
// 0000 1111 0000 0000 0000 0000 0000 -> useless
// 0001 0000 0000 0000 0000 0000 0000 -> useless

#define FROM(m) ((m) & 0x7F)
#define TO(m) (((m)>>7) & 0x7F)
#define CAPTURED(m) (((m)>>14) & 0xF)
typedef struct{
    int move;
    int score;
} S_MOVE;

//----------------------------------------------------------
#define FR2SQ(f,r) (( 21+ (f))+((r)*10)) //file and rank convertor
int sq110tosq64[BOARDSIZE]; //tale of 110 board
#define SQ110(sq64) (sq64tosq110[(sq64)])
int sq64tosq110[64]; //coresponding numbers in 64 boad
#define SQ64(sq110) (sq110tosq64[(sq110)]) //macro for fast table look up
bitboard setMask[64];//lookup table for setmask
#define SETBIT(board,sq) ((board) |= setMask[(sq)]) //macro for fast seting bit
bitboard clearMask[64];//lookuptable for inverse of setmask
#define CLRBIT(board,sq) ((board) &= clearMask[(sq)])//macro for fast clear bit


int pieceValue[9]= {0,100,300,400,5000,100,300,400,5000};
int pieceColor[9]= {BOTH,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK};
int fileBoard[BOARDSIZE];
int rankBoard[BOARDSIZE];



void makemove();
int min(int depth);
int max(int depth);
int evaluate();
int check4winner();
void checkGameOver();
void getamove();
void setup();
void printboard();
char b[10][11];//BOARD DATA STRUCTURE
char l[10][10];// LIVES DATA STRUCTURE
int maxdepth=9;

bitboard bishopXray[64]{
    2216338399296,5532188426368,11068671819776,22137360351232,44274703990784,88545113014528,175990714401281,70506452091906,
    562958610993184,1407396493664320,2814793004105856,5629586008276992,11259172016488704,22518344016200193,45036683737433090,
    18014673925310468,1128098963916816,2257297456238624,4796069889253440,9592139778507136,19184279557014017,38368559113962498,
    4679524173219844,9077569074761736,2256206450263048,4512417195558928,9025933902745888,18333342782202433,36666685564404866,
    1275777090881540,2270079204986888,4539058881568784,4512412933816836,9024825884411144,18049656063789585,36100411639206946,
    424704217196612,567933457682568,1134767403737104,2269530512441376,9024825867763714,18049651735592965,36099303487963146,
    141017232965652,1659000848424,283693466779728,567382638592160,1134765260406848,18049651735527936,36099303471056128,
    141012904249856,550848566272,6480472064,1108177604608,283691315142656,567382630219776
};

/*
bitboard whiteKnightLeft = 1L; bitboard whiteBishopLeft = 2L;bitboard whiteQueen = 4L;bitboard whiteKing = 8L;bitboard whiteBishopRight = 16L;bitboard whiteKnightRight = 32L;

bitboard  A0=256.000000;
bitboard  A1=512.000000;
bitboard  A2=1024.000000;
bitboard  A3=2048.000000;
bitboard  A4=4096.000000;
bitboard  A5=8192.000000;
bitboard  A6=16384.000000;
bitboard  A7=32768.000000;
bitboard  B0=65536.000000;
bitboard  B1=131072.000000;
bitboard  B2=262144.000000;
bitboard  B3=524288.000000;
bitboard  B4=1048576.000000;
bitboard  B5=2097152.000000;
bitboard  B6=4194304.000000;
bitboard  B7=8388608.000000;
bitboard  C0=16777216.000000;
bitboard  C1=33554432.000000;
bitboard  C2=67108864.000000;
bitboard  C3=134217728.000000;
bitboard  C4=268435456.000000;
bitboard  C5=536870912.000000;
bitboard  C6=1073741824.000000;
bitboard  C7=2147483648.000000;
bitboard  D0=4294967296.000000;
bitboard  D1=8589934592.000000;
bitboard  D2=17179869184.000000;
bitboard  D3=34359738368.000000;
bitboard  D4=68719476736.000000;
bitboard  D5=137438953472.000000;
bitboard  D6=274877906944.000000;
bitboard  D7=549755813888.000000;
bitboard  E0=1099511627776.000000;
bitboard  E1=2199023255552.000000;
bitboard  E2=4398046511104.000000;
bitboard  E3=8796093022208.000000;
bitboard  E4=17592186044416.000000;
bitboard  E5=35184372088832.000000;
bitboard  E6=70368744177664.000000;
bitboard  E7=140737488355328.000000;
bitboard  F0=281474976710656.000000;
bitboard  F1=562949953421312.000000;
bitboard  F2=1125899906842624.000000;
bitboard  F3=2251799813685248.000000;
bitboard  F4=4503599627370496.000000;
bitboard  F5=9007199254740992.000000;
bitboard  F6=18014398509481984.000000;
bitboard  F7=36028797018963968.000000;
bitboard  G0=72057594037927936.000000;
bitboard  G1=144115188075855872.000000;
bitboard  G2=288230376151711744.000000;
bitboard  G3=576460752303423488.000000;
bitboard  G4=1152921504606846976.000000;
bitboard  G5=2305843009213693952.000000;
bitboard  G6=4611686018427387904.000000;
bitboard  G7=9223372036854775808.000000;

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

# define A8  56 # define B8  57 # define C8  58 # define D8  59 # define E8  60 # define F8  61 # define G8  62 # define H8  63
# define A7  48 # define B7  49 # define C7  50 # define D7  51 # define E7  52 # define F7  53 # define G7  54 # define H7  55
# define A6  40 # define B6  41 # define C6  42 # define D6  43 # define E6  44 # define F6  45 # define G6  46 # define H6  47
# define A5  32 # define B5  33 # define C5  34 # define D5  35 # define E5  36 # define F5  37 # define G5  38 # define H5  39
# define A4  24 # define B4  25 # define C4  26 # define D4  27 # define E4  28 # define F4  29 # define G4  30 # define H4  31
# define A3  16 # define B3  17 # define C3  18 # define D3  18 # define E3  20 # define F3  21 # define G3  22 # define H3  23
# define A2  8  # define B2  9  # define C2  10 # define D2  11 # define E2  12 # define F2  13 # define G2  14 # define H2  15
# define A1  0  # define B1  1  # define C1  2  # define D1  4  # define E1  4  # define F1  8  # define G1  16  # define H1  32

*/
void setup() {
    {
        //=========================================================================
        //LOOKUPTABLE INITIALIZATION FOR 110 sq based and 64 sq based
        int i = 0;int file = FILE_A;int rank = RANK_1;int sq = A1;int sq64 = 0;
        for (i = 0; i <110; ++i) {sq110tosq64[i]=65;fileBoard[i]=OFFBOARD;rankBoard[i]=OFFBOARD;}
        for (i = 0; i <64; ++i) sq64tosq110[i]=BOARDSIZE;
        for (rank = RANK_1; rank <=RANK_7; ++rank) {
            for (file = FILE_A; file <= FILE_H; ++file) {
                sq = FR2SQ(file, rank);
                fileBoard[sq]=file;//CREATED LOOK UP TABLE FOR FILES
                rankBoard[sq] = rank;//CREATES LOOKUP TABLE FOR RANKS
                sq64tosq110[sq64] = sq;//CREATES LOOKUP TABLE FOR SQ110
                sq110tosq64[sq] = sq64;//CREATES LOOKUP TABLE FOR SQ64
                sq64++;
            }
        }
        //=========================================================================
        
        //------------------------------
        //------------------------------
        //BITBOARDMASK INITIALAZATION
        i=0;
        for (i = 0; i <64; ++i){
            setMask[i]=0ULL; //clearing for no reason
            clearMask[i]=0ULL; // what he said..
        }
        i=0;
        for (i = 0; i <64; ++i){
            setMask[i] |= (1ULL <<i); // shifting bits from 1 to 64
            clearMask[i] = ~setMask[i]; // inversing whatever setmask has
        }
        //------------------------------
        //------------------------------
    }
}
//BOARD RESET
void resetBoard(S_BOARD *board){
    for (int  i = 0; i < 110; ++i) board->pieces[i] = OFFBOARD; // ALL ARE SET TO OFFBOARD
    for (int  i = 0; i < 64; ++i) board->pieces[SQ110(i)] = EMPTY; // ALL ARE SET TO THEIR CORRESPONDING INDEX FROM 64 lookup table
    for(int i = 0; i < 9; ++i)board->pceNum[i] = 0;
    for(int i = 0; i < 2; ++i) {
        board->knights[i] = 0;
        board->bishops[i] = 0;
        board->queen[i] = 0;
        board->king[i] = 0;
        board->material[i] =0;
    }
    board->side = BOTH;
    board->gas = 3;
    //POSITIONING WILL BE MANAGED WITH FEN POSITIONING SYSTEM
    // position fen 1nbqkbn1/8/8/8/8/8/8/1NBQKBN1 w KQkq - 0 1
}
//UPDATELISTS
void UpdateListsMaterial(S_BOARD *board) {
    for (int i =0;i<9;i++)for (int j = 0 ; j<2; j++)board->plist[i][j]=0;
    int piece,sq,index,color;
    for(index = 0; index < BOARDSIZE; ++index) {
        sq = index;
        piece = board->pieces[index];
        if(piece!=OFFBOARD && piece!= EMPTY) {
            color = pieceColor[piece];
            board->material[color] += pieceValue[piece];
            board->plist[piece][board->pceNum[piece]] = sq;
            board->pceNum[piece]++;
        }
    }
}


//PRINTBOARD
char pceChar[] = ".NBQKnbqk";
char turnChar[] = "wn-";
char rankChar[] = "12345678";
char fileChar[] = "abcedfgh";
void printboard(const S_BOARD *board) {
    int sq,file,rank,piece;
    printf("\nGAME BOARD\n\n");
    
    for(rank = RANK_7;rank >= RANK_1;--rank){
        printf("%d ",rank+1);
        for (file = FILE_A; file <= FILE_H;++file){
            sq = FR2SQ(file, rank);
            piece = board->pieces[sq];
            printf("%3c",pceChar[piece]);
        }
        printf("\n");
    }
    
    printf("\n  "); for(file = FILE_A;file <= FILE_H;file++) printf("%3c",'a'+file);
    printf("\nIt is the %c turn to play\n",turnChar[board->side]);
}


//PARSING FEN
int parse_FEN(string FEN, S_BOARD *board){
    int rank = RANK_7;int file = FILE_A;int piece = 0;int count = 0;int sq64 =0;int sq110;
    int k =0;
    resetBoard(board);
    while (rank >= RANK_1) {
        count = 1;
        switch (FEN[k]){
            case 'n': piece = bN;break;
            case 'b': piece = bB;break;
            case 'q': piece = bQ;break;
            case 'k': piece = bK;break;
            case 'N': piece = wN;break;
            case 'B': piece = wB;break;
            case 'Q': piece = wQ;break;
            case 'K': piece = wK;break;
            case '1': {count = 1;piece = EMPTY;break;}
            case '2': {count = 2;piece = EMPTY;break;}
            case '3': {count = 3;piece = EMPTY;break;}
            case '4': {count = 4;piece = EMPTY;break;}
            case '5': {count = 5;piece = EMPTY;break;}
            case '6': {count = 6;piece = EMPTY;break;}
            case '7': {count = 7;piece = EMPTY;break;}
            case '8': {count = 8;piece = EMPTY;break;}
            case '/': {rank--;file = FILE_A;k++;continue;}
            case ' ':{rank--;file = FILE_A;k++;continue;}
            default:{printf("FEN ERROR \n");return -1;}
        }
        for (int i = 0 ; i <count;i++){
            sq64 = rank * 8 + file;
            sq110 = SQ110(sq64);
            if (piece != EMPTY) board->pieces[sq110] = piece;
            file++;
        }
        k++;
    }
    board->side = (FEN[k] == 'w') ? WHITE : BLACK;
    UpdateListsMaterial(board);
    
    return 0;
}
char *PrintSquare(const int sq){
    static char SqStr[3];
    int file = fileBoard[sq];
    int rank = rankBoard[sq];
    sprintf(SqStr, "%c%c" ,('a'+file),('1'+rank));
    return SqStr;
}
char *PrintMove(const int move){
    static char MvStr[6];
    int ff = fileBoard[FROM(move)];
    int rf = rankBoard[FROM(move)];
    int ft = fileBoard[TO(move)];
    int rt = rankBoard[TO(move)];
    sprintf(MvStr, "%c%c%c%c" ,('a'+ff),('1'+rf),('a'+ft),('1'+rt));
    return MvStr;
}

void printBitBoard(bitboard  board) {
    bitboard shift = 1ULL;
    
    int rank = 0;int file=0;int sq=0; int sq64=0;
    printf("BITBOARD\n");
    for(rank = RANK_7;rank >= RANK_1;--rank){
        for (file = FILE_A; file <= FILE_H;++file){
            sq = FR2SQ(file, rank); // 110 board
            sq64 = SQ64(sq); // 64 board
            if ((shift << sq64) & board)printf("1");else printf("0");
        }
        printf("\n");
    }
    printf("\n");
}
//==========================================================================================
//==========================================================================================
//==========================================================================================
//==========================================================================================
//==========================================================================================
//==========================================================================================
//MOVE GENERATION
#define MAXPOSITIONMOVES 256
#define move(f,t,ca) ((f)|((t)<<7)|((ca)<<14))
#define SQOFFBOARD(sq) (fileBoard[(sq)] == OFFBOARD)
int LoopSlidePieace[6]={wB , wQ , 0 , bB , bQ , 0};
int LoopSlideIndex[2] = {0 , 3};

int LoopNonSlidePieace[8]={wN , wQ , wK, 0 , bN , bQ , bK,0};
int LoopNonSlideIndex[2] = {0 , 4};

int pceDir[9][12]= {
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {-8,-19,-21,-12,8,19,21,12,0,0,0,0},//knight
    {-9,-11,11,9,0,0,0,0,0,0,0,0},//bishop
    {-9,-11,11,9,-8,-19,-21,-12,8,19,21,12},//queen
    {-1,-10,1,10,-9,-11,11,9,0,0,0,0},//king
    {-8,-19,-21,-12,8,19,21,12,0,0,0,0},//knight
    {-9,-11,11,9,0,0,0,0,0,0,0,0},//bishop
    {-9,-11,11,9,-8,-19,-21,-12,8,19,21,12},//queen
    {-1,-10,1,10,-9,-11,11,9,0,0,0,0},//king
};
int NumDir[9]={
    0,8,4,12,8,8,4,12,8
};

typedef struct {
    S_MOVE moves[MAXPOSITIONMOVES];
    int count;
}S_MOVELIST;

void addQuiteMove(const S_BOARD *board,int move,S_MOVELIST *list){
    list->moves[list->count].move = move;
    list->moves[list->count].score=0;
    list->count++;
}
void addCaptureMove(const S_BOARD *board,int move,S_MOVELIST *list){
    list->moves[list->count].move = move;
    list->moves[list->count].score=0;
    list->count++;
}

void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list) {
    
    
    list->count = 0;
    
    int pce = EMPTY;
    int side = pos->side;
    int sq = 0; int t_sq = 0;
    int pceNum = 0;
    int dir = 0;
    int index = 0;
    int pceIndex = 0;
    char pceChar[] = ".NBQKnbqk";
    //printf("\n\nSide:%d\n",side);
    
    /* Loop for slide pieces */
    
    
    bitboard p = 0ULL;
   
    
    
    pceIndex = LoopSlideIndex[side];
    pce = LoopSlidePieace[pceIndex++];
    while( pce != 0) {
        //printf("sliders pceIndex:%d pce:%d\n",pceIndex,pce);
        
        for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum) {
            sq = pos->plist[pce][pceNum];
            //printf("Piece:%c on %s\n",pceChar[pce],PrintSquare(sq));
            
            for(index = 0; index < NumDir[pce]; ++index) {
                dir = pceDir[pce][index];
                t_sq = sq + dir;
                
                while(!SQOFFBOARD(t_sq)) {
                    // BLACK ^ 1 == WHITE       WHITE ^ 1 == BLACK
                    if(pos->pieces[t_sq] != EMPTY) {
                        if( pieceColor[pos->pieces[t_sq]] == (side ^ 1)) {
                            //printf("\t\tCapture on %s\n",PrintSquare(t_sq));
                             //p |= (1ULL << SQ64(t_sq));
                        }
                        break;
                    }
                    //printf("\t\tNormal on %s\n",PrintSquare(t_sq));
                    //p |= (1ULL << SQ64(t_sq));
                    t_sq += dir;
                }
            }
        }
        
        pce = LoopSlidePieace[pceIndex++];
    }
    //printBitBoard(p);
    //cout << p << " , "<<endl;
    //printf("%lld,\n",p);
    
    /* Loop for non slide */
    pceIndex = LoopNonSlideIndex[side];
    pce = LoopNonSlidePieace[pceIndex++];
    
    while( pce != 0) {
        //printf("non sliders pceIndex:%d pce:%d\n",pceIndex,pce);
        
        for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum) {
            sq = pos->plist[pce][pceNum];
            //printf("Piece:%c on %s\n",pceChar[pce],PrintSquare(sq));
            
            for(index = 0; index < NumDir[pce]; ++index) {
                dir = pceDir[pce][index];
                t_sq = sq + dir;
                
                if(SQOFFBOARD(t_sq)) {				    
                    continue;
                }
                
                // BLACK ^ 1 == WHITE       WHITE ^ 1 == BLACK
                if(pos->pieces[t_sq] != EMPTY) {
                    if( pieceColor[pos->pieces[t_sq]] == (side ^ 1)) {
                        //printf("\t\tCapture on %s\n",PrintSquare(t_sq));
                    }
                    continue;
                }	
                //printf("\t\tNormal on %s\n",PrintSquare(t_sq));
            }
        }
        
        pce = LoopNonSlidePieace[pceIndex++];
    }	
}





//==========================================================================================
//==========================================================================================
//==========================================================================================
//==========================================================================================
//==========================================================================================
//==========================================================================================
// BITBOARD FUNCTIONS!!!


int countBits(bitboard b){
    int i =0; for(i = 0;b;i++,b &= b-1);
    return i;
}
// using magic here...
const int bitTable[64]= {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8
};
int popBit(bitboard *board){
    bitboard b = *board ^ (*board - 1);
    unsigned int fold = (unsigned) ((b& 0xffffffff)^(b>>32));
    *board &= (*board -1);
    return bitTable[(fold * 0x783a9b23) >> 26];
}
//==========================================================================================
//==========================================================================================
//==========================================================================================






void textcolor(int attr, int fg, int bg)
{ char command[13];
    sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
    printf("%s", command);
}
bool getBit(bitboard const board, int x, int y) {
    int pos = y * 8 +x;
    return ( board >> pos ) & 1 ;
}

bitboard makeBitBoard(int x, int y,int val) {
    int pos = y*8+x;
    return static_cast<bitboard>(val) << pos;
}
bitboard ArrayToBitBoard(char b[10][11]){
    bitboard bb = 0  ;
    for (int x= 0; x<10 ;x++){
        for (int y= 0; y<11 ;y++){
            if (b[x][y] != '-') bb = bb | (static_cast<bitboard>(1) << (y*8+x));
        }
    }
    return bb;
}

inline bitboard rotateBitBoard(register bitboard b) {
     bitboard t; // temporary
    //borrowed from http://www-cs-faculty.stanford.edu/~knuth/fasc1a.ps.gz
    // reflect b against diagonal line going through bits 1<<7 and 1<<56
    t = (b ^ (b >> 63)) & 0x0000000000000001; b ^= t ^ (t << 63);
    t = (b ^ (b >> 54)) & 0x0000000000000102; b ^= t ^ (t << 54);
    t = (b ^ (b >> 45)) & 0x0000000000010204; b ^= t ^ (t << 45);
    t = (b ^ (b >> 36)) & 0x0000000001020408; b ^= t ^ (t << 36);
    t = (b ^ (b >> 27)) & 0x0000000102040810; b ^= t ^ (t << 27);
    t = (b ^ (b >> 18)) & 0x0000010204081020; b ^= t ^ (t << 18);
    t = (b ^ (b >>  9)) & 0x0001020408102040; b ^= t ^ (t <<  9);
    // reflect b against vertical center line
    t = (b ^ (b >>  7)) & 0x0101010101010101; b ^= t ^ (t <<  7);
    t = (b ^ (b >>  5)) & 0x0202020202020202; b ^= t ^ (t <<  5);
    t = (b ^ (b >>  3)) & 0x0404040404040404; b ^= t ^ (t <<  3);
    t = (b ^ (b >>  1)) & 0x0808080808080808; b ^= t ^ (t <<  1);
    return b;
}



//==========================================================================================
//==========================================================================================
//==========================================================================================
//MINIMAX
/*
int min(int depth) {
    int best=20000,score;
    if (check4winner() != -1) return (check4winner());
    if (depth == maxdepth) return (evaluate());
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (b[i][j]==0) {
                b[i][j]=2; // make move on board
                score = max(depth+1);
                if (score < best) best=score;
                b[i][j]=0; // undo move
            }
        }
    }
    return(best);
}

int max(int depth) {
    int best=-20000,score;
    if (check4winner() != -1) return (check4winner());
    if (depth == maxdepth) return (evaluate());
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (b[i][j]==0) {
                b[i][j]=1; // make move on board
                score = min(depth+1);
                if (score > best) best=score;
                b[i][j]=0; // undo move
            }
        }
    }
    return(best);
}
 */
//==========================================================================================
//==========================================================================================
//==========================================================================================
//SQUARE ATTACKED SECTION
//CHECK IF THE SQUARE IS ATTACKED OR NOT RETURNS TRUE IF ITS IS NEEDS COLOR AND BOARD
int pieceKnightQueen[9] = {FALSE,TRUE,FALSE,TRUE,FALSE,TRUE,FALSE,TRUE,FALSE};
int pieceKing[9] = {FALSE,FALSE,FALSE,FALSE,TRUE,FALSE,FALSE,FALSE,TRUE};
int pieceBishopQueen[9]= {FALSE,FALSE,TRUE,TRUE,FALSE,FALSE,TRUE,TRUE,FALSE};
int piceSlides[9]={FALSE,FALSE,TRUE,TRUE,FALSE,FALSE,TRUE,TRUE,FALSE};
#define IsKightQeen(p) (pieceKnightQueen[(p)])
#define IsKing(p) (pieceKing[(p)])
#define IsBishopQeen(p) (pieceBishopQueen[(p)])
const int KnightDirection[8] = {-8,-19,-21,-12,8,19,21,12};
const int BishopDirection[4] = {-9,-11,11,9};
const int KingDirection[8]= {-1,-10,1,10,-9,-11,11,9};
int sqAttacked(const int sq, const int side, const S_BOARD *board){
    int pce,index,t_sq,dir;
    //King
    for (index = 0; index <8;++index){
        pce = board->pieces[sq + KingDirection[index]];
        if (IsKing(pce)&& pieceColor[pce]==side)return TRUE;
    }
    //knight or queen
    for (index = 0; index <8;++index){
        pce = board->pieces[sq + KnightDirection[index]];
        if (IsKightQeen(pce)&& pieceColor[pce]==side)return TRUE;
    }
    //Bishop or queen
    for(index = 0; index < 4; ++index) {
        dir = BishopDirection[index];
        t_sq = sq + dir;
        pce = board->pieces[t_sq];
        while(pce != OFFBOARD) {
            if(pce != EMPTY) {
                if(IsBishopQeen(pce) && pieceColor[pce] == side) {
                    return TRUE;
                }
                break;
            }
            t_sq += dir;
            pce = board->pieces[t_sq];
        }
    }
    return FALSE;
}
//=================================================================================================
//=================================================================================================


void getamove() {
    char x1,x2;
    int y1,y2;
    int xx1 = 0;
    int xx2 = 0;
    cout << "Enter your move:  ";
    cin >> x1 >> y1 >> x2 >> y2;
    
    if (x1 == 'a' | x1 == 'A') xx1 = 0;
    if (x1 == 'b' | x1 == 'B') xx1 = 1;
    if (x1 == 'c' | x1 == 'C') xx1 = 2;
    if (x1 == 'd' | x1 == 'D') xx1 = 3;
    if (x1 == 'e' | x1 == 'E') xx1 = 4;
    if (x1 == 'f' | x1 == 'F') xx1 = 5;
    if (x1 == 'g' | x1 == 'G') xx1 = 6;
    if (x1 == 'h' | x1 == 'H') xx1 = 7;
    
    if (x2 == 'a' | x2 == 'A') xx2 = 0;
    if (x2 == 'b' | x2 == 'B') xx2 = 1;
    if (x2 == 'c' | x2 == 'C') xx2 = 2;
    if (x2 == 'd' | x2 == 'D') xx2 = 3;
    if (x2 == 'e' | x2 == 'E') xx2 = 4;
    if (x2 == 'f' | x2 == 'F') xx2 = 5;
    if (x2 == 'g' | x2 == 'G') xx2 = 6;
    if (x2 == 'h' | x2 == 'H') xx2 = 6;
    y1 = y1 -1;
    y2 = y2 -1;
    char oldPiece = b[y1][xx1];
    char oldLife = l[y1][xx1];
    b[y1][xx1]='-';
    l[y1][xx1]='-';
    b[y2][xx2]=oldPiece;
    l[y2][xx2]=oldLife;
    
}

int main (){
    
    setup();
    /*
   
    
    
  
    parse_FEN("1nbqkbn1/8/8/8/8/8/1NBQKBN1 w KQkq - 0 1", board);
    printboard(board);
 
    
    int rank = 0;
    int file = 0;
    
    int sq = 0;
    
    printf("\n\nSquares attacked by:%c\n",'w');
    for(rank = RANK_7; rank >= RANK_1; --rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file,rank);
            if(sqAttacked(sq,WHITE,board)==TRUE) {
                printf("X");
            } else {
                printf("-");
            }
            
        }
        printf("\n");
    }  
    printf("\n\n");
    int moveto = 0;
    int from =A2; int to = H7;
    int cap = wB;
    
    moveto = (from)| (to<<7) |(cap <<14);
    printf("\ndec:%d hex:%x\n",moveto,moveto); // STORE MOVE
    
    printf("from:%d to:%d cap:%d\n",FROM(moveto),TO(moveto),CAPTURED(moveto)); //USE MOVE

    
    printf("from:%s\n",PrintSquare(from));
    printf("to:%s\n",PrintSquare(to));
    printf("move:%s\n",PrintMove(moveto));
    
    int index=0 ;int score = 0; int move =0;S_MOVELIST list[1];
    for(index = 0 ; index < list->count; ++index){
        move = list->moves[index].move;
        score = list->moves[index].score;
        printf("move:%d > %s (score:%d)\n",index+1,PrintMove(move),score);
    }
    printf("movelist total %d: \n",list->count);
    
  
    
    
    
    bitboard p = 0ULL;
    p |= (1ULL << SQ64(D2));
    p |= (1ULL << SQ64(D3));
    p |= (1ULL << SQ64(D4));
    
    printBitBoard(p);

    printf("%d\n",countBits(p));
  
    printf("%d\n",popBit(&p));
    printf("%d\n",popBit(&p));
    printBitBoard(p);
    
    SETBIT(p, 25);
    printBitBoard(p);
    SETBIT(p, 28);
    printBitBoard(p);
    
    // BITBOARD TEMPLATE GENERATOR
    int f = 0;int r = 0;
    for(int i = 8 ; i<64 ; i++){
        //cout << pow(2, i);
        if (f > 7) {
            r++;
            f =0;
        }
        printf( "%s %c%d=%F;\n", "bitboard ",rankOf(r),f,pow(2,i));
        f++;
    }

    
    
    
    
    
    {
        printboard();
        cout << "\n\n";
        bitboard board = ArrayToBitBoard(b);
        board = rotateBitBoard(board);
        printBitBoard(board);
        cout << "\n\n";
    }
    
    
    getamove();
    {
        printboard();
        cout << "\n\n";
        bitboard board = ArrayToBitBoard(b);
        board = rotateBitBoard(board);
        printBitBoard(board);
        cout << "\n\n";
    }
    
    //checkGameOver();
    //makemove();
    //checkGameOver();
    
  
    //S_BOARD board[1];
    //
    */
    S_BOARD board[1];
    S_MOVELIST list[1];
    //resetBoard(board);
    
    parse_FEN("B7/8/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("1B6/8/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("2B5/8/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("3B4/8/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("4B3/8/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("5B2/8/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("6B1/8/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("7B/8/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    
    parse_FEN("8/B7/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/1B6/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/2B5/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/3B4/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/4B3/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/5B2/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/6B1/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/7B/8/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    
    parse_FEN("8/8/B7/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/1B6/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/2B5/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/3B4/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/4B3/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/5B2/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/6B1/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/7B/8/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    
    parse_FEN("8/8/8/B7/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/1B6/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/2B5/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/3B4/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/4B3/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/5B2/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/6B1/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/7B/8/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    
    parse_FEN("8/8/8/8/B7/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/1B6/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/2B5/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/3B4/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/4B3/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/5B2/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/6B1/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/7B/8/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    
    parse_FEN("8/8/8/8/8/B7/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/1B6/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/2B5/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/3B4/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/4B3/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/5B2/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/6B1/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/7B/8 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    
    parse_FEN("8/8/8/8/8/8/B7 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/8/1B6 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/8/2B5 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/8/3B4 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/8/4B3 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/8/5B2 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/8/6B1 w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    parse_FEN("8/8/8/8/8/8/7B w KQkq - 0 1", board);
    GenerateAllMoves(board,list);
    
    
    parse_FEN("1nbqkbn1/8/8/8/8/8/1NBQKBN1 w KQkq - 0 1", board);
    timer t;
    t.Start();
    int counter = 0;
    for (int i = 0;i<1000000000;i++) {
        GenerateAllMoves(board,list);
        //printBitBoard(bishopXray[i]);
        counter ++;
        if (t.GetTicks() > 5000000) break;
    }
    
     printf("\n COUNTER : %d\n",counter);
}

 
