# Process this file with autoconf to produce a configure script

### Version numbers

# Release Versions
m4_define([tp_matrix_major_version], [0])
m4_define([tp_matrix_minor_version], [0])
m4_define([tp_matrix_micro_version], [0])
m4_define([tp_matrix_nano_version], [1])

m4_define([tp_matrix_base_version],
          [tp_matrix_major_version.tp_matrix_minor_version.tp_matrix_micro_version])
m4_define([tp_matrix_version],
          [m4_if(tp_matrix_nano_version, 0,
                 [tp_matrix_base_version],
                 [tp_matrix_base_version].[tp_matrix_nano_version])])

### Setup

# Initialise autoconf with project details, version
AC_INIT([telepathy-matrix], matrix_version,
        [gergely@polonkai.eu], [telepathy-matrix])

# Enable silent build rules by default, requires at least
# Automake-1.11. Disable by either passing --disable-silent-rules to
# configure or passing V=1 to make
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_PREREQ([2.60])

AC_CONFIG_MACRO_DIR([m4])
AM_CONFIG_HEADER(config.h)
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.9 -Wno-portability subdir-objects])

dnl check for tools
AC_PROG_CC
AC_PROG_CC_STDC
AM_PROG_LIBTOOL
AC_PROG_MKDIR_P
AM_PROG_AS

VALAC_CHECK


# these aren't really error flags but they serve a similar purpose for us -
# making the toolchain stricter
AS_IF([test "x$enable_fatal_warnings" = xyes],
  [TP_ADD_LINKER_FLAG([ERROR_LDFLAGS], [-Wl,--no-copy-dt-needed-entries])])

AC_HEADER_STDC([])
AC_C_INLINE

AC_DEFINE(GLIB_VERSION_MIN_REQUIRED, GLIB_VERSION_2_28, [Ignore post 2.28 deprecations])
AC_DEFINE(GLIB_VERSION_MAX_ALLOWED, GLIB_VERSION_2_32, [Prevent post 2.32 APIs])

PKG_CHECK_MODULES([GLIB],
  [glib-2.0 >= 2.32.0, gobject-2.0 >= 2.32.0, gio-2.0 >= 2.32.0 ])

PKG_CHECK_MODULES([DBUS], [dbus-1 >= 0.51, dbus-glib-1 >= 0.51])

AC_DEFINE([TP_SEAL_ENABLE], [], [Prevent to use sealed variables])
AC_DEFINE([TP_DISABLE_SINGLE_INCLUDE], [], [Disable single header include])
AC_DEFINE(TP_VERSION_MIN_REQUIRED, TP_VERSION_0_22, [Ignore post 0.22 deprecations])
AC_DEFINE(TP_VERSION_MAX_ALLOWED, TP_VERSION_0_22, [Prevent post 0.22 APIs])
PKG_CHECK_MODULES([TELEPATHY], [telepathy-glib >= 0.21])

dnl Check for code generation tools
XSLTPROC=
AC_CHECK_PROGS([XSLTPROC], [xsltproc])
AS_IF([test -z "$XSLTPROC"],
  [AC_MSG_ERROR([xsltproc (from the libxslt source package) is required])])

AS_AC_EXPAND(DATADIR, $datadir)
DBUS_SERVICES_DIR="$DATADIR/dbus-1/services"
AC_SUBST(DBUS_SERVICES_DIR)
AC_DEFINE_UNQUOTED(DBUS_SERVICES_DIR, "$DBUS_SERVICES_DIR", [DBus services directory])

AC_CHECK_FUNCS(strnlen)

AC_CONFIG_FILES([
    Makefile
    data/Makefile
    m4/Makefile
    src/Makefile
    tools/Makefile
])
AC_OUTPUT
