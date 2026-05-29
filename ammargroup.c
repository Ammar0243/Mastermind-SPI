/***********************************************************************************
    Group Name            :    ammargroup
    1st Member Name       :    Muhammad Ammar Haziq Bin Abdul Malek
    1st Matric            :    22010458
    2nd  Member Name      :    Muhammad Isfahann Syakir Bin Shahrum
    2nd Matric            :    22010486      

    Semester              :    May 2024

-Command to compile the project:

gcc ammargroup.c gfx.c -o ammargroup.o -lX11 -lm
***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gfx.h"
#include <string.h>

void generateCode(int code[]);
void guessCode(int guess[]);
void checkCode(int code[],int guess[],int *correction, int games);
void playGame(int level,int *won,int *lost,time_t *startTime);
void colorCode(int guess[],int games, int f0inal);
void openGraphic(int repeat);
void mainMenu(int *level);
void openStatistic(int totalWon,int totalLost,int gamesPlayed,time_t startTime);

//Array for color
char* color[]={"Red", "Blue", "Green", "Yellow", "Orange", "Purple", "Pink", "Brown", "Black", "White"};

int main(void) // Basically the head of the game setup
{  
    
    int played = 1,gamesPlayed = 1;
    int level,won,lost,totalWon=0,totalLost=0;
    time_t startTime;
    char c;
    
    while(played == 1){
    srand(time(NULL));
    char play;
    char c;
    int ysize = 700;
    int xsize = 800;
  
    gfx_open(xsize, ysize, "Mastermind: The Game");
    gfx_clear_color(1, 50, 32);
    gfx_clear();

    gfx_color(136,8,8);
    gfx_fillrectangle(0,65,800,100);
    gfx_color(255,191,0);
    gfx_fillrectangle(0,45,800,20);
    gfx_color(255,191,0);
    gfx_fillrectangle(0,165,800,20);
    gfx_color(255,255,255);
    gfx_text("WELCOME TO THE MASTERMIND",250,100,2);
    
    //The play button
    gfx_color(153, 0, 0);
    gfx_fillrectangle(300,365,200,100);
    gfx_color(255,255,255);
    gfx_text("PLAY",378,400,2);
      
    gfx_flush();
    
    while (1) {
        c = gfx_wait();        
        if ((gfx_xpos() >= 300 && gfx_xpos() <= 500) && (gfx_ypos() >= 365 && gfx_ypos() < 465) && c == 0x01)
        {
          gfx_clear();
          mainMenu(&level);
        }
        else if (c == 'q') 
        {
          break;
        }
    }
    
    playGame(level,&won,&lost,&startTime);
    totalLost = totalLost + lost;
    totalWon = totalWon + won;
    
    //Tab to ask player the difficulty
    gfx_clear();
    gfx_color(255,255,255);
    gfx_text("Do you want to continue playing?",200,200,2);
    
    gfx_color(0,109,91);
    gfx_fillrectangle(175,400,200,100);
    gfx_color(255,255,255);
    gfx_text("Yes",255,435,2);
    
    gfx_color(0,109,91);
    gfx_fillrectangle(425,400,200,100);
    gfx_color(255,255,255);
    gfx_text("No",515,435,2);
    
    c = gfx_wait();
    if ((gfx_xpos() >= 175 && gfx_xpos() <= 375) && (gfx_ypos() >= 400 && gfx_ypos() <= 500) && (c==0x01))
    { 
    play = 'Y';
    }
    else if ((gfx_xpos() >= 425 && gfx_xpos() <= 625) && (gfx_ypos() > 400 && gfx_ypos() < 500) && (c ==0x01)) 
    {
    play = 'N';
    }
    else {
    gfx_wait();
    }
    
    switch(play)
    {
      case 'Y':
      case 'y':
        gamesPlayed++;
        played = 1;
        break;
      case 'n':
      case 'N':
        played = 0;
        break;
    }  
  }
  
  openStatistic(totalWon,totalLost,gamesPlayed,startTime);
}

//Difficulty menu
void mainMenu(int *level) {
    char c;
    gfx_color(255,255,255);
    gfx_text("Select a Difficulty.",280,200,2);
    
    gfx_color(50,205,50);
    gfx_fillrectangle(100,400,100,100);
    gfx_color(255,255,255);
    gfx_text("EASY",125,430,2);
    
    gfx_color(255,165,0);
    gfx_fillrectangle(360,400,100,100);
    gfx_color(255,255,255);
    gfx_text("MEDIUM",373,430,2);
  
    gfx_color(210,4,45);
    gfx_fillrectangle(600,400,100,100);
    gfx_color(255,255,255);
    gfx_text("HARD",625,430,2);
   
    c = gfx_wait();
    if ((gfx_xpos() >= 100 && gfx_xpos() <= 200) && (gfx_ypos() >= 400 && gfx_ypos() <= 500) && (c==0x01))
  { 
    *level = 1;
  }
    else if ((gfx_xpos() >= 360 && gfx_xpos() < 460) && (gfx_ypos() > 400 && gfx_ypos() < 500) && (c ==0x01)) 
  {
    *level = 2;
  }
    else if ((gfx_xpos() > 600 && gfx_xpos() < 700) && (gfx_ypos() > 400 && gfx_ypos() < 500) && (c ==0x01)) 
  {
    *level = 3;
  }
    else {
    gfx_wait();
    }
    gfx_flush();
}

void playGame(int level,int *gamesWon, int *gamesLost,time_t *startTime) // Function where all the function operates
{
  int games = 0;
  int repeat;
  int code[4];
  int levelPlayer = level;
  *gamesWon = 0;
  *gamesLost = 0;
  *startTime = time(NULL);

  generateCode(code);
  switch(levelPlayer)
  {
    case 1:
      repeat = 10;
      break;
    case 2:
      repeat = 6;
      break;
    case 3:
      repeat = 3;
      break;
  }
  
  openGraphic(repeat);
  
  while(games<repeat)
  {
    int guess[4];
    guessCode(guess);
    int correction;
    checkCode(code,guess,&correction, games);
    colorCode(guess,games,0);
    if (correction==4)
    { 
      break;
    }
    else 
    {
      games++;
    }
  }
  if (games==repeat) 
  {
    gfx_color(255,255,255);
    gfx_text("Sorry, you lost. The code was: ", 25, 575, 1);
    (*gamesLost)++;
    for (int i = 0; i < 4; i++) 
    {
      gfx_color(0,0,0);
      gfx_circle((i+1)*50, 625, 27);
      colorCode(code, 0,575);
      
    }
      
      printf("\n");
  } 
  else 
  {
     (*gamesWon)++;
     printf("Congratulations, you won!\n");  
     gfx_color(255,255,255);
     gfx_text("Congratulations, you won!", 25, 575, 1);
  }  
  gfx_wait();
}

// function to generate random codes for the player to guess
void generateCode(int code[]) { 
  srand(time(NULL)); 
  for (int i = 0; i < 4; i++) {
    code[i] = rand() % 10;
  }

}

// function that collect the player's guess code
void guessCode(int guess[4]) {
    char c = gfx_wait();
    
    for (int i = 0; i < 4; i++) {
        if (gfx_xpos()>=500 && gfx_xpos()<=600 && gfx_ypos()>=50 && gfx_ypos()<=150 && c==0x01 ) {
          guess[i] = 0;
          gfx_wait();                   
        }
        else if (gfx_xpos()>=625 && gfx_xpos()<=725 && gfx_ypos()>=50 && gfx_ypos()<=150 && c==0x01) {
          guess[i] = 1;
          gfx_wait();          
        }
        else if (gfx_xpos()>=500 && gfx_xpos()<=600 && gfx_ypos()>=175 && gfx_ypos()<275 && c==0x01) {
          guess[i] = 2;
          gfx_wait();         
        }
        else if (gfx_xpos()>=625 && gfx_xpos()<=725 && gfx_ypos()>=175 && gfx_ypos()<=275 && c==0x01) {
          guess[i] = 3;
          gfx_wait();         
        }
        else if (gfx_xpos()>=500 && gfx_xpos()<=600 && gfx_ypos()>=300 && gfx_ypos()<400 && c==0x01) {
          guess[i] = 4;  
          gfx_wait();
        }
        else if (gfx_xpos()>=625 && gfx_xpos()<725 && gfx_ypos()>=300 && gfx_ypos()<=400 && c==0x01) {
          guess[i] = 5;          
          gfx_wait();
        }
        else if (gfx_xpos()>500 && gfx_xpos()<=600 && gfx_ypos()>=425 && gfx_ypos()<=525 && c==0x01) {
          guess[i] = 6;          
          gfx_wait();
        }
        else if (gfx_xpos()>=625 && gfx_xpos()<=725 && gfx_ypos()>=425 && gfx_ypos()<=525 && c==0x01) {
          guess[i] = 7;
          gfx_wait();         
        }
        else if (gfx_xpos()>=500 && gfx_xpos()<=600 && gfx_ypos()>=550 && gfx_ypos()<=650 && c==0x01) {
          guess[i] = 8;
          gfx_wait();
        }
        else if (gfx_xpos()>=625 && gfx_xpos()<=725 && gfx_ypos()>=550 && gfx_ypos()<=650 && c==0x01) {
          guess[i] = 9;
          gfx_wait();
        }
        else {
          gfx_wait();
        }
         
    }
}

// function to open the tab graphic
void openGraphic(int repeat)
{
    gfx_clear();
    char c;
    
    
    for (int i = 0; i < repeat; i++) { 
        for (int j=1; j<5; j++) {
            gfx_color(255,255,255);
            gfx_circle(j * 50, (i+1) *50,27);
        }
    }
    
    //red
    gfx_color(0, 0, 0);
    gfx_rectangle(498, 48,102,102);
    gfx_color(255, 0, 0);
    gfx_fillrectangle(500, 50, 100, 100);
    
    //blue
    gfx_color(0, 0, 0);
    gfx_rectangle(623, 48,102,102);
    gfx_color(0, 0, 255);
    gfx_fillrectangle(625, 50, 100, 100);
    
    //green
    gfx_color(0, 0, 0);
    gfx_rectangle(498, 173,102,102);
    gfx_color(0, 255, 0);
    gfx_fillrectangle(500, 175, 100,100);
    
    //yellow
    gfx_color(0, 0, 0);
    gfx_rectangle(623, 173,102,102);
    gfx_color(255, 255, 0);
    gfx_fillrectangle(625, 175, 100,100);
    
    //orange
    gfx_color(0, 0, 0);
    gfx_rectangle(498, 298,102,102);
    gfx_color(255, 165, 0);
    gfx_fillrectangle(500, 300, 100, 100);
    
    //purple
    gfx_color(0, 0, 0);
    gfx_rectangle(623, 298,102,102);
    gfx_color(160, 39, 240);
    gfx_fillrectangle(625, 300, 100, 100);
    
    //pink
    gfx_color(0, 0, 0);
    gfx_rectangle(498, 423,102,102);
    gfx_color(255, 192, 203);
    gfx_fillrectangle(500, 425,100, 100);
    
    //brown
    gfx_color(0, 0, 0);
    gfx_rectangle(623, 423,102,102);
    gfx_color(150, 75, 0);
    gfx_fillrectangle(625, 425, 100, 100);
    
    //black
    gfx_color(0, 0, 0);
    gfx_rectangle(498, 548,102,102);
    gfx_color(0, 0, 0);
    gfx_fillrectangle(500, 550, 100, 100);
    
    //white
    gfx_color(0, 0, 0);
    gfx_rectangle(623, 548,102,102);
    gfx_color(255, 255, 255);
    gfx_fillrectangle(625, 550, 100, 100);


    while (1) {
        c = gfx_wait();
        if (c == 'q') break;
    }
}

// function to appear color on graphics
void colorCode(int guess[4], int games, int final)
{
    int row = 0;
    row = games + 1;
    for (int i = 0; i < 4; i++) {
        // red
        if (guess[i] == 0) {
            gfx_color(255, 0, 0);
            gfx_fillcircle((i + 1) * 50, (row * 50) + final, 25);
            
        }
        // blue
        else if (guess[i] == 1) {
            gfx_color(0, 0, 255);
            gfx_fillcircle((i + 1) * 50, (row * 50) + final, 25);
            gfx_flush();
        }
        // green
        else if (guess[i] == 2) {
            gfx_color(0, 255, 0);
            gfx_fillcircle((i + 1) * 50, (row * 50) + final, 25);
            gfx_flush();
        }
        // yellow
        else if (guess[i] == 3) {
            gfx_color(255, 255, 0);
            gfx_fillcircle((i + 1) * 50, (row * 50) + final, 25);
            gfx_flush();
        }
        // orange
        else if (guess[i] == 4) {
            gfx_color(255, 165, 0);
            gfx_fillcircle((i + 1) * 50, (row * 50) + final, 25);
            gfx_flush();
        }
        // purple
        else if (guess[i] == 5) {
            gfx_color(160, 39, 240);
            gfx_fillcircle((i + 1) * 50, (row * 50) + final, 25);
            gfx_flush();
        }
        // pink
        else if (guess[i] == 6) {
            gfx_color(255, 192, 203);
            gfx_fillcircle((i + 1) * 50, (row * 50) + final, 25);
            gfx_flush();
        }
        // brown
        else if (guess[i] == 7) {
            gfx_color(150, 75, 0);
            gfx_fillcircle((i + 1) * 50, (row * 50) + final, 25);
            gfx_flush();
        }
        // black
        else if (guess[i] == 8) {
            gfx_color(0, 0, 0);
            gfx_fillcircle((i + 1) * 50, (row * 50) + final, 25);
            gfx_flush();
        }
        // white
        else if (guess[i] == 9) {
            gfx_color(255, 255, 255);
            gfx_fillcircle((i + 1) * 50, (row * 50) + final, 25);
            gfx_flush();
        }
    }
    gfx_flush();// Update the graphics
}

// function to check whether the player's guess is correct or not
void checkCode(int code[4], int guess[4], int* correction, int games) {
    *correction = 0;
    int row = games + 1;
    for (int i = 0; i < 4; i++) {
        if (code[i] == guess[i]) {
            gfx_color(255,255,255);
            gfx_fillrectangle(((i + 1) * 50) + 200, (row * 50)-12, 10 ,25);
            (*correction)++;
        }
        else {
        gfx_color(0,0,0);
        gfx_fillrectangle(((i + 1) * 50) + 200, (row * 50)-12, 10,25);    
        }
    }
}
//To show the game's statistics
void openStatistic(int totalWon,int totalLost,int gamesPlayed,time_t startTime)
{
    char lostGame[10];
    char wonGame[10];
    char plays[10];
    char timeGame[100];
    char c;
    time_t end_time=time(NULL);
    double duration = difftime(end_time,startTime);
    
    
    int ysize = 800;
    int xsize = 1000;
    gfx_open(xsize, ysize, "Mastermind Game Play Statistic");
    gfx_clear_color(1, 50, 32);
    gfx_clear();
    
    //To change to string data type
    sprintf(timeGame,"%.0f",duration);
    sprintf(lostGame,"%d",totalLost);
    sprintf(wonGame,"%d",totalWon);
    sprintf(plays,"%d",gamesPlayed);
    while(1)
    {
      c = gfx_wait();
      
      gfx_color(136,8,8);
      gfx_fillrectangle(0,65,1000,100);
      gfx_color(255,191,0);
      gfx_fillrectangle(0,45,1000,20);
      gfx_color(255,191,0);
      gfx_fillrectangle(0,165,1000,20);
      gfx_color(255,255,255);
      gfx_text("GAME PLAY STATISTIC",394,100,2);
      
      gfx_color(0,0,139);
      gfx_fillrectangle(0,265,1000,100);
      gfx_color(70,130,180);
      gfx_fillrectangle(0,245,1000,20);
      gfx_color(70,130,180);
      gfx_fillrectangle(0,365,1000,20);
      gfx_color(255,255,255);
      gfx_text("GAMES PLAYED : ",200,292,2);
      gfx_text(plays,500,294,2);
      
      gfx_color(0,0,139);
      gfx_fillrectangle(0,365,1000,100);
      gfx_color(70,130,180);
      gfx_fillrectangle(0,345,1000,20);
      gfx_color(70,130,180);
      gfx_fillrectangle(0,465,1000,20);
      gfx_color(255,255,255);
      gfx_text("GAMES LOST : ",200,394,2);
      gfx_text(lostGame,500,394,2);

      gfx_color(0,0,139);
      gfx_fillrectangle(0,465,1000,100);
      gfx_color(70,130,180);
      gfx_fillrectangle(0,445,1000,20);
      gfx_color(70,130,180);
      gfx_fillrectangle(0,565,1000,20);
      gfx_color(255,255,255);
      gfx_text("GAMES WON : ",200,490,2);
      gfx_text(wonGame,500,490,2);
      
      gfx_color(0,0,139);
      gfx_fillrectangle(0,565,1000,100);
      gfx_color(70,130,180);
      gfx_fillrectangle(0,545,1000,20);
      gfx_color(70,130,180);
      gfx_fillrectangle(0,665,1000,20);
      gfx_color(255,255,255);
      gfx_text("DURATION : ",200,600,2);
      gfx_text(timeGame,500,600,2);
      gfx_text("SECONDS",586,600,2);
      
      gfx_flush();
      if (c=='q')
      {
        break;
      }
   }
}
