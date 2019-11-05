// HackerConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>

#include <cstdlib>

#include <random>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

class drawing
{
public:

	enum COLORS { BLACK, NAVY_BLUE, DARK_GREEN, TURQUOISE, RED, PURPLE, GOLD_YELLOW, SILVER, GREY, BLUE, GREEN, LIGHT_BLUE, LIGHT_RED, PINK, LIGHT_YELLOW, WHITE };
	enum TEXT_TYPE { BINARY, DECIMAL_, HEXADECIMAL, LETTER_AND_NUMBER };
	enum ANIMATION_TYPE { FALLINGSTAR, LINE };

	static void imlec_konumu(int x, int y) {
		static HANDLE h = NULL;
		if (!h)
			h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD c = { x, y };
		SetConsoleCursorPosition(h, c);
	}

	static void sayfayi_temizle(int x, int x2, int y, int y2) {
		int sayacx, sayacy;
		for (sayacx = x; sayacx < (x2 + 1); sayacx++)
		{
			for (sayacy = y; sayacy < (y2 + 1); sayacy++)
			{
				imlec_konumu(sayacx, sayacy); printf(" ");
			}
		}
	}

	static void dikeycizgi(int x, int s, int y) {
		do
		{
			imlec_konumu(x, y); printf("|"); y += 1; s -= 1;
		} while (s != 0);
	}

	static void yataycizgi(int y, int s, int x) {
		do
		{
			imlec_konumu(x, y); printf("-"); x += 1; s -= 1;
		} while (s != 0);
	}

	static void change_color(int color_Text, int color_Background)
	{
		int color = color_Background * 16 + color_Text;
		if (1 <= color && color <= 255)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
		}
	}

	template<typename T>
	static void fillVector(vector<int>& vec, T rndGen)
	{
		generate(begin(vec), end(vec), rndGen);
	}

	static void hacker_console(int height, int width, int first, int last, ANIMATION_TYPE animation_type)
	{
		vector<int> vector(height*width), vector_width(width), vector_height(height);

		random_device randomDevice, randomDevice_width, randomDevice_height;
		mt19937 engine(randomDevice()), engine_width(randomDevice_width()), engine_height(randomDevice_height());
		uniform_int_distribution<int> distributor(first, last), distributor_width(0, width), distributor_height(0, height);

		auto generator = std::bind(distributor, engine), generator_width = std::bind(distributor_width, engine_width), generator_height = std::bind(distributor_height, engine_height);

		fillVector(vector, generator);
		fillVector(vector_width, generator_width);
		fillVector(vector_height, generator_height);

		int x = 0;
		int y = 0;

		Sleep(5000); //Ýlk yazýmdan önce pencereyi karakter sýðacak þekilde büyüklüðe getir. Yoksa program hata verir.

		//Ekrana ilk yazým
		for (x = 0; x < width; x++)
		{
			for (y = 0; y < height; y++)
			{
				imlec_konumu(x, y);
				cout << vector[width*y + x];
			}
		}

		int transfer = 0;

		//Deðiþim
		
		if (animation_type == ANIMATION_TYPE::FALLINGSTAR)
		{
			int sx = 0, sy = 0;
			while (1)
			{
				transfer = vector[(width*vector_height[sy]) + vector_width[sx]];

				vector[(width*vector_height[sy]) + vector_width[sx]] = vector[width * sy + sx];
				vector[width * sy + sx] = transfer;

				//cout << "\n width = ";
				//cout << vector_width[x];
				//cout << " height =";
				//cout << vector_height[y];
				//Sleep(10);

				imlec_konumu((vector_width[sx]), vector_height[sy]);
				cout << vector[width * vector_height[sy] + vector_width[sx]];


				sx++;
				sy++;
				if (sx >= width - 1)
				{
					sx = 0;
					for (int fx = 0; fx < width - 1; fx++)
					{
						if (vector_width[fx] < width - 1)
						{
							vector_width[fx] += 1;
						}
						else
						{
							vector_width[fx] = 0;
						}
					}
				}

				if (sy >= height - 1)
				{
					sy = 0;
					for (int fy = 0; fy < height - 1; fy++)
					{
						if (vector_height[fy] < height - 1)
						{
							vector_height[fy] += 1;
						}
						else
						{
							vector_height[fy] = 0;
						}
					}
				}
			}
		}
		else if ((animation_type == ANIMATION_TYPE::LINE))
		{
			while (1)
			{
				for (x = 0; x < width; x++)
				{
					for (y = 0; y < height; y++)
					{

						transfer = vector[width*y + x];

						if ((width * y + x) < ((width * height) / 2))
						{
							vector[width * y + x] = vector[(width * y + x) + ((width * height) / 2)];
							vector[(width * y + x) + ((width * height) / 2)] = transfer;

							imlec_konumu((((width * y + x) + ((width * height) / 2)) % width), (((width * y + x) + ((width * height)) / 2) / width));
							cout << vector[(width * y + x) + ((width * height) / 2)];
						}
						else if ((width * y + x) < (width*height - 1))
						{
							vector[width * y + x] = vector[width * y + x + 1];
							vector[width * y + x + 1] = transfer;

							imlec_konumu(((width * y + x + 1) % width), (width * y + x + 1) / width);
							cout << vector[width * y + x + 1];
						}


						imlec_konumu(x, y);
						cout << vector[width*y + x];
					}
				}
			}
		}
	}
};

int main()
{

	drawing::change_color(drawing::COLORS::GREEN, drawing::COLORS::BLACK);
	drawing::hacker_console(64, 237, 0, 9, drawing::ANIMATION_TYPE::FALLINGSTAR);

	//BEKLEME KOMUTU
	int st = 0;
	cin >> st;

	return 0;
}