#include "usb.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

USBDevice* openDevice(char* name) {
    char* base = "/dev/hidraw";
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

    //freopen(device->path, "r", device->file);
    free(device);
}

#include <time.h>

void readLatestData(USBDevice* device, void* buffer, size_t size) {
    struct timespec start;
    struct timespec end;

    clock_gettime(0, &start);
    fread(buffer, 9, 1, device->file);
    clock_gettime(0, &end);

    printf("%ld\n", (end.tv_nsec - start.tv_nsec) / 1000000);
}

void printBits(char c) {
    for(char i = 0; i < 8; ++i) {
        char bit = (c >> (7 - i)) & 0x1;
        printf("%d", bit);
    }
}