/* 
 * File:   safer.c
 * Author: lcosta, rmarques
 *
 * Created on September 18, 2008, 8:05 PM
 */

#include <stdio.h>

#include "safer.h"
#include "tbl.h"
#include "modular.h"
#include "types.h"
#include "operations.h"

/** Left rotate 3 bits of a byte */
INLINE byte saferLS3(REG byte b) {

    REG byte l = b << 3;
    REG byte r = b >> 5; /* 8 - 3 = 5 */

    l |= r;

    return l;

}

/** rotate bytes of a round key */
INLINE void saferRotateBytes(byte *from, byte *to) {

    REG int b;

    for (b = 1; b < 18; b++) {
        to[b] = saferLS3(from[b]);
    }

}

/** copy from a key array to another */
INLINE void saferKeyCopy(key from, key to) {

    REG int b;

    for (b = 1; b < 17; b++) {
        to[b] = from[b];
    }

}

/** receives a 16byte byte key and returns 17 keys for each Safer+ enc/dec round */
INLINE void keySchedule(key k, key *keys) {

    key roundkey[18];
    REG int i, r, b, t;

    roundkey[1][1] = k[1];
    roundkey[1][2] = k[2];
    roundkey[1][3] = k[3];
    roundkey[1][4] = k[4];
    roundkey[1][5] = k[5];
    roundkey[1][6] = k[6];
    roundkey[1][7] = k[7];
    roundkey[1][8] = k[8];
    roundkey[1][9] = k[9];
    roundkey[1][10] = k[10];
    roundkey[1][11] = k[11];
    roundkey[1][12] = k[12];
    roundkey[1][13] = k[13];
    roundkey[1][14] = k[14];
    roundkey[1][15] = k[15];
    roundkey[1][16] = k[16];

/*
     K1 = first 16 round bytes
*/
    saferKeyCopy(roundkey[1], keys[1]);

/*
     Sum bit-by-bit modulo two. result to roundkey 17th byte (fig. 4)
*/
    roundkey[1][17] = roundkey[1][1];
    for (i = 2; i < 17; i++) {
        roundkey[1][17] = saferXor(roundkey[1][17], roundkey[1][i]);
    }

/*
     Start of K2, ...
*/
    for (r = 2; r < 18; r++) {
/*
         Rotate left all round bytes, each by 3bit positions
*/
        saferRotateBytes(roundkey[r - 1], roundkey[r]);
    }

    for (r = 2; r < 18; r++) {

        for (b = 1; b < 17; b++) {
/*
             copy bytes according to round (Round 2 start at byte 2, ... Round 6 start at byte 6, ...
*/
            t = r + (b - 1);
            if (t > 17) {
                t = t % 17;
            }

            keys[r][b] = roundkey[r][t];
            keys[r][b] = saferAdd(keys[r][b], saferBias(r, b));
        }
    }
}

/** Safer encrypt rounds */
INLINE void saferEncryptBlock(block inputblock) {
    
    REG int i;
    REG int k1;
    REG int k2;

    for (i = 1; i < 9; i++) {
        
        k2 = 2 * i;
        k1 = k2 - 1;

        inputblock[1] = saferAdd(saferExp(saferXor(inputblock[1],keys[k1][1])),keys[k2][1]);
        inputblock[4] = saferAdd(saferExp(saferXor(inputblock[4], keys[k1][4])), keys[k2][4]);
        inputblock[5] = saferAdd(saferExp(saferXor(inputblock[5], keys[k1][5])), keys[k2][5]);
        inputblock[8] = saferAdd(saferExp(saferXor(inputblock[8], keys[k1][8])), keys[k2][8]);
        inputblock[9] = saferAdd(saferExp(saferXor(inputblock[9], keys[k1][9])), keys[k2][9]);
        inputblock[12] = saferAdd(saferExp(saferXor(inputblock[12], keys[k1][12])), keys[k2][12]);
        inputblock[13] = saferAdd(saferExp(saferXor(inputblock[13], keys[k1][13])), keys[k2][13]);
        inputblock[16] = saferAdd(saferExp(saferXor(inputblock[16], keys[k1][16])), keys[k2][16]);


        inputblock[2] = saferXor(saferLog(saferAdd(inputblock[2], keys[k1][2])), keys[k2][2]);
        inputblock[3] = saferXor(saferLog(saferAdd(inputblock[3], keys[k1][3])), keys[k2][3]);
        inputblock[6] = saferXor(saferLog(saferAdd(inputblock[6], keys[k1][6])), keys[k2][6]);
        inputblock[7] = saferXor(saferLog(saferAdd(inputblock[7], keys[k1][7])), keys[k2][7]);
        inputblock[10] = saferXor(saferLog(saferAdd(inputblock[10], keys[k1][10])), keys[k2][10]);
        inputblock[11] = saferXor(saferLog(saferAdd(inputblock[11], keys[k1][11])), keys[k2][11]);
        inputblock[14] = saferXor(saferLog(saferAdd(inputblock[14], keys[k1][14])), keys[k2][14]);
        inputblock[15] = saferXor(saferLog(saferAdd(inputblock[15], keys[k1][15])), keys[k2][15]);
    
        saferMatrixXMul(inputblock);
    
    }

/*
     17th key
*/
    inputblock[1] = saferXor(inputblock[1], keys[17][1]);
    inputblock[4] = saferXor(inputblock[4], keys[17][4]);
    inputblock[5] = saferXor(inputblock[5], keys[17][5]);
    inputblock[8] = saferXor(inputblock[8], keys[17][8]);
    inputblock[9] = saferXor(inputblock[9], keys[17][9]);
    inputblock[12] = saferXor(inputblock[12], keys[17][12]);
    inputblock[13] = saferXor(inputblock[13], keys[17][13]);
    inputblock[16] = saferXor(inputblock[16], keys[17][16]);

    inputblock[2] = saferAdd(inputblock[2], keys[17][2]);
    inputblock[3] = saferAdd(inputblock[3], keys[17][3]);
    inputblock[6] = saferAdd(inputblock[6], keys[17][6]);
    inputblock[7] = saferAdd(inputblock[7], keys[17][7]);
    inputblock[10] = saferAdd(inputblock[10], keys[17][10]);
    inputblock[11] = saferAdd(inputblock[11], keys[17][11]);
    inputblock[14] = saferAdd(inputblock[14], keys[17][14]);
    inputblock[15] = saferAdd(inputblock[15], keys[17][15]);

}

/** Safer decrypt rounds */
INLINE void saferDecryptBlock(block inputblock) {
    
    REG int i;
    REG int k1;
    REG int k2;


/*
     17th key
*/
    inputblock[1] = saferXor(inputblock[1], keys[17][1]);
    inputblock[4] = saferXor(inputblock[4], keys[17][4]);
    inputblock[5] = saferXor(inputblock[5], keys[17][5]);
    inputblock[8] = saferXor(inputblock[8], keys[17][8]);
    inputblock[9] = saferXor(inputblock[9], keys[17][9]);
    inputblock[12] = saferXor(inputblock[12], keys[17][12]);
    inputblock[13] = saferXor(inputblock[13], keys[17][13]);
    inputblock[16] = saferXor(inputblock[16], keys[17][16]);

/*
     17th key
*/
    inputblock[2] = saferSub(inputblock[2], keys[17][2]);
    inputblock[3] = saferSub(inputblock[3], keys[17][3]);
    inputblock[6] = saferSub(inputblock[6], keys[17][6]);
    inputblock[7] = saferSub(inputblock[7], keys[17][7]);
    inputblock[10] = saferSub(inputblock[10], keys[17][10]);
    inputblock[11] = saferSub(inputblock[11], keys[17][11]);
    inputblock[14] = saferSub(inputblock[14], keys[17][14]);
    inputblock[15] = saferSub(inputblock[15], keys[17][15]);

    for (i = 8; i > 0; i--) {
        
        saferMatrixYMul(inputblock);
        
        k2 = 2 * i;
        k1 = k2 - 1;
        
        inputblock[1] = saferXor(saferLog(saferSub(inputblock[1], keys[k2][1])), keys[k1][1]);
        inputblock[4] = saferXor(saferLog(saferSub(inputblock[4], keys[k2][4])), keys[k1][4]);
        inputblock[5] = saferXor(saferLog(saferSub(inputblock[5], keys[k2][5])), keys[k1][5]);
        inputblock[8] = saferXor(saferLog(saferSub(inputblock[8], keys[k2][8])), keys[k1][8]);
        inputblock[9] = saferXor(saferLog(saferSub(inputblock[9], keys[k2][9])), keys[k1][9]);
        inputblock[12] = saferXor(saferLog(saferSub(inputblock[12], keys[k2][12])), keys[k1][12]);
        inputblock[13] = saferXor(saferLog(saferSub(inputblock[13], keys[k2][13])), keys[k1][13]);
        inputblock[16] = saferXor(saferLog(saferSub(inputblock[16], keys[k2][16])), keys[k1][16]);

        inputblock[2] = saferSub(saferExp(saferXor(inputblock[2], keys[k2][2])), keys[k1][2]);
        inputblock[3] = saferSub(saferExp(saferXor(inputblock[3], keys[k2][3])), keys[k1][3]);
        inputblock[6] = saferSub(saferExp(saferXor(inputblock[6], keys[k2][6])), keys[k1][6]);
        inputblock[7] = saferSub(saferExp(saferXor(inputblock[7], keys[k2][7])), keys[k1][7]);
        inputblock[10] = saferSub(saferExp(saferXor(inputblock[10], keys[k2][10])), keys[k1][10]);
        inputblock[11] = saferSub(saferExp(saferXor(inputblock[11], keys[k2][11])), keys[k1][11]);
        inputblock[14] = saferSub(saferExp(saferXor(inputblock[14], keys[k2][14])), keys[k1][14]);
        inputblock[15] = saferSub(saferExp(saferXor(inputblock[15], keys[k2][15])), keys[k1][15]);
    }

}

