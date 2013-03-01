#include <stdlib.h>

#include "JReedSolomon.h"
#include "javautility.h"
#include "reed_sol.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

/*
* Class:     eu_vandertil_jerasure_jni_ReedSolomon
* Method:    reed_sol_vandermonde_coding_matrix
* Signature: (III)[I
*/
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_reed_1sol_1vandermonde_1coding_1matrix
	(JNIEnv *env, jclass clazz, jint k, jint m, jint w)
{
	int* matrix = reed_sol_vandermonde_coding_matrix(k, m, w);

	if(matrix == NULL) {
		throwOutOfMemoryError(env, "Error allocating memory for matrix");
		return NULL;
	}

	jintArray result = env->NewIntArray(m*k);
	if(result != NULL) {
		env->SetIntArrayRegion(result, 0, m*k, (jint*)matrix);
	}

	free(matrix);
	return result;
}

/*
* Class:     eu_vandertil_jerasure_jni_ReedSolomon
* Method:    reed_sol_extended_vandermonde_matrix
* Signature: (III)[I
*/
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_reed_1sol_1extended_1vandermonde_1matrix
	(JNIEnv *env, jclass clazz, jint rows, jint cols, jint w)
{
	int* matrix = reed_sol_extended_vandermonde_matrix(rows, cols, w);

	if(matrix == NULL) {
		throwOutOfMemoryError(env, "Error allocating memory for matrix");
		return NULL;
	}

	jintArray result = env->NewIntArray(rows*cols);
	if(result != NULL) {
		env->SetIntArrayRegion(result, 0, rows*cols, (jint*)matrix);
	}

	free(matrix);
	return result;
}

/*
* Class:     eu_vandertil_jerasure_jni_ReedSolomon
* Method:    reed_sol_big_vandermonde_distribution_matrix
* Signature: (III)[I
*/
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_reed_1sol_1big_1vandermonde_1distribution_1matrix
	(JNIEnv *env, jclass clazz, jint rows, jint cols, jint w)
{
	int* matrix = reed_sol_big_vandermonde_distribution_matrix(rows, cols, w);

	if(matrix == NULL) {
		throwOutOfMemoryError(env, "Error allocating memory for matrix");
		return NULL;
	}

	jintArray result = env->NewIntArray(rows*cols);
	if(result != NULL) {
		env->SetIntArrayRegion(result, 0, rows*cols, (jint*)matrix);
	}

	free(matrix);
	return result;
}

/*
* Class:     eu_vandertil_jerasure_jni_ReedSolomon
* Method:    reed_sol_r6_encode
* Signature: (II[[B[[BI)I
*/
JNIEXPORT jboolean JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_reed_1sol_1r6_1encode
	(JNIEnv *env, jclass clazz, jint k, jint w, jobjectArray jdata_ptrs, jobjectArray jcoding_ptrs, jint size)
{
	int i;
	jobject* dataPtrs = talloc(jobject, k);
	jbyte** data_ptrs = talloc(jbyte*, k);
	if(data_ptrs == NULL || dataPtrs == NULL) {
		free(dataPtrs);
		free(data_ptrs);

		throwOutOfMemoryError(env, "");
		return NULL;
	}

	for(i = 0; i < k; ++i) {
		dataPtrs[i] = env->GetObjectArrayElement(jdata_ptrs, i);
		data_ptrs[i] = env->GetByteArrayElements((jbyteArray)dataPtrs[i], NULL);

		if(data_ptrs[i] == NULL) {
			// Free already retrieved memory
			for(int j = 0; j < i; ++j) {
				env->ReleaseByteArrayElements((jbyteArray)dataPtrs[j], data_ptrs[j], NULL);
			}

			free(data_ptrs);
			free(dataPtrs);

			throwOutOfMemoryError(env, "Error getting data_ptrs from Java");
			return NULL;
		}
	}

	jobject* codingPtrs = talloc(jobject, 2);
	jbyte** coding_ptrs = talloc(jbyte*, 2);
	if(codingPtrs == NULL || coding_ptrs == NULL) {
		for(i = 0; i < k; ++i) {
			env->ReleaseByteArrayElements((jbyteArray)dataPtrs[i], data_ptrs[i], NULL);
		}

		free(data_ptrs);
		free(dataPtrs);

		throwOutOfMemoryError(env, "");
		return NULL;
	}

	for(i = 0; i < 2; ++i)
	{
		codingPtrs[i] = env->GetObjectArrayElement(jcoding_ptrs, i);
		coding_ptrs[i] = env->GetByteArrayElements((jbyteArray)codingPtrs[i], NULL);
		if(coding_ptrs[i] == NULL) {
			int j;
			for(j = 0; j < i; ++j) {
				env->ReleaseByteArrayElements((jbyteArray)codingPtrs[j], coding_ptrs[j], NULL);
			}
			free(coding_ptrs);
			free(codingPtrs);

			for(j = 0; j < k; ++j) {
				env->ReleaseByteArrayElements((jbyteArray)dataPtrs[i], data_ptrs[j], NULL);
			}
			free(data_ptrs);
			free(dataPtrs);
			
			throwOutOfMemoryError(env, "Error getting data_ptrs from Java");
			return NULL;
		}
	}

	int result = reed_sol_r6_encode(k,w, (char**)data_ptrs, (char**)coding_ptrs,size);

	for(i = 0; i < 2; ++i) {
		env->ReleaseByteArrayElements((jbyteArray)codingPtrs[i], coding_ptrs[i], NULL);
	}
	free(coding_ptrs);
		free(codingPtrs);

	for(i = 0; i < k; ++i) {
		env->ReleaseByteArrayElements((jbyteArray)dataPtrs[i], data_ptrs[i], NULL);
	}
	free(data_ptrs);
	free(dataPtrs);

	if(result == 1)
		return JNI_TRUE;

	return JNI_FALSE;
}

