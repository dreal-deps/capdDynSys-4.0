include ${capdMake}/make/common_programs_makefile.mkf

noinst_PROGRAMS=cndemo1 cndemo2 cndemo3

cndemo1_SOURCES=cndemo1.cpp
cndemo1_CXXFLAGS= ${AM_CXXFLAGS} ${capdDynSys_CFLAGS}
cndemo1_libs=${capdDynSys_LIBS} 
cndemo1_LDADD=${cndemo1_libs}
cndemo1_DEPENDENCIES=${filter %.a %.la,${cndemo1_libs}}

cndemo2_SOURCES=cndemo2.cpp
cndemo2_CXXFLAGS= ${AM_CXXFLAGS} ${capdDynSys_CFLAGS}
cndemo2_libs=${capdDynSys_LIBS}
cndemo2_LDADD=${cndemo2_libs}
cndemo2_DEPENDENCIES=${filter %.a %.la,${cndemo2_libs}}

cndemo3_SOURCES=cndemo3.cpp
cndemo3_CXXFLAGS= ${AM_CXXFLAGS} ${capdDynSys_CFLAGS}
cndemo3_libs=${capdDynSys_LIBS}
cndemo3_LDADD=${cndemo3_libs}
cndemo3_DEPENDENCIES=${filter %.a %.la,${cndemo3_libs}}

