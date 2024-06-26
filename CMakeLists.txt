cmake_minimum_required(VERSION 3.20)

project(kwin4_effect_colorcorrectionfilter)

set(KF_MIN_VERSION "5.78")
set(QT_MIN_VERSION "5.15")
set(QT_MAJOR_VERSION 5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DQT_NO_DEBUG_OUTPUT")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${ECM_MODULE_PATH}
    ${ECM_KDE_MODULE_DIR}
)
if(ECM_VERSION VERSION_GREATER "5.200.0")
    set(QT_MIN_VERSION "6.4.0")
    set(QT_MAJOR_VERSION 6)
endif()

include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

# required frameworks by Core
find_package(KF${QT_MAJOR_VERSION} ${KF_MIN_VERSION} REQUIRED COMPONENTS
    ConfigWidgets
)
if(${QT_MAJOR_VERSION} EQUAL 6)
    find_package(KF${QT_MAJOR_VERSION} ${KF_MIN_VERSION} REQUIRED COMPONENTS
            KCMUtils
    )

    find_package(KWin REQUIRED COMPONENTS
            kwineffects
    )
    set(KWIN_EFFECT_INCLUDE_FILE "/usr/include/kwin/effect/effect.h")
else()
    find_package(KWinEffects REQUIRED COMPONENTS
            kwineffects
            kwinglutils
    )
    set(KWIN_EFFECT_INCLUDE_FILE "/usr/include/kwineffects.h")
endif ()

find_package(epoxy REQUIRED)
find_package(XCB REQUIRED COMPONENTS XCB)

find_package(KWinDBusInterface CONFIG REQUIRED)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

execute_process(
    COMMAND sh -c "grep '#define KWIN_EFFECT_API_VERSION_MINOR' ${KWIN_EFFECT_INCLUDE_FILE} | awk '{print \$NF}'"
    OUTPUT_VARIABLE KWIN_EFFECT_API_VERSION_MINOR OUTPUT_STRIP_TRAILING_WHITESPACE
)
message("KWinEffect API Version: ${KWIN_EFFECT_API_VERSION_MINOR}")
message("")

add_test (NAME KWinEffectSupport COMMAND sh ${CMAKE_CURRENT_LIST_DIR}/tools/isSupported.sh)
set_property (TEST KWinEffectSupport PROPERTY PASS_REGULAR_EXPRESSION "true")


# these are cache variables, so they could be overwritten with -D,
set(CPACK_PACKAGE_NAME kwin4-effect-colorcorrectionfilter
    CACHE STRING kwin4-effect-colorcorrectionfilter
)
set(CPACK_DEBIAN_FILE_NAME "kwin4-effect-colorcorrection-lliurex23-amd64.deb")
set(CPACK_PACKAGE_CONTACT "juanma1980@gmail.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "juanma1980")
set(CPACK_DEBIAN_PACKAGE_VERSION "0.3.0")

# autogenerate dependency information
set (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

# To generate deb files, install 'dpkg-dev' package and then run 'cpack -G DEB'
