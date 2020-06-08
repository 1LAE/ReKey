#include <QColor>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <iostream>
#include <string>

#include "helper.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

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


    vid.totalFrames = vid.capture.get(CAP_PROP_FRAME_COUNT);
    vid.fps = vid.capture.get(CAP_PROP_FPS);
    vid.height = vid.capture.get(CAP_PROP_FRAME_HEIGHT);
    vid.width = vid.capture.get(CAP_PROP_FRAME_WIDTH);

    Mat image;
    image = imread((const std::string)"./ReKey/template.jpg", IMREAD_COLOR);

    imwrite("../Rekey/image.jpg", image);
    imwrite("../Rekey/image_alpha.jpg", image);

    return true;
}
