//
// Created by Apple on 2020-03-22.
//

#include <assert.h>
#include <cstring>
#include <native_log.h>
#include "OpenSLESPlayer.h"


void pcmPlayCallBack(SLAndroidSimpleBufferQueueItf bq, void *data) {
    PCMData *pcmdata = reinterpret_cast<PCMData *>(data);
    (*bq)->Enqueue(bq, pcmdata->data, pcmdata->size);
}

OpenSLESPlayer::OpenSLESPlayer() {


}

OpenSLESPlayer::~OpenSLESPlayer() {


    if (playerObjectItf) {
        (*playerObjectItf)->Destroy(playerObjectItf);
    }

    if (outputMixItf) {
        (*outputMixItf)->Destroy(outputMixItf);
    }


    if (engineItf) {
        (*engineItf)->Destroy(engineItf);
    }

}

int getSampleRate(int sampleRate) {
    switch (sampleRate) {
        case 8000:
            return SL_SAMPLINGRATE_8;
        case 11025:
            return SL_SAMPLINGRATE_11_025;
        case 12000:
            return SL_SAMPLINGRATE_12;
        case 16000:
            return SL_SAMPLINGRATE_16;
        case 22050:
            return SL_SAMPLINGRATE_22_05;
        case 24000:
            return SL_SAMPLINGRATE_24;
        case 32000:
            return SL_SAMPLINGRATE_32;
        default:
            return SL_SAMPLINGRATE_44_1;
    }
}

void convertToSampleFormat(SLAndroidDataFormat_PCM_EX *androidDataFormatPcmEx,
                           const AVCodecParameters *parameters) {

    memset(androidDataFormatPcmEx, 0, sizeof(*androidDataFormatPcmEx));

    androidDataFormatPcmEx->endianness = SL_BYTEORDER_LITTLEENDIAN;
    androidDataFormatPcmEx->formatType = SL_DATAFORMAT_PCM;
    androidDataFormatPcmEx->sampleRate = getSampleRate(parameters->sample_rate);

    if (parameters->channels <= 1) {
        androidDataFormatPcmEx->numChannels = 1;
        androidDataFormatPcmEx->channelMask = SL_SPEAKER_FRONT_LEFT;
    } else {
        androidDataFormatPcmEx->numChannels = 2;
        androidDataFormatPcmEx->channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
    }


    androidDataFormatPcmEx->containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
    androidDataFormatPcmEx->bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;

}

int OpenSLESPlayer::initPlayer(const AVCodecParameters *parameters) {
    //创建引擎接口
    SLresult result = slCreateEngine(&engineItf, 0, NULL, 0, NULL, NULL);
    if (result != SL_BOOLEAN_TRUE) {
        return -1;
    }

//    引擎接口初始化
    result = (*engineItf)->Realize(engineItf, SL_BOOLEAN_FALSE);
    if (result != SL_BOOLEAN_TRUE) {
        return -1;
    }

    //实例化引擎
    result = (*engineItf)->GetInterface(engineItf, SL_IID_ENGINE, &slEngineItf);
    if (result != SL_BOOLEAN_TRUE) {
        return -1;
    }


    //创建混音器
    result = (*slEngineItf)->CreateOutputMix(slEngineItf, &outputMixItf, 0, NULL, NULL);
    if (result != SL_BOOLEAN_TRUE) {
        return -1;
    }

    result = (*outputMixItf)->Realize(outputMixItf, SL_BOOLEAN_FALSE);
    if (result != SL_BOOLEAN_TRUE) {
        return -1;
    }

    //numBuffers=2 这个numBuffers最少要大于1 其中一个用于存储正在播放的数据 其他作为缓存 numBuffers越大 延迟越高
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};


    convertToSampleFormat(&formatPcmEx, parameters);

    SLDataSource dataSource = {&loc_bufq, &formatPcmEx};

    SLDataLocator_OutputMix locatorOutputMix = {SL_DATALOCATOR_OUTPUTMIX, outputMixItf};

    SLDataSink dataSink = {&outputMixItf, NULL};

    SLInterfaceID ids[2] = {SL_IID_BUFFERQUEUE, SL_IID_VOLUME};
    SLboolean req[2] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};

    result = (*slEngineItf)->CreateAudioPlayer(slEngineItf, &playerObjectItf, &dataSource,
                                               &dataSink, 2,
                                               ids, req);

    if (result < 0) {
        LOGE("OpenSLES CreateAudioPlayer failed error code = %d", result);
        return -1;
    }

    result = (*playerObjectItf)->Realize(playerObjectItf, SL_BOOLEAN_FALSE);


    if (result < 0) {
        LOGE("OpenSLES AudioPlayer Realize failed error code = %d", result);
        return -1;
    }


    result = (*playerObjectItf)->GetInterface(playerObjectItf, SL_IID_PLAY, &playItf);

    if (result < 0) {
        LOGE("OpenSLES AudioPlayer Realize failed error code = %d", result);
        return -1;
    }


    result = (*playerObjectItf)->GetInterface(playerObjectItf, SL_IID_BUFFERQUEUE,
                                              &playBufferQueueItf);

    if (result < 0) {
        LOGE("OpenSLES AudioPlayer GetInterface SL_IID_BUFFERQUEUE failed error code = %d", result);
        return -1;
    }


    result = (*playBufferQueueItf)->RegisterCallback(playBufferQueueItf, pcmPlayCallBack, this);

    if (result < 0) {
        LOGE("OpenSLES playBufferQueueItf RegisterCallback failed error code = %d", result);
        return -1;
    }


    result = (*playItf)->SetPlayState(playItf, SL_PLAYSTATE_STOPPED);

    if (result < 0) {
        LOGE("OpenSLES playItf SetPlayState SL_PLAYSTATE_STOPPED failed error code = %d", result);
        return -1;
    }


    return 0;

}


int OpenSLESPlayer::start() {

    SLuint32 state;

    SLresult result = (*playItf)->GetPlayState(playItf, &state);

    if (result != SL_RESULT_SUCCESS) {
        return -1;
    }

    if (state == SL_PLAYSTATE_PLAYING) {
        return 0;
    }

    result = (*playItf)->SetPlayState(playItf, SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS) {
        return -1;
    }


    return 0;
}

int OpenSLESPlayer::stop() {

    SLuint32 state;

    SLresult result = (*playItf)->GetPlayState(playItf, &state);

    if (result != SL_RESULT_SUCCESS) {
        return -1;
    }

    if (state == SL_PLAYSTATE_STOPPED) {
        return 0;
    }

    result = (*playItf)->SetPlayState(playItf, SL_PLAYSTATE_STOPPED);
    if (result != SL_RESULT_SUCCESS) {
        return -1;
    }


    return 0;
}

int OpenSLESPlayer::setVolume(float left, float right) {
    return 0;
}

int OpenSLESPlayer::pause() {

    return 0;
}


int OpenSLESPlayer::enqueueData(void *buf, int size) {


    return 0;
}


