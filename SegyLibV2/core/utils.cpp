#include "utils.h"
#include <cfloat>
#include <cstring>
#include <cmath>

int getFormatSize(Format format){
    static const int formatSize[]={0,4,4,2,4,4,0,0,1,8};
    return formatSize[static_cast<int>(format)];
}

void revert(byte* buf,int length){
    byte tbyte;
    for(int i=0;i<length/2;++i){
        tbyte=buf[i];
        buf[i]=buf[length-1-i];
        buf[length-1-i]=tbyte;
    }
}

bool isPositiveInt(const byte *buf,int length,Endian endian=currentEndian){
    const byte *c;

    if(endian==Endian::ENDIAN_LITTLE) c=buf+length-1;
    else c=buf;

    if(*c>>7) return false;

    return true;
}

int bytesToSignedInt(const byte *buf,size_t length,Endian endian){
    int res=0;

    if(length>sizeof(int))return res;

    if(isPositiveInt(buf,length,endian))res=0;
    else res=-1;

    byte *resByte=(byte*)&res;

    if(currentEndian==Endian::ENDIAN_LITTLE){
        if(currentEndian==endian){
            memcpy((void*)&res,buf,length);
        }else{
            for(size_t i=0;i<length;++i)
                resByte[i]=buf[length-1-i];
        }
    }else{
        if(currentEndian==Endian::ENDIAN_BIG){
            memcpy(resByte+(sizeof(int)-length),buf,length);
        }else{
            for(size_t i=0;i<length;++i)
                resByte[sizeof(int)-length+i]=buf[length-1-i];
        }
    }
    return res;
}

double bytesToDoubleFromIBM(const byte *buf,Endian endian){
    typedef unsigned int ulng;

    int swap=0;
    if(endian!=currentEndian)swap=1;

    byte tbuf[4];
    memcpy(tbuf,buf,4);
    float* input=(float*)tbuf;

    byte  *cbuf,expp,tem,sign;
    ulng  *umantis,expll;
    int *mantis;
    int  shift;

    cbuf=(byte*)&input[0];        /* assign address of input to char array */
    umantis=(ulng*)&input[0];     /* two differnt points to the same spot  */
    mantis =(int*)&input[0];     /* signned & unsigned                    */

    if(swap)
    {
        /* now byte reverce for PC use if swap true */
        tem=cbuf[0]; cbuf[0]=cbuf[3]; cbuf[3]=tem;
        tem=cbuf[2]; cbuf[2]=cbuf[1]; cbuf[1]=tem;
    }

    /* start extraction information from number */

    expp=*mantis>>24;     /* get expo fro upper byte      */
    *mantis=(*mantis)<<8; /* shift off upper byte         */
    shift=1;              /* set a counter to 1           */
    while(*mantis>0 && shift<23) /* start of shifting data*/
    {
        *mantis=*mantis<<1;
        shift++;
    } /* shift until a 1 in msb */

    *mantis=*mantis<<1; /* need one more shift to get implied one bit */
    sign=expp & 0x80;   /* set sign to msb of exponent            */
    expp=expp & 0x7F;   /* kill sign bit                          */

    if(expp!=0)        /* don't do anymore if zero exponent       */
    {
        expp=expp-64;   /* compute what shift was (old exponent)*/
        *umantis=*umantis>>9; /* MOST IMPORTANT an UNSIGNED shift back down */
        expll=0x7F+(expp*4-shift); /* add in excess 172 */

        /* now mantissa is correctly aligned, now create the other two pairs */
        /* needed the extended sign word and the exponent word               */

        expll=expll<<23;        /* shift exponent up */

        /* combine them into a floating point IEEE format !     */

        if(sign) *umantis=expll | *mantis | 0x80000000;
        else     *umantis=expll | *mantis; /* set or don't set sign bit */
    }
    return *input;
}

double bytesToDoubleFrom4IEEE(const byte *buf,Endian endian){
    float res;
    memcpy(&res,buf,4);
    if(endian!=currentEndian) revert((byte*)&res,4);
    return res;
}

double bytesToDoubleFrom8IEEE(const byte *buf, Endian endian)
{
    double res;
    memcpy(&res,buf,8);
    if(endian!=currentEndian) revert((byte*)&res,8);
    return res;
}

