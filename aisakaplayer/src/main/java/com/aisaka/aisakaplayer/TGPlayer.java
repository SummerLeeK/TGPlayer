package com.aisaka.aisakaplayer;

import android.content.Context;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Parcel;
import android.os.Parcelable;
import android.view.Surface;
import android.view.SurfaceHolder;

import java.io.FileDescriptor;
import java.net.HttpCookie;
import java.util.List;
import java.util.Map;

import androidx.annotation.IntDef;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class TGPlayer implements ITGMediaPlayer {


    static {
        System.loadLibrary("avutil");
        System.loadLibrary("avdevice");
        System.loadLibrary("avformat");
        System.loadLibrary("avcodec");
        System.loadLibrary("swscale");
        System.loadLibrary("swresample");
        System.loadLibrary("avfilter");
        System.loadLibrary("tgplayer");
        native_init();
    }

    @Override
    public void prepare() {

    }


    public void useOpenSLES(boolean use){

    }

    public void useMediaCodec(boolean use){

    }

    @Override
    public void setDisplay(SurfaceHolder sh) {

    }

    @Override
    public void setSurface(Surface surface) {

    }

    @Override
    public void setVideoScalingMode(int mode) {

    }

    @Override
    public void setDataSource(@NonNull Context context, @NonNull Uri uri, @Nullable Map<String, String> headers) {

    }

    @Override
    public void setDataSource(@NonNull Context context, @NonNull Uri uri) {

    }

    @Override
    public void setDataSource(@NonNull Context context, @NonNull Uri uri, @Nullable Map<String, String> headers, @Nullable List<HttpCookie> cookies) {

    }

    @Override
    public void setDataSource(String path, Map<String, String> headers) {

    }

    @Override
    public void setDataSource(String path, Map<String, String> headers, List<HttpCookie> cookies) {

    }

    @Override
    public void setLooping(boolean looping) {

    }

    @Override
    public boolean isLooping() {
        return false;
    }

    @Override
    public void setVolume(float leftVolume, float rightVolume) {

    }

    @Override
    public void seekTo(int msec, int mode) {

    }

    @Override
    public Metadata getMetaData() {
        return null;
    }

    @Override
    public Bitmap getFrameAtTime(int msec, int mode) {
        return null;
    }

    @Override
    public int getDuration() {
        return 0;
    }

    @Override
    public int getCurrentPosition() {
        return 0;
    }

    @Override
    public void start() {

    }

    @Override
    public void pause() {

    }

    @Override
    public void resume() {

    }

    @Override
    public void stop() {

    }

    @Override
    public void release() {

    }


    private static native final void native_init();

    private native final void native_setup(Object mediaplayer_this);

    private native void _setVideoScalingMode(int mode);

    private native void _setDataSource(String path, Map<String, String> headers, List<HttpCookie> cookies);

    private native final void _prepareAsync();

    private native final void _start();

    private native final void _pause();

    private native final void _resume();

    private native final void _stop();

    private native final void _release();

    private native final void _seekTo(int msec, int mode);

    private native final void _setVolume(int leftVolume, int rightVolume);

    private native final boolean _setLooping(boolean looping);

    private native final int _getCurrentPosition();

    private native final int _getDuration();

    private native final Bitmap _getFrameAtTime(int msec, int mode);

    private native final Bundle _getMetadata();


}
