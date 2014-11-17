include ${capdMake}/make/common_makefile.mkf

noinst_LTLIBRARIES=libcapdkrak.la
libcapdkrak_la_SOURCES=atom.cpp  chain.cpp  color.cpp  coord3d.cpp  frame.cpp  frstring.cpp  item.cpp  job.cpp  kernel.cpp  noframe.cpp  primitiv.cpp  usermove.cpp
libcapdkrak_la_LDFLAGS=${LIBCAPD_LDFLAGS}
libcapdkrak_la_CXXFLAGS= ${capdkrak_CFLAGS}  ${capdkrak_CFLAGS} ${X11_CFLAGS}



pkgconfigdir = @PKG_CONFIG_DIR@
pkgconfig_DATA =
