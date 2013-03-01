#include "javautility.h"

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