# Makefile generated by imake - do not edit!
# $XConsortium: imake.c,v 1.65 91/07/25 17:50:17 rws Exp $
#
# The cpp used on this machine replaces all newlines and multiple tabs and
# spaces in a macro expansion with a single space.  Imake tries to compensate
# for this, but is not always successful.
#

# -------------------------------------------------------------------------
# Makefile generated from "Imake.tmpl" and </tmp/IIf.a004b3>
# $XConsortium: Imake.tmpl,v 1.139 91/09/16 08:52:48 rws Exp $
#
# Platform-specific parameters may be set in the appropriate <vendor>.cf
# configuration files.  Site-specific parameters should be set in the file
# site.def.  Full rebuilds are recommended if any parameters are changed.
#
# If your C preprocessor does not define any unique symbols, you will need
# to set BOOTSTRAPCFLAGS when rebuilding imake (usually when doing
# "make World" the first time).
#

# -------------------------------------------------------------------------
# site-specific configuration parameters that need to come before
# the platform-specific parameters - edit site.def to change

# site:  $XConsortium: site.def,v 1.2 91/07/30 20:26:44 rws Exp $

# -------------------------------------------------------------------------
# platform-specific configuration parameters - edit sun.cf to change

# platform:  $XConsortium: sun.cf,v 1.72.1.1 92/03/18 13:13:37 rws Exp $

# operating system:  SunOS 5.1

# $XConsortium: sv4Lib.rules,v 1.8 91/07/19 15:38:53 rws Exp $

# -------------------------------------------------------------------------
# site-specific configuration parameters that go after
# the platform-specific parameters - edit site.def to change

# site:  $XConsortium: site.def,v 1.2 91/07/30 20:26:44 rws Exp $

            SHELL = /bin/sh

              TOP = .
      CURRENT_DIR = .

               AR = ar cq
  BOOTSTRAPCFLAGS = -DSVR4
               CC = gcc -fpcc-struct-return
               AS = as

         COMPRESS = compress
              CPP = /usr/ccs/lib/cpp $(STD_CPP_DEFINES)
    PREPROCESSCMD = gcc -fpcc-struct-return -E $(STD_CPP_DEFINES)
          INSTALL = /usr/ucb/install
               LD = gcc -nostdlib
             LINT = lint
      LINTLIBFLAG = -o
         LINTOPTS = -ax
               LN = ln -s
             MAKE = make
               MV = mv
               CP = cp

               RM = rm -f
            TROFF = psroff
         MSMACROS = -ms
              TBL = tbl
              EQN = eqn
     STD_INCLUDES =
  STD_CPP_DEFINES = -DSVR4 -DSYSV
      STD_DEFINES = -DSVR4 -DSYSV
 EXTRA_LOAD_FLAGS =
  EXTRA_LIBRARIES = -lsocket -lnsl
             TAGS = ctags

    SHAREDCODEDEF =
         SHLIBDEF =

    PROTO_DEFINES = -DFUNCPROTO=15

     INSTPGMFLAGS =

     INSTBINFLAGS = -m 0755
     INSTUIDFLAGS = -m 4755
     INSTLIBFLAGS = -m 0644
     INSTINCFLAGS = -m 0444
     INSTMANFLAGS = -m 0444
     INSTDATFLAGS = -m 0444
    INSTKMEMFLAGS = -g sys -m 2755

      PROJECTROOT = /local/X11R5

     TOP_INCLUDES = -I$(INCROOT)

      CDEBUGFLAGS = -O2
        CCOPTIONS =

      ALLINCLUDES = $(INCLUDES) $(EXTRA_INCLUDES) $(TOP_INCLUDES) $(STD_INCLUDES)
       ALLDEFINES = $(ALLINCLUDES) $(STD_DEFINES) $(EXTRA_DEFINES) $(PROTO_DEFINES) $(DEFINES)
           CFLAGS = $(CDEBUGFLAGS) $(CCOPTIONS) $(ALLDEFINES)
        LINTFLAGS = $(LINTOPTS) -DLINT $(ALLDEFINES)

           LDLIBS = $(SYS_LIBRARIES) $(EXTRA_LIBRARIES)

        LDOPTIONS = $(CDEBUGFLAGS) $(CCOPTIONS) $(LOCAL_LDFLAGS) -L$(USRLIBDIR) -R$(USRLIBDIR)$${LD_RUN_PATH+\:$$LD_RUN_PATH}

   LDCOMBINEFLAGS = -r
      DEPENDFLAGS =

        MACROFILE = sun.cf
           RM_CMD = $(RM) *.CKP *.ln *.BAK *.bak *.o core errs ,* *~ *.a .emacs_* tags TAGS make.log MakeOut

    IMAKE_DEFINES =

         IRULESRC = $(CONFIGDIR)
        IMAKE_CMD = $(IMAKE) -DUseInstalled -I$(IRULESRC) $(IMAKE_DEFINES)

     ICONFIGFILES = $(IRULESRC)/Imake.tmpl $(IRULESRC)/Imake.rules \
			$(IRULESRC)/Project.tmpl $(IRULESRC)/site.def \
			$(IRULESRC)/$(MACROFILE) $(EXTRA_ICONFIGFILES)