double bytesToDoubleFrom4FixedPoint(const byte* buf,Endian endian) {
    int ires=*(int*)buf;
    if(endian!=currentEndian) revert((byte*)&ires,4);
    double res=ires;
    res=res/double(1<<16);
    return res;
}

double bytesToDouble(const byte *buf,Format format,Endian endian){
    switch(format){
        case Format::FORMAT_IBM:
            return bytesToDoubleFromIBM(buf,endian);
        case Format::FORMAT_4IEEE:
            return bytesToDoubleFrom4IEEE(buf,endian);
        case Format::FORMAT_4INT:
        case Format::FORMAT_2INT:
        case Format::FORMAT_1INT:
            return bytesToSignedInt(buf,getFormatSize(format),endian);
        case Format::FORMAT_4FIXEDPOINT:
            return bytesToDoubleFrom4FixedPoint(buf,endian);
        case Format::FORMAT_8IEEE:
            return bytesToDoubleFrom8IEEE(buf,endian);
        default:
            return bytesToDoubleFromIBM(buf,endian);
    }
}

template<class T>
T min(T a, T b){
	if (a < b)return a;
	return b;
}

void intToBytesSignedInt(const int num,byte* out,int length,Endian endian){
	for (int i = 0; i < length; ++i)out[i] = 0;
    int inum=num;
	if (inum < 0)for (int i = 0; i < length; ++i)out[i] = 255;
    byte* bytes=(byte*)&inum;

    if(currentEndian==Endian::ENDIAN_BIG && endian==Endian::ENDIAN_BIG)
        for(int i=0;i<min(length,(int)sizeof(inum));++i)out[length-1-i]=bytes[sizeof(inum)-1-i];
    if(currentEndian==Endian::ENDIAN_BIG && endian==Endian::ENDIAN_LITTLE)
        for(int i=0;i<min(length,(int)sizeof(inum));++i)out[i]=bytes[sizeof(inum)-1-i];
    if(currentEndian==Endian::ENDIAN_LITTLE && endian==Endian::ENDIAN_BIG)
        for(int i=0;i<min(length,(int)sizeof(inum));++i)out[length-1-i]=bytes[i];
    if(currentEndian==Endian::ENDIAN_LITTLE && endian==Endian::ENDIAN_LITTLE)
        for(int i=0;i<min(length,(int)sizeof(inum));++i)out[i]=bytes[i];
}

void doubleToBytesSignedInt(const double num,byte* out,int length,Endian endian){
    intToBytesSignedInt(num,out,length,endian);
}

void doubleToBytesIBM(const double num,byte* out,Endian endian){

    float fnum=num;
	if (fnum < FLT_MIN && (-fnum)<FLT_MIN)fnum = 0;
	if (fnum > FLT_MAX)fnum = FLT_MAX;
	if (fnum < -FLT_MAX)fnum = -FLT_MAX;
	if (!(fnum == fnum)) fnum = 0;

    unsigned fr; /* fraction */
    int exp; /* exponent */
    int sgn; /* sign */
    /* split into sign, exponent, and fraction */
    fr = *((unsigned *)&fnum); /* pick up value */
    sgn = fr >> 31; /* save sign */
    fr <<= 1; /* shift sign out */
    exp = fr >> 24; /* save exponent */
    fr <<= 8; /* shift exponent out */

    if (exp == 255) { /* infinity (or NAN) - map to largest */
        fr = 0xffffff00;
        exp = 0x7f;
        goto done;
    }
    else if (exp > 0) /* add assumed digit */
        fr = (fr >> 1) | 0x80000000;
    else if (fr == 0) /* short-circuit for zero */
        goto done;

    /* adjust exponent from base 2 offset 127 radix point after first digit
    to base 16 offset 64 radix point before first digit */
    exp += 130;
    fr >>= -exp & 3;
    exp = (exp + 3) >> 2;

/* (re)normalize */
    while (fr < 0x10000000) { /* never executed for normalized input */
        --exp;
        fr <<= 4;
    }

done:
    /* put the pieces back together and return it */
    fr = (fr >> 8) | (exp << 24) | (sgn << 31);
    if(endian!=currentEndian)revert((byte*)&fr,4);
    *(unsigned *)out = fr;
}

