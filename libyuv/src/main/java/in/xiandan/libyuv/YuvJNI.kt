package `in`.xiandan.libyuv

/**
 * Created by dengyuhan on 2021/3/16 13:56
 */
object YuvJNI {

    init {
        System.loadLibrary("yuv-jni")
    }

    fun rgbaToI420(rgba: ByteArray, width: Int, height: Int): ByteArray {
        val yuv = ByteArray(width * height * 3 / 2)
        nativeRGBAToI420(rgba, yuv, width, height)
        return yuv
    }


    /**
     * rgba -> I420
     */
    external fun nativeRGBAToI420(rgba: ByteArray, yuv: ByteArray, width: Int, height: Int)

}