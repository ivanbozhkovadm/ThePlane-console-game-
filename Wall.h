#pragma once

class Wall 
{
public:
	Wall(Scene* s, int holePosition, int holeSize, int position);
	~Wall();
	void Move();
	void setWall();
	
	int getPosition();
	int getHolePosition();
private:
	int holePosition;
	int holeSize;
	int position;
	Scene* s;
};

Wall::Wall(Scene* s,int holePosition, int holeSize, int position) 
	: s(s) ,holePosition(holePosition), holeSize(holeSize), position(position) {};

Wall::~Wall()
{
	std::cout << s << std::endl;
	delete s;
	std::cout << s << std::endl;
}

int Wall::getPosition()
{
	return position;
}

int Wall::getHolePosition()
{
	return holePosition;
}



void Wall::setWall()
{
	
	for (int i = 1; i < HEIGHT; i++)
	{
		if (i == holePosition)
		{
			s->scene[i][position] = ' ';
		}
		else 
		{
			s->scene[i][position] = 254;
		}
	}
	
}

void Wall::Move()
{
	if(position >= 0)
	{ 
		position--;
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (s->scene[i][j] == 254)
				{
					s->scene[i][j] == ' ';
					s->scene[i - 1][j - 1] == 254;
				}
			}
		}
	}
}

