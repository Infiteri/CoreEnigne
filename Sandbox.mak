DIR := $(subst /,\,${CURDIR})
BUILD_DIR := Bin
OBJ_DIR := Bin-Obj

ASSEMBLY := Sandbox
EXTENSION := .exe
COMPILER_FLAGS := -g #-fPIC
INCLUDE_FLAGS := -ISandbox\Source -IEngine/Source -IEngine/Vendor/ImGui -IEngine/Vendor/GLFW/include -IEngine/Vendor/GLAD/include -IEngine/Vendor/stb
LINKER_FLAGS := -g -lEngine -L$(BUILD_DIR) -lImGui -lGlad
DEFINES := -D_DEBUG -D_CRT_SECURE_NO_WARNINGS -DCORE_WINDOWS_PLATFORM

# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRC_FILES := $(call rwildcard,$(ASSEMBLY)/,*.cpp) # Get all .cpp files
DIRECTORIES := \$(ASSEMBLY)\Source $(subst $(DIR),,$(shell dir $(ASSEMBLY)\Source /S /AD /B | findstr /i Source)) # Get all directories under src.
OBJ_FILES := $(SRC_FILES:%=$(OBJ_DIR)/%.o) # Get all compiled .cpp.o objects for sandbox

all: scaffold compile link

.PHONY: scaffold
scaffold: # create build directory
	-@setlocal enableextensions enabledelayedexpansion && mkdir $(addprefix $(OBJ_DIR), $(DIRECTORIES)) 2>NUL || cd .
	-@setlocal enableextensions enabledelayedexpansion && mkdir $(BUILD_DIR) 2>NUL || cd .

.PHONY: link
link: scaffold $(OBJ_FILES) # link
	@echo Linking $(ASSEMBLY)...
	@g++ $(OBJ_FILES) -o $(BUILD_DIR)\$(ASSEMBLY)$(EXTENSION) $(LINKER_FLAGS)

.PHONY: compile
compile: #compile .cpp files
	@echo Building $(ASSEMBLY)

.PHONY: clean
clean: # clean build directory
	if exist $(BUILD_DIR)\$(ASSEMBLY)$(EXTENSION) del $(BUILD_DIR)\$(ASSEMBLY)$(EXTENSION)
	rmdir /s /q $(OBJ_DIR)\$(ASSEMBLY)

$(OBJ_DIR)/%.cpp.o: %.cpp # compile .cpp to .cpp.o object
	@echo   $<...
	@g++ $< $(COMPILER_FLAGS) -c -o $@ $(DEFINES) $(INCLUDE_FLAGS)