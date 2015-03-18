#include<stdio.h>
#include <string>

#include "des/des.h"
#include "base64/base64.h"
#include "zlib/zlib.h"
#include "Crypt.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

void z(char *src, int slen, char **dst, int *dlen)
{
	uLongf mSize;
	char *buf = new char[slen * 10];
	compress((Bytef*)buf, &mSize, (Bytef*)src, slen);
	
	*dst = new char[mSize+1];
	memset(*dst, 0, mSize+1);
	memcpy((char*)*dst, (char*)buf, mSize);
	*dlen = mSize;

	free(buf);
}

void uz(char *src, int slen, char **dst, int *dlen)
{
	uLongf mSize;
	char *buf = new char[slen * 10];
	uncompress((Bytef*)buf, &mSize, (Bytef*)src, slen);

	*dst = new char[mSize+1];
	memset(*dst, 0, mSize+1);
	memcpy((char*)*dst, (char*)buf, mSize);
	*dlen = mSize;

	free(buf);
}

// base64 encode
string b(char *src, int slen)
{
	return base64_encode((const unsigned char*)src, slen);
}

// base64 decode
void ub(char *buf, char **dst, int *dlen)
{
	string base64Enc(buf);
	std::vector<char> buffer = base64_decode(base64Enc);
	string base64Dec(buffer.begin(), buffer.end());
	*dst = new char[base64Dec.length()];
	memset(*dst, 0, base64Dec.length());
	memcpy(*dst, base64Dec.c_str(), base64Dec.length());
	*dlen = base64Dec.length();
}

// des encode
void e(char *key, char *src, char **dst, int *dlen)
{
	*dlen = E(src, dst, key);
}

// des decode
void d(char *key, char *src, int slen, char **dst)
{
	D(src, slen, dst, key);
}

char* getKey(char *key)
{
	if (key == NULL || strlen(key) == 0)
	{
		key = (char*)"12345678";
	}

	return key;
}

// DES(encode) -> BASE64(encode) -> ZIP(encode)
void dbz(char *key, char *srcBuffer, char **dstBuffer, int *dlen)
{
	char *buffer = NULL;
	int iSize = 0;

	key = getKey(key);
	e(key, srcBuffer, &buffer, &iSize);
	string base64 = b(buffer, iSize);
	free(buffer);

	z((char*)base64.c_str(), strlen(base64.c_str()), dstBuffer, dlen);
}

// DES(encode) -> BASE64(encode)
void db(char *key, char *srcBuffer, char **dstBuffer)
{
	char *buffer = NULL;
	int iSize = 0;

	key = getKey(key);
	e(key, srcBuffer, &buffer, &iSize);
	string base64 = b(buffer, iSize);
	free(buffer);

	*dstBuffer = new char[base64.length() + 1];
	memset(*dstBuffer, 0, base64.length() + 1);
	memcpy((char*)*dstBuffer, (char*)base64.c_str(), base64.length());
}

// ZIP(decode) -> BASE64(decode) -> DES(decode)
void uuu(char *key, char *srcBuffer, int slen, char **dstBuffer)
{
	char *zbuf = NULL;
	char *buffer = NULL;
	int iSize = 0;

	key = getKey(key);

	uz(srcBuffer, slen, &zbuf, &iSize);
	ub(zbuf, &buffer, &iSize);
	d(key, buffer, iSize, dstBuffer);
	free(zbuf);
	free(buffer);
}

// BASE64(decode) -> DES(decode)
void uu(char *key, char *srcBuffer, char **dstBuffer)
{
	char *buffer = NULL;
	int iSize = 0;

	key = getKey(key);
	ub(srcBuffer, &buffer, &iSize);
	d(key, buffer, iSize, dstBuffer);
	free(buffer);
}

#ifdef __cplusplus  
}  
#endif