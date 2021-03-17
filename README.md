## Gradle引入

```
implementation 'in.xiandan:libyuv-jni:1.0.0'
```



## RGBA转I420

```
YuvJNI.rgbaToI420(rgba, width, height)
```



## 编译相关

### Git

[https://chromium.googlesource.com/libyuv/libyuv](https://chromium.googlesource.com/libyuv/libyuv)

基于2021-3-13 09:17:02 [**f37014fcfffd62f00a80a900f016964763c56864**](**f37014fcfffd62f00a80a900f016964763c56864**)

> f37014f Add support for AR64 format by Yuan Tong · 2 days ago master



### Cmake

将源码解压到cpp，在cpp根目录的`CMakeLists.txt`追加

```
include_directories(libyuv/include)
add_subdirectory(libyuv)
add_library( # Sets the name of the library.
             yuv-jni

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             yuv-jni.cpp)

target_link_libraries( # Specifies the target library.
                       yuv-jni

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       yuv)
```