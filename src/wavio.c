#include <stdio.h>
#include <stdlib.h>

#include <wavio.h>
#include <audio.h>

char compare(int length, char* a, char* b){
    for(int i = 0; i < length; ++i)
        if(a[i] != b[i])
            return -1;
    return 1;
}

Audio read_wav(char* file_name, char* has_err, char** err_msg){
    *has_err = 0;

    FILE *fp = fopen(file_name, "rb");
    if(fp == NULL){
        *has_err = 1;
        *err_msg = "no file";
        return;
    }

    char tag[4];
    fread(&tag, sizeof(char), 4, fp);
    if(!compare(4, tag, "RIFF")){
        fclose(fp);
        //printf("tag=%s\n", tag);
        *has_err = 1;
        *err_msg = "tag is not RIFF";
        return;
    }

    unsigned int size;
    fread(&size, sizeof(int), 1, fp);
    unsigned int file_size = size;
    /*
    if(size != 4){
        fclose(fp);
        printf("size=%u=%x\n", size, size);
        return -3;
    }
    */

    char format[4];
    fread(&format, sizeof(char), 4, fp);
    if(!compare(4, format, "WAVE")){
        fclose(fp);
        *has_err = 1;
        *err_msg = "format is not WAVE";
        return;
    }

    char temp;
    /*
    for(unsigned int i = 4; i < size; ++i){
        fread(&temp, sizeof(char), 1, fp);
    }
    */

   char read_fmt = 0;
   char read_data = 0;
   Audio audio;

    for(unsigned int k = 0; k < file_size; k += 8){
        size_t r = fread(&tag, sizeof(char), 4, fp);
        fread(&size, sizeof(int), 1, fp);

        if(!read_fmt && compare(4, tag, "fmt ")){
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

            audio.bit_per_sample = bits_per_sample;
            audio.channel_size = channels;
            audio.sample_per_second = sample_per_second;

            read_fmt = 1;
        }
        else if(!read_data && compare(4, tag, "data")){
            unsigned short c = audio.channel_size;
            unsigned int n = size / (sizeof(short) * c);
            audio.data_size = n;
            audio.data = (int**)malloc(sizeof(int*) * c);
            for(unsigned short i = 0; i < c; ++i)
                audio.data[i] = (int*)malloc(sizeof(int) * n);

            short d;
            for(unsigned int j = 0; j < n; ++j){
                for(unsigned short i = 0; i < c; ++i){
                    fread(&d, sizeof(short), 1, fp);
                    audio.data[i][j] = (int)d;
                }
            }

            read_data = 1;
            break;
        }
        else{
            for(unsigned int i = 0; i < size; ++i)
                fread(&temp, sizeof(char), 1, fp);
        }

        k += size;
    }

    fclose(fp);

    if(read_fmt && read_data)
        return audio;
    else if(!read_fmt){
        *has_err = 1;
        *err_msg = "no fmt chunk";
        return;
    }
    else{
        *has_err = 1;
        *err_msg = "no data chunk";
    }
}