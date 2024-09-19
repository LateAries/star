#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
#define MAX_STAR 150
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 800
#define MAX_STEP 3
#define MAX_RADIUS 3
#define BOTTOM_MARGIN 150
//星星状态
enum STATUS {
	STOP = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	RANDOM,
	ALL_STATUS
};
struct STAR {
	int x; //星星的 x 坐标
	int y; //星星的 y 坐标
	enum STATUS stat; //状态
	unsigned radius; //星星的半径
	int step; //每次跳跃的间隔
	int color; //星星的颜色
};
struct STAR star[MAX_STAR];
/************************************
* 功能：初始化星星
* * 输入参数：
* i - 星星在全局数组中的下标
* 返回值：无
************************************/

//某个星星移动一次
inline void starMove(int i) {
	//移动效果的实现：遮挡原来的，移动一下，再画一个
	setfillcolor(BLACK);
	solidcircle(star[i].x, star[i].y, star[i].radius);

	setfillcolor(RGB(253, 122, 189));


	if (star[i].stat == UP) {
		star[i].y -= star[i].step;
		if (star[i].y < 0) {
			star[i].y = SCREEN_HEIGHT;
		}
	}
	else if (star[i].stat == DOWN) {
		star[i].y += star[i].step;

	}
	else if (star[i].stat == LEFT) {
		star[i].x -= star[i].step;

	}
	else if (star[i].stat == RIGHT) {
		star[i].x += star[i].step;

	}

	solidcircle(star[i].x, star[i].y, star[i].radius);
}

//判断星星是不是已经全部退出了屏幕
//需要逐个检索,只要有一个星星还在屏幕里，就直接返回false，继续下一次移动
bool isQuit() {
	for (int i = 0; i < MAX_STAR; i++) {
		if (star[i].x > 0 && star[i].x < SCREEN_WIDTH && star[i].y>0 &&
			star[i].y < SCREEN_HEIGHT) {
			return false;
		}
	}
	return true;
}

void initStar(int i) {
	int rgb = 0;
	if (i<0 || i>MAX_STAR) {
		fprintf(stderr, "老司机，你传的值 i[%d]我受不了！", i);

		return;
	}

	//rand() 得到随机数范围 0 - 32767 RAND_MAX
	star[i].x = rand() % SCREEN_WIDTH; // x 范围 0 -639
	star[i].y = rand() % (SCREEN_HEIGHT - BOTTOM_MARGIN);// y 范围 0 - 379
	//star[i].stat = (enum STATUS)(rand()%ALL_STATUS);
	star[i].stat = UP;
	star[i].radius = 1 + rand() % MAX_RADIUS; //半径控制 1 - 3
	star[i].step = rand() % MAX_STEP + 1; //步长 1 - 5
	rgb = 255 * star[i].step / MAX_STEP; // 0 - 255
	star[i].color = RGB(rgb, rgb, rgb);
}

int main() {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	srand(time(NULL));



	//初始化所有星星
	for (int i = 0; i < MAX_STAR; i++) {
		initStar(i);
	}
	//绘制出初始星星
	for (int i = 0; i < MAX_STAR; i++) {
		setfillcolor(star[i].color);
		solidcircle(star[i].x, star[i].y, star[i].radius);
	}
	//char name[500];
	//sprintf_s(name, sizeof(name), "陈佳，你是傻子吗？");
	//settextcolor(WHITE);
	//srand(time(NULL));
	//int x, y;
	//x = rand()% SCREEN_WIDTH;
	//y = rand()% SCREEN_HEIGHT;

	//outtextxy(x, y, name); 
	/*
	char name1[500];
	sprintf_s(name1, sizeof(name1), "陈佳，你是傻子吗？");
	settextcolor(WHITE);
	srand(time(NULL));
	x = rand() % SCREEN_WIDTH;
	y = rand() % SCREEN_HEIGHT;
	*/
	//outtextxy(x, y, name1);
	//音乐播放
	//mciSendString("play res\\萤火虫.mp3", 0, 0, 0);

	//实现星星移动
	while (1) {
		//需要优化：出了屏幕，就应该删掉这个星星，不然还要调用这个函数，就会大大影响效率
		for (int i = 0; i < MAX_STAR; i++) {
			starMove(i);
		}
		if (isQuit()) {
			break;
		}
		Sleep(50);
	}
	//IMAGE tortoise;//王八图片
	//loadimage(&tortoise, "tortoise.jpg", 30, 30, false);
	//putimage(SCREEN_WIDTH * 4 / 10 - 30, SCREEN_HEIGHT - 30, &tortoise);
	//putimage(SCREEN_WIDTH * 6 / 10, SCREEN_HEIGHT - 30, &tortoise);
	/*bool quit = false;
	while (quit==false) {
		for (int i = 0; i < MAX_STAR; i++) {
			starMove(i);

		}
		Sleep(50);
	}*/
	system("pause");
	closegraph();
	return 0;
}