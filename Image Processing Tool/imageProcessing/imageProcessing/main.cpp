
// TASK 5(Final Task): Image Processing Tool

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

// for gaussian blur //
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;
char window_name[] = "operating";
Mat src; Mat dst;

int display_caption(const char* caption);
int display_dst(int delay);
// for gaussian blur //

int main(){
    cv::Mat img;
    cout << "\n\t\tWelcome to Photoshop\n" << endl;
    while (true) {
        // loading pictures
        cout << "1. Dodge Challenger Picture" << endl;
        cout << "2. Ferrari SF812 Picture" << endl;
        cout << "3. Ford Mustang Picture" << endl;
        cout << "4. Range Rover Picture" << endl;
        cout << "5. Lamborghini Picture" << endl;
        cout << "6. Exit!" << endl;
        cout << "\nChoose picture to load or exit(1 to 5 for pictures or 6 to exit): ";
        int choice;
        cin >> choice;
        if (choice < 1 or choice>6) {
            cout << "Invalid Input!" << endl;
            exit(0);
        }
        else if (choice == 1) {
            img = cv::imread("C:/Users/ACER/Desktop/CodSoft/Tasks/Task5/pictures/dodgechallenger2.jpg");
            namedWindow("Image Processing Application", WINDOW_AUTOSIZE);
            cv::imshow("Image Processing Application", img);
            cv::moveWindow("Image Processing Application", 0, 45);
            cv::waitKey(0);
            cv::destroyAllWindows();
        }
        else if (choice == 2) {
            img = cv::imread("C:/Users/ACER/Desktop/CodSoft/Tasks/Task5/pictures/ferrari.jpg");
            namedWindow("Image Processing Application", WINDOW_AUTOSIZE);
            cv::imshow("Image Processing Application", img);
            cv::moveWindow("Image Processing Application", 0, 45);
            cv::waitKey(0);
            cv::destroyAllWindows();
        }
        else if (choice == 3) {
            img = cv::imread("C:/Users/ACER/Desktop/CodSoft/Tasks/Task5/pictures/fordmustang.jpg");
            namedWindow("Image Processing Application", WINDOW_AUTOSIZE);
            cv::imshow("Image Processing Application", img);
            cv::moveWindow("Image Processing Application", 0, 45);
            cv::waitKey(0);
            cv::destroyAllWindows();
        }
        else if (choice == 4) {
            img = cv::imread("C:/Users/ACER/Desktop/CodSoft/Tasks/Task5/pictures/rangerover.jpg");
            namedWindow("Image Processing Application", WINDOW_AUTOSIZE);
            cv::imshow("Image Processing Application", img);
            cv::moveWindow("Image Processing Application", 0, 45);
            cv::waitKey(0);
            cv::destroyAllWindows();
        }
        else if (choice == 5) {
            img = cv::imread("C:/Users/ACER/Desktop/CodSoft/Tasks/Task5/pictures/lamborghini.jpg");
            namedWindow("Image Processing Application", WINDOW_AUTOSIZE);
            cv::imshow("Image Processing Application", img);
            cv::moveWindow("Image Processing Application", 0, 45);
            cv::waitKey(0);
            cv::destroyAllWindows();
        }
        else if (choice == 6) { // exiting from the program
            cout << "\nThank you for using Photoshop!!" << endl;
            exit(0);
        }
        while (true) {
            // applying operations
            cout << "\nSelect operation to perform-> " << endl;
            cout << "1. Apply Gaussian Blur" << endl;
            cout << "2. Apply Grayscale" << endl;
            cout << "3. Apply Sharpen" << endl;
            cout << "4. Change Brightness" << endl;
            cout << "5. Change Contrast" << endl;
            cout << "6. Crop Image" << endl;
            cout << "7. Resize Image" << endl;
            cout << "8. Save and Exit" << endl;
            cout << "Enter choice: ";
            int choice2;
            cin >> choice2;
            if(choice2 < 1 or choice2>8){
                cout << "Invalid Input!" << endl;
                break;
            }
            else if (choice2 == 1) { // gaussian blur
                namedWindow(window_name, WINDOW_AUTOSIZE);
                src = img;
                if (display_caption("Original Image") != 0) {
                    return 0;
                }
                dst = src.clone();
                if (display_dst(DELAY_CAPTION) != 0) {
                    return 0;
                }
                if (display_caption("Gaussian Blur") != 0) {
                    return 0;
                }
                for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
                    GaussianBlur(src, dst, Size(i, i), 0, 0);
                    if (display_dst(DELAY_BLUR) != 0) {
                        return 0;
                    }
                }
                display_caption("Done!");
                cv::moveWindow("Image Processing Application", 0, 45);
                cv::waitKey(0);
                cv::destroyAllWindows();
            }
            else if (choice2 == 2) { // grayscaling
                src = img;
                Mat grayImg;
                cvtColor(src, grayImg, COLOR_BGR2GRAY);
                imshow("Grayscaled image", grayImg);
                cv::waitKey(0);
                cv::destroyAllWindows();
            }
            else if (choice2 == 3) { // sharpening
                src = img;
                Mat sharpImg; 
                Mat sharpening_kernel = (Mat_<double>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);
                filter2D(src, sharpImg, -1, sharpening_kernel);
                imshow("Sharpened Image", sharpImg);
                cv::waitKey(0);
                cv::destroyAllWindows();
            }
            else if (choice2 == 4) { // brightness(increase or decrease)
                src = img;
                cout << "1. Increase Brightness" << endl;
                cout << "2. Decrease Brightness"<< endl;
                cout << "Enter Choice: ";
                int choice3;
                cin >> choice3;
                if (choice3 < 1 or choice3 > 2) {
                    cout << "Invalid Input!" << endl;
                    break;
                }
                else if (choice3 == 1) {
                    src = img;
                    Mat brighterImg;
                    brighterImg = src;
                    src.convertTo(brighterImg, -1, 1, 50);
                    imshow("Brightened Image", brighterImg);
                    cv::waitKey(0);
                    cv::destroyAllWindows();
                }
                else if (choice3 == 2) {
                    src = img;
                    Mat deamImg;
                    deamImg = src;
                    src.convertTo(deamImg, -1, 1, -50);
                    imshow("Deamed Image", deamImg);
                    cv::waitKey(0);
                    cv::destroyAllWindows();
                }
            }
            else if (choice2 == 5) { // contrast(increase or decrease)
                cout << "1. Increase Contrast" << endl;
                cout << "2. Decrease Contrast" << endl;
                cout << "Enter Choice: ";
                int choice3;
                cin >> choice3;
                if (choice3 < 1 or choice3 > 2) {
                    cout << "Invalid Input!" << endl;
                    break;
                }
                else if (choice3 == 1) {
                    src = img;
                    Mat contrastImg;
                    contrastImg = src;
                    src.convertTo(contrastImg, -1, 2, 0);
                    imshow("Increased Contrast", contrastImg);
                    cv::waitKey(0);
                    cv::destroyAllWindows();
                }
                else if (choice3 == 2) {
                    src = img;
                    Mat contrastImg;
                    contrastImg = src;
                    src.convertTo(contrastImg, -1, 0.5, 0);
                    imshow("Increased Contrast", contrastImg);
                    cv::waitKey(0);
                    cv::destroyAllWindows();
                }
            }
            else if (choice2 == 6) { // cropping the image
                src = img;
                cv::Rect myROI(10, 20, 700, 600);
                cv::Mat croppedImage = src(myROI);
                imshow("Cropped Image", croppedImage);
                cv::waitKey(0);
                cv::destroyAllWindows();
            }
            else if (choice2 == 7) { // resizing the image according to user
                src = img;
                cout << "Enter width: ";
                int width;
                cin >> width;
                cout << "Enter height: ";
                int height;
                cin >> height;
                Mat resizedImg;
                resize(src, resizedImg, Size(width, height), INTER_LINEAR);
                imshow("Resized Image", resizedImg);
                cv::waitKey(0);
                cv::destroyAllWindows();
            }
            else if (choice2 == 8) { // going back to the menu
                imwrite("test.jpg", img);
                cout << "Going back to menu!\n" << endl;
                break;
            }
        }
    }
    return 0;
}
int display_caption(const char* caption) {
    dst = Mat::zeros(src.size(), src.type());
    putText(dst, caption, Point(src.cols / 4, src.rows / 2), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
    return display_dst(DELAY_CAPTION);
}
int display_dst(int delay) {
    imshow(window_name, dst);
    int c = waitKey(delay);
    if (c >= 0) {
        return -1;
    }
    return 0;
}