# -------------------------------------------------------------------------
# X Window System Build Parameters
# $XConsortium: Project.tmpl,v 1.138.1.1 92/11/11 09:49:19 rws Exp $

# -------------------------------------------------------------------------
# X Window System make variables; this need to be coordinated with rules

          PATHSEP = /
        USRLIBDIR = /local/X11R5/lib
           BINDIR = /local/X11R5/bin
          INCROOT = /local/X11R5/include
     BUILDINCROOT = $(TOP)
      BUILDINCDIR = $(BUILDINCROOT)/X11
      BUILDINCTOP = ..
           INCDIR = $(INCROOT)/X11
           ADMDIR = /usr/adm
           LIBDIR = $(USRLIBDIR)/X11
        CONFIGDIR = $(LIBDIR)/config
       LINTLIBDIR = $(USRLIBDIR)/lint

          FONTDIR = $(LIBDIR)/fonts
         XINITDIR = $(LIBDIR)/xinit
           XDMDIR = $(LIBDIR)/xdm
           TWMDIR = $(LIBDIR)/twm
          MANPATH = /local/X11R5/man
    MANSOURCEPATH = $(MANPATH)/man
        MANSUFFIX = n
     LIBMANSUFFIX = 3
           MANDIR = $(MANSOURCEPATH)$(MANSUFFIX)
        LIBMANDIR = $(MANSOURCEPATH)$(LIBMANSUFFIX)
           NLSDIR = $(LIBDIR)/nls
        PEXAPIDIR = $(LIBDIR)/PEX
      XAPPLOADDIR = $(LIBDIR)/app-defaults
       FONTCFLAGS = -t

     INSTAPPFLAGS = $(INSTDATFLAGS)

            IMAKE = imake
           DEPEND = makedepend
              RGB = rgb

            FONTC = bdftopcf

        MKFONTDIR = mkfontdir
        MKDIRHIER = /bin/sh $(BINDIR)/mkdirhier

        CONFIGSRC = $(TOP)/config
       DOCUTILSRC = $(TOP)/doc/util
        CLIENTSRC = $(TOP)/clients
          DEMOSRC = $(TOP)/demos
           LIBSRC = $(TOP)/lib
          FONTSRC = $(TOP)/fonts
       INCLUDESRC = $(TOP)/X11
        SERVERSRC = $(TOP)/server
          UTILSRC = $(TOP)/util
        SCRIPTSRC = $(UTILSRC)/scripts
       EXAMPLESRC = $(TOP)/examples
       CONTRIBSRC = $(TOP)/../contrib
           DOCSRC = $(TOP)/doc
           RGBSRC = $(TOP)/rgb
        DEPENDSRC = $(UTILSRC)/makedepend
         IMAKESRC = $(CONFIGSRC)
         XAUTHSRC = $(LIBSRC)/Xau
          XLIBSRC = $(LIBSRC)/X
           XMUSRC = $(LIBSRC)/Xmu
       TOOLKITSRC = $(LIBSRC)/Xt
       AWIDGETSRC = $(LIBSRC)/Xaw
       OLDXLIBSRC = $(LIBSRC)/oldX
      XDMCPLIBSRC = $(LIBSRC)/Xdmcp
      BDFTOSNFSRC = $(FONTSRC)/bdftosnf
      BDFTOSNFSRC = $(FONTSRC)/clients/bdftosnf
      BDFTOPCFSRC = $(FONTSRC)/clients/bdftopcf
     MKFONTDIRSRC = $(FONTSRC)/clients/mkfontdir
         FSLIBSRC = $(FONTSRC)/lib/fs
    FONTSERVERSRC = $(FONTSRC)/server
     EXTENSIONSRC = $(TOP)/extensions
         XILIBSRC = $(EXTENSIONSRC)/lib/xinput
        PEXLIBSRC = $(EXTENSIONSRC)/lib/PEXlib
      PHIGSLIBSRC = $(EXTENSIONSRC)/lib/PEX

