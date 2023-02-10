#We need to check whether tool is multi config
macro(check_multi_config)

   #For now, we will require it

   get_cmake_property(isMultiConfig GENERATOR_IS_MULTI_CONFIG)
   if(NOT isMultiConfig)
      message(FATAL_ERROR "This generator doesn't support multi-config!")
   else()
      message("Multi-config: Success!")
   endif()

endmacro()

#Initializes Debug, Release and Dist configurations
macro(init_configurations)

   #Debug -> core engine debugging and development
   #Release -> for graphics engine with gui
   #Distribution -> for engine exported projects, without gui

   list(REMOVE_ITEM CMAKE_CONFIGURATION_TYPES MinSizeRel RelWithDebInfo PARENT_SCOPE)
   list(APPEND CMAKE_CONFIGURATION_TYPES Dist)
   list(REMOVE_DUPLICATES CMAKE_CONFIGURATION_TYPES)

   message("Configuration types: Success! (${CMAKE_CONFIGURATION_TYPES})")

endmacro()

#Sets/unsets building DLLs
macro(set_shared isShared)

   set(BUILD_SHARED_LIBS ${isShared})
   message("Shared set: Success! (${isShared})")

endmacro()

#Lists all targets recursively into a hierarchy tree
function(listTargets currentDir)

   get_property(currentTargets DIRECTORY "${currentDir}" PROPERTY BUILDSYSTEM_TARGETS)
   get_property(currentSubdirs DIRECTORY "${currentDir}" PROPERTY SUBDIRECTORIES)

   string(REPLACE "${Tigraf_SOURCE_DIR}" "Tigraf" currentTargetsPath "${currentDir}")

   foreach(target IN LISTS currentTargets)

      set_target_properties(
         "${target}"
            PROPERTIES
               FOLDER "${currentTargetsPath}" 
         )
      
   endforeach()


   foreach(subdir IN LISTS currentSubdirs)
      listTargets("${subdir}")
   endforeach()
   
endfunction()

#Lists all sources recursively into a hierarchy tree
macro(listSources sources root_path)

   foreach(source IN LISTS "${sources}")

      get_filename_component(source_path "${source}" PATH)
      string(REPLACE "${root_path}" "" source_path "${source_path}")

      if(MSVC)
         string(REPLACE "/" "\\" source_path "${source_path}")
      endif()

      source_group("${source_path}" FILES "${source}")

   endforeach()

endmacro()