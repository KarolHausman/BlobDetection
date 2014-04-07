#include "blobdetector.h"


BlobDetector::BlobDetector()
{
}


void BlobDetector::detectBlobsLaplacian(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs)
{
      int kernel_size = 3;
      int ddepth = CV_16S;

      // Remove noise by blurring with a Gaussian filter
      cv::GaussianBlur( input_image, input_image, cv::Size(3,3), 0, 0 );

      // Apply Laplace function
      cv::Mat abs_dst;
      cv::Mat laplacian;

      cv::Laplacian( input_image, laplacian, ddepth, kernel_size );

      cv::convertScaleAbs( laplacian, abs_dst );
      blobs_image = abs_dst;

}

void BlobDetector::detectBlobsContours(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity, const int& max_intensity)
{
    uint min_contour_size(40);
    blobs_image = input_image;
    bool no_color_flag = true;

    cv::Mat blurred_image;
    cv::Mat processed_image;

    cv::GaussianBlur(input_image, blurred_image, cv::Size(3, 3), 0, 0);

    if (( max_intensity >= 0 ) || (min_intensity >= 0))
    {
        cv::inRange(blurred_image, cv::Scalar(min_intensity), cv::Scalar(max_intensity), processed_image);
        no_color_flag = false;
    }
    else
    {
        double canny_threshold(70);
        cv::Mat canny_image;
        cv::Canny(blurred_image, canny_image, canny_threshold, canny_threshold * 2);

        cv::morphologyEx(canny_image, processed_image, cv::MORPH_CLOSE, cv::Mat());
    }

    cv::namedWindow( "processed", CV_WINDOW_AUTOSIZE );
    cv::imshow( "processed", processed_image );
    cv::waitKey(0);


    std::vector < std::vector < cv::Point > > contours;
    std::vector < cv::Vec4i > hierarchy;
    cv::findContours(processed_image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

    std::cout<< "contour size" << contours[0].size() <<std::endl;
    // Get the moments
    std::vector<cv::Moments> mu(contours.size() );
    for( uint i = 0; i < contours.size(); i++ )
    {
        std::cout << "hierarchy 0 = " << hierarchy[i][0] << ", 1 = " << hierarchy[i][1] << ", 2 = " << hierarchy[i][2] << ", 3 = " <<hierarchy[i][3] <<std::endl;
        mu[i] = cv::moments( contours[i], false );
    }
    // Get the mass centers:
    std::vector<cv::Point2f> mc( contours.size() );
    for( uint i = 0; i < contours.size(); i++ )
    {
        mc[i] = cv::Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
    }


    // Draw contours
    cv::RNG rng(12345);
    cv::Mat drawing = cv::Mat::zeros( processed_image.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        if ( ( (hierarchy[i][3] != -1) || (!no_color_flag) ) && (!cv::isContourConvex(contours[i])) && (contours[i].size() > min_contour_size))
        {
            //calculate moments
            cv::Moments mu = cv::moments( contours[i], false );
            cv::Point2f mc = cv::Point2f( mu.m10/mu.m00 , mu.m01/mu.m00 );

            //calculate circularity
            cv::Point2f circle_center = cv::Point2f( 0, 0);
            float circle_radius(0);
            cv::minEnclosingCircle( contours[i], circle_center, circle_radius);
            double area = mu.m00;
            double circularity = (M_PI * circle_radius * circle_radius) / area;


            if (circularity < 1.4 && circularity > 0.6)
            {
                //draw circles on the output_image
                cv::circle( blobs_image, circle_center, circle_radius, cv::Scalar(255));
            }

            //add blob
            Blob blob( mc, area, circularity);
            blobs.push_back(blob);

            cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            cv::drawContours( drawing, contours, i, color, 2, 8, hierarchy, 1);
            cv::circle( drawing, mc, 2, color, 1);
        }
    }

    cv::namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    cv::imshow( "Contours", drawing );
    cv::waitKey(0);

}




void BlobDetector::detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity, const int& max_intensity)
{
    //thresholding
    //TODO: make params

    //show circles on input_image
    blobs_image = input_image;

    const cv::Scalar floodfill_lo_diff = cv::Scalar(0);
    const cv::Scalar floodfill_up_diff = cv::Scalar(10);
    const int min_blob_radius = 10;

    cv::Mat blurred_image;
    cv::GaussianBlur(input_image, blurred_image, cv::Size(3, 3), 0, 0);

    cv::Mat closed_image;
    cv::morphologyEx(input_image, closed_image, cv::MORPH_CLOSE, cv::Mat());


    cv::Mat bw_image;

    cv::inRange(closed_image, cv::Scalar(min_intensity), cv::Scalar(max_intensity), bw_image);
    // 0 = black, 255 = white


    //distance transform
    cv::Mat distance_image;
    cv::distanceTransform(bw_image, distance_image, CV_DIST_L1, 3);
    // how far from black


    double min_val(0), max_val(0);
    cv::Point p_min, p_max;
    int area(0);
    double circularity(0);
    cv::Mat mask = cv::Mat::ones(distance_image.rows, distance_image.cols, CV_8U);

    while(true)
    {

        cv::minMaxLoc(distance_image, &min_val, &max_val, &p_min, &p_max, mask);

        if (max_val < min_blob_radius)
        {
            return;
        }

        cv::Mat mask_flood = cv::Mat::zeros(bw_image.rows + 2, bw_image.cols + 2, CV_8U);
        cv::Rect rect;
        area = cv::floodFill(bw_image, mask_flood, p_max, cv::Scalar(0), &rect, floodfill_lo_diff, floodfill_up_diff);


        //draw blobs
        cv::circle(blobs_image, p_max, max_val, cv::Scalar(175), 1);
//        cv::circle(blobs_image, p_max, 3, cv::Scalar(175), 10 );

        circularity = (M_PI * max_val * max_val)/static_cast<double> (area);

        Blob blob(p_max, area, circularity);
        blobs.push_back(blob);

        mask = mask - mask_flood(cv::Rect(1, 1, bw_image.cols, bw_image.rows));

    }
//    blobs_image = bw_image;
//    cv::normalize(blobs_image, blobs_image, 0, 1., cv::NORM_MINMAX);
//    std::cout<<blobs_image;

}



