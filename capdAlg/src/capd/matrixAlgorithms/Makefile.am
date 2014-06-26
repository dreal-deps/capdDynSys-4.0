include ${capdMake}/make/common_makefile.mkf


noinst_LTLIBRARIES=libcapdmatrixAlgorithms.la
libcapdmatrixAlgorithms_la_SOURCES= floatMatrixAlgorithms.cpp  intMatrixAlgorithms.cpp PARIInterface.cpp SmithFormFactory.cpp PARISmithForm.cpp
libcapdmatrixAlgorithms_la_LDFLAGS=${LIBCAPD_LDFLAGS}
libcapdmatrixAlgorithms_la_CXXFLAGS= ${capdmatrixAlgorithms_CFLAGS} ${capdAux_CFLAGS} ${capdExt_CFLAGS} ${mpcapdAlg_CFLAGS}



pkgconfigdir = @PKG_CONFIG_DIR@
pkgconfig_DATA =
