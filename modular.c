/*
 * File:   modular.c
 * Author: lcosta, rmarques
 *
 * Created on September 21, 2008, 9:00 AM
 */

#include <stdio.h>
#include "modular.h"

#ifdef SAFERMATRIX_SIMPLE
static byte matrixM1[17][17] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 2, 2, 1, 1, 16, 8, 2, 1, 4, 2, 4, 2, 1, 1, 4, 4},
    { 0, 1, 1, 1, 1, 8, 4, 2, 1, 2, 1, 4, 2, 1, 1, 2, 2},
    { 0, 1, 1, 4, 4, 2, 1, 4, 2, 4, 2, 16, 8, 2, 2, 1, 1},
    { 0, 1, 1, 2, 2, 2, 1, 2, 1, 4, 2, 8, 4, 1, 1, 1, 1},
    { 0, 4, 4, 2, 1, 4, 2, 4, 2, 16, 8, 1, 1, 1, 1, 2, 2},
    { 0, 2, 2, 2, 1, 2, 1, 4, 2, 8, 4, 1, 1, 1, 1, 1, 1},
    { 0, 1, 1, 4, 2, 4, 2, 16, 8, 2, 1, 2, 2, 4, 4, 1, 1},
    { 0, 1, 1, 2, 1, 4, 2, 8, 4, 2, 1, 1, 1, 2, 2, 1, 1},
    { 0, 2, 1, 16, 8, 1, 1, 2, 2, 1, 1, 4, 4, 4, 2, 4, 2},
    { 0, 2, 1, 8, 4, 1, 1, 1, 1, 1, 1, 2, 2, 4, 2, 2, 1},
    { 0, 4, 2, 4, 2, 4, 4, 1, 1, 2, 2, 1, 1, 16, 8, 2, 1},
    { 0, 2, 1, 4, 2, 2, 2, 1, 1, 1, 1, 1, 1, 8, 4, 2, 1},
    { 0, 4, 2, 2, 2, 1, 1, 4, 4, 1, 1, 4, 2, 2, 1, 16, 8},
    { 0, 4, 2, 1, 1, 1, 1, 2, 2, 1, 1, 2, 1, 2, 1, 8, 4},
    { 0, 16, 8, 1, 1, 2, 2, 1, 1, 4, 4, 2, 1, 4, 2, 4, 2},
    { 0, 8, 4, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 1, 4, 2}
};


static byte matrixM2[17][17] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 254, 1, 254, 1, 255, 4, 248, 2, 252, 1, 255, 1, 254, 1, 255},
    {0, 252, 4, 254, 4, 254, 2, 248, 16, 254, 4, 255, 1, 255, 2, 255, 1},
    {0, 1, 254, 1, 255, 2, 252, 1, 255, 1, 255, 1, 254, 2, 254, 4, 248},
    {0, 254, 4, 254, 2, 254, 4, 255, 1, 255, 1, 255, 2, 252, 4, 248, 16},
    {0, 1, 255, 2, 252, 1, 255, 1, 254, 1, 254, 1, 255, 4, 248, 2, 254},
    {0, 255, 1, 254, 4, 255, 1, 255, 2, 254, 4, 254, 2, 248, 16, 252, 4},
    {0, 2, 252, 1, 255, 1, 254, 1, 255, 2, 254, 4, 248, 1, 255, 1, 254},
    {0, 254, 4, 255, 1, 255, 2, 255, 1, 252, 4, 248, 16, 254, 2, 254, 4},
    {0, 1, 255, 1, 254, 1, 255, 2, 252, 4, 248, 2, 254, 1, 254, 1, 255},
    {0, 255, 1, 255, 2, 255, 1, 254, 4, 248, 16, 252, 4, 254, 4, 254, 2},
    {0, 1, 254, 1, 255, 4, 248, 2, 254, 1, 255, 1, 254, 1, 255, 2, 252},
    {0, 255, 2, 255, 1, 248, 16, 252, 4, 254, 2, 254, 4, 255, 1, 254, 4},
    {0, 4, 248, 2, 254, 1, 254, 1, 255, 1, 254, 1, 255, 2, 252, 1, 255},
    {0, 248, 16, 252, 4, 254, 4, 254, 2, 255, 2, 255, 1, 254, 4, 255, 1},
    {0, 1, 255, 4, 248, 2, 254, 1, 254, 1, 255, 2, 252, 1, 255, 1, 254},
    {0, 254, 2, 248, 16, 252, 4, 254, 4, 255, 1, 254, 4, 255, 1, 255, 2}
};
#endif

