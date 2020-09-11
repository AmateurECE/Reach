###############################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
#
# DESCRIPTION:	    Makefile for the flac decoder component.
#
# CREATED:	    09/09/2020
#
# LAST EDITED:	    09/11/2020
###

CC = em++
CFLAGS = -Wall -Wextra --bind -I../../include -Os -s FILESYSTEM=0 \
	-s ENVIRONMENT="web" -s MODULARIZE=1 -s EXPORT_NAME="ReachCodec"
LDFLAGS = -L/usr/local/Cellar/flac/1.3.3/lib -lFLAC++ -lFLAC
SOURCES = StreamDecoder.cpp

production: build/ReachCodec.js
	cp ProductionGlue.js build/ReachCodecGlue.js

build=$(shell realpath .)/build
nginxConf=$(shell realpath .)/reach-development.conf
development: build/ReachCodec.js
	cp DevelopmentGlue.js build/ReachCodecGlue.js
	mkdir -p log
	-docker stop reach
	docker run -d --rm --name reach -p "8080:80" \
		-v "$(build):/var/www/reach:ro" \
		-v "$(nginxConf):/etc/nginx/conf.d/default.conf:ro"\
		-v "`realpath .`/log:/var/log/nginx" \
		nginx:latest

build/ReachCodec.js: $(SOURCES)
	rm -rf build/
	mkdir -p build/
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

###############################################################################
