#include"Snake.h"

namespace SnakeName
{
	//ʳ��ĳ�Ա����ʵ��
	Food::Food(Snake blackSnake)
	{
		produceFood(blackSnake);
	}
	void Food::produceFood(Snake blackSnake)
	{
		/*this->foodPosx = 10;
		this->foodPosy = 470;*/
		int count = 0;//�ϸ��Ϊ0
		while (1)
		{//�Ȳ���һ��ʳ��
			srand((unsigned int)time(NULL));//���������
			this->foodPosx = rand() % (Width / stepSize) * stepSize;//ȷ��ʳ�����ߵ�·���ϣ�
			this->foodPosy = rand() % (Height / stepSize) * stepSize;//������ָ��stepSize*stepSize�ĸ���
			//�ڼ��ʳ���Ƿ�ϸ�
			for (int i = 0; i < blackSnake.length; i++)
			{
				if ((foodPosx == blackSnake.snakePosx[i])&&
					(foodPosy==blackSnake.snakePosy[i]))//ʳ���������ϣ����²���
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


	//�ߵĳ�Ա����ʵ��
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
		//������ƶ�
		for (int i = length-1; i >0 ; i--)
		{
			snakePosx[i] = snakePosx[i - 1];
			snakePosy[i] = snakePosy[i - 1];
		}
		//��ͷ���ƶ�
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
	//Game ��Ա������ʵ��
	 Game::Game()
	{
		 srand((unsigned int)time(NULL));//���������
		 Snake _blackSnake;
		 Food _mouse(_blackSnake);
		 blackSnake = _blackSnake;
		 mouse = _mouse;
	}
	 void Game::gameStart()
	 {
		 initgraph(Width, Height);//��ͼ����

		 outtextxy(Width / 2 - 30, Height / 2, _T("���ո����ʼ��Ϸ"));
		 while (!_getch())
		 {
			 Sleep(0.001);
		 }
		 cleardevice();
		 outtextxy(Width / 2 - 5, Height / 2, _T("GameStart!"));
		 while (1)
		 {
			 //��ʾ����Ļ�Ķ���
			 DrawSnake();//������
			 DrawFood();//����ʳ��
				  //������һ��������ʾ�����ݲ���
			 blackSnake.moveFront();//���ж�
			 blackSnake.eat(mouse);//��ʳ��
			 mouse.changeFoodStatus(blackSnake);//ʳ�����
			 Sleep(50);//��Ϸ�Ѷ��������ڴ�
			 if (this->GameOver()) break;
			 while(_kbhit()) if(_getch())blackSnake.changeDirection();	//���ݰ����ñ߷���
			 
		 }
		 outtextxy(Width / 2 - 5, Height / 2, _T("GameOver!"));
		 wchar_t szW[200];
		 swprintf_s(szW, L"���ĵ÷֣�%d", 100*(blackSnake.length-3));
		 outtextxy(Width / 2-5 , Height / 3, szW);
		 outtextxy(Width / 2 - 30, 2*(Height / 3), _T("���ո���˳���Ϸ"));
		 Sleep(1000);
		 while (!_getch())
		 {
			 Sleep(0.01);
		 }

		 
	 }
	 void Game::DrawSnake()
	 {
		 cleardevice();
		 for (int i = 0; i < blackSnake.length; i++)//����
		 {
			 setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
			 fillrectangle(blackSnake.snakePosx[i], blackSnake.snakePosy[i],
				 blackSnake.snakePosx[i] + sectionSize, blackSnake.snakePosy[i] + sectionSize);
		 }
	 }
	 void Game::DrawFood()
	 {
		 setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		 fillcircle(mouse.foodPosx + 5, mouse.foodPosy + 5, 5);//��ʳ��
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

