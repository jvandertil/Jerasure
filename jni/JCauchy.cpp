#include <stdlib.h>

#include "JCauchy.h"
#include "cauchy.h"
#include "javautility.h"

/*
* Class:     eu_vandertil_jerasure_jni_Cauchy
* Method:    cauchy_original_coding_matrix
* Signature: (III)[I
*/
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_Cauchy_cauchy_1original_1coding_1matrix
	(JNIEnv *env, jclass clazz, jint jk, jint jm, jint jw)
{
	int* matrix = cauchy_original_coding_matrix(jk, jm, jw);

	if(matrix == NULL) {
		throwOutOfMemoryError(env, "Could not allocate memory for matrix.");
		return NULL;
	}

	jintArray result = env->NewIntArray(jk*jm);
	if(result != NULL) {
		env->SetIntArrayRegion(result, 0, jk*jm, (jint*)matrix);
	}

	free(matrix);

	return result;
}

/*
* Class:     eu_vandertil_jerasure_jni_Cauchy
* Method:    cauchy_xy_coding_matrix
* Signature: (III[I[I)[I
*/
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_Cauchy_cauchy_1xy_1coding_1matrix
	(JNIEnv *env, jclass clazz, jint k, jint m, jint w, jintArray jx, jintArray jy)
{
	jint *x = env->GetIntArrayElements(jx, NULL);
	jint *y = env->GetIntArrayElements(jy, NULL);

	if(x == NULL || y == NULL) {
		throwOutOfMemoryError(env, "Error getting x or y from Java");
		return NULL;
	}

	int* matrix = cauchy_xy_coding_matrix(k,m,w, (int*)x, (int*)y);

	if(matrix == NULL) {
		throwOutOfMemoryError(env, "Could not allocate memory for matrix.");
		return NULL;
	}

	jintArray result = env->NewIntArray(k*m);
	if(result != NULL) {
		env->SetIntArrayRegion(result, 0, k*m, (jint*)matrix);
	}

	env->ReleaseIntArrayElements(jx, x, NULL);
	env->ReleaseIntArrayElements(jy, y, NULL);
	free(matrix);

	return result;
}

/*
* Class:     eu_vandertil_jerasure_jni_Cauchy
* Method:    cauchy_improve_coding_matrix
* Signature: (III[I)V
*/
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Cauchy_cauchy_1improve_1coding_1matrix
	(JNIEnv *env, jclass clazz, jint k, jint m, jint w, jintArray jmatrix)
{
	jint* matrix = env->GetIntArrayElements(jmatrix, NULL);

	if(matrix == NULL) {
		throwOutOfMemoryError(env, "Error getting matrix from Java");
		return;
	}

	cauchy_improve_coding_matrix(k, m, w, (int*)matrix);

	env->ReleaseIntArrayElements(jmatrix, matrix, NULL);
}

/*
* Class:     eu_vandertil_jerasure_jni_Cauchy
* Method:    cauchy_good_general_coding_matrix
* Signature: (III)[I
*/
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_Cauchy_cauchy_1good_1general_1coding_1matrix
	(JNIEnv *env, jclass clazz, jint jk, jint jm, jint jw)
{
	int* matrix = cauchy_good_general_coding_matrix(jk, jm, jw);

	if(matrix == NULL) {
		throwOutOfMemoryError(env, "Error allocating memory for matrix");
		return NULL;
	}

	jintArray result = env->NewIntArray(jk*jm);

	if(result != NULL) {
		env->SetIntArrayRegion(result, 0, jk*jm, (jint*)matrix);
	}

	free(matrix);
	return result;
}

/*
* Class:     eu_vandertil_jerasure_jni_Cauchy
* Method:    cauchy_n_ones
* Signature: (II)I
*/
JNIEXPORT jint JNICALL Java_eu_vandertil_jerasure_jni_Cauchy_cauchy_1n_1ones
	(JNIEnv *env, jclass clazz, jint jn, jint jw)
{
	return cauchy_n_ones(jn, jw);
}