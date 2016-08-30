/*
 * File:   utils.h
 * Author: lcosta, rmarques
 *
 * Created on September 18, 2008, 8:05 PM
 */

#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h> 

#include "types.h"
#include "operations.h"

/* 
 * Get the elapsed time in microseconds. 
 * 
 * Usage: 
 * 1) declare two timeval structures    -  struct timeval begin, end; 
 * 2) To get the time at the beginning  -  getTime(begin); 
 * 3) To get the time at the end        -  getTime(end); 
 * 4) To print the results              -  printTime(stdout, "", begin, end);   
 */ 
#define getTime(BEGIN)                      gettimeofday(&(BEGIN), (struct timezone*) 0) 
#define elapTime(BEGIN, END)                (1e+6*((END).tv_sec - (BEGIN).tv_sec) + ((END).tv_usec - (BEGIN).tv_usec)) 
#define printTime(FILE, MESG, BEGIN, END)   fprintf(FILE, "Elapsed time(usec) %s :%.2f\n", MESG, elapTime(BEGIN, END)) 

#define ENCRYPT 1
#define DECRYPT 0
#define KEYSIZE 16

FILE * keyFile;         /* this file stores the key */
FILE * unencrytedFile;       /* this file stores the intput data */
FILE * encrytedFile;   /* this file stores the encrypted data */

int file_size;

key key_data;           /* user key, read from file */
block *data;            /* this buffer stores input data (plain data or encrypted text) */

int handleCommandLine(int, char **, unsigned char);
int loadKey();
int loadFile(FILE *);
int writeFile(FILE *, int);
void cleanUp(void);


void printBlock(block);
void printBlockHex(block);

#ifdef  __cplusplus
}
#endif

#endif  /* _UTILS_H */


