#pragma once
#ifndef _SNAKE_H_
#define _SNAKE_H_
#include<vector>
#include<graphics.h>
#include<conio.h>
#include<ctime>
#include<iostream>

/*
1.ʳ��
2.��
3.��Ϸ
*/
namespace SnakeName
{
	using std::vector;//��װ�ߵ�����
	using std::cout;
	using std::endl;
	enum snakeDirection { up = 72, down = 80, left = 75, right = 77 };//��ͷ�ķ������
	const int stepSize = 10;//��ÿ���ƶ��Ĳ���
	const int sectionSize = 10;//�ߵ�ÿһ�ڳ���
	const int Width = 640;
	const int Height = 480;
	class Snake;
	struct Food
	{
		Food(Snake);
		Food() {};//Ĭ�Ϲ��캯��
		void produceFood(Snake);
		void changeFoodStatus(Snake);
		
		int foodPosx;//ʳ������
		int foodPosy;//ʳ������
		bool foodStatus;//ʳ��״̬��true ���Գԣ�false  ���ܳԣ��Ѿ������ˣ� ��
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
	};//�� �����

	class Game
	{
	public:
		Game();//���캯��
		void gameStart();
		Snake blackSnake;
		Food mouse;
		void DrawSnake();
		void DrawFood();
		
		bool GameOver();
	};// Game �����
}


#endif // !_SNAKE_H_

