###############################################################################
#####               This makefile generates ELWEP.DLL                     #####
###############################################################################
!include $(WGDEV)\src\gcrules.mak

VIRDIR = .\GCVIRDAT

PARSEOPTS = $(PARSEOPTS) -DIS30

DEFILE =

VIRFILES =          \
     GCVIRDAT\elwepcou.vir \
     GCVIRDAT\elwepnws.vir \
     GCVIRDAT\elweppa.vir  \
     GCVIRDAT\elweppm.vir  \
     GCVIRDAT\elwepusr.vir 
     
DLLLIB =            \
     $(DLLLIB)      \
     wgserver.lib   \
     galgsbl.lib

OBJFILES =          \
     elwep.obj     

elwep.dll:          \
     $(GCBUILD)     \
     $(OBJFILES)    \
     $(DLLLIB)      \
     $(DEFILE)      \
     $(VIRFILES)
     $(LINK) $(LIBCMD) @&&|
$(PRODLL) $(OBJFILES)
$(RUNDIR)\$&
$(RUNDIR)\$&
$(DLLLIB) $(LINKDLL)
$(DEFILE)
|
