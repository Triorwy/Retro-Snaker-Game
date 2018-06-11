#define  _CRT_SECURE_NO_WARNINGS 1
#include"snake.h"

void SetPos(int x,int y)//设置光标位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  pos = {0};
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle,pos);
}
void DrawMap(void)//打印背景框
{
	int i = 0;
	for(i=0;i < 78;i+=2)//上
	{
		SetPos(i,0);
		printf(FOOD);
	}
	for(i=0;i<78;i+=2)//下
	{
		SetPos(i,26);
		printf(FOOD);
	}
	for(i = 0;i < 26;i++)//左
	{
		SetPos(0,i);
		printf(FOOD);
	}
	for(i = 0;i <= 26;i++)//右
	{
		SetPos(58,i);
		printf(FOOD);	
	}	
	for (i = 0; i <= 26; i++)//显示信息栏
	{
		SetPos(78, i);
		printf(FOOD);
	}
	printf("\n");
}

void InitSnake(Snake* s)//初始化蛇
{
	SnakeNode* cur = (SnakeNode*)malloc(sizeof(SnakeNode));//蛇头
	assert(cur);
	memset(cur, 0, sizeof(SnakeNode));
	cur->_X = ROW_X;//蛇头的位置
	cur->_Y = COL_Y;
	cur->_next = NULL;
	for (int i = 1; i <= 4; i++)//初始化蛇长为5
	{
		s->_pSnake = (SnakeNode*)malloc(sizeof(SnakeNode));
		assert(s->_pSnake);
		s->_pSnake->_X = ROW_X + 2*i;
		s->_pSnake->_Y = COL_Y;
		s->_pSnake->_next = cur;
		cur = s->_pSnake;

	}
	while (cur)
	{
		SetPos(cur->_X, cur->_Y);
		printf(FOOD);
		cur = cur->_next;
	}
	s->_Dir = RIGHT;
	s->_SleepTime = 500;
	s->_Status = LIVE;
}
void CreatFood(Snake* s)//初始化食物
{
	SnakeNode* cur = NULL;
	SnakeNode* food = (SnakeNode*)malloc(sizeof(SnakeNode));
	assert(food);
begin:
	memset(food, 0, sizeof(SnakeNode));
	cur = s->_pSnake;
	do
	{
		food->_X = rand() % 55 + 2;
	} while (food->_X % 2 != 0);
	food->_Y = rand() % 25 + 1;
	while (cur)
	{
		if (cur->_X == food->_X&&cur->_Y == food->_Y)
		{
			goto begin;
		}
		cur = cur->_next;
	}
	s->_pFood = food;
	SetPos(food->_X, food->_Y);
	printf(FOOD);

}
void EatFood(Snake *s, SnakeNode* pNode)
{
	SnakeNode* cur = NULL;
	pNode->_next = s->_pSnake;
	s->_pSnake = pNode;

	cur = s->_pSnake;
	while (cur)
	{
		SetPos(cur->_X, cur->_Y);
		printf(FOOD);
		cur = cur->_next;
	}
	CreatFood(s);
}
void NoFood(Snake *s, SnakeNode* pNode)
{
	SnakeNode* cur = s->_pSnake;
	pNode->_next = cur;
	s->_pSnake = pNode;
	cur = s->_pSnake;

	while (cur->_next->_next)
	{
		SetPos(cur->_X, cur->_Y);
		printf(FOOD);
		cur = cur->_next;
	}
	SetPos(cur->_next->_X, cur->_next->_Y);
	printf("  ");
	free(cur->_next);
	cur->_next = NULL;
}
void SnakeMove(Snake*s)//蛇移动
{
	SnakeNode* pNode = (SnakeNode*)malloc(sizeof(SnakeNode));
	assert(pNode);
	memset(pNode, 0, sizeof(SnakeNode));
	pNode->_X = s->_pSnake->_X;
	pNode->_Y = s->_pSnake->_Y;
	switch (s->_Dir)
	{
	case UP:pNode->_Y--;
		break;
	case DOWN:pNode->_Y++;
		break;
	case LEFT:pNode->_X -= 2;
		break;
	case RIGHT:pNode->_X += 2;
		break;
	case Esc:return;
		break;
	default:
		break;
	}
	if (pNode->_X == s->_pFood->_X&&pNode->_Y == s->_pFood->_Y)//判断下一个位置有没有食物
	{
		EatFood(s, pNode);
		s->_Grade++;
	}
	else
	{
		NoFood(s, pNode);
	}
}
void SnakeRun(Snake* s)//蛇移动
{
	do
	{
		if (GetAsyncKeyState(VK_DOWN)&&s->_Dir!=UP)
		{
			s->_Dir = DOWN;
		}
		else if (GetAsyncKeyState(VK_UP) && s->_Dir != DOWN)
		{
			s->_Dir = UP;
		}
		else if (GetAsyncKeyState(VK_LEFT) && s->_Dir != RIGHT)
		{
			s->_Dir = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && s->_Dir != LEFT)
		{
			s->_Dir = RIGHT;
		}
		else if (GetAsyncKeyState(VK_ESCAPE) && s->_Dir != ESC)
		{
			s->_Dir = Esc;
		}
		SnakeMove(s);
		Sleep(s->_SleepTime);
		s->_Status = KILLStatus(s);//判断生死
	} while (s->_Status == LIVE);
	if (s->_Status == KILL_BY_SELF)
	{
		SetPos(62, 10);
		printf("你被自己撞死了\n");
	}
	else if (s->_Status == KILL_BY_WALL)
	{
		SetPos(65, 10);
		printf("你撞墙死了\n");
	}
	else
	{
		SetPos(65, 10);
		printf("退出游戏\n");
		return;
	}
}
int KILLStatus(Snake* s)//蛇的死亡状态
{
	if (s->_pSnake->_X == 0 || s->_pSnake->_X == 58 ||
		s->_pSnake->_Y == 0 || s->_pSnake->_Y == 26)//被强撞死
	{
		return KILL_BY_WALL;
	}
	else if (s->_Dir == Esc)
	{
		return ESC;
	}
	else 
	{
		SnakeNode* cur = s->_pSnake->_next;
		while (cur)
		{
			if (cur->_X == s->_pSnake->_X&&cur->_Y == s->_pSnake->_Y)
			{
				return KILL_BY_SELF;
			}
			cur = cur->_next;
		}
	}
	return LIVE;
}
