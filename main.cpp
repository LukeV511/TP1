#include "mbed.h"

//defines

AnalogIn VoltageSensor(A0);
AnalogIn CurrentSensor(A1);

UnbufferedSerial uartUsb(USBTX, USBRX, 9600);

float vsensitivity = 1/125.2;
float isensitivity = 0.185;

//main code

int main()
{
    while (true) {
        float voltage = VoltageSensor.read();
        float current = CurrentSensor.read();

        float Voltage = ((voltage * 5.000/1023.000)-2.5)/vsensitivity; 
        float Current = ((current * 5.000/1023.000)-2.5)/isensitivity;

        float Power = Voltage * Current;
        
        char str[100];
        sprintf(str, "Voltage: %.2f V \r\n", Voltage);
        
        uartUsb.write(str, strlen(str));
        
        ThisThread::sleep_for(500ms);
    }
}