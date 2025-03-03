#include<iostream>
#include<easyx.h>//图形库
#include<vector>
#include<time.h>
using namespace std;


#define TITLE 100// 标题高度
#define GRID_W 100//格子宽高
#define GRID_H 150


vector<int>flag = { 3,0,1,2 };//每行黑块编号
bool isOver = false;//结束标志
int score = 0,startTime=0;//分数,时间


//初始化
void init() {
	for (int i = 0; i < flag.size(); i++) {
		flag[i] = rand() % 4;//黑块随机位置
	}
}


//游戏绘制
void draw() {
	settextcolor(BLACK);//标题颜色
	settextstyle(36, 0, "黑体");//字体大小，默认宽度，字体
	char title[100] = "别踩白块儿";
	sprintf(title, "别踩白块儿 %d %d",score, startTime ? (clock() - startTime) / 1000 : 0);//clock返回程序开始执行到结束的tick数
	//cout << " 别踩白块儿  分数: " << score << "游戏时长: " << startTime?(clock()-startTime)/1000:0;

	//字符串宽度获取 左侧边距
	int space = (getwidth() - textwidth(title)) / 2;
	outtextxy(space, 5, title);//标题居中

	//绘制格子
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
		for (int i = 0; i < 5; i++) {
			line(0, TITLE+i*GRID_H,400,TITLE+i*GRID_H);//起始点到终止点，横线
			line(i * GRID_W, 100, i * GRID_W, 700);//竖线
		}
	
	//绘制黑块
	setfillcolor(BLACK);
	for (int i = 0; i < 4; i++) {
		int x = flag[i]*GRID_W;
		int y = i * GRID_H + TITLE;//高度按次序绘制，宽度按编号绘制

		solidrectangle(x, y, x + GRID_W, y + GRID_H);//填色
	}
}


//处理鼠标点击
void mouseMessage(ExMessage* msg) {
	if (startTime == 0) {
		startTime = clock();
	}
	int x = flag[3] * GRID_W;
	int y = 3 * GRID_H + TITLE;//最下面一排
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
	srand(time(NULL));//随机数种子

	initgraph(400,700);//创建游戏窗口


	//初始化
	setbkcolor(WHITE);//背景白色
	cleardevice();//清屏
	init();//调用初始化
	BeginBatchDraw();	//防止卡顿，开启双缓冲绘图
	ExMessage em;//按键消息


	//游戏主要循环
	while (true) {
		//清屏，不然画面会重叠
		cleardevice();

		//游戏绘制
		draw();

		//游戏刷新
		FlushBatchDraw();


		//用户输入
		if (peekmessage(&em, EX_MOUSE)) {
			if(em.message==WM_LBUTTONDOWN){ //左键点击
				mouseMessage(&em);
			}
		}


		//游戏是否结束
		if (isOver) {
			MessageBox(GetHWnd(), "游戏结束", "提示", MB_OK);//弹出消息框,句柄类似于指针但貌似只能定位
			break;
		}

	}


	EndBatchDraw();	//关闭双缓冲绘图
	closegraph();	//关闭游戏窗口
	return 0;
}