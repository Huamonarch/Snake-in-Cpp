#pragma once
#ifndef _SNAKE_H_
#define _SNAKE_H_
#include<vector>
#include<graphics.h>
#include<conio.h>
#include<ctime>
#include<iostream>

/*
1.食物
2.蛇
3.游戏
*/
namespace SnakeName
{
	using std::vector;//用装蛇的坐标
	using std::cout;
	using std::endl;
	enum snakeDirection { up = 72, down = 80, left = 75, right = 77 };//蛇头的方向控制
	const int stepSize = 10;//蛇每次移动的步长
	const int sectionSize = 10;//蛇的每一节长度
	const int Width = 640;
	const int Height = 480;
	class Snake;
	struct Food
	{
		Food(Snake);
		Food() {};//默认构造函数
		void produceFood(Snake);
		void changeFoodStatus(Snake);
		
		int foodPosx;//食物坐标
		int foodPosy;//食物坐标
		bool foodStatus;//食物状态（true 可以吃；false  不能吃（已经被吃了） ）
	};
	class Snake
	{
	public:
		Snake();
		void moveFront();
		void changeDirection();
		void growUp();
		void eat(Food&);
		int length;
		vector<int> snakePosx;
		vector<int> snakePosy;
		snakeDirection snakeHead;
	};//蛇 这个类

	class Game
	{
	public:
		Game();//构造函数
		void gameStart();
		Snake blackSnake;
		Food mouse;
		void DrawSnake();
		void DrawFood();
		
		bool GameOver();
	};// Game 这个类
}


#endif // !_SNAKE_H_

