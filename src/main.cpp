#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "blobdetector.h"


int main( int argc, char** argv )
{
  cv::Mat input_image;
  input_image = cv::imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );

  if( argc != 2 || !input_image.data )
    {
      printf( "No image data \n" );
      return -1;
    }



  BlobDetector blobDetector;

  std::vector<Blob> blobs;
  cv::Mat blobs_image;

  blobDetector.detectBlackBlob(input_image, blobs_image, blobs);

  cv::namedWindow( "Blobs Image", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Blobs Image", blobs_image );

  cv::waitKey(0);

  return 0;
}
