dnl configure.ac                                        -*- Autoconf -*-
dnl
dnl Process this file with `autoconf` to produce a configure script.
dnl
dnl This is free and unencumbered software released into the public domain.
AC_PREREQ([2.68])

dnl Define version information:
m4_define([VERSION_MAJOR],
  m4_esyscmd([cut -d'.' -f1 VERSION | tr -d '\n']))
m4_define([VERSION_MINOR],
  m4_esyscmd([cut -d'.' -f2 VERSION | tr -d '\n']))
m4_define([VERSION_PATCH],
  m4_esyscmd([cut -d'.' -f3 VERSION | tr -d '\n']))
m4_define([VERSION_STRING],
  m4_esyscmd([git describe --dirty --always | tr -d '\n']))

dnl Define package information:
AC_INIT([libxsd++], [VERSION_STRING],
  [arto@bendiken.net], [libxsd++],
  [https://github.com/datagraph/libxsd])

dnl Configure Autoconf:
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_SRCDIR([src/xsd++.h])
AC_CONFIG_AUX_DIR([etc/aclocal])
AC_CONFIG_MACRO_DIR([etc/aclocal])
AC_CONFIG_LIBOBJ_DIR([lib])

dnl Configure Automake:
AM_INIT_AUTOMAKE([foreign -Wall -Werror dist-bzip2 subdir-objects nostdinc])
AM_SILENT_RULES([yes])

dnl Check for programs:
AC_PROG_CC(clang gcc cc)
AC_PROG_CC_C99
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_CXX(clang++ g++ c++)
AC_PROG_CXXCPP
AC_USE_SYSTEM_EXTENSIONS
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT
PKG_PROG_PKG_CONFIG([0.24])
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext])

dnl Check for configuration options:
# --with-stdlib=libstdc++|libc++
AC_ARG_WITH([stdlib],
  [AS_HELP_STRING([--with-stdlib=LIB], [specify the C++ standard library to use [default=system]])],
  [], [with_stdlib=system])
AS_IF([test "x$with_stdlib" != "xsystem"],
  [CXXFLAGS="$CXXFLAGS -stdlib=$with_stdlib"
   LDFLAGS="$LDFLAGS -stdlib=$with_stdlib"])
# --with-icu/--without-icu
AC_ARG_WITH([icu],
  [AS_HELP_STRING([--with-icu], [support extended date/time ranges using ICU4C @<:@default=check@:>@])],
  [], [with_icu=check])
# --enable-debug/--disable-debug
AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug], [build with debugging support [default=no]])],
  [], [enable_debug=no])
AS_IF([test "x$enable_debug" != "xno"],
  [AC_DEFINE([DEBUG], [1], [Enable debugging support.])],
  [AC_DEFINE([NDEBUG], [1], [Disable assertions.])])
AM_CONDITIONAL([ENABLE_DEBUG], [test "x$enable_debug" != "xno"])
# --enable-unicode/--disable-unicode
AC_ARG_ENABLE([unicode],
  [AS_HELP_STRING([--disable-unicode], [omit support for Unicode strings])])
AS_IF([test "x$enable_unicode" == "xno"],
  [AC_DEFINE([DISABLE_UNICODE], 1, [Define to disable Unicode string support.])])

dnl Check for libraries:
# libboost (libboost-dev on Ubuntu, boost on Mac OS X + MacPorts)
AX_BOOST_BASE([1.48], [AX_BOOST_REGEX])
# libicu (libicu-dev on Ubuntu, icu on Mac OS X + MacPorts)
AS_IF([test "x$with_icu" != "xno"], [
  PKG_CHECK_MODULES([libicu], [icu-uc >= 52.1],
    [AC_DEFINE([HAVE_ICU], [1], [Define to 1 if you have ICU4C.])])
])
AM_CONDITIONAL([HAVE_ICU], [test "x$libicu_LIBS" != "x"])

dnl Check for header files:

dnl Check for types:

dnl Check for structures:

dnl Check for compiler characteristics:
AC_CANONICAL_HOST
AM_CPPFLAGS="$AM_CPPFLAGS -I\$(top_srcdir)/lib -I\$(top_srcdir)/src -iquote \$(srcdir) \$(BOOST_CPPFLAGS)"
AM_CXXFLAGS="$AM_CXXFLAGS -Wall -Wextra -pipe"
AM_LDFLAGS="$AM_LDFLAGS \$(BOOST_LDFLAGS) \$(BOOST_REGEX_LIB)"
TEST_CPPFLAGS="$AM_CPPFLAGS -DCATCH_CONFIG_MAIN"
TEST_CXXFLAGS="$AM_CXXFLAGS"
TEST_LDFLAGS="$AM_LDFLAGS"
AC_SUBST([AM_CPPFLAGS])
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])
AC_SUBST([TEST_CPPFLAGS])
AC_SUBST([TEST_CXXFLAGS])
AC_SUBST([TEST_LDFLAGS])

dnl Check for library functions:
AC_CHECK_FUNCS_ONCE([timegm])

dnl Check for system services:

dnl Generate output:
AC_CONFIG_FILES([Makefile lib/Makefile src/Makefile src/xsd++/Makefile test/Makefile])
AC_SUBST([PACKAGE_VERSION_MAJOR], ["VERSION_MAJOR"])
AC_SUBST([PACKAGE_VERSION_MINOR], ["VERSION_MINOR"])
AC_SUBST([PACKAGE_VERSION_PATCH], ["VERSION_PATCH"])
AC_CONFIG_FILES([src/xsd++/version.h])
AH_BOTTOM([#include "libcompat.h"])
AC_OUTPUT
