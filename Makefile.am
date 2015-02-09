include ${capdMake}/make/common_makefile.mkf

SUBDIRS=. ${CAPD_PACKAGES} capdMake/libcapd

.PHONY: lib deb release

distclean-local:
	-rm -fr lib capd.cache

lib:
	@for dir in ${CAPD_PACKAGES}; do \
	   echo "Making lib in $$dir"; \
	   $(MAKE) $(AM_MAKEFLAGS) -C $$dir lib ; \
	   done;
	@$(MAKE) $(AM_MAKEFLAGS) -C "capdMake/libcapd" lib;



DEBSOURCEPKG=$(PACKAGE)_$(VERSION).orig.tar.gz
DEBSOURCEDIR=$(PACKAGE)-$(VERSION)
DEBFILES=$(top_srcdir)/capdMake/debian

deb: dist
	@$(ECHO) "Building Debian package..."; \
	if $(TEST) ! -d $(DEBFILES); then \
		$(ECHO) "The files needed for building a Debian package are not" \
		"included by default in the distribution. To build a package, check" \
		"out the project from source control."; \
		exit 1; \
	fi; \
	$(MV) $(PACKAGE)-$(VERSION).tar.gz $(DEBSOURCEPKG) && \
	$(TAR) --extract --gunzip --file $(DEBSOURCEPKG) && \
	$(MKDIR_P) $(DEBSOURCEDIR)/debian && \
	$(CP) -fr \
		$(DEBFILES) \
		$(DEBSOURCEDIR)/ && \
	cd $(DEBSOURCEDIR) && \
	$(DEBUILD) -j$(shell grep -c ^processor /proc/cpuinfo)  -rfakeroot -D -us -uc; \
	cd $(srcdir); \
	rm --force $(DEBSOURCEPKG); \
	rm --recursive --force $(DEBSOURCEDIR)



package_version:
	@$(ECHO) package_version=$(PACKAGE)-$(VERSION)


EXTRA_DIST = capdMake/make/common_makefile.mkf capdMake/make/common_programs_makefile.mkf capdMake/debian capdMake/capd_library_version_number.m4 capdMake/capd_version_number.m4 ChangeLog README.md
