project(BlobDetection)

cmake_minimum_required(VERSION 2.8)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
find_package( OpenCV REQUIRED )

add_executable( BlobDetection src/main.cpp )
target_link_libraries( BlobDetection ${OpenCV_LIBS} )
