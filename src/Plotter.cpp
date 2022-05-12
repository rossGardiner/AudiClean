#include "Plotter.h"
#include <stdlib.h>
#include <chrono>
#include <thread>

void Plotter::NextSample(double next){
    int graphX = 0;
    cb->push_back(next);
    if(cb->size() >= 2) {
        std::vector<double> v(cb->begin(), cb->end());
        frame = cv::Scalar(0, 0, 0);
        cvui::sparkline(frame, v, 0, 20, w, h, 0xffffff);
        //cvui::text(     frame,            graphX, graphY + topOffset + graphDY, "Outer: raw(b) & filtered(w) & end(gray)");
        cvui::update();
        step+=1;
        int timespan = (int)((1.0/framerate_fps) * 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(timespan));
    }
    
    
    if(sampleCallback) sampleCallback->NextSample(next);
    
}

Plotter::Plotter(cv::Mat &_ref, int _bsize, int _w, int _h, double _framerate_fps){
    frame = _ref;
    w = _w;
    h = _h;
    bsize = _bsize;
    cb = new boost::circular_buffer<double>(_bsize);
    //graphDX = w; //w/2 - gapX * 2;
    //graphDY = h;
    graphY = 20;
    framerate_fps = _framerate_fps;
}

