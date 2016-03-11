# correctly clean the generated source files
CLEANFILES = $(BUILT_SOURCES) $(man_MANS)

libexec_PROGRAMS = telepathy-cauchy

AM_VALAFLAGS = \
	-C \
	-H cauchy.h \
	--use-header \
	tp-base.vapi \
	--pkg=telepathy-glib \
	$(NULL)

libtp_cauchy_convenience_la_VALA_SOURCES = \
	cauchy-connection-manager.vala \
	cauchy-protocol.vala \
	$(NULL)

vala-stamp: $(libtp_cauchy_convenience_la_VALA_SOURCES)
	@rm -f vala-temp
	@touch vala-temp
	$(AM_V_GEN) $(VALAC) $(AM_VALAFLAGS) $^
	@mv -f vala-temp $@

CLEANFILES += \
	$(libtp_cauchy_convenience_la_VALA_SOURCES:.vala=.c) \
	$(NULL)

$(libtp_cauchy_convenience_la_VALA_SOURCES:.vala=.c): vala-stamp
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

libcauchy_convenience_la_SOURCES = \
	$(libtp_cauchy_convenience_la_VALA_SOURCES:.vala=.c) \
	cauchy-connection.c \
	cauchy-connection.h \
	cauchy-debug.c \
	cauchy-debug.h \
	cauchy-handles.c \
	cauchy-handles.h \
	cauchy-im-manager.c \
	cauchy-im-manager.h \
	cauchy-muc-manager.c \
	cauchy-muc-manager.h \
	cauchy-contact-info.c \
	cauchy-contact-info.h \
	$(NULL)

nodist_libcauchy_convenience_la_SOURCES = \
	$(BUILT_SOURCES)

telepathy_cauchy_SOURCES = \
	cauchy.c

telepathy_cauchy_LDADD = \
	libcauchy-convenience.la \
	$(ALL_LIBS)

noinst_LTLIBRARIES = libcauchy-convenience.la

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

man_MANS = telepathy-cauchy.8

EXTRA_DIST = telepathy-cauchy.8.in

%.8: %.8.in Makefile
	$(AM_V_GEN)sed -e 's,[@]libexecdir[@],@libexecdir@,' < $< > $@
