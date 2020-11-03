#include <jni.h>
//#include <cstring>
#include <string>
#include <vector>

//using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_com_phantom_automath_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject obj) {
    std::string hello = "Numbers: ";
    return env->NewStringUTF(hello.c_str());
}
