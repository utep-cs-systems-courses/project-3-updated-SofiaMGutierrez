#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "drawFunction.h"

static int state = 0;
static int note = 0;

void play_buzzer(short note){
  buzzer_set_period(2000000/note);
}

void xmas(int color)
{
  drawTree(color);
  drawString5x7(20, 40, "Happy Holidays!", COLOR_RED, COLOR_WHITE);
  switch(note){
  case 0:
    buzzer_set_period(2000000/3136);
    note++;
    break;
  case 1:
    buzzer_set_period(2000000/2093);
    note++;
    break;
  case 2:
    buzzer_set_period(2000000/2093);
    note++;
    break;
  case 3:
    buzzer_set_period(2000000/2349);
    note = 0;
    break;
  }
}

char toggle_red() // on, off, on, off
{
  switch (state){
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  led_changed = 1;
  led_update();
  return led_changed; // for state_advance
}

void toggle_red25() // off, off, off, on
{
  switch(state){
  case 0:
    red_on = 0;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 2;
    break;
  case 2:
    red_on = 0;
    state = 3;
    break;
  case 3:
    red_on = 1;
    state = 0;
    break;
  }
  led_changed = 1;
  led_update();
}

void toggle_red75() // on, on, on, off
{
  switch(state){
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 1;
    state = 2;
    break;
  case 2:
    red_on = 1;
    state = 3;
    break;
  case 3:
    red_on = 0;
    state = 0;
    break;
  }
  led_changed = 1;
  led_update();
}

void dim()
{
  switch(state){
  case 0:           /* no dim */
    red_on = 1;
    led_changed = 1;
    led_update();
    state++;
    break;
  case 1:           /* 25% intensity */
    toggle_red25();
    state++;
    break;
  case 2:           /* 50% intensity */
    toggle_red();
    state++;
    break;
  case 3:
    toggle_red75(); /* 75% intensity */
    state = 0;
    break;
  }
}

// turns green on only when red is on
char toggle_green()
{
  char changed = 0;
  if(red_on){
    green_on ^=1;
    changed = 1;
  }
  return changed; // for state_advance
}

// called by state_advance to play song
void buzz_advance()
{
  switch(state){
  case 0:
    buzz_assembly(0);
    state++;
    break;
  case 1:
    buzz_assembly(1);
    state++;
    break;
  case 2:
    buzz_assembly(2);
    state++;
    break;
  case 3:
    buzz_assembly(3);
    state = 0;
    break;
  default:
    state++;
  }
}

// alternate between toggling red and toggling green
void state_advance()
{
  char changed = 0;
  static enum {R=0, G=1} color = G;
  switch (color){
  case R:
    changed = toggle_red();
    color = G;
    buzz_advance();
    break;
  case G:
    changed = toggle_green();
    color = R;
    buzz_advance();
    break;
  }
  led_changed = changed;
  led_update();
}
