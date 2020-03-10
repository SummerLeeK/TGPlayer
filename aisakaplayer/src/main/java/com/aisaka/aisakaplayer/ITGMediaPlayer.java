package com.aisaka.aisakaplayer;

import android.content.Context;
import android.graphics.Bitmap;
import android.media.MediaMetadata;
import android.net.Uri;
import android.os.Bundle;
import android.view.Surface;
import android.view.SurfaceHolder;

import java.io.IOException;
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


    public void setDataSource(String path, Map<String, String> headers) throws IOException;

    public void setDataSource(String path, Map<String, String> headers, List<HttpCookie> cookies) throws IOException;

    public void setLooping(boolean looping);

    public boolean isLooping();

    public void setVolume(float leftVolume, float rightVolume);

    public void seekTo(long msec, int mode);

    public Bundle getMetaData();

    public Bitmap getFrameAtTime(int msec, int mode);

    public long getDuration();

    public long getCurrentPosition();

    public void start();

    public void pause();

    public void resume();

    public void stop();

    public void release();
}
