#include "eu_vandertil_jerasure_jni_Encoding.h"
#include "jerasure.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

/*
 * Class:     eu_vandertil_jerasure_jni_Encoding
 * Method:    getParity
 * Signature: (I[[B[BI)V
 */
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_getParity
  (JNIEnv *, jclass, jint, jobjectArray, jbyteArray, jint)
{}

/*
 * Class:     eu_vandertil_jerasure_jni_Encoding
 * Method:    encodeWithMatrix
 * Signature: (III[I[[B[[BI)V
 */
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_encodeWithMatrix
	(JNIEnv *env, jclass clazz, jint numDataDevices, jint numCodingDevices, jint wordSize, jintArray matrix, jobjectArray dataDevices, jobjectArray codingDevices, jint size)
{
	// C variables
	int i;

	// Brought in from the JVM
	jint* matrixElements = env->GetIntArrayElements(matrix, NULL);

	jobject* dataDevicesElements = talloc(jobject, numDataDevices);
	jbyte** data_ptrs = talloc(jbyte*, numDataDevices);
	for(i = 0; i < numDataDevices; ++i)
	{
		dataDevicesElements[i] = env->GetObjectArrayElement(dataDevices, i);
		data_ptrs[i] = env->GetByteArrayElements((jbyteArray)dataDevicesElements[i], NULL);
	}

	jobject* codingDevicesElements = talloc(jobject, numCodingDevices);
	jbyte** coding_ptrs = talloc(jbyte*, numCodingDevices);
	for(i = 0; i < numCodingDevices; ++i)
	{
		codingDevicesElements[i] = env->GetObjectArrayElement(codingDevices, i);
		coding_ptrs[i] = env->GetByteArrayElements((jbyteArray)codingDevicesElements[i], NULL);
	}

	// Do work
	jerasure_matrix_encode(numDataDevices, numCodingDevices, wordSize, (int*)matrixElements, (char**)data_ptrs, (char**)coding_ptrs, size);

	// Cleanup memory

	// Cleanup matrix
	env->ReleaseIntArrayElements(matrix, matrixElements, NULL);

	// Cleanup data pointers
	for(i = 0; i < numDataDevices; ++i)
	{
		env->ReleaseByteArrayElements((jbyteArray)dataDevicesElements[i], data_ptrs[i], NULL);
	}
	free(data_ptrs);
	free(dataDevicesElements);

	// Cleanup coding pointers
	for(i = 0; i < numCodingDevices; ++i)
	{
		env->ReleaseByteArrayElements((jbyteArray)codingDevicesElements[i], coding_ptrs[i], NULL);
	}
	free(coding_ptrs);
	free(codingDevicesElements);

	// Done
}

/*
 * Class:     eu_vandertil_jerasure_jni_Encoding
 * Method:    encodeWithBitMatrix
 * Signature: (III[I[[B[[BII)V
 */
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_encodeWithBitMatrix
	(JNIEnv *, jclass, jint, jint, jint, jintArray, jobjectArray, jobjectArray, jint, jint){}

/*
 * Class:     eu_vandertil_jerasure_jni_Encoding
 * Method:    encodeWithSchedule
 * Signature: (III[[I[[B[[BII)V
 */
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_encodeWithSchedule
	(JNIEnv *, jclass, jint, jint, jint, jobjectArray, jobjectArray, jobjectArray, jint, jint){}
