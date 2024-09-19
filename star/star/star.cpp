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
//����״̬
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
	int x; //���ǵ� x ����
	int y; //���ǵ� y ����
	enum STATUS stat; //״̬
	unsigned radius; //���ǵİ뾶
	int step; //ÿ����Ծ�ļ��
	int color; //���ǵ���ɫ
};
struct STAR star[MAX_STAR];
/************************************
* ���ܣ���ʼ������
* * ���������
* i - ������ȫ�������е��±�
* ����ֵ����
************************************/

//ĳ�������ƶ�һ��
inline void starMove(int i) {
	//�ƶ�Ч����ʵ�֣��ڵ�ԭ���ģ��ƶ�һ�£��ٻ�һ��
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

//�ж������ǲ����Ѿ�ȫ���˳�����Ļ
//��Ҫ�������,ֻҪ��һ�����ǻ�����Ļ���ֱ�ӷ���false��������һ���ƶ�
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
		fprintf(stderr, "��˾�����㴫��ֵ i[%d]���ܲ��ˣ�", i);

		return;
	}

	//rand() �õ��������Χ 0 - 32767 RAND_MAX
	star[i].x = rand() % SCREEN_WIDTH; // x ��Χ 0 -639
	star[i].y = rand() % (SCREEN_HEIGHT - BOTTOM_MARGIN);// y ��Χ 0 - 379
	//star[i].stat = (enum STATUS)(rand()%ALL_STATUS);
	star[i].stat = UP;
	star[i].radius = 1 + rand() % MAX_RADIUS; //�뾶���� 1 - 3
	star[i].step = rand() % MAX_STEP + 1; //���� 1 - 5
	rgb = 255 * star[i].step / MAX_STEP; // 0 - 255
	star[i].color = RGB(rgb, rgb, rgb);
}

int main() {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	srand(time(NULL));



	//��ʼ����������
	for (int i = 0; i < MAX_STAR; i++) {
		initStar(i);
	}
	//���Ƴ���ʼ����
	for (int i = 0; i < MAX_STAR; i++) {
		setfillcolor(star[i].color);
		solidcircle(star[i].x, star[i].y, star[i].radius);
	}
	//char name[500];
	//sprintf_s(name, sizeof(name), "�¼ѣ�����ɵ����");
	//settextcolor(WHITE);
	//srand(time(NULL));
	//int x, y;
	//x = rand()% SCREEN_WIDTH;
	//y = rand()% SCREEN_HEIGHT;

	//outtextxy(x, y, name); 
	/*
	char name1[500];
	sprintf_s(name1, sizeof(name1), "�¼ѣ�����ɵ����");
	settextcolor(WHITE);
	srand(time(NULL));
	x = rand() % SCREEN_WIDTH;
	y = rand() % SCREEN_HEIGHT;
	*/
	//outtextxy(x, y, name1);
	//���ֲ���
	//mciSendString("play res\\ө���.mp3", 0, 0, 0);

	//ʵ�������ƶ�
	while (1) {
		//��Ҫ�Ż���������Ļ����Ӧ��ɾ��������ǣ���Ȼ��Ҫ��������������ͻ���Ӱ��Ч��
		for (int i = 0; i < MAX_STAR; i++) {
			starMove(i);
		}
		if (isQuit()) {
			break;
		}
		Sleep(50);
	}
	//IMAGE tortoise;//����ͼƬ
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