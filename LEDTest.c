#include <stdio.h>
#include <wiringPi.h>

#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define LED4 23

int main(void)
{	
	wiringPiSetupGpio();
	pinMode(LED4, OUTPUT);
	while(1)
	{
		digitalWrite(LED4, HIGH);
		delay(1000);
		digitalWrite(LED4, LOW);
		delay(1000); 
	}
	
	return 0;
}
