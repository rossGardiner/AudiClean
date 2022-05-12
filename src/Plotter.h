#ifndef AUDICLEAN_PLOTTER_H
#define AUDICLEAN_PLOTTER_H

#include <opencv2/opencv.hpp>

#include "boost/circular_buffer.hpp"
#include "cvui.h"
#include "SampleLink.h"

class Plotter : public SampleLink{
public:
    void NextSample(double next);
    Plotter(cv::Mat &_ref, int _bsize, int _w, int _h, double _framerate_fps);
    
private:
    cv::Mat frame;
    int w = 0; int h = 0;
    boost::circular_buffer<double>* cb;
    int topOffset = 30;
    int graphY = 0;
    int gapY = 30;
    int barDX = 200;
    int bar_p = 1;
    int titleY = 2;
    int step = 0;
    int bsize = 2;
    double framerate_fps = 0.2;
};


#endif //AUDICLEAN_PLOTTER_H
