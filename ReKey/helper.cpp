#include <QColor>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <iostream>
#include <string>
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/core.hpp"
//#include "opencv2/videoio.hpp"
#include "helper.h"

#include </usr/local/include/opencv4/opencv2/imgproc.hpp>
#include </usr/local/include/opencv4/opencv2/imgcodecs.hpp>
#include </usr/local/include/opencv4/opencv2/core.hpp>
#include </usr/local/include/opencv4/opencv2/videoio.hpp>

using namespace cv;

Video vid;

bool load(QString path){

    vid.path = path;

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        std::cerr << "No such file found\n";
        return false;
    }
    file.close();

    if(vid.capture.isOpened()){
        vid.capture.release();
    }

    if(!(bool)vid.capture.open(path.toStdString())){
        std::cerr << "Cant open video file\n";
        return false;
    }

    vid.totalFrames = vid.capture.get(CAP_PROP_FRAME_COUNT);
    vid.fps = vid.capture.get(CAP_PROP_FPS);
    vid.height = vid.capture.get(CAP_PROP_FRAME_HEIGHT);
    vid.width = vid.capture.get(CAP_PROP_FRAME_WIDTH);

    Mat image;
    image = imread((const std::string)"../ReKey/template.jpg", IMREAD_COLOR);
    if(image.empty()){
        return false;
    }

    imwrite("../Rekey/image.jpg", image);
    imwrite("../Rekey/image_alpha.jpg", image);

    return true;
}


void prerender(QString key, int hue, int sat, int val, int ai, int time){

    if(time == 100){
        time = 99;
    }

    int current = round(vid.totalFrames * ((double)time / 100));

    Mat frame, prerender;

    vid.capture.set(CAP_PROP_POS_FRAMES, current);
    vid.capture.read(frame);
    vid.capture.read(prerender);

    process(&prerender, convert(toRGB(key)), hue, sat, val, ai);

    double scale;
    if((double)vid.width / vid.height >= (double)250/140){
        scale = (double)500 / vid.width;
    } else {
        scale = (double)280 / vid.height;
    }

    Size size;
    Mat crop;
    resize(frame, crop, size, scale, scale, INTER_LINEAR);
    imwrite("../ReKey/image.jpg", crop);
    resize(prerender, crop, size, scale, scale, INTER_LINEAR);
    imwrite("../ReKey/image_alpha.jpg", crop);
}
