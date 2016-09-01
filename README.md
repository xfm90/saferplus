# Safer+ speed test implementation


## Context
SAFER+ was submitted in 1998 as a candidate for the Advanced Encryption Standard (AES) and is used for message authentication codes in Bluetooth. It is based on the original 64-bit block cipher SAFER (published in 1993), using a similar round construction that consists of pseudo-Hadamard transforms, substitution tables, and subkey insertion. However, some important improvements were made to SAFER+, such as the introduction of the “Armenian Shuffle” permutation, which boosts the diffusion of single-bit modifications in the input data.

## Implementation
SAFER+ has two subsystems: the key scheduling subsystem and the encryption subsystem. SAFER+ is a 16-byte block cipher algorithm. Therefore, the input for encryption is a 16-byte of plaintext, which is subject to several mathematical operations, permutations, and non-linear transformations through a series of rounds of encryption. The number of rounds depends on the length of the input key. We only use 128-bit input keys, which according to the standard specification require a total of 8 rounds and 17 subkeys (two subkeys for each round, plus one last subkey added to the output of the final round) generated from the 128-bit input key by the key scheduling subsystem. 

## Usage

saferenc <inputkey.file> <plain_data.file> <encrypted_output.file> 
- inputkey.file : Input file with 128-bit key.
- plain_data.file : Input file of arbitrary size with unencrypted data. 
- encrypted_output.file : Output file with encrypted data.

saferdec <inputkey.file> <encrypted_data.file> <plain_output.file>
- inputkey.file : Input file with 128-bit key.
- encrypted_data.file : Input file of arbitrary size with encrypted data. 
- plain_output.file : Output file with unencrypted data.


