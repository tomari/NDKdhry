#include <stdlib.h>
#include <stdio.h>
#include <jni.h>
#include <string.h>
/*#include <android/log.h>*/
#define DEBUG_TAG "NDK_DhryThread"
#define OUTBUF_SIZE 8100
extern int dhrymain (int nLoops, char *outbuf);

jstring Java_com_example_ndkdhryv7_DhryThread_runNdkDhry(JNIEnv * env, jobject this, jint loops)
{
	char *res=(char *)calloc(OUTBUF_SIZE,sizeof(char));
	jstring jres=NULL;
    jboolean isCopy;
	if(res) {
		/*snprintf(res,OUTBUF_SIZE,"Run Dhrystone %d times\n",loops); */
		dhrymain(loops,res);
		jres=(*env)->NewStringUTF(env,res);
	    /*__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "native code successful"); */
	} /*else {
	    __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "calloc returns NULL.");
	}*/
	free(res);
	return jres;
}