# $XConsortium: sv4Lib.tmpl,v 1.4.1.1 92/11/11 09:57:17 rws Exp $

SHLIBLDFLAGS = -G -z text
PICFLAGS = -fPIC

  DEPEXTENSIONLIB =
     EXTENSIONLIB = -lXext

          DEPXLIB = $(DEPEXTENSIONLIB)
             XLIB = $(EXTENSIONLIB) -lX11

        DEPXMULIB =
       XMULIBONLY = -lXmu

           XMULIB = -lXmu

       DEPOLDXLIB =
          OLDXLIB = -loldX

      DEPXTOOLLIB =
         XTOOLLIB = -lXt

        DEPXAWLIB =
           XAWLIB = -lXaw

        DEPXILIB =
           XILIB = -lXi

        DEPPEXLIB =
         PEXLIB = -lPEX5

        SOXLIBREV = 5.0
          SOXTREV = 5.0
         SOXAWREV = 5.0
        SOOLDXREV = 5.0
         SOXMUREV = 5.0
        SOXEXTREV = 5.0
      SOXINPUTREV = 5.0
         SOPEXREV = 1.0

      DEPXAUTHLIB = $(USRLIBDIR)/libXau.a
         XAUTHLIB =  -lXau
      DEPXDMCPLIB = $(USRLIBDIR)/libXdmcp.a
         XDMCPLIB =  -lXdmcp

        DEPPHIGSLIB = $(USRLIBDIR)/libphigs.a
           PHIGSLIB =  -lphigs

       DEPXBSDLIB = $(USRLIBDIR)/libXbsd.a
          XBSDLIB =  -lXbsd

 LINTEXTENSIONLIB = $(LINTLIBDIR)/llib-lXext.ln
         LINTXLIB = $(LINTLIBDIR)/llib-lX11.ln
          LINTXMU = $(LINTLIBDIR)/llib-lXmu.ln
        LINTXTOOL = $(LINTLIBDIR)/llib-lXt.ln
          LINTXAW = $(LINTLIBDIR)/llib-lXaw.ln
           LINTXI = $(LINTLIBDIR)/llib-lXi.ln
          LINTPEX = $(LINTLIBDIR)/llib-lPEX5.ln
        LINTPHIGS = $(LINTLIBDIR)/llib-lphigs.ln

          DEPLIBS = $(DEPXAWLIB) $(DEPXMULIB) $(DEPXTOOLLIB) $(DEPXLIB)

         DEPLIBS1 = $(DEPLIBS)
         DEPLIBS2 = $(DEPLIBS)
         DEPLIBS3 = $(DEPLIBS)

# -------------------------------------------------------------------------
# Imake rules for building libraries, programs, scripts, and data files
# rules:  $XConsortium: Imake.rules,v 1.123 91/09/16 20:12:16 rws Exp $

# -------------------------------------------------------------------------
# start of Imakefile

