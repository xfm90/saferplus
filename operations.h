/*
 * File:   operations.h
 * Author: lcosta, rmarques
 *
 *
 * Wrapper for modular or tabular operations and 
 * other optimization options using compiler macros
 *
 *
 * Created on September 21, 2008, 9:00 AM
 */

#ifndef _OPERATIONS_H
#define _OPERATIONS_H

#include "modular.h"
#include "tbl.h"


#ifdef  __cplusplus
extern "C" {
#endif


/* set/unset inline compiler directive */
#define INLINE __inline
/*#define INLINE */

/* set/unset register compiler directive */
#define REG register
/*#define REG */
    
/* Safer+ xor operation (just a define a name similar to the other operations) */
#define saferXor(n,m) n^m




/* Operations are organized as follows:    
 - operations _1 are based on arithmetic (or simple implementation for matrix op) 
        => smaller binary 
            => some operations (much more) slower than tables
 - operations _2 are based on pre-computed tables (or optimized code for the matrix op) 
        => much larger binary and memory footprint
            => some ops faster
 
 Required operations:
  add, sub, mul, exp, log, y=xM, x=My-1, (xor and bias table are defined in only one alternative and do not appear here)
 
  
*/
    
/*
 * Define here which of the tests you want to do:
 * 1) All _1 Operations
 * 2) Mostly _1 Operations except for log and exp that use _2
 * 3) Mostly _2 Operations except for matrix that use _1
 * 4) Best run btw 1-3:
 *      - Matrix: _2 ops
 *      - Add, Sub, Mul: _1 ops
 *      - Exp, Log: _2 ops
 */
    
/* Note that some "#defines" are used to avoid large binary when some ops are not used. check *.[hc] for details. */

/*
 * Define Measure Test Number HERE 
 */
#ifndef MEASURE_TEST_1
#ifndef MEASURE_TEST_2
#ifndef MEASURE_TEST_3
#ifndef MEASURE_TEST_4
#define MEASURE_TEST_4
#endif
#endif
#endif
#endif
/*
 * Measure Test #1
 */    
#ifdef MEASURE_TEST_1
/* All _1 Operations */
#define saferAdd(n,m) saferAdd_1(n,m)
#define saferSub(n,m) saferSub_1(n,m)
#define saferMul(n,m) saferMul_1(n,m)
#define saferExp(x) saferExp_1(x)
#define saferLog(x) saferLog_1(x)
#define SAFERMATRIX_SIMPLE
#define saferMatrixXMul(b) saferMatrixXMul_1(b)
#define saferMatrixYMul(b) saferMatrixYMul_1(b)
#endif
/*
 * Measure Test #2
 */
#ifdef MEASURE_TEST_2
/* Mostly _1 Operations except for log and exp that use _2 (table based ops) */
#define saferAdd(n,m) saferAdd_1(n,m)
#define saferSub(n,m) saferSub_1(n,m)
#define saferMul(n,m) saferMul_1(n,m)
#define SAFEREXP_TBL
#define saferExp(x) saferExp_2(x)
#define SAFERLOG_TBL
#define saferLog(x) saferLog_2(x)
#define SAFERMATRIX_SIMPLE
#define saferMatrixXMul(b) saferMatrixXMul_1(b)
#define saferMatrixYMul(b) saferMatrixYMul_1(b)    
#endif
/*
 * Measure Test #3
 */
#ifdef MEASURE_TEST_3
/* Mostly _2 Operations except for matrix that use _1 */
#define SAFERADD_TBL
#define saferAdd(n,m) saferAdd_2(n,m)
#define SAFERSUB_TBL
#define saferSub(n,m) saferSub_2(n,m)
#define SAFERMUL_TBL
#define saferMul(n,m) saferMul_2(n,m)
#define SAFEREXP_TBL
#define saferExp(x) saferExp_2(x)
#define SAFERLOG_TBL
#define saferLog(x) saferLog_2(x)
#define SAFERMATRIX_SIMPLE
#define saferMatrixXMul(b) saferMatrixXMul_1(b)
#define saferMatrixYMul(b) saferMatrixYMul_1(b)
#endif
/*
 * Measure Test #4
 */
#ifdef MEASURE_TEST_4
#define saferAdd(n,m) saferAdd_1(n,m)
#define saferSub(n,m) saferSub_1(n,m)
#define saferMul(n,m) saferMul_1(n,m)
#define SAFEREXP_TBL
#define saferExp(x) saferExp_2(x)
#define SAFERLOG_TBL
#define saferLog(x) saferLog_2(x)
#define SAFERMATRIX_OPTIM
#define saferMatrixXMul(b) saferMatrixXMul_2(b)
#define saferMatrixYMul(b) saferMatrixYMul_2(b)
#endif    
    
#ifdef  __cplusplus
}
#endif

#endif  /* _OPERATIONS_H */
