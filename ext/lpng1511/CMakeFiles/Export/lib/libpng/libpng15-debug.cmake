#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Compute the installation prefix relative to this file.
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

# Import target "png15" for configuration "Debug"
SET_PROPERTY(TARGET png15 APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(png15 PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/libpng15d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "D:/Voltrox/ext/lib/zlib.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/libpng15d.dll"
  )

# Import target "png15_static" for configuration "Debug"
SET_PROPERTY(TARGET png15_static APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(png15_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "D:/Voltrox/ext/lib/zlib.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libpng15_staticd.lib"
  )

# Cleanup temporary variables.
SET(_IMPORT_PREFIX)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