#
# xgraph - program to graphically display numerical data
#
# David Harrison
# University of California, Berkeley
# 1989
#
# Copyright (c) 1988, 1989, Regents of the University of California.
# All rights reserved.
#
# Use and copying of this software and preparation of derivative works
# based upon this software are permitted.  However, any distribution of
# this software or derivative works must include the above copyright
# notice.
#
# This software is made available AS IS, and neither the Electronics
# Research Laboratory or the University of California make any
# warranty about the software, its performance or its conformity to
# any specification.
#
# Suggestions, comments, or improvements are welcome and should be
# addressed to:
#
#   davidh@ic.Berkeley.EDU
#   ..!ucbvax!ic!davidh
#

        DEFINES =
LOCAL_LIBRARIES = $(XLIB)
  SYS_LIBRARIES = -lm
           SRCS = xgraph.c xgX.c hard_devices.c dialog.c hpgl.c \
		  ps.c idraw.c xtb.c st.c params.c
           OBJS = xgraph.o xgX.o hard_devices.o dialog.o hpgl.o \
		  ps.o idraw.o xtb.o st.o params.o

 PROGRAM = xgraph

all:: xgraph

xgraph: $(OBJS) $(DEPLIBS)
	$(RM) $@
	$(CC) -o $@ $(OBJS) $(LDOPTIONS) $(LOCAL_LIBRARIES) $(LDLIBS) $(EXTRA_LOAD_FLAGS)

saber_xgraph:: $(SRCS)
	# load $(ALLDEFINES) $(SRCS) $(LOCAL_LIBRARIES) $(SYS_LIBRARIES) $(EXTRA_LIBRARIES)

osaber_xgraph:: $(OBJS)
	# load $(ALLDEFINES) $(OBJS) $(LOCAL_LIBRARIES) $(SYS_LIBRARIES) $(EXTRA_LIBRARIES)

install:: xgraph
	@if [ -d $(DESTDIR)$(BINDIR) ]; then set +x; \
	else (set -x; $(MKDIRHIER) $(DESTDIR)$(BINDIR)); fi
	$(INSTALL) -c $(INSTPGMFLAGS)  xgraph $(DESTDIR)$(BINDIR)

install.man:: xgraph.man
	@if [ -d $(DESTDIR)$(MANDIR) ]; then set +x; \
	else (set -x; $(MKDIRHIER) $(DESTDIR)$(MANDIR)); fi
	$(INSTALL) -c $(INSTMANFLAGS) xgraph.man $(DESTDIR)$(MANDIR)/xgraph.$(MANSUFFIX)

depend::
	$(DEPEND) $(DEPENDFLAGS) -s "# DO NOT DELETE" -- $(ALLDEFINES) -- $(SRCS)

lint:
	$(LINT) $(LINTFLAGS) $(SRCS) $(LINTLIBS)
lint1:
	$(LINT) $(LINTFLAGS) $(FILE) $(LINTLIBS)

clean::
	$(RM) $(PROGRAM)

# -------------------------------------------------------------------------
# common rules for all Makefiles - do not edit

emptyrule::

clean::
	$(RM_CMD) "#"*

Makefile::
	-@if [ -f Makefile ]; then set -x; \
	$(RM) Makefile.bak; $(MV) Makefile Makefile.bak; \
	else exit 0; fi
	$(IMAKE_CMD) -DTOPDIR=$(TOP) -DCURDIR=$(CURRENT_DIR)

tags::
	$(TAGS) -w *.[ch]
	$(TAGS) -xw *.[ch] > TAGS

saber:
	# load $(ALLDEFINES) $(SRCS)

osaber:
	# load $(ALLDEFINES) $(OBJS)

# -------------------------------------------------------------------------
# empty rules for directories that do not have SUBDIRS - do not edit

install::
	@echo "install in $(CURRENT_DIR) done"

install.man::
	@echo "install.man in $(CURRENT_DIR) done"

Makefiles::

includes::

# -------------------------------------------------------------------------
# dependencies generated by makedepend
