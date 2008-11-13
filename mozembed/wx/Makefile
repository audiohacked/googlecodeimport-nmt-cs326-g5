CC=gcc
CXX=g++

MOZ_CFLAGS=-DMOZ_DLL_SUFFIX="\".so\"" `pkg-config --cflags libxul libxul-embedding-unstable mozilla-js`
MOZ_LIBS=`pkg-config --libs libxul libxul-embedding-unstable mozilla-js`


SRCS = \
	../common/embed.cpp \
	../common/WebBrowserChrome.cpp \
	../common/EmbeddingSetup.cpp \
	../common/ContentListener.cpp \

HEADERS = \
	../common/embed.h \

CFLAGS=-fno-rtti -I../common $(MOZ_CFLAGS) `wx-config --unicode --cxxflags` `pkg-config --cflags gtk+-2.0` 

LDFLAGS=`wx-config --libs core` $(MOZ_LIBS)

test_SRCS  = test.cpp wxMozView.cpp wxMozProfile.cpp 

all:: test 

test:  $(test_SRCS) $(SRCS)  
	$(CXX) -g $(CFLAGS) -o $@ $(test_SRCS) $(SRCS) $(LDFLAGS)

clean:
	rm test

