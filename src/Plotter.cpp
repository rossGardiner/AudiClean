#include "Plotter.h"
#include <stdlib.h>
#include <chrono>
#include <thread>

void Plotter::NextSample(double next){
    cb->push_back(next);
    if(cb->size() >= 2) {
        std::vector<double> v(cb->begin(), cb->end());
        frame = cv::Scalar(0, 0, 0);
        cvui::sparkline(frame, v, 0, 0, w, h, 0xffffff);
        cvui::update();
        int timespan = (int)((1.0/framerate_fps) * 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(timespan));
    }
    if(sampleCallback) sampleCallback->NextSample(next);
    
}

void Plotter::Init() {
    cvui::init(window_name);
}

Plotter::Plotter(std::string _winname, int _bsize, int _w, int _h, double _framerate_fps){
    window_name = _winname;
    frame = cv::Mat(cv::Size(_w, _h), CV_8UC3);
    w = _w;
    h = _h;
    bsize = _bsize;
    cb = new boost::circular_buffer<double>(_bsize);
    framerate_fps = _framerate_fps;
}

void Plotter::Show() {
    cv::imshow(window_name, frame);
}

