/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class eu_vandertil_jerasure_jni_Encoding */

#ifndef _Included_eu_vandertil_jerasure_jni_Encoding
#define _Included_eu_vandertil_jerasure_jni_Encoding
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     eu_vandertil_jerasure_jni_Encoding
 * Method:    getParity
 * Signature: (I[[B[BI)V
 */
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_getParity
  (JNIEnv *, jclass, jint, jobjectArray, jbyteArray, jint);

/*
 * Class:     eu_vandertil_jerasure_jni_Encoding
 * Method:    encodeWithMatrix
 * Signature: (III[I[[B[[BI)V
 */
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_encodeWithMatrix
  (JNIEnv *, jclass, jint, jint, jint, jintArray, jobjectArray, jobjectArray, jint);

/*
 * Class:     eu_vandertil_jerasure_jni_Encoding
 * Method:    encodeWithBitMatrix
 * Signature: (III[I[[B[[BII)V
 */
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_encodeWithBitMatrix
  (JNIEnv *, jclass, jint, jint, jint, jintArray, jobjectArray, jobjectArray, jint, jint);

/*
 * Class:     eu_vandertil_jerasure_jni_Encoding
 * Method:    encodeWithSchedule
 * Signature: (III[[I[[B[[BII)V
 */
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_encodeWithSchedule
  (JNIEnv *, jclass, jint, jint, jint, jobjectArray, jobjectArray, jobjectArray, jint, jint);

#ifdef __cplusplus
}
#endif
#endif