#include <iostream>
#include <cstring>

#include "SoxEndpoint.h"
#include "SoxReader.h"
#include "FirLMS.h"
#include "LinkDNF.h"
#include "Plotter.h"
#include "FilterInputSignal.h"
#include "FilterInputNoise.h"

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define W 640
#define H 480


static void prt_usage(char * exe) {
    fprintf(stderr, "Usage: %s [-D] [-l<lrate>] [-T<ntaps>] [-P] [<sox global options>] [<sox input options>]\n", exe);
    fprintf(stderr, "\t<input file> [<sox noiseref options>] <noise file> [sox output options] <output file>\n\n");
}


int main(int argc, char ** argv) {
    int i;
    char * s;
    char globalopts[256] = "";
    char fileopts[3][256] = {"","",""};
    char effectopts[256] = "";
    char *paths[3];
    int rates[3] = {0,0,0}, nchans[3] = {0,0,0};
    int pcnt = 0;
    std::thread * threads[3];
    double lr = 0.001;
    int nt = 100;
    bool dnf = false;
    bool plot = false;

    for(i = 1; i < argc; i++) {
        if(argv[i][0] != '-') {
            if(pcnt > 2) goto error;
            paths[pcnt++] = argv[i];
        } else switch(argv[i][1]) {
            case '\0':
            case 'p':
            case 'd':
            case 'n':
                if(pcnt > 2) goto error;
                paths[pcnt++] = argv[i];
                break;
            case 'h':
                prt_usage(argv[0]);
                fprintf(stderr, "The -D option causes a DNF filter rather than a single-layer LMS filter to be used.\n");
                fprintf(stderr, "The -P option plots filter signals in dynamic pop-up windows.\n");
                fprintf(stderr, "The -l and -T options control the filter parameters.\n");
                fprintf(stderr, "Standard 'sox' options may be used directly in their short form. File options will\n");
                fprintf(stderr, "apply to the following input file, just as they would in a normal sox invocation.\n");
                fprintf(stderr, "Long options (those beginning with '--') must be escaped with '-G' for global\n");
                fprintf(stderr, "options, '-I' for input file options, '-R' for noise reference file options, or\n");
                fprintf(stderr, "'-O' for output file options. Sox effects must be escaped with '-E' and will be\n");
                fprintf(stderr, "applied after the filter.\n");
                return 0;
            case 'l':
                if(argv[i][2]) {
                    lr = atof(argv[i] + 2);
                } else if(++i < argc) {
                    lr = atof(argv[i]);
                } else goto error;
                break;
            case 'T':
                if(argv[i][2]) {
                    nt = atoi(argv[i] + 2);
                } else if(++i < argc) {
                    nt = atoi(argv[i]);
                } else goto error;
                break;
            case 'D':
                dnf = true;
                break;
            case 'q':
            case 'S':
            case 'V':
                /* Pass as global options */
                strncat(globalopts, argv[i], 255);
                strncat(globalopts, " ", 255);
                break;
            case 'c':
                /* Channel count -- pass as file opt and take note */
                strncat(fileopts[pcnt], argv[i], 255);
                    strncat(fileopts[pcnt], " ", 255);
                if(argv[i][2]) {
                    nchans[pcnt] = atoi(argv[i] + 2);
                } else if(++i < argc) {
                    nchans[pcnt] = atoi(argv[i]);
                    strncat(fileopts[pcnt], argv[i], 255);
                    strncat(fileopts[pcnt], " ", 255);
                } else goto error;
                break;
            case 'r':
                /* Sample rate -- pass as file opt and take note */
                strncat(fileopts[pcnt], argv[i], 255);
                    strncat(fileopts[pcnt], " ", 255);
                if(argv[i][2]) {
                    rates[pcnt] = strtoul(argv[i] + 2, &s, 0);
                    if(*s == 'k') rates[pcnt] *= 1000;
                } else if(++i < argc) {
                    rates[pcnt] = strtoul(argv[i], &s, 0);
                    if(*s == 'k') rates[pcnt] *= 1000;
                    strncat(fileopts[pcnt], argv[i], 255);
                    strncat(fileopts[pcnt], " ", 255);
                } else goto error;
                break;
            case 'v':
            case 'b':
            case 'e':
            case 't':
            case 'C':
                /* Pass this and possibly next as file options */
                strncat(fileopts[pcnt], argv[i], 255);
                strncat(fileopts[pcnt], " ", 255);
                if(!argv[i][2] && ++i < argc) {
                    strncat(fileopts[pcnt], argv[i], 255);
                    strncat(fileopts[pcnt], " ", 255);
                }
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '8':
            case 'L':
            case 'B':
            case 'x':
            case 'N':
            case 'X':
            case 's':
            case 'u':
            case 'f':
            case 'A':
            case 'U':
            case 'o':
            case 'i':
            case 'a':
            case 'g':
                /* TODO pass as file options */
                strncat(fileopts[pcnt], argv[i], 255);
                strncat(fileopts[pcnt], " ", 255);
                break;
            case 'E':
                /* Drop and pass next as effect options */
                if(argv[i][2]) {
                    strncat(effectopts, argv[i] + 2, 255);
                    strncat(effectopts, " ", 255);
                } else if(++i < argc) {
                    strncat(effectopts, argv[i], 255);
                    strncat(effectopts, " ", 255);
                }
                break;
            case 'I':
                /* Drop and pass next as input options */
                if(argv[i][2]) {
                    if(argv[i][2] != '-') strncat(fileopts[0], "-", 255);
                    strncat(fileopts[0], argv[i] + 2, 255);
                    strncat(fileopts[0], " ", 255);
                } else if(++i < argc) {
                    strncat(fileopts[0], argv[i], 255);
                    strncat(fileopts[0], " ", 255);
                }
                break;
            case 'R':
                /* Drop and pass next as noise reference options */
                if(argv[i][2]) {
                    if(argv[i][2] != '-') strncat(fileopts[1], "-", 255);
                    strncat(fileopts[1], argv[i] + 2, 255);
                    strncat(fileopts[1], " ", 255);
                } else if(++i < argc) {
                    strncat(fileopts[1], argv[i], 255);
                    strncat(fileopts[1], " ", 255);
                }
                break;
            case 'O':
                /* Drop and pass next as output options */
                if(argv[i][2]) {
                    if(argv[i][2] != '-') strncat(fileopts[2], "-", 255);
                    strncat(fileopts[2], argv[i] + 2, 255);
                    strncat(fileopts[2], " ", 255);
                } else if(++i < argc) {
                    strncat(fileopts[2], argv[i], 255);
                    strncat(fileopts[2], " ", 255);
                }
                break;
            case 'G':
                /* Drop and pass next as global options */
                if(argv[i][2]) {
                    if(argv[i][2] != '-') strncat(globalopts, "-", 255);
                    strncat(globalopts, argv[i] + 2, 255);
                    strncat(globalopts, " ", 255);
                } else if(++i < argc) {
                    strncat(globalopts, argv[i], 255);
                    strncat(globalopts, " ", 255);
                }
                break;
            default: goto error;
        }        
    }

    if(pcnt < 3) {
      error:
        fprintf(stderr, "Unrecognised argument\n");
        prt_usage(argv[0]);
        return 1;
    }
   
    if(!rates[0]) rates[0] = get_wav_attr("r", paths[0]);
    if(!rates[1]) rates[1] = rates[0];
    if(!rates[2]) rates[2] = rates[0];
    if(!nchans[0]) nchans[0] = get_wav_attr("c", paths[0]);
    if(!nchans[1]) nchans[1] = nchans[0];
    if(!nchans[2]) nchans[2] = nchans[0];
    
    FirLMS flms(nt, lr);
    LinkDNF fdnf(nt, lr, rates[0]);
    NoiseFilter * filt;
    if(dnf) filt = &fdnf;
    else filt = &flms;
    SoxReader sigReader;
    SoxReader noiReader;
    Plotter plotter_samples("Filter Output", 1000, W, H, 60);
    Plotter plotter_weights("Weight Distance", 1000, W, H, 60);
    Plotter plotter_remover("Remover", 1000, W, H, 60);
    
    FilterInputSignal sigin;
    FilterInputNoise noisein;
    
    sigReader.RegisterCallback(&sigin);
    noiReader.RegisterCallback(&noisein);
    sigin.RegisterCallback(filt);
    noisein.RegisterCallback(filt);
    
    SoxEndpoint endpoint;
    /* N.B. not a typo -- should indeed be rates[0] despite others being indexed [2] */
    endpoint.Open(rates[0], nchans[2], globalopts, fileopts[2], paths[2], effectopts);
    
    if(dnf){
        fdnf.RegisterWeightDistCallback(&plotter_weights);
    }
    filt->RegisterCallback(&plotter_samples);
    plotter_samples.RegisterCallback(&endpoint);
    threads[2] = filt->Start();
    
    threads[0] = sigReader.Start(rates[0], nchans[0], globalopts, fileopts[0], paths[0]);
    threads[1] = noiReader.Start(rates[1], nchans[1], globalopts, fileopts[1], paths[1]);
    
    while(true){
       plotter_samples.Show();
       plotter_weights.Show();
    
        if(cv::waitKey(1) == 27) {
            break;
        }
    }
    
    for(i = 0; i < 2; i++) if(threads[i]) threads[i]->join();
    
    filt->Stop();
    
    endpoint.Close();
    return 0;
}

