# correctly clean the generated source files
CLEANFILES = $(BUILT_SOURCES) $(man_MANS)

libexec_PROGRAMS=telepathy-matrix

libmatrix_convenience_la_SOURCES = \
	matrix-connection-manager.c \
	matrix-connection-manager.h \
	matrix-protocol.c \
	matrix-protocol.h \
	matrix-debug.c \
	matrix-debug.h \
	$(NULL)

nodist_libmatrix_convenience_la_SOURCES = \
	$(BUILT_SOURCES)

telepathy_matrix_SOURCES = \
	matrix.c

telepathy_matrix_LDADD = \
	libmatrix-convenience.la \
	$(ALL_LIBS)

noinst_LTLIBRARIES = libmatrix-convenience.la

AM_CFLAGS = \
	-I$(top_srcdir) \
	-I$(top_builddir) \
	$(ERROR_CFLAGS) \
	@DBUS_CFLAGS@ \
	@GLIB_CFLAGS@ \
	@TELEPATHY_CFLAGS@ \
	-std=c99

AM_LDFLAGS = \
	$(ERROR_LDFLAGS) \
	$(NULL)

ALL_LIBS = \
	@DBUS_LIBS@ \
	@GLIB_LIBS@ \
	@TELEPATHY_LIBS@

man_MANS = telepathy-matrix.8

EXTRA_DIST = telepathy-matrix.8.in

%.8: %.8.in Makefile
	$(AM_V_GEN)sed -e 's,[@]libexecdir[@],@libexecdir@,' < $< > $@
