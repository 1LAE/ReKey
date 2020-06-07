#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QString>
#include <ctime>
#include "helper.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>

TEST(load,exist){

    QString path = "/home/travis/build/1LAE/ReKey/tests/videos/video.mp4";
    bool ret;
    ret = load(path);
    ASSERT_EQ(ret, true);
}


TEST(load, empty){

    QString path = "abc";
    bool ret;
    testing::internal::CaptureStderr();
    ret = load(path);
    EXPECT_EQ(false, ret);
    std::string output = testing::internal::GetCapturedStderr();

    ASSERT_EQ("No such file found\n", output);
}

TEST(load, expansion){

    QString path = "home/travis/build/1LAE/ReKey/tests/videos/video";
    bool ret;
    testing::internal::CaptureStderr();
    ret = load(path);
    EXPECT_EQ(true, ret);
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ("", output);
}

TEST(load, opened){

    QString path = "/home/travis/build/1LAE/ReKey/tests/videos/video.mp4";
    load(path);
    bool ret;
    path = "/home/travis/build/1LAE/ReKey/tests/videos/video";
    testing::internal::CaptureStderr();
    testing::internal::CaptureStdout();
    ret = load(path);
    EXPECT_EQ(true, ret);
    std::string cout = testing::internal::GetCapturedStdout();
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ("", output);
    EXPECT_EQ("", cout);
}


//################################################################


TEST(toRGB, correct){

    QString color = "#ffffff";
    RGB rgb = toRGB(color);
    EXPECT_FLOAT_EQ(rgb.r, 1);
    EXPECT_FLOAT_EQ(rgb.g, 1);
    EXPECT_FLOAT_EQ(rgb.b, 1);

}

TEST(toRGB, convertation){

    QString color = "#a945fc";
    RGB rgb = toRGB(color);
    EXPECT_NEAR(rgb.r, 0.6627, 0.001);
    EXPECT_NEAR(rgb.g, 0.2705, 0.001);
    EXPECT_NEAR(rgb.b, 0.9882, 0.001);


}

TEST(toRGB, format_a){

    QString color = "ffffff";
    testing::internal::CaptureStderr();
    RGB rgb = toRGB(color);
    EXPECT_FLOAT_EQ(rgb.r, 0);
    EXPECT_FLOAT_EQ(rgb.g, 0);
    EXPECT_FLOAT_EQ(rgb.b, 0);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "ERROR: wrong color format\n");

}



TEST(toRGB, format_b){

    QString color = "helloo";
    testing::internal::CaptureStderr();
    RGB rgb = toRGB(color);
    EXPECT_FLOAT_EQ(rgb.r, 0);
    EXPECT_FLOAT_EQ(rgb.g, 0);
    EXPECT_FLOAT_EQ(rgb.b, 0);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "ERROR: wrong color format\n");

}

TEST(toRGB, format_c){

    QString color = "#fffff";

    testing::internal::CaptureStderr();

    RGB rgb = toRGB(color);
    EXPECT_FLOAT_EQ(rgb.r, 0);
    EXPECT_FLOAT_EQ(rgb.g, 0);
    EXPECT_FLOAT_EQ(rgb.b, 0);

    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "ERROR: wrong color format\n");

}


//################################################################


TEST(convert, correct_a){

    RGB rgb;
    HSV hsv;
    rgb.r = 0.6627;
    rgb.g = 0.2705;
    rgb.b = 0.9882;

    hsv = convert(rgb);
    EXPECT_NEAR(hsv.H, 312.3, 0.1);
    EXPECT_NEAR(hsv.S, 0.329, 0.01);
    EXPECT_NEAR(hsv.V, 0.988, 0.01);

}


TEST(convert, correct_b){

    RGB rgb;
    HSV hsv;
    rgb.r = 0.6627;
    rgb.g = 0.2705;
    rgb.b = 0.9882;

    hsv = convert(rgb);
    EXPECT_NEAR(hsv.H, 312.2, 0.1);
    EXPECT_NEAR(hsv.S, 0.329, 0.1);
    EXPECT_NEAR(hsv.V, 0.9882, 0.1);
}


