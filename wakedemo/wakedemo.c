#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int color = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount == 250) {		/* once/sec */
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
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_WHITE);
  while (1) {			/* forever */
    static char count = 1;
    if (redrawScreen) {
      redrawScreen = 0;
      drawString11x16(20,20, "hello", color, COLOR_WHITE);
      switch(count){
      case 1:
	fillRectangle(30, 30, 60, 60, color);
	drawTree(50, 60, COLOR_GREEN);
	count++;
      case 2:
	//buzzer_set_period(2000);
	count = 1;
	break;
      }
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



