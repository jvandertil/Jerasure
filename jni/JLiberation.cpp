#include <stdlib.h>
#include "JLiberation.h"
#include "javautility.h"
#include "liberation.h"

/*
 * Class:     eu_vandertil_jerasure_jni_Liberation
 * Method:    liberation_coding_bitmatrix
 * Signature: (II)[I
 */
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_Liberation_liberation_1coding_1bitmatrix
  (JNIEnv *env, jclass clazz, jint k, jint w)
{
	int* matrix = liberation_coding_bitmatrix(k,w);
	return NULL;
}

/*
 * Class:     eu_vandertil_jerasure_jni_Liberation
 * Method:    liber8tion_coding_bitmatrix
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_Liberation_liber8tion_1coding_1bitmatrix
  (JNIEnv *env, jclass clazz, jint);

/*
 * Class:     eu_vandertil_jerasure_jni_Liberation
 * Method:    blaum_roth_coding_bitmatrix
 * Signature: (II)[I
 */
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_Liberation_blaum_1roth_1coding_1bitmatrix
  (JNIEnv *env, jclass clazz, jint, jint);