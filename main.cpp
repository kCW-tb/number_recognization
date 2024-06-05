#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat save_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Save_black.jpg");
Mat save_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Save_red.jpg");
Mat load_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Load_black.jpg");
Mat load_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Load_red.jpg");
Mat clear_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Clear_black.jpg");
Mat clear_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Clear_red.jpg");
Mat run_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Run_black.jpg");
Mat run_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Run_red.jpg");
Mat exit_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Exit_black.jpg");
Mat exit_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Exit_red.jpg");
Mat feature1_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature1_black.jpg");
Mat feature2_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature2_black.jpg");
Mat feature3_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature3_black.jpg");
Mat feature4_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature4_black.jpg");
Mat feature5_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature5_black.jpg");
Mat feature6_black = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature6_black.jpg");
Mat feature1_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature1_red.jpg");
Mat feature2_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature2_red.jpg");
Mat feature3_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature3_red.jpg");
Mat feature4_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature4_red.jpg");
Mat feature5_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature5_red.jpg");
Mat feature6_red = imread("C:/Users/AIRLAB/source/repos/OpenCV/OpenCV/Feature6_red.jpg");

//menu
void copyimg(Mat& img, Rect area, Mat& copy);
Mat drawLineImg();
void turn_menu_color(Mat board);
//전처리
Mat grayThres(Mat numberimg);
Mat get_numberArea(Mat origin_numberimg);
void sizerepair(Mat& preImg);
//feature

//mouse_event
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main(void)
{
    Mat img = drawLineImg();
    char c;
    namedWindow("NUMBER");
    while (true) {
        setMouseCallback("NUMBER", on_mouse, &img);
        imshow("NUMBER", img);
        c = waitKey(1);
        if (c == 27) break;
    }
    return 0;
}

//menu 관련 함수
void copyimg(Mat& img, Rect area, Mat& copy) {
    resize(copy, copy, Size(120, 70));
    Point start(area.x, area.y);
    start.x += (area.width - copy.cols) / 2;
    start.y += (area.height - copy.rows) / 2;

    copy.copyTo(img(Rect(start.x, start.y, copy.cols, copy.rows)));
}
Mat drawLineImg() {
    Mat board(500, 800, CV_8UC3, Scalar(255, 255, 255));
    rectangle(board, Rect(0, 0, 500, 650), Scalar(0, 0, 0), 2);
    rectangle(board, Rect(500, 0, 150, 100), Scalar(0, 0, 0), 2);       //Save  Rect(500, 0, 150, 100)
    rectangle(board, Rect(500, 100, 150, 100), Scalar(0, 0, 0), 2);     //Load  Rect(500, 100, 150, 100)
    rectangle(board, Rect(500, 200, 150, 100), Scalar(0, 0, 0), 2);     //Clear Rect(500, 200, 150, 100)
    rectangle(board, Rect(500, 300, 150, 100), Scalar(0, 0, 0), 2);     //Run   Rect(500, 300, 150, 100)
    rectangle(board, Rect(500, 400, 150, 100), Scalar(0, 0, 0), 2);     //Exit  Rect(500, 400, 150, 100)
    rectangle(board, Rect(650, 0, 150, 100), Scalar(0, 0, 0), 2);   //feature1
    rectangle(board, Rect(650, 100, 150, 100), Scalar(0, 0, 0), 2);   //feature2
    rectangle(board, Rect(650, 200, 150, 100), Scalar(0, 0, 0), 2);   //feature3
    rectangle(board, Rect(650, 300, 150, 100), Scalar(0, 0, 0), 2);   //feature4
    rectangle(board, Rect(650, 400, 150, 100), Scalar(0, 0, 0), 2);   //feature5

    copyimg(board, Rect(500, 0, 150, 100), save_black);
    copyimg(board, Rect(500, 100, 150, 100), load_black);
    copyimg(board, Rect(500, 200, 150, 100), clear_black);
    copyimg(board, Rect(500, 300, 150, 100), run_black);
    copyimg(board, Rect(500, 400, 150, 100), exit_black);
    copyimg(board, Rect(650, 0, 150, 100), feature1_black);
    copyimg(board, Rect(650, 100, 150, 100), feature2_black);
    copyimg(board, Rect(650, 200, 150, 100), feature3_black);
    copyimg(board, Rect(650, 300, 150, 100), feature4_black);
    copyimg(board, Rect(650, 400, 150, 100), feature5_black);

    return board;
}
void turn_menu_color(Mat board) {
    copyimg(board, Rect(500, 0, 150, 100), save_black);
    copyimg(board, Rect(500, 100, 150, 100), load_black);
    copyimg(board, Rect(500, 200, 150, 100), clear_black);
    copyimg(board, Rect(500, 300, 150, 100), run_black);
    copyimg(board, Rect(500, 400, 150, 100), exit_black);
    copyimg(board, Rect(650, 0, 150, 100), feature1_black);
    copyimg(board, Rect(650, 100, 150, 100), feature2_black);
    copyimg(board, Rect(650, 200, 150, 100), feature3_black);
    copyimg(board, Rect(650, 300, 150, 100), feature4_black);
    copyimg(board, Rect(650, 400, 150, 100), feature5_black);
}

//이미지 전처리 관련 함수
//1번 GrayScale + Threshold
Mat grayThres(Mat numberimg) {
    cvtColor(numberimg, numberimg, COLOR_BGR2GRAY);
    threshold(numberimg, numberimg, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    return numberimg;
}
//2번 모폴로지 연산

//3번 숫자 영역 가져오기
Mat get_numberArea(Mat preImg) {
    Mat labels, stats, centroids;
    int cnt = connectedComponentsWithStats(preImg, labels, stats, centroids);
    //숫자 객체가 분리되어 있는 경우
    if (cnt > 2) {
        int largth = 10;
        while (true) {
            //점차 증가하는 length값으로 모폴로지 연산 수행
            morphologyEx(preImg, preImg, MORPH_CLOSE, Mat(largth, largth, CV_8UC1));
            cnt = connectedComponentsWithStats(preImg, labels, stats, centroids);
            if (cnt <= 2) break;
            largth += 3;
        }
    }
    int* p = stats.ptr<int>(1);
    return preImg(Rect(p[0], p[1], p[2], p[3])).clone();
}

//4번
void sizerepair(Mat& preImg) {
    Mat array(400, 250, CV_8UC1);
    resize(preImg, preImg, Size(250, 500));
}

//전처리 통합 함수
Mat PretreatmentImg(Mat origin_numberimg) {
    Mat preImg = grayThres(origin_numberimg);   //GrayScale 변경 및 이진화
    morphologyEx(preImg, preImg, MORPH_CLOSE, Mat(10, 10, CV_8UC1)); //모폴로지 연산
    Mat numberImg = get_numberArea(preImg);     //숫자영역만 추출
    sizerepair(numberImg);  //size수정
    return numberImg;
}

//feature 관련 함수
//1번 이미지 객체에 대해 외각선 개수 추출
//2번 내부 외각선이 없으면 pass 내부 외각선이 있다면 전체 객체와 내부외각선 무게중심을 비교
//3번 객체에 선을 그어 만나는 외각선 개수 판별
//4번 중앙 영역(가로로 직사각형)제거하고 생기는 외각선 개수 판별


//마우스 이벤트 관련 함수
void savefile(Mat& userdata) {
    string fileName = "";
    Mat save = (userdata)(Rect(1, 1, 498, 498)).clone();
    resize(save, save, Size(500, 500));
    cout << "input fileName : ";
    cin >> fileName;
    fileName += ".jpg";
    imwrite(fileName, save);
    cout << fileName << " saved file" << endl;
}
Mat loadfile() {
    Mat number;
    while (true) {
        string fileName = "";
        cout << "input fileName : ";
        cin >> fileName;
        fileName += ".jpg";
        number = imread(fileName);
        if (number.empty()) { cout << "none img, enter the correct file name"; }
        else break;
    }
    rectangle(number, Rect(0, 0, 500, 500), Scalar(0, 0, 0), 2);
    return number;
}


void on_mouse(int event, int x, int y, int flags, void* userdata) {
    static Point prePoint = Point(0, 0);
    Rect save(500, 0, 148, 100), load(500, 100, 148, 100), clear(500, 200, 148, 100), run(500, 300, 148, 100), exit_f(500, 400, 148, 100);
    Rect feature1(650, 0, 148, 100), feature2(650, 100, 148, 100), feature3(650, 200, 148, 100), feature4(650, 300, 148, 100), feature5(650, 400, 148, 100);
    if (Point(x, y).inside(save)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, save, save_red);
    }
    else if (Point(x, y).inside(load)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, load, load_red);
    }
    else if (Point(x, y).inside(clear)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, clear, clear_red);
    }
    else if (Point(x, y).inside(run)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, run, run_red);
    }
    else if (Point(x, y).inside(exit_f)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, exit_f, exit_red);
    }
    else if (Point(x, y).inside(feature1)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, feature1, feature1_red);
    }
    else if (Point(x, y).inside(feature2)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, feature2, feature2_red);
    }
    else if (Point(x, y).inside(feature3)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, feature3, feature3_red);
    }
    else if (Point(x, y).inside(feature4)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, feature4, feature4_red);
    }
    else if (Point(x, y).inside(feature5)) {
        turn_menu_color(*(Mat*)userdata);
        copyimg(*(Mat*)userdata, feature5, feature5_red);
    }
    else {
        turn_menu_color(*(Mat*)userdata);
    }

    switch (event) {
    case EVENT_LBUTTONDOWN:
        prePoint = Point(x, y);
        if (Point(x, y).inside(Rect(500, 300, 150, 100))) {
            //Run
            Mat preimg = PretreatmentImg((*(Mat*)userdata)(Rect(2, 2, 497, 497)));
            imshow("preImg", preimg);
            waitKey();
        }
        else if (Point(x, y).inside(Rect(500, 0, 150, 100))) {
            //Save
            savefile(*(Mat*)userdata);
        }
        else if (Point(x, y).inside(Rect(500, 100, 150, 100))) {
            //Load
            loadfile().copyTo((*(Mat*)userdata)(Rect(0, 0, 500, 500)));
        }
        else if (Point(x, y).inside(Rect(500, 200, 150, 100))) {
            //Clear
            (*(Mat*)userdata)(Rect(1, 1, 498, 498)) = Scalar(255, 255, 255);
        }
        else if (Point(x, y).inside(Rect(500, 400, 150, 100))) {
            //Exit
            exit(1);
        }
        break;
    case EVENT_MOUSEMOVE:
        if (!Rect(1, 1, 498, 498).contains(Point(x, y))) break;
        if (flags == EVENT_FLAG_LBUTTON) {
            line(*(Mat*)userdata, prePoint, Point(x, y), Scalar(0, 0, 0), 3);
            prePoint = Point(x, y);
        }
        else if (flags == EVENT_FLAG_CTRLKEY) {
            line(*(Mat*)userdata, prePoint, Point(x, y), Scalar(255, 255, 255), 10);
            prePoint = Point(x, y);
        }
        break;
    case EVENT_LBUTTONUP:
        prePoint = Point(x, y);
        break;
    default:
        break;
    }
    imshow("NUMBER", *(Mat*)userdata);
}
