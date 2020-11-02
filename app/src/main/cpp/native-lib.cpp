#include <jni.h>
//#include <cstring>
#include <string>
#include <vector>

//using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_com_phantom_automath_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++ Bhosdike";
    return env->NewStringUTF(hello.c_str());
}
