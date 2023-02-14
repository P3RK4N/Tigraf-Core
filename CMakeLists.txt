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

#############################################################################   
#Language Standard ##########################################################
#############################################################################   

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
target_compile_definitions(
   Tigraf-Core
      PUBLIC $<$<CONFIG:Debug>:TIGRAF_DEBUG>
)

#Release
target_compile_definitions(
   Tigraf-Core
      PUBLIC $<$<CONFIG:Release>:TIGRAF_RELEASE>
)

#Dist
target_compile_definitions(
   Tigraf-Core
      PUBLIC $<$<CONFIG:Dist>:TIGRAF_DIST>
)

set(CMAKE_EXE_LINKER_FLAGS_DIST "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")


if(MSVC)

   if(DEBUG)
      message("MSVC set")
   endif()
   
   set(CMAKE_CXX_FLAGS_DEBUG "/RTC1 /Zi /Od /Ob0")
   set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob2 /Oi /Ot /DNDEBUG")
   set(CMAKE_CXX_FLAGS_DIST "/O2 /Ob2 /Oi /Ot /DNDEBUG")
   
else()
   
   if(DEBUG)
      message("MSVC not set")
   endif()
   
   set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-functions")
   set(CMAKE_CXX_FLAGS_DEBUG "-fno-inline -O0 -g")
   set(CMAKE_CXX_FLAGS_DIST "-O2 -finline-functions")      

endif()
      
if(DEBUG)

   message("CXX COMPILE FLAGS RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
   message("CXX COMPILE FLAGS DIST: ${CMAKE_CXX_FLAGS_DIST}")
   message("CXX COMPILE FLAGS DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")

endif()
   
#############################################################################   
#Refreshing Precompiles #####################################################
#############################################################################   

#Standard precompiled headers
set(
   std_headers 
      <iostream>
      <string>
      <fstream>
      <memory>
      <vector>
      <unordered_map>
      <unordered_set>
      <filesystem>
      <functional>
)

#Custom dependency precompiled headers
set(
   dependency_headers
      <glm/glm.hpp>
)

#Tigraf precompiled headers
set(
   tigraf_headers
      [["Tigraf/Core/Core.h"]]
      [["Tigraf/Core/Log.h"]] 
      [["Tigraf/Core/Assert.h"]] 
      [["Tigraf/Core/Timer.h"]] 
)

#Creating PCH.h
set(precompiled_headers "#pragma once\n")

foreach(precompiled_header IN LISTS std_headers dependency_headers tigraf_headers)
   string(APPEND precompiled_headers "#include ${precompiled_header}\n")
endforeach()

if(DEBUG)
   message("Refreshing PCH:\n${precompiled_headers}")
endif()

file(GENERATE
      OUTPUT "${Tigraf_SOURCE_DIR}/src/PCH.h"
      CONTENT "${precompiled_headers}"
   )

#############################################################################   
#Refreshing includes ########################################################
#############################################################################   

#Create Tigraf.h file string which will include all of them, initialising with PCH.h
set(tigraf_includes "${precompiled_headers}")

#Collect all interface header files into Tigraf.h
file(REMOVE "${Tigraf_SOURCE_DIR}/include/Tigraf/Tigraf.h")
file(GLOB_RECURSE interface_headers "${Tigraf_SOURCE_DIR}/include/Tigraf/*.h")

foreach(interface_filepath IN LISTS interface_headers)

   string(REPLACE "${Tigraf_SOURCE_DIR}/include/" "" rel_interface_filepath "${interface_filepath}")

   if(DEBUG)
      message("Refreshing Includes: ${rel_interface_filepath}")
   endif()
   
   string(APPEND tigraf_includes "\n#include \"${rel_interface_filepath}\"")
   
endforeach()

file(
   GENERATE 
      OUTPUT "${Tigraf_SOURCE_DIR}/include/Tigraf/Tigraf.h"
      CONTENT "${tigraf_includes}"
   )


#############################################################################   
#Setup Tigraf-Core ##########################################################
#############################################################################

#Searching for files
file(GLOB_RECURSE sources src/*.cpp src/*.c src/*.h src/*.hpp)
file(GLOB_RECURSE headers include/*.h include/*.hpp)

#Add generated header since it is not yet created during GLOB
list(APPEND headers "${Tigraf_SOURCE_DIR}/include/Tigraf/Tigraf.h")

target_sources(Tigraf-Core PRIVATE "${sources};${headers}")

#Building a hierarchy tree
#Tigraf Source
groupSources(sources "${Tigraf_SOURCE_DIR}/src" "Source")

#Tigraf include
groupSources(headers "${Tigraf_SOURCE_DIR}/include" "Include")

#Precompiles
source_group("\\Precompile\\" FILES "${Tigraf_SOURCE_DIR}/src/PCH.h")
source_group("\\Precompile\\" FILES "${Tigraf_SOURCE_DIR}/src/PCH.cpp")

if(NOT MSVC)

   # target_precompile_headers(
   #    Tigraf-Core
   #       PRIVATE <string>
   #       PRIVATE <iostream>
   #       PRIVATE <fstream>
   #       PRIVATE <memory>
   #       PRIVATE <vector>
   #       PRIVATE <unordered_map>
   #       PRIVATE <unordered_set>
   #       PRIVATE <filesystem>
   #       PRIVATE <functional>
   #       PRIVATE "${Tigraf_SOURCE_DIR}/src/Tigraf/Core/Core.h"
   #       PRIVATE "${Tigraf_SOURCE_DIR}/src/Tigraf/Core/Log.h"
   #       PRIVATE "${Tigraf_SOURCE_DIR}/src/Tigraf/Core/Assert.h"
   #       PRIVATE "${Tigraf_SOURCE_DIR}/src/Tigraf/Core/Timer.h"
   #    )
   
   target_precompile_headers(
      Tigraf-Core
         PRIVATE std_headers dependency_headers tigraf_headers
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

#Macros
target_compile_definitions(
   Tigraf-Core
      PRIVATE TIGRAF_CORE  
)

#Add includes
target_include_directories(
   Tigraf-Core
      PRIVATE        "${Tigraf_SOURCE_DIR}/src"         #For use inside a Tigraf-Core
      PUBLIC         "${Tigraf_SOURCE_DIR}/include"     #Includes
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
      PRIVATE  glad
      PRIVATE  glfw
      PUBLIC   spdlog::spdlog
      PUBLIC   glm
   )

#############################################################################
#Temporary ##################################################################
#############################################################################

add_executable(Tigraf-Console)

file(GLOB_RECURSE console_sources debug_console/*.cpp debug_console/*.h debug_console/*.glsl debug_console/*.jpg debug_console/*.png)

file(GLOB_RECURSE console_resources debug_console/*.glsl debug_console/*.jpg debug_console/*.png)

groupSources(console_resources "${Tigraf_SOURCE_DIR}/debug_console/resources" "Resources")

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

groupTargets("${CMAKE_CURRENT_LIST_DIR}")