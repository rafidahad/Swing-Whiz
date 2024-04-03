#include "SwingWhiz.h"

int screen = 100;//initializing home screen



void pendulumn(int x, int y, int l){

	if (startlength)
	{
		gameSwing.length = findLength(hook.x, hook.y, character.x, character.y);

		gameSwing.angle = findAngle(hook.x, hook.y, character.x, character.y);
		startlength = false;
	}
	else if (gameRestar)
	{
		gameStart = true;
		startlength = false;
		swing = true;
		//fall = false;
		gameSwing.angle = -PI / 3;
		gameRestar = false;


		gameSwing.length = l;
		hookAttached = true;
		swingContineu = true;
		hook.x = x;
		hook.y = y;
		setAnchoreVariables();
		viewAnchor = true;
	}
	else if (gameOn)
	{
		playGameOver = true;
		gameOver = false;
		gameSwing.length = l;
		gameOn = false;
		hookAttached = true;
		swingContineu = true;
		hook.x = x;
		hook.y = y;
		setAnchoreVariables();
		viewAnchor = true;
		health = 3;
		Score = 0;
	}
	
	

	
	
	

	if (swing)
	{
		iSetColor(255, 255, 255);
		iLine(hook.x, hook.y, character.x, character.y);
	}
	iSetColor(255, 0, 0);
	double tempAngle = gameSwing.angle * 180 / PI;

	if (swing)
	{
		if (tempAngle>15)
		{
			iRotate(character.x, character.y, tempAngle);
			iShowImage(character.x - 100, character.y - 180, 200, 240, characterIMG[3]);
			iUnRotate();
		}
		else if (tempAngle < -15)
		{
			{
				iRotate(character.x, character.y, tempAngle);
				iShowImage(character.x - 100, character.y - 180, 200, 240, characterIMG[1]);
				iUnRotate();
			}

		}
		else if ((tempAngle >= -15) && (tempAngle <= 15) || (tempAngle >= -165) && (tempAngle <= 165))
		{
			{
				iRotate(character.x, character.y, tempAngle);
				iShowImage(character.x - 100, character.y - 180, 200, 240, characterIMG[2]);
				iUnRotate();
			}

		}
	}
	
	else
		iShowImage(character.x - 100, character.y - 180, 200, 240, characterIMG[0]);



}
void swingStatic()
{
	hook.x = 1060;
	hook.y = 500;
	hooks(hook.x, hook.y);
	timer = true;
	swing = true;
	swingAnimation = true;
	if (staticSwing)
	{
		animationInitialized = true;
	}
	constantSwing(150,PI/3);
	
	double tempAngle = AnimationSwing.angle * 180 / PI;

	if (tempAngle>15 )
	{
		iRotate(character.x, character.y, tempAngle);
		iShowImage(character.x - 125, character.y - 225, 250, 300, characterIMG[3]);
		iUnRotate();
	}
	else if (tempAngle < -15)
	{
		{
			iRotate(character.x, character.y, tempAngle);
			iShowImage(character.x - 125, character.y - 225, 250, 300, characterIMG[1]);
			iUnRotate();
		}

	}
	else if ((tempAngle >= -15) && (tempAngle <= 15))
	{
		{
			iRotate(character.x, character.y, tempAngle);
			iShowImage(character.x - 125, character.y - 225, 250, 300, characterIMG[2]);
			iUnRotate();
		}

	}
	
	iSetColor(255, 255, 255);
	iLine(hook.x, hook.y, character.x, character.y);
	iFilledCircle(character.x, character.y, 7, 1000);
}

