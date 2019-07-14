#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <cstdio>
#include <time.h>

using namespace cv;
using namespace std;
void onMouse(int event, int x, int y, int flags, void* param);
void onMouseCheck(int event, int x, int y, int flags, void* param);
void draw_line(Mat* im);
void checkIn(Mat* im,int x , int y);
void delay(clock_t sec);