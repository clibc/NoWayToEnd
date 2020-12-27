#pragma once
#include <iostream>

#pragma pack(push, 1)
struct bmp_header
{
    unsigned char id[2];
    uint32_t file_size;
    int unused;
    uint32_t pixel_data_offset;
};
#pragma pack(pop)

// NOTE(62bit): Memory layout BB GG RR AA
// TODO(62bit): load file upside down so pixels get aligned correctly !!
struct bmp_image
{
    int width;
    int height;
    unsigned char *pixel_data;
};

static bmp_image *load_bmp_file(const char *file_path)
{
    FILE *file;
    long file_size;
    unsigned char *file_buffer;
    bmp_header header;
    bmp_image *image;
    unsigned char *pixel_data;
    file = fopen(file_path, "r");
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    if (file == NULL)
        return NULL;

    file_buffer = (unsigned char *)malloc(file_size);
    fread(file_buffer, sizeof(char), file_size, file);

    // TODO(62bit): Receive an image pointer, so we may prevent heap allocation
    image = (bmp_image *)malloc(sizeof(bmp_image));
    memcpy(&header, file_buffer, sizeof(bmp_header));
    memcpy(&image->width, file_buffer + 0x12, sizeof(uint32_t));
    memcpy(&image->height, file_buffer + 0x16, sizeof(uint32_t));

    pixel_data = (unsigned char *)malloc((image->width * image->height) * 4);
    memcpy(pixel_data, file_buffer + header.pixel_data_offset, (image->width * image->height) * 4);

    image->pixel_data = pixel_data;

    free(file_buffer);
    fclose(file);
    return image;
}
