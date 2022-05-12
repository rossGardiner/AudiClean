#ifndef AUDICLEAN_PLOTTER_H
#define AUDICLEAN_PLOTTER_H

#include <opencv2/opencv.hpp>

#include "boost/circular_buffer.hpp"
#include "cvui.h"
#include "SampleLink.h"

class Plotter : public SampleLink{
public:
    void NextSample(double next);
    Plotter(cv::Mat &_ref, int _bsize, int _w, int _h);
    
private:
    cv::Mat frame;
    int w; int h;
    boost::circular_buffer<double>* cb;
};


#endif //AUDICLEAN_PLOTTER_H
