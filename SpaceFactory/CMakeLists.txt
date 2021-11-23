cmake_minimum_required(VERSION 3.0.2)

SET (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})

project(SpaceFactory)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to 'Release' as none was specified.")
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
		"MinSizeRel" "RelWithDebInfo")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-conversion-null")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(MSVC)
	add_definitions (/D _CRT_SECURE_NO_WARNINGS)
	add_definitions (/D YY_NO_UNISTD_H)
	add_compile_options(/wd4251)
	add_compile_options(/wd4099)
	add_compile_options(/wd4098)
endif()


include_directories(Src)

file( GLOB CC_SOURCE
  Src/Window/*.cpp
  )

add_library(SpaceFactoryLib STATIC ${CC_SOURCE})

add_executable(SpaceFactory Src/main.cpp)

target_link_libraries(SpaceFactory SpaceFactoryLib)

find_package(SFML 2.4 REQUIRED system window graphics)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(SpaceFactory ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