void doubleToBytes4IEEE(const double num,byte* out,Endian endian){
    float fnum=num;
	if (fnum < FLT_MIN && (-fnum)<FLT_MIN)fnum = 0;
	if (fnum > FLT_MAX)fnum = FLT_MAX;
	if (fnum < -FLT_MAX)fnum = -FLT_MAX;
	if (!(fnum == fnum)) fnum = 0;
    byte *b=(byte*)&fnum;
    if(endian!=currentEndian)
        for(int i=0;i<4;++i) out[i]=b[3-i];
    else
        for(int i=0;i<4;++i) out[i]=b[i];
}

void doubleToBytes8IEEE(const double num,byte* out,Endian endian){
    double f=num;
    byte *b=(byte*)&f;
    if(endian!=currentEndian)
        for(int i=0;i<8;++i) out[i]=b[7-i];
    else
        for(int i=0;i<8;++i) out[i]=b[i];
}

void doubleToBytes4FixedPoint(const double num,byte* out,Endian endian){
    float fnum=num;
    *(int*)out=(int)(fnum * 65536.0f);
    if(endian!=currentEndian)revert(out,4);
}

void doubleToBytes(const double num,byte* out,Format format,Endian endian){

    switch(format){
        case Format::FORMAT_IBM:
            doubleToBytesIBM(num,out,endian);
            break;
        case Format::FORMAT_4IEEE:
            doubleToBytes4IEEE(num,out,endian);
            break;
        case Format::FORMAT_8IEEE:
            doubleToBytes8IEEE(num,out,endian);
            break;
        case Format::FORMAT_4INT:
            doubleToBytesSignedInt(num,out,4,endian);
            break;
        case Format::FORMAT_2INT:
            doubleToBytesSignedInt(num,out,2,endian);
            break;
        case Format::FORMAT_1INT:
            doubleToBytesSignedInt(num,out,1,endian);
            break;
        case Format::FORMAT_4FIXEDPOINT:
            doubleToBytes4FixedPoint(num,out,endian);
            break;
        default:
            doubleToBytesIBM(num,out,endian);
            break;
    }
}

static const unsigned char e2a[256] = {
          0,  1,  2,  3,156,  9,134,127,151,141,142, 11, 12, 13, 14, 15,
         16, 17, 18, 19,157,133,  8,135, 24, 25,146,143, 28, 29, 30, 31,
        128,129,130,131,132, 10, 23, 27,136,137,138,139,140,  5,  6,  7,
        144,145, 22,147,148,149,150,  4,152,153,154,155, 20, 21,158, 26,
         32,160,161,162,163,164,165,166,167,168, 91, 46, 60, 40, 43, 33,
         38,169,170,171,172,173,174,175,176,177, 93, 36, 42, 41, 59, 94,
         45, 47,178,179,180,181,182,183,184,185,124, 44, 37, 95, 62, 63,
        186,187,188,189,190,191,192,193,194, 96, 58, 35, 64, 39, 61, 34,
        195, 97, 98, 99,100,101,102,103,104,105,196,197,198,199,200,201,
        202,106,107,108,109,110,111,112,113,114,203,204,205,206,207,208,
        209,126,115,116,117,118,119,120,121,122,210,211,212,213,214,215,
        216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,
        123, 65, 66, 67, 68, 69, 70, 71, 72, 73,232,233,234,235,236,237,
        125, 74, 75, 76, 77, 78, 79, 80, 81, 82,238,239,240,241,242,243,
         92,159, 83, 84, 85, 86, 87, 88, 89, 90,244,245,246,247,248,249,
         48, 49, 50, 51, 52, 53, 54, 55, 56, 57,250,251,252,253,254,255
};

void ebcdicToAscii (unsigned char *source,unsigned char *dest,size_t length){
    for(size_t i=0;i<length;++i){
        dest[i]=e2a[(int)source[i]];
    }
}

long long perfomSegyTraceCount(long long segySize, int samplePerTrace, int formatSize)
{
    static const int ebcidicHeaderSize=3200;
    static const int lineHeaderSize=400;
    static const int traceHeaderSize=240;
    return (segySize-ebcidicHeaderSize-lineHeaderSize)/(traceHeaderSize+samplePerTrace*formatSize);
}

long long perfomSuTraceCount(long long suSize, int samplePerTrace, int formatSize)
{
    static const int traceHeaderSize=240;
    return (suSize)/(traceHeaderSize+samplePerTrace*formatSize);
}
