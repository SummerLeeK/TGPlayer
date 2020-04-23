package com.aisaka.playerdemo;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Bitmap;
import android.media.MediaPlayer;
import android.os.Binder;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Process;
import android.util.Log;
import android.widget.TextView;


import com.aisaka.media.TGPlayer;

import java.io.File;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    public static final String TAG = "MainActivity";

    //    "http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4"
    TextView textView;
    String path;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = findViewById(R.id.player);

        path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "1.mp4";

        TGPlayer player = new TGPlayer();
        try {
            player.setDataSource(path,null);
        } catch (IOException e) {
            Log.e(TAG, "IOException \t" + e.getMessage());
        }
        player.setOnPreparedListener(new TGPlayer.OnPreparedListener() {
            @Override
            public void onPrepared(TGPlayer mp) {
                textView.setText("onPrepared finished");
                mp.start();
            }
        });


        player.setOnVideoSizeChangedListener(new TGPlayer.OnVideoSizeChangedListener() {
            @Override
            public void onVideoSizeChanged(TGPlayer mp, int width, int height) {
                Log.e(TAG, "onVideoSizeChanged \t" + width+"\t"+height);
            }
        });
        player.prepareSync();

//        long time=System.currentTimeMillis();
//        try {
//            player.prepare();
//        } catch (IOException e) {
//            Log.e(TAG, "prepare \t" + e.getMessage());
//        }
//
//        textView.setText("onPrepared finished main thread"+(System.currentTimeMillis()-time));



    }

}
