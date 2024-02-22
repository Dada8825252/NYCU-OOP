#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)
using namespace std;
#include <SDL.h> // Using SDL
#include <SDL2_gfxPrimitives.h> // Using SDL2_gfx
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include <time.h>
#include "RenderWindow.h"
#include "System.h"
#include "Jump.h"
#include "Platform.h"
#include "Image.h"
#include "StaticRole.h"
#include "AnimeRole.h"
#include "Text.h"
#include "SDL_ttf.h"
#include "constants.h"
#include "Planet.h"
#include "Triangle.h"
#include "button.h"
#include "Mixer.h"
#include "Image2.h"
#include "RotatingCoin.h"
#include "ThreeD.h"
#include "Energy.h"
bool once = false;
bool addforonce = false;

int main(int argc, char* args[])
{
	srand(time(NULL)); //算金幣出現的機率
	System sdl;

	bool quit = false; //Main loop flag

	// Start up SDL and create window
	if (!sdl.init())
	{
		printf("Failed to initialize SDL system!\n");
		return -1;
	}

	RenderWindow window("OOP SDL Tutorial", 20, 20, WIDTH, HEIGHT);
	SDL_RendererFlip no = SDL_FLIP_NONE;
	Mixer bgm("../audio/b.wav", MUSIC);
	Mixer m1("../audio/p.wav", EFFECT);
	Mixer fail("../audio/fail.wav", EFFECT);
	Mixer shoot("../audio/shooting.wav", EFFECT);
	button sbutton("../images/startbutton/",1, window.getRenderer());
	button rsbutton("../images/restartbutton/", 1, window.getRenderer());
	button buybutton("../images/buy_button/", 1, window.getRenderer(), 255, 255, 255);
	AnimeRole startbackground("../images/startbackground/", 1,window.getRenderer());
	AnimeRole overpenguin("../images/over_penguin/", 1, window.getRenderer());
	StaticRole background("../images/NBackGround.png", window.getRenderer());
	StaticRole cloud("../images/cloud.png", window.getRenderer());
	StaticRole cloud01("../images/cloud.png", window.getRenderer());
	StaticRole StaticCoin("../images/coin.png", window.getRenderer());
	Platform platform1("../images/platform1/", 1, window.getRenderer());
	Platform platform2("../images/platform2/", 1, window.getRenderer());
	//Jump penguin("../images/penguin_move/", 2, window.getRenderer());
	Planet sun("../images/sun/", 1, window.getRenderer(), 200, 200, 650, 170, 70);
	Planet moon("../images/moon/", 1, window.getRenderer(), 100, 100, 720, 0, 120);
	Planet star1("../images/star/", 1, window.getRenderer(), 200, 200, 800,120);
	Planet star2("../images/star/", 1, window.getRenderer(), 200, 200, 220, 120);
	Planet star3("../images/star/", 1, window.getRenderer(), 200, 200, 240, 180);
	Planet star4("../images/star/", 1, window.getRenderer(), 200, 200, 750, 180);
	Planet star5("../images/star/", 1, window.getRenderer(), 200, 200, 273, 160);
	Planet star6("../images/star/", 1, window.getRenderer(), 200, 200, 634, 120);
	Planet star7("../images/star/", 1, window.getRenderer(), 200, 200, 325, 150);   
	Planet star8("../images/star/", 1, window.getRenderer(), 200, 200, 350, 50);
	Planet star9("../images/star/", 1, window.getRenderer(), 200, 200, 530, 30);
	Planet star10("../images/star/", 1, window.getRenderer(), 200, 200, 480, 110);
	Planet star11("../images/star/", 1, window.getRenderer(), 200, 200, 100, 40);
	Planet star12("../images/star/", 1, window.getRenderer(), 200, 200, 530, 30);
	Planet star13("../images/star/", 1, window.getRenderer(), 200, 200, 680, 130);
	Planet star14("../images/star/", 1, window.getRenderer(), 200, 200, 140, 70);
	Planet star15("../images/star/", 1, window.getRenderer(), 200, 200, 550, 200);
	Planet star16("../images/star/", 1, window.getRenderer(), 200, 200, 820, 170);
	Planet star17("../images/star/", 1, window.getRenderer(), 200, 200, 750, 190);
	Planet star18("../images/star/", 1, window.getRenderer(), 200, 200, 850, 50);

	RotatingCoin coin("../images/rotating_coin.png", 16, 4, 4, window.getRenderer());
	
	Text points("0", "../fonts/lazy.ttf", 60, TTF_STYLE_BOLD, { 0, 105, 148 }, BLENDED,
		{ 100, 100, 100 }, window.getRenderer(), { 40, 500 }, { NULL, NULL }, NULL, no, 100);
	Text gameover("GAME OVER", "../fonts/lazy.ttf", 60, TTF_STYLE_BOLD, { 0, 105, 148 }, BLENDED,
		{ 100, 100, 100 }, window.getRenderer(), { 30, 300 }, { NULL, NULL }, NULL, no, 0);
	Text BestRecord("Best Record:", "../fonts/lazy.ttf", 30, TTF_STYLE_BOLD, { 220, 220, 220 }, BLENDED,
		{ 100, 100, 100 }, window.getRenderer(), { 40, 400 }, { NULL, NULL }, NULL, no, 0);
	Text Record("0", "../fonts/lazy.ttf", 30, TTF_STYLE_BOLD, {220,220,220 }, BLENDED,
		{ 100, 100, 100 }, window.getRenderer(), { 40, 450 }, { NULL, NULL }, NULL, no, 100);
	Text money("0", "../fonts/lazy.ttf", 60, TTF_STYLE_BOLD, { 0, 105, 148 }, BLENDED,
		{ 100, 100, 100 }, window.getRenderer(), { 730, 10 }, { NULL, NULL }, NULL, no, 100);

	Triangle t("../model/Low_poly_penguin.txt", window.getRenderer());
	double a[8][3] = { {1,1,0},{1,-1,0},{-1,-1,0},{-1,1,0} ,{-1,1,-1},{1,1,-1},{1,-1,-1},{-1,-1,-1} };
	ThreeD plat(a);

	FILE *fb;
	if ((fb = fopen("BestRecord.dat", "w+b")) == NULL) {
		printf("Cannot open file. \n");
	}
	Energy e1(WIDTH - 50, 250, 40, 10);
	Energy heart;
	heart.setlife(5);
	heart.setpath("../images/heart.png", window.getRenderer(), 255, 255, 255);
	for (int i = 0; i < heart.getlife(); i++) {
		heart.E[i].setposition(10 + i * 35, 10);
		heart.E[i].setdwh(30, 30);
		heart.E[i].setshown(true);
	}
	static bool* over = new bool[heart.getlife() + 1]{ false };
	static int i = 0;
	background.setPosition(WIDTH/2, HEIGHT/2, -M_PI/2.0);
	startbackground.setXspeed(5);
	startbackground.setdh(HEIGHT);
	startbackground.startTimer(50);
	window.startTimer(120);
	gameover.startTimer(50);
	
	plat.startTimer(50);

	sbutton.setPosition(WIDTH / 2 - 100, HEIGHT - 150);
	sbutton.setdwh(200, 100);
	sbutton.startTimer(50);
	
	rsbutton.setPosition(210, 380);
	rsbutton.setdwh(100, 100);
	buybutton.setPosition(WIDTH - 180, -10);
	buybutton.setdwh(75, 75);
	
	StaticCoin.setPosition(700, 10 );

	cloud.setPosition(WIDTH - 200, HEIGHT / 2 - 50 , -1, 1, 1);
	cloud.setcamD(0.5);
	cloud01.setPosition(WIDTH / 2, HEIGHT / 2 - 50, -1, 1, 1);
	cloud01.setcamD(0.25);
	/*
	penguin.setposition(0, 0, 0, M_PI / 4.0);
	penguin.setdistance(0);
	penguin.setvelocity(0, 0, 0);
	penguin.setpoints(0);
	//penguin.settargetposition(275);
	penguin.setdw(300);
	penguin.setdh(300);
//	penguin.setAlpha(255);
	penguin.startTimer(50);
	*/
	overpenguin.setdh(300);
	overpenguin.setdw(300);
	overpenguin.setPosition(WIDTH / 2 ,10);
	overpenguin.startTimer(50);

	sun.startTimer(80);
	moon.startTimer(80);
	sun.setAlpha(0);
	sun.setMove(false);
	moon.setMove(true);
	star1.startTimerStar(300);
	star2.startTimerStar(300);
	star3.startTimerStar(300);
	star4.startTimerStar(300);
	star5.startTimerStar(300);
	star6.startTimerStar(300);
	star7.startTimerStar(300);
	star8.startTimerStar(300);
	star9.startTimerStar(300);
	star10.startTimerStar(300);
	star11.startTimerStar(300);
	star12.startTimerStar(300);
	star13.startTimerStar(300);
	star14.startTimerStar(300);
	star15.startTimerStar(300);

	platform1.settargetposition(400);
	platform2.settargetposition(400);
	platform1.setposition(0, platstarty, platupz);
	platform2.setposition(0, platform2.gettargetpos(), platdownz);
	platform2.setEmerge(true);
	platform2.setAlpha(50);
	platform1.setvelocity(20, 10);
	platform2.setvelocity(20, 10);
	platform1.startTimer(70);
	platform2.startTimer(70);

	t.setposition(0, 0, 0, M_PI / 4.0);
	t.startTimer(70);
	t.startTimer2(70);

	coin.startTimer(100);

	SDL_Event e;
	bgm.play(FOREVER);
	//bool over = false;
	bool die = false;
	bool playFail = false;
	char* record;
	record = new char[3];
	strcpy(record, "0");
	rewind(fb);
	fwrite(&record, sizeof(record), 1, fb);
	//While application is running
	while (!quit)
	{
		
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			static Uint64 initialtime = SDL_GetTicks64();
			Uint64 endtime = 0;
			Uint64 currenttime = 0;

			

			//press start button
			int x, y;
			if (sbutton.getispressed() == false && die==false) { //最最一開始的畫面
				
				
				if (e.type == SDL_MOUSEBUTTONUP)
				{
					m1.playEffect(ONE, -1);
					// Get mouse position              
					SDL_GetMouseState(&x, &y);
					if (e.button.button == SDL_BUTTON_LEFT)
					{
						if (x > WIDTH / 2 - 100 && x < WIDTH / 2 + 200) {
							if (y > HEIGHT - 150 && y < HEIGHT - 50) {
								cout << "play effect" << endl;
								sbutton.setispressed(true);
								t.setstartgame(true);
								//rsbutton.setispressed(true);
							}
						}
					}
				}
				else if (startbackground.getbackgroundEnded() == true) {
					sbutton.setispressed(true);
					t.setstartgame(true);
				}
			}
			
			//over
			else if (die==true&&sbutton.getispressed() == false) {  
				cout << "searching..." << endl;
				//restart button
				if (e.type == SDL_MOUSEBUTTONUP)
				{
					m1.playEffect(ONE, -1);
					// Get mouse position
					SDL_GetMouseState(&x, &y);
					if (e.button.button == SDL_BUTTON_LEFT)
					{
						if (x > 210 && x < 310) {
							if (y > 380 && y < 480) {  //按restart
								//cout << "press restart" << endl;
								sbutton.setispressed(true);
								overpenguin.setover(false);
								overpenguin.setPosition(WIDTH / 2, 10);
								die = false;
								i = 0;
								for (int j = 1; j < 6; j++) {
									over[j] = false;
								}
								e1.setpower(10);
								points.setAlpha(255);
								t.setstartrotate(true);
								playFail = false;
								bgm.play(FOREVER);
								
							}
						}
					}
				}
			}
			//遊戲畫面
			else if( sbutton.getispressed()==true&&die==false ) { //start  || rsbutton.getispressed() == true
				//rsbutton.setispressed(false);
				
				// press buybutton to buy energy
				if (e.type == SDL_MOUSEBUTTONUP && !buybutton.getispressed()) {
					m1.playEffect(ONE, -1);
					// Get mouse position              
					SDL_GetMouseState(&x, &y);
					if (e.button.button == SDL_BUTTON_LEFT)
					{
						if (x >= WIDTH - 180 && x < WIDTH - 180 + 75) {
							if (y > -10 && y < 75 - 10) {
								cout << "play effect" << endl;
								buybutton.setispressed(true);
							}
						}
					}
				}
				if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						background.setspeed(5);
						cloud.setspeed(0.02);
						cloud01.setspeed(0.02);
						break;
					case SDLK_DOWN:
						background.setspeed(-5);
						cloud.setspeed(-0.02);
						cloud01.setspeed(-0.02);
						break;
					case SDLK_RIGHT:
						background.setwangle(1.0);
						break;
					case SDLK_LEFT:
						background.setwangle(-1.0);
						break;
					case SDLK_SPACE:
						initialtime = SDL_GetTicks64();
						t.setstartsqueeze(true);
						t.setvlift(15);
						t.setjumpflag(true);
						//penguin.setnewimage("../images/penguin_stand/", 5, window.getRenderer(), 1);
						//penguin.setvlift(15);
						//penguin.setjumpflag(true);
						break;
					case SDLK_q:
						//penguin.setflyback(-10);
						t.setflyback(-10);
						break;

					}
				}
				else if (e.type == SDL_KEYUP && e.key.repeat == 0)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						background.setspeed(0);
						cloud.setspeed(0);
						cloud01.setspeed(0);
						break;
					case SDLK_DOWN:
						background.setspeed(0);
						cloud.setspeed(0);
						cloud01.setspeed(0);
						break;
					case SDLK_RIGHT:
						background.setwangle(0);
						break;
					case SDLK_LEFT:
						//	cout << "in left\n";
						background.setwangle(0);
						break;
					case SDLK_SPACE:
						//	cout << "in keyup\n";
						once = true;
						addforonce = true;
						shoot.playEffect(ONE);
						endtime = SDL_GetTicks64();
						currenttime = endtime - initialtime;
						/*
						penguin.setnewimage("../images/penguin_jump/", 3, window.getRenderer(), 0);
						//	cout << currenttime << endl;
						penguin.setdistance((double)currenttime / 5.0);
						//cout << penguin.getdistance() << endl;
						penguin.setvelocity((double)currenttime / 50.0, 9.8);
						penguin.setnowposition(0);
						penguin.setwindvelocity(0);
						*/
						t.setdistance((double)currenttime / 5.0);
						t.setstartsqueeze(false);
						t.setvelocity((double)currenttime / 50.0, 9.8);
						t.setnowposition(0);
						t.setwindvelocity(0);

						e1.setpower(e1.getpower() - 1);
						break;

					}
				}
			}
			

		}
		
		
		bool overflag = true;
		bool arrived = false;

		if (t.gety() == t.getdistance() && t.getdistance()) {
			arrived = true;
			t.setjumpflag(false);
		}
		cout << "distance :" << t.getdistance() << " target :" << t.gettarget() << endl;
		if (arrived &&(t.getdistance() < t.gettarget() - 50 || t.getdistance() > t.gettarget() + 100))
		{
			over[i] = true;
			if (once) {
				i++;
				once = false;
			}
			cout << "GAME OVER\n";
			t.setfallflag(true);
		}
		for (int j = 1; j < 6; j++) {
			if (over[j]==0) {
				overflag = false;
			}
			heart.E[heart.getlife() - j].setshown(!over[j]);
			cout << over[j] << " ";
		}
		if (overflag == true) {
			die = true;
		}
		
	//	cout << penguin.gety() <<" "<< penguin.getdistance() << endl;
		bool add = false;
		bool addMoney = false;
		
		if (t.gety() == t.getdistance() && t.getdistance() && t.getdistance() >= t.gettarget() - 50 && t.getdistance() <= t.gettarget() + 100)//	cout << "arrived\n";
		{
			//penguin.setnewimage("../images/penguin_move/", 2, window.getRenderer(), 0);
			platform1.setButtomLeftMove(true);
			platform2.setButtomLeftMove(true);
			//penguin.setfallflag(false);

			t.setfallflag(false);
			
			if (addforonce) {
				add = 1;
				addforonce = false;
			}
			if (coin.getShow()) {
				addMoney = true;
				coin.setShow(false);
			}
			cloud.setspeed(0.002);
			cloud01.setspeed(0.002);
			// setting velocity
			platform1.setvelocity(15, 10);
			platform2.setvelocity(15, 10);
		}
		if (add)
		{
			points.addpoints();
			points.generateTexture();
			add = 0;
			cout << "in" << endl;
			
		}
		if (addMoney) {
			money.addpoints();
			money.generateTexture();
			addMoney = false;
			
		}

		if (die)
		{
			gameover.setAlpha(255);
			BestRecord.setAlpha(225);
			
			points.generateTexture();
			money.setString("0");
			money.generateTexture();
			//penguin.setnewimage("../images/penguin_move/", 2, window.getRenderer(), 0);
			t.setfallflag(true);
			overpenguin.setover(true);
			bgm.pause();
			
			sbutton.setispressed(false);
			if (playFail == false) {
				fail.playEffect(ONE);
				playFail = true;
			}
			rewind(fb);
			fread(&record, sizeof(record), 1, fb);

			cout << "compare: " << strcmp(record, points.getString()) << endl;
			if (strcmp(record, points.getString()) < 0) {  //points.getString is bigger  
				strcpy(record, points.getString());
			}
			Record.setString(record);
			Record.generateTexture();
			cout << "record: " << record << endl;
			cout << "Record string: " << Record.getString() << endl;
			rewind(fb);
			fwrite(&record, sizeof(record), 1, fb);
			points.setString("0");
			
			
		}
		
		if (window.getChangeLight() && sun.getMove()) { //該從白天轉黑夜
			window.setLight(NIGHT);
			sun.setAlpha(0);
			sun.setMove(false);
			sun.setposition(0, 650, 170);
			//moon.setAlpha(255);
			moon.setMove(true);
		}
		else if (window.getChangeLight() && moon.getMove()) { //該從黑夜轉白天
			window.setLight(DAY);
			moon.setAlpha(0);
			moon.setMove(false);
			moon.setposition(0, 720, 0);
			//sun.setAlpha(255);
			sun.setMove(true);
		}

		if (platform1.getswitchFlag() == true && platform2.getswitchFlag() == true)
		{
			platform1.setAlpha(50);
			Platform tmp;
			tmp = platform1;
			platform1 = platform2;
			platform2 = tmp;
			//cout << platform2.gety() << platform2.getz() << endl;
			platform2.setEmerge(true);
			platform1.setButtomLeftMove(false);
			platform2.setButtomLeftMove(false);
		//	cout << "exchanged\n";
			platform1.setswitchFlag(false);
			platform2.setswitchFlag(false);
			
			//計算下個平台是否出現金幣
			int r = rand() % 100;
			cout << "random number: " << r;
			if (r < 60) {
				coin.setShow(true);
			}
			else {
				coin.setShow(false);
			}

			cloud.setspeed(0);
			cloud01.setspeed(0);
		}
		background.moveWorldxy();
		background.moveWorlda();
		cloud.movefarnear();
		cloud01.movefarnear();

		window.clear();
		if (buybutton.getispressed()) {
			money.buysth();
			money.generateTexture();
			//cout << money.getmoney() << endl << endl;
						//if (money.getmoney() >= 3) {
			if (e1.getpower() <= 5)
				e1.setpower(e1.getpower() + 5);
			else
				e1.setpower(10);
			//	}
			buybutton.setispressed(false);
		}
	//	background.pseudo3D(window.getRenderer(), 20, 150, M_PI / 4.0);
		if (sbutton.getispressed() == false&&die==false) {
			startbackground.draw(window.getRenderer());
			sbutton.draw(window.getRenderer());
		}
		else if (overpenguin.getover()==true) {
			//cout << "over scene" << endl;
			overpenguin.draw(window.getRenderer());
			gameover.draw(window.getRenderer(), { WIDTH / 2-270, 100 }, { points.getWidth() / 2, points.getHeight() / 2 }, 0, no, gameover.getAlpha());
			BestRecord.draw(window.getRenderer(), {60, 250 }, { points.getWidth() / 3, points.getHeight() / 3 }, 0, no, gameover.getAlpha());
			Record.draw(window.getRenderer(), { 100, 300 }, { points.getWidth() / 3, points.getHeight() / 3 }, 0, no, gameover.getAlpha());
			rsbutton.draw(window.getRenderer());
		}
		else {
			coin.setPosition(0, platform2.gety()+110, platform2.getz()+30);
			background.draw(window.getRenderer());	
			StaticCoin.draw2(window.getRenderer());
			cloud.drawscene(window.getRenderer());
			cloud01.drawscene(window.getRenderer());
			sun.draw(window.getRenderer());
			moon.draw(window.getRenderer());
			star1.drawStar(window.getRenderer(),window.getStar());
			star2.drawStar(window.getRenderer(), window.getStar());
			star3.drawStar(window.getRenderer(), window.getStar());
			star4.drawStar(window.getRenderer(), window.getStar());
			star5.drawStar(window.getRenderer(), window.getStar());
			star6.drawStar(window.getRenderer(), window.getStar());
			star7.drawStar(window.getRenderer(), window.getStar());
			star8.drawStar(window.getRenderer(), window.getStar());
			star9.drawStar(window.getRenderer(), window.getStar());
			star10.drawStar(window.getRenderer(), window.getStar());
			star11.drawStar(window.getRenderer(), window.getStar());
			star12.drawStar(window.getRenderer(), window.getStar());
			star13.drawStar(window.getRenderer(), window.getStar());
			star14.drawStar(window.getRenderer(), window.getStar());
			star15.drawStar(window.getRenderer(), window.getStar());
			//plat.draw(window.getRenderer());
			points.draw(window.getRenderer(), { WIDTH / 2, 50 }, { points.getWidth() / 2, points.getHeight() / 2 }, 0, no, 255);
			money.draw2(window.getRenderer(), { 730,10 }, { money.getWidth() / 2, money.getHeight() / 2 }, 0, no, 255);
			platform1.draw(window.getRenderer());
			platform2.draw(window.getRenderer());
			coin.draw();
			//penguin.draw(window.getRenderer());
			gameover.draw(window.getRenderer(), { WIDTH/2-200, 100 }, { points.getWidth() / 2, points.getHeight() / 2 }, 0, no, gameover.getAlpha());
			e1.draw(window.getRenderer());
			t.draw(window.getRenderer());
			buybutton.draw(window.getRenderer());
			heart.draw(window.getRenderer());
		}
		
		
		window.display();

		
				
	}
	startbackground.close();
	sbutton.close();
	points.close();
	money.close();
	coin.close();
	background.close();
	//penguin.close();
	sun.close();
	moon.close();
	m1.close();
	shoot.close();
	bgm.close();
	fail.close();
	window.close();
	sdl.close();
	fclose(fb);
	
	return 0;
}