#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ(2.61)
m4_define([capdMake_PATH],[../../../../../../../capdMake])
m4_include(capdMake_PATH[/make/capd_version.m4])
AC_INIT(capdDynSys-tests, CAPD_VERSION_NUMBER, http://capd.ii.uj.edu.pl, [], http://capd.ii.uj.edu.pl)

AC_CONFIG_AUX_DIR(../../capdMake)
default_top_capd=${srcdir}/../..
top_capd_build=./../..
m4_include([../../capdMake/make/configure_common.ac])
AM_INIT_AUTOMAKE(capd_automake_init_options)


AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([nonAutTest/Makefile])
#AC_CONFIG_FILES([map/Makefile])
#AC_CONFIG_FILES([dynset/Makefile])

AC_PROG_CXX
LT_INIT

PKG_CHECK_MODULES([capdAux], [capdAux >= 1.0])
PKG_CHECK_MODULES([capdExt], [capdExt >= 1.0])
PKG_CHECK_MODULES([capdDynSys], [capdDynSys >= 1.0])


HAVE_capdkrak=yes
PKG_CHECK_MODULES([capdkrak], [capdkrak >= 1.0], [], [HAVE_capdkrak=no])
AM_CONDITIONAL([HAVE_capdkrak], [test "x$HAVE_capdkrak" = "xyes"])


AC_CONFIG_HEADER(config.h)
AC_OUTPUT
