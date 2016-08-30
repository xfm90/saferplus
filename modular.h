/*
 * File:   modular.h
 * Author: lcosta, rmarques
 *
 * Created on September 21, 2008, 9:00 AM
 */

#ifndef _MODULAR_H
#define _MODULAR_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "types.h"
#include "operations.h"

#ifdef SAFERMATRIX_SIMPLE
void saferMatrixXMul_1(block);
void saferMatrixYMul_1(block);
#endif
#ifdef SAFERMATRIX_OPTIM 
void saferMatrixXMul_2(block);
void saferMatrixYMul_2(block);
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* _MODULAR_H */
