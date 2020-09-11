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
# LAST EDITED:	    09/11/2020
###

start:
	$(MAKE) -C ReachCodec development
	mv ReachCodec/build/ReachCodecGlue.js src/
	react-scripts start

build:
	$(MAKE) -C ReachCodec
	mv ReachCodec/build/ReachCodecGlue.js src/
	react-scripts build
	mv ReachCodec/build/* build/

###############################################################################
