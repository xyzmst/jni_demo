/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <android/log.h>

#define DEBUG 1

#if DEBUG
#define LOG(msg, args...) __android_log_print(ANDROID_LOG_ERROR, "hello-jni", msg, ## args)
#else
#define LOG(msg, args...)
#endif


jstring
Java_com_example_hellojni_HelloJni_stringFromJNI(JNIEnv *env, jobject thiz) {
    LOG("============== start =============");
    LOG("debug function %s", "stringFromJNI");

    return (*env)->NewStringUTF(env, "Hello from JNI !");
}


jbyteArray Java_com_example_hellojni_HelloJni_arrayFromJNI(JNIEnv *env, jobject thiz,
                                                           jbyteArray inputArray) {
    jbyte *buffer = (*env)->GetByteArrayElements(env, inputArray, (jboolean) 0);
    int inputSize = (*env)->GetArrayLength(env, inputArray);
    jbyteArray jarray = (*env)->NewByteArray(env, inputSize * 2);

    int position = 0;

    int i;
    int j = 0;
    for (i = 0; i < inputSize; i += 2) {
        char *array = malloc(4 * sizeof(char));
        array[0] = 0;
        array[1] = 1;
        array[2] = 0;
        array[3] = 1;
        (*env)->SetByteArrayRegion(env, jarray, position, sizeof(array), (jbyte *) array);
        free(array);
        position += sizeof(array);
        j++;
    }
    jbyte *jarrayAdd = (*env)->GetByteArrayElements(env, jarray, (jboolean) 0);
    jbyteArray jarray2 = (*env)->NewByteArray(env, position);
    (*env)->SetByteArrayRegion(env, jarray2, 0, position * 8, jarrayAdd);
    (*env)->ReleaseByteArrayElements(env, inputArray, buffer, JNI_ABORT);
    (*env)->ReleaseByteArrayElements(env, jarray, jarrayAdd, JNI_ABORT);
    return jarray2;
}


jbyteArray Java_com_example_hellojni_HelloJni_arrayTest(JNIEnv *env, jobject thiz,
                                                        jintArray inputArray) {
    jint *buffer = (*env)->GetByteArrayElements(env, inputArray, (jboolean) 0);
    int inputSize = (*env)->GetArrayLength(env, inputArray);
    int i = 0;
    for (; i < inputSize; i++) {
        *(buffer + i) = i + 1;
    }

    // 经验证 所有参数 都不影响返回值,数组已变
    //将内容复制回来并释放原生数组
//    (*env)->ReleaseIntArrayElements(env, inputArray, buffer, 0);
    //将内容复制回来但不释放原生数组,一般用于周期性更新一个java数组
//    (*env)->ReleaseIntArrayElements(env, inputArray, buffer, JNI_COMMIT);
    //释放原生数组但不用将内容复制回来
    (*env)->ReleaseIntArrayElements(env, inputArray, buffer, JNI_ABORT);
    return inputArray;
}

int *temp = 0;

jbyteArray Java_com_example_hellojni_HelloJni_reallocTest(JNIEnv *env, jobject thiz,
                                                          jintArray inputArray) {
    jint *buffer = (*env)->GetByteArrayElements(env, inputArray, (jboolean) 0);
    int inputSize = (*env)->GetArrayLength(env, inputArray);

    temp = (int *) realloc(temp, sizeof(int) * 4);
    LOG("temp orignal size %d", sizeof(temp) / sizeof(temp[0]));
    int i = 0;
    for (; i < inputSize; i++) {
        *(temp + i) = *(buffer + i) + 2;
        LOG("%d = %d", i, *(temp + i));
    }

    temp = (int *) realloc(temp, sizeof(temp) * 2);


//
    *(temp + 4) = 5;
    i = 0;
    for (; i < 5; i++) {
        LOG("==== %d = %d", i, *(temp + i));
    }
    jintArray returnarray = (*env)->NewIntArray(env, inputSize * 2);
    int newSize = (*env)->GetArrayLength(env, returnarray);
    LOG("array size is %d", newSize);
    (*env)->SetIntArrayRegion(env, returnarray, 0, newSize - 1, temp);

//    jint *bt = (*env)->GetByteArrayElements(env, returnarray, (jboolean) 0);
    (*env)->ReleaseIntArrayElements(env, returnarray, temp, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, inputArray, buffer, JNI_ABORT);
    temp = realloc(temp, 0);
    return returnarray;
}