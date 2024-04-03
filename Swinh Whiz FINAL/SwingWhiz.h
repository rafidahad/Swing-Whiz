#include "iGraphics.h"
#include <math.h>
#include<iostream>
using namespace std;

#define screenWidth 1366
#define screenHeight 786
#define AnchorNumber 4
#define CloudNumber 5
#define projectName "Swing Whiz"
#define FileDirectory "Assets/DATA/playData.txt"
const int MaxPlayerData=100;

FILE *playerInfo;
char name[100], savedName[MaxPlayerData][100];
int PlayerScore[MaxPlayerData];
int nameIndex = 0;
int background;
int gameBackground;
int enterName;
int credits;
int scoreBoard;
int cloud;
int star[2];
int button0[9], button1[9], button2[9];
int musicButton[3], sfxButton[3];
int characterIMG[4];
int buttonTimer = 0;
int buttonSelect;
int starTimer = 0;
int startGame;
int GameOver;
int clockTime = 0;
int health;
int heart;
int Score = 0;
int FullScoreBoard;
int totalPlayers;
int howToPlay;
int continueIMG;

const double GRAVITY = 0.1;
const double PI = 3.14159;

bool playGameOver = true;
bool startInitialized = false;
bool Sort = true;
bool scoreCount=false; 
bool viewAnchor = false;
bool randHook = false;
bool swingContineu = true;
bool swing = false;
bool fileWrite = false;
bool startlength = false;
bool gameOn = false;
bool swingAnimation = false;
bool buttonState = false;
bool buttonClick = false;
bool audio = true;
bool playing = true;
bool sfxAudio = true; 
bool playingS = false;
bool space = true;
bool gameStart = false;
bool backGroundChange = false;
bool timer = false;
bool animationInitialized = false;
bool staticSwing = true;
bool gameOver = false;
bool gameRestar = false;
bool hookInRange = false;
bool hookAttached = true;


double Time = 0;

typedef struct hookData{
	double hook_x;
	double hook_y;
	double hookIndex = 0;
	bool hookShow;
}HookInfo;
HookInfo anchor[AnchorNumber], clouds[CloudNumber];
typedef struct swingData{
	double angle =0;
	double angleV = 0;
	double angleA = 0;
	double length = 1;
}Data;
Data gameSwing, AnimationSwing;
typedef struct Coordinate{
	double x = 0, y = 0;
} axis;
axis character, hook, hook1, hook2, vel, button, BackgroundPosition, cloudPosition;
void hookRange(double x, double y);
void SortScore()
{
	fopen_s(&playerInfo, FileDirectory, "r");
	totalPlayers = 0;
	if (playerInfo != NULL)
	{
		while (fscanf_s(playerInfo, "%99s %d", savedName[totalPlayers], (unsigned)_countof(savedName[totalPlayers]), &PlayerScore[totalPlayers]) != EOF)
		{
			totalPlayers++;
		}

		fclose(playerInfo);

		for (int i = 0; i < totalPlayers - 1; i++)
		{
			for (int j = 0; j < totalPlayers - 1 - i; j++)
			{
				if (PlayerScore[j] < PlayerScore[j + 1])
				{
					int temp = PlayerScore[j];
					char tempC[100];
					strcpy_s(tempC, sizeof(tempC), savedName[j]);
					PlayerScore[j] = PlayerScore[j + 1];
					strcpy_s(savedName[j], sizeof(savedName[j]), savedName[j + 1]);
					PlayerScore[j + 1] = temp;
					strcpy_s(savedName[j + 1], sizeof(savedName[j + 1]), tempC);
				}
			}
		}

		fopen_s(&playerInfo, FileDirectory, "w");
		if (playerInfo != NULL)
		{
			for (int i = 0; i < totalPlayers; i++)
			{
				fprintf(playerInfo, "%s %d\n", savedName[i], PlayerScore[i]);
			}
			printf("File is updated\n");
			fclose(playerInfo);
		}
		else
		{
			std::cout << "Error opening file for writing!" << std::endl;
		}
	}
	else
	{
		std::cout << "Error opening file for reading!" << std::endl;
	}
	
	

}
void setAnchoreVariables()
{
	axis s, c;
	s.x = 250;
	s.y = 550;
	c.x = 280;
	c.y = 560;
	for (int i = 0; i < AnchorNumber; i++)
	{
		if (i == 0)
		{
			anchor[i].hook_x = s.x;
			anchor[i].hook_y = s.y;
		}
		else
		{
			anchor[i].hook_x = s.x + rand() % 50;
			anchor[i].hook_y = s.y + rand() % 200;
		}
		
		anchor[i].hookIndex = 0;
		anchor[i].hookShow = true;
		s.x += 700;

	}
	for (int i = 0; i < CloudNumber; i++)
	{
		clouds[i].hook_x = c.x + rand() % 80;
		clouds[i].hook_y = c.y + rand() % 150;
		clouds[i].hookIndex = 0;
		c.x += 500;

	}

}
axis findVelocity(double aV, double l, double a)
{
	axis Velocity;
	double velocity = aV*l / 2;
	Velocity.x = velocity*cos(a);
	Velocity.y = velocity*sin(a);

	return Velocity;

}
void playAudio(int n)
{
	if (audio)
	{
		if (n == 0 && playing)
		{
			PlaySound("Assets/Sound/background.wav", NULL, SND_LOOP | SND_ASYNC);

			playing = false;
		}
		else if (n == 1 && playing)
		{
			PlaySound("Assets/Sound/gameMusic.wav", NULL, SND_LOOP | SND_ASYNC);

			playing = false;;
		}
	}
	else
	{
		playing = true;
		PlaySound(0, 0, 0);
	}


}

void playSFX(int n)
{
	if (sfxAudio)
	{
		if (n == 0 && playGameOver)
		{
			PlaySound("Assets/Sound/gameOver.wav", NULL, SND_ASYNC);
			
			playGameOver = false;
		}
	}
	else
	{
		playGameOver = true;
		PlaySound(0, 0, 0);
	}


}

void continueScreen()
{
	iShowImage(0, 0, screenWidth, screenHeight, continueIMG);
	if (playGameOver)
	{
		playSFX(0);
		playGameOver = false;
		playing = true;
	}
}
void hooks(double x, double y)
{
	iSetColor(255, 255, 255);
	iFilledCircle(x, y, 7, 1000);
	iSetColor(0, 0, 0);
	iCircle(x, y, 15, 1000);
	hookRange(x, y);
	
}
void showAnchor()
{
	for (int i = 0; i < AnchorNumber; i++)
	{
		hooks(anchor[i].hook_x, anchor[i].hook_y);
		

	}
	for (int i= 0; i < CloudNumber; i++)
	{
		iShowImage(clouds[i].hook_x, clouds[i].hook_y, 100, 75, cloud);
	}

}

double findLength(double x1, double y1, double x2, double y2)
{
	double len = sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1) * (y2 - y1)));
	
	return len;
}
double findAngle(double x1, double y1, double x2, double y2)
{
	double angle = atan((x1 - x2) / (y2 - y1));
	return angle;
}
void constantSwing(double length, double angle)
{
	if (animationInitialized)
	{
		AnimationSwing.angle = angle;
		AnimationSwing.length = length;
		animationInitialized = false;
		staticSwing = false;

	}
	
}
void TimingPendulumn()
{
	
	
	if (gameStart)
	{
	
		if (swing)//Swing motion
		{

			hookInRange = false;
			double force = GRAVITY *sin(gameSwing.angle);

			gameSwing.angleA = (-1 * force) / gameSwing.length;
			gameSwing.angleV += gameSwing.angleA;


			if (gameSwing.angle != PI)
			{
				gameSwing.angle += gameSwing.angleV;
				if (gameSwing.angle > 2 * PI)
				{
					gameSwing.angle -= 2 * PI;
				}
				else if (gameSwing.angle < -2 * PI)
				{
					gameSwing.angle += 2 * PI;
				}
				character.x = gameSwing.length*sin(gameSwing.angle) + hook.x;
				character.y = hook.y - gameSwing.length *cos(gameSwing.angle);
				gameSwing.angleV *= .9995;

				vel = findVelocity(gameSwing.angleV, gameSwing.length, gameSwing.angle);
				
			}
			else
			{
				cout << "Swing Stopped" << endl;
				gameSwing.angleV = 0;
			}

			

		}
		else if (!swing)//projectil fall motion
		{

			
			Time = 2;
			character.x += vel.x*Time*2.2;
			double temp_y = vel.y*Time - .5*GRAVITY*Time*Time;
			character.y += temp_y;
			vel.y = vel.y - GRAVITY / 5 * Time;
			if (character.y <= 0&&character.y>=-15)
			{
				gameRestar = true;
				health--;
				Score--;
				if (Score < 0)
				{
					Score = 0;
				}
			}
			if (health == 0)
			{
				gameStart = false;
				gameOver = true;
			}


			
			
		}
		
	}
	if (swingAnimation)//Swing motion
	{
		double force = GRAVITY *sin(AnimationSwing.angle);

		AnimationSwing.angleA = (-1 * force) / AnimationSwing.length;
		AnimationSwing.angleV += AnimationSwing.angleA;


		if (AnimationSwing.angle != PI)
		{
			AnimationSwing.angle += AnimationSwing.angleV;
			character.x = AnimationSwing.length*sin(AnimationSwing.angle) + hook.x;
			character.y = hook.y - AnimationSwing.length *cos(AnimationSwing.angle);
		}

	}
	clockTime += 10;
	if (clockTime == 900)
		clockTime = 0;
}

void backgroundSpeed()
{
	if (swing||!swing)
	{
		cout << vel.x * 5 << endl;
		
		if (character.x > 750)
		{
			if (vel.x > 0)
			{
				BackgroundPosition.x -= vel.x * 3;
			}
			else
			{
				BackgroundPosition.x += vel.x * 3;
			}
		}
		else if (character.x < 450)
		{
			if (vel.x < 0)
			{
				BackgroundPosition.x -= vel.x * 3;
			}
			else
			{
				BackgroundPosition.x += vel.x * 3;
			}
			
		}
		else if (character.x < 750 && character.x > 450)
		{
			BackgroundPosition.x = 0;
		}
		character.x += BackgroundPosition.x;
		hook.x += BackgroundPosition.x;
		hook1.x += BackgroundPosition.x;
		int temp = AnchorNumber - 1;
		int temp2 = CloudNumber - 1;
		for (int i = 0; i < AnchorNumber; i++)
		{
			anchor[i].hook_x += BackgroundPosition.x;
		
			anchor[i].hookIndex++;
			if (anchor[i].hookIndex >= AnchorNumber)
			{
				anchor[i].hookIndex = 0;
			}
			if (anchor[i].hook_x <= -1400)
			{
				if (i == 0)
				{
					anchor[i].hook_x = anchor[3].hook_x + 700 + rand() % 50;
				}
				else if (i==1)
				{
					anchor[i].hook_x = anchor[0].hook_x + 700 + rand() % 50;

				}
				else if (i == 2)
				{
					anchor[i].hook_x = anchor[1].hook_x + 700 + rand() % 50;

				}
				else if (i == 3)
				{
					anchor[i].hook_x = anchor[2].hook_x + 700 + rand() % 50;

				}
			}

			
		}
		for (int i = 0; i < CloudNumber; i++)
		{
			clouds[i].hook_x += BackgroundPosition.x;

			clouds[i].hookIndex++;
			if (clouds[i].hookIndex >= CloudNumber)
			{
				clouds[i].hookIndex = 0;
			}
			if (clouds[i].hook_x <= -1500)
			{
				if (i == 0)
				{
					clouds[i].hook_x = clouds[4].hook_x + 600 + rand() % 80;
				}
				else if (i == 1)
				{
					clouds[i].hook_x = clouds[0].hook_x + 600 + rand() % 80;

				}
				else if (i == 2)
				{
					clouds[i].hook_x = clouds[1].hook_x + 600 + rand() % 80;

				}
				else if (i == 3)
				{
					clouds[i].hook_x = clouds[2].hook_x + 600 + rand() % 80;

				}
				else if (i == 4)
				{
					clouds[i].hook_x = clouds[3].hook_x + 600 + rand() % 80;

				}
			}


		}

		BackgroundPosition.x = 0;
	
		
		
		
	}
	
}
void hookRange(double x,double y)
{
	if (!swing)
	{
		if ((character.x>x - 400 && character.x<x + 400) && character.y > 100)
		{
			iSetColor(0, 255, 0);
			iCircle(x, y, 35, 1000);
			hookInRange = true;
			hookAttached = true;
			swingContineu = true;
			scoreCount = true;
			hook.x = x;
			hook.y = y;

		}
		else
		{
			hookInRange = false;
			swingContineu = false;
			hookAttached = false;
		}
			

	}
	
	else
	{
		if (scoreCount)
		{
			Score++;
			scoreCount = false;
		}
		hookInRange = false;
		hookAttached = true;
	}
		
}
void fullScoreBoard()
{
	iShowImage(0, 0, screenWidth, screenHeight, FullScoreBoard);
	int textY = 0;
	for (int i = 0; i < totalPlayers; i++)
	{
		char p[5],sc[100];
		sprintf_s(p, "%d", i+1);
		sprintf_s(sc, "%d", PlayerScore[i]);
		if (i == 21)
		{
			textY = 0;
		}
		if (i <= 20)
		{
			iText(50, 578 - textY, p, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(50+230, 578 - textY, savedName[i], GLUT_BITMAP_TIMES_ROMAN_24);
			iText(50+230+300, 578 - textY, sc, GLUT_BITMAP_TIMES_ROMAN_24);

		}
		else
		{
			iText(712, 578 - textY, p, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(712 + 230, 578 - textY, savedName[i], GLUT_BITMAP_TIMES_ROMAN_24);
			iText(712 + 230 + 300, 578 - textY, sc, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iSetColor(0, 0, 0);
		
		textY += 29;
	}
}
void initializeAssets()
{
	button.x = 306;
	button.y = 84;
	background = iLoadImage("Assets\\Background\\home_screen-background.png");
	gameBackground = iLoadImage("Assets/Background/gameBackground.png");
	enterName = iLoadImage("Assets\\Background\\nameEnter.png");
	credits = iLoadImage("Assets/Background/credits.png");
	scoreBoard = iLoadImage("Assets/Background/ScoreBoard.png");
	FullScoreBoard = iLoadImage("Assets/Background/fullScoreBoard.png");
	star[0] = iLoadImage("Assets/Background/star0.png");
	star[1] = iLoadImage("Assets/Background/star1.png");
	startGame = iLoadImage("Assets/Background/Startgame.png");
	cloud = iLoadImage("Assets/Background/cloud.png");
	GameOver = iLoadImage("Assets/Background/GameOver.png");
	heart = iLoadImage("Assets/Background/heart.png");
	howToPlay = iLoadImage("Assets/Background/howToPlay.png");
	continueIMG = iLoadImage("Assets/Background/Contineu.png");
	char directory[40];
	for (int i = 0; i < 9; i++){
		sprintf_s(directory, "Assets/Background/s%d.png", i);
		button0[i] = iLoadImage(directory);
		sprintf_s(directory, "Assets/Background/ss%d.png", i);
		button1[i] = iLoadImage(directory);
		sprintf_s(directory, "Assets/Background/sss%d.png", i);
		button2[i] = iLoadImage(directory);
		if (i >= 0 && i < 4)
		{
			sprintf_s(directory, "Assets/Charecter/c%d.png", i);
			characterIMG[i] = iLoadImage(directory);
		}
		if (i >= 0 && i < 3)
		{
			sprintf_s(directory, "Assets/Background/m%d.png", i);
			musicButton[i] = iLoadImage(directory);
			sprintf_s(directory, "Assets/Background/sfx%d.png", i);
			sfxButton[i] = iLoadImage(directory);
		}
	}
	int i2 = iSetTimer(1, backgroundSpeed);

}