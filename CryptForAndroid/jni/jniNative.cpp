#include <jni.h>  
#include "stdio.h"
#include "stdlib.h"
#include "com_chris_crypt_utils_Native.h"
#include "Crypt.h"
#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif

char* Jstring_To_Chars(JNIEnv *env, jstring js)
{
	if(js == NULL)
	{
		return NULL;
	}
	return (char*)env->GetStringUTFChars(js, 0);
}

jstring Chars_To_Jstring(JNIEnv *env, char *buf)
{
	jclass strClass = (env)->FindClass("java/lang/String"); 
	jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = (env)->NewByteArray(strlen(buf));
	(env)->SetByteArrayRegion(bytes, 0, strlen(buf), (jbyte*)buf);
	jstring encoding = env->NewStringUTF("utf-8"); 
	return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

jbyteArray Chars_To_JbyteArray(JNIEnv *env, char *buf, jint len)
{
	jint size = (len == -1 ? strlen(buf) : len);
	jbyteArray bytes = (env)->NewByteArray(size);
	(env)->SetByteArrayRegion(bytes, 0, size, (jbyte*)buf);
	return bytes;
}

JNIEXPORT jbyteArray JNICALL Java_com_chris_crypt_utils_Native_dbz
  (JNIEnv *env, jclass obj_class, jstring key, jstring srcBuffer)
{
	char *buffer = NULL;
	jint dlen = 0;
	dbz(Jstring_To_Chars(env, key), Jstring_To_Chars(env, srcBuffer), &buffer, &dlen);
	return Chars_To_JbyteArray(env, buffer, dlen);
}

JNIEXPORT jstring JNICALL Java_com_chris_crypt_utils_Native_db
  (JNIEnv *env, jclass obj_class, jstring key, jstring srcBuffer)
{
	char *dbuf = NULL;
	db(Jstring_To_Chars(env, key), Jstring_To_Chars(env, srcBuffer), &dbuf);
	return Chars_To_Jstring(env, dbuf);
}
  
JNIEXPORT jstring JNICALL Java_com_chris_crypt_utils_Native_uuu
  (JNIEnv *env, jclass obj_class, jstring key, jbyteArray srcBuffer)
{
	char *dbuf = NULL;
	jint len = env->GetArrayLength(srcBuffer)*2;  //jbyte = 2 * char
	char *buffer = (char*)env->GetByteArrayElements(srcBuffer, 0);
	uuu(Jstring_To_Chars(env, key), buffer, len, &dbuf);	
	return Chars_To_Jstring(env, dbuf);
}
  
JNIEXPORT jstring JNICALL Java_com_chris_crypt_utils_Native_uu
  (JNIEnv *env, jclass obj_class, jstring key, jstring srcBuffer)
{
	char *dbuf = NULL;
	uu(Jstring_To_Chars(env, key), Jstring_To_Chars(env, srcBuffer), &dbuf);
	return Chars_To_Jstring(env, dbuf);
}

#ifdef __cplusplus  
}  
#endif