#include "utils.h"
#include "types.h"
#include "operations.h"

/** Global var holding all round keys for current execution */
key keys[18]; /* keys 1..17 */

int main(int argc, char **argv) {

    REG int i;
    REG int n_blocks;
    struct timeval begin, end;
    
#ifdef SAFERENC
    if (handleCommandLine(argc, argv, ENCRYPT) != 0) {
#endif
#ifdef SAFERDEC
    if (handleCommandLine(argc, argv, DECRYPT) != 0) {
#endif
        cleanUp();
        exit(-1);
    }

    if (loadKey() < 0) {
        fprintf(stderr, "An error occurred while loading the key file into memory.\n");
        cleanUp();
        exit(-1);
    }
    
#ifdef SAFERENC
    n_blocks=loadFile(unencrytedFile);
#endif
#ifdef SAFERDEC
    n_blocks=loadFile(encrytedFile);
#endif
    if (n_blocks < 0) {
        fprintf(stderr, "An error occurred while loading the file into memory.\n");
        cleanUp();
        exit(-1);
    }

    init_tables();

    getTime(begin);

    keySchedule(key_data, keys);

    for (i=0; i<n_blocks; i++) {
#ifdef SAFERENC
        saferEncryptBlock(data[i]);
#endif
#ifdef SAFERDEC
        saferDecryptBlock(data[i]);
#endif
    }

    getTime(end);
    printTime(stdout, "", begin, end);


#ifdef SAFERENC
    if (writeFile(encrytedFile, n_blocks) < 0) {
#endif
#ifdef SAFERDEC
    if (writeFile(unencrytedFile, n_blocks) < 0) {
#endif
        fprintf(stderr, "An error occurred while writing the output file.\n");
        cleanUp();
        exit(-1);
    }


    cleanUp();
    return 0;
}
