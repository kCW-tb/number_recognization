#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
//각 숫자에 대해 학습하기 위한 Mat 객체 배열
Mat learning_number[10];

Mat prepairImg(Mat img);
void plus_learning_number(Mat preImg, int i);
void test_number(Mat img);
void studyNumberData();

int main(void) {
    //배열의 모든 값을 모두 0으로 초기화.
    for (int i = 0; i < 10; i++) {
        learning_number[i] = Mat::zeros(400, 300, CV_8UC1);
    }
    studyNumberData();
    Mat test = imread("save.jpg");
    test_number(test);
    return 0;
}

//이미지 전처리
Mat prepairImg(Mat img) {
    cvtColor(img, img, COLOR_BGR2GRAY);
    threshold(img, img, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    Mat labels, stats, centorids;
    Rect all_img;
    int cnt = connectedComponentsWithStats(img, labels, stats, centorids);
    int* p = stats.ptr<int>(1);
    if (cnt == 2) {
        Mat tmp = img(Rect(p[0], p[1], p[2], p[3]));
        resize(tmp, tmp, Size(300, 400));
        return tmp;
    }
    else {
        int min_x, min_y, max_x, max_y;
        int* p = stats.ptr<int>(1);
        min_x = p[0]; min_y = p[1]; max_x = p[0] + p[2]; max_y = p[1] + p[3];
        for (int i = 2; i < cnt; i++) {
            int* p = stats.ptr<int>(i);
            min_x = min(min_x, p[0]);
            min_y = min(min_y, p[1]);
            max_x = max(max_x, p[0] + p[2]);
            max_y = max(max_y, p[1] + p[3]);
        }
        all_img = Rect(Point(min_x, min_y), Point(max_x, max_y));
    }
    Mat tmp = img(all_img);
    resize(tmp, tmp, Size(300, 400));
    return tmp;
}
void studyNumberData() {
    string fileName = "./all_num_data/";
    for (int i = 0; i < 10; i++) {
        if (i == 0) fileName += "0";
        fileName += to_string(i);
        for (int j = 1; j <= 60; j++) { //데이터 수 늘어나면 여기 60을 변경
            if (j < 10) fileName += ("-0" + to_string(j));
            else fileName += ("-" + to_string(j));

            fileName += ".png";

            Mat img = imread(fileName, IMREAD_GRAYSCALE);
            Mat preImg = prepairImg(img);
            plus_learning_number(preImg, i);
        }
    }
    for (int i = 0; i < 10; i++) {  //숫자 개당 60개이므로 35개 이상이면 해당 영역은 숫자의 영역으로 판단함.
        threshold(learning_number[i], learning_number[i], 35, 255, THRESH_BINARY);
    }
}
void plus_learning_number(Mat preImg, int i) {
    int row = 40;
    int col = 30;
    Mat labels;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            Rect rec(x * col, y * row, col, row);
            int cnt = connectedComponents(preImg(rec), labels);
            if(cnt >= 2) learning_number[i](rec) += 1;
        }
    }
}
void test_number(Mat img) {
    int identify_number[10] = { 0, };
    int row = 40;
    int col = 30;
    Mat labels, preImg;
    preImg = prepairImg(img);
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            Rect rec(x * col, y * row, col, row);
            int cnt = connectedComponents(preImg(rec), labels);
            
            for (int k = 0; k < 10; k++) {
                int ex_cnt = connectedComponents(learning_number[k](rec), labels);
                if (ex_cnt >= 2 && cnt >= 2) identify_number[k]++;
                else if (ex_cnt >= 2 && cnt < 2) identify_number[k]--;
            }
        }
    }
    int maxIndex = 0;
    int maxVal = identify_number[0];
    string large_val = "";
    for (int i = 1; i < 10; ++i) {
        if (identify_number[i] > maxVal) {
            maxVal = identify_number[i];
            maxIndex = i;
            large_val = "";
        }
        if (identify_number[i] == maxVal) {
            large_val += " ";
            large_val += to_string(i);
            large_val += " ";
        }
    }
    cout << "가장 확률이 가까운 숫자 " << maxIndex << large_val;
}
