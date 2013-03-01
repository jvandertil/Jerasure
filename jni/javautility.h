#include <jni.h>

jint throwNoClassDefError(JNIEnv*, char *);
jint throwOutOfMemoryError(JNIEnv*, char *);
jint throwIllegalArgumentException(JNIEnv *env, char* message);