# number_recognization

**이미지 전처리 관련 함수**

https://github.com/kCW-tb/number_recognization/blob/7e91ea707141c4eb9d0e42fd00720907c46f29ac/main.cpp#L112-L147

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

https://github.com/kCW-tb/number_recognization/blob/7e91ea707141c4eb9d0e42fd00720907c46f29ac/main.cpp#L149-L223

1번 특징은 이미지 자체에 있어 외각선의 개수이다.

2번 특징은 우측 영역의 픽셀값을 0로 만든 이후 남는 영역에 대해서 나오는 객체의 개수이다.

https://github.com/kCW-tb/number_recognization/blob/7e91ea707141c4eb9d0e42fd00720907c46f29ac/main.cpp#L283-L420

3번 특징으로 여러개의 이미지를 학습시키고 이에 대한 값을 저장한 이후 새로운 데이터가 들어오면 이전에 학습되어 있는 데이터를 기반으로 새로운 데이터의 숫자에 대해 추측한다.
이미지가 많아지고 영역을 세밀하게 조정할수록 정확도를 올릴 수 있다.
현 프로젝트는 숫자당 60개 총 600개의 숫자 이미지를 학습 데이터로 사용하였다.
4와 같은 숫자의 경우 내부 외각선이 존재하는 필기체와 없는 필기체가 있는데 4-1, 4-2처럼 따로 학습시켜 높은 정확도를 가지도록 몇가지 필기체를 추가하였다.

![특징에 대해](https://github.com/kCW-tb/number_recognization/assets/71691159/ebbe0ad0-c9fc-456c-a8f9-dffc12793fa6)

좌측이 여러개의 2의 숫자에 대해 데이터를 축척하여 2의 영역을 크게 잡아둔 영역을 표현하였고
우측은 test데이터가 들어갔을 때 얼마나 해당 영역에 들어가는지 영역을 넘어가는 픽셀이 존재하는지 확인하는 작업을 표현.

![image](https://github.com/kCW-tb/number_recognization/assets/71691159/4e5037ff-9d80-4bc6-bd01-e8c6bd74a71f)
![image](https://github.com/kCW-tb/number_recognization/assets/71691159/8b967004-99ba-40ed-b65d-cb7cc480b598)

학습 데이터로 사용한 숫자 데이터들 중 일부


https://github.com/kCW-tb/number_recognization/blob/7e91ea707141c4eb9d0e42fd00720907c46f29ac/main.cpp#L422-L523

마우스가 이동 혹은 이벤트 발생 시 작동하는 함수이며 해당 영역 내에 들어갔을 때 이미지를 변환시키거나 각 기능을 실행시킨다.


**최종 결과 영상**

[최종 작동 영상](https://youtu.be/UH-VKuOvG74)

[특징 출력과 결과 영상](https://www.youtube.com/watch?v=tEuhGJNG6go)
