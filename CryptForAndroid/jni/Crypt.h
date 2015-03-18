#ifndef CRYPT_H
#define CRYPT_H

#ifdef __cplusplus
extern "C" {
#endif

void dbz(char *key, char *srcBuffer, char **dstBuffer, int *dlen);
void db(char *key, char *srcBuffer, char **dstBuffer);
void uuu(char *key, char *srcBuffer, int slen, char **dstBuffer);
void uu(char *key, char *srcBuffer, char **dstBuffer);

#ifdef __cplusplus  
}  
#endif

#endif