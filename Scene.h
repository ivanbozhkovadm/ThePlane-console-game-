#pragma once

const int HEIGHT= 20;
const int WIDTH = 100;

class Scene
{
public:
	char scene[HEIGHT][WIDTH];
	void initialize();
	void setPlane(ThePlane plane);
	void update();
private:
};

//set values for scene
void Scene::initialize()
{
	for (int i = 0; i <= HEIGHT; i++)
	{

		for (int j = 0; j <= WIDTH; j++)
		{
			if (j == 0 | i == 0)
			{
				scene[i][j] = 176;
			}
			else 
			{
				if (j == WIDTH | i == HEIGHT)
				{
					scene[i][j] = 176;
				}
				else
				{
					scene[i][j] = ' ';
				}
			}
		}
	}	

}

//Set coordinates for the bird
void Scene::setPlane(ThePlane bird) 
{
	scene[bird.coordinates.x][bird.coordinates.y] = bird.image;	
}


//Function that print the array with scene 
void Scene::update()
{
	
	for (int i = 0; i <= HEIGHT; i++)
	{
		for (int j = 0; j <= WIDTH; j++)
		{
			std::cout << scene[i][j];
		}
		std::cout << '\n';
	}
}

