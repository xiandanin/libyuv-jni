#include <jni.h>

#include "libyuv/include/libyuv.h"
#include <android/log.h>

static int
(*i420ToRgbaFunc[])(const uint8_t *, int, const uint8_t *, int, const uint8_t *, int, uint8_t *,
                    int, int, int) ={
        libyuv::I420ToABGR, libyuv::I420ToRGBA, libyuv::I420ToARGB, libyuv::I420ToBGRA,
        libyuv::I420ToRGB24, libyuv::I420ToRGB565
};

static int
(*rgbaToI420Func[])(const uint8_t *, int, uint8_t *, int, uint8_t *, int, uint8_t *,
                    int, int, int) ={
        libyuv::ABGRToI420, libyuv::RGBAToI420, libyuv::ARGBToI420, libyuv::BGRAToI420,
        libyuv::RGB24ToI420, libyuv::RGB565ToI420
};

void rgbaToI420(int type, JNIEnv *env, jobject thiz, jbyteArray src,
                jbyteArray dst, jint width, jint height) {

    int src_stride_rgba = ((type & 0xF0) >> 4) * width;

    int dst_stride_y = width;
    int dst_stride_u = width >> 1;
    int dst_stride_v = dst_stride_u;

    size_t y_size = (size_t) (dst_stride_y * height);
    size_t u_size = (size_t) (dst_stride_u * height >> 1);

    jbyte *j_src = env->GetByteArrayElements(src, JNI_FALSE);
    jbyte *j_dst = env->GetByteArrayElements(dst, JNI_FALSE);

    const uint8_t *src_rgba = (const uint8_t *) j_src;
    uint8_t *dst_yuv = (uint8_t *) j_dst;

    uint8_t *dst_u = (uint8_t *) (j_dst) + y_size;
    uint8_t *dst_v = (uint8_t *) (j_dst) + y_size + u_size;

    uint8_t func_type = (uint8_t) (type & 0x0F);
    rgbaToI420Func[func_type](src_rgba, src_stride_rgba, dst_yuv, dst_stride_y,
                              dst_u, dst_stride_u, dst_v, dst_stride_v, width, height);

    env->ReleaseByteArrayElements(src, j_src, JNI_OK);
    env->ReleaseByteArrayElements(dst, j_dst, JNI_OK);
}

extern "C"
JNIEXPORT void JNICALL
Java_in_xiandan_libyuv_YuvJNI_nativeRGBAToI420(JNIEnv *env, jobject thiz, jbyteArray src,
                                               jbyteArray dst, jint width, jint height) {
    //0-3 表示转换类型
    //4-7 表示rgba_stride的宽度的倍数
    //8-11 表示yuv_stride宽度移位数
    //12-15 表示uv左移位数

    //RGBA_TO_I420=0x01001040;
    //ABGR_TO_I420=0x01001041;
    //BGRA_TO_I420=0x01001042;
    //ARGB_TO_I420=0x01001043;
    //RGB24_TO_I420=0x01001034;
    //RGB565_TO_I420=0x01001025;

    //I420_TO_RGBA=0x02001040;
    //I420_TO_ABGR=0x02001041;
    //I420_TO_BGRA=0x02001042;
    //I420_TO_ARGB=0x02001043;
    //I420_TO_RGB24=0x02001034;
    //I420_TO_RGB565=0x02001025;

    // 最终会使用 libyuv::ABGRToI420
    const int type_rgba_i420 = 0x01001040;
    rgbaToI420(type_rgba_i420, env, thiz, src, dst, width, height);
}