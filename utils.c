#include "utils.h"

/***
 * Validates the command line and associates the files to the global vars.
 * Opens and checks if it is possible to read from the input files and write to the output file.
 *
 * argc, argv - the parameters as captured by main
 * encryptOrDecrypt = 1 for encrypt, 0 for decrypt
 * 
 * returns 0 on success, 1 on error
 ***/

int handleCommandLine(int argc, char **argv, unsigned char encryptOrDecrypt) {

    char *strEnc = "saferenc";
    char *strDec = "saferdec";
    char *strPlain = "data";
    char *strEncrypted = "encrypted";
    unsigned short int ret = 0;
    FILE * fTemp;

    if (argc != 4) {
        fprintf(stderr, "Syntax error!\nUsage: %s <inputkey.file> <%s_data.file> <%s_output.file>\n\n",
                (encryptOrDecrypt ? strEnc : strDec),
                (encryptOrDecrypt ? strPlain : strEncrypted),
                (encryptOrDecrypt ? strEncrypted : strPlain));

        fprintf(stderr, "\tinputkey.file \t\t- Input file with 128-bit key.\n");

        fprintf(stderr, "\t%s_data.file \t- Input file of arbitrary size with %sencrypted data.\n",
                (encryptOrDecrypt ? strPlain : strEncrypted),
                (encryptOrDecrypt ? "un" : ""));

        fprintf(stderr, "\t%s_output.file \t- Output file with %sencrypted data.\n\n",
                (encryptOrDecrypt ? strEncrypted : strPlain),
                (encryptOrDecrypt ? "" : "un"));

        ret = 1;

    } else {

        /* verify if the key file exists and can be read */
        if ((fTemp = fopen(argv[1], "rb")) == NULL) {
            fprintf(stderr, "Error reading %s file! %s\n", argv[1], strerror(errno));
            ret = 1;

        } else {
            /* the key file is ok */
            keyFile = fTemp;

            /* verify if the data file exists and can be read */
            if ((fTemp = fopen(argv[2], "rb")) == NULL) {
                fprintf(stderr, "Error reading %s file! %s\n", argv[2], strerror(errno));
                ret = 1;
            } else {

                /* data file is ok
                 * 
                 * for encryptions, the second parameter is the plain data
                 * for decryptions, the second parameter is the encrypted text */
                if (encryptOrDecrypt) {
                    unencrytedFile = fTemp;
                } else {
                    encrytedFile = fTemp;
                }

                /* verify if the output file exists and can be written */
                if ((fTemp = fopen(argv[3], "w+b")) == NULL) {
                    fprintf(stderr, "Error opening %s file for writing! %s\n", argv[3], strerror(errno));
                    ret = 1;
                } else {

                    /* output file is ok
                     * 
                     * for encryptions, the third parameter is the encrypted text
                     * for decryptions, the third parameter is the plain data */
                    if (encryptOrDecrypt) {
                        encrytedFile = fTemp;
                    } else {
                        unencrytedFile = fTemp;
                    }
                }
            }
        }
    }

    return ret;
}

/** 
 * Reads a file into memory
 * Returns the number of read bytes
 * Returns -1 if file has unexpected size
 **/
int loadKey() {

    int r_size = 0, i;

    /* read 16-byte key into memory */
    for (i = 1; i < KEYSIZE + 1; i++) {
        r_size += fread(&key_data[i], 1, 1, keyFile);
    }

    if (r_size != KEYSIZE) {
        fprintf(stderr, "Error reading key file!\n");
        return -1;
    }

    return KEYSIZE;
}

/** 
 * Reads a file into memory
 * Returns the number of read blocks
 * Returns -1 if malloc fails
 * Returns -2 if it cannot read the whole file
 **/
int loadFile(FILE * file) {

    int r_size = 0, n_blocks, i, m;

    /* Count number of bytes to know how many to alloc */
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);

    /*
        printf("file size: %i\n", f_size);
     */

    n_blocks = file_size / 16;

    if (file_size % 16 > 0)
        n_blocks++; /* round up */

    /*
        printf("n blocks: %i\n", n_blocks);
     */

    /* reset file position */
    fseek(file, 0, SEEK_SET);

    if ((data = (block*) malloc(sizeof (block) * n_blocks)) == NULL) {
        fprintf(stderr, "Error allocating memory!\n");
        return -1;
    }

/*
     read a block at a time
*/
    for (i = 0; i < file_size / 16; i++) {
        r_size += fread(&data[i][1], 16, 1, file); /* we do not use array position 0 so we give the address to position 1 */
    }
    /*
        printf("read input: %i\n", r_size);
     */

/*
     read missing bytes to complete multiple of 16 block
*/
    int k = 0;
    if (file_size % 16 > 0) {
        m = file_size % 16; /* read 16 - fsize mod 16 bytes */
        k = fread(&data[n_blocks - 1][1], m, 1, file);

/*
         clean unused bytes
*/
        int h = 0;
        for (i = m; i < 16; i++) {
            data[n_blocks - 1][i] = 0x0;
            h++;
        }
    }

    return n_blocks;
}

/* Writes the contents of a buffer to disk
 * Returns -1 if writing fails
 */
int writeFile(FILE * file, int n_blocks) {
    int i, w_size = 0;
    int total = 0;

    for (i = 0; i < n_blocks; i++) {
        w_size = fwrite(&data[i][1], 16, 1, file); /* we do not use array position 0 => give the address of byte pos 1 to fwrite */
        total += w_size;
    }

    if (total != n_blocks) {
        fprintf(stderr, "Error writing file!\n");
        return -1;
    }

    return w_size;
}

/**
 * Frees allocated memory 
 * Closes all open files
 **/
void cleanUp() {

    free(data);

    /* If there is an error while politely closing any file, we mask the error,
     * because the program is terminating and file descriptors are released
     * anyway */

    fclose(keyFile);
    fclose(unencrytedFile);
    fclose(encrytedFile);
}

void printBlock(block blk) {
    REG int i;

    for (i = 1; i < 17; i++) {
        printf("%i ", blk[i]);
    }

    printf("\n");
}

void printBlockHex(block blk) {
    REG int i;

    for (i = 1; i < 17; i++) {
        printf("%x ", blk[i]);
    }

    printf("\n");
}
