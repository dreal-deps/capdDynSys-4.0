#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ(2.61)
AC_INIT(capdAux-examples, 1.0, BUG-REPORT-ADDRESS)

m4_define([capdMake_PATH],[../../capdMake])

AC_CONFIG_AUX_DIR(../../capdMake)
default_top_capd=${srcdir}/../..
top_capd_build=./../..
m4_include([../../capdMake/make/configure_common.ac])

boost_optional=yes
m4_include([../../capdMake/make/configure_common_boost.ac])


AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([auxilTests/Makefile])


AC_PROG_CXX
LT_INIT

PKG_CHECK_MODULES([capdauxil], [capdauxil >= 1.0])
PKG_CHECK_MODULES([capdAux], [capdAux >= 1.0])


AM_COND_IF([HAVE_BOOST], [
  BOOST_TEST()
  BOOST_SYSTEM()
  BOOST_FILESYSTEM()
  BOOST_REGEX()
])

AC_CONFIG_HEADER(config.h)
AC_OUTPUT