/**
 * Safer+ add operation using byte mathematics
 */
INLINE byte saferAdd_1(byte n, byte m) {
    return (byte) (n + m);
}

/**
 * Safer+ sub operation using byte mathematics
 */
INLINE byte saferSub_1(byte n, byte m) {
    return (byte) (n - m);
}

/**
 * Safer+ mul operation using byte mathematics
 */
INLINE byte saferMul_1(byte n, byte m) {
    return (byte) (n * m);
}

/**
 * Safer+ exp operation using byte mathematics: returns (45^m) mod 257,
 * using Bruce Schneier's "right-to-left binary algorithm 
 * Applied Cryptography, 2ed.
 */
INLINE byte saferExp_1(byte m) {

    REG unsigned int result = 1;
    REG unsigned int base = 45;

    if (m == 128) return 0;

    while (m > 0) {
        if ((m & 1) == 1) {

            /*
              multiply this bit's contribution (using modulus to keep result small)
              cannot use saferMul, because that would be modulus 256
             */

            result = (result * base) % 257;
        }

        /* move to the next bit of the exponent, square (and mod) the base accordingly */
        m >>= 1;
        base = (base * base) % 257;
    }

    /*
             pre-calculations show this is always 0..255, so can safely reduce to byte
     */
    return (byte) result;
}

/**
 * Safer+ log operation using byte mathematics: instead of doing a simple incremental search
 * split the search space in two and try to meet-in-the-middle  
 */
INLINE byte saferLog_1(byte x) {

    REG byte y1 = 0;
    REG byte y2 = 255;

    if (x == 0) return 128;

    for (; y1 < y2; y1++, y2--) { /* stops when y1=128, y2=127, all 255 checked! */
        if (saferExp(y1) == x) return y1;
        if (saferExp(y2) == x) return y2;
    }

    return 0;
}

/**
 * SAFER+ mul operations using left shifts (multiply by power of 2)
 */
INLINE byte saferMulPower2(byte n, byte power) {
    return (byte) (n << power);
}

/**
 * Safer+ matriz multiplication. simple version. y = xM
 */
#ifdef SAFERMATRIX_SIMPLE 
INLINE void saferMatrixXMul_1(block blk) {

    REG byte y;
    REG int i;
    REG int j;

    block aux;


    for (i = 1; i < 17; i++) {

        y = 0;

        for (j = 1; j < 17; j++) {
            y = saferAdd(y, saferMul(blk[j], matrixM1[j][i]));
        }

        aux[i] = y;
    }

    /* copy to final block */
    for (i = 1; i < 17; i++) {
        blk[i] = aux[i];
    }
}
#endif
/**
 * Safer+ matrix multiplication. Yaniv Shaked, Avishai Wool version. y = xM, but less operations
 * 
 * pseudo-code:
 * X = (x0,x1,x2,...,xn) = input
 * h1 = x1 + x2 + x3 + x6 +x7 + 2(x0 + x5 + 2(x4))
 * h2 = x8 + x9 + x11 + 2(x10 + x12 +x13 + 2(x15 + 2(x14)))
 * y1 = h1 + h2
 * y0 = y1 + h2
 * 
 * since the matrix has an intial column and a line of zeros,
 * and the input has always a leading zero
 * so matrix indexes need to be adjusted...
 */
