cmake_minimum_required(VERSION 3.25)
include("cmake/Tigraf_Utils.cmake")

#Debug
set(DEBUG ON)

#############################################################################
#PROJECT INIT ###############################################################
#############################################################################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(BUILD_SHARED_LIBS OFF)

project(Tigraf VERSION 0.1.0 LANGUAGES C CXX)

debug_log("SOURCE DIRECTORY: ${Tigraf_SOURCE_DIR}") 
debug_log("BINARY DIRECTORY: ${Tigraf_BINARY_DIR}")
debug_log("Using MSVC: ${MSVC}")

#Tigraf core
add_library(Tigraf-Core)

#############################################################################   
#Language Standard ##########################################################
#############################################################################   

set(cxx_version 20)

if(CMAKE_CXX_STANDARD VERSION_GREATER 20)
   set(cxx_version "${CMAKE_CXX_STANDARD}")
endif()

set_target_properties(
   Tigraf-Core
      PROPERTIES
         CXX_STANDARD "${cxx_version}"
         CXX_STANDARD_REQUIRED ON
         CXX_EXTENSIONS OFF
         VS_DEBUGGER_WORKING_DIRECTORY "${Tigraf_SOURCE_DIR}/resources"
)

#############################################################################
#Setup configurations #######################################################
#############################################################################

get_cmake_property(is_multi_config GENERATOR_IS_MULTI_CONFIG)

if(is_multi_config) #Using multi config tools

   #Debug,Release,Custom
   target_compile_definitions(
      Tigraf-Core
         PUBLIC $<$<CONFIG:Debug>:TIGRAF_DEBUG>
         PUBLIC $<$<CONFIG:Release>:TIGRAF_RELEASE>
         PUBLIC $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:TIGRAF_RELEASE>
   )

   #Multi config Compiler flags
   if(MSVC)

      target_compile_options(
         Tigraf-Core
         PRIVATE $<$<CONFIG:Debug>:/Zi /Od /Ob0>
         PRIVATE $<$<CONFIG:Release>:/O2 /Ob2 /Oi /Ot /DNDEBUG>
         PRIVATE $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:/O2 /Ob2 /Oi /Ot /DNDEBUG>
      )

   elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

      target_compile_options(
         Tigraf-Core
         PRIVATE $<$<CONFIG:Debug>:-fno-inline -O0 -g>
         PRIVATE $<$<CONFIG:Release>:-O2 -finline-functions>
         PRIVATE $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:-O2 -finline-functions>
      )

   else()
   
      message(FATAL_ERROR "Unsupported platform or compiler!")

   endif()

else() #Not using multi config tools

   if(CMAKE_BUILD_TYPE STREQUAL "Debug")

      target_compile_definitions(Tigraf-Core PUBLIC TIGRAF_DEBUG)

      if(MSVC)
         target_compile_options(Tigraf-Core PRIVATE /Zi /Od /Ob0)
      elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
         target_compile_options(Tigraf-Core PRIVATE -fno-inline -O0 -g)
      else()
         message(FATAL_ERROR "Unsupported platform or compiler!")
      endif()

   else()

      set(CMAKE_BUILD_TYPE "Release")

      target_compile_definitions(Tigraf-Core PUBLIC TIGRAF_RELEASE)

      if(MSVC)
         target_compile_options(Tigraf-Core PRIVATE /O2 /Ob2 /Oi /Ot /DNDEBUG)
      elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
         target_compile_options(Tigraf-Core PRIVATE -O2 -finline-functions)
      else()
         message(FATAL_ERROR "Unsupported platform or compiler!")
      endif()

   endif()

   debug_log("NOT USING MULTI CONFIG, DEFAULT CONFIG: ${CMAKE_BUILD_TYPE}")

endif()
   
get_target_property(compiler_options_debug Tigraf-Core COMPILE_OPTIONS)
get_target_property(compiler_definitions_debug Tigraf-Core COMPILE_DEFINITIONS)

debug_log("COMPILER OPTIONS: ${compiler_options_debug}")
debug_log("COMPILER DEFINITIONS: ${compiler_definitions_debug}")

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
debug_log("Refreshing PCH:")
set(precompiled_headers "#pragma once\n")

foreach(precompiled_header IN LISTS std_headers dependency_headers tigraf_headers)
   string(APPEND precompiled_headers "#include ${precompiled_header}\n")
   debug_log("    #include ${precompiled_header}")
endforeach()


file(GENERATE
      OUTPUT "${Tigraf_SOURCE_DIR}/src/PCH.h"
      CONTENT "${precompiled_headers}"
)

#############################################################################   
#Refreshing includes ########################################################
#############################################################################   

#Create Tigraf.h file string which will include all of them, initialising with PCH.h
debug_log("Refreshing Includes:")
set(tigraf_includes "${precompiled_headers}")

#Collect all interface header files into Tigraf.h
file(REMOVE "${Tigraf_SOURCE_DIR}/include/Tigraf/Tigraf.h")
file(GLOB_RECURSE interface_headers "${Tigraf_SOURCE_DIR}/include/Tigraf/*.h")

foreach(interface_filepath IN LISTS interface_headers)

   string(REPLACE "${Tigraf_SOURCE_DIR}/include/" "" rel_interface_filepath "${interface_filepath}")

   debug_log("    ${rel_interface_filepath}")
   
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
tigraf_group_sources(sources "${Tigraf_SOURCE_DIR}/src" "Source")

#Tigraf include
tigraf_group_sources(headers "${Tigraf_SOURCE_DIR}/include" "Include")

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
#Example App ################################################################
#############################################################################

if(PROJECT_IS_TOP_LEVEL)

   debug_log("Adding example app")

   add_executable(Tigraf-ExampleApp)
   set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tigraf-ExampleApp)

   set_target_properties(
      Tigraf-ExampleApp
         PROPERTIES
            CXX_STANDARD "${cxx_version}"
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
   )
   
   file(
      GLOB_RECURSE 
         console_sources example_app/*.cpp example_app/*.h example_app/*.glsl example_app/*.jpg example_app/*.png
   )
   
   file(
      GLOB_RECURSE 
         console_resources example_app/*.glsl example_app/*.jpg example_app/*.png
   )
   
   tigraf_group_sources(console_resources "${Tigraf_SOURCE_DIR}/example_app/resources" "Resources")
   
   target_sources(
      Tigraf-ExampleApp
      PRIVATE "${console_sources}"
   )
      
   target_include_directories(
      Tigraf-ExampleApp
      PRIVATE "${Tigraf_SOURCE_DIR}/example_app/src/"
   )
   
   target_link_libraries(
      Tigraf-ExampleApp
      PRIVATE Tigraf-Core
   )
      
   set_target_properties(
      Tigraf-ExampleApp
      PROPERTIES
      VS_DEBUGGER_WORKING_DIRECTORY "${Tigraf_SOURCE_DIR}/example_app"
   )

endif()
         
#############################################################################
#Targets Hierarchy ##########################################################
#############################################################################

tigraf_group_targets("${CMAKE_CURRENT_LIST_DIR}")