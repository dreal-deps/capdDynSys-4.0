include ${capdMake}/make/common_programs_makefile.mkf


noinst_PROGRAMS=MpIntExample
MpIntExample_SOURCES=MpIntExample.cpp
MpIntExample_libs=${capdvectalg_LIBS} ${mpfr_LIBS}
MpIntExample_LDADD=${MpIntExample_libs}
MpIntExample_DEPENDENCIES=${filter %.a %.la,${MpIntExample_libs}}
MpIntExample_CXXFLAGS=${capdvectalg_CFLAGS} ${mpfr_CFLAGS}
