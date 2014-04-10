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

  srand(time(NULL));

  BlobDetector blobDetector;

  std::vector<Blob> blobs;
  cv::Mat blobs_image;

//  std::vector<cv::Mat> images;
//  blobDetector.generateBlobImages(7, 3, 1, images);

  cv::Mat gen_image;
  blobDetector.generateKnownBlobImage(gen_image, blobs);

  std::cout << "size of blobs: " << blobs.size() << std::endl;

  for(uint i = 0; i < blobs.size(); i++)
  {
      std::cout << "blob " << i << " center = " << blobs[i].center_.x << ", " << blobs[i].center_.y << " area = " << blobs[i].area_ << " circularity = " << blobs[i].circularity_ << std::endl;
  }


  cv::namedWindow( "Blobs Image", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Blobs Image", gen_image );

  cv::waitKey(0);

  std::vector<Blob> blobs_out;


    blobDetector.detectBlobs(gen_image, blobs_image, blobs_out, 0, 50);

    for(uint i = 0; i < blobs_out.size(); i++)
    {
        std::cout << "blob " << i << " center = " << blobs_out[i].center_.x << ", " << blobs_out[i].center_.y << " area = " << blobs_out[i].area_ << " circularity = " << blobs_out[i].circularity_ << std::endl;
    }


//  blobDetector.detectBlobsLaplacian(input_image, blobs_image, blobs);



//  std::cout << blobs_image <<std::endl;

//  blobDetector.detectBlobsContours(input_image, blobs_image, blobs, 0 ,50);
//  blobDetector.detectBlobs(input_image, blobs_image, blobs, 0, 50);
//  std::cout << "number of blobs = " << blobs.size() << std::endl;

//  for(uint i = 0; i < blobs.size(); i++)
//  {
//      std::cout << "blob " << i << " area = " << blobs[i].area_ << " circularity = " << blobs[i].circularity_ << std::endl;
//  }

  cv::namedWindow( "Blobs Image", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Blobs Image", blobs_image );

  cv::waitKey(0);
//  cv::imwrite("output.jpg", blobs_image);


  return 0;
}
