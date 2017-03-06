#pragma once

struct Coordinates
{
public:
	int x;
	int y;
};

class ThePlane
{
public:
	ThePlane();
	Coordinates coordinates;
	char image;
	void Move(int H,int V);
private:

};

ThePlane::ThePlane()
{
	coordinates.x = 5;
	coordinates.y = 5;
	image = 206;
}
void ThePlane :: Move(int V,int H)
{
	coordinates.x = coordinates.x + V;
	coordinates.y = coordinates.y + H;

}
