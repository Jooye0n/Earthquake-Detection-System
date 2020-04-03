#include <stdio.h>
#include <wiringPi.h>

#define LCD_RS 11
#define LCD_E 10
#define LCD_D4 6
#define LCD_D5 5
#define LCD_D6 4
#define LCD_D7 1

int main()
{
   int lcd;
   wiringPiSetup();
   
   
   if(lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0)) {
      printf("lcd init failed!\n");
      return -1;
   }
   
   lcdPosition(lcd, 0, 0); //First row of display
   lcdPuts(lcd, "  It's time to  ");
   lcdPosition(lcd, 0, 1); //Second row of display
   lcdPuts(lcd, "take your pills!");
}