#ifdef SAFERMATRIX_OPTIM 
INLINE void saferMatrixXMul_2(block blk) {

    REG int h1;
    REG int h2;
    REG int t1;

    block aux;

    /**********************
     * 
     * START   columns 1, 2 (0 contains zeros)
     * first part of the matrix: all values are x,x
     * 
     **********************/
    h1 = saferAdd(blk[7], blk[8]);
    h1 = saferAdd(blk[4], h1);
    h1 = saferAdd(blk[3], h1);
    h1 = saferAdd(blk[2], h1);

    /*
         when the matrix value is 4,4, multiply by 2 once (another one later)
     */
    t1 = saferAdd(blk[6], saferMulPower2(blk[5], 1));
    t1 = saferAdd(blk[1], t1);
    /*
         second multiplication by 2 (covers items that must be used twice and four times)
     */
    h1 = saferAdd(h1, saferMulPower2(t1, 1));

    /*
         second half of the matrix:
         the parts where the matrix is not x,x, but instead 2x,x
     */
    h2 = saferAdd(blk[10], blk[12]);
    h2 = saferAdd(blk[9], h2);

    /*
         first multiplication by 2 (two more to follow)
     */
    t1 = saferAdd(blk[16], saferMulPower2(blk[15], 1));

    /*
         second multiplication by 2 (one more to follow)
     */
    t1 = saferAdd(blk[14], saferMulPower2(t1, 1));
    t1 = saferAdd(blk[13], t1);
    t1 = saferAdd(blk[11], t1);

    /*
         third multiplication by 2
     */
    h2 = saferAdd(h2, saferMulPower2(t1, 1));

    aux[2] = saferAdd(h1, h2);
    aux[1] = saferAdd(aux[2], h2);

    /**********************
     * 
     * END      columns 1, 2
     * 
     **********************
     * 
     * START    columns 3, 4
     * first part of the matrix: all values are x,x
     * 
     **********************/
    h1 = saferAdd(blk[15], blk[16]);
    h1 = saferAdd(blk[14], h1);
    h1 = saferAdd(blk[2], h1);
    h1 = saferAdd(blk[1], h1);

    /*
         when the matrix value is 4,4, multiply by 2 once (another one later)
     */
    t1 = saferAdd(blk[4], saferMulPower2(blk[3], 1));
    t1 = saferAdd(blk[13], t1);
    /*
         second multiplication by 2 (covers items that must be used twice and four times)
     */
    h1 = saferAdd(h1, saferMulPower2(t1, 1));

    /*
         second half of the matrix:
         the parts where the matrix is not x,x, but instead 2x,x
     */
    h2 = saferAdd(blk[5], blk[6]);
    h2 = saferAdd(blk[8], h2);

    /*
         first multiplication by 2 (two more to follow)
     */
    t1 = saferAdd(blk[10], saferMulPower2(blk[9], 1));

    /*
         second multiplication by 2 (one more to follow)
     */
    t1 = saferAdd(blk[12], saferMulPower2(t1, 1));
    t1 = saferAdd(blk[11], t1);
    t1 = saferAdd(blk[7], t1);

    /*
         third multiplication by 2
     */
    h2 = saferAdd(h2, saferMulPower2(t1, 1));

    aux[4] = saferAdd(h1, h2);
    aux[3] = saferAdd(aux[4], h2);

    /**********************
     * 
     * END      columns 3, 4
     * 
     **********************
     * 
     * START    columns 5, 6
     * first part of the matrix: all values are x,x
     * 
     **********************/
    h1 = saferAdd(blk[14], blk[16]);
    h1 = saferAdd(blk[13], h1);
    h1 = saferAdd(blk[10], h1);
    h1 = saferAdd(blk[9], h1);

    /*
         when the matrix value is 4,4, multiply by 2 once (another one later)
     */
    t1 = saferAdd(blk[12], saferMulPower2(blk[11], 1));
    t1 = saferAdd(blk[15], t1);
    /*
         second multiplication by 2 (covers items that must be used twice and four times)
     */
    h1 = saferAdd(h1, saferMulPower2(t1, 1));

    /*
         second half of the matrix:
         the parts where the matrix is not x,x, but instead 2x,x
     */
    h2 = saferAdd(blk[3], blk[4]);
    h2 = saferAdd(blk[6], h2);

    /*
         first multiplication by 2 (two more to follow)
     */
    t1 = saferAdd(blk[2], saferMulPower2(blk[1], 1));

    /*
         second multiplication by 2 (one more to follow)
     */
    t1 = saferAdd(blk[8], saferMulPower2(t1, 1));
    t1 = saferAdd(blk[7], t1);
    t1 = saferAdd(blk[5], t1);

    /*
         third multiplication by 2
     */
    h2 = saferAdd(h2, saferMulPower2(t1, 1));

    aux[6] = saferAdd(h1, h2);
    aux[5] = saferAdd(aux[6], h2);

    /**********************
     * 
     * END      columns 5, 6
     * 
     **********************
     * 
     * START    columns 7, 8
     * first part of the matrix: all values are x,x
     * 
     **********************/
    h1 = saferAdd(blk[15], blk[16]);
    h1 = saferAdd(blk[12], h1);
    h1 = saferAdd(blk[11], h1);
    h1 = saferAdd(blk[10], h1);

    /*
         when the matrix value is 4,4, multiply by 2 once (another one later)
     */
    t1 = saferAdd(blk[14], saferMulPower2(blk[13], 1));
    t1 = saferAdd(blk[9], t1);
    /*
         second multiplication by 2 (covers items that must be used twice and four times)
     */
    h1 = saferAdd(h1, saferMulPower2(t1, 1));

    /*
         second half of the matrix:
         the parts where the matrix is not x,x, but instead 2x,x
     */
    h2 = saferAdd(blk[1], blk[2]);
    h2 = saferAdd(blk[4], h2);

    /*
         first multiplication by 2 (two more to follow)
     */
    t1 = saferAdd(blk[8], saferMulPower2(blk[7], 1));

    /*
         second multiplication by 2 (one more to follow)
     */
    t1 = saferAdd(blk[6], saferMulPower2(t1, 1));
    t1 = saferAdd(blk[5], t1);
    t1 = saferAdd(blk[3], t1);

    /*
         third multiplication by 2
     */
    h2 = saferAdd(h2, saferMulPower2(t1, 1));

    aux[8] = saferAdd(h1, h2);
    aux[7] = saferAdd(aux[8], h2);

    /**********************
     * 
     * END      columns 7, 8
     * 
     **********************
     * 
     * START    columns 9, 10
     * first part of the matrix: all values are x,x
     * 
     **********************/
    h1 = saferAdd(blk[13], blk[14]);
    h1 = saferAdd(blk[12], h1);
    h1 = saferAdd(blk[10], h1);
    h1 = saferAdd(blk[9], h1);

    /*
         when the matrix value is 4,4, multiply by 2 once (another one later)
     */
    t1 = saferAdd(blk[16], saferMulPower2(blk[15], 1));
    t1 = saferAdd(blk[11], t1);
    /*
         second multiplication by 2 (covers items that must be used twice and four times)
     */
    h1 = saferAdd(h1, saferMulPower2(t1, 1));

    /*
         second half of the matrix:
         the parts where the matrix is not x,x, but instead 2x,x
     */
    h2 = saferAdd(blk[7], blk[8]);
    h2 = saferAdd(blk[2], h2);

    /*
         first multiplication by 2 (two more to follow)
     */
    t1 = saferAdd(blk[6], saferMulPower2(blk[5], 1));

    /*
         second multiplication by 2 (one more to follow)
     */
    t1 = saferAdd(blk[4], saferMulPower2(t1, 1));
    t1 = saferAdd(blk[3], t1);
    t1 = saferAdd(blk[1], t1);

    /*
         third multiplication by 2
     */
    h2 = saferAdd(h2, saferMulPower2(t1, 1));

    aux[10] = saferAdd(h1, h2);
    aux[9] = saferAdd(aux[10], h2);

    /**********************
     * 
     * END      columns 9, 10
     * 
     **********************
     * 
     * START    columns 11, 12
     * first part of the matrix: all values are x,x
     * 
     **********************/
    h1 = saferAdd(blk[11], blk[12]);
    h1 = saferAdd(blk[8], h1);
    h1 = saferAdd(blk[6], h1);
    h1 = saferAdd(blk[5], h1);

    /*
         when the matrix value is 4,4, multiply by 2 once (another one later)
     */
    t1 = saferAdd(blk[10], saferMulPower2(blk[9], 1));
    t1 = saferAdd(blk[7], t1);
    /*
         second multiplication by 2 (covers items that must be used twice and four times)
     */
    h1 = saferAdd(h1, saferMulPower2(t1, 1));

    /*
         second half of the matrix:
         the parts where the matrix is not x,x, but instead 2x,x
     */
    h2 = saferAdd(blk[15], blk[16]);
    h2 = saferAdd(blk[14], h2);

    /*
         first multiplication by 2 (two more to follow)
     */
    t1 = saferAdd(blk[4], saferMulPower2(blk[3], 1));

    /*
         second multiplication by 2 (one more to follow)
     */
    t1 = saferAdd(blk[13], saferMulPower2(t1, 1));
    t1 = saferAdd(blk[2], t1);
    t1 = saferAdd(blk[1], t1);

    /*
         third multiplication by 2
     */
    h2 = saferAdd(h2, saferMulPower2(t1, 1));

    aux[12] = saferAdd(h1, h2);
    aux[11] = saferAdd(aux[12], h2);

    /**********************
     * 
     * END      columns 11, 12
     * 
     **********************
     * 
     * START    columns 13, 14
     * first part of the matrix: all values are x,x
     * 
     **********************/
    h1 = saferAdd(blk[5], blk[6]);
    h1 = saferAdd(blk[4], h1);
    h1 = saferAdd(blk[2], h1);
    h1 = saferAdd(blk[1], h1);

    /*
         when the matrix value is 4,4, multiply by 2 once (another one later)
     */
    t1 = saferAdd(blk[8], saferMulPower2(blk[7], 1));
    t1 = saferAdd(blk[3], t1);
    /*
         second multiplication by 2 (covers items that must be used twice and four times)
     */
    h1 = saferAdd(h1, saferMulPower2(t1, 1));

    /*
         second half of the matrix:
         the parts where the matrix is not x,x, but instead 2x,x
     */
    h2 = saferAdd(blk[14], blk[16]);
    h2 = saferAdd(blk[13], h2);

    /*
         first multiplication by 2 (two more to follow)
     */
    t1 = saferAdd(blk[12], saferMulPower2(blk[11], 1));

    /*
         second multiplication by 2 (one more to follow)
     */
    t1 = saferAdd(blk[15], saferMulPower2(t1, 1));
    t1 = saferAdd(blk[10], t1);
    t1 = saferAdd(blk[9], t1);

    /*
         third multiplication by 2
     */
    h2 = saferAdd(h2, saferMulPower2(t1, 1));

    aux[14] = saferAdd(h1, h2);
    aux[13] = saferAdd(aux[14], h2);

    /**********************
     * 
     * END      columns 13, 14
     * 
     **********************
     * 
     * START    columns 15, 16
     * first part of the matrix: all values are x,x
     * 
     **********************/
    h1 = saferAdd(blk[7], blk[8]);
    h1 = saferAdd(blk[6], h1);
    h1 = saferAdd(blk[4], h1);
    h1 = saferAdd(blk[3], h1);

    /*
         when the matrix value is 4,4, multiply by 2 once (another one later)
     */
    t1 = saferAdd(blk[2], saferMulPower2(blk[1], 1));
    t1 = saferAdd(blk[5], t1);
    /*
         second multiplication by 2 (covers items that must be used twice and four times)
     */
    h1 = saferAdd(h1, saferMulPower2(t1, 1));

    /*
         second half of the matrix:
     */
    /*
         the parts where the matrix is not x,x, but instead 2x,x
     */
    h2 = saferAdd(blk[11], blk[12]);
    h2 = saferAdd(blk[10], h2);

    /*
         first multiplication by 2 (two more to follow)
     */
    t1 = saferAdd(blk[14], saferMulPower2(blk[13], 1));

    /*
         second multiplication by 2 (one more to follow)
     */
    t1 = saferAdd(blk[16], saferMulPower2(t1, 1));
    t1 = saferAdd(blk[15], t1);
    t1 = saferAdd(blk[9], t1);

    /*
         third multiplication by 2
     */
    h2 = saferAdd(h2, saferMulPower2(t1, 1));

    aux[16] = saferAdd(h1, h2);
    aux[15] = saferAdd(aux[16], h2);

    /**********************
     * 
     * END      columns 15, 16
     * 
     **********************/

    /*
         copy to final block
     */
    for (t1 = 16; t1 > 0; t1--) {
        blk[t1] = aux[t1];
    }
}
#endif

/**
 * Safer+ matriz multiplication. simple version. x = yM^-1
 */
#ifdef SAFERMATRIX_SIMPLE 
INLINE void saferMatrixYMul_1(block blk) {

    REG byte y;
    REG int i;
    REG int j;
    block aux;

    for (i = 1; i < 17; i++) {

        y = 0;

        for (j = 1; j < 17; j++) {
            y = saferAdd(y, saferMul(blk[j], matrixM2[j][i]));
        }

        aux[i] = y;
    }

    /* copy to final block */
    for (i = 1; i < 17; i++) {
        blk[i] = aux[i];
    }
}
#endif

/**
 * Safer+ matriz multiplication. optimised version. x = yM^-1, less operations
 * Follows the same principle of the y=Mx approach, but tweaked because of negative numbers
 * Instead of using the saferOps, the "normal (decimal)" operations are used, and in the end
 * the modulus is used
 */
#ifdef SAFERMATRIX_OPTIM 
INLINE void saferMatrixYMul_2(block blk) {

    REG int h1;
    REG int h2;
    REG int h3;
    REG int h4;
    REG int t1;
    REG int t2;

    block aux;

    /**********************
     * 
     * START   columns 1, 2 (0 contains zeros)
     * first part of the matrix: all values are x,x
     * 
     **********************/

    /*
             positive multipliers (x, -x)
     */
    h1 = (blk[1] << 1) + blk[5] + blk[9] + blk[15];
    /*
             negative multipliers (-x, x)
     */
    h2 = (blk[2] << 2) + blk[6] + blk[10]+(blk[16] << 1);

    /*
             positive multipliers (x, -2x)
     */
    h3 = blk[3]+(blk[7] << 1) + blk[11]+(blk[13] << 2);
    /*
             negative multipliers (-x, 2x)
     */
    h4 = (blk[4] << 1)+(blk[8] << 1) + blk[12]+(blk[14] << 3);

    /*
             add and subtract everything
     */
    t1 = saferAdd(h1, h3);
    t2 = saferAdd(h2, h4);
    aux[1] = saferSub(t1, t2);
    aux[2] = -h1 + h2 - (h3 << 1)+(h4 << 1);

    /**********************
     * 
     * END      columns 1, 2
     * 
     **********************
     * 
     * START    columns 3, 4
     * first part of the matrix: all values are x,x
     * 
     **********************/

    /*
             positive multipliers (x, -x)
     */
    h1 = blk[3] + blk[7] + blk[11]+(blk[13] << 1);
    /*
             negative multipliers (-x, x)
     */
    h2 = (blk[4] << 1) + blk[8] + blk[12]+(blk[14] << 2);

    /*
             positive multipliers (x, -2x)
     */
    h3 = blk[1]+(blk[5] << 1) + blk[9]+(blk[15] << 2);
    /*
             negative multipliers (-x, 2x)
     */
    h4 = (blk[2] << 1)+(blk[6] << 1) + blk[10]+(blk[16] << 3);

    /*
             add and subtract everything
     */
    t1 = saferAdd(h1, h3);
    t2 = saferAdd(h2, h4);
    aux[3] = saferSub(t1, t2);
    aux[4] = -h1 + h2 - (h3 << 1)+(h4 << 1);

    /**********************
     * 
     * END      columns 3, 4
     * 
     **********************
     * 
     * START    columns 5, 6
     * first part of the matrix: all values are x,x
     * 
     **********************/

    /*
             positive multipliers (x, -x)
     */
    h1 = blk[1] + blk[5] + blk[9]+(blk[15] << 1);
    /*
             negative multipliers (-x, x)
     */
    h2 = (blk[2] << 1) + blk[6] + blk[10]+(blk[16] << 2);

    /*
             positive multipliers (x, -2x)
     */
    h3 = (blk[3] << 1) + blk[7]+(blk[11] << 2) + blk[13];
    /*
             negative multipliers (-x, 2x)
     */
    h4 = (blk[4] << 1) + blk[8]+(blk[12] << 3)+(blk[14] << 1);

    /*
             add and subtract everything
     */
    t1 = saferAdd(h1, h3);
    t2 = saferAdd(h2, h4);
    aux[5] = saferSub(t1, t2);
    aux[6] = -h1 + h2 - (h3 << 1)+(h4 << 1);

    /**********************
     * 
     * END      columns 5, 6
     * 
     **********************
     * 
     * START    columns 7, 8
     * first part of the matrix: all values are x,x
     * 
     **********************/

    /*
             positive multipliers (x, -x)
     */
    h1 = blk[3] + blk[7]+(blk[11] << 1) + blk[13];
    /*
             negative multipliers (-x, x)
     */
    h2 = blk[4] + blk[8]+(blk[12] << 2)+(blk[14] << 1);

    /*
             positive multipliers (x, -2x)
     */
    h3 = (blk[1] << 2) + blk[5]+(blk[9] << 1) + blk[15];
    /*
             negative multipliers (-x, 2x)
     */
    h4 = (blk[2] << 3) + blk[6]+(blk[10] << 1)+(blk[16] << 1);

    /*
             add and subtract everything
     */
    t1 = saferAdd(h1, h3);
    t2 = saferAdd(h2, h4);
    aux[7] = saferSub(t1, t2);
    aux[8] = -h1 + h2 - (h3 << 1)+(h4 << 1);

    /**********************
     * 
     * END      columns 7, 8
     * 
     **********************
     * 
     * START    columns 9, 10
     * first part of the matrix: all values are x,x
     * 
     **********************/

    /*
             positive multipliers (x, -x)
     */
    h1 = blk[3]+(blk[7] << 1) + blk[11] + blk[15];
    /*
             negative multipliers (-x, x)
     */
    h2 = blk[4]+(blk[8] << 2)+(blk[12] << 1) + blk[16];

    /*
             positive multipliers (x, -2x)
     */
    h3 = (blk[1] << 1) + blk[5]+(blk[9] << 2) + blk[13];
    /*
             negative multipliers (-x, 2x)
     */
    h4 = (blk[2] << 1)+(blk[6] << 1)+(blk[10] << 3) + blk[14];

    /*
             add and subtract everything
     */
    t1 = saferAdd(h1, h3);
    t2 = saferAdd(h2, h4);
    aux[9] = saferSub(t1, t2);
    aux[10] = -h1 + h2 - (h3 << 1)+(h4 << 1);

    /**********************
     * 
     * END      columns 9, 10
     * 
     **********************
     * 
     * START    columns 11, 12
     * first part of the matrix: all values are x,x
     * 
     **********************/

    /*
             positive multipliers (x, -x)
     */
    h1 = blk[1] + blk[5]+(blk[9] << 1) + blk[13];
    /*
             negative multipliers (-x, x)
     */
    h2 = blk[2]+(blk[6] << 1)+(blk[10] << 2) + blk[14];

    /*
             positive multipliers (x, -2x)
     */
    h3 = blk[3]+(blk[7] << 2) + blk[11]+(blk[15] << 1);
    /*
             negative multipliers (-x, 2x)
     */
    h4 = blk[4]+(blk[8] << 3)+(blk[12] << 1)+(blk[16] << 1);

    /*
             add and subtract everything
     */
    t1 = saferAdd(h1, h3);
    t2 = saferAdd(h2, h4);
    aux[11] = saferSub(t1, t2);
    aux[12] = -h1 + h2 - (h3 << 1)+(h4 << 1);

    /**********************
     * 
     * END      columns 11, 12
     * 
     **********************
     * 
     * START    columns 13, 14
     * first part of the matrix: all values are x,x
     * 
     **********************/

    /*
             positive multipliers (x, -x)
     */
    h1 = (blk[3] << 1) + blk[7] + blk[11] + blk[15];
    /*
             negative multipliers (-x, x)
     */
    h2 = (blk[4] << 2)+(blk[8] << 1) + blk[12] + blk[16];

    /*
             positive multipliers (x, -2x)
     */
    h3 = blk[1]+(blk[5] << 2) + blk[9]+(blk[13] << 1);
    /*
             negative multipliers (-x, 2x)
     */
    h4 = blk[2]+(blk[6] << 3)+(blk[10] << 1)+(blk[14] << 1);

    /*
             add and subtract everything
     */
    t1 = saferAdd(h1, h3);
    t2 = saferAdd(h2, h4);
    aux[13] = saferSub(t1, t2);
    aux[14] = -h1 + h2 - (h3 << 1)+(h4 << 1);

    /**********************
     * 
     * END      columns 13, 14
     * 
     **********************
     * 
     * START    columns 15, 16
     * first part of the matrix: all values are x,x
     * 
     **********************/

    /*
             positive multipliers (x, -x)
     */
    h1 = blk[1]+(blk[5] << 1) + blk[9] + blk[13];
    /*
             negative multipliers (-x, x)
     */
    h2 = blk[2]+(blk[6] << 2)+(blk[10] << 1) + blk[14];

    /*
             positive multipliers (x, -2x)
     */
    h3 = (blk[3] << 2) + blk[7]+(blk[11] << 1) + blk[15];
    /*
             negative multipliers (-x, 2x)
     */
    h4 = (blk[4] << 3)+(blk[8] << 1)+(blk[12] << 1) + blk[16];

    /*
             add and subtract everything
     */
    t1 = saferAdd(h1, h3);
    t2 = saferAdd(h2, h4);
    aux[15] = saferSub(t1, t2);
    aux[16] = -h1 + h2 - (h3 << 1)+(h4 << 1);

    /**********************
     * 
     * END      columns 15, 16
     * 
     **********************/

    /*
         copy to final block
     */
    for (t1 = 16; t1 > 0; t1--) {
        blk[t1] = aux[t1];
    }
}
#endif
