#ifndef DES_H
#define DES_H

int E(char* sBuf, char** eBuf, char key[]);
void D(char* sBuf, int size, char** dBuf, char key[]);

#endif