//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"


bool Image::load(string filename) {
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);
    // need to spec. binary mode for Windows users
    try {
        if (ifs.fail()) {
            throw ("Can't open input file");
        }
        std::string header;
        int w, h, b;
        ifs >> header;
        if (strcmp(header.c_str(), "P6") != 0) throw ("Can't read input file");
        ifs >> w >> h >> b;
        this->w = w;
        this->h = h;
        this->pixels = new Rgb[w * h]; // this is throw an exception if bad_alloc
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
        unsigned char pix[3]; // read each pixel one by one and convert bytes to floats
        for (int i = 0; i < w * h; ++i) {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
        }
        ifs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ifs.close();
        return false;
    }

    return true;
}

bool Image::loadRaw(string filename) {


    return false;
}

bool Image::savePPM(string filename) {
    std::ofstream ofs;
    ofs.open(filename, std::ios::binary);

    if (ofs.fail()) { return false;}

    ofs << "P6\n" << this->w << " " << this->h << "\n255\n";

    unsigned char r, g, b;

    for (int i = 0; i < this->w * this->h; ++i) {
        r = this->pixels[i].r;
        g = this->pixels[i].g;
        b = this->pixels[i].b;

        ofs << r << g << b;
    }

    ofs.close();

    return true;
}


void Image::filterRed() {

}

void Image::filterGreen() {

}

void Image::filterBlue() {

}

void Image::greyScale() {
    for (int c = 0; c < w * h; c++) {
        int greyscale = (0.2126 * this->pixels[c].r + 0.7152 * this->pixels[c].g + 0.0722 * this->pixels[c].b);

        this->pixels[c].b = greyscale;
        this->pixels[c].g = greyscale;
        this->pixels[c].r = greyscale;
    }
}

void Image::flipHorizontal() {


}

void Image::flipVertically() {


}

void Image::AdditionalFunction2() {

}

void Image::AdditionalFunction3() {

}

void Image::AdditionalFunction1() {

}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth() {
    return w;
}

int Image::getHeight() {
    return h;
}

Rgb *Image::getImage() {
    return pixels;
}