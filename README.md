# AudiClean

AudiClean is an event driven audio processing libary which implements adaptive LMS and DNF filters as an extension of the Sound eXchange (SoX) package for audio processing. 

# Prerequisites

You must have SoX installed to use our application standalone. Install SoX with `apt` using the following command:
```
sudo apt install sox 
```
To make use of the DNF filter, you must also install the boost library:

```
 sudo apt-get install libboost-all-dev
```

To use the plotting features, you need the opencv library:

```
sudo apt-get install libopencv-dev
```

All of these packages may be easily installed by running our `setup.sh` script:
```
bash setup.sh
```

# Build

To build `AudiClean` use `cmake` and `make` as shown:

```
cmake .
make
```

# Documentation

Check out the developer documentation hosted [here](https://rossgardiner.github.io/AudiClean/html/annotated.html).
