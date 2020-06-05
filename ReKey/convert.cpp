#include <QString>
#include <string>
#include <iostream>
#include "helper.h"


HSV convert(RGB rgb){
    //#rrggbb

    HSV hsv;
    if(rgb.r > 1 || rgb.r < 0 || rgb.g > 1 || rgb.g < 0 ||rgb.b > 1 || rgb.b < 0){
        std::cerr << "ERROR: Cant' assign to hsv (invalid values)\n";
        hsv.H = 0;
        hsv.S = 0;
        hsv.V = 0;
        return hsv;
    }

    float maximum, minimum;
    float r, g ,b;    

    r = rgb.r;
    g = rgb.g;
    b = rgb.b;

    maximum = std::max(b,g);
    maximum = std::max(maximum, r);
    minimum = std::min(b,g);
    minimum = std::max(minimum, r);

    if(maximum == minimum){
        hsv.V = 0;
    } else if(maximum == r){
        if(g >= b){
            hsv.H = 60 * (g - b) / (maximum - minimum) + 0;
        } else {
            hsv.H = 60 * (g - b) / (maximum - minimum) + 360;
        }
    } else if(maximum == g) {
        hsv.H = 60 * (b - r) / (maximum - minimum) + 120;
    } else {
        hsv.H = 60 * (r - g) / (maximum - minimum) + 240;
    }

    if(maximum == 0){
        hsv.S = 0;
    } else {
        hsv.S = 1.0 - (minimum / maximum);
    }

    hsv.V = maximum;

    return hsv;
}

RGB toRGB(QString color){    
    /* #RRGGBB */


    RGB rgb;
    if(color.size() != 7 || color[0] != '#') {
        std::cerr << "ERROR: wrong color format\n";
        rgb.r = 0;
        rgb.g = 0;
        rgb.b = 0;
        return rgb;
    }

    for(auto at: color.toStdString()){

        bool flag = 0;
        switch (at) {

        case '1': flag = 1; break;
        case '2': flag = 1; break;
        case '3': flag = 1; break;
        case '4': flag = 1; break;
        case '5': flag = 1; break;
        case '6': flag = 1; break;
        case '7': flag = 1; break;
        case '8': flag = 1; break;
        case '9': flag = 1; break;
        case '0': flag = 1; break;
        case 'a': flag = 1; break;
        case 'b': flag = 1; break;
        case 'c': flag = 1; break;
        case 'd': flag = 1; break;
        case 'e': flag = 1; break;
        case 'f': flag = 1; break;
        default: flag = 0; break;



        if(!flag){
            std::cerr << "ERROR: wrong color format\n";
            rgb.r = 0;
            rgb.g = 0;
            rgb.b = 0;
            return rgb;
            }
        }
    }


    QString buf;    

    buf = color.mid(1,2);
    rgb.r = (float)stoi(buf.toStdString(), 0, 16) / 255;
    buf = color.mid(3,2);
    rgb.g = (float)stoi(buf.toStdString(), 0, 16) / 255;
    buf = color.mid(5,2);
    rgb.b = (float)stoi(buf.toStdString(), 0, 16) / 255;        

    return rgb;

}
