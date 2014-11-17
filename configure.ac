#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


#AC_PREREQ(2.61)
AC_INIT(capd, 1.0, BUG-REPORT-ADDRESS)

AC_CONFIG_AUX_DIR(capdMake)
default_top_capd=${srcdir}
top_capd_build=.

m4_include([capdMake/make/configure_common.ac])

if test "$cache_file" = /dev/null; then
  cache_file="${top_capd_build}/capd.cache"
  if test -e $cache_file; then
     ${RM} $cache_file
   fi
fi

AC_CONFIG_FILES([Makefile])

CAPD_PACKAGES=""

if test -e "${srcdir}/capdExt"; then
  AC_CONFIG_SUBDIRS([capdExt])
  CAPD_PACKAGES="$CAPD_PACKAGES  capdExt "
fi

if test -e "${srcdir}/capdAux"; then
  AC_CONFIG_SUBDIRS([capdAux])
  CAPD_PACKAGES="$CAPD_PACKAGES  capdAux "
fi

if test -e "${srcdir}/capdAlg"; then
  AC_CONFIG_SUBDIRS([capdAlg])
  CAPD_PACKAGES="$CAPD_PACKAGES  capdAlg "
fi

if test -e "${srcdir}/capdDynSys"; then
  AC_CONFIG_SUBDIRS([capdDynSys])
  CAPD_PACKAGES="$CAPD_PACKAGES  capdDynSys"
else
  if test -e "${srcdir}/capdDynSys4"; then
    AC_CONFIG_SUBDIRS([capdDynSys4])
    CAPD_PACKAGES="$CAPD_PACKAGES  capdDynSys4"
  fi
fi

if test -e "${srcdir}/capdExtHom"; then
  AC_CONFIG_SUBDIRS([capdExtHom])
  CAPD_PACKAGES="$CAPD_PACKAGES  capdExtHom "
fi

if test -e "${srcdir}/capdRedHom"; then
  AC_CONFIG_SUBDIRS([capdRedHom])
  CAPD_PACKAGES="$CAPD_PACKAGES  capdRedHom "
fi

AC_CONFIG_SUBDIRS([capdMake/libcapd])

AC_SUBST([CAPD_PACKAGES])


AC_OUTPUT
