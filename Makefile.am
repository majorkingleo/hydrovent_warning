bin_PROGRAMS=\
	hydrovent_warning \
	test_HydrothermalVentingLine

hydrovent_warning_SOURCES=\
	src/main.cc \
	src/FileBaseParser.h \
	src/FileBaseParser.cc \
	src/HydrothermalVentingFileParser.h \
	src/HydrothermalVentingFileParser.cc		 


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
	test/test_HydrothermalVentingLine.cc \
	$(test_utils)
	
AM_CPPFLAGS = -I$(top_srcdir)/src \
	-std=c++17	

hydrovent_warning_LDADD = 
