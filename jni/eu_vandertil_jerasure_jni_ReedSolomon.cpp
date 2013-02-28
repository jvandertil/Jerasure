#include "eu_vandertil_jerasure_jni_ReedSolomon.h"
#include "reed_sol.h"

jintArray tojintArray(JNIEnv *env, int* contents, int length)
{
	jintArray result = env->NewIntArray(length);
	env->SetIntArrayRegion(result, 0, length, (jint*)contents);
	return result;
}

/*
 * Class:     eu_vandertil_jerasure_jni_ReedSolomon
 * Method:    getVandermondeCodingMatrix
 * Signature: (III)[I
 */
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_getVandermondeCodingMatrix
  (JNIEnv *env, jclass clazz, jint dataDevices, jint codingDevices, jint wordSize)
{
	int* matrix = reed_sol_vandermonde_coding_matrix(dataDevices, codingDevices, wordSize);

	return tojintArray(env, matrix, (codingDevices * dataDevices));
}

/*
 * Class:     eu_vandertil_jerasure_jni_ReedSolomon
 * Method:    getExtendedVandermondeMatrix
 * Signature: (III)[I
 */
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_getExtendedVandermondeMatrix
	(JNIEnv *env, jclass clazz, jint rows, jint cols, jint wordSize)
{
	int* matrix = reed_sol_extended_vandermonde_matrix(rows, cols, wordSize);

	return tojintArray(env, matrix, (rows * cols)); 
}

/*
 * Class:     eu_vandertil_jerasure_jni_ReedSolomon
 * Method:    getBigVandermondeDistributionMatrix
 * Signature: (III)[I
 */
JNIEXPORT jintArray JNICALL Java_eu_vandertil_jerasure_jni_ReedSolomon_getBigVandermondeDistributionMatrix
  (JNIEnv *env, jclass clazz, jint rows, jint cols, jint wordSize)
{
	int* matrix = reed_sol_big_vandermonde_distribution_matrix(rows, cols, wordSize);

	return tojintArray(env, matrix, (rows * cols)); 
}