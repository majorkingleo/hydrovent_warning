# hydrovent_warning

## Building on Windows with MSVC

* use Microsoft Visual Studio 2022 Community Edition https://visualstudio.microsoft.com/de/vs/
* install Package "Desktop Development with C++"
* start it
  * clone a repository from github https://github.com/majorkingleo/hydrovent_warning/
  * or unpack zip file and 
* open within the directory HydroVentWarning the project file HydroVentWarning.sln

## Building on a Linux like system (also cygwin)

### if you have cloned this project from github
(automake, autoconf, aclocal tools required)

```
git clone https://github.com/majorkingleo/hydrovent_warning/
./reconfigure.sh
./configure
make
```

### if you have downloaded a release

```
./configure
make
```

### HydroVentWarning.exe [INPUT.txt] [OUTPUT.txt]

This is the console app as decribed by the requirement doku.
Optional you can directly add an input and output file.

### test_HydrothermalVentingLine.exe

Test programm for testing HydrothermalVentingLine class. No input required.

### test_CrossMap.exe

Test programm for testing CrossMap class. No input required.

# Directory structure

* HydroVentWarning: Visual Studio project files
* src: main source code
* test: test classes source code
* testdata: test data



