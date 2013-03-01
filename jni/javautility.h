#ifndef _JAVAUTILITY_H
#define _JAVAUTILITY_H

#include <jni.h>

jint throwNoClassDefError(JNIEnv *env, char *message);
jint throwOutOfMemoryError(JNIEnv *env, char *message);
jint throwIllegalArgumentException(JNIEnv *env, char* message);

/*
* arrayOfArrays and resultData do not have to be initialized.
*/
bool getArrayOfByteArrays(JNIEnv *env, jobjectArray* arrays, jbyteArray* arrayOfArrays, jbyte** resultData, int numArrays);
void freeArrayOfByteArrays(JNIEnv *env, jbyteArray* arrayOfArrays, jbyte** resultData, int numArrays);
#endif