package com.aisaka.playerdemo;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Bitmap;
import android.media.MediaPlayer;
import android.os.Binder;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.os.Process;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.TextView;


import com.aisaka.media.TGPlayer;

import java.io.File;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    public static final String TAG = "MainActivity";

    String netPath = "http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4";
    TextView textView;
    String path;

    private SurfaceView surfaceView;
    TGPlayer player;
    private Handler handler = new Handler(Looper.getMainLooper()) {

        @Override
        public void handleMessage(Message msg) {
            player.start();
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = findViewById(R.id.player);
        surfaceView = findViewById(R.id.surface);
        path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "1.mp4";

//        path=netPath;
        player = new TGPlayer();
        try {
            player.setDataSource(path, null);
        } catch (IOException e) {
            Log.e(TAG, "IOException \t" + e.getMessage());
        }
        player.setOnPreparedListener(new TGPlayer.OnPreparedListener() {
            @Override
            public void onPrepared(TGPlayer mp) {
//                textView.setText("onPrepared finished");
//                mp.start();
                Log.e(TAG, "onPrepared \t" + Thread.currentThread().toString());
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        player.setSurface(surfaceView.getHolder().getSurface());
                        player.start();
                    }
                });

            }
        });


        player.setOnVideoSizeChangedListener(new TGPlayer.OnVideoSizeChangedListener() {
            @Override
            public void onVideoSizeChanged(TGPlayer mp, int width, int height) {
                Log.e(TAG, "onVideoSizeChanged \t" + width + "\t" + height + "\t" + Thread.currentThread().toString());
            }
        });

        player.setOnErrorListener(new TGPlayer.OnErrorListener() {
            @Override
            public void onError(TGPlayer mp, int what, String msg) {
                Log.e(TAG, "onError \t" + what + "\t" + msg);
            }
        });


        player.prepareAsync();

        surfaceView.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(SurfaceHolder surfaceHolder) {
                Log.d(TAG, "surfaceCreated \t" + Thread.currentThread().toString());

            }

            @Override
            public void surfaceChanged(SurfaceHolder surfaceHolder, int i, int i1, int i2) {
                Log.d(TAG, "surfaceChanged \t" + Thread.currentThread().toString());

            }

            @Override
            public void surfaceDestroyed(SurfaceHolder surfaceHolder) {
                Log.d(TAG, "surfaceDestroyed \t" + Thread.currentThread().toString());

            }
        });

    }

}
