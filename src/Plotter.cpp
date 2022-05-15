#include "Plotter.h"
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <algorithm>

/*!
 * Callback function for Plotter. This will add the sample to an internal ring buffer, plot the sample on the internal cv::Mat and callback the next pipeline element with the sample
 * @param next
 */
void Plotter::NextSample(double next){
    cb->push_back(next);
    if(cb->size() >= 2) {
        std::vector<double> v(cb->begin(), cb->end());
        double min = *min_element(v.begin(), v.end());
        double max = *max_element(v.begin(), v.end());
        frame = cv::Scalar(0, 0, 0);
        cvui::sparkline(frame, v, 0, textdepth_y, w-margin, h-textdepth_y);
        cvui::printf(   frame, margin, margin, "min: %+.5lf max: %+.5lf buff_sz:%d sample: %d", min, max, v.size(), n);
        cvui::update();
        int timespan = (int)((1.0/framerate_fps) * 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(timespan));
    }
    n++;
    if(sampleCallback) sampleCallback->NextSample(next);
    
}

/*!
 * Initialises the window, must be called before Show()
 */
void Plotter::Init() {
    cvui::init(window_name);
}

/*!
 * Constructor for Plotter
 * @param _winname the text window name for this dynamic plot
 * @param _bsize the internal ring buffer size desired
 * @param _w desired width of the window
 * @param _h desired height of the window
 * @param _framerate_fps desired refreshrate of the window (maxiumum)
 */
Plotter::Plotter(std::string _winname, int _bsize, int _w, int _h, double _framerate_fps){
    window_name = _winname;
    frame = cv::Mat(cv::Size(_w, _h), CV_8UC3);
    w = _w;
    h = _h;
    bsize = _bsize;
    cb = new boost::circular_buffer<double>(_bsize);
    framerate_fps = _framerate_fps;
}

/*!
 * Shows the latest version of the internal cv::Mat
 */
void Plotter::Show() {
    cv::imshow(window_name, frame);
}

