#include "blobdetectorlog.h"
#include <opencv2/nonfree/features2d.hpp>


BlobDetectorLoG::BlobDetectorLoG()
{
}


void BlobDetectorLoG::buildGaussianPyramid(const cv::Mat& input_image, std::vector< cv::Mat >& pyramid, cv::Mat& smallest_level, const int& levels)
{
    pyramid.clear();
    cv::Mat current_image = input_image;
    for (int l=0; l<levels; l++)
    {
        cv::Mat down;
        cv::pyrDown(current_image, down);
        pyramid.push_back(down);
        current_image = down;

        cv::imshow( "down Image", down );
        cv::waitKey(0);
    }

    current_image.copyTo(smallest_level);
}


void BlobDetectorLoG::buildLaplacianPyramid(const cv::Mat& input_image, std::vector<cv::Mat>& pyramid, cv::Mat& smallest_level, const int& levels)
{
    std::vector<cv::Mat> gaussian_pyramid;
    cv::Mat smallest_level_gaussian;
    buildGaussianPyramid(input_image, gaussian_pyramid, smallest_level_gaussian, levels);


    pyramid.clear();
    cv::Mat current_image = input_image;
    std::cout<< "gaussian pyramid size: " << gaussian_pyramid.size() << std::endl;
    for (int l=gaussian_pyramid.size() - 1; l > 1; l--)
    {
        cv::Mat down,up;
        std::cout<< "l = " << l <<std::endl;
//        cv::pyrDown(current_image, down);

        cv::pyrUp(gaussian_pyramid[l], up);
        std::cout<<"size of 1 = " << gaussian_pyramid[l-1].rows <<", " <<gaussian_pyramid[l-1].cols <<std::endl;
        std::cout<<"size of 2 = " << up.rows <<", " <<up.cols <<std::endl;


        cv::Mat dog = gaussian_pyramid[l-1] - up;
        pyramid.push_back(dog);

        cv::imshow( "dog Image", dog);
        cv::waitKey(0);
//        current_image = dog;
    }
    current_image.copyTo(smallest_level);


}

void BlobDetectorLoG::detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity, const int& max_intensity)
{
//      int kernel_size = 3;
//      int ddepth = CV_16S;

//      // Remove noise by blurring with a Gaussian filter
//      cv::GaussianBlur( input_image, input_image, cv::Size(3,3), 0, 0 );

//      // Apply Laplace function
//      cv::Mat abs_dst;
//      cv::Mat laplacian;

//      cv::Laplacian( input_image, laplacian, ddepth, kernel_size );

//      cv::convertScaleAbs( laplacian, abs_dst );

    std::vector < cv::Mat > pyramid;
    std::vector < cv::Mat > dog_pyramid;

//    buildLaplacianPyramid(input_image, pyramid, blobs_image, 4);
//    blobs_image = abs_dst;


    cv::SIFT sift;
//    cv::SURF surf(5000);
    blobs_image = input_image;

//    std::vector < cv::KeyPoint > keypoints_surf;
//    surf.detect(input_image, keypoints_surf);
//    cv::drawKeypoints(input_image, keypoints_surf, blobs_image );

    cv::Mat blurred_img;
    cv::GaussianBlur(input_image, blurred_img, cv::Size(3, 3), 0, 0);


    sift.buildGaussianPyramid(blurred_img, pyramid, 3);
    sift.buildDoGPyramid(pyramid, dog_pyramid);
    std::vector < cv::KeyPoint > keypoints;
    sift.findScaleSpaceExtrema(pyramid, dog_pyramid, keypoints);
    std::cout << "size: " << keypoints.size() << std::endl;
    for(int i = 0; i < keypoints.size(); i++)
    {
        cv::circle(blobs_image, keypoints[i].pt, 5, cv::Scalar(175), 2);

    }

    cv::namedWindow( "processed", CV_WINDOW_AUTOSIZE );
    cv::imshow( "processed", dog_pyramid[4] );
    cv::waitKey(0);

}
