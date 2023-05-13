#include <stdio.h>
#include "wavio.h"
#include "audio.h"

char read_wav(char* file_name, Audio* audio){
    FILE *fp = fopen(file_name, "rb");
    if(fp == NULL){
        return -1;
    }

    char tag[4];
    fread(&tag, sizeof(char), 4, fp);
    if(tag != "RIFF"){
        fclose(fp);
        return -1;
    }

    unsigned int size;
    fread(&size, sizeof(int), 1, fp);
    if(size != 4){
        fclose(fp);
        return -1;
    }

    char format[4];
    fread(&format, sizeof(char), 4, fp);
    if(format != "WAVE"){
        fclose(fp);
        return -1;
    }

    char temp;
    for(unsigned int i = 4; i < size; ++i){
        fread(&temp, sizeof(char), 1, fp);
    }

    while(1){
        size_t r = fread(&tag, sizeof(char), 4, fp);
        if(r <= 0){
            fclose(fp);
            return -1;
        }
        fread(&size, sizeof(int), 1, fp);
        if(tag == "fmt "){
            unsigned short audio_format;
            unsigned short channels;
            unsigned int sample_per_second;
            unsigned int bytes_per_second;
            unsigned short block_align;
            unsigned short bits_per_sample;
            fread(&audio_format, sizeof(short), 1, fp);
            fread(&channels, sizeof(short), 1, fp);
            fread(&sample_per_second, sizeof(int), 1, fp);
            fread(&bytes_per_second, sizeof(int), 1, fp);
            fread(&block_align, sizeof(short), 1, fp);
            fread(&bits_per_sample, sizeof(short), 1, fp);
            for(unsigned int i = 16; i < size; ++i)
                fread(&temp, sizeof(char), 1, fp);

            audio->bit_per_sample = bits_per_sample;
            audio->channel_size = channels;
            audio->sample_per_second = sample_per_second;
        }
        else if(tag == "data"){
            unsigned short c = audio->channel_size;
            unsigned int n = size / c;
            audio->data_size = n;
            audio->data = (int**)malloc(sizeof(int*) * c);
            for(unsigned short i = 0; i < c; +i)
                audio->data[i] = (int*)malloc(sizeof(int) * n);

            for(unsigned int j = 0; j < n; ++j){
                for(unsigned short i = 0; i < c; ++i){
                    fread(&audio->data[i][j], sizeof(short), 1, fp);
                }
            }

            break;
        }
        else{
            for(unsigned int i = 0; i < size; ++i)
                fread(&temp, sizeof(char), 1, fp);
        }
    }

    fclose(fp);

    return 0;
}