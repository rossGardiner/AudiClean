#ifndef AUDICLEAN_PLOTTER_H
#define AUDICLEAN_PLOTTER_H

#include <opencv2/opencv.hpp>

#include "boost/circular_buffer.hpp"
#include "cvui.h"
#include "SampleLink.h"

class Plotter : public SampleLink{
public:
    void NextSample(double next);
    Plotter(std::string _winname, int _bsize, int _w, int _h, double _framerate_fps);
    void Init();
    void Show();
private:
    std::string window_name;
    cv::Mat frame;
    int w = 0; int h = 0;
    boost::circular_buffer<double>* cb;
    int bsize = 2;
    int textdepth_y = 20;
    int margin = 5;
    int n = 0;
    double framerate_fps = 0.2;
};


#endif //AUDICLEAN_PLOTTER_H
