#include"Snake.h"

namespace SnakeName
{
	//食物的成员函数实现
	Food::Food(Snake blackSnake)
	{
		produceFood(blackSnake);
	}
	void Food::produceFood(Snake blackSnake)
	{
		/*this->foodPosx = 10;
		this->foodPosy = 470;*/
		int count = 0;//合格的为0
		while (1)
		{//先产生一份食物
			srand((unsigned int)time(NULL));//随机数种子
			this->foodPosx = rand() % (Width / stepSize) * stepSize;//确保食物在蛇的路径上，
			this->foodPosy = rand() % (Height / stepSize) * stepSize;//将画面分割成stepSize*stepSize的格子
			//在检查食物是否合格
			for (int i = 0; i < blackSnake.length; i++)
			{
				if ((foodPosx == blackSnake.snakePosx[i])&&
					(foodPosy==blackSnake.snakePosy[i]))//食物在蛇身上，重新产生
				{
					count = 1;
					break;
				}
			}
			if (count == 1) continue;
			else break;

		}//
		foodStatus = true;
	}
	void Food::changeFoodStatus(Snake blacksnake)
	{
		if (!foodStatus)
		{
			this->produceFood(blacksnake);
		}
	}


	//蛇的成员函数实现
	Snake::Snake()
	{
		snakePosx.push_back(10);
		snakePosx.push_back(10);
		snakePosx.push_back(10);
		snakePosy.push_back(10);
		snakePosy.push_back(20);
		snakePosy.push_back(30);
		length = 3;
		snakeHead = up;
	}
	void Snake::moveFront()
	{
		//蛇身的移动
		for (int i = length-1; i >0 ; i--)
		{
			snakePosx[i] = snakePosx[i - 1];
			snakePosy[i] = snakePosy[i - 1];
		}
		//蛇头的移动
		switch (snakeHead)
		{
		case up:snakePosy[0] = (snakePosy[0]-stepSize+480)%480; break;
		case down:snakePosy[0] = (snakePosy[0]+stepSize)%480; break;
		case left:snakePosx[0] = (snakePosx[0] - stepSize+640)%640; break;
		case right:snakePosx[0] = (snakePosx[0] +stepSize)%640; break;
		default:break;
		}
	}
	void Snake::changeDirection()
	{
		char Ch;
		Ch = _getch();
		switch (Ch)
		{
		case up:if(snakeHead!=down) snakeHead=up;break;
		case down:if (snakeHead != up) snakeHead = down; break;
		case left:if (snakeHead != right) snakeHead = left; break;
		case right:if (snakeHead != left) snakeHead = right; break;
		default:break;
		}
	}
	void Snake::growUp()
	{
		snakePosx.push_back(snakePosx[length - 1]);
		snakePosy.push_back(snakePosy[length - 1]);
		length += 1;
	}
	void Snake::eat(Food &mouse)
	{
		if ((mouse.foodStatus)&&(mouse.foodPosx == snakePosx[0]) && (mouse.foodPosy == snakePosy[0]))
		{
			this->growUp();
			mouse.foodStatus = false;
		}
	}
	//Game 成员函数的实现
	 Game::Game()
	{
		 srand((unsigned int)time(NULL));//随机数种子
		 Snake _blackSnake;
		 Food _mouse(_blackSnake);
		 blackSnake = _blackSnake;
		 mouse = _mouse;
	}
	 void Game::gameStart()
	 {
		 initgraph(Width, Height);//绘图环境

		 outtextxy(Width / 2 - 30, Height / 2, _T("按空格键开始游戏"));
		 while (!_getch())
		 {
			 Sleep(0.001);
		 }
		 cleardevice();
		 outtextxy(Width / 2 - 5, Height / 2, _T("GameStart!"));
		 while (1)
		 {
			 //显示在屏幕的东西
			 DrawSnake();//画出蛇
			 DrawFood();//画出食物
				  //更新下一次用于显示的数据部分
			 blackSnake.moveFront();//蛇行动
			 blackSnake.eat(mouse);//吃食物
			 mouse.changeFoodStatus(blackSnake);//食物更新
			 Sleep(50);//游戏难度设置在于此
			 if (this->GameOver()) break;
			 while(_kbhit()) if(_getch())blackSnake.changeDirection();	//根据按键该边方向
			 
		 }
		 outtextxy(Width / 2 - 5, Height / 2, _T("GameOver!"));
		 wchar_t szW[200];
		 swprintf_s(szW, L"您的得分：%d", 100*(blackSnake.length-3));
		 outtextxy(Width / 2-5 , Height / 3, szW);
		 outtextxy(Width / 2 - 30, 2*(Height / 3), _T("按空格键退出游戏"));
		 Sleep(1000);
		 while (!_getch())
		 {
			 Sleep(0.01);
		 }

		 
	 }
	 void Game::DrawSnake()
	 {
		 cleardevice();
		 for (int i = 0; i < blackSnake.length; i++)//画蛇
		 {
			 setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
			 fillrectangle(blackSnake.snakePosx[i], blackSnake.snakePosy[i],
				 blackSnake.snakePosx[i] + sectionSize, blackSnake.snakePosy[i] + sectionSize);
		 }
	 }
	 void Game::DrawFood()
	 {
		 setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		 fillcircle(mouse.foodPosx + 5, mouse.foodPosy + 5, 5);//画食物
	 }
	 bool Game::GameOver()
	 {
		 for (int i = blackSnake.length - 1; i > 0; i--)
		 {
			if ((blackSnake.snakePosx[0]==blackSnake.snakePosx[i])&&
				(blackSnake.snakePosy[0]==blackSnake.snakePosy[i]))
			{
				return true;
			}
		 }
		 return false; 
	 }
}

