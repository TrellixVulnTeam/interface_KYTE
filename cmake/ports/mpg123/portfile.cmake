set(MPG123_VERSION 1.26.3)
set(MPG123_HASH 7574331afaecf3f867455df4b7012e90686ad6ac8c5b5e820244204ea7088bf2b02c3e75f53fe71c205f9eca81fef93f1d969c8d0d1ee9775dc05482290f7b2d)

#architecture detection
if(VCPKG_TARGET_ARCHITECTURE STREQUAL "x86")
   set(MPG123_ARCH Win32)
   set(MPG123_CONFIGURATION _x86)
elseif(VCPKG_TARGET_ARCHITECTURE STREQUAL "x64")
   set(MPG123_ARCH x64)
   set(MPG123_CONFIGURATION _x86)
elseif(VCPKG_TARGET_ARCHITECTURE STREQUAL "arm")
   set(MPG123_ARCH ARM)
   set(MPG123_CONFIGURATION _Generic)
elseif(VCPKG_TARGET_ARCHITECTURE STREQUAL "arm64")
   set(MPG123_ARCH ARM64)
   set(MPG123_CONFIGURATION _Generic)
else()
   message(FATAL_ERROR "unsupported architecture")
endif()

#linking
if (VCPKG_LIBRARY_LINKAGE STREQUAL dynamic)
    set(MPG123_CONFIGURATION_SUFFIX _Dll)
endif()

if (NOT VCPKG_TARGET_IS_WINDOWS)
    vcpkg_from_sourceforge(
        OUT_SOURCE_PATH SOURCE_PATH
        REPO mpg123/mpg123
        REF ${MPG123_VERSION}
        FILENAME "mpg123-${MPG123_VERSION}.tar.bz2"
        SHA512 ${MPG123_HASH}
        PATCHES
            0001-fix-x86-build.patch
    )
endif()

# include(${CURRENT_INSTALLED_DIR}/share/yasm-tool-helper/yasm-tool-helper.cmake)
# yasm_tool_helper(APPEND_TO_PATH)

if(VCPKG_TARGET_IS_UWP)
    vcpkg_install_msbuild(
        SOURCE_PATH ${SOURCE_PATH}
        PROJECT_SUBPATH ports/MSVC++/2015/uwp/libmpg123/libmpg123.vcxproj
        OPTIONS /p:UseEnv=True
        PLATFORM ${MPG123_ARCH}
        RELEASE_CONFIGURATION Release_uwp
        DEBUG_CONFIGURATION Debug_uwp
    )
    file(INSTALL
        ${SOURCE_PATH}/ports/MSVC++/mpg123.h
        ${SOURCE_PATH}/src/libmpg123/fmt123.h
        ${SOURCE_PATH}/src/libmpg123/mpg123.h.in
        DESTINATION ${CURRENT_PACKAGES_DIR}/include
    )
elseif(VCPKG_TARGET_IS_WINDOWS)
    # vcpkg_install_msbuild(
    #     SOURCE_PATH ${SOURCE_PATH}
    #     PROJECT_SUBPATH ports/MSVC++/2015/win32/libmpg123/libmpg123.vcxproj
    #     OPTIONS /p:UseEnv=True
    #     RELEASE_CONFIGURATION Release${MPG123_CONFIGURATION}${MPG123_CONFIGURATION_SUFFIX}
    #     DEBUG_CONFIGURATION Debug${MPG123_CONFIGURATION}${MPG123_CONFIGURATION_SUFFIX}
    # )
    # file(INSTALL
    #     ${SOURCE_PATH}/ports/MSVC++/mpg123.h
    #     ${SOURCE_PATH}/src/libmpg123/fmt123.h
    #     ${SOURCE_PATH}/src/libmpg123/mpg123.h.in
    #     DESTINATION ${CURRENT_PACKAGES_DIR}/include
    # )

    vcpkg_download_distfile(
		MPG123_ARCHIVE
		URLS https://cdn.tivolicloud.com/dependencies/mpg123-${MPG123_VERSION}-windows.zip
		SHA512 ef946260f4444713e8967635e76fcca7cb53c1ab645b38a0455e5cda6658a3a304622a037db2fe0d46d4e2c54d5dede28eaaec3441099078d0da80819535fec1
		FILENAME mpg123-${MPG123_VERSION}-windows.zip
    )
    
    vcpkg_extract_source_archive_ex(
        OUT_SOURCE_PATH MPG123_EXTRACTED
        ARCHIVE ${MPG123_ARCHIVE}
    )

    file(INSTALL ${MPG123_EXTRACTED}/bin/ DESTINATION ${CURRENT_PACKAGES_DIR}/bin)
    file(INSTALL ${MPG123_EXTRACTED}/debug/ DESTINATION ${CURRENT_PACKAGES_DIR}/debug)
    file(INSTALL ${MPG123_EXTRACTED}/include/ DESTINATION ${CURRENT_PACKAGES_DIR}/include)
    file(INSTALL ${MPG123_EXTRACTED}/lib/ DESTINATION ${CURRENT_PACKAGES_DIR}/lib)
    file(INSTALL ${MPG123_EXTRACTED}/share/ DESTINATION ${CURRENT_PACKAGES_DIR}/share)

elseif(VCPKG_TARGET_IS_OSX OR VCPKG_TARGET_IS_LINUX)
    set(MPG123_OPTIONS
        --disable-dependency-tracking
    )

    # Find cross-compiler prefix
    if(VCPKG_CHAINLOAD_TOOLCHAIN_FILE)
        include("${VCPKG_CHAINLOAD_TOOLCHAIN_FILE}")
    endif()
    if(CMAKE_C_COMPILER)
        vcpkg_execute_required_process(
            COMMAND ${CMAKE_C_COMPILER} -dumpmachine
            WORKING_DIRECTORY ${CURRENT_BUILDTREES_DIR}
            LOGNAME dumpmachine-${TARGET_TRIPLET}
        )
        file(READ ${CURRENT_BUILDTREES_DIR}/dumpmachine-${TARGET_TRIPLET}-out.log MPG123_HOST)
        string(REPLACE "\n" "" MPG123_HOST "${MPG123_HOST}")
        message(STATUS "Cross-compiling with ${CMAKE_C_COMPILER}")
        message(STATUS "Detected autoconf triplet --host=${MPG123_HOST}")
        set(MPG123_OPTIONS
            --host=${MPG123_HOST}
            ${MPG123_OPTIONS}
        )
    endif()

    vcpkg_configure_make(
        SOURCE_PATH ${SOURCE_PATH}
        OPTIONS ${MPG123_OPTIONS}
    )
    vcpkg_install_make()

    file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/share")
endif()

if (NOT VCPKG_TARGET_IS_WINDOWS)
    file(INSTALL ${SOURCE_PATH}/COPYING DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
endif()

message(STATUS "Installing done")
