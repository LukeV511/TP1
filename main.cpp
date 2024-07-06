#include "mbed.h"
//REVISION PENDIENTE 06/07/2024
//defines

AnalogIn VoltageSensor(A0); //Sensores de tension y corriente en entradas analogicas
AnalogIn CurrentSensor(A1);

UnbufferedSerial uartUsb(USBTX, USBRX, 9600); //configuracion comunicacion UART

float vsensitivity = 1/110.5; //sensibilidad para calibrar sensores. (Siguen en etapa de pruebas y correccion)
float isensitivity = 0.185;

float TIME_INCREMENT_MS = 1.0; //delay entre lecturas de sensores

//main code

int main()
{   
    float accumulated_time = 0; //inicializador de contador de tiempo
    float energy = 0; //inicializador de contador de energia
    float MaxPower = 0; //inicializador de registro de Maxima Potencia
    
    DigitalIn B1_USER(BUTTON1); //boton integrado de la placa a usar para resetear contador de energia

    DigitalOut LD1(LED1); //LED integrado de la placa a usar para indicar programa corriendo
    DigitalOut LD3(LED3); //LED integrado de la placa a usar para indicar reseteo de energia
    

    while (true) {
        
        
        float voltage = VoltageSensor.read(); //adquisicion de valores de los sensores
        float current = CurrentSensor.read();

        float Voltage = (voltage-0.606)*3.3/vsensitivity;  //calibracion de valores
        float Current = (current-0.5)*3.3/isensitivity;
        float Power = Voltage * Current; // calculo de potencia instantanea y registro de maxima potencia
        if (Power>MaxPower)
        {
            MaxPower=Power;
        }

        float energy = energy + (Power * TIME_INCREMENT_MS/3600000) ; //conversion de potencia a energia en KWh

        accumulated_time = accumulated_time + TIME_INCREMENT_MS; //contador de tiempo

        if (accumulated_time == (1000*TIME_INCREMENT_MS)) // print en serial monitor cada un segundo
        { 
            char str[100];
            sprintf(str, "Voltaje: %.2f V, Corriente: %.2f A, Potencia: %.2f W \r\n Energia: %.2f KWh, Maxima Potencia %.2f W \r\n", Voltage, Current, Power, energy, MaxPower);
            uartUsb.write(str, strlen(str));
            accumulated_time = 0.0;
        }
        if (B1_USER == 1) //reseteo de contador de energia y registro de maxima potencia mediante boton
        {
        energy = 0.0;
        MaxPower = 0.0;
        LD1 = 0;
        LD3 = 1;
        }
        else {
        LD1 = 1;
        LD3 = 0;
        }

        ThisThread::sleep_for(TIME_INCREMENT_MS); //delay entre lecturas. El programa lee cada 1ms,
        //independientemente del print cada 1s

    }
}
