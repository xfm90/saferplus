/* 
 * File:   safer.h
 * Author: lcosta, rmarques
 *
 * Created on September 18, 2008, 8:05 PM
 */

#ifndef _SAFER_H
#define	_SAFER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "operations.h"
#include "types.h"

/** Global var holding all round keys for current execution */
extern key keys[18]; /* keys 1..17 */

/** Left rotate 3 bits of a byte */
INLINE byte saferLS3(register byte b); 

/** rotate bytes of a round key */
INLINE void saferRotateBytes(byte *from, byte *to); 

/** copy from a key array to another */
INLINE void saferKeyCopy(key from, key to); 

INLINE void keySchedule(key k, key *keys); 


INLINE void saferEncryptBlock(block); 
INLINE void saferDecryptBlock(block); 


#ifdef	__cplusplus
}
#endif

#endif	/* _SAFER_H */
