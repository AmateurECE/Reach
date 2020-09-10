###############################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
#
# DESCRIPTION:	    Makefile for the flac decoder component.
#
# CREATED:	    09/09/2020
#
# LAST EDITED:	    09/09/2020
###

CC = em++
CFLAGS = -Wall -Wextra --bind -I../../include -s MODULARIZE=1 \
       -s FILESYSTEM=0 -Os -s EXPORT_ES6=1
LDFLAGS = -L/usr/local/Cellar/flac/1.3.3/lib -lFLAC++ -lFLAC
SOURCES = StreamDecoder.cpp

StreamDecoder.js: $(SOURCES)
	mkdir -p .libs
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

###############################################################################
