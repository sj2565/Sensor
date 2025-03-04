#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

#define PRESSURE_SENSOR 0 

float GetPressure() {
    int raw_value = analogRead(PRESSURE_SENSOR);
    float voltage = (raw_value / 1023.0) * 3.3; 
    float pressure = (voltage / 3.3) * 100.0;
    return pressure;
}

int main() {
    while (1) {
        float pressure = GetPressure();

        printf("{\"pressure\" : %.2f}\n", pressure);
        fflush(stdout);
        usleep(5000);
    }
    return 0;
}
