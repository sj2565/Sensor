#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <signal.h>

#define TRIG 2
#define ECHO 0

void cleanup(int signum){
	printf("GPIO 핀번호 리셋\n");
	
	digitalWrite(TRIG, LOW);
	pinMode(TRIG, INPUT);
	pinMode(ECHO, INPUT);
	printf("안전하게 종료!\n");
	exit(0);
}

void setup(){
	if (wiringPiSetup() == -1){
		printf("wiringPi 초기화 실패");
		exit(1);
	}
	
	//wiringPiSetup();
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	
	digitalWrite(TRIG, LOW);
		
	signal(SIGINT, cleanup);
}

int getDistance(){
	digitalWrite(TRIG, LOW);
	delayMicroseconds(10);
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG, LOW);

	while (digitalRead(ECHO) == LOW);
	long startTime = micros();
	while (digitalRead(ECHO) == HIGH);
	long travelTime = micros() - startTime;

	return travelTime / 58;
}

int main(){
	setup();
	while (1){
		printf("Distance : %d cm\n", getDistance());
	    delay(1000);
	}	       
	return 0;
}
