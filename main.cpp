#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <iomanip>  
#include <fstream>
#include <time.h>

#include "ThePlane.h"
#include "Scene.h"
#include "Wall.h"


void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void clearScreen()
{
	HANDLE hOut; // Get the Win32 handle representing standard output.
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set cursor position
	Position.X = 0;
	Position.Y = 10;
	SetConsoleCursorPosition(hOut, Position); // Move the cursor back to the top left for the next sequence of writes
}

void writeResultInFile(char userName[20],int points)
{
	//set time
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	int hour = aTime->tm_hour;
	int minutes = aTime->tm_min;
	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
	int year = aTime->tm_year + 1900; // Year is # years since 1900

	std::ofstream resultsFile;
	resultsFile.open("RESULTS.txt", std::ofstream::out | std::ofstream::app);
	for (int i = 0; i < 50; i++)
	{
		resultsFile << '-';
	}
	resultsFile << std::endl;
	resultsFile << "USER: " << userName << " has: " << points << " POINTS at: "
		<< '[' << hour << "]:" << '[' << minutes << "]" << day << '/' << month << '/' << year;
	resultsFile << std::endl;
	for (int i = 0; i < 50; i++)
	{
		resultsFile << '-';
	}
	resultsFile << std::endl;
	resultsFile.close();

}

void printPlane()
{
	std::cout << "   @                @@@   " << "\n";
	std::cout << "  @@@@@@          @@@@@   " << "\n";
	std::cout << "  @@@@@          @@@@@@   " << "\n";
	std::cout << "  @@@@@@@@@@@@@@@@@@@@    " << "\n";
	std::cout << " @@@      @@@@@@@@@@@     " << "\n";
	std::cout << "             @@@@@@@@@@@@ " << "\n";
	std::cout << "            @@@@@@@@@@@@@@" << "\n";
	std::cout << "            @@@@@@@@      " << "\n";
	std::cout << "           @@@@@@         " << "\n";
	std::cout << "           @@@@@          " << "\n";
}

int checkWall(ThePlane b,Wall* w, Wall* w2,Wall* w3,int activity)
{
	if ((b.coordinates.x != w->getHolePosition()) && (b.coordinates.y == w->getPosition()))
	{
		system("cls");
		printPlane();
		std::cout << '\n';
		std::cout << std::setw(20) << "GameOver!" << '\n';
		return 0;
	}
	if ((b.coordinates.x != w2->getHolePosition()) && (b.coordinates.y == w2->getPosition()))
	{
		system("cls");
		printPlane();
		std::cout << '\n';
		std::cout << std::setw(20) << "GameOver!" << '\n';
		return 0;
	}
	if ((b.coordinates.x != w3->getHolePosition()) && (b.coordinates.y == w3->getPosition()))
	{
		system("cls");
		printPlane();
		std::cout << '\n';
		std::cout << std::setw(20) << "GameOver!" << '\n';
		return 0;
	}

}

int main()
{
	int activity = 1;
	
	
	system("COLOR F3");
	Scene s;
	ThePlane b;
	s.initialize();
	
	Wall* w = new Wall(&s, 5, 2, 30);
	Wall* w2 = new Wall(&s, 15, 2, 60);
	Wall* w3 = new Wall(&s, 10, 2, 90);
	int points = 0;
	char userName[20];
	int level = 100;
	std::cout << std::setw(20) << "...:::PLANE:::..." << std::endl;
	printPlane();
	std::cout << "USERNAME: ";
	
	std::cin >> userName;

	ShowConsoleCursor(false);
	system("cls");

	while (activity)
	{

		clearScreen();
		std::cout << std::setw(50)<< "...:::PLANE:::..." <<std::endl;
		s.initialize();
		s.setPlane(b);
		s.update();
		
		//set wall
		w->setWall();
		w2->setWall();
		w3->setWall();

		//move wall
		clearScreen();
		std::cout << std::endl;
		w->Move();
		w2->Move();
		w3->Move();

		s.update();

		//system("pause>nul");
		//event listeners
		if (GetAsyncKeyState(VK_UP))
		{
			if (b.coordinates.x == 1)
			{
				b.Move(0, 0);
			}
			else
			{
				b.Move(-1, 0); 
			}
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (b.coordinates.x == 19)
			{
				b.Move(0, 0); 
			}
			else
			{
				b.Move(1, 0);
			}
		}

		
		//check wall
		activity = checkWall(b, w,w2,w3,activity);
		if ((b.coordinates.x == 0) || (b.coordinates.x == 20))
		{
			if (GetAsyncKeyState(VK_UP))
			{
				b.Move(+1, 0);
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				b.Move(-1, 0);
			}
		}

		//Generate new wall
		if (b.coordinates.y - 1 == w->getPosition())
		{
			int hole = rand() % 18 + 2;
			w = new Wall(&s, hole, 2, 100);
			points++;
		}
		if (b.coordinates.y - 1 == w2->getPosition())
		{
			int hole = rand() % 18 + 2; ;
			w2 = new Wall(&s, hole, 2, 100);
			points++;
		}
		if (b.coordinates.y - 1 == w3->getPosition())
		{
			int hole = rand() % 18 + 2; ;
			w3 = new Wall(&s, hole, 2, 100);
			points++;
		}

		//print points info
		std::cout << "POINTS: "<<points << '\n';
		

		//Level
		Sleep(level);
	
		if (level > 0)
		{
			level--;
		}
		
	}

	writeResultInFile(userName, points);

	system("pause");
	return 0;
}