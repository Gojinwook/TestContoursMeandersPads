#-----------------------------------------------------------------------------
# HALCON extension package example "halconuser"
#
# General, makefile independed rule definitions for HALCON extension package
# examples
#
#-----------------------------------------------------------------------------
# Copyright (c) 1996-2018 MVTec Software GmbH, http://www.mvtec.com
#-----------------------------------------------------------------------------


all:
	$(MAKE) -f$(MAKE_DIR)$(MAKE_FILE) xpackage
	$(MAKE) -f$(MAKE_DIR)$(MAKE_FILE) XL=1 xpackage

xpackage:    $(BIN_DIR) $(OBJ_DIR) $(LIB_DIR) $(XPKG_LIB_H) $(XPKG_LIB_C) $(XPKG_LIB_CPP) \
	$(XPKG_HELP)$(SL)$(HELP_NAME).ref

cpp10:
	$(MAKE) -f$(MAKE_DIR)$(MAKE_FILE) xpkg_cpp10
	$(MAKE) -f$(MAKE_DIR)$(MAKE_FILE) XL=1 xpkg_cpp10

xpkg_cpp10: $(XPKG_LIB_CPP10)

dotnet: 
	$(MAKE) -f$(MAKE_DIR)$(MAKE_FILE) xpkg_dotnet
	$(MAKE) -f$(MAKE_DIR)$(MAKE_FILE) XL=1 xpkg_dotnet

xpkg_dotnet: $(XPKG_LIB_DOTNET)

app: $(BIN_DIR) all $(APPLICATION_C)	$(APPLICATION_CPP)
app_dotnet: dotnet $(BIN_DIR_DOTNET) $(APPLICATION_DOTNET)


#-----------------------------------------------------------------------------
# Rules for generating the user extension libs (HALCON):

$(XPKG_LIB_H): $(XPKG_OBJS)
	$(LD) $(LFLAGS_SH) $(LFLAGS) $(AR_OUT)$(XPKG_LIB_H) $(XPKG_OBJS) \
	  $(EXTRA_LFLAGS_LIB)

$(XPKG_LIB_C): $(XPKG_C_OBJS) $(XPKG_LIB_H)
	$(LD) $(LFLAGS_SH) $(LFLAGS) $(AR_OUT)$(XPKG_LIB_C) $(XPKG_C_OBJS) \
	  $(XPKG_LIB) $(EXTRA_LFLAGS_C_LIB)

$(XPKG_LIB_CPP): $(XPKG_CPP_OBJS) $(XPKG_LIB_H)
	$(LD) $(LFLAGS_SH) $(LFLAGS) $(AR_OUT)$(XPKG_LIB_CPP) $(XPKG_CPP_OBJS) \
	  $(XPKG_LIB) $(EXTRA_LFLAGS_CPP_LIB)

$(XPKG_LIB_CPP10): $(XPKG_CPP10_OBJS) $(XPKG_LIB_H)
	$(LD) $(LFLAGS_SH) $(LFLAGS) $(AR_OUT)$(XPKG_LIB_CPP10) $(XPKG_CPP10_OBJS) \
	  $(XPKG_LIB) $(EXTRA_LFLAGS_CPP10_LIB)

#-----------------------------------------------------------------------------

# common rules for compiling user extension source code (HALCON):
# gmake syntax:
$(OBJ_DIR)/%.$(O): $(XPKG_SRC)/%.c
	$(CC) $(CFLAGS) $(HCINCLUDES) -c $(OUT_FLAG) $@ $<

$(OBJ_DIR)/%.$(O): $(XPKG_SRC)/%.cpp
	$(CCC) $(CFLAGS) $(HCPPINCLUDES) -c $(OUT_FLAG) $@ $<


# nmake syntax:
{$(XPKG_SRC)}.c{$(OBJ_DIR)}.$(O):
	$(CC) $(CFLAGS) $(HCINCLUDES) /c $(OUT_FLAG)$@ $<

{$(XPKG_SRC)}.cpp{$(OBJ_DIR)}.$(O):
	$(CC) $(CFLAGS) $(HCPPINCLUDES) /I$(XPKG_INC) /DH_PARALLEL /c $(OUT_FLAG)$@ $<


# Special rules for compiling against old C++ interface:
# gmake syntax
$(XPKG_CPP10_OBJS): $(XPKG_SRC)$(SL)HCPP10$(PACKAGE_NAME).cpp
	$(CCC) $(HCPP10INCLUDES) $(CFLAGS) -DH_PARALLEL -c \
                $(OUT_FLAG)$(XPKG_CPP10_OBJS) \
                $(XPKG_SRC)$(SL)HCPP10$(PACKAGE_NAME).cpp
# nmake syntax
{$(XPKG_SRC)}.cpp{$(XPKG_CPP10_OBJS)}.$(O):
	$(CC) /I"$(H_INCLUDE_CPP10)" $(CFLAGS) /DH_PARALLEL /c $(OUT_FLAG)$@ $<


# Rules for calling hcomp to generate source code and documentation:

$(XPKG_SRC)/H$(PACKAGE_NAME).c: $(XPKG_DEF_FILES) $(XPKG_INC)
	$(HCOMP) -u -H -p$(PACKAGE_NAME) $(XPKG_DEF_FILES)
	$(CP) H$(PACKAGE_NAME).c $(XPKG_SRC)
	$(RM) H$(PACKAGE_NAME).c

$(XPKG_SRC)/HC$(PACKAGE_NAME).c $(XPKG_INC)/HC$(PACKAGE_NAME).h: \
	    $(XPKG_DEF_FILES) $(XPKG_INC)
	$(HCOMP) -u -C -p$(PACKAGE_NAME) $(XPKG_DEF_FILES)
	$(CP) HC$(PACKAGE_NAME).h $(XPKG_INC)
	$(CP) HC$(PACKAGE_NAME).c $(XPKG_SRC)
	$(RM) HC$(PACKAGE_NAME).h
	$(RM) HC$(PACKAGE_NAME).c

$(XPKG_SRC)/HCPP$(PACKAGE_NAME).cpp $(XPKG_INC)/HCPP$(PACKAGE_NAME).h: \
	    $(XPKG_DEF_FILES) $(XPKG_INC)
	$(HCOMP) -u -P -p$(PACKAGE_NAME) $(XPKG_DEF_FILES)
	$(CP) HCPP$(PACKAGE_NAME).h $(XPKG_INC)
	$(CP) HCPP$(PACKAGE_NAME).cpp $(XPKG_SRC)
	$(RM) HCPP$(PACKAGE_NAME).h
	$(RM) HCPP$(PACKAGE_NAME).cpp

$(XPKG_SRC)/HCPP10$(PACKAGE_NAME).cpp $(XPKG_INC)/HCPP10$(PACKAGE_NAME).h: \
	    $(XPKG_DEF_FILES) $(XPKG_INC)
	$(HCOMP) -u -D -p$(PACKAGE_NAME) $(XPKG_DEF_FILES)
	$(CP) HCPP10$(PACKAGE_NAME).h $(XPKG_INC)
	$(CP) HCPP10$(PACKAGE_NAME).cpp $(XPKG_SRC)
	$(RM) HCPP10$(PACKAGE_NAME).h
	$(RM) HCPP10$(PACKAGE_NAME).cpp

$(XPKG_SRC)/HDOTNET$(PACKAGE_NAME).cs: $(XPKG_DEF_FILES)
	$(HCOMP) -u -N -p$(PACKAGE_NAME) $(XPKG_DEF_FILES)
	$(CP) HDOTNET$(PACKAGE_NAME).cs $(XPKG_SRC)
	$(RM) HDOTNET$(PACKAGE_NAME).cs

$(XPKG_HELP)$(SL)$(HELP_NAME).ref: $(XPKG_DEF_FILES) $(XPKG_HELP) $(XPKG_DOC_REF)
	$(HCOMP) -u -M -p$(PACKAGE_NAME) $(XPKG_DEF_FILES)
	$(CP) $(HELP_NAME).* $(XPKG_HELP)
	$(RM) $(HELP_NAME).*
	$(HCOMP) -u -R -p$(PACKAGE_NAME) -a"MVTec Software GmbH" \
	    -f"Copyright 1996-2018 MVTec Software GmbH" $(XPKG_DEF_FILES)
	$(CP) *.html $(XPKG_DOC_REF)
	$(RM) *.html


#-----------------------------------------------------------------------------
# common rules for linking application source code (HALCON):
#
# gmake syntax:
$(BIN_DIR)$(SL)%$(EXE)$(HSUFFIX): $(XPKG_SRC)$(SL)%.c $(XPKG_LIB_H) $(XPKG_LIB_C)
	$(LD) $(LFLAGS) $(CFLAGS) $(HCINCLUDES) \
	$(OUT_FLAG)$(BIN_DIR)$(SL)$*$(HSUFFIX) $< \
	-L$(LIB_DIR) -l$(XPKG_LIB_C_NAME) -l$(XPKG_LIB_NAME) \
	$(H_CLIBS) $(EXTRA_LFLAGS)

$(BIN_DIR)$(SL)%$(EXE)$(HSUFFIX): $(XPKG_SRC)$(SL)%.cpp $(XPKG_LIB_H) $(XPKG_LIB_CPP)
	$(CCC) $(LFLAGS) $(CFLAGS) $(HCPPINCLUDES) \
	$(OUT_FLAG)$(BIN_DIR)$(SL)$*$(HSUFFIX) $< \
	-L$(LIB_DIR) -l$(XPKG_LIB_CPP_NAME) -l$(XPKG_LIB_NAME) \
	$(H_CPPLIBS) $(EXTRA_LFLAGS)

#nmake syntax: 
#  Note: nmake syntax does not support file prefixes/suffixes -> explicite rules
COMP_C = $(CC) $(CFLAGS)  $(HCINCLUDES) $** $(OUT_FLAG)$(OBJ_DIR) \
  $(LIB_DIR)$(SL)$(XPKG_LIB_C_NAME).lib $(H_CLIBS) \
	/link $(AR_OUT)$*.exe

COMP_CXX = $(CCC) $(CFLAGS) $(HCPPINCLUDES)  $** $(OUT_FLAG)$(OBJ_DIR) \
  $(LIB_DIR)$(SL)$(XPKG_LIB_CPP_NAME).lib $(H_CPPLIBS) \
	/link $(AR_OUT)$*.exe

$(BIN_DIR)$(SL)testthreshold$(HSUFFIX).exe: $(XPKG_SRC)$(SL)testthreshold.c 
	$(COMP_C)

$(BIN_DIR)$(SL)testprint$(HSUFFIX).exe: $(XPKG_SRC)$(SL)testprint.c
	$(COMP_C)

$(BIN_DIR)$(SL)testregionfeatures$(HSUFFIX).exe: $(XPKG_SRC)$(SL)testregionfeatures.c
	$(COMP_C)

$(BIN_DIR)$(SL)testfilter$(HSUFFIX).exe: $(XPKG_SRC)$(SL)testfilter.c
	$(COMP_C)

$(BIN_DIR)$(SL)testthresholdcpp$(HSUFFIX).exe: $(XPKG_SRC)$(SL)testthresholdcpp.cpp
	$(COMP_CXX)

$(BIN_DIR)$(SL)testregionfeaturescpp$(HSUFFIX).exe: $(XPKG_SRC)$(SL)testregionfeaturescpp.cpp
	$(COMP_CXX)

$(BIN_DIR)$(SL)testfiltercpp$(HSUFFIX).exe: $(XPKG_SRC)$(SL)testfiltercpp.cpp
	$(COMP_CXX)

#-----------------------------------------------------------------------------
# Rules for generating directories:

$(XPKG_INC):
	-$(MKDIR) $(XPKG_INC)

$(XPKG_HELP):
	-$(MKDIR) $(XPKG_HELP)

$(XPKG_DOC_REF): $(XPKG_DOC_HTML)
	-$(MKDIR) $(XPKG_DOC_REF)

$(XPKG_DOC_HTML): $(XPKG_DOC)
	-$(MKDIR) $(XPKG_DOC_HTML)

$(XPKG_DOC):
	-$(MKDIR) $(XPKG_DOC)

$(OBJ_DIR): $(OBJ_BASE)
	-$(MKDIR) $(OBJ_DIR)


$(OBJ_BASE_ARCH): $(OBJ_BASE)
	-$(MKDIR) $(OBJ_BASE_ARCH)

$(OBJ_BASE):
	-$(MKDIR) $(OBJ_BASE)

$(LIB_DIR): $(LIB_BASE)
	-$(MKDIR) $(LIB_DIR)

$(LIB_DIR_DOTNET): $(BIN_BASE)
	-$(MKDIR) $(LIB_DIR_DOTNET)

$(LIB_BASE):
	-$(MKDIR) $(LIB_BASE)

$(BIN_BASE):
	-$(MKDIR) $(BIN_BASE)

$(BIN_DIR): $(BIN_BASE)
	-$(MKDIR) $(BIN_DIR)



#-----------------------------------------------------------------------------

clean:
	$(MAKE) -f$(MAKE_DIR)$(MAKE_FILE) clean_all
	$(MAKE) -f$(MAKE_DIR)$(MAKE_FILE) XL=1 clean_all

clean_all: clean_xpackage clean_app

clean_xpackage:
	-$(RM) $(XPKG_OBJS)
	-$(RM) $(XPKG_C_OBJS) $(XPKG_CPP_OBJS)
	-$(RM) $(XPKG_LIB_H) $(XPKG_LIB_C) $(XPKG_LIB_CPP)
	-$(RM) $(XPKG_LIB_DOTNET) $(LIB_DIR_DOTNET)$(SL)$(XPKG_LIB_DOTNET_NAME).xml
	-$(RM) $(XPKG_HELP)$(SL)$(HELP_NAME).*
	-$(RM) $(LIB_DIR)$(SL)$(PACKAGE_NAME)*
	-$(RM) $(XPKG_SRC)$(SL)H$(PACKAGE_NAME).c
	-$(RM) $(XPKG_SRC)$(SL)HC$(PACKAGE_NAME).c
	-$(RM) $(XPKG_SRC)$(SL)HCPP$(PACKAGE_NAME).cpp
	-$(RM) $(XPKG_SRC)$(SL)HCPP10$(PACKAGE_NAME).cpp
	-$(RM) $(XPKG_SRC)$(SL)HDOTNET$(PACKAGE_NAME).cs
	-$(RM) $(XPKG_INC)$(SL)HC$(PACKAGE_NAME).h
	-$(RM) $(XPKG_INC)$(SL)HCPP$(PACKAGE_NAME).h
	-$(RM) $(XPKG_INC)$(SL)HCPP10$(PACKAGE_NAME).h

clean_app:
	-$(RM) $(APPLICATION_DOTNET)
	-$(RM) $(APPLICATION_C) $(APPLICATION_CPP)
