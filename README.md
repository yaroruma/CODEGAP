# ESW 2020 자율주행 자동차

## Brief
2020 임베디드 소프트웨어 경진대회 CODEGAP 팀 결선 코드입니다. 주최측에서 제공된 모형자동차로 여러 미션을 수행하는 자율주행을 구현했습니다. 차선 및 정지선 인식, 기본적인 주행 코드를 담당했습니다.   
대회는 코로나-19 관계로 결선이 취소되어 결선 진출 팀 전원 특선상을 수상했습니다.   
결선 제출용 영상은 https://www.youtube.com/watch?v=gFrpFWd1hl0 이곳에서 볼 수 있습니다.

## Mission   
![mission](https://user-images.githubusercontent.com/72549957/144243402-75ec342d-69a1-46f2-a93c-93f4146443eb.PNG)
## `project.c`
각 미션을 수행하기 위해 판단 및 분기.
```c
static int fun_select(struct display *disp, struct buffer *cambuf, int n);
                            // 카메라에서 받아온 데이터를 가공 후 원하는 함수 선택하여 실행
int project(struct display *disp, struct buffer *cambuf, int mode, int green_num);
                            // 영상과 센서값들을 통해 조건을 판별하여 각각의 모드 실행
```

## `exam_cv.cpp`
requires - openCV2   
영상인식을 통한 미션, 모드별 동작 실행.
```cpp
int line_tracing(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf);
                            // OpenCV로 차선을 따라 라인트레이싱
                            // 나머지 미션은 코드 주석 참고
```

## Line tracing
![tracing](https://user-images.githubusercontent.com/72549957/144243392-b806e705-2de6-4657-add1-b8d0f60b2048.PNG)
