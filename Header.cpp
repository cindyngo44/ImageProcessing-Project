//
// Created by Cindy Ngo on 7/12/20.
//
#include "Header.h"
#include <fstream>

Header::Header() {

}
Header::Header(char &_idLength, char &_colorMapType, char &_dataTypeCode, short &_colorMapOrigin, short &_colorMapLength,
               char &_colorMapDepth, short &_xOrigin, short &_yOrigin, short &_width, short &_height, char &_bitsPerPixel,
               char &_imageDescriptor, vector<Pixels> &_pixelVector) {

    idLength = _idLength;
    colorMapType = _colorMapType;
    dataTypeCode = _dataTypeCode;
    colorMapOrigin = _colorMapOrigin;
    colorMapLength = _colorMapLength;
    colorMapDepth = _colorMapDepth;
    xOrigin = _xOrigin;
    yOrigin = _yOrigin;
    width = _width;
    height = _height;
    bitsPerPixel = _bitsPerPixel;
    imageDescriptor = _imageDescriptor;
    pixelVector = _pixelVector;

}
void Header::readTGA(string fileName, Header &header){
    ifstream TGAfile(fileName, ios_base:: in | ios_base::binary);
    //reading header order: 1,1,1,2,2,1,2,2,2,2,1,1,
    if(TGAfile.is_open()) {
        TGAfile.read((char *) &idLength, 1);
        TGAfile.read((char *) &colorMapType, 1);
        TGAfile.read((char *) &dataTypeCode, 1);
        TGAfile.read((char *) &colorMapOrigin, 2);
        TGAfile.read((char *) &colorMapLength, 2);
        TGAfile.read((char *) &colorMapDepth, 1);
        TGAfile.read((char *) &xOrigin, 2);
        TGAfile.read((char *) &yOrigin, 2);
        TGAfile.read((char *) &width, 2);
        TGAfile.read((char *) &height, 2);
        TGAfile.read((char *) &bitsPerPixel, 1);
        TGAfile.read((char *) &imageDescriptor, 1);

        //pixel variables
        Pixels pixelObj;
        int imgDimensions = width * height;

        for (int i = 0; i < imgDimensions; i++) {
            TGAfile.read((char *) &pixelObj.blue, 1);
            TGAfile.read((char *) &pixelObj.green, 1);
            TGAfile.read((char *) &pixelObj.red, 1);

            pixelVector.push_back(pixelObj);
        }
    }
}
void Header::PrintAll() {
        cout << "ID Length: " << idLength << endl;
        cout << "Color Map Type: " << colorMapType << endl;
        cout << "Data type code: " << dataTypeCode << endl;
        cout << "Color Map Origin: " << colorMapOrigin << endl;
        cout << "Color Map Length: " << colorMapLength << endl;
        cout << "Color Map Drigin: " << colorMapDepth << endl;
        cout << "X Origin: " << xOrigin << endl;
        cout << "Y Origin: " << yOrigin << endl;
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Bits per pixel: " << bitsPerPixel << endl;
        cout << "Image Descriptor: " << imageDescriptor << endl;
}

void Header::writeTGA(string fileName, Header &header) {
    vector<Pixels> finalPixelVector = header.pixelVector;

    ofstream TGAfile(fileName, ios_base::out | ios_base::binary);
    //writing header order: 1,1,1,2,2,1,2,2,2,2,1,1,
    if (TGAfile.is_open()) {
        TGAfile.write((char *) &header.idLength, 1);
        TGAfile.write((char *) &header.colorMapType, 1);
        TGAfile.write((char *) &header.dataTypeCode, 1);
        TGAfile.write((char *) &header.colorMapOrigin, 2);
        TGAfile.write((char *) &header.colorMapLength, 2);
        TGAfile.write((char *) &header.colorMapDepth, 1);
        TGAfile.write((char *) &header.xOrigin, 2);
        TGAfile.write((char *) &header.yOrigin, 2);
        TGAfile.write((char *) &header.width, 2);
        TGAfile.write((char *) &header.height, 2);
        TGAfile.write((char *) &header.bitsPerPixel, 1);
        TGAfile.write((char *) &header.imageDescriptor, 1);

        int imgDimensions = header.height * header.width;

        for ( int i = 0; i < imgDimensions; i++) {
            TGAfile.write((char *) &finalPixelVector[i].blue, 1);
            TGAfile.write((char *) &finalPixelVector[i].green, 1);
            TGAfile.write((char *) &finalPixelVector[i].red, 1);
        }
    }

}

Header::Pixels::Pixels() {
}

Header::Pixels::Pixels(unsigned char _red, unsigned char _green, unsigned char _blue) {
    red = _red;
    green = _green;
    blue = _blue;
}
