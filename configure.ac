dnl Process this file with autoconf to produce a configure script.
AC_INIT([xgraph],[12.1])
AC_CONFIG_SRCDIR([xgraph.c])
AM_INIT_AUTOMAKE([foreign])

AC_CONFIG_HEADERS([autoconf.h])

dnl Checks for programs.
AC_PROG_CC

dnl Checks for libraries.
AC_CHECK_LIB([m], [pow])
AC_CHECK_LIB([X11], [XOpenDisplay])
AC_PATH_X

dnl check header files.
AC_CHECK_HEADERS([float.h limits.h memory.h stdlib.h string.h strings.h unistd.h])

dnl checks for typedefs
dnl checks for structures
dnl checks for compiler characteristics

dnl checks for library functions
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([floor memset pow strcasecmp strchr])

dnl checks for system services

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
