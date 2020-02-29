package com.aisaka.aisakaplayer;

import android.content.Context;
import android.graphics.Bitmap;
import android.media.MediaMetadata;
import android.net.Uri;
import android.view.Surface;
import android.view.SurfaceHolder;

import java.net.HttpCookie;
import java.util.List;
import java.util.Map;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public interface ITGMediaPlayer {


    public void prepare();

    public void setDisplay(SurfaceHolder sh);

    public void setSurface(Surface surface);

    public void setVideoScalingMode(int mode);


    public void setDataSource(@NonNull Context context, @NonNull Uri uri,
                              @Nullable Map<String, String> headers);

    public void setDataSource(@NonNull Context context, @NonNull Uri uri);

    public void setDataSource(@NonNull Context context, @NonNull Uri uri,
                              @Nullable Map<String, String> headers, @Nullable List<HttpCookie> cookies);


    public void setDataSource(String path, Map<String, String> headers);

    public void setDataSource(String path, Map<String, String> headers, List<HttpCookie> cookies);

    public void setLooping(boolean looping);

    public boolean isLooping();

    public void setVolume(float leftVolume, float rightVolume);

    public void seekTo(int msec, int mode);

    public Metadata getMetaData();

    public Bitmap getFrameAtTime(int msec, int mode);

    public int getDuration();

    public int getCurrentPosition();

    public void start();

    public void pause();

    public void resume();

    public void stop();

    public void release();
}
