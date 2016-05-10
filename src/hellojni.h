//
// Created by TianyuYan on 5/1/2016.
//

#ifndef HELLOOJNI_HELLOJNI_H
#define HELLOOJNI_HELLOJNI_H

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_tianyuyan_helloojni_MainActivity
 * Method:    getJNIString
 * Signature: ([BI)S
 */
JNIEXPORT jshort JNICALL Java_com_example_tianyuyan_helloojni_MainActivity_getJNIString___3BI
  (JNIEnv *, jclass, jbyteArray, jint);

/*
 * Class:     com_example_tianyuyan_helloojni_MainActivity
 * Method:    getJNIBytes
 * Signature: ([BI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_example_tianyuyan_helloojni_MainActivity_getJNIBytes
  (JNIEnv *, jclass, jbyteArray, jint);

/*
 * Class:     com_example_tianyuyan_helloojni_MainActivity
 * Method:    getJNIString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_tianyuyan_helloojni_MainActivity_getJNIString__
  (JNIEnv *, jclass);

/*
 * Class:     com_redteamobile_virtual_softsim_core_CardImpl
 * Method:    process
 * Signature: ([BI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_redteamobile_virtual_softsim_core_CardImpl_process
  (JNIEnv *, jobject, jbyteArray, jint);

/*
 * Class:     com_redteamobile_virtual_softsim_core_CardImpl
 * Method:    initCard
 * Signature: ()V
*/
JNIEXPORT void JNICALL Java_com_redteamobile_virtual_softsim_core_CardImpl_initCard
  (JNIEnv *, jobject);

  
#ifdef __cplusplus
}
#endif

#endif //HELLOOJNI_HELLOJNI_H
