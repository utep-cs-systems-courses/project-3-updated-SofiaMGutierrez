#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

static int state = 0;
static int note = 0;

short call_assembly(){
  short note = -10;
  return buzz_advance_assembly(note);
}

void xmas(int color)
{
  drawTree(color);
  drawString5x7(20, 40, "Happy Holidays!", COLOR_RED, COLOR_WHITE);
  switch(note){
  case 0:
    buzzer_set_period(3136);
    note++;
    break;
  case 1:
    buzzer_set_period(2093);
    note++;
    break;
  case 2:
    buzzer_set_period(2093);
    note++;
    break;
  case 3:
    buzzer_set_period(2349);
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
  char state = 0;
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

char toggle_green()
{
  char changed = 0;
  if(red_on){
    green_on ^=1;
    changed = 1;
  }
  return changed; // for state_advance
}

static int s = 1;
static int note1 = 0;
/*
void song()
{
  switch (s){
  case 1:
    note1 = 1000;
    s++;
    break;
  case 2:
    note1 = 2000;
    s++;
    break;
  case 3:
    note1 = 3000;
    s = 1;
    break;
  }
  play_buzzer(note1);
}
*/

void play_buzzer(int n)
{
  buzzer_set_period(2000000/n);
}

//void buzz_advance()              /* called by state_advance to play siren */
/*
  switch(state){
  case 0:
    note = 1000;
    state++;
    break;
  case 1:
    note = 2000;
    state++;
    break;
  case 2:
    note = 3000;
    state++;
    break;
  case 3:
    note = 4000;
    state = 0;
    break;
  default:
    state++;
  }
  play_buzzer(note);
}
*/
void state_advance()		/* alternate between toggling red & green */
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