/*
* Class:     eu_vandertil_jerasure_jni_ReedSolomon
* Method:    reed_sol_r6_coding_matrix
* Signature: (II)[I
*/
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_reed_1sol_1r6_1coding_1matrix
	(JNIEnv *env, jclass clazz, jint k, jint w)
{
	int* matrix = reed_sol_r6_coding_matrix(k, w);

	if(matrix == NULL) {
		throwOutOfMemoryError(env, "Error allocating memory for matrix");
		return NULL;
	}

	jintArray result = env->NewIntArray(2*k);
	if(result != NULL) {
		env->SetIntArrayRegion(result, 0, 2*k, (jint*)matrix);
	}

	free(matrix);
	return result;
}

/*
* Class:     eu_vandertil_jerasure_jni_ReedSolomon
* Method:    reed_sol_galois_w08_region_multby_2
* Signature: ([BI)V
*/
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_reed_1sol_1galois_1w08_1region_1multby_12
	(JNIEnv *env, jclass clazz, jbyteArray jregion, jint nbytes)
{
	jbyte* region = env->GetByteArrayElements(jregion, NULL);
	if(region == NULL) {
		throwOutOfMemoryError(env, "Error retrieving region from Java");
		return;
	}

	reed_sol_galois_w08_region_multby_2((char*)region, nbytes);

	env->ReleaseByteArrayElements(jregion, region, NULL);
}

/*
* Class:     eu_vandertil_jerasure_jni_ReedSolomon
* Method:    reed_sol_galois_w16_region_multby_2
* Signature: ([BI)V
*/
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_reed_1sol_1galois_1w16_1region_1multby_12
	(JNIEnv *env, jclass clazz, jbyteArray jregion, jint nbytes)
{
	jbyte* region = env->GetByteArrayElements(jregion, NULL);
	if(region == NULL) {
		throwOutOfMemoryError(env, "Error retrieving region from Java");
		return;
	}

	reed_sol_galois_w16_region_multby_2((char*)region, nbytes);

	env->ReleaseByteArrayElements(jregion, region, NULL);
}
/*
* Class:     eu_vandertil_jerasure_jni_ReedSolomon
* Method:    reed_sol_galois_w32_region_multby_2
* Signature: ([BI)V
*/
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_reed_1sol_1galois_1w32_1region_1multby_12
	(JNIEnv *env, jclass clazz, jbyteArray jregion, jint nbytes)
{
		jbyte* region = env->GetByteArrayElements(jregion, NULL);
	if(region == NULL) {
		throwOutOfMemoryError(env, "Error retrieving region from Java");
		return;
	}

	reed_sol_galois_w32_region_multby_2((char*)region, nbytes);

	env->ReleaseByteArrayElements(jregion, region, NULL);
}
