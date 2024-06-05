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


**Run에 사용되는 함수들**

```
//1번 이미지 객체에 대해 외각선 개수 추출
int contours_size(Mat img) {
    vector<vector<int>> contours;
    findContours(img, contours, RETR_LIST, CHAIN_APPROX_NONE);
    return contours.size();
}
//2번 내부 외각선이 없으면 pass 내부 외각선이 있다면 전체 객체와 내부외각선 무게중심을 비교
bool weight_contours(Mat img) {
    vector<vector<int>> contours;
    findContours(img, contours, RETR_LIST, CHAIN_APPROX_NONE);
    
    //임시값 true 반환
    return true;
}
//3번 객체에 선을 그어 만나는 외각선 개수 판별
//4번 중앙 영역(가로로 직사각형)제거하고 생기는 외각선 개수 판별
```
