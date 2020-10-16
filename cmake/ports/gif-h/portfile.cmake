include(vcpkg_common_functions)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO charlietangora/gif-h
    REF 08d2fa5c0cc1fb9f03b250b83a2b68f7a62f5fe1
    SHA512 aebbbe20480e08e13abb8e5ed2c835c0a709b913939d3fcffb96e602791522aaa337e44a57e51c5232122524799e18b9bec80c29d2708fa4ef0c5258ddc17a50
    HEAD_REF master
)

file(INSTALL ${SOURCE_PATH}/gif.h
	DESTINATION ${CURRENT_PACKAGES_DIR}/include
)

file(INSTALL ${SOURCE_PATH}/LICENSE
	DESTINATION ${CURRENT_PACKAGES_DIR}/share/gif-h/copyright
)