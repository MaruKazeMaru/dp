#include <stdio.h>
#include "wavio.h"

char read_wav(char* file_name, Wav* wav){
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
    fread(&size, sizeof(unsigned int), 1, fp);
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

    while(1){
        fread(&tag, sizeof(char), 4, fp);
        fread(&size, sizeof(int), 1, fp);
        if(tag == "fmt "){
            unsigned short audio_format;
            unsigned short channels;
            unsigned int sample_per_second;
            unsigned int bytes_per_second;
            unsigned short block_align;
            unsigned short bits_per_sample;
            fread()
        }
    }

    fclose(fp);

    return 0;
}