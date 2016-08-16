project(AGain)
cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_COLOR_MAKEFILE ON)

if(MSVC)
    add_definitions(/D _CRT_SECURE_NO_WARNINGS)
endif()

set(VSTSDK_PATH "/Applications/JUCE/VST3_SDK/" CACHE PATH "Path to VST SDK")
set(VSTSDK_INCLUDE_DIR ${VSTSDK_PATH})
set(VSTSDK_PLUGIN_SOURCE
    ${VSTSDK_PATH}/public.sdk/source/vst2.x/audioeffectx.cpp
    ${VSTSDK_PATH}/public.sdk/source/vst2.x/audioeffect.cpp
    ${VSTSDK_PATH}/public.sdk/source/vst2.x/vstplugmain.cpp
)

set(VSTSDK_HOST_SOURCE
  ${VSTSDK_PATH}/pluginterfaces/vst2.x/aeffectx.h
)

set(AGAIN_SOURCE
    src/again.cpp
    src/again.h
    src/againmain.cpp
    resources/again.rc
    resources/vstplug.def
    ${VSTSDK_PLUGIN_SOURCE}
    ${VSTSDK_HOST_SOURCE}
)

add_library(again MODULE ${AGAIN_SOURCE})

include_directories(${VSTSDK_INCLUDE_DIR})
target_link_libraries(again ${VSTSDK_LIBRARIES})

set_target_properties(again PROPERTIES 
  BUNDLE true
  BUNDLE_EXTENSION "vst"
  XCODE_ATTRIBUTE_WRAPPER_EXTENSION "vst"
  MACOSX_BUNDLE_INFO_PLIST "resources/Info.plist.in"
  MACOSX_BUNDLE_BUNDLE_NAME "AGain"
  MACOSX_BUNDLE_GUI_IDENTIFIER "com.CompanyName.AGain"
  MACOSX_BUNDLE_ICON_FILE ""
  MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0.0"
  MACOSX_BUNDLE_COPYRIGHT "CompanyName © 2016"
)

if(APPLE)
  install(TARGETS again
    DESTINATION "$ENV{HOME}/Library/Audio/Plug-Ins/VST"
  )
endif()

if(WIN32)
  #Set Install Path
endif()
