# number_recognization

**이미지 전처리 관련 함수**
```
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
    return preImg(Rect(p[0], p[1], p[2], p[3]));
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
    sizerepair(numberImg);
    return numberImg;
}
```

[작동 영상](https://youtu.be/G28ypY8kamA)

특징을 구현하면서 기본 기반으로 생각한 조건
1. 기본적으로 각 특성을 적용 시킬 때의 출력이 있어야 함으로 어느 특정 숫자에서만 적용이 가능한 함수는 제작하지 않아야 함.
2. 각 특성에 대해 어느 하나의 특징으로만 결정되는것은 피해야 함.
3. 특징은 적을수록 좋으나 숫자를 구별해야 함.

Run이 작동되는 원리
```
const int rows = 10;
const int cols = 5;
int identify_number[rows][cols] = { 0 };
```
해당 코드는 rows가 숫자를 나타내는 클래스로 0~9까지의 숫자를 뜻하며 cols는 특징으로 늘이거나 줄임이 가능함.
1번 특성이 각 숫자에 대해 적합하다면 해당 배열값으로 1을 부여하고 해당 특성이 나타날 수 없는 숫자에 대해서는 -5를 해주어 우선 순위에서 제거
이후 각 열에 대해 해당 숫자를 합하여 최대 값을 가지는 숫자로 출력

![image](https://github.com/kCW-tb/number_recognization/assets/71691159/e3070154-b90b-42e8-a878-869424237a09)


**Run에 사용되는 함수들(미완)**

```
//1번 이미지 객체에 대해 외각선 개수 추출
void contours_size(Mat img) {
    vector<vector<Point>> contours;
    findContours(img, contours, RETR_LIST, CHAIN_APPROX_NONE);
    cout << "해당 숫자 객체에 대한 외각선 개수 : " << contours.size() << endl;
}
//2번 내부 외각선이 있다면 전체 객체와 내부외각선 무게중심을 비교 6,4,9판별을 위한 조건
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
            cout << endl << "해당 특성 결과는 8입니다." << endl;
        }
        else if (eight_zero == 3) {
            cout << endl << "해당 특성 결과는 0입니다." << endl;
        }
    }
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
            cout << "in_contours : " << in_contours.y << " out_contours : " << out_contours << endl;
            cout << "내부 외각선의 무게중심이 외부 외각선의 무게중심보다 높음" << endl;
            cout << endl << "4, 9, 0 중 하나입니다." << endl;
        }
        if (in_contours.y < out_contours.y) {
            cout << "in_contours : " << in_contours.y << " out_contours : " << out_contours << endl;
            cout << "내부 외각선의 무게중심이 외부 외각선의 무게중심보다 낮음" << endl;
            cout << endl << "6, 0 중 하나입니다." << endl;
        }
    }
    else {
        cout << "내부 외각선 0개 존재 " << endl;
        cout << endl << "1, 2, 3, 4, 5, 7 중 하나입니다." << endl;
    }
}
```
기본적 코드로 외각선의 개수와 내부 외각선이 존재할 경우 약간의 조건을 더해서 외각선의 개수를 구하는 방식을 사용함.


```
//3번 우측 상단 시작점에서 좌측 하단 끝나는 종료점까지 선을 그어 만나는 외각선 개수 판별
//4번 중앙 영역(가로로 직사각형)제거하고 생기는 외각선 개수 판별
void ru_2_ld(Mat img) {
    Mat tmp_img = img.clone();
    Mat line_img(Size(img.cols, img.rows), CV_8UC3, Scalar(0,0,0));
    tmp_img /= 2;
    line(line_img, Point(tmp_img.cols - 51, 0), Point(60, tmp_img.rows - 1), Scalar(150, 150, 150), 3);
    cvtColor(line_img, line_img, COLOR_BGR2GRAY);
    addWeighted(tmp_img, 1, line_img, 1, 0, tmp_img);
    threshold(tmp_img, tmp_img, 250, 255, THRESH_BINARY);
    Mat labels;
    int num_labels = connectedComponents(tmp_img, labels);
    num_labels -= 1; //배경 제거
}
```
해당 코드는 addWeighted를 사용한 기법으로 일반적으로 일정 영역에 대해 존재하는 외각선 또는 객체 개수를 찾는데 있어 대각선 영역은 처리를 못하지만 조금 돌아가 원본의 전체적 픽셀값을 낮추고 line의 픽셀값을 150정도로 하여 두 이미지가 겹치는 영역에 대하여 픽셀값이 250이상으로 올라가게 하여 이진화를 통해 해당 영역만 남긴 이후 connectedComponents로 객체 개수를 찾는 방법을 통해 자유롭게 영역을 지정하여 영역에 대한 외각선이나 객체 개수를 찾을 수 있게 함.

![image](https://github.com/kCW-tb/number_recognization/assets/71691159/9b11c592-e99d-491e-85a0-3cc01a086ea3)

우측 상단에서 좌측 하단으로 그려진 line에 대해 겹치는 객체 판별에 쓰인 이미지

```
//5번 우측 영역(세로로 직사각형)제거하고 생기는 외각선 개수 판별 - stop
void erase_rArea(Mat img) {
    Mat erase_area = img.clone(), lables;
    erase_area(Rect(150, 0, 100, 500)) = Scalar(0, 0, 0);
    int count = connectedComponents(erase_area, lables);
    count -= 1; //배경 제거
}
```
우측 영역의 픽셀값을 0로 만든 이후 남는 영역에 대해서 나오는 객체의 개수를 특성으로 지정함.

![image](https://github.com/kCW-tb/number_recognization/assets/71691159/84b21052-47c0-4367-9575-dad620d365af)

```
 RotatedRect rect = minAreaRect(contours);
 int eight_zero = contours_size(img(Rect(0, rect.center.y, img.cols, 1)));
 if (eight_zero == 2 || eight_zero == 1) return 8;
 else if(eight_zero == 3) return 0;
```
사진에 대해 1 pixel의 row값을 가진 사각형 영역에 대하여 외각선 검출을 하는 함수에 대한 예시



아직 특성이 충분치 않아 중복으로 모든 조건의 합이 5가 되는 경우가 존재 특성을 늘리거나 조정이 필요

[중간인식과정](https://youtu.be/wSoOFS5d_Bc)
