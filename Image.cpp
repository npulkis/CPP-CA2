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

    if (ofs.fail()) { return false; }

    ofs << "P6\n" << w << " " << h << "\n255\n";

    unsigned char r, g, b;

    for (int i = 0; i < w * h; ++i) {
        r = pixels[i].r;
        g = pixels[i].g;
        b = pixels[i].b;

        ofs << r << g << b;
    }

    ofs.close();

    return true;
}


void Image::filterRed() {

    for (int i = 0; i < w*h; ++i) {
        pixels[i].b=0;
        pixels[i].g=0;
    }
}

void Image::filterGreen() {

    for (int i = 0; i < w*h; ++i) {
        pixels[i].b=0;
        pixels[i].r=0;
    }

}

void Image::filterBlue() {

    for (int i = 0; i < w*h; ++i) {
        pixels[i].r=0;
        pixels[i].g=0;
    }

}

void Image::greyScale() {
    for (int i = 0; i < w * h; i++) {
        int greyscale = (0.2126 * pixels[i].r + 0.7152 * pixels[i].g + 0.0722 * pixels[i].b);

        pixels[i].b = greyscale;
        pixels[i].g = greyscale;
        pixels[i].r = greyscale;
    }
}

void Image::flipHorizontal() {

    int px1;
    int px2;
    int tempPixel[3];

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w / 2; ++x) {

            px1 = x + y * w;
            px2 = (w - 1 - x) + y * w;

            tempPixel[0] = pixels[px1].r;
            tempPixel[1] = pixels[px1].g;
            tempPixel[2] = pixels[px1].b;

            pixels[px1].r = pixels[px2].r;
            pixels[px1].g = pixels[px2].g;
            pixels[px1].b = pixels[px2].b;

            pixels[px2].r = tempPixel[0];
            pixels[px2].g = tempPixel[1];
            pixels[px2].b = tempPixel[2];

        }
    }

}

void Image::flipVertically() {

    int px1;
    int px2;
    int tempPixel[3];

    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h / 2; ++y) {

            px1 = x + y * w;
            px2 = x + (h - 1 - y) * w;

            tempPixel[0] = pixels[px1].r;
            tempPixel[1] = pixels[px1].g;
            tempPixel[2] = pixels[px1].b;

            pixels[px1].r = pixels[px2].r;
            pixels[px1].g = pixels[px2].g;
            pixels[px1].b = pixels[px2].b;

            pixels[px2].r = tempPixel[0];
            pixels[px2].g = tempPixel[1];
            pixels[px2].b = tempPixel[2];

        }
    }
}

void Image::AdditionalFunction2() {

}

void Image::AdditionalFunction3() {

}

void Image::AdditionalFunction1() {

    //Invert pixels

    for (int i = 0; i < w*h; ++i) {
        pixels[i].r = 255 - pixels[i].r;
        pixels[i].g = 255 - pixels[i].g;
        pixels[i].b = 255 - pixels[i].b;
    }

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