##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CodeOSoccer
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jai/robocup/CodeOSoccer"
ProjectPath            := "/home/jai/robocup/CodeOSoccer/CodeOSoccer"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=jai
Date                   :=Monday 15 October 2012
CodeLitePath           :="/home/jai/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)_DEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/jai/robocup/CodeOSoccer/CodeOSoccer/CodeOSoccer.txt"
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -Wall -O0 -UWIN32 -DGR_SIM_COMM -DPS_CLASS=NaivePS -URUN_REFBOX -DSHOW_REFBOX_LOG -DSHOW_SSLVISION_LOG -UMIN -UMAX $(Preprocessors)
C_CmpOptions           := -g -Wall -O0 -UWIN32 -DGR_SIM_COMM -DPS_CLASS=NaivePS -URUN_REFBOX -DSHOW_REFBOX_LOG -DSHOW_SSLVISION_LOG -UMIN -UMAX $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)include $(IncludeSwitch)../common/include $(IncludeSwitch)../common/gpb/proto/cpp 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)codeosoccer $(LibrarySwitch)protobuf $(LibrarySwitch)protobuf-lite $(LibrarySwitch)protoc 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../libs 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/bot$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jai/robocup/CodeOSoccer/CodeOSoccer/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/jai/robocup/CodeOSoccer/CodeOSoccer/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/jai/robocup/CodeOSoccer/CodeOSoccer/main.cpp"

$(IntermediateDirectory)/bot$(ObjectSuffix): bot.cpp $(IntermediateDirectory)/bot$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jai/robocup/CodeOSoccer/CodeOSoccer/bot.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/bot$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bot$(DependSuffix): bot.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/bot$(ObjectSuffix) -MF$(IntermediateDirectory)/bot$(DependSuffix) -MM "/home/jai/robocup/CodeOSoccer/CodeOSoccer/bot.cpp"

$(IntermediateDirectory)/bot$(PreprocessSuffix): bot.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/bot$(PreprocessSuffix) "/home/jai/robocup/CodeOSoccer/CodeOSoccer/bot.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/bot$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/bot$(DependSuffix)
	$(RM) $(IntermediateDirectory)/bot$(PreprocessSuffix)
	$(RM) $(OutputFile)


