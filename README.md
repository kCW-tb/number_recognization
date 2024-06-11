# number_recognization

**이미지 전처리 관련 함수**

https://github.com/kCW-tb/number_recognization/blob/6695c7893b0920aac93de38534265fa0b1b99b43/main.cpp#L116-L153

1. 이미지 전처리 단계로 GrayScale 및 이진화를 진행해준다
2. 모폴로지 연산을 통해 미약한 거리를 연결시킨다
3. 숫자 객체의 영상을 가져오지만 객체가 여러개인 경우 모폴로지 연산을 반복하여 연결시킨 뒤 가져온다.
4. 크기를 숫자의 일반적 크기의 비율로 조정한다.

[작동 영상](https://youtu.be/G28ypY8kamA)

Run이 작동되는 원리
```
const int rows = 10;
const int cols = 3;
int identify_number[rows][cols] = { 0 };
```
해당 코드는 rows가 숫자를 나타내는 클래스로 0~9까지의 숫자를 뜻하며 cols는 특징으로 늘이거나 줄임이 가능함.
1번 특성이 각 숫자에 대해 적합하다면 해당 배열값으로 1을 부여하고 해당 특성이 나타날 수 없는 숫자에 대해서는 -1를 해주어 우선 순위에서 제거
이후 각 열에 대해 해당 숫자를 합하여 최대 값을 가지는 숫자로 출력

![image](https://github.com/kCW-tb/number_recognization/assets/71691159/e3070154-b90b-42e8-a878-869424237a09)



**Run에 사용되는 함수들**

https://github.com/kCW-tb/number_recognization/blob/6695c7893b0920aac93de38534265fa0b1b99b43/main.cpp#L155-L214

1번 특징은 이미지 자체에 있어 외각선의 개수이다.
2번 특징은 우측 영역의 픽셀값을 0로 만든 이후 남는 영역에 대해서 나오는 객체의 개수이다.

https://github.com/kCW-tb/number_recognization/blob/6695c7893b0920aac93de38534265fa0b1b99b43/main.cpp#L272-L395

3번 특징이고 여러개의 이미지를 학습시키고 이에 대한 값을 저장한 이후 새로운 데이터가 들어오면 이전에 학습되어 있는 데이터를 기반으로 새로운 데이터의 숫자에 대해 추측한다.
이미지가 많아지고 영역을 세밀하게 조정할수록 정확도를 올릴 수 있다.

![특징에 대해](https://github.com/kCW-tb/number_recognization/assets/71691159/ebbe0ad0-c9fc-456c-a8f9-dffc12793fa6)

좌측이 여러개의 2의 숫자에 대해 데이터를 축척하여 2의 영역을 크게 잡아둔 영역을 표현하였고
우측은 test데이터가 들어갔을 때 얼마나 해당 영역에 들어가는지 영역을 넘어가는 픽셀이 존재하는지 확인하는 작업을 표현.

https://github.com/kCW-tb/number_recognization/blob/6695c7893b0920aac93de38534265fa0b1b99b43/main.cpp#L397-L498

마우스가 이동 혹은 이벤트 발생 시 작동하는 함수이며 해당 영역 내에 들어갔을 때 이미지를 변환시키거나 각 기능을 실행시킨다.


**최종 결과 영상**

[최종 작동 영상](https://www.youtube.com/watch?v=KwxDLTu-fVY)
