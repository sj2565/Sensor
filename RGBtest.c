#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>
#include <stdlib.h>

#define RED 0 // GPIO 17
#define GREEN 2 // GPIO 27
#define BLUE 3 // GPIO 22

void cleanup(int signum){
	printf(" GPIO핀번호 리셋.. \n");
	
	softPwmWrite(RED, 0);
	softPwmWrite(GREEN, 0);
	softPwmWrite(BLUE, 0);
	
	pinMode(RED, INPUT);
	pinMode(GREEN, INPUT);
	pinMode(BLUE, INPUT);
	
	printf("안전하게 종료! \n");
	exit(0);
}

void setup(){
	wiringPiSetup();
	
	softPwmCreate(RED, 0, 100); //pinMode(RED, PWM_OUTPUT); 
	softPwmCreate(GREEN, 0, 100); //pinMode(GREEN, PWM_OUTPUT);
	softPwmCreate(BLUE, 0, 100); //pinMode(BLUE, PWM_OUTPUT);

	//pwmWrite(RED, 1024);
	//pwmWrite(GREEN, 1024);
	//pwmWrite(BLUE, 1024);
	
	signal(SIGINT, cleanup);
}

void fade(int *start, int *end, int pin1, int pin2){
	for(int i = 0; i <= 100; i++){
		*start -= 1; 
		*end += 1;
		softPwmWrite(pin1, *start);
		softPwmWrite(pin2, *end);
		delay(20); // 부드러운 페이드 효과
	}
} 

void loop(){
	int redValue, greenValue, blueValue;
	redValue = 100;
	greenValue = 0;
	blueValue = 0;
	
	/*
	//Red -> Green
	for (int i = 0; i < 1024; i++){
		redValue -= 1;
		greenValue += 1;
		pwmWrite(RED, redValue);  
		pwmWrite(GREEN, greenValue);
		delay(10);
	}

	redValue = 0;
	greenValue = 1024;
	blueValue = 0;
	
	//Green -> Blue
	for (int i = 0; i < 1024; i++){
		greenValue -= 1;
		blueValue += 1;
		pwmWrite(GREEN, redValue);  
		pwmWrite(BLUE, blueValue);
		delay(10);
	}

	redValue = 0;
	greenValue = 0;
	blueValue = 1024;

	//Blue -> Red
	for (int i = 0; i < 1024; i++){
		blueValue -= 1;
		redValue += 1;
		pwmWrite(BLUE, blueValue);  
		pwmWrite(RED, redValue);
		delay(10); 		*/
		
	fade(&redValue, &greenValue, RED, GREEN);
	fade(&greenValue, &blueValue, GREEN, BLUE);
	fade(&blueValue, &redValue, BLUE, RED);
}

int main(){
	setup();
	while (1){
		loop();
	}
	return 0;
}	
