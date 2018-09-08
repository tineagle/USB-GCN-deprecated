#ifndef USB_H
#define USB_H

#include <stddef.h>
#include <stdio.h>

typedef struct USBDevice {
    char* path;
    FILE* file;
} USBDevice;

USBDevice* openDevice(char* name);
void closeDevice(USBDevice* device);

void readLatestData(USBDevice* device, void* buffer, size_t size);

char getBit(char c, char bit);
void printBits(char c);


#endif