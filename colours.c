#include <stdio.h>
#include "gfx.h"

int main () {

int ysize = 600;
int xsize = 800;
int color[4],count,c,row;

gfx_open(xsize,ysize,"Colours for Mastermind");
gfx_clear_color(1,50,32);
gfx_clear();

for (row=1;row<4;row++) {
printf("Enter a number: ");
for (count=1;count<5;count++) {
scanf("%d", &color[count]);

//red
if (color[count] == 0) {
  gfx_color(255,0,0);
  gfx_fillcircle(count*50,row*50,25);
}
//blue
else if (color[count] == 1) {
  gfx_color(0,0,255);
  gfx_fillcircle(count*50,row*50,25);
}
//green
else if (color[count] == 2) {
  gfx_color(0,255,0);
  gfx_fillcircle(count*50,row*50,25);
}
//yellow
else if (color[count] == 3) {
  gfx_color(255,255,0);
  gfx_fillcircle(count*50,row*50,25);
}
//orange
else if (color[count] == 4) {
  gfx_color(255,165,0);
  gfx_fillcircle(count*50,row*50,25);
}
//purple
else if (color[count] == 5) {
  gfx_color(160,39,240);
  gfx_fillcircle(count*50,row*50,25);
}
//pink
else if (color[count] == 6) {
  gfx_color(255,192,203);
  gfx_fillcircle(count*50,row*50,25);
}
//brown
else if (color[count] == 7) {
  gfx_color(150,75,0);
  gfx_fillcircle(count*50,row*50,25);
}
//black
else if (color[count] == 8) {
  gfx_color(0,0,0);
  gfx_fillcircle(count*50,row*50,25);
}
//white
else if (color[count] == 9) {
  gfx_color(255,255,255);
  gfx_fillcircle(count*50,row*50,25);
}
}
}
while(1) {
c = gfx_wait();
if(c=='q') break;
}
}
