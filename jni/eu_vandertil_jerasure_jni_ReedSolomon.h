/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class eu_vandertil_jerasure_jni_ReedSolomon */

#ifndef _Included_eu_vandertil_jerasure_jni_ReedSolomon
#define _Included_eu_vandertil_jerasure_jni_ReedSolomon
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     eu_vandertil_jerasure_jni_ReedSolomon
 * Method:    getVandermondeCodingMatrix
 * Signature: (III)[I
 */
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_getVandermondeCodingMatrix
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     eu_vandertil_jerasure_jni_ReedSolomon
 * Method:    getExtendedVandermondeMatrix
 * Signature: (III)[I
 */
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_getExtendedVandermondeMatrix
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     eu_vandertil_jerasure_jni_ReedSolomon
 * Method:    getBigVandermondeDistributionMatrix
 * Signature: (III)[I
 */
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_getBigVandermondeDistributionMatrix
  (JNIEnv *, jclass, jint, jint, jint);

#ifdef __cplusplus
}
#endif
#endif