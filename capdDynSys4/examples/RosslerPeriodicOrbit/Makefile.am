include ${capdMake}/make/common_programs_makefile.mkf

noinst_PROGRAMS=RosslerPeriodicOrbit

RosslerPeriodicOrbit_SOURCES=RosslerPeriodicOrbit.cpp
RosslerPeriodicOrbit_CXXFLAGS=${capdDynSys_CFLAGS} -std=c++11
RosslerPeriodicOrbit_libs=${capdDynSys_LIBS}
RosslerPeriodicOrbit_LDADD=${RosslerPeriodicOrbit_libs}
RosslerPeriodicOrbit_DEPENDENCIES=${filter %.a %.la,${RosslerPeriodicOrbit_libs}}

