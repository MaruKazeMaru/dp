#ifndef _AUDIO_H_
#define _AUDIO_H_

typedef struct{
    unsigned short channel_size;
    unsigned int sample_per_second;
    unsigned int bit_per_sample;
    unsigned int data_size;
    int** data;
}Audio;

#endif