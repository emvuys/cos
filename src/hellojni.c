//
// Created by TianyuYan on 5/1/2016.
//

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "hellojni.h"
#include <Android/log.h>
#include <string.h>  
#include "commandprocess/dispatcher.h"

jbyteArray *jarrayOut = NULL;
jbyte apduResponse[256];
jbyte apduBuffer[256];
jshort apduResponseLen = 0;

#define TAG    "myhello-jni-test"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__) // 定义LOGD类型  


jshort JNICALL Java_com_example_tianyuyan_helloojni_MainActivity_getJNIString___3BI
	(JNIEnv *env, jclass thiz, jbyteArray buf, jint len) {

	short sum = 0, i;

    jbyte *jbarray = (jbyte *)malloc(len * sizeof(jbyte));
    (*env)->GetByteArrayRegion(env, buf, 0, len, jbarray);     
		
	for( i = 0; i < len; i ++) {
		sum += jbarray[i];
	}
	
    return sum;
}



jbyteArray JNICALL Java_com_example_tianyuyan_helloojni_MainActivity_getJNIBytes
	(JNIEnv *env, jclass thiz, jbyteArray buf, jint len) {

	short sum = 0, i;

    jbyte *jbarray = (jbyte *)malloc(len * sizeof(jbyte));
    (*env)->GetByteArrayRegion(env, buf, 0, len, jbarray);     
		
	for( i = 0; i < len; i ++) {
		jbarray[i] *= 2;
	}
	(*env)->SetByteArrayRegion(env, buf, 0, len, jbarray);
	//(*env)->CallStaticVoidMethod(env,cls, mid,buf);
	
    return buf;
}

jbyteArray JNICALL Java_com_redteamobile_virtual_softsim_core_CardImpl_process
	(JNIEnv *env, jclass thiz, jbyteArray buf, jint len) {

	short sum = 0, i;
	short length = sizeof(apduResponse);

    memset(apduResponse, 0x44, length);
    (*env)->GetByteArrayRegion(env, buf, 0, len, apduBuffer);

	//for( i = 0; i < length; i ++) {
	//	apduResponse[i] *= 2;
	//}
	
	/*
	if (jarrayOut != NULL) {
	    (*env)->DeleteLocalRef(env, jarrayOut);
	}
	*/
	//LOGD("########## len = %d", len);
	apduResponseLen = dispatcher(apduBuffer, len, apduResponse, &apduResponseLen);
	//LOGD("########## apduResponseLen = %d", apduResponseLen);  
	jarrayOut = (*env)->NewByteArray(env, apduResponseLen *  sizeof(jbyte));
    (*env)->SetByteArrayRegion(env, jarrayOut, 0, apduResponseLen, apduResponse);
    return jarrayOut;
}

/*
 * Class:     com_redteamobile_virtual_softsim_core_CardImpl
 * Method:    initCard
 * Signature: ()V
 */
void JNICALL Java_com_redteamobile_virtual_softsim_core_CardImpl_initCard
  (JNIEnv *env, jobject thiz) {
	 insertCard(
				"",//"460010300000001",//imsi,
				"",//ki,
				"",//opc,
				"",//iccid,
				"",//acc,
				"",//spn,
				"",//apn,
				"",//hplmn,
				"",//ehplmn
				"",//loci,
				"",//psloci
				""//fplmn
				);
}

/*
 * Class:     com_example_tianyuyan_helloojni_MainActivity
 * Method:    getJNIString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_tianyuyan_helloojni_MainActivity_getJNIString__
  (JNIEnv *env, jclass thiz) {
#if defined(__arm__)
  #if defined(__ARM_ARCH_7A__)
    #if defined(__ARM_NEON__)
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a/NEON (hard-float)"
      #else
        #define ABI "armeabi-v7a/NEON"
      #endif
    #else
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a (hard-float)"
      #else
        #define ABI "armeabi-v7a"
      #endif
    #endif
  #else
   #define ABI "armeabi"
  #endif
#elif defined(__i386__)
   #define ABI "x86"
#elif defined(__x86_64__)
   #define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
   #define ABI "mips64"
#elif defined(__mips__)
   #define ABI "mips"
#elif defined(__aarch64__)
   #define ABI "arm64-v8a"
#else
   #define ABI "unknown"
#endif

    return (*env)->NewStringUTF(env, "Hello from JNI !  Compiled with ABI " ABI ".");
  }