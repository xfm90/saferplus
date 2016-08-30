/* 
 * File:   tbl.h
 * Author: lcosta, rmarques
 *
 * Created on September 20, 2008, 3:46 PM
 */

#ifndef _TBL_H
#define	_TBL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "types.h"
#include "operations.h"

/**
 * SAFER+ Tables
 */

/** Table with mod256 add operation given two bytes */
#ifdef SAFERADD_TBL
static byte saferAddTbl[256][256];
#endif

/** Table with mod256 sub operation given two bytes */
#ifdef SAFERSUB_TBL
static byte saferSubTbl[256][256];
#endif

/** Table with mod256 mul operation given two bytes */
#ifdef SAFERMUL_TBL
static byte saferMulTbl[256][256];
#endif

/** Table with SAFER+ exp operation */
#ifdef SAFEREXP_TBL
static byte saferExpTbl[256];
#endif

/** Table with SAFER+ discrete log operation */
#ifdef SAFERLOG_TBL
static byte saferLogTbl[256];
#endif

/** Table with SAFER+ Bias words */
static byte saferBiasTbl[18][17];

/**
 * SAFER+ Tables' creation
 */

#ifdef SAFERADD_TBL
byte saferAdd_2(byte, byte); 
#endif
#ifdef SAFERSUB_TBL
byte saferSub_2(byte, byte);
#endif
#ifdef SAFERMUL_TBL
byte saferMul_2(byte, byte);
#endif
#ifdef SAFEREXP_TBL
byte saferExp_2(byte);
#endif
#ifdef SAFERLOG_TBL
byte saferLog_2(byte);
#endif

byte saferBias(byte, byte);

void init_tables();


#ifdef	__cplusplus
}
#endif

#endif	/* _TBL_H */