TEST(convert, correct_c){

    RGB rgb;
    HSV hsv;
    rgb.r = 1;
    rgb.g = 1;
    rgb.b = 1;

    hsv = convert(rgb);
    EXPECT_DOUBLE_EQ(hsv.H, 0);
    EXPECT_DOUBLE_EQ(hsv.S, 0);
    EXPECT_DOUBLE_EQ(hsv.V, 1);
}

TEST(convert, range){

    RGB rgb;
    HSV hsv;
    rgb.r = -0.75;
    rgb.g = 3;
    rgb.b = 0.23;

    testing::internal::CaptureStderr();

    hsv = convert(rgb);
    EXPECT_NEAR(hsv.H, 0, 0.1);
    EXPECT_NEAR(hsv.S, 0, 0.1);
    EXPECT_NEAR(hsv.V, 0, 0.1);

    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "ERROR: Cant' assign to hsv (invalid values)\n");


}

//################################################################


TEST(process, correct){

    cv::VideoCapture cap("./tests/videos/video.mp4");
    cv::Mat frame;
    cap >> frame;
    HSV hsv;
    hsv.H = 180;
    hsv.S = 0.5;
    hsv.V = 0.032;
    testing::internal::CaptureStderr();

    process(&frame, hsv, 20, 20, 20, 20);

    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "");
}


TEST(process, timing_soft){

    cv::VideoCapture cap("./tests/videos/video_soft.mp4");
    cv::Mat frame;
    cap >> frame;
    HSV hsv;
    hsv.H = 180;
    hsv.S = 0.5;
    hsv.V = 0.032;
    testing::internal::CaptureStderr();
    int end;
    int start = clock();
    process(&frame, hsv, 0, 0, 0, 0);
    end = clock();
    double time = (float)(end - start) / CLOCKS_PER_SEC;
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "");
    EXPECT_LE(time, 0.01);


}

TEST(process, timing_normal){

    cv::VideoCapture cap("./tests/videos/video.mp4");
    cv::Mat frame;
    cap >> frame;
    HSV hsv;
    hsv.H = 180;
    hsv.S = 0.5;
    hsv.V = 0.032;
    testing::internal::CaptureStderr();
    int end;
    int start = clock();
    process(&frame, hsv, 180, 50, 50, 50);
    end = clock();
    double time = (float)(end - start) / CLOCKS_PER_SEC;
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "");
    EXPECT_LE(time, 0.1);


}



TEST(process, timing_hard){

    cv::VideoCapture cap("./tests/videos/video_4k.mp4");
    cv::Mat frame;
    cap >> frame;
    HSV hsv;
    hsv.H = 180;
    hsv.S = 0.5;
    hsv.V = 0.032;
    testing::internal::CaptureStderr();
    int end;
    int start = clock();
    process(&frame, hsv, 359, 100, 100, 100);
    end = clock();
    double time = (float)(end - start) / CLOCKS_PER_SEC;
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "");
    EXPECT_LE(time, 2);

}

TEST(process, empty){

    cv::Mat frame;
    HSV hsv;
    hsv.H = 180;
    hsv.S = 0.5;
    hsv.V = 0.032;
    testing::internal::CaptureStderr();

    process(&frame, hsv, 20, 20, 20, 20);

    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "ERROR: fame has no data\n");

}

TEST(process, range){

    cv::VideoCapture cap("./tests/videos/video.mp4");
    cv::Mat frame;
    cap >> frame;
    HSV hsv;
    hsv.H = 180;
    hsv.S = 0.5;
    hsv.V = 0.032;
    testing::internal::CaptureStderr();

    process(&frame, hsv, 480, 0, -43, 100);

    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "ERROR: Invalid types range\n");

}




