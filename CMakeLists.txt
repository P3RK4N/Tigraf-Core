cmake_minimum_required(VERSION 3.25)

include("cmake/Utils.cmake")

#Debug
set(DEBUG ON)
set(CMAKE_MESSAGE_INDENT "Tigraf: ")

#Needs multi-config
check_multi_config()

#For project hierarchy
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Static libs
set(BUILD_SHARED_LIBS OFF)

#Language standards & extensions
if(NOT CMAKE_C_STANDARD VERSION_GREATER 17)

   if(DEBUG)
      message("Setting C standard to 17")
   endif()
   
   set(CMAKE_C_STANDARD 17)
   set(CMAKE_C_STANDARD_REQUIRED ON)

endif()

if(NOT CMAKE_CXX_STANDARD VERSION_GREATER 20)

   if(DEBUG)
      message("Setting C++ standard to 20")
   endif()

   set(CMAKE_CXX_STANDARD_REQUIRED ON)
   set(CMAKE_CXX_STANDARD 20)

endif()

if(DEBUG)
   message("Turning off C++ extensions")
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

#############################################################################
#PROJECT INIT ###############################################################
#############################################################################

project(Tigraf VERSION 0.1.0 LANGUAGES C CXX)

if(DEBUG)
   message("SOURCE DIRECTORY: ${Tigraf_SOURCE_DIR}")
   message("BINARY DIRECTORY: ${Tigraf_BINARY_DIR}")
endif()

#Tigraf core
add_library(Tigraf-Core)

#############################################################################
#Setup configurations #######################################################
#############################################################################

init_configurations()

#Debug
add_compile_definitions($<$<CONFIG:Debug>:TIGRAF_DEBUG>)

#Release
add_compile_definitions($<$<CONFIG:Release>:TIGRAF_RELEASE>)

#Dist
add_compile_definitions($<$<CONFIG:Dist>:TIGRAF_DIST>)
set(CMAKE_EXE_LINKER_FLAGS_DIST "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")


if(MSVC)

   if(DEBUG)
      message("MSVC set")
   endif()
   
   set(CMAKE_CXX_FLAGS_DEBUG "/RTC1 /Zi /Od /Ob0")
   set(CMAKE_CXX_FLAGS_RELEASE "/O3 /Ob2 /Oi /Ot /DNDEBUG")
   set(CMAKE_CXX_FLAGS_DIST "/O3 /Ob2 /Oi /Ot /DNDEBUG")
   
else()
   
   if(DEBUG)
      message("MSVC not set")
   endif()
   
   set(CMAKE_CXX_FLAGS_RELEASE "-O3 -finline-functions")
   set(CMAKE_CXX_FLAGS_DEBUG "-fno-inline -O0 -g")
   set(CMAKE_CXX_FLAGS_DIST "-O3 -finline-functions")      

endif()
      
if(DEBUG)
   message("CXX COMPILE FLAGS RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
   message("CXX COMPILE FLAGS DIST: ${CMAKE_CXX_FLAGS_DIST}")
   message("CXX COMPILE FLAGS DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
endif()
   
#############################################################################   
#Setup Tigraf-Core ##########################################################
#############################################################################

#Searching for files
file(GLOB_RECURSE sources src/*.cpp src/*.c src/*.h src/*.hpp)
file(GLOB_RECURSE headers include/*.h include/*.hpp)

target_sources(Tigraf-Core PRIVATE "${sources};${headers}")

#Building a hierarchy tree
#Tigraf Source
foreach(source IN LISTS sources)
   get_filename_component(source_path "${source}" PATH)
   string(REPLACE "${Tigraf_SOURCE_DIR}/src" "" source_path "${source_path}")

   if(MSVC)
      string(REPLACE "/" "\\" source_path_msvc "${source_path}")
   endif()

   source_group("${source_path_msvc}" FILES "${source}")
endforeach()

#Tigraf include
source_group("Include" FILES "${headers}")

#Precompiles
source_group("\\Precompiles\\" FILES "${Tigraf_SOURCE_DIR}/src/PCH.h")
source_group("\\Precompiles\\" FILES "${Tigraf_SOURCE_DIR}/src/PCH.cpp")

if(NOT MSVC)

   target_precompile_headers(
      Tigraf-Core
         PRIVATE "${Tigraf_SOURCE_DIR}/src/Tigraf/Core/Log.h"
         PRIVATE "${Tigraf_SOURCE_DIR}/src/Tigraf/Core/Core.h"
         PRIVATE "${Tigraf_SOURCE_DIR}/src/Tigraf/Core/Assert.h"
         PRIVATE "${Tigraf_SOURCE_DIR}/src/Tigraf/Core/Timer.h"
         PRIVATE <string>
         PRIVATE <iostream>
         PRIVATE <fstream>
         PRIVATE <memory>
         PRIVATE <vector>
         PRIVATE <unordered_map>
         PRIVATE <unordered_set>
         PRIVATE <filesystem>
      )
   
else()
   
   foreach(source IN LISTS sources)
      set_source_files_properties(
         "${source}"
            PROPERTIES
               COMPILE_OPTIONS "/YuPCH.h;/FIPCH.h"
      )
   endforeach()

   set_source_files_properties(
      "${Tigraf_SOURCE_DIR}/src/PCH.cpp"
         PROPERTIES
            COMPILE_OPTIONS "/YcPCH.h;/FIPCH.h"
      )
   
endif()

#Add includes
target_include_directories(
   Tigraf-Core
      PUBLIC "${Tigraf_SOURCE_DIR}/src"         #TODO: Set PRIVATE
      PUBLIC "${Tigraf_SOURCE_DIR}/include"     #TODO: Set INTERFACE
   )

#############################################################################
#Add dependencies ###########################################################
#############################################################################

unset(CMAKE_MESSAGE_INDENT)

#OpenGL Loader
add_subdirectory(vendor/glad)

#Logger
add_subdirectory(vendor/spdlog)

#OpenGL FrameWork
add_subdirectory(vendor/glfw)
   target_include_directories(Tigraf-Core PRIVATE vendor/glfw/include)

#OpenGL Maths
set(BUILD_STATIC_LIBS NOT "${BUILD_DYNAMIC_LIBS}")    #TODO: Remove
add_subdirectory(vendor/glm)

#Image loader
target_include_directories(Tigraf-Core PRIVATE vendor/stb)

#Linking
target_link_libraries(
   Tigraf-Core 
      PUBLIC glad                         #TODO: Set to PRIVATE
      PUBLIC spdlog::spdlog               #TODO: Set to PRIVATE
      PUBLIC glfw                         #TODO: Set to PRIVATE
      PUBLIC glm
      # PRIVATE -LGL
   )

#############################################################################
#Temporary ##################################################################
#############################################################################

add_executable(Tigraf-Console)

file(GLOB_RECURSE console_sources debug_console/*.cpp debug_console/*.h)

target_sources(
   Tigraf-Console
      PRIVATE "${console_sources}"
   )

target_include_directories(
   Tigraf-Console
      PRIVATE "${Tigraf_SOURCE_DIR}/debug_console/src/"
   )

target_link_libraries(
   Tigraf-Console
      PRIVATE Tigraf-Core
)

set(VS_STARTUP_PROJECT Tigraf-Console)

set_target_properties(
   Tigraf-Console
      PROPERTIES
         VS_DEBUGGER_WORKING_DIRECTORY "${Tigraf_SOURCE_DIR}/debug_console"
   )

#############################################################################
#Targets Hierarchy ##########################################################
#############################################################################

listTargets("${CMAKE_CURRENT_LIST_DIR}")