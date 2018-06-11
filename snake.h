#ifndef _SNAKE_H_
#define _SNAKE_H_

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<assert.h>
#include<time.h>

#define FOOD "■"
#define ROW_X  24
#define COL_Y  10


typedef struct Node
{
	int _X;
	int _Y;
	struct Node* _next;

}SnakeNode;

enum Direction
{
	UP = 1,
	DOWN ,
	LEFT ,
	RIGHT,
	Esc//退出

};
enum Status
{
	KILL_BY_SELF,//自己把自己撞死
	KILL_BY_WALL,//撞墙死掉
	LIVE,//活着
	ESC,//退出
};

typedef struct Snake
{
	SnakeNode* _pSnake;//蛇头
	SnakeNode* _pFood;//食物
	enum Status _Status;//蛇的状态
	enum Direction _Dir;//蛇的行走方向
	int _SleepTime;//蛇每走一步停留的时间
	int _Grade;//分数

}Snake;

void SetPos(int x,int y);//设置光标位置
void DrawMap(void);//打印外框
void InitSnake(Snake* s);//初始化蛇
void CreatFood(Snake* s);//初始化食物
void SnakeMove(Snake*s);//蛇移动前的准备
void SnakeRun(Snake* s);//蛇移动
int KILLStatus(Snake* s);

#endif//_SNAKE_H_


