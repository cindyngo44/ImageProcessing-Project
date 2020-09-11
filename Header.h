//
// Created by Cindy Ngo on 7/12/20.
//
#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Header{
    struct Pixels{
        unsigned char blue;
        unsigned char green;
        unsigned char red;

        Pixels();
        Pixels(unsigned char _red, unsigned char _green, unsigned char _blue);
    };
    char  idLength;
    char  colorMapType;
    char  dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char  colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char  bitsPerPixel;
    char  imageDescriptor;
    vector<Pixels> pixelVector;

    Header();
    Header(char &_idLength, char &_colorMapType, char &_dataTypeCode, short &_colorMapOrigin, short &_colorMapLength,
           char &_colorMapDepth, short &_xOrigin, short &_yOrigin, short &_width, short &_height, char &_bitsPerPixel,
           char &_imageDescriptor, vector<Pixels> &_pixelVector);

    void readTGA(string fileName, Header &header);
    void writeTGA(string fileName, Header &header);
    void PrintAll();
};