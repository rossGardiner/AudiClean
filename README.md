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

# Build

To build `AudiClean` use `cmake` and `make` as shown:

```
cmake .
make
```

# Run 

To fill in, describe how SoX is used as an extension.

# Documentation

Check out the developer documentation hosted [here](https://rossgardiner.github.io/AudiClean/html/annotated.html).
