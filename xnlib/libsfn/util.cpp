/*
 * libsfn/util.c
 *
 * Copyright (C) 2020 bzt (bztsrc@gitlab)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * @brief Utility functions
 *
 */

#include <stdlib.h>
#include <ssfn.h>

/**
 * Convert hex string to binary number. Use this lightning fast implementation
 * instead of the unbeliveably crap, slower than a pregnant snail sscanf...
 */
unsigned int gethex(char *ptr, int len)
{
    unsigned int ret = 0;
    for(;len--;ptr++) {
        if(*ptr>='0' && *ptr<='9') {          ret <<= 4; ret += (unsigned int)(*ptr-'0'); }
        else if(*ptr >= 'a' && *ptr <= 'f') { ret <<= 4; ret += (unsigned int)(*ptr-'a'+10); }
        else if(*ptr >= 'A' && *ptr <= 'F') { ret <<= 4; ret += (unsigned int)(*ptr-'A'+10); }
        else break;
    }
    return ret;
}

/**
 * Turn a decimal or hex string into binary number
 */
unsigned int getnum(char *s)
{
    if(!s || !*s) return 0;
    if(*s=='\'') { s++; return ssfn_utf8(&s); }
    if((*s=='0' && s[1]=='x') || (*s=='U' && s[1]=='+')) return gethex(s+2,8);
    return atoi(s);
}

/**
 * Encode run-length bytes
 */
unsigned char *rle_enc(unsigned char *inbuff, int inlen, int *outlen)
{
    int i, k, l, o;
    unsigned char *outbuff;

    if(!inbuff || inlen < 1 || !outlen) return NULL;

    /* allocate memory for the worst case scenario */
    outbuff = (unsigned char *)realloc(NULL, 2 * inlen + 1);
    if(!outbuff) return NULL;

    k = o = 0; outbuff[o++] = 0;
    for(i = 0; i < inlen; i++) {
        for(l = 1; l < 128 && i + l < inlen && inbuff[i] == inbuff[i + l]; l++);
        if(l > 1) {
            l--; if(outbuff[k]) { outbuff[k]--; outbuff[o++] = 0x80 | l; } else outbuff[k] = 0x80 | l;
            outbuff[o++] = inbuff[i]; k = o; outbuff[o++] = 0; i += l; continue;
        }
        outbuff[k]++; outbuff[o++] = inbuff[i];
        if(outbuff[k] > 127) { outbuff[k]--; k = o; outbuff[o++] = 0; }
    }
    if(!(outbuff[k] & 0x80)) { if(outbuff[k]) outbuff[k]--; else o--; }
    *outlen = o;
    outbuff = (unsigned char *)realloc(outbuff, o);
    return outbuff;
}

/**
 * Decode run-length encoded bytes
 */
unsigned char *rle_dec(unsigned char *inbuff, int inlen, int *outlen)
{
    int l, o = 0, s = 0;
    unsigned char *end = inbuff + inlen, *outbuff = NULL;

    if(!inbuff || inlen < 2 || !outlen) return NULL;

    if(*outlen) {
        s = *outlen;
        outbuff = (unsigned char*)realloc(outbuff, s);
        if(!outbuff) return NULL;
    }
    while(inbuff < end) {
        l = ((*inbuff++) & 0x7F) + 1;
        /* if we don't know the required buffer size in advance, allocate memory in 4k blocks */
        if(o + l + 1 > s) {
            s += 4096;
            outbuff = (unsigned char*)realloc(outbuff, s);
            if(!outbuff) return NULL;
        }
        if(inbuff[-1] & 0x80) {
            while(l--) outbuff[o++] = *inbuff;
            inbuff++;
        } else while(l--) outbuff[o++] = *inbuff++;
    }
    *outlen = o;
    outbuff = (unsigned char *)realloc(outbuff, o);
    return outbuff;
}

/**
 * Check if a row is background color only
 */
int isempty(int len, unsigned char *data)
{
    int i;
    if(!data || len < 1) return 1;
    for(i = 0; i < len; i++)
        if(data[i] != 0xFF) return 0;
    return 1;
}
