#include <wiringPi.h>
#include <softPwm.h>



#define PIN 1


int main (void) {

wiringPiSetup();
softPwmCreate(PIN, 0, 200);

while(1){:
        softPwmWrite(PIN, 5);
        delay(100);
        softPwmWrite(PIN, 15);
        delay(100);
        softPwmWrite(PIN, 30);
        delay(100);
        softPwmWrite(PIN, 100);
        delay(100);
        }
return 0;
}
