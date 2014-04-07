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

  blobDetector.detectBlobsLaplacian(input_image, blobs_image, blobs);

//  std::cout << blobs_image <<std::endl;

//  blobDetector.detectBlobsContours(input_image, blobs_image, blobs, 0 ,50);
//  blobDetector.detectBlobs(input_image, blobs_image, blobs, 0, 50);
  std::cout << "number of blobs = " << blobs.size() << std::endl;

  for(uint i = 0; i < blobs.size(); i++)
  {
      std::cout << "blob " << i << " area = " << blobs[i].area_ << " circularity = " << blobs[i].circularity_ << std::endl;
  }

  cv::namedWindow( "Blobs Image", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Blobs Image", blobs_image );

  cv::waitKey(0);
//  cv::imwrite("output.jpg", blobs_image);


  return 0;
}
