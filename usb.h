#ifndef USB_H
#define USB_H

#include <stddef.h>

typedef struct USBDevice USBDevice;
USBDevice* openDevice(char* name);
void closeDevice(USBDevice* device);

size_t readLatestData(USBDevice* device, void* buffer, size_t size);

char getBit(char c, char bit);
void printBits(char c);


#endif