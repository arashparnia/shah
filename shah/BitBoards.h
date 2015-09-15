//
//  BitBoards.h
//  csc180game
//
//  Created by arash parnia on 3/18/15.
//  Copyright (c) 2015 arash. All rights reserved.
//

#ifndef __csc180game__BitBoards__
#define __csc180game__BitBoards__

#include <stdio.h>

#endif /*


#define SETBIT(board,sq) ((board) |= setMask[(sq)]) //macro for fast seting bit
#define CLRBIT(board,sq) ((board) &= clearMask[(sq)])//macro for fast clear bit
BITBOARD setMask[64];//lookup table for setmask
#define SETBIT(board,sq) ((board) |= setMask[(sq)]) //macro for fast seting bit
BITBOARD clearMask[64];//lookuptable for inverse of setmask
#define CLRBIT(board,sq) ((board) &= clearMask[(sq)])//macro for fast clear bit


BITBOARD BitBoardRank[8] = {
    0xFF00000000000000ULL,
    0x00FF000000000000L,
    0x0000FF0000000000L,
    0x000000FF00000000L,
    0x00000000FF000000L,
    0x0000000000FF0000L,
    0x000000000000FF00L,
    0x00000000000000FFL,
};

BITBOARD BitBoardFile[8] = {
    0x0101010101010101L,
    0x0202020202020202L,
    0x0404040404040404L,
    0x0808080808080808L,
    0x1010101010101010L,
    0x2020202020202020L,
    0x4040404040404040L,
    0x8080808080808080L,
};
//======================================================================

static const long long int BISHOP_MAGICS[64] = {
    0x2008300840c242, 0x4908526008a0204, 0x40c040c82000000, 0x140402800c0410, 0x81040c2000010304, 0x101100290408000, 0x1408a808290480, 0x1044420814020a00, 0x1060182058078112, 0x4000c088a140820, 0x40200800ac108400, 0x3051040401804200, 0x4800040422000400, 0x480082210100400, 0x24022b04022005a0, 0x2020020a8080840, 0x4100300d481180, 0x220000404040852, 0x801041204050200, 0xe00042a020020, 0x4001080a08001, 0x26201100a01020, 0x289000188411010, 0x880022080200, 0x368082340102100, 0x104040842080840, 0x8a08580105020400, 0x8080000202020, 0x2001010100104000, 0x3001020002c80400, 0xb118120280820110, 0x100042008100821a, 0x82482210400200, 0x108041c03110120, 0x3802019000060029, 0x8108200800890104, 0x502020200100880, 0x22020c100828180, 0x810008914021100, 0x82040880a04a0108, 0x3061019040021008, 0x40441024001802, 0x9009014502401000, 0x2088082018000300, 0x801a400091000a00, 0x8409100200900200, 0x8010401802420, 0x1140400840040, 0x1006008a60301000, 0x5904008404a220, 0x14404040000, 0x300c0042021480, 0x900005042020000, 0x82e48220080, 0x18101308111018, 0x10a302400828048, 0x1002208c10091005, 0x5002002404040480, 0x820000104010408, 0x1007018000608804, 0x4100000040328200, 0x3000414202040104, 0x2840041110090104, 0x6028029004010010};


// BOARD STRUCTURE ---------------------------------------

BITBOARD King_Xray[64]={
    
};
*/