include ${capdMake}/make/common_programs_makefile.mkf

noinst_PROGRAMS=LorenzPeriodicOrbit

LorenzPeriodicOrbit_SOURCES=LorenzPeriodicOrbit.cpp
LorenzPeriodicOrbit_CXXFLAGS=${capdDynSys_CFLAGS} -std=c++11
LorenzPeriodicOrbit_libs=${capdDynSys_LIBS}
LorenzPeriodicOrbit_LDADD=${LorenzPeriodicOrbit_libs}
LorenzPeriodicOrbit_DEPENDENCIES=${filter %.a %.la,${LorenzPeriodicOrbit_libs}}

