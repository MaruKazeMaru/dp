typedef struct{
    unsigned short channel_size;
    unsigned int sample_per_second;
    unsigned int bit_per_sample;
    unsigned int data_size;
    short** data;
}Wav;

char read_wav(char* file_name, Wav* wav);