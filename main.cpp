#include "mbed.h"

//defines

AnalogIn VoltageSensor(A0);
AnalogIn CurrentSensor(A1);

UnbufferedSerial uartUsb(USBTX, USBRX, 9600);

float vsensitivity = 1/110.5;
float isensitivity = 0.2;

//main code

int main()
{
    while (true) {
        float voltage = VoltageSensor.read();
        float current = CurrentSensor.read();

        float Voltage = (voltage-0.606)/vsensitivity; 
        float Current = (current-0.5)/isensitivity;

        float Power = Voltage * Current;
        
        char str[100];
        sprintf(str, "Voltaje: %.2f V, Corriente: %.2f A, Potencia: %.2f W \r\n", Voltage, Current, Power);
        
        uartUsb.write(str, strlen(str));
        
        ThisThread::sleep_for(1ms);

    }
}