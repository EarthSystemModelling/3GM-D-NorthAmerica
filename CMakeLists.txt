cmake_minimum_required(VERSION 3.25.0)
if(${CMAKE_VERSION} VERSION_LESS "3.25.0")
    message(STATUS "You need to upgrade CMake! Minimum required version is 3.25.0.")
endif()

set(CMAKE_C_COMPILER "clang-14")
set(CMAKE_CXX_COMPILER "clang++-14")

# CMAKE flags
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

project(COASTGUARD)

# Build folder structure
add_subdirectory(global-gradient-based-groundwater-model/src)
add_subdirectory(global-gradient-based-groundwater-model/lib)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread")

################# Libs ################
# Boost
find_package(Boost 1.80.0 COMPONENTS system filesystem serialization log REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_LOG_DYN_LINK")

# OpenMP
FIND_PACKAGE(OpenMP)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -fopenmp")

# GMP
if (GMP_INCLUDE_DIR AND GMP_LIBRARIES)
    # Already in cache, be silent
    set(GMP_FIND_QUIETLY TRUE)
endif (GMP_INCLUDE_DIR AND GMP_LIBRARIES)
find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARIES NAMES gmp libgmp)
find_library(GMPXX_LIBRARIES NAMES gmpxx libgmpxx)
MESSAGE(STATUS "GMP libs: " ${GMP_LIBRARIES} " " ${GMPXX_LIBRARIES})
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMP DEFAULT_MSG GMP_INCLUDE_DIR GMP_LIBRARIES)

################################
# Steady North America model (with Variable Density Flow (VDF))
################################
add_subdirectory(SteadyNorthAmerica)
set(steady_na_src ${SOURCE})
add_executable(steady_na SteadyNorthAmerica/steady_na_runner.cpp ${steady_na_src} ${HEADERS})
target_link_libraries(steady_na pthread ${Boost_LIBRARIES} ${GMP_LIBRARIES})