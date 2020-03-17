package com.aisaka.playerdemo;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;


import com.aisaka.media.TGPlayer;

import java.io.File;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    public static final String TAG="MainActivity";

//    "http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4"
    String path;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        path= Environment.getExternalStorageDirectory().getAbsolutePath()+ File.separator+"1.mp4";

        TGPlayer player=new TGPlayer();
        try {
            player.setDataSource("http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4",null,null);
        } catch (IOException e) {
            Log.e(TAG,"IOException \t"+e.getMessage());
        }
        player.setOnPreparedListener(new TGPlayer.OnPreparedListener() {
            @Override
            public void onPrepared(TGPlayer mp) {
                Log.e(TAG,"onPrepared finish\t");
            }
        });
        try {
            player.prepare();
        } catch (IOException e) {
            Log.e(TAG,"prepare \t"+e.getMessage());
        }

    }
}
