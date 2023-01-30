bin_PROGRAMS=\
	hydrovent_warning \
	test_HydrothermalVentingLine \
	test_CrossMap

hydrovent_warning_SOURCES=\
	src/main.cc \
	src/FileBaseParser.h \
	src/FileBaseParser.cc \
	src/HydrothermalVentingFileParser.h \
	src/HydrothermalVentingFileParser.cc \
	src/HydrothermalVentingLine.h \
	src/HydrothermalVentingLine.cc \
	src/CrossMap.h \
	src/CrossMap.cc \
	src/GetInputFromUser.h \
	src/GetInputFromUser.cc \
	src/ProgressInfo.h \
	src/ProgressInfo.cc


test_utils=\
	test/ColBuilder.h \
	test/ColBuilder.cc \
	test/ColoredOutput.h \
	test/ColoredOutput.cc \
	test/TestUtils.h

test_HydrothermalVentingLine_SOURCES=\
	src/FileBaseParser.h \
	src/FileBaseParser.cc \
	src/HydrothermalVentingFileParser.h \
	src/HydrothermalVentingFileParser.cc \
	src/HydrothermalVentingLine.h \
	src/HydrothermalVentingLine.cc \
	test/test_HydrothermalVentingLine.cc \
	$(test_utils)

test_CrossMap_SOURCES=\
	src/FileBaseParser.h \
	src/FileBaseParser.cc \
	src/HydrothermalVentingFileParser.h \
	src/HydrothermalVentingFileParser.cc \
	src/HydrothermalVentingLine.h \
	src/HydrothermalVentingLine.cc \
	src/CrossMap.h \
	src/CrossMap.cc \
	test/test_CrossMap.cc \
	$(test_utils)
	
AM_CPPFLAGS = -I$(top_srcdir)/src \
	-std=c++17	

hydrovent_warning_LDADD = 

EXTRA_DIST=testdata \
	doc \
	HydroVentWarning \
	README.md

