#include<iostream>
#include<easyx.h>//ͼ�ο�
#include<vector>
#include<time.h>
using namespace std;


#define TITLE 100// ����߶�
#define GRID_W 100//���ӿ��
#define GRID_H 150


vector<int>flag = { 3,0,1,2 };//ÿ�кڿ���
bool isOver = false;//������־
int score = 0,startTime=0;//����,ʱ��


//��ʼ��
void init() {
	for (int i = 0; i < flag.size(); i++) {
		flag[i] = rand() % 4;//�ڿ����λ��
	}
}


//��Ϸ����
void draw() {
	settextcolor(BLACK);//������ɫ
	settextstyle(36, 0, "����");//�����С��Ĭ�Ͽ�ȣ�����
	char title[100] = "��Ȱ׿��";
	sprintf(title, "��Ȱ׿�� %d %d",score, startTime ? (clock() - startTime) / 1000 : 0);//clock���س���ʼִ�е�������tick��
	//cout << " ��Ȱ׿��  ����: " << score << "��Ϸʱ��: " << startTime?(clock()-startTime)/1000:0;

	//�ַ�����Ȼ�ȡ ���߾�
	int space = (getwidth() - textwidth(title)) / 2;
	outtextxy(space, 5, title);//�������

	//���Ƹ���
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
		for (int i = 0; i < 5; i++) {
			line(0, TITLE+i*GRID_H,400,TITLE+i*GRID_H);//��ʼ�㵽��ֹ�㣬����
			line(i * GRID_W, 100, i * GRID_W, 700);//����
		}
	
	//���ƺڿ�
	setfillcolor(BLACK);
	for (int i = 0; i < 4; i++) {
		int x = flag[i]*GRID_W;
		int y = i * GRID_H + TITLE;//�߶Ȱ�������ƣ���Ȱ���Ż���

		solidrectangle(x, y, x + GRID_W, y + GRID_H);//��ɫ
	}
}


//���������
void mouseMessage(ExMessage* msg) {
	if (startTime == 0) {
		startTime = clock();
	}
	int x = flag[3] * GRID_W;
	int y = 3 * GRID_H + TITLE;//������һ��
	if (msg->x >= x && msg->x <= x + GRID_W&& msg->y >= y && msg->y <= y + GRID_H) {
		for (int i = 3; i > 0; i--) {
			flag[i] = flag[i - 1];
		}
		flag[0] = rand() % 4;
		score++;
	}
	else {
		isOver = true;
	}
}


int main() {
	srand(time(NULL));//���������

	initgraph(400,700);//������Ϸ����


	//��ʼ��
	setbkcolor(WHITE);//������ɫ
	cleardevice();//����
	init();//���ó�ʼ��
	BeginBatchDraw();	//��ֹ���٣�����˫�����ͼ
	ExMessage em;//������Ϣ


	//��Ϸ��Ҫѭ��
	while (true) {
		//��������Ȼ������ص�
		cleardevice();

		//��Ϸ����
		draw();

		//��Ϸˢ��
		FlushBatchDraw();


		//�û�����
		if (peekmessage(&em, EX_MOUSE)) {
			if(em.message==WM_LBUTTONDOWN){ //������
				mouseMessage(&em);
			}
		}


		//��Ϸ�Ƿ����
		if (isOver) {
			MessageBox(GetHWnd(), "��Ϸ����", "��ʾ", MB_OK);//������Ϣ��,���������ָ�뵫ò��ֻ�ܶ�λ
			break;
		}

	}


	EndBatchDraw();	//�ر�˫�����ͼ
	closegraph();	//�ر���Ϸ����
	return 0;
}