include ${capdMake}/make/common_programs_makefile.mkf

check_PROGRAMS=mpsintest
TESTS=${check_PROGRAMS}

mpsintest_SOURCES=mpsintest.cpp
mpsintest_libs=  ${mpcapdAlg_LIBS} ${capdAux_LIBS} 
# ${mpcapdintervals_LIBS} 
mpsintest_LDADD=${mpsintest_libs}
mpsintest_DEPENDENCIES=${filter %.a %.la,${mpsintest_libs}} 
mpsintest_CXXFLAGS= ${AM_CXXFLAGS} ${mpcapdintervals_CFLAGS} ${mpfr_CFLAGS} ${capdAux_CFLAGS}
