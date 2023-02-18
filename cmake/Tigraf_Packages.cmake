macro(tigraf_findOpenGL)

   #OpenGL_FOUND
   #OPENGL_LIBRARIES

   find_package(OpenGL)

   if(OpenGL_FOUND)

      set(TIGRAF_OPENGL "TIGRAF_OPENGL")
      set(TIGRAF_OPENGL_LIBRARY_PATH "${OPENGL_LIBRARIES}")

      message(
         STATUS 
            "Tigraf: OpenGL found!\n\tIncludes: ${TIGRAF_OPENGL_INCLUDE_PATH}\n\tLibraries: ${TIGRAF_OPENGL_LIBRARY_PATH}\n"
      )

   else()

      set(TIGRAF_OPENGL "")

      message(STATUS "Tigraf: OpenGL not found!\n")

   endif()

endmacro()

macro(tigraf_findVulkan) #TODO: Add other libraries

   #Vulkan_FOUND
   #Vulkan_LIBRARY
   #Vulkan_INCLUDE_DIR

   find_package(Vulkan)

   if(Vulkan_FOUND)

      set(TIGRAF_VULKAN "TIGRAF_VULKAN")
      set(TIGRAF_VULKAN_LIBRARY_PATH "${Vulkan_LIBRARY}")
      set(TIGRAF_VULKAN_INCLUDE_PATH "${Vulkan_INCLUDE_DIR}")

      message(
         STATUS 
            "Tigraf: Vulkan found!\n\tIncludes: ${TIGRAF_VULKAN_INCLUDE_PATH}\n\tLibraries: ${TIGRAF_VULKAN_LIBRARY_PATH}\n"
      )

   else()

      set(TIGRAF_VULKAN "")

      message(STATUS "Tigraf: Vulkan not found!\n")

   endif()

endmacro()

macro(tigraf_findD3D11)

   # DirectX11_FOUND
   # DirectX11_INCLUDE_DIRS
   # DirectX11_LIBRARIES

   find_package(D3D11)

   if(DirectX11_FOUND)

      set(TIGRAF_D3D11 "TIGRAF_D3D11")
      set(TIGRAF_D3D11_LIBRARY_PATH "${DirectX11_LIBRARIES}")
      set(TIGRAF_D3D11_INCLUDE_PATH "${DirectX11_INCLUDE_DIRS}")

      message(
         STATUS 
            "Tigraf: D3D11 found!\n\tIncludes: ${TIGRAF_D3D11_INCLUDE_PATH}\n\tLibraries: ${TIGRAF_D3D11_LIBRARY_PATH}\n"
      )

   else()

      set(TIGRAF_D3D11 "")

      message(STATUS "Tigraf: D3D11 not found!\n")

   endif()

endmacro()

macro(tigraf_findD3D12)

   # D3D12_FOUND
   # D3D12_INCLUDE_DIRS
   # D3D12_LIBRARIES

   set(CMAKE_MESSAGE_LOG_LEVEL "SEND ERROR")
   find_package(D3D12)
   set(CMAKE_MESSAGE_LOG_LEVEL "STATUS")


   if(D3D12_FOUND)

      set(TIGRAF_D3D12 "TIGRAF_D3D12")
      set(TIGRAF_D3D12_LIBRARY_PATH "${D3D12_LIBRARIES}")
      set(TIGRAF_D3D12_INCLUDE_PATH "${D3D12_INCLUDE_DIRS}")

      message(
         STATUS 
            "Tigraf: D3D12 found!\n\tIncludes: ${TIGRAF_D3D12_INCLUDE_PATH}\n\tLibraries: ${TIGRAF_D3D12_LIBRARY_PATH}\n"
      )

   else()

      set(TIGRAF_D3D12 "")

      message(STATUS "Tigraf: D3D12 not found!\n")

   endif()

endmacro()

macro(tigraf_findMetal)

   # METAL_FOUND
   # METAL_INCLUDE_DIR
   # METAL_LIBRARIES

   find_package(Metal)

   if(METAL_FOUND)

      set(TIGRAF_METAL "TIGRAF_METAL")
      set(TIGRAF_METAL_LIBRARY_PATH "${METAL_LIBRARIES}")
      set(TIGRAF_METAL_INCLUDE_PATH "${METAL_INCLUDE_DIR}")

      message(
         STATUS 
            "Tigraf: Metal found!\n\tIncludes: ${TIGRAF_METAL_INCLUDE_PATH}\n\tLibraries: ${TIGRAF_METAL_LIBRARY_PATH}\n"
      )

   else()

      set(TIGRAF_METAL "")

      message(STATUS "Tigraf: Metal not found!\n")

   endif()

endmacro()

