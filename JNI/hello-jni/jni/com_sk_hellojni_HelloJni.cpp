
#include "com_sk_hellojni_HelloJni.h"

JNIEXPORT jint JNICALL Java_com_sk_hellojni_HelloJni_AddNumber
(JNIEnv *, jobject, jint a, jint b)
{
	return a+b;
}
