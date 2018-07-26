#ifndef UTILS_H
#define UTILS_H

#include "types.h"

int getFormatSize(Format format);

bool isPositiveInt(const byte *buf,int length,Endian endian);

int bytesToSignedInt(const byte *buf, size_t length, Endian endian=currentEndian);

double bytesToDoubleFromIBM(const byte *buf,Endian endian);

double bytesToDoubleFrom4IEEE(const byte *buf,Endian endian);

double bytesToDoubleFrom8IEEE(const byte *buf,Endian endian);

double bytesToDoubleFrom4FixedPoint(const byte* buf,Endian endian);

double bytesToDouble(const byte *buf,Format format,Endian endian);

void doubleToBytesSignedInt(const double num,byte* out,int length,Endian endian=currentEndian);
void intToBytesSignedInt(const int num,byte* out,int length,Endian endian=currentEndian);

void doubleToBytesIBM(const double num,byte* out,Endian endian);
void doubleToBytes4IEEE(const double num,byte* out,Endian endian);
void doubleToBytes8IEEE(const double num,byte* out,Endian endian);
void doubleToBytes4FixedPoint(const double num,byte* out,Endian endian);
void doubleToBytes(const double num,byte* out,Format format,Endian endian);

void ebcdicToAscii (unsigned char *source,unsigned char *dest,size_t length);
void asciiToEbcidic(unsigned char* source, unsigned char* dest,size_t length);

long long perfomSegyTraceCount(long long segySize, int samplePerTrace, int formatSize);
long long perfomSuTraceCount(long long suSize, int samplePerTrace, int formatSize);

#endif // UTILS_H
