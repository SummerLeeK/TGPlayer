package com.aisaka.media.annotation;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

import androidx.annotation.IntDef;

import static com.aisaka.media.utils.Constants.*;


@Retention(RetentionPolicy.RUNTIME)
@IntDef({STAUES_IDLE, STAUES_PREPARED, PLAYING, PLAYING_BUFFERING, PAUSE, RELEASE})
public @interface PlayerStatus {
}
