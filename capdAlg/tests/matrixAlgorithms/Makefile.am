include ${capdMake}/make/common_programs_makefile.mkf

check_PROGRAMS=floatMatrixAlgorithmsTest intMatrixAlgorithmsTest

if HAVE_BOOST
   check_PROGRAMS+=matrixAlgorithmsTest
endif

TESTS=${check_PROGRAMS}

floatMatrixAlgorithmsTest_SOURCES=floatMatrixAlgorithmsTest.cpp
floatMatrixAlgorithmsTest_CXXFLAGS=${capdintervals_CFLAGS}
floatMatrixAlgorithmsTest_libs=${capdintervals_LIBS}
floatMatrixAlgorithmsTest_LDADD=${floatMatrixAlgorithmsTest_libs}
floatMatrixAlgorithmsTest_DEPENDENCIES=${filter %.a %.la,${floatMatrixAlgorithmsTest_libs}}

intMatrixAlgorithmsTest_SOURCES=intMatrixAlgorithmsTest_legacy.cpp
intMatrixAlgorithmsTest_CXXFLAGS=${capdintervals_CFLAGS}
intMatrixAlgorithmsTest_libs=${capdintervals_LIBS}
intMatrixAlgorithmsTest_LDADD=${intMatrixAlgorithmsTest_libs}
intMatrixAlgorithmsTest_DEPENDENCIES=${filter %.a %.la,${intMatrixAlgorithmsTest_libs}}


matrixAlgorithmsTest_SOURCES=matrixAlgorithmsTestMain.cpp intMatrixAlgorithmsTest.cpp SmithFixtures.cpp LinearEquationFixtures.cpp QuotientBaseMatrixFixtures.cpp SmithFormFactoryTest.cpp
if HAVE_PARI
   matrixAlgorithmsTest_SOURCES+=PARIInterfaceTest.cpp
endif
matrixAlgorithmsTest_CXXFLAGS=${capdAlg_CFLAGS} ${mpcapdAlg_CFLAGS} ${BOOST_CPPFLAGS}
matrixAlgorithmsTest_libs=${capdAlg_LIBS} ${mpcapdAlg_LIBS} ${BOOST_UNIT_TEST_FRAMEWORK_LIBS}
matrixAlgorithmsTest_LDFLAGS=${BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS}
matrixAlgorithmsTest_LDADD=${matrixAlgorithmsTest_libs}
matrixAlgorithmsTest_DEPENDENCIES=${filter %.a %.la,${matrixAlgorithmsTest_libs}}
