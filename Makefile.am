include ${capdMake}/make/common_makefile.mkf

SUBDIRS=. ${CAPD_PACKAGES} capdMake/libcapd

.PHONY: lib

lib:
	for dir in ${CAPD_PACKAGES}; do \
	   echo "Making lib in $$dir"; \
	   $(MAKE) $(AM_MAKEFLAGS) -C $$dir lib ; \
	   done;
