# not GPL, thus no COPYING
AUTOMAKE_OPTIONS=dist-xz foreign

ACLOCAL_AMFLAGS=	-I m4

SUBDIRS=lib man src regress examples

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libzip.pc

EXTRA_DIST=	API-CHANGES \
		CMakeLists.txt \
		LICENSE \
		NEWS.md \
		README.md \
		TODO.md \
		cmake-config.h.in \
		cmake-zipconf.h.in \
		libzip-uninstalled.pc.in \
		libzip.pc.in \
		m4

not-dist-hook:
	mkdir $(distdir)/xcode
	mkdir $(distdir)/xcode/libzip.xcodeproj
	mkdir $(distdir)/xcode/libzip.xcodeproj/project.xcworkspace
	cp -p $(srcdir)/xcode/Info.plist \
		  $(srcdir)/xcode/config.h \
		  $(srcdir)/xcode/extract-version.sh \
		  $(srcdir)/xcode/zipconf.h $(distdir)/xcode
	cp -p $(srcdir)/xcode/libzip.xcodeproj/project.pbxproj $(distdir)/xcode/libzip.xcodeproj
	cp -p $(srcdir)/xcode/libzip.xcodeproj/project.xcworkspace/contents.xcworkspacedata \
		$(distdir)/xcode/libzip.xcodeproj/project.xcworkspace
