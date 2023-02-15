#Lists all targets recursively into a hierarchy tree
function(groupTargets currentDir)

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
      groupTargets("${subdir}")
   endforeach()
   
endfunction()

#Lists all sources recursively into a hierarchy tree
macro(groupSources sources root_path root_replacer)

   foreach(source IN LISTS "${sources}")

      get_filename_component(source_path "${source}" PATH)
      string(REPLACE "${root_path}" "${root_replacer}" source_path "${source_path}")

      if(MSVC)
         string(REPLACE "/" "\\" source_path "${source_path}")
      endif()

      source_group("${source_path}" FILES "${source}")

   endforeach()

endmacro()

macro(debug_log)
   if(DEBUG)
      foreach(log IN LISTS ARGN)
         debug_log("Tigraf: ${log}")
      endforeach()
   endif()
endmacro()