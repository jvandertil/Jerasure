#include <string.h> //For memset
#include <stdlib.h>
#include "javautility.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

jint throwNoClassDefError(JNIEnv *env, char *message) {
	jclass exClass;
	char *className = "java/lang/NoClassDefFoundError";

	exClass = env->FindClass(className );
	if ( exClass == NULL )
	{
		return throwNoClassDefError(env, className );
	}

	return env->ThrowNew(exClass, message );
}

jint throwOutOfMemoryError(JNIEnv *env, char *message) {
	jclass exClass;
	char *className = "java/lang/OutOfMemoryError";

	exClass = env->FindClass(className);
	if(exClass == NULL)
	{
		return throwNoClassDefError(env, className);
	}

	return env->ThrowNew(exClass, message);
}

jint throwIllegalArgumentException(JNIEnv *env, char* message) {
	jclass exClass;
	char* className = "java/lang/IllegalArgumentException";

	exClass = env->FindClass(className);
	if(exClass == NULL)
	{
		return throwNoClassDefError(env, className);
	}

	return env->ThrowNew(exClass, message);
}

bool getArrayOfByteArrays(JNIEnv *env, jobjectArray* arrays, jbyteArray* arrayOfArrays, jbyte** resultData, int numArrays)
{
	arrayOfArrays = talloc(jbyteArray, numArrays);
	resultData = talloc(jbyte*, numArrays);

	// Clear values for safety.
	memset(arrayOfArrays, NULL, numArrays);
	memset(resultData, NULL, numArrays);

	if(arrayOfArrays == NULL || resultData == NULL) {
		freeArrayOfByteArrays(env, arrayOfArrays, resultData, 0);
		return false;
	}

	for(int i = 0; i < numArrays; ++i) {
		arrayOfArrays[i] = (jbyteArray)env->GetObjectArrayElement(*arrays, i);
		resultData[i] = env->GetByteArrayElements(arrayOfArrays[i], NULL);
		if(resultData[i] == NULL) {
			freeArrayOfByteArrays(env, arrayOfArrays, resultData, i);
			return false;
		}
	}

	return true;
}

/*
* Can be used to clean up arrays retrieved from getArrayOfByteArrays()
*/
void freeArrayOfByteArrays(JNIEnv *env, jbyteArray* arrayOfArrays, jbyte** resultData, int numArrays)
{
	int i;
	if(arrayOfArrays != NULL && resultData != NULL) {
		for(i = 0; i < numArrays; ++i) {
			env->ReleaseByteArrayElements(arrayOfArrays[i], resultData[i], NULL);
			env->DeleteLocalRef(arrayOfArrays[i]);
		}
	}

	free(resultData);
	free(arrayOfArrays);
}