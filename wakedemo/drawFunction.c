#include "lcdutils.h"
#include "drawFunction.h"

void drawT(u_int color){
  u_char r, c;
  u_char center = 10;
  for(r = 0; r <= 10; r++){
    for(c = 0; c <= r; c++){
      drawPixel(center+c+55, r+60, color);
      drawPixel(center-c+55, r+60, color);
    }
  }
  for(r = 0; r <= 20; r++){
    for(c = 0; c <= r; c++){
      drawPixel(center+c+55, r+65, color);
      drawPixel(center-c+55, r+65, color);
    }
  }
  for(r = 0; r <= 30; r++){
    for(c = 0; c <= r; c++){
      drawPixel(center+c+55, r+73, color);
      drawPixel(center-c+55, r+73, color);
    }
  }
  for(r = 0; r <= 10; r++){
    for(c = 0; c <= 10; c++){
      drawPixel(c+60, r+104, COLOR_BROWN);
    }
  }
}
