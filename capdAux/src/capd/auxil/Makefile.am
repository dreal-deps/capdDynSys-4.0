include ${capdMake}/make/common_makefile.mkf

noinst_LTLIBRARIES=libcapdauxil.la

libcapdauxil_la_SOURCES= memSize.cpp ofstreamcout.cpp  skipCommentsIstream.cpp timeused.cpp ApplicationDesc.cpp ResourceUsage.cpp Logger.cpp logger_deprecated_20141101.cpp arg_deprecated_20141101.cpp
# TODO
# CAPDConfig.cpp
libcapdauxil_la_LDFLAGS=${LIBCAPD_LDFLAGS} @capdauxil_LIBS@
libcapdauxil_la_CPPFLAGS=-DDATADIR=\"$(pkgdatadir)\" @capdauxil_CFLAGS@


pkgdata_DATA=capd.log4cxx.properties

pkgconfigdir = @PKG_CONFIG_DIR@
pkgconfig_DATA =
