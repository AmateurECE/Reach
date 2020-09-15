###############################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
#
# DESCRIPTION:	    Makefile for the project. This Makefile is used to glue
#		    together the React application and the independent pieces.
#
# CREATED:	    09/11/2020
#
# LAST EDITED:	    09/14/2020
###

build=$(shell realpath .)/ReachCodec/build/bin
music=$(shell realpath .)/music
nginxConf=$(shell realpath .)/reach-development.conf
start: ReachCodec
	cp -f ReachCodec/DevelopmentGlue.js src/ReachCodecGlue.js
	mkdir -p log
	-docker stop reach
	docker run -d --rm --name reach -p "8080:80" \
		-v "$(build):/var/www/reach:ro" \
		-v "$(music):/var/www/music:ro" \
		-v "$(nginxConf):/etc/nginx/conf.d/default.conf:ro" \
		-v "`realpath .`/log:/var/log/nginx" \
		nginx:latest
	react-scripts start

build: ReachCodec
	cp -f ReachCodec/ProductionGlue.js src/ReachCodecGlue.js
	react-scripts build
	mv -f ReachCodec/build/bin/* build/

.PHONY: ReachCodec start build
ReachCodec:
	emcmake cmake ReachCodec -B ReachCodec/build
	emmake make -C ReachCodec/build

###############################################################################
