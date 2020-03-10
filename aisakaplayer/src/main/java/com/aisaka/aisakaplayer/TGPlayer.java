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
import java.io.IOException;
import java.lang.ref.WeakReference;
import java.net.HttpCookie;
import java.util.List;
import java.util.Map;

import androidx.annotation.IntDef;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class TGPlayer implements ITGMediaPlayer {


    private long playerPtr;

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

    public TGPlayer() {
        native_setup(new WeakReference<TGPlayer>(this));
    }

    @Override
    public void prepare() {
        _prepareAsync();
    }


    public void useOpenSLES(boolean use) {

    }

    public void useMediaCodec(boolean use) {

    }

    @Override
    public void setDisplay(SurfaceHolder sh) {

    }

    @Override
    public void setSurface(Surface surface) {
        _setVideoSurface(surface);
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
    public void setDataSource(String path, Map<String, String> headers) throws IOException {
        setDataSource(path, headers, null);
    }

    @Override
    public void setDataSource(String path, Map<String, String> headers, List<HttpCookie> cookies) throws IOException {
        _setDataSource(path);
    }

    @Override
    public void setLooping(boolean looping) {
        _setLooping(looping);
    }

    @Override
    public boolean isLooping() {
        return false;
    }

    @Override
    public void setVolume(float leftVolume, float rightVolume) {
        _setVolume(leftVolume, rightVolume);
    }

    @Override
    public void seekTo(long msec, int mode) {
        _seekTo(msec, mode);
    }

    @Override
    public Bundle getMetaData() {
        return _getMetadata();
    }

    @Override
    public Bitmap getFrameAtTime(int msec, int mode) {
        return _getFrameAtTime(msec, mode);
    }

    @Override
    public long getDuration() {
        return _getDuration();
    }

    @Override
    public long getCurrentPosition() {
        return _getCurrentPosition();
    }

    @Override
    public void start() {
        _start();
    }

    @Override
    public void pause() {
        _pause();
    }

    @Override
    public void resume() {
        _resume();
    }

    @Override
    public void stop() {
        _stop();
    }

    @Override
    public void release() {
        _release();
    }


    /**
     * Interface definition for a callback to be invoked when the media
     * source is ready for playback.
     */
    public interface OnPreparedListener {
        /**
         * Called when the media file is ready for playback.
         *
         * @param mp the TGPlayer that is ready for playback
         */
        void onPrepared(TGPlayer mp);
    }

    /**
     * Register a callback to be invoked when the media source is ready
     * for playback.
     *
     * @param listener the callback that will be run
     */
    public void setOnPreparedListener(TGPlayer.OnPreparedListener listener) {
        mOnPreparedListener = listener;
    }

    private TGPlayer.OnPreparedListener mOnPreparedListener;

    /**
     * Interface definition for a callback to be invoked when playback of
     * a media source has completed.
     */
    public interface OnCompletionListener {
        /**
         * Called when the end of a media source is reached during playback.
         *
         * @param mp the TGPlayer that reached the end of the file
         */
        void onCompletion(TGPlayer mp);
    }

    /**
     * Register a callback to be invoked when the end of a media source
     * has been reached during playback.
     *
     * @param listener the callback that will be run
     */
    public void setOnCompletionListener(TGPlayer.OnCompletionListener listener) {
        mOnCompletionListener = listener;
    }

    private TGPlayer.OnCompletionListener mOnCompletionListener;

    /**
     * @hide Internal completion listener to update PlayerBase of the play state. Always "registered".
     */
    private final TGPlayer.OnCompletionListener mOnCompletionInternalListener = new TGPlayer.OnCompletionListener() {
        @Override
        public void onCompletion(TGPlayer mp) {

        }
    };

    /**
     * Interface definition of a callback to be invoked indicating buffering
     * status of a media resource being streamed over the network.
     */
    public interface OnBufferingUpdateListener {
        /**
         * Called to update status in buffering a media stream received through
         * progressive HTTP download. The received buffering percentage
         * indicates how much of the content has been buffered or played.
         * For example a buffering update of 80 percent when half the content
         * has already been played indicates that the next 30 percent of the
         * content to play has been buffered.
         *
         * @param mp      the TGPlayer the update pertains to
         * @param percent the percentage (0-100) of the content
         *                that has been buffered or played thus far
         */
        void onBufferingUpdate(TGPlayer mp, int percent);
    }

    /**
     * Register a callback to be invoked when the status of a network
     * stream's buffer has changed.
     *
     * @param listener the callback that will be run.
     */
    public void setOnBufferingUpdateListener(TGPlayer.OnBufferingUpdateListener listener) {
        mOnBufferingUpdateListener = listener;
    }

    private TGPlayer.OnBufferingUpdateListener mOnBufferingUpdateListener;

    /**
     * Interface definition of a callback to be invoked indicating
     * the completion of a seek operation.
     */
    public interface OnSeekCompleteListener {
        /**
         * Called to indicate the completion of a seek operation.
         *
         * @param mp the TGPlayer that issued the seek operation
         */
        public void onSeekComplete(TGPlayer mp);
    }

    /**
     * Register a callback to be invoked when a seek operation has been
     * completed.
     *
     * @param listener the callback that will be run
     */
    public void setOnSeekCompleteListener(TGPlayer.OnSeekCompleteListener listener) {
        mOnSeekCompleteListener = listener;
    }

    private TGPlayer.OnSeekCompleteListener mOnSeekCompleteListener;

    /**
     * Interface definition of a callback to be invoked when the
     * video size is first known or updated
     */
    public interface OnVideoSizeChangedListener {
        /**
         * Called to indicate the video size
         * <p>
         * The video size (width and height) could be 0 if there was no video,
         * no display surface was set, or the value was not determined yet.
         *
         * @param mp     the TGPlayer associated with this callback
         * @param width  the width of the video
         * @param height the height of the video
         */
        public void onVideoSizeChanged(TGPlayer mp, int width, int height);
    }

    /**
     * Register a callback to be invoked when the video size is
     * known or updated.
     *
     * @param listener the callback that will be run
     */
    public void setOnVideoSizeChangedListener(TGPlayer.OnVideoSizeChangedListener listener) {
        mOnVideoSizeChangedListener = listener;
    }

    private TGPlayer.OnVideoSizeChangedListener mOnVideoSizeChangedListener;



    /* Do not change these values without updating their counterparts
     * in include/media/TGPlayer.h!
     */
    /**
     * Unspecified media player error.
     */
    public static final int MEDIA_ERROR_UNKNOWN = 1;

    /**
     * Media server died. In this case, the application must release the
     * TGPlayer object and instantiate a new one.
     */
    public static final int MEDIA_ERROR_SERVER_DIED = 100;

    /**
     * The video is streamed and its container is not valid for progressive
     * playback i.e the video's index (e.g moov atom) is not at the start of the
     * file.
     */
    public static final int MEDIA_ERROR_NOT_VALID_FOR_PROGRESSIVE_PLAYBACK = 200;

    /**
     * File or network related operation errors.
     */
    public static final int MEDIA_ERROR_IO = -1004;
    /**
     * Bitstream is not conforming to the related coding standard or file spec.
     */
    public static final int MEDIA_ERROR_MALFORMED = -1007;
    /**
     * Bitstream is conforming to the related coding standard or file spec, but
     * the media framework does not support the feature.
     */
    public static final int MEDIA_ERROR_UNSUPPORTED = -1010;
    /**
     * Some operation takes too long to complete, usually more than 3-5 seconds.
     */
    public static final int MEDIA_ERROR_TIMED_OUT = -110;

    /**
     * Unspecified low-level system error. This value originated from UNKNOWN_ERROR in
     * system/core/include/utils/Errors.h
     *
     * @hide
     */
    public static final int MEDIA_ERROR_SYSTEM = -2147483648;

    /**
     * Interface definition of a callback to be invoked when there
     * has been an error during an asynchronous operation (other errors
     * will throw exceptions at method call time).
     */
    public interface OnErrorListener {
        /**
         * Called to indicate an error.
         *
         * @param mp    the TGPlayer the error pertains to
         * @param what  the type of error that has occurred:
         *              <ul>
         *              <li>{@link #MEDIA_ERROR_UNKNOWN}
         *              <li>{@link #MEDIA_ERROR_SERVER_DIED}
         *              </ul>
         * @param extra an extra code, specific to the error. Typically
         *              implementation dependent.
         *              <ul>
         *              <li>{@link #MEDIA_ERROR_IO}
         *              <li>{@link #MEDIA_ERROR_MALFORMED}
         *              <li>{@link #MEDIA_ERROR_UNSUPPORTED}
         *              <li>{@link #MEDIA_ERROR_TIMED_OUT}
         *              <li><code>MEDIA_ERROR_SYSTEM (-2147483648)</code> - low-level system error.
         *              </ul>
         * @return True if the method handled the error, false if it didn't.
         * Returning false, or not having an OnErrorListener at all, will
         * cause the OnCompletionListener to be called.
         */
        boolean onError(TGPlayer mp, int what, int extra);
    }

    /**
     * Register a callback to be invoked when an error has happened
     * during an asynchronous operation.
     *
     * @param listener the callback that will be run
     */
    public void setOnErrorListener(TGPlayer.OnErrorListener listener) {
        mOnErrorListener = listener;
    }

    private TGPlayer.OnErrorListener mOnErrorListener;



    /* Do not change these values without updating their counterparts
     * in include/media/TGPlayer.h!
     */
    /**
     * Unspecified media player info.
     */
    public static final int MEDIA_INFO_UNKNOWN = 1;

    /**
     * The player was started because it was used as the next player for another
     * player, which just completed playback.
     */
    public static final int MEDIA_INFO_STARTED_AS_NEXT = 2;

    /**
     * The player just pushed the very first video frame for rendering.
     */
    public static final int MEDIA_INFO_VIDEO_RENDERING_START = 3;

    /**
     * The video is too complex for the decoder: it can't decode frames fast
     * enough. Possibly only the audio plays fine at this stage.
     */
    public static final int MEDIA_INFO_VIDEO_TRACK_LAGGING = 700;

    /**
     * TGPlayer is temporarily pausing playback internally in order to
     * buffer more data.
     */
    public static final int MEDIA_INFO_BUFFERING_START = 701;

    /**
     * TGPlayer is resuming playback after filling buffers.
     */
    public static final int MEDIA_INFO_BUFFERING_END = 702;

    /**
     * Estimated network bandwidth information (kbps) is available; currently this event fires
     * simultaneously as {@link #MEDIA_INFO_BUFFERING_START} and {@link #MEDIA_INFO_BUFFERING_END}
     * when playing network files.
     *
     * @hide
     */
    public static final int MEDIA_INFO_NETWORK_BANDWIDTH = 703;

    /**
     * Bad interleaving means that a media has been improperly interleaved or
     * not interleaved at all, e.g has all the video samples first then all the
     * audio ones. Video is playing but a lot of disk seeks may be happening.
     */
    public static final int MEDIA_INFO_BAD_INTERLEAVING = 800;

    /**
     * The media cannot be seeked (e.g live stream)
     */
    public static final int MEDIA_INFO_NOT_SEEKABLE = 801;

    /**
     * A new set of metadata is available.
     */
    public static final int MEDIA_INFO_METADATA_UPDATE = 802;

    /**
     * A new set of external-only metadata is available.  Used by
     * JAVA framework to avoid triggering track scanning.
     *
     * @hide
     */
    public static final int MEDIA_INFO_EXTERNAL_METADATA_UPDATE = 803;

    /**
     * Informs that audio is not playing. Note that playback of the video
     * is not interrupted.
     */
    public static final int MEDIA_INFO_AUDIO_NOT_PLAYING = 804;

    /**
     * Informs that video is not playing. Note that playback of the audio
     */
    public static final int MEDIA_INFO_VIDEO_NOT_PLAYING = 805;

    /**
     * Failed to handle timed text track properly.
     * <p>
     * {@hide}
     */
    public static final int MEDIA_INFO_TIMED_TEXT_ERROR = 900;

    /**
     * Subtitle track was not supported by the media framework.
     */
    public static final int MEDIA_INFO_UNSUPPORTED_SUBTITLE = 901;

    /**
     * Reading the subtitle track takes too long.
     */
    public static final int MEDIA_INFO_SUBTITLE_TIMED_OUT = 902;

    /**
     * Interface definition of a callback to be invoked to communicate some
     * info and/or warning about the media or its playback.
     */
    public interface OnInfoListener {
        /**
         * Called to indicate an info or a warning.
         *
         * @param mp    the TGPlayer the info pertains to.
         * @param what  the type of info or warning.
         *              <ul>
         *              <li>{@link #MEDIA_INFO_UNKNOWN}
         *              <li>{@link #MEDIA_INFO_VIDEO_TRACK_LAGGING}
         *              <li>{@link #MEDIA_INFO_VIDEO_RENDERING_START}
         *              <li>{@link #MEDIA_INFO_BUFFERING_START}
         *              <li>{@link #MEDIA_INFO_BUFFERING_END}
         *              <li><code>MEDIA_INFO_NETWORK_BANDWIDTH (703)</code> -
         *              bandwidth information is available (as <code>extra</code> kbps)
         *              <li>{@link #MEDIA_INFO_BAD_INTERLEAVING}
         *              <li>{@link #MEDIA_INFO_NOT_SEEKABLE}
         *              <li>{@link #MEDIA_INFO_METADATA_UPDATE}
         *              <li>{@link #MEDIA_INFO_UNSUPPORTED_SUBTITLE}
         *              <li>{@link #MEDIA_INFO_SUBTITLE_TIMED_OUT}
         *              </ul>
         * @param extra an extra code, specific to the info. Typically
         *              implementation dependent.
         * @return True if the method handled the info, false if it didn't.
         * Returning false, or not having an OnInfoListener at all, will
         * cause the info to be discarded.
         */
        boolean onInfo(TGPlayer mp, int what, int extra);
    }

    /**
     * Register a callback to be invoked when an info/warning is available.
     *
     * @param listener the callback that will be run
     */
    public void setOnInfoListener(TGPlayer.OnInfoListener listener) {
        mOnInfoListener = listener;
    }

    private TGPlayer.OnInfoListener mOnInfoListener;


    private static native final void native_init();

    private native final void native_setup(Object TGPlayer_this);

    private native void _setVideoScalingMode(int mode);

    private native void _setVideoSurface(Surface surface);


    private native void _setDataSource(String path) throws IOException, IllegalArgumentException, SecurityException, IllegalStateException;

    private native final void _prepareAsync() throws IllegalStateException;

    private native final void _start();

    private native final void _pause();

    private native final void _resume();

    private native final void _stop();

    private native final void _reset();

    private native final boolean _isPlaying();

    private native final void _release();

    private native final void _seekTo(long msec, int mode);

    private native final void _setVolume(float leftVolume, float rightVolume);

    private native final boolean _setLooping(boolean looping);

    private native final long _getCurrentPosition();

    private native final long _getDuration();

    private native final Bitmap _getFrameAtTime(long msec, int mode);

    private native final Bundle _getMetadata();


}
