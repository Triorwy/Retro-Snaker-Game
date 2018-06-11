#include"snake.h"

void Menu(void)
{
	//system("mode con cols = 100 lines = 30");
	SetPos(30, 9);
	printf("**************************\n");
	SetPos(30, 10);
	printf("*  欢迎来到贪吃蛇小游戏  *\n");
	SetPos(30, 11);
	printf("* ↑↓← →控制移动方向  *\n");
	SetPos(30, 12);
	printf("*     开始游戏:Enter     *\n");
	SetPos(30, 13);
	printf("**************************\n");
	getchar();
	system("cls");
}
//void Menu2()
//{
//
//
//
//}
void SnakeGame(void)
{
	Snake s;
	memset(&s, 0, sizeof(Snake));
	srand((unsigned int)time(NULL));
	system("mode con cols = 100 lines = 30");
	DrawMap();//打印贪吃蛇框
	InitSnake(&s);//初始化
	CreatFood(&s);//产生食物
	SnakeMove(&s);//移动
	SnakeRun(&s);
}
int main(void)
{
	Menu();
	SnakeGame();
	getchar();
	system("pause");
	return 0;

}
