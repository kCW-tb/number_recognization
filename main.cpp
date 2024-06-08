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
void contours_size(Mat img);
void weight_contours(Mat img);
void erase_rArea(Mat img);
void ru_2_ld(Mat img);

//mouse_event
void on_mouse(int event, int x, int y, int flags, void* userdata);

const int rows = 10;
const int cols = 5;
int identify_number[rows][cols] = { 0 };
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
    rectangle(board, Rect(0, 0, 500, 650), Scalar(0, 0, 0), 1);
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
        int largth = 13;
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
//4번 크기조정
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
//1번 이미지 객체에 대해 외각선 개수 추출 - stop
void contours_size(Mat img) {
    vector<vector<Point>> contours;
    findContours(img, contours, RETR_LIST, CHAIN_APPROX_NONE);
    if (contours.size() == 1) {
        //1, 2, 3, 4, 5, 7
        identify_number[1][0] = 1;
        identify_number[2][0] = 1;
        identify_number[3][0] = 1;
        identify_number[4][0] = 1;
        identify_number[5][0] = 1;
        identify_number[7][0] = 1;
        cout << "가능 숫자 : 1, 2, 3, 4, 5, 7" << endl;
    }
    else if (contours.size() == 2) {
        //4,6,9,0
        identify_number[1][0] = -5;
        identify_number[2][0] = -5;
        identify_number[3][0] = -5;
        identify_number[7][0] = -5;
        identify_number[4][0] = 1;
        identify_number[6][0] = 1;
        identify_number[9][0] = 1;
        identify_number[0][0] = 1;
        cout << "가능 숫자 : 4, 6, 9, 0" << endl;
    }
    else {
        //0, 8
        identify_number[1][0] = -5;
        identify_number[2][0] = -5;
        identify_number[3][0] = -5;
        identify_number[7][0] = -5;
        identify_number[0][0] = 1;
        identify_number[8][0] = 1;
        cout << "가능 숫자 : 8, 0" << endl;
    }
    cout << "해당 숫자 객체에 대한 외각선 개수 : " << contours.size() << endl;
}
//2번 내부 외각선이 없으면 false 내부 외각선이 있다면 전체 객체와 내부외각선 무게중심을 비교 6,4,9판별을 위한 조건
void weight_contours(Mat img) {
    cout << "내부 외각전 유무와 내부 외각선에 대한 무게중심 비교." << endl;
    vector<vector<Point>> contours, min_contours;
    findContours(img, contours, RETR_LIST, CHAIN_APPROX_NONE);
    Point out_contours(0, 0), in_contours(0, 0);
    if (contours.size() >= 3) {
        cout << "내부 외각선 2개 존재" << endl;
        RotatedRect rect = minAreaRect(contours[2]);
        findContours(img(Rect(0, rect.center.y, img.cols, 1)), min_contours, RETR_LIST, CHAIN_APPROX_NONE);
        int eight_zero = min_contours.size();
        img(Rect(0, rect.center.y, img.cols, 1)) = 0;
        //imshow("dddd", img);
        //waitKey();
        if (eight_zero == 2 || eight_zero == 1) {
            identify_number[8][1] = 1;
            cout << endl << "해당 특성 결과는 8입니다." << endl;
        }
        else if (eight_zero == 3) {
            identify_number[0][1] = 1;
            cout << endl << "해당 특성 결과는 0입니다." << endl;
        }
    }
    /*
    //boundingRect사용방법
    if (contours.size() >= 3) {
        cout << "내부 외각선 2개 존재" << endl;
        Rect rec = boundingRect(contours[2]);
        Mat lables, eight_or_zero = img(Rect(0, rec.y + rec.height / 2, img.cols, 1)).clone();
        int count_8_0 = connectedComponents(eight_or_zero, lables);
        count_8_0 -= 1;
        img(Rect(0, rec.y + rec.height / 2, img.cols, 1)) = 0;
        imshow("dddd", img);
        waitKey();
        if (count_8_0 == 2 || count_8_0 == 1) {
            identify_number[8][1] = 1;
            cout << endl << "해당 특성 결과는 8입니다." << endl;
        }
        else {
            identify_number[0][1] = 1;
            cout << endl << "해당 특성 결과는 0입니다." << endl;
        }
    }
    */
    else if (contours.size() == 2) {
        cout << "내부 외각선 1개 존재 " << endl;
        for (int i = 0; i < contours[0].size(); i++) {
            out_contours += Point(contours[0][i]);
        }
        for (int i = 0; i < contours[1].size(); i++) {
            in_contours += Point(contours[1][i]);
        }
        out_contours.y /= contours[0].size();
        in_contours.y /= contours[1].size();
        if (in_contours.y > out_contours.y) {
            identify_number[0][1] = 1;
            identify_number[4][1] = 1;
            identify_number[9][1] = 1;
            cout << "in_contours : " << in_contours.y << " out_contours : " << out_contours << endl;
            cout << "내부 외각선의 무게중심이 외부 외각선의 무게중심보다 높음" << endl;
            cout << endl << "4, 9, 0 중 하나입니다." << endl;
        }
        if (in_contours.y < out_contours.y) {
            identify_number[0][1] = 1;
            identify_number[6][1] = 1;
            cout << "in_contours : " << in_contours.y << " out_contours : " << out_contours << endl;
            cout << "내부 외각선의 무게중심이 외부 외각선의 무게중심보다 낮음" << endl;
            cout << endl << "6, 0 중 하나입니다." << endl;
        }
    }
    else {
        cout << "내부 외각선 0개 존재 " << endl;
        identify_number[1][1] = 1;
        identify_number[2][1] = 1;
        identify_number[3][1] = 1;
        identify_number[4][1] = 1;
        identify_number[5][1] = 1;
        identify_number[7][1] = 1;
        cout << endl << "1, 2, 3, 4, 5, 7 중 하나입니다." << endl;
    }
}
//3번 우측 상단 시작점에서 좌측 하단 끝나는 종료점까지 선을 그어 만나는 외각선 개수 판별 - stop
void ru_2_ld(Mat img) {
    Mat tmp_img = img.clone();
    Mat line_img(Size(img.cols, img.rows), CV_8UC3, Scalar(0,0,0));
    tmp_img /= 2;
    line(line_img, Point(tmp_img.cols - 51, 0), Point(50, tmp_img.rows - 1), Scalar(200, 200, 200), 3);
    cvtColor(line_img, line_img, COLOR_BGR2GRAY);
    addWeighted(tmp_img, 1, line_img, 1, 0, tmp_img);
    threshold(tmp_img, tmp_img, 250, 255, THRESH_BINARY);
    //imshow("tmp_img", tmp_img);
    //waitKey();
    Mat labels, stats, centroids;
    int num_labels = connectedComponentsWithStats(tmp_img, labels, stats, centroids);
    num_labels -= 1; //배경 제거
    if (num_labels == 1) {
        //1, 7, 4
        cout << "우측 상단에서 좌측 하단으로 선을 그을 때 접촉하는 외각선 개수 1개" << endl;
        cout << "1, 7, 4 중 하나입니다." << endl;
        identify_number[6][2] = -5;
        identify_number[9][2] = -5;
        identify_number[8][2] = -5;
        identify_number[0][2] = -5;
        identify_number[1][2] = 1;
        identify_number[4][2] = 1;
        identify_number[7][2] = 1;
    }
    else if (num_labels == 2) {
        //1, 2, 6, 9, 0
        cout << "우측 상단에서 좌측 하단으로 선을 그을 때 접촉하는 외각선 개수 2개" << endl;
        cout << "1, 2, 6, 9, 0 중 하나입니다." << endl;
        identify_number[0][2] = 1;
        identify_number[1][2] = 1;
        identify_number[2][2] = 1;
        identify_number[6][2] = 1;
        identify_number[9][2] = 1;
    }
    else if (num_labels == 3) {
        //3, 5, 6, 8
        cout << "우측 상단에서 좌측 하단으로 선을 그을 때 접촉하는 외각선 개수 3개" << endl;
        cout << "3, 5, 6, 8 중 하나입니다." << endl;
        identify_number[3][2] = 1;
        identify_number[5][2] = 1;
        identify_number[6][2] = 1;
        identify_number[8][2] = 1;
    }
    else {
        //3, 8
        cout << "우측 상단에서 좌측 하단으로 선을 그을 때 접촉하는 외각선 개수 4개 이상" << endl;
        cout << "해당 특성에 대한 수는 8입니다." << endl;
        identify_number[8][2] = 1;
        identify_number[3][2] = 1;
    }
}
//4번 우측 상단 시작점에서 좌측 하단 끝나는 종료점까지 선을 그어 만나는 외각선 개수 판별 - stop
void lu_2_rd(Mat img) {
    Mat tmp_img = img.clone();
    Mat line_img(Size(img.cols, img.rows), CV_8UC3, Scalar(0, 0, 0));
    tmp_img /= 2;
    line(line_img, Point(0, 0), Point(tmp_img.cols - 100, tmp_img.rows), Scalar(200, 200, 200), 3);
    cvtColor(line_img, line_img, COLOR_BGR2GRAY);
    addWeighted(tmp_img, 1, line_img, 1, 0, tmp_img);
    threshold(tmp_img, tmp_img, 250, 255, THRESH_BINARY);
    Mat labels, stats, centroids;
    int num_labels = connectedComponentsWithStats(tmp_img, labels, stats, centroids);
    num_labels -= 1;
    //imshow("tmp_img", tmp_img);
    //waitKey();
    if (num_labels == 1) {
        //1, 3
        cout << "좌측 상단에서 우측 하단으로 선을 그을 때 접촉하는 외각선 개수 1개" << endl;
        cout << "1, 7, 4 중 하나입니다." << endl;
        identify_number[1][3] = 1;
        identify_number[4][3] = 1;
        identify_number[7][3] = 1;
    }
    else if (num_labels == 2) {
        //2, 3, 7, 0
        cout << "좌측 상단에서 우측 하단으로 선을 그을 때 접촉하는 외각선 개수 2개" << endl;
        cout << "2, 3, 9, 0 중 하나입니다." << endl;
        identify_number[0][3] = 1;
        identify_number[2][3] = 1;
        identify_number[3][3] = 1;
        identify_number[7][3] = 1;
        identify_number[9][3] = 1;
    }
    else if (num_labels == 3) {
        //1, 2, 3, 4, 5, 6, 8, 9
        cout << "좌측 상단에서 우측 하단으로 선을 그을 때 접촉하는 외각선 개수 3개" << endl;
        cout << "1, 2, 3, 4, 5, 6, 8, 9 중 하나입니다." << endl;
        identify_number[1][3] = 1;
        identify_number[2][3] = 1;
        identify_number[3][3] = 1;
        identify_number[4][3] = 1;
        identify_number[5][3] = 1;
        identify_number[6][3] = 1;
        identify_number[8][3] = 1;
        identify_number[9][3] = 1;
    }
    else {
        //8, 5
        cout << "좌측 상단에서 우측 하단으로 선을 그을 때 접촉하는 외각선 개수 4개 이상" << endl;
        cout << "5, 8 중 하나입니다." << endl;
        identify_number[5][3] = 1;
        identify_number[8][3] = 1;
    }
}
//5번 우측 영역(세로로 직사각형)제거하고 생기는 외각선 개수 판별 - stop
void erase_rArea(Mat img) {
    Mat erase_area = img.clone(), lables;
    erase_area(Rect(150, 0, 100, 500)) = Scalar(0, 0, 0);
    int count = connectedComponents(erase_area, lables);
    count -= 1; //배경 제거
    if (count == 1) {
        cout << "우측 영역 제거시 생기는 외각선 개수 1개" << endl;
        cout << endl << "1, 4, 6, 7, 8, 9, 0 중 하나입니다." << endl;
        identify_number[0][4] = 1;
        identify_number[1][4] = 1;
        identify_number[4][4] = 1;
        identify_number[6][4] = 1;
        identify_number[7][4] = 1;
        identify_number[8][4] = 1;
        identify_number[9][4] = 1;
    }
    else if (count == 2) {
        cout << "우측 영역 제거시 생기는 외각선 개수 2개" << endl;
        cout << endl << "2, 4, 5, 7, 8 중에 하나입니다." << endl;
        identify_number[2][4] = 1;
        identify_number[4][4] = 1;
        identify_number[5][4] = 1;
        identify_number[7][4] = 1;
        identify_number[8][4] = 1;
    }
    else {
        cout << "우측 영역 제거시 생기는 외각선 개수 3개" << endl;
        cout << endl << "3 입니다" << endl;
        identify_number[3][4] = 1;
    }
}
//6번 특징

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
    rectangle(number, Rect(0, 0, 500, 500), Scalar(0, 0, 0), 1);
    return number;
}
//feature에 따라서 결과 도출 함수
int result_number() {
    int maxSum = 0;
    int maxRow = 0;
    for (int i = 0; i < rows; i++) {
        int identifySum = 0;
        for (int j = 0; j < cols; j++) {
            identifySum += identify_number[i][j];
        }
        if (identifySum >= maxSum) {
            maxSum = identifySum;
            maxRow = i;
        }
    }
    for (int i = 0; i < 10; i++) {
        cout << "숫자 " << i << " : ";
        for (int j = 0; j < 5; j++) {
            cout << identify_number[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            identify_number[i][j] = 0;
        }
    }
    return maxRow;
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
            Mat preimg = PretreatmentImg((*(Mat*)userdata)(Rect(2, 2, 497, 497)).clone());
            contours_size(preimg);
            weight_contours(preimg);
            ru_2_ld(preimg);
            lu_2_rd(preimg);
            erase_rArea(preimg);
            int identify_number = result_number();
            cout << endl << "해당 숫자는 " << identify_number << "일 가능성이 가장 높습니다." << endl;
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
        else if (Point(x, y).inside(Rect(feature1))) {
            //feature1
            Mat preimg = PretreatmentImg((*(Mat*)userdata)(Rect(2, 2, 497, 497)).clone());
            contours_size(preimg);
        }
        else if (Point(x, y).inside(Rect(feature2))) {
            //feature2
            Mat preimg = PretreatmentImg((*(Mat*)userdata)(Rect(2, 2, 497, 497)).clone());
            weight_contours(preimg);
        }
        else if (Point(x, y).inside(Rect(feature3))) {
            //feature3
            Mat preimg = PretreatmentImg((*(Mat*)userdata)(Rect(2, 2, 497, 497)).clone());
            ru_2_ld(preimg);
        }
        else if (Point(x, y).inside(Rect(feature4))) {
            //feature4
            Mat preimg = PretreatmentImg((*(Mat*)userdata)(Rect(2, 2, 497, 497)).clone());
            lu_2_rd(preimg);
        }
        else if (Point(x, y).inside(Rect(feature5))) {
            //feature5
            Mat preimg = PretreatmentImg((*(Mat*)userdata)(Rect(2, 2, 497, 497)).clone());
            erase_rArea(preimg);
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
