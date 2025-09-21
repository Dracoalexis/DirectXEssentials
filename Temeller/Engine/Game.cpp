/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	r = 255;
	g = 255;
	b = 255;

	crosshair = wnd.kbd.KeyIsPressed(VK_SHIFT);

	//UP
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		if(inhibitUp) {
		}
		else {
			vy -= 1;
			inhibitUp = true;
		}
	}
	else {
		inhibitUp = false;
	}
	//Left
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		if (inhibitLeft) {
		}
		else {
			vx -= 1;
			inhibitLeft = true;
		}
	}
	else {
		inhibitLeft = false;
	}
	//Down
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		if (inhibitDown) {
		}
		else {
			vy += 1;
			inhibitDown = true;
		}
	}
	else {
		inhibitDown = false;
	}
	//Right
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		if (inhibitRight) {
		}
		else {
			vx += 1;
			inhibitRight = true;
		}
	}
	else {
		inhibitRight = false;
	}
	//Renk deðiþtirme
	if (wnd.kbd.KeyIsPressed(VK_CONTROL)) {
		g -= 255;
		b -= 255;
	}
	//Space ile hýzý sýfýra eþitle
	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		vx = 0;
		vy = 0;
	}
	x += vx; 
	y += vy;
	//Þeklin ekranýn sýnýrlarýný aþmamasý için if statement larý:
	//Sað kenar:
	if (x + 7 > gfx.ScreenWidth) {
		x = gfx.ScreenWidth - 7;
		vx = -vx;
	}
	//Sol kenar:
	if (x - 8 < 0) {
		x = 8;
		vx = -vx;
	}
	//Üst kenar:
	if (y - 8 < 0) {
		y = 8;
		vy = -vy;
	}
	//Alt kenar:
	if (y + 7 > gfx.ScreenHeight) {
		y = gfx.ScreenHeight - 7;
		vy = -vy;
	}
	//Hedef crosshair ýn koordinatlarýnýn içine girdiðinde rengi deðiþsin:
	if ((x + 7 >= enemy_x - 7 && x - 6 <= enemy_x + 6) && 
		(y + 7 >= enemy_y - 7 && y - 6 <= enemy_y + 6)) {
		vx = -vx;
		vy = -vy;	
	}
	//Hedef kare koordinatlarýna geldiðinde yönü deðiþsin
	if ((x + 7 >= square_x - 100 && x - 6 <= square_x + 100) &&
		(y + 7 >= square_y - 100 && y - 6 <= square_y + 100)) {
		vx = -vx;
		vy = -vy;
	}
}

void Game::ComposeFrame()
{
	// Sol üst köþe
	gfx.PutPixel(-7 + x, -7 + y, r, g, b);
	gfx.PutPixel(-7 + x, -6 + y, r, g, b);
	gfx.PutPixel(-7 + x, -5 + y, r, g, b);
	gfx.PutPixel(-6 + x, -7 + y, r, g, b);
	gfx.PutPixel(-5 + x, -7 + y, r, g, b);

	//Sað üst köþe
	gfx.PutPixel(6 + x, -7 + y, r, g, b);
	gfx.PutPixel(5 + x, -7 + y, r, g, b);
	gfx.PutPixel(4 + x, -7 + y, r, g, b);
	gfx.PutPixel(6 + x, -6 + y, r, g, b);
	gfx.PutPixel(6 + x, -5 + y, r, g, b);

	//Sað alt köþe
	gfx.PutPixel(6 + x, 6 + y, r, g, b);
	gfx.PutPixel(5 + x, 6 + y, r, g, b);
	gfx.PutPixel(4 + x, 6 + y, r, g, b);
	gfx.PutPixel(6 + x, 5 + y, r, g, b);
	gfx.PutPixel(6 + x, 4 + y, r, g, b);

	//Sol alt köþe
	gfx.PutPixel(-6 + x, 6 + y, r, g, b);
	gfx.PutPixel(-6 + x, 5 + y, r, g, b);
	gfx.PutPixel(-6 + x, 4 + y, r, g, b);
	gfx.PutPixel(-5 + x, 6 + y, r, g, b);
	gfx.PutPixel(-4 + x, 6 + y, r, g, b);

	//Hedef crosshair konumu
	// Sol üst köþe
	gfx.PutPixel(-7 + enemy_x, -7 + enemy_y, 0, 255, 0);
	gfx.PutPixel(-7 + enemy_x, -6 + enemy_y, 0, 255, 0);
	gfx.PutPixel(-7 + enemy_x, -5 + enemy_y, 0, 255, 0);
	gfx.PutPixel(-6 + enemy_x, -7 + enemy_y, 0, 255, 0);
	gfx.PutPixel(-5 + enemy_x, -7 + enemy_y, 0, 255, 0);

	//Sað üst köþe
	gfx.PutPixel(6 + enemy_x, -7 + enemy_y, 0, 255, 0);
	gfx.PutPixel(5 + enemy_x, -7 + enemy_y, 0, 255, 0);
	gfx.PutPixel(4 + enemy_x, -7 + enemy_y, 0, 255, 0);
	gfx.PutPixel(6 + enemy_x, -6 + enemy_y, 0, 255, 0);
	gfx.PutPixel(6 + enemy_x, -5 + enemy_y, 0, 255, 0);

	//Sað alt köþe
	gfx.PutPixel(6 + enemy_x, 6 + enemy_y, 0, 255, 0);
	gfx.PutPixel(5 + enemy_x, 6 + enemy_y, 0, 255, 0);
	gfx.PutPixel(4 + enemy_x, 6 + enemy_y, 0, 255, 0);
	gfx.PutPixel(6 + enemy_x, 5 + enemy_y, 0, 255, 0);
	gfx.PutPixel(6 + enemy_x, 4 + enemy_y, 0, 255, 0);

	//Sol alt köþe
	gfx.PutPixel(-6 + enemy_x, 6 + enemy_y, 0, 255, 0);
	gfx.PutPixel(-6 + enemy_x, 5 + enemy_y, 0, 255, 0);
	gfx.PutPixel(-6 + enemy_x, 4 + enemy_y, 0, 255, 0);
	gfx.PutPixel(-5 + enemy_x, 6 + enemy_y, 0, 255, 0);
	gfx.PutPixel(-4 + enemy_x, 6 + enemy_y, 0, 255, 0);

	//Kare
	gfx.PutPixel(square_x, square_y, 255, 0, 0);
	//Üst Kenar
	for (int i = -100; i <= 100; i++) {
		gfx.PutPixel(i + square_x, -100 + square_y, 255, 0, 0);
	}
	//Sol kenar
	for (int i = -99; i <= 100; i++) {
		gfx.PutPixel(-100 + square_x, i + square_y, 255, 0, 0);
	}
	//Sað kenar
	for (int i = -99; i <= 100; i++) {
		gfx.PutPixel(100 + square_x, i + square_y, 255, 0, 0);
	}
	//Alt Kenar
	for (int i = -99; i <= 99; i++) {
		gfx.PutPixel(i + square_x, 100 + square_y, 255, 0, 0);
	}
}