void homeScreen(){
	playAudio(0);
	iShowImage(0, 0, screenWidth, screenHeight, background);

	
	int ium = 0, textY = 0;

	iShowImage(420, 120, 400, 400, scoreBoard);
	if (Sort)
	{
		SortScore();
		Sort = false;
	}
	fopen_s(&playerInfo, FileDirectory, "r");

	if (playerInfo != NULL)
	{
		while (ium < 6 && fscanf_s(playerInfo, "%99s %d", savedName[ium], (unsigned)_countof(savedName[ium]), &PlayerScore[ium]) != EOF)
		{

			char sc[30];
			sprintf_s(sc, "%d", PlayerScore[ium]);

			iSetColor(0, 0, 0);
			iText(460, 290 - textY, savedName[ium], GLUT_BITMAP_TIMES_ROMAN_24);
			iText(710, 290 - textY, sc, GLUT_BITMAP_TIMES_ROMAN_24);
			ium++;
			textY += 30;
		}
	}
	
	fclose(playerInfo);
	swingStatic();
	

	if (buttonState == true && buttonClick == false)
	{
		if (buttonSelect == 0)
		{
			iShowImage(50, 50, button.x, button.y, button0[4]);//exit
			iShowImage(50, 159, button.x, button.y, button0[3]);//settings
			iShowImage(50, 268, button.x, button.y, button0[2]);//credits
			iShowImage(50, 377, button.x, button.y, button0[1]);//how to play
			iShowImage(420, 420, 400, 102, button0[8]);
			iShowImage(50, 486, button.x + 10, button.y + 10, button1[0]);//play game
			
		}
		else if (buttonSelect == 1)
		{
			iShowImage(50, 50, button.x, button.y, button0[4]);//exit
			iShowImage(50, 159, button.x, button.y, button0[3]);//settings
			iShowImage(50, 268, button.x, button.y, button0[2]);//credits
			iShowImage(50, 377, button.x + 10, button.y + 10, button1[1]);//how to play
			iShowImage(50, 486, button.x, button.y, button0[0]);//play game
			iShowImage(420, 420, 400, 102, button0[8]);
		}
		else if (buttonSelect == 2)
		{
			iShowImage(50, 50, button.x, button.y, button0[4]);//exit
			iShowImage(50, 159, button.x, button.y, button0[3]);//settings
			iShowImage(50, 268, button.x + 10, button.y + 10, button1[2]);//credits
			iShowImage(50, 377, button.x, button.y, button0[1]);//how to play
			iShowImage(50, 486, button.x, button.y, button0[0]);//play game
			iShowImage(420, 420, 400, 102, button0[8]);
		}
		else if (buttonSelect == 3)
		{
			iShowImage(50, 50, button.x, button.y, button0[4]);//exit
			iShowImage(50, 159, button.x + 10, button.y + 10, button1[3]);//settings
			iShowImage(50, 268, button.x, button.y, button0[2]);//credits
			iShowImage(50, 377, button.x, button.y, button0[1]);//how to play
			iShowImage(50, 486, button.x, button.y, button0[0]);//play game
			iShowImage(420, 420, 400, 102, button0[8]);
		}
		else if (buttonSelect == 4)
		{
			iShowImage(50, 50, button.x + 10, button.y + 10, button1[4]);//exit
			iShowImage(50, 159, button.x, button.y, button0[3]);//settings
			iShowImage(50, 268, button.x, button.y, button0[2]);//credits
			iShowImage(50, 377, button.x, button.y, button0[1]);//how to play
			iShowImage(50, 486, button.x, button.y, button0[0]);//play game
			iShowImage(420, 420, 400, 102, button0[8]);
		}
		else if (buttonSelect == 50)
		{
			iShowImage(50, 50, button.x, button.y, button0[4]);//exit
			iShowImage(50, 159, button.x, button.y, button0[3]);//settings
			iShowImage(50, 268, button.x, button.y, button0[2]);//credits
			iShowImage(50, 377, button.x, button.y, button0[1]);//how to play
			iShowImage(50, 486, button.x, button.y, button0[0]);//play game
			iShowImage(420, 420, 400+10, 102+10, button1[8]);
		}

	}
	else if (buttonState == true && buttonClick == true)
	{
		if (buttonSelect == 0)
		{
			if (buttonTimer < 50)
			{
				iShowImage(50, 50, button.x, button.y, button0[4]);//exit
				iShowImage(50, 159, button.x, button.y, button0[3]);//settings
				iShowImage(50, 268, button.x, button.y, button0[2]);//credits
				iShowImage(50, 377, button.x, button.y, button0[1]);//how to play
				iShowImage(50, 486, button.x, button.y, button2[0]);//play game

				buttonTimer++;
			}
			else
			{
				buttonTimer = 0;
				buttonClick = false;
				buttonState = false;
				screen = 0;
			}
		}
		else if (buttonSelect == 1)
		{
			if (buttonTimer < 50)
			{
				iShowImage(50, 50, button.x, button.y, button0[4]);//exit
				iShowImage(50, 159, button.x, button.y, button0[3]);//settings
				iShowImage(50, 268, button.x, button.y, button0[2]);//credits
				iShowImage(50, 377, button.x, button.y, button2[1]);//how to play
				iShowImage(50, 486, button.x, button.y, button0[0]);//play game
				buttonTimer++;
			}
			else
			{
				buttonTimer = 0;
				buttonClick = false;
				buttonState = false;
				screen = 1;
			}

		}
		else if (buttonSelect == 2)
		{
			if (buttonTimer < 50)
			{
				iShowImage(50, 50, button.x, button.y, button0[4]);//exit
				iShowImage(50, 159, button.x, button.y, button0[3]);//settings
				iShowImage(50, 268, button.x, button.y, button2[2]);//credits
				iShowImage(50, 377, button.x, button.y, button0[1]);//how to play
				iShowImage(50, 486, button.x, button.y, button0[0]);//play game
				buttonTimer++;
			}
			else
			{
				buttonTimer = 0;
				buttonClick = false;
				buttonState = false;
				screen = 2;
			}

		}
		else if (buttonSelect == 3)
		{
			if (buttonTimer < 50)
			{
				iShowImage(50, 50, button.x, button.y, button0[4]);//exit
				iShowImage(50, 159, button.x, button.y, button2[3]);//settings
				iShowImage(50, 268, button.x, button.y, button0[2]);//credits
				iShowImage(50, 377, button.x, button.y, button0[1]);//how to play
				iShowImage(50, 486, button.x, button.y, button0[0]);//play game
				buttonTimer++;
			}
			else
			{
				buttonTimer = 0;
				buttonClick = false;
				buttonState = false;
				screen = 3;
			}

		}
		else if (buttonSelect == 4)
		{
			if (buttonTimer < 50)
			{
				iShowImage(50, 50, button.x, button.y, button2[4]);//exit
				iShowImage(50, 159, button.x, button.y, button0[3]);//settings
				iShowImage(50, 268, button.x, button.y, button0[2]);//credits
				iShowImage(50, 377, button.x, button.y, button0[1]);//how to play
				iShowImage(50, 486, button.x, button.y, button0[0]);//play game
				buttonTimer++;
			}
			else
			{
				buttonTimer = 0;
				buttonClick = false;
				buttonState = false;
				exit(0);
			}

		}
		else if (buttonSelect == 50)
		{
			if (buttonTimer < 50)
			{
				iShowImage(50, 50, button.x, button.y, button0[4]);//exit
				iShowImage(50, 159, button.x, button.y, button0[3]);//settings
				iShowImage(50, 268, button.x, button.y, button0[2]);//credits
				iShowImage(50, 377, button.x, button.y, button0[1]);//how to play
				iShowImage(50, 486, button.x, button.y, button0[0]);//play game
				iShowImage(420, 420, 400, 102, button2[8]);
				buttonTimer++;
			}
			else
			{
				buttonTimer = 0;
				buttonClick = false;
				buttonState = false;
				screen = 50;
			}

		}
	}


	else
	{
		iShowImage(50, 50, button.x, button.y, button0[4]);//exit
		iShowImage(50, 159, button.x, button.y, button0[3]);//settings
		iShowImage(50, 268, button.x, button.y, button0[2]);//credits
		iShowImage(50, 377, button.x, button.y, button0[1]);//how to play
		iShowImage(50, 486, button.x, button.y, button0[0]);//play game
		iShowImage(420, 420, 400, 102, button0[8]);
	}


}
void playGame(){
	playAudio(0);
	iShowImage(0, 0, screenWidth, screenHeight, background);
	swingStatic();

	if (buttonState == true && buttonClick == false)
	{
		if (buttonSelect == 5)
		{
			iShowImage(50, 159, button.x, button.y, button0[7]);//back
			iShowImage(50, 268, button.x, button.y, button0[6]);//continue
			iShowImage(50, 377, button.x + 10, button.y + 10, button1[5]);//new game
		}
		else if (buttonSelect == 6)
		{
			iShowImage(50, 159, button.x, button.y, button0[7]);//back
			iShowImage(50, 268, button.x + 10, button.y + 10, button1[6]);//continue
			iShowImage(50, 377, button.x, button.y, button0[5]);//new game
		}
		else if (buttonSelect == 7)
		{
			iShowImage(50, 159, button.x + 10, button.y + 10, button1[7]);//back
			iShowImage(50, 268, button.x, button.y, button0[6]);//continue
			iShowImage(50, 377, button.x, button.y, button0[5]);//new game
		}

	}
	else if (buttonState == true && buttonClick == true)
	{
		if (buttonSelect == 5)
		{
			if (buttonTimer < 50)
			{
				iShowImage(50, 159, button.x, button.y, button0[7]);//back
				iShowImage(50, 268, button.x, button.y, button0[6]);//continue
				iShowImage(50, 377, button.x, button.y, button2[5]);//new game
				buttonTimer++;
			}
			else
			{
				buttonTimer = 0;
				buttonClick = false;
				buttonState = false;
				
				gameOver = false;
				screen = 5;
				swingAnimation = false;
			}
		}
		else if (buttonSelect == 6)
		{
			if (buttonTimer < 50)
			{
				iShowImage(50, 159, button.x, button.y, button0[7]);//back
				iShowImage(50, 268, button.x, button.y, button2[6]);//continue
				iShowImage(50, 377, button.x, button.y, button0[5]);//new game
				buttonTimer++;
			}
			else
			{
				buttonTimer = 0;
				buttonClick = false;
				buttonState = false;
				playGameOver = true;
				screen = 6;
			}

		}
		else if (buttonSelect == 7)
		{
			if (buttonTimer < 50)
			{
				iShowImage(50, 159, button.x, button.y, button2[7]);//back
				iShowImage(50, 268, button.x, button.y, button0[6]);//continue
				iShowImage(50, 377, button.x, button.y, button0[5]);//new game
				buttonTimer++;
			}
			else
			{
				buttonTimer = 0;
				buttonClick = false;
				buttonState = false;
				screen = 100;
			}

		}
	}


	else
	{
		iShowImage(50, 159, button.x, button.y, button0[7]);//back
		iShowImage(50, 268, button.x, button.y, button0[6]);//continue
		iShowImage(50, 377, button.x, button.y, button0[5]);//new game
	}





}
void creditScreen()
{
	playAudio(0);
	iShowImage(0, 0, screenWidth, screenHeight, credits);
	timer = true;
	cout << clockTime << endl;

	if (buttonState == true && buttonClick == false)
	{
		if (buttonSelect == 7)
		{
			iShowImage(50, 268, button.x + 10, button.y + 10, button1[7]);//back
		}


	}
	else if (buttonState == true && buttonClick == true)
	{

		if (buttonSelect == 7)
		{
			if (buttonTimer < 50)
			{
				iShowImage(50, 268, button.x, button.y, button2[7]);//back
				buttonTimer++;
			}
			else
			{
				buttonTimer = 0;
				buttonClick = false;
				buttonState = false;
				screen = 100;
			}

		}
	}


	else
	{
		iShowImage(50, 268, button.x, button.y, button0[7]);//back

	}
	if (clockTime <= 300)
	{
		iShowImage(700, 105, 100, 100, star[0]);
		iShowImage(700, 240, 100, 100, star[0]);
		iShowImage(700, 375, 100, 100, star[1]);
	}
	else if (clockTime <= 600)
	{
		iShowImage(700, 105, 100, 100, star[0]);
		iShowImage(700, 240, 100, 100, star[1]);
		iShowImage(700, 375, 100, 100, star[0]);
	}
	else if (clockTime <= 900)
	{
		iShowImage(700, 105, 100, 100, star[1]);
		iShowImage(700, 240, 100, 100, star[0]);
		iShowImage(700, 375, 100, 100, star[0]);
	}
	else
		timer = false;



}
void settings(){
	playAudio(0);
	iShowImage(0, 0, screenWidth, screenHeight, background);
	swingStatic();


	if (buttonState == true && buttonClick == false)
	{
		if (buttonSelect == 8)
		{
			if (sfxAudio)
			{
				iShowImage(50, 268, button.x, button.y, sfxButton[1]);//sfx
			}
			else
			{
				iShowImage(50, 268, button.x, button.y, sfxButton[0]);//sfx
			}
			iShowImage(50, 159, button.x, button.y, button0[7]);//back

			iShowImage(50, 377, button.x + 10, button.y + 10, musicButton[2]);//music
		}
		else if (buttonSelect == 9)
		{
			if (audio)
			{
				iShowImage(50, 377, button.x, button.y, musicButton[1]);//music
			}
			else
			{
				iShowImage(50, 377, button.x, button.y, musicButton[0]);//music
			}
			iShowImage(50, 159, button.x, button.y, button0[7]);//back
			iShowImage(50, 268, button.x + 10, button.y + 10, sfxButton[2]);//sfx

		}
		else if (buttonSelect == 7)
		{
			if (audio)
			{
				iShowImage(50, 377, button.x, button.y, musicButton[1]);//music
			}
			else
			{
				iShowImage(50, 377, button.x, button.y, musicButton[0]);//music
			}
			if (sfxAudio)
			{
				iShowImage(50, 268, button.x, button.y, sfxButton[1]);//sfx
			}
			else
			{
				iShowImage(50, 268, button.x, button.y, sfxButton[0]);//sfx
			}
			iShowImage(50, 159, button.x + 10, button.y + 10, button1[7]);//back
		}

	}
	else if (buttonState == true && buttonClick == true)
	{
		if (buttonSelect == 8)
		{
			if (audio)
			{
				iShowImage(50, 377, button.x, button.y, musicButton[0]);//music
				audio = false;
				//playing = false;
			}
			else
			{
				iShowImage(50, 377, button.x, button.y, musicButton[1]);//music
				audio = true;
			}
			if (sfxAudio)
			{
				iShowImage(50, 268, button.x, button.y, sfxButton[1]);//sfx
			}
			else
			{
				iShowImage(50, 268, button.x, button.y, sfxButton[0]);//sfx
			}

			iShowImage(50, 159, button.x, button.y, button0[7]);//back
			playAudio(0);
			buttonClick = false;
			buttonState = false;



		}
		else if (buttonSelect == 9)
		{
			if (audio)
			{
				iShowImage(50, 377, button.x, button.y, musicButton[1]);//music
			}
			else
			{
				iShowImage(50, 377, button.x, button.y, musicButton[0]);//music
			}
			if (sfxAudio)
			{
				iShowImage(50, 268, button.x, button.y, sfxButton[0]);//sfx
				sfxAudio = false;

			}
			else
			{
				iShowImage(50, 268, button.x, button.y, sfxButton[1]);//sfx
				sfxAudio = true;
			}

			iShowImage(50, 159, button.x, button.y, button0[7]);//back
			playAudio(0);
			buttonClick = false;
			buttonState = false;

		}
		else if (buttonSelect == 7)
		{
			if (buttonTimer < 50)
			{
				iShowImage(50, 159, button.x, button.y, button2[7]);//back
				if (audio)
				{
					iShowImage(50, 377, button.x, button.y, musicButton[1]);//music
				}
				else
				{
					iShowImage(50, 377, button.x, button.y, musicButton[0]);//music
				}
				if (sfxAudio)
				{
					iShowImage(50, 268, button.x, button.y, sfxButton[1]);//sfx
				}
				else
				{
					iShowImage(50, 268, button.x, button.y, sfxButton[0]);//sfx
				}
				buttonTimer++;
			}
			else
			{
				buttonTimer = 0;
				buttonClick = false;
				buttonState = false;
				screen = 100;
			}

		}
	}


	else
	{
		iShowImage(50, 159, button.x, button.y, button0[7]);//back
		if (audio)
		{
			iShowImage(50, 377, button.x, button.y, musicButton[1]);//music
		}
		else
		{
			iShowImage(50, 377, button.x, button.y, musicButton[0]);//music
		}
		if (sfxAudio)
		{
			iShowImage(50, 268, button.x, button.y, sfxButton[1]);//sfx
		}
		else
		{
			iShowImage(50, 268, button.x, button.y, sfxButton[0]);//sfx
		}
	}





}
void playerName()
{
	iShowImage(0, 0, screenWidth, screenHeight, enterName);
	iSetColor(0, 0, 0);
	iText(500, 400, name, GLUT_BITMAP_TIMES_ROMAN_24);
}
bool gameStartScreen = true;;
void newGame()
{
	
	iShowImage(0, 0, screenWidth, screenHeight, gameBackground);
	axis h;
	h.x = 1246;
	h.y = 748;
	if (gameOver)
	{
		if (playGameOver)
		{
			playSFX(0);
			playGameOver = false;
			playing = true;
		}
		
		
		iShowImage(0, 0, screenWidth, screenHeight, GameOver);
		iSetColor(0, 0, 0);
		iText(270, 270, name, GLUT_BITMAP_TIMES_ROMAN_24);
		char ScoreC[40];
		sprintf_s(ScoreC, "%d", Score);
		iText(900, 270, ScoreC, GLUT_BITMAP_TIMES_ROMAN_24);
		if (fileWrite)
		{
			fopen_s(&playerInfo, FileDirectory, "a");
			if (playerInfo != NULL)
			{
				fprintf_s(playerInfo, "%s %d\n", name, Score);
				printf("File is writen\n");
				fclose(playerInfo);
				fileWrite = false;
			}
			
		}
		Sort = true;
		
	}
	else if (gameStart)
	{
		pendulumn(250, 550, 300);
		showAnchor();
		fileWrite = true;


		for (int i = 1; i <= health; i++)
		{
			iShowImage(h.x, h.y, 35, 35, heart);
			h.x += 40;
		}
		iSetColor(0, 0, 0);
		char ScoreC[40];
		sprintf_s(ScoreC, "Score: %d", Score);
		iText(1080, 750, ScoreC, GLUT_BITMAP_TIMES_ROMAN_24);
		

		
	}

	else if (gameStartScreen)
	{
		playAudio(1);

		iShowImage(0, 0, screenWidth, screenHeight, startGame);
		


	}

}

void iDraw()
{
	iClear();

	if (screen == 100)
		homeScreen();
	else if (screen == 0)
		playGame();
	
	else if (screen == 2)
	{

		timer = true;
		creditScreen();
	}

	else if (screen == 3)
		settings();
	else if (screen == 5)
		playerName();
	else if (screen == 10)
	{
		newGame();
	}
	else if (screen == 50)
	{
		fullScoreBoard();
	}
	else if (screen == 6)

		continueScreen();
	else if (screen == 1)
	{
		iShowImage(0, 0, screenWidth, screenHeight, howToPlay);
	}

}








void iMouseMove(int mx, int my)
{
	
}

void iPassiveMouseMove(int mx, int my)
{
	if (screen == 100)
	{
		if ((mx > 50 && mx<356) && (my>50 && my<134))//exit
		{
			buttonState = true;
			buttonSelect = 4;
		}
		else if ((mx > 50 && mx<356) && (my>159 && my < 243))//settings
		{
			buttonState = true;
			buttonSelect = 3;
		}
		else if ((mx > 50 && mx<356) && (my>268 && my < 352))//credits
		{
			buttonState = true;
			buttonSelect = 2;
		}
		else if ((mx > 50 && mx<356) && (my>377 && my<461))//how to play
		{
			buttonState = true;
			buttonSelect = 1;
		}
		else if ((mx > 50 && mx<356) && (my>486 && my < 570))//play game
		{
			buttonState = true;
			buttonSelect = 0;

		}
		else if ((mx >435 && mx<805) && (my>423 && my < 523))
		{
			buttonState = true;
			buttonSelect = 50;

		}
		else
		{
			buttonState = false;
			buttonTimer = 0;

		}
	}
	else if (screen == 0)
	{
		if ((mx > 50 && mx<356) && (my>159 && my < 243))//back
		{
			buttonState = true;
			buttonSelect = 7;
		}
		else if ((mx > 50 && mx<356) && (my>268 && my < 352))//continue
		{
			buttonState = true;
			buttonSelect = 6;
		}
		else if ((mx > 50 && mx<356) && (my>377 && my<461))//new game
		{
			buttonState = true;
			buttonSelect = 5;
		}
		else
		{
			buttonState = false;
			buttonTimer = 0;

		}

	}
	else if (screen == 2)
	{
		if ((mx > 50 && mx<356) && (my>268 && my < 352))//continue
		{
			buttonState = true;
			buttonSelect = 7;
		}
		else
		{
			buttonState = false;
			buttonTimer = 0;

		}
	}
	else if (screen == 3)
	{
		if ((mx > 50 && mx<356) && (my>159 && my < 243))//back
		{
			buttonState = true;
			buttonSelect = 7;
		}
		else if ((mx > 50 && mx<356) && (my>268 && my < 352))//sfx
		{
			buttonState = true;
			buttonSelect = 9;
		}
		else if ((mx > 50 && mx<356) && (my>377 && my<461))//music
		{
			buttonState = true;
			buttonSelect = 8;
		}
		else
		{
			buttonState = false;
			buttonTimer = 0;

		}

	}
}

void iMouse(int button, int state, int mx, int my)
{
	
	if (screen == 100)
	{
		if ((mx > 50 && mx<356) && (my>50 && my<134))
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				buttonClick = true;
				

			}
		}
		else if ((mx > 50 && mx<356) && (my>159 && my < 243))
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				buttonClick = true;
				

			}
		}
		else if ((mx > 50 && mx<356) && (my>268 && my < 352))
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				buttonClick = true;
				timer = false;
				

			}
		}
		else if ((mx > 50 && mx<356) && (my>377 && my<461))
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				buttonClick = true;
				

			}
		}
		else if ((mx > 50 && mx<356) && (my>486 && my < 570))
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				buttonClick = true;
				

			}

		}
		else if ((mx >435 && mx<805) && (my>423 && my < 523))
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				buttonClick = true;
				

			}
		}
		else
		{


		}
	}
	else if (screen == 10)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (space)
			{
				startlength = true;
				swing = true;
				
				space = false;
			}
			else
			{
				Time = 0;
				swing = false;
				
				space = true;
			}
		}
	}
	else if (screen == 0 || screen == 3)
	{
		if ((mx > 50 && mx<356) && (my>159 && my < 243))
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				buttonClick = true;
				

			}
		}
		else if ((mx > 50 && mx<356) && (my>268 && my < 352))
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				buttonClick = true;
				

			}
		}
		else if ((mx > 50 && mx<356) && (my>377 && my<461))
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				buttonClick = true;
				nameIndex = 0;
				name[nameIndex] = '\0';
				gameStartScreen = true;
				
			}
		}
		else
		{


		}

	}
	else if (screen == 2)
	{
		if ((mx > 50 && mx<356) && (my>268 && my < 352))
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				buttonClick = true;
				

			}
			else
			{


			}
		}
	}




	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}




void iKeyboard(unsigned char key)
{
	
	if (screen == 5)
	{
		if (key != '\b')
		{
			if (key == ' ')
			{
				name[nameIndex] = '_';
				nameIndex++;
				name[nameIndex] = '\0';
			}
			else if (key == '\r')
			{
			
				startInitialized = true;
				screen = 10;
				playing = true;
			

			}

			else
			{
				name[nameIndex] = key;
				nameIndex++;
				name[nameIndex] = '\0';

			}


		}


		else
		{
			if (nameIndex <= 0)
			{
				nameIndex = 0;
			}
			else
			{
				nameIndex--;
			}

			name[nameIndex] = '\0';
		}

	}
	else if (screen == 10)
	{
		if (startInitialized)
		{
			if (key == 's')
			{
				gameStartScreen = false;
				gameStart = true;
				startlength = false;
				gameOn = true;
				swing = true;
				gameOver = false;
				
				gameSwing.angle = -PI / 3;
				startInitialized = false;
			}

		}
		
		
		if (key == ' ')
		{
			
				if (space)
				{
					startlength = true;
					

					swing = true;

					
					space = false;
				}
				else
				{
					Time = 0;
					swing = false;
					
					space = true;
				}
			
			cout << swingContineu << endl;

		}
	}

	
	
}


void iSpecialKeyboard(unsigned char key)
{

	
	if (screen == 5 || screen == 6)
	{
		if (key == GLUT_KEY_F1)
		{
			screen = 0;

		}

	}
	if (screen == 6)
	{
		if (key == GLUT_KEY_F1)
		{
			screen = 0;
			playing = true;
		}
	}
	if (screen == 10 || screen == 50 || screen == 1)
	{
		if (key == GLUT_KEY_F1)
		{
			screen = 100;

		}

	}
	
	
}


int main()
{
	int i = iSetTimer(15, TimingPendulumn);
	iInitialize(screenWidth, screenHeight, projectName);
	initializeAssets();
	iStart();
	return 0;
}