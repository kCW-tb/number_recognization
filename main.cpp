#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat save_black = imread("./Save_black.jpg");
Mat save_red = imread("./Save_red.jpg");
Mat load_black = imread("./Load_black.jpg");
Mat load_red = imread("./Load_red.jpg");
Mat clear_black = imread("./Clear_black.jpg");
Mat clear_red = imread("./Clear_red.jpg");
Mat run_black = imread("./Run_black.jpg");
Mat run_red = imread("./Run_red.jpg");
Mat exit_black = imread("./Exit_black.jpg");
Mat exit_red = imread("./Exit_red.jpg");
Mat feature1_black = imread("./Feature1_black.jpg");
Mat feature2_black = imread("./Feature2_black.jpg");
Mat feature3_black = imread("./Feature3_black.jpg");
Mat feature1_red = imread("./Feature1_red.jpg");
Mat feature2_red = imread("./Feature2_red.jpg");
Mat feature3_red = imread("./Feature3_red.jpg");

void copyimg(Mat& img, Rect area, Mat& copy);
Mat drawLineImg();
void turn_menu_color(Mat board);
Mat grayThres(Mat numberimg);
Mat get_numberArea(Mat origin_numberimg);
void sizerepair(Mat& preImg);
void contours_size(Mat img, bool main);
void erase_rArea(Mat img, bool main);
Mat prepairImg_toDNN(Mat img);
void plus_learning_number(Mat preImg, int i);
void studyNumberData();
void test_number_DNN(Mat img, bool main);


//mouse_event
void on_mouse(int event, int x, int y, int flags, void* userdata);

const int rows = 10;
const int cols = 3;
int identify_number[rows][cols] = { 0 };
Mat learning_number[13];


int main(void)
{
    for (int i = 0; i < 13; ++i) {
        learning_number[i] = Mat::zeros(400, 300, CV_8UC1);
    }
    Mat img = drawLineImg();
    char c;
    studyNumberData();
      
    namedWindow("NUMBER");
    while (true) {
        setMouseCallback("NUMBER", on_mouse, &img);
        imshow("NUMBER", img);
        c = waitKey(1);
        if (c == 27) break;
    }
    return 0;
}




//menu related functions
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
    rectangle(board, Rect(650, 0, 150, 100), Scalar(0, 0, 0), 2);       //feature1
    rectangle(board, Rect(650, 100, 150, 100), Scalar(0, 0, 0), 2);     //feature2
    rectangle(board, Rect(650, 200, 150, 100), Scalar(0, 0, 0), 2);     //feature3

    copyimg(board, Rect(500, 0, 150, 100), save_black);
    copyimg(board, Rect(500, 100, 150, 100), load_black);
    copyimg(board, Rect(500, 200, 150, 100), clear_black);
    copyimg(board, Rect(500, 300, 150, 100), run_black);
    copyimg(board, Rect(500, 400, 150, 100), exit_black);
    copyimg(board, Rect(650, 0, 150, 100), feature1_black);
    copyimg(board, Rect(650, 100, 150, 100), feature2_black);
    copyimg(board, Rect(650, 200, 150, 100), feature3_black);

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
}

//image preporcessing related functions
//1. GrayScale + Threshold
Mat grayThres(Mat numberimg) {
    cvtColor(numberimg, numberimg, COLOR_BGR2GRAY);
    threshold(numberimg, numberimg, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    return numberimg;
}
//2. Morphology
//3. Get number area
Mat get_numberArea(Mat preImg) {
    Mat labels, stats, centroids;
    int cnt = connectedComponentsWithStats(preImg, labels, stats, centroids);
    if (cnt > 2) {
        int largth = 7;
        while (true) {
            morphologyEx(preImg, preImg, MORPH_CLOSE, Mat(largth, largth, CV_8UC1));
            cnt = connectedComponentsWithStats(preImg, labels, stats, centroids);
            if (cnt <= 2) break;
            largth += 3;
        }
    }
    int* p = stats.ptr<int>(1);
    return preImg(Rect(p[0], p[1], p[2], p[3])).clone();
}
//4. Resize to standard size
void sizerepair(Mat& preImg) {
    resize(preImg, preImg, Size(250, 500));
}
//Preporcessing function
Mat PretreatmentImg(Mat origin_numberimg) {
    Mat preImg = grayThres(origin_numberimg);  
    morphologyEx(preImg, preImg, MORPH_CLOSE, Mat(10, 10, CV_8UC1));
    Mat numberImg = get_numberArea(preImg);  
    sizerepair(numberImg);
    return numberImg;
}

//feature related functions
//1.Contours size
void contours_size(Mat img, bool main) {
    vector<vector<Point>> contours;
    findContours(img, contours, RETR_LIST, CHAIN_APPROX_NONE);
    if(main == false) cout << "해당 숫자 객체에 대한 외각선 개수 : " << contours.size() << endl << endl;
    if (contours.size() == 1) {
        identify_number[1][0] = 1;
        identify_number[2][0] = 1;
        identify_number[3][0] = 1;
        identify_number[4][0] = 1;
        identify_number[5][0] = 1;
        identify_number[7][0] = 1;
        identify_number[6][0] = -1;
        identify_number[9][0] = -1;
        identify_number[8][0] = -1;
        identify_number[0][0] = -1;
    }
    else if (contours.size() == 2) {
        identify_number[4][0] = 1;
        identify_number[6][0] = 1;
        identify_number[9][0] = 1;
        identify_number[0][0] = 1;
        identify_number[7][0] = -1;
        identify_number[1][0] = -1;
    }
    else {
        identify_number[8][0] = 1;
        identify_number[1][0] = -1;
        identify_number[7][0] = -1;
    }
}
//2. Erase Area
void erase_rArea(Mat img, bool main) {
    Mat erase_area = img.clone(), erase_area_left = img.clone(), erase_area_right = img.clone(), lables;
    erase_area_left(Rect(100, 0, 150, 500)) = Scalar(0, 0, 0);
    erase_area(Rect(150, 0, 100, 500)) = Scalar(0, 0, 0);
    erase_area_right(Rect(200, 0, 50, 500)) = Scalar(0, 0, 0);
    int count = connectedComponents(erase_area, lables);
    int count_l = connectedComponents(erase_area_left, lables);
    int count_r = connectedComponents(erase_area_right, lables);
    count -= 1;
    count_l -= 1;
    if (count == 1 && count_l == 1) {
        if (main == false) cout << "우측 영역 제거시 생기는 외각선 개수 1개" << endl << endl;
        identify_number[1][1] = 1;
        identify_number[4][1] = 1;
        identify_number[6][1] = 1;
        identify_number[7][1] = 1;
        identify_number[8][1] = 1;
        identify_number[9][1] = 1;
        identify_number[0][1] = 1;
        identify_number[3][1] = -1;
        identify_number[5][1] = -1;
    }
    else if (count_l == 2) {
        if (main == false) cout << "우측 영역 제거시 생기는 외각선 개수 2개" << endl << endl;
        identify_number[2][1] = 1;
        identify_number[1][1] = 1;
        identify_number[4][1] = 1;
        identify_number[5][1] = 1;
        if(identify_number[7][1] == 1 && count_r == 2) identify_number[7][1] = 1;
        identify_number[8][1] = 1;
        identify_number[6][1] = -1;
        identify_number[9][1] = -1;
    }
    else if (count == 3) {
        if (main == false) cout << "우측 영역 제거시 생기는 외각선 개수 3개" << endl << endl;
        identify_number[3][1] = 1;
        identify_number[2][1] = -1;
        identify_number[4][1] = -1;
        identify_number[5][1] = -1;
        identify_number[8][1] = -1;
    }
}


//mouse event related functions
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

//Get result about identify number
int result_number(bool main) {
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
        if (main == false) {
            cout << "숫자 " << i << " : ";
            for (int j = 0; j < cols; j++) {
                cout << identify_number[i][j] << " ";
            }
            cout << endl;
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            identify_number[i][j] = 0;
        }
    }
    return maxRow;
}

//Preporcessing learning related functions
Mat prepairImg_toDNN(Mat img) {
    cvtColor(img, img, COLOR_BGR2GRAY);
    threshold(img, img, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    Mat labels, stats, centorids;
    Rect all_img;
    int cnt = connectedComponentsWithStats(img, labels, stats, centorids);
    int* p = stats.ptr<int>(1);
    if (cnt == 2) {
        Mat tmp = img(Rect(p[0], p[1], p[2], p[3]));
        if (p[2] < 40) {
            Mat tmp_small(400, 300, CV_8UC1, Scalar(0, 0, 0));
            line(tmp_small, Point(150, 0), Point(150, 399), Scalar(255, 255, 255), 5);
            return tmp_small;
        }
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
        if ((max_y - min_y) / (double)(max_x - min_x) > 2.5) {
            min_x = max(min_x - 75, 0); max_x = min(max_x + 75, 300);
        }
        all_img = Rect(Point(min_x, min_y), Point(max_x, max_y));
    }

    Mat tmp = img(all_img);
    resize(tmp, tmp, Size(300, 400));
    return tmp;
}
void studyNumberData() {
    for (int i = 0; i < 13; i++) {
        string fileName = "./all_num_data/";
        if (i < 10) {
            fileName += "0";
            fileName += to_string(i);
        }
        else fileName += to_string(i);
        for (int j = 1; j <= 60; j++) {
            string number_name = "";
            if (j < 10) number_name += ("-0" + to_string(j));
            else number_name += ("-" + to_string(j));
            number_name += ".png";
            string final_path = fileName + number_name;
            Mat img = imread(final_path);
            if (img.empty()) { cout << "image is empty pls check filename : " << final_path; }
            Mat preImg = prepairImg_toDNN(img);
            plus_learning_number(preImg, i);
        }
    }
    learning_number[2](Rect(180, 40, 60, 200)) = 40;
    learning_number[2](Rect(180, 320, 30, 40)) = 0; 
    for (int i = 0; i < 13; i++) {  
        threshold(learning_number[i], learning_number[i], 30, 255, THRESH_BINARY);
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
            if (cnt >= 2) learning_number[i](rec) += 1;
        }
    }
}
void test_number_DNN(Mat img, bool main) {
    int identify_number_D[13] = { 0, };
    int index_num[2] = { 0,0 };
    int row = 40;
    int col = 30;
    int count = 0;
    Mat labels, preImg;
    preImg = prepairImg_toDNN(img);
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            Rect rec(x * col, y * row, col, row);
            int cnt = connectedComponents(preImg(rec), labels);
            for (int k = 0; k < 13; k++) {
                int ex_cnt = connectedComponents(learning_number[k](rec), labels);
                if (ex_cnt >= 2 && cnt >= 2) identify_number_D[k] += 2;      
                else if (ex_cnt >= 2 && cnt < 2) identify_number_D[k] -= 1;  
                else if (ex_cnt < 2 && cnt >= 2) identify_number_D[k] -= 2; 
            }
        }
    }

    int largest_index = -1;
    int second_largest_index = -1;
    int largest = INT_MIN;
    int second_largest = INT_MIN;

    for (int i = 0; i < 13; i++) {
        if (identify_number_D[i] > largest) {
            second_largest = largest;
            second_largest_index = largest_index;
            largest = identify_number_D[i];
            largest_index = i;
        }
        else if (identify_number_D[i] > second_largest) {
            second_largest = identify_number_D[i];
            second_largest_index = i;
        }
    }

    index_num[0] = largest_index;
    index_num[1] = second_largest_index;
    if (main == false) {
        for (int i = 0; i < 13; i++) {
            cout << i << " 숫자에 대한 점수 : " << identify_number_D[i] << endl;
        }
        cout << "가장 확률이 가까운 숫자 인덱스 2개  high : " << index_num[0] << ", sec high : " << index_num[1] << endl << endl;
    }
    if (index_num[0] == 10) index_num[0] = 4;
    else if (index_num[1] == 10) index_num[1] = 4;
    if (index_num[0] == 11) index_num[0] = 1;
    else if (index_num[1] == 11) index_num[1] = 1;
    if (index_num[0] == 12) index_num[0] = 2;
    else if (index_num[1] == 12) index_num[1] = 2;
    if (index_num[0] - index_num[1] < 5) {
        identify_number[index_num[0]][2] = 1;
    }
    else {
        identify_number[index_num[0]][2] = 1;
        identify_number[index_num[1]][2] = 1;
    }
}

void on_mouse(int event, int x, int y, int flags, void* userdata) {
    static Point prePoint = Point(0, 0);
    Rect save(500, 0, 148, 100), load(500, 100, 148, 100), clear(500, 200, 148, 100), run(500, 300, 148, 100), exit_f(500, 400, 148, 100);
    Rect feature1(650, 0, 148, 100), feature2(650, 100, 148, 100), feature3(650, 200, 148, 100);
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
    else {
        turn_menu_color(*(Mat*)userdata);
    }

    switch (event) {
    case EVENT_LBUTTONDOWN:
        prePoint = Point(x, y);
        if (Point(x, y).inside(Rect(500, 300, 150, 100))) {
            //Run
            Mat preimg = PretreatmentImg((*(Mat*)userdata)(Rect(2, 2, 497, 497)).clone());
            contours_size(preimg, true);
            erase_rArea(preimg, true);
            test_number_DNN((*(Mat*)userdata)(Rect(2, 2, 497, 497)), true);
            int identify_number = result_number(true);
            cout << endl << "해당 숫자는 '" << identify_number << "' 입니다." << endl;
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
            //Contours Size
            Mat preimg = PretreatmentImg((*(Mat*)userdata)(Rect(2, 2, 497, 497)).clone());
            contours_size(preimg, false);
        }
        else if (Point(x, y).inside(Rect(feature2))) {
            //Erase Area
            Mat preimg = PretreatmentImg((*(Mat*)userdata)(Rect(2, 2, 497, 497)).clone());
            erase_rArea(preimg, false);
        }
        else if (Point(x, y).inside(Rect(feature3))) {
            //Similarity
            test_number_DNN((*(Mat*)userdata)(Rect(2, 2, 497, 497)), false);
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
