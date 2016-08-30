/*
 * File:   types.h
 * Author: lcosta, rmarques
 *
 * Created on September 23, 2008, 2:46 AM
 */

#ifndef _TYPES_H
#define _TYPES_H

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * SAFER+ types
 */
/** round byte */
typedef unsigned char byte;

/** bias bytes for key schedule (1..16 for simplicity) */
typedef byte bias[17];

/** round block with 16 bytes (1..16 for simplicity) */
typedef byte block[17];

/** keys */
typedef byte key[18];

#ifdef  __cplusplus
}
#endif

#endif  /* _TYPES_H */
