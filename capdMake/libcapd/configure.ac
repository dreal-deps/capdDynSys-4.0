#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ(2.61)
m4_define([capdMake_PATH],[../../capdMake])
m4_include(capdMake_PATH[/make/capd_version.m4])

AC_INIT(capd, CAPD_VERSION_NUMBER, http://capd.ii.uj.edu.pl, [], http://capd.ii.uj.edu.pl)

AC_PROG_SED

AC_CONFIG_MACRO_DIR([../m4])
AC_CONFIG_AUX_DIR(../../capdMake)
default_top_capd=${srcdir}/../..
top_capd_build=./../..
m4_include([../../capdMake/make/configure_common.ac])
AM_INIT_AUTOMAKE(capd_automake_init_options)

AC_CANONICAL_HOST # for host_os

AC_LANG([C++])

dnl AS_IF([ test "$cross_compiling" != "yes" ],
dnl   [
dnl    AC_RUN_IFELSE(
dnl    [AC_LANG_SOURCE([
dnl #include <dlfcn.h>
dnl int main()
dnl {
dnl void* h1 = dlopen("libstdc++.dylib", RTLD_LAZY);
dnl void* h2 = dlopen("libstdc++.so", RTLD_LAZY);

dnl return (h1 != 0 || h2 != 0) ? 0 : 1;
dnl }
dnl 	])], [HAVE_LIB_DYNAMIC_STDCPP=true], [HAVE_LIB_DYNAMIC_STDCPP=false])
dnl   ], [HAVE_LIB_DYNAMIC_STDCPP=true])


dnl AM_CONDITIONAL([LINK_WITH_LIBSTDCPP], [test "x$host_os" = "xmingw32" || test $HAVE_LIB_DYNAMIC_STDCPP = true])

AM_CONDITIONAL([LINK_WITH_LIBSTDCPP], [test "x$host_os" = "xmingw32"])


LIB_LA_TO_A="${SED} 's|\([[^ ]]*\)/\(lib[[a-zA-Z0-9_-]]*\)\.la|\1/.libs/\2.a|g'"

AC_SUBST([LIB_LA_TO_A])
AC_SUBST([top_capd_build])
AC_CONFIG_FILES([Makefile])

AS_IF([ test "x$BASH" != "x" ],
[
    AS_IF([ test "x${!pkg_config_path_var}" = "x" ],
                 [ export ${pkg_config_path_var}="${pkg_config_install}"],
                 [ export ${pkg_config_path_var}="${pkg_config_install}${PATH_SEPARATOR}${!pkg_config_path_var}"])

    echo "Exporting ${pkg_config_path_var} as ${!pkg_config_path_var}"
],
[
    AC_MSG_WARN([Your interpreter is not like BASH])
    AS_IF([ test "x${PKG_CONFIG_PATH}" = "x" ],
                 [ export PKG_CONFIG_PATH="${pkg_config_install}"],
                 [ export PKG_CONFIG_PATH="${pkg_config_install}${PATH_SEPARATOR}${PKG_CONFIG_PATH}"])

    echo "Exporting PKG_CONFIG_PATH as ${PKG_CONFIG_PATH}"
])

CAPD_PACKAGES=""
MPCAPD_PACKAGES=""

PKG_CHECK_EXISTS([capdDynSys], [CAPD_PACKAGES="${CAPD_PACKAGES} capdDynSys"], [])
PKG_CHECK_EXISTS([capdRedHom], [CAPD_PACKAGES="${CAPD_PACKAGES} capdRedHom"], [])

# REQUIRED PACKAGES SHOULD BE CHECKED BY 'Requires:' in cpadDynSys/capdRedHom.
# With bellow lines pkg-config do not use correct order of libraries, e.g libprim is firts
# PKG_CHECK_EXISTS([capdAlg], [CAPD_PACKAGES="${CAPD_PACKAGES} capdAlg"], [])
# PKG_CHECK_EXISTS([capdAux], [CAPD_PACKAGES="${CAPD_PACKAGES} capdAux"], [])
# PKG_CHECK_EXISTS([capdExt], [CAPD_PACKAGES="${CAPD_PACKAGES} capdExt"], [])
# PKG_CHECK_EXISTS([capdExtHom], [CAPD_PACKAGES="${CAPD_PACKAGES} capdExtHom"], [])

AC_DEFUN([DEFINE_LIBS_FLAGS_ONLY],
[
  $1_FLAGS_ONLY="$(echo $$1 | ${SED} 's|-L[[-.a-zA-Z0-9_/\\]]*||g' | ${SED} 's|[[-.a-zA-Z0-9_/\\]]*\.la||g' | ${SED} 's|[[-.a-zA-Z0-9_/\\]]*\.a||g')"

  export $1_FLAGS_ONLY="${$1_FLAGS_ONLY}"
  AC_SUBST([$1_FLAGS_ONLY])
]
)

AS_IF([test "x${CAPD_PACKAGES}" != "x"],
	    [AC_SUBST([CAPD_PACKAGES])
	    PKG_CHECK_MODULES([capd], [${CAPD_PACKAGES}])
	    DEFINE_LIBS_FLAGS_ONLY(capd_LIBS)
	    AC_CONFIG_FILES([${pkg_config_dev}/capd.pc:capd-dev.pc.in])
	    AC_CONFIG_FILES([capd.pc:capd.pc.in])
	    AC_CONFIG_FILES(capd-config)
	    AC_CONFIG_FILES(${top_capd_build}/bin/capd-config:capd-config-dev.in)])

AM_CONDITIONAL(HAVE_CAPD, [test "x${CAPD_PACKAGES}" != "x"])

PKG_CHECK_EXISTS([capdkrak], [CAPD_PACKAGES_GUI="capdkrak"], [])

AS_IF([test "x${CAPD_PACKAGES_GUI}" != "x"],
	    [AC_SUBST([CAPD_PACKAGES_GUI])
	    PKG_CHECK_MODULES([capd_gui], [${CAPD_PACKAGES_GUI} ${CAPD_PACKAGES}])
	    DEFINE_LIBS_FLAGS_ONLY(capd_gui_LIBS)
	    AC_CONFIG_FILES([${pkg_config_dev}/capd-gui.pc:capd-gui-dev.pc.in])
	    AC_CONFIG_FILES([capd-gui.pc:capd-gui.pc.in])
    	    AC_CONFIG_FILES(capd-gui-config)
	    AC_CONFIG_FILES(${top_capd_build}/bin/capd-gui-config:capd-gui-config-dev.in)
	    ])

AM_CONDITIONAL(HAVE_CAPD_GUI, [test "x${CAPD_PACKAGES_GUI}" != "x"])

PKG_CHECK_EXISTS([mpcapdDynSys], [MPCAPD_PACKAGES="${MPCAPD_PACKAGES} mpcapdDynSys"], [])
PKG_CHECK_EXISTS([mpcapdRedHom], [MPCAPD_PACKAGES="${MPCAPD_PACKAGES} mpcapdRedHom"], [])
PKG_CHECK_EXISTS([mpcapdAlg], [MPCAPD_PACKAGES="${MPCAPD_PACKAGES} mpcapdAlg"], [])

AS_IF([test "x${MPCAPD_PACKAGES}" != "x"],
	    [AC_SUBST([MPCAPD_PACKAGES])
	    PKG_CHECK_MODULES([mpcapd], [${MPCAPD_PACKAGES} ${CAPD_PACKAGES}])
	    DEFINE_LIBS_FLAGS_ONLY(mpcapd_LIBS)
	    AC_CONFIG_FILES([${pkg_config_dev}/mpcapd.pc:mpcapd-dev.pc.in])
	    AC_CONFIG_FILES([mpcapd.pc:mpcapd.pc.in])
    	    AC_CONFIG_FILES(mpcapd-config)
	    AC_CONFIG_FILES(${top_capd_build}/bin/mpcapd-config:mpcapd-config-dev.in)
	    ])

AM_CONDITIONAL([HAVE_MPCAPD], [test "x${MPCAPD_PACKAGES}" != "x"])

AS_IF([test "x${MPCAPD_PACKAGES}" != "x" && test "x${CAPD_PACKAGES_GUI}" != "x"],
	    [AC_SUBST([MPCAPD_PACKAGES])
	    PKG_CHECK_MODULES([mpcapd_gui], [${MPCAPD_PACKAGES} ${CAPD_PACKAGES_GUI} ${CAPD_PACKAGES}])
	    DEFINE_LIBS_FLAGS_ONLY(mpcapd_gui_LIBS)
	    AC_SUBST([CAPD_PACKAGES_GUI])
	    AC_CONFIG_FILES([${pkg_config_dev}/mpcapd-gui.pc:mpcapd-gui-dev.pc.in])
	    AC_CONFIG_FILES([mpcapd-gui.pc:mpcapd-gui.pc.in])
    	    AC_CONFIG_FILES(mpcapd-gui-config)
	    AC_CONFIG_FILES(${top_capd_build}/bin/mpcapd-gui-config:mpcapd-gui-config-dev.in)
	    ])

AM_CONDITIONAL([HAVE_MPCAPD_GUI], [test "x${MPCAPD_PACKAGES}" != "x" && test "x${CAPD_PACKAGES_GUI}" != "x"])


AC_PROG_CXX
# Checks for libraries.
LT_INIT([win32-dll])


AC_OUTPUT
