#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "p2switches.h"
#include "stateMachines.h"
#include "led.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int color = COLOR_GREEN;
short decide_var = 0;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount++;
  // toggle_red25 will be called 25 times
  if(secCount <= 62 && button_state == 1){
    toggle_red25();
    redrawScreen = 1;
  }
  // toggle_red will be called 25 times
  if((secCount > 62 && secCount <= 124) && button_state == 1){
    toggle_red(); // led will be 50% intensity
    redrawScreen = 1;
  }
  // toggle_red75 will be called 25 times
  if((secCount > 124 && secCount <= 186) && button_state == 1){
    toggle_red75();
    redrawScreen = 1;
  }
  if(secCount == 250){		/* once/sec */
    secCount = 0;
    color = (color == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  }
}

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  buzzer_init();
  p2sw_init(15);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_WHITE);
  drawString11x16(20, 20, "Welcome!", COLOR_PINK, COLOR_WHITE);
  drawString5x7(20, 40, "S1: Dim red LED", COLOR_RED, COLOR_WHITE);
  drawString5x7(20, 60, "S2: Xmas Tree!", COLOR_RED, COLOR_WHITE);
  drawString5x7(20, 80, "S3: Play song!", COLOR_RED, COLOR_WHITE);
  drawString5x7(20, 100, "S4: Reset", COLOR_RED, COLOR_WHITE);
  
  while (1) {			      /* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      switch(button_state){
      case 1:                         /* case will dim red LED */
	buzzer_set_period(0);
	break;
      case 2:
	xmas(color);                  /* color will be changed using the wdt */
	break;
      case 3:                         /* testing assembly */
	if(decide(decide_var)){
	  state_advance();
	}
	else if(decide_var == 0){
	  buzzer_set_period(3000);
	}
	break;
      case 4:                         /* off state */
	clearScreen(COLOR_WHITE);
	buzzer_set_period(0);
	red_on = 0;
	led_changed = 1;
	led_update();
	break;
      }
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}
