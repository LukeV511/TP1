#include "mbed.h"

//defines

AnalogIn VoltageSensor(A0);
AnalogIn CurrentSensor(A1);

UnbufferedSerial uartUsb(USBTX, USBRX, 9600);

float vsensitivity = 1/110.5;
float isensitivity = 0.2;

float TIME_INCREMENT_MS = 1;

//main code

int main()
{   
    float accumulated_time = 0;
    float energy = 0;
    
    DigitalIn B1_USER(BUTTON1);

    DigitalOut LD1(LED1);
    LD1 = 1;

    while (true) {
        
        float voltage = VoltageSensor.read();
        float current = CurrentSensor.read();

        float Voltage = (voltage-0.606)/vsensitivity; 
        float Current = (current-0.5)/isensitivity;

        float Power = Voltage * Current;

        float energy = energy + (Power * TIME_INCREMENT_MS) ;

        accumulated_time = accumulated_time + TIME_INCREMENT_MS;

        if (accumulated_time == (1000*Power)) {
        
            char str[100];
            sprintf(str, "Voltaje: %.2f V, Corriente: %.2f A, Potencia: %.2f W, Energia: %.2f KWh \r\n", Voltage, Current, Power, energy);
            uartUsb.write(str, strlen(str));
            float accumulated_time = 0;
        }
        if (B1_USER == 1) {
        float energy = 0;
        }
        
        ThisThread::sleep_for(TIME_INCREMENT_MS);

    }
}