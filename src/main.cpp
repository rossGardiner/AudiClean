#include <iostream>
#include <cstring>

#include "SoxEndpoint.h"
#include "WavReader.h"
#include "FirLMS.h"
#include "FilterInputSignal.h"
#include "FilterInputNoise.h"

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
		/* TODO Show our help */
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
        return 1;
    }
   
    if(!rates[0]) rates[0] = get_wav_attr("r", paths[0]);
    if(!rates[1]) rates[1] = rates[0];
    if(!rates[2]) rates[2] = rates[0];
    if(!nchans[0]) nchans[0] = get_wav_attr("c", paths[0]);
    if(!nchans[1]) nchans[1] = nchans[0];
    if(!nchans[2]) nchans[2] = nchans[0];
    

    WavReader sigReader;
    WavReader noiReader;
    
    
    FilterInputSignal sigin;
    FilterInputNoise noisein;
    FirLMS filt(50, 0.001);
    
    sigReader.RegisterCallback(&sigin);
    noiReader.RegisterCallback(&noisein);
    sigin.RegisterCallback(&filt);
    noisein.RegisterCallback(&filt);
    
    SoxEndpoint endpoint;
    //SampleLink endpoint;
    /* N.B. not a typo -- should indeed be rates[0] despite others being indexed [2] */
    endpoint.Open(rates[0], nchans[2], globalopts, fileopts[2], paths[2], effectopts);

    filt.RegisterCallback(&endpoint);
    threads[2] = filt.Start();
    
    threads[0] = sigReader.Start(rates[0], nchans[0], globalopts, fileopts[0], paths[0]);
    threads[1] = noiReader.Start(rates[1], nchans[1], globalopts, fileopts[1], paths[1]);
    
    for(i = 0; i < 2; i++) if(threads[i]) threads[i]->join();
    
    filt.Stop();
    
    endpoint.Close();
    return 0;
}

