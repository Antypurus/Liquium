if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(warnings "/W4 /WX /EHsc")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd26812")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /nologo")
        
        # Debug only compiler options
        #add_compile_options("$<$<CONFIG:DEBUG>:/MDd>")
        
        # Release only compiler options
        add_compile_options("$<$<CONFIG:RELEASE>:/Oi>")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        #clang frontend
endif()

file(GLOB_RECURSE ENGINE_SOURCES
        **.cpp
        **.hpp
        )

set(ENGINE_DYNAMIC_COMPILE OFF CACHE STRING "Sets weather the engine should be comipled into a dinamic library (DLL) or a static library (LIB)" FORCE)

if(${ENGINE_DYNAMIC_COMPILE})
        add_library(Liquium SHARED ${ENGINE_SOURCES})
        
        set_target_properties(Liquium PROPERTIES PREFIX "")
        set_target_properties(Liquium PROPERTIES SUFFIX ".dll")
        
        target_compile_definitions(Liquium PUBLIC __INTERNAL_LIQUIUM_ENGINE__)
        add_compile_definitions(DYNAMIC_ENGINE_BUILD)

        set_target_properties(Liquium PROPERTIES LINK_FLAGS "${LINK_FLAGS} /INCREMENTAL:NO")
else()
        add_library(Liquium STATIC ${ENGINE_SOURCES})
        set_target_properties(Liquium PROPERTIES PREFIX "")
        set_target_properties(Liquium PROPERTIES SUFFIX ".lib")
endif()

set_target_properties(Liquium PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Liquium PROPERTIES CXX_STANDARD 20)

# warning blob of gabage incoming
set_target_properties(Liquium PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)# required by clang
set_target_properties(Liquium PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(Liquium PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(Liquium PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(Liquium PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)# required by clang
set_target_properties(Liquium PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)# required by clang
set_target_properties(Liquium PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(Liquium PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(Liquium PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(Liquium PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(Liquium PROPERTIES LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)# required by msvc
set_target_properties(Liquium PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)# required by msvc