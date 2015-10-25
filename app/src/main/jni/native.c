#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <jni.h>
#include <string.h>
#include <android/log.h>
#ifndef DHRY_DEBUG
#define DHRY_DEBUG 1
#endif
#define DEBUG_TAG "NDK_DhryThread"
#define DHRY_MAX_THREADS 128
static const char runlogname[]="run.log";
char runlogpath[PATH_MAX+1];

extern int dhrymain (long nLoops, FILE *outbuf);
static void mkRunLogPath(JNIEnv *env, jstring cacheDir);
static jstring copyLogToJstring(JNIEnv *env);
static void run_dhry_mt(long loops, int threads, FILE *runlog);

static void mkRunLogPath(JNIEnv *env, jstring cacheDir) {
	/* create a file for run log */
	const char *logprefix=(*env)->GetStringUTFChars(env,cacheDir,JNI_FALSE);
	strncpy(runlogpath, logprefix, PATH_MAX);
	(*env)->ReleaseStringUTFChars(env,cacheDir,logprefix);
	strncat(runlogpath, runlogname, PATH_MAX);
	if(DHRY_DEBUG) {
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Run log => %s", runlogpath);
	}
}

static jstring copyLogToJstring(JNIEnv *env) {
	FILE *runlog=fopen(runlogpath, "r");
	fseek(runlog, 0L, SEEK_END);
	long loglen=ftell(runlog);
	if(DHRY_DEBUG) { __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "log length = %ld", loglen); }
	fseek(runlog,0L, SEEK_SET);
	char *log=(char *)calloc(1+loglen,sizeof(char));
	size_t bytes_read=fread(log, 1, loglen, runlog);
	fclose(runlog);
	if(DHRY_DEBUG) { __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "bytes read = %zd", bytes_read); }
	log[bytes_read]='\0';
	jstring jres=(*env)->NewStringUTF(env,log);
	free(log);
	return jres;
}

static void run_dhry_mt(long loops, int threads, FILE *runlog) {
	int pids[DHRY_MAX_THREADS];
	int pid;
	int i=0;
	int nfork=threads-1;
	while(i<nfork) {
		if((pid=fork())<0) { return; }
		if(pid==0) { break; }
		pids[i++]=pid;
	}
	dhrymain(loops,runlog);
	fclose(runlog);
	if(pid>0) {
		for(i=0; i<nfork; i++) {
			int status;
			waitpid(pids[i], &status, 0);
		}
	} else {
		exit(0);
	}
}

jstring Java_com_example_ndkdhryv7_DhryThread_runNdkDhry(JNIEnv * env, jobject this, jlong loops, jint threads, jstring cacheDir)
{
	mkRunLogPath(env, cacheDir);
	FILE *runlog;
	if(!(runlog=fopen(runlogpath, "w"))) {
		if(DHRY_DEBUG) { __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "fopen failed"); }
		return NULL;
	}
	run_dhry_mt(loops,threads, runlog);
	jstring jres=copyLogToJstring(env);
	if(unlink(runlogpath)) {
		if(DHRY_DEBUG) { __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "unlink failed"); }
	}
	return jres;
}

jint Java_com_example_ndkdhryv7_DhryThread_killPG(JNIEnv * env, jobject this)
{
	return kill(-getpgrp(),SIGKILL);
}

jint Java_com_example_ndkdhryv7_DhryThread_maxThreads(JNIEnv * env, jobject this)
{
	return DHRY_MAX_THREADS;
}

#define DIAGBUF_SZ 256L
jstring Java_com_example_ndkdhryv7_DhryThread_getDiagInfo(JNIEnv *env, jobject this)
{
	unsigned int nbits=sizeof(void*)*8;
	char buf[DIAGBUF_SZ];
	snprintf(buf,DIAGBUF_SZ,
			"Compiled with "
#ifdef __clang__
			"clang version " __clang_version__
#elif defined(__GNUC__)
			"GCC version " __VERSION__
#endif
			"\nsize of pointers = %d bits\n", nbits);
	jstring diagstr=(*env)->NewStringUTF(env,buf);
}
