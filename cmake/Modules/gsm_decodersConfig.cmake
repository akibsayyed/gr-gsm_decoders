INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_GSM_DECODERS gsm_decoders)

FIND_PATH(
    GSM_DECODERS_INCLUDE_DIRS
    NAMES gsm_decoders/api.h
    HINTS $ENV{GSM_DECODERS_DIR}/include
        ${PC_GSM_DECODERS_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GSM_DECODERS_LIBRARIES
    NAMES gnuradio-gsm_decoders
    HINTS $ENV{GSM_DECODERS_DIR}/lib
        ${PC_GSM_DECODERS_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GSM_DECODERS DEFAULT_MSG GSM_DECODERS_LIBRARIES GSM_DECODERS_INCLUDE_DIRS)
MARK_AS_ADVANCED(GSM_DECODERS_LIBRARIES GSM_DECODERS_INCLUDE_DIRS)

