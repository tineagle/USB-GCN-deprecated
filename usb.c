#include "usb.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct USBDevice {
    char* path;
    FILE* file;
};

USBDevice* openDevice(char* name) {
    char* base = "/dev/";
    size_t totalLen = strlen(base) + strlen(name);

    char* fullName = malloc(totalLen + 1);
    fullName[0] = '\0';

    strcat(fullName, base);
    strcat(fullName, name);

    FILE* file = fopen(fullName, "r");
    if(file == NULL) {
        free(fullName);
        return NULL;
    }

    USBDevice* device = malloc(sizeof(USBDevice));
    device->file = file;
    device->path = fullName;

    return device;
}

void closeDevice(USBDevice* device) {
    if(device == NULL) {
        return;
    }

    fclose(device->file);
    free(device->path);
    free(device);
}

size_t readLatestData(USBDevice* device, void* buffer, size_t size) {
    fseek(device->file, -size, SEEK_END);
    return fread(buffer, size, 1, device->file);
}

void printBits(char c) {
    for(char i = 0; i < 8; ++i) {
        char bit = (c >> (7 - i)) & 0x1;
        printf("%d", bit);
    }
}