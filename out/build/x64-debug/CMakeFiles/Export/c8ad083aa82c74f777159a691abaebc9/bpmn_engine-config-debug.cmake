#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "bpmn::bpmn_engine" for configuration "Debug"
set_property(TARGET bpmn::bpmn_engine APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(bpmn::bpmn_engine PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/bpmn_engine.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/bpmn_engine.dll"
  )

list(APPEND _cmake_import_check_targets bpmn::bpmn_engine )
list(APPEND _cmake_import_check_files_for_bpmn::bpmn_engine "${_IMPORT_PREFIX}/lib/bpmn_engine.lib" "${_IMPORT_PREFIX}/bin/bpmn_engine.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
