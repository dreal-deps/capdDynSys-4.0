include ${capdMake}/make/common_makefile.mkf

SUBDIRS=include src examples tests


.PHONY: doc
doc:
	$(MAKE) $(AM_MAKEFLAGS) -C docs doc

.PHONY: lib

lib:
	$(MAKE) $(AM_MAKEFLAGS) -C src
