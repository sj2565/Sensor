#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdint.h>

#define SPI_CHANNEL 0  // SPI 채널 (CEO 사용)
#define SPI_SPEED 1000000  // 1MHz 속도
#define LM35_CHANNEL 0  // MCP3008의 0번 채널 사용

float GetLM35(){
	uint8_t buffer[3];
    int adc_value;
    float voltage, temperature;
	
	buffer[0] = 1; // MCP3008 시작 비트
    buffer[1] = (8 + LM35_CHANNEL) << 4; // 채널 선택
    buffer[2] = 0;
    
    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);
    
     // 10비트 ADC 값 변환
    adc_value = ((buffer[1] & 3) << 8) + buffer[2];

    // 전압 변환 (3.3V 기준)
    voltage = (adc_value * 3.3) / 1023.0;

    // 온도 변환 (LM35는 10mV/C)
    temperature = voltage * 100.0;

    return temperature;
}

int main() {
    if (wiringPiSetup() == -1 || wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
        fprintf(stderr, "SPI 초기화 실패!\n");
        return 1;
    }

    while (1) {
        float temperature = GetLM35();
        printf("LM35 온도 : %.2fC\n", temperature);
        delay(1000); // 1초마다 측정
    }
    return 0;
}
