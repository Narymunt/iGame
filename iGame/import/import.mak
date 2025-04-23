# Microsoft Developer Studio Generated NMAKE File, Based on import.dsp
!IF "$(CFG)" == ""
CFG=import - Win32 Debug
!MESSAGE No configuration specified. Defaulting to import - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "import - Win32 Release" && "$(CFG)" != "import - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "import.mak" CFG="import - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "import - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "import - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "import - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\import.exe"


CLEAN :
	-@erase "$(INTDIR)\FBackground.obj"
	-@erase "$(INTDIR)\FEpisode.obj"
	-@erase "$(INTDIR)\FEvent.obj"
	-@erase "$(INTDIR)\FGame.obj"
	-@erase "$(INTDIR)\FScene.obj"
	-@erase "$(INTDIR)\FSprite.obj"
	-@erase "$(INTDIR)\FWorld.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\import.exe"
	-@erase "$(OUTDIR)\import.ilk"
	-@erase "$(OUTDIR)\import.map"
	-@erase "$(OUTDIR)\import.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\import.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\import.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib fox.lib foxmain.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\import.pdb" /map:"$(INTDIR)\import.map" /debug /machine:I386 /out:"$(OUTDIR)\import.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FBackground.obj" \
	"$(INTDIR)\FEpisode.obj" \
	"$(INTDIR)\FEvent.obj" \
	"$(INTDIR)\FGame.obj" \
	"$(INTDIR)\FScene.obj" \
	"$(INTDIR)\FSprite.obj" \
	"$(INTDIR)\FWorld.obj" \
	"$(INTDIR)\main.obj"

"$(OUTDIR)\import.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "import - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\import.exe"


CLEAN :
	-@erase "$(INTDIR)\FBackground.obj"
	-@erase "$(INTDIR)\FEpisode.obj"
	-@erase "$(INTDIR)\FEvent.obj"
	-@erase "$(INTDIR)\FGame.obj"
	-@erase "$(INTDIR)\FScene.obj"
	-@erase "$(INTDIR)\FSprite.obj"
	-@erase "$(INTDIR)\FWorld.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\import.exe"
	-@erase "$(OUTDIR)\import.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\import.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\import.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib FOX.lib FOXmain.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\import.pdb" /machine:I386 /out:"$(OUTDIR)\import.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\FBackground.obj" \
	"$(INTDIR)\FEpisode.obj" \
	"$(INTDIR)\FEvent.obj" \
	"$(INTDIR)\FGame.obj" \
	"$(INTDIR)\FScene.obj" \
	"$(INTDIR)\FSprite.obj" \
	"$(INTDIR)\FWorld.obj" \
	"$(INTDIR)\main.obj"

"$(OUTDIR)\import.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("import.dep")
!INCLUDE "import.dep"
!ELSE 
!MESSAGE Warning: cannot find "import.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "import - Win32 Release" || "$(CFG)" == "import - Win32 Debug"
SOURCE=.\FBackground.cpp

"$(INTDIR)\FBackground.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FEpisode.cpp

"$(INTDIR)\FEpisode.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FEvent.cpp

"$(INTDIR)\FEvent.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FGame.cpp

"$(INTDIR)\FGame.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FScene.cpp

"$(INTDIR)\FScene.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FSprite.cpp

"$(INTDIR)\FSprite.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FWorld.cpp

"$(INTDIR)\FWorld.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

