# correctly clean the generated source files
CLEANFILES = $(BUILT_SOURCES) $(man_MANS)

libexec_PROGRAMS = telepathy-matrix

AM_VALAFLAGS = -C --pkg=telepathy-glib

libtp_matrix_convenience_la_VALA_SOURCES = \
	$(NULL)

vala-stamp: $(libtp_matrix_convenience_la_VALA_SOURCES)
	@rm -f vala-temp
	@touch vala-temp
	$(AM_V_GEN) $(VALAC) $(AM_VALAFLAGS) $^
	@mv -f vala-temp $@

CLEANFILES += \
	$(libtp_matrix_convenience_la_VALA_SOURCES:.vala=.c) \
	$(NULL)

$(libtp_matrix_convenience_la_VALA_SOURCES:.vala=.c): vala-stamp
	@if test -f $@; then :; else \
	    trap 'rm -rf vala-lock vala-stamp' 1 2 13 15; \
	    if mkdir vala-lock 2> /dev/null; then \
	        rm -f vala-stamp; \
	        $(MAKE) $(AM_MAKEFLAGS) vala-stamp; \
	        rmdir vala-lock; \
	    else \
	        while test -d vala-lock; do sleep 1; done; \
	        test -f vala-stamp; exit $$?; \
	    fi \
	fi

libmatrix_convenience_la_SOURCES = \
	$(libtp_matrix_convenience_la_VALA_SOURCES:.vala=.c) \
	matrix-connection-manager.c \
	matrix-connection-manager.h \
	matrix-protocol.c \
	matrix-protocol.h \
	matrix-debug.c \
	matrix-debug.h \
	matrix-handles.c \
	matrix-handles.h \
	matrix-connection.c \
	matrix-connection.h \
	matrix-im-manager.c \
	matrix-im-manager.h \
	matrix-muc-manager.c \
	matrix-muc-manager.h \
	matrix-contact-info.c \
	matrix-contact-info.h \
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
