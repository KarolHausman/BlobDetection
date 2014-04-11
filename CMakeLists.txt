project(BlobDetection)

cmake_minimum_required(VERSION 2.8)


if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
find_package( OpenCV REQUIRED )

add_executable( BlobDetection src/blobdetector.cpp src/blobdetectorlog.cpp src/blobdetectorcontours.cpp src/blobdetectorfloodfill.cpp src/blobevaluator.cpp src/main.cpp )
target_link_libraries( BlobDetection ${OpenCV_LIBS} )
