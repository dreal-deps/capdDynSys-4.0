include ${capdMake}/make/common_programs_makefile.mkf

check_PROGRAMS= ReversibleSolverTest
TESTS=${check_PROGRAMS}


ReversibleSolverTest_SOURCES=ReversibleSolverTest.cpp
ReversibleSolverTest_CXXFLAGS=${capdDynSys_CFLAGS} ${BOOST_CPPFLAGS}
ReversibleSolverTest_libs=${capdDynSys_LIBS} ${BOOST_UNIT_TEST_FRAMEWORK_LIBS}
ReversibleSolverTest_LDFLAGS=${BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS}
ReversibleSolverTest_LDADD=${ReversibleSolverTest_libs}
ReversibleSolverTest_DEPENDENCIES=${filter %.a %.la,${ReversibleSolverTest_libs}}
