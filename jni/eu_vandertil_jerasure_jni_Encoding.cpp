#include <stdlib.h>

#include "eu_vandertil_jerasure_jni_Encoding.h"
#include "jerasure.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

void releaseArrayOfByteArrays(JNIEnv *env, jobject* arrays, jbyte** elements, int count)
{
	for(int i = 0; i < count; ++i)
	{
		env->ReleaseByteArrayElements((jbyteArray)arrays[i], elements[i], NULL);
	}
	free(arrays);
	free(elements);
}

/*
* Class:     eu_vandertil_jerasure_jni_Encoding
* Method:    getParity
* Signature: (I[[B[BI)V
*/
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_getParity
	(JNIEnv *env, jclass clazz, jint numDataDevices, jobjectArray data, jbyteArray parity, jint size)
{
	// C variables
	int i;

	// JVM variables
	jobject* dataDevices = talloc(jobject, numDataDevices);
	jbyte** data_ptrs = talloc(jbyte*, numDataDevices);
	for(i = 0; i < numDataDevices; ++i)
	{
		dataDevices[i] = env->GetObjectArrayElement(data, i);
		data_ptrs[i] = env->GetByteArrayElements((jbyteArray)dataDevices[i], NULL);
	}

	jbyte* parity_ptr = env->GetByteArrayElements(parity, NULL);

	// Do work
	jerasure_do_parity(numDataDevices, (char**)data_ptrs, (char*)parity_ptr, size);

	// Clean up
	env->ReleaseByteArrayElements(parity, parity_ptr, NULL);
	releaseArrayOfByteArrays(env, dataDevices, data_ptrs, numDataDevices);
}

/*
* Class:     eu_vandertil_jerasure_jni_Encoding
* Method:    encodeWithMatrix
* Signature: (III[I[[B[[BI)V
*/
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_encodeWithMatrix
	(JNIEnv *env, jclass clazz, jint numDataDevices, jint numCodingDevices, jint wordSize, jintArray matrix, 
	jobjectArray dataDevices, jobjectArray codingDevices, jint size)
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

	// Cleanup
	env->ReleaseIntArrayElements(matrix, matrixElements, NULL);
	releaseArrayOfByteArrays(env, dataDevicesElements, data_ptrs, numDataDevices);
	releaseArrayOfByteArrays(env, codingDevicesElements, coding_ptrs, numCodingDevices);
}

/*
* Class:     eu_vandertil_jerasure_jni_Encoding
* Method:    encodeWithBitMatrix
* Signature: (III[I[[B[[BII)V
*/
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_encodeWithBitMatrix
	(JNIEnv *env, jclass clazz, jint numDataDevices, jint numCodingDevices, jint wordSize, jintArray bitMatrix, 
	jobjectArray dataDevices, jobjectArray codingDevices, jint size, jint packetSize)
{
	// C variables
	int i;

	// JVM variables
	jint* bitMatrixElements = env->GetIntArrayElements(bitMatrix, NULL);
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
	jerasure_bitmatrix_encode(numDataDevices, numCodingDevices, wordSize, (int*)bitMatrixElements, (char**)data_ptrs, (char**)coding_ptrs, size, packetSize);

	// Cleanup
	env->ReleaseIntArrayElements(bitMatrix, bitMatrixElements, NULL);

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
}

/*
* Class:     eu_vandertil_jerasure_jni_Encoding
* Method:    encodeWithSchedule
* Signature: (III[[I[[B[[BII)V
*/
JNIEXPORT void JNICALL Java_eu_vandertil_jerasure_jni_Encoding_encodeWithSchedule
	(JNIEnv *env, jclass clazz, jint numDataDevices, jint numCodingDevices, jint wordSize, jobjectArray schedule, 
	jobjectArray dataDevices, jobjectArray codingDevices, jint size, jint packetSize)
{
	int i;

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

	int scheduleElementCount = env->GetArrayLength(schedule);
	jobject* scheduleElements = talloc(jobject, scheduleElementCount);
	jint** schedule_ptrs = talloc(jint*, scheduleElementCount);

	for(i = 0; i < scheduleElementCount; ++i)
	{
		scheduleElements[i] = env->GetObjectArrayElement(schedule, i);
		schedule_ptrs[i] = env->GetIntArrayElements((jintArray)scheduleElements[i], NULL);
	}

	jerasure_schedule_encode(numDataDevices, numCodingDevices, wordSize, (int**)schedule_ptrs, (char**)data_ptrs, (char**)coding_ptrs, size, packetSize);

	// Cleanup data pointers
	releaseArrayOfByteArrays(env, dataDevicesElements, data_ptrs, numDataDevices);
	releaseArrayOfByteArrays(env, codingDevicesElements, coding_ptrs, numCodingDevices);

	// Cleanup schedule pointers
	for(i = 0; i < scheduleElementCount; ++i)
	{
		env->ReleaseIntArrayElements((jintArray)scheduleElements[i], schedule_ptrs[i], NULL);
	}
	free(schedule_ptrs);
	free(scheduleElements);
}
