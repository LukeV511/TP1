## TP1: Idea Proyecto
## Titulo del trabajo: Medidor Inteligente de Energia
#### Alumno: 
Lucas Veglia

#### Objetivo: 
Desarrollar un sistema que permita monitorear el consumo de energía eléctrica residencial

#### Descripción:
El sistema calcula la energía eléctrica consumida por una residencia en tiempo real. Para ello se integra en el tiempo la potencia instantánea, 
calculada a partir de los valores de tensión y corriente, obtenidos de los siguientes sensores comerciales:
- Sensor de Tensión: ZMPT101B (250 V AC max)
- Sensor de Corriente: ACS712 (5A max)
  
Si bien se realizó una calibración previa, faltan realizar calibraciones mas precisas de los sensores utilizados, para la obtención de valores correctos.

La placa utilizada como plataforma de desarrollo fue:

- NUCLEO F429ZI

En esta instancia del trabajo, los datos de tensión, corriente y potencia instantánea son enviados cada 1 milisegundo por el puerto serie, así como también un contador incremental de energía consumida, y un registro de la máxima potencia registrada. Sin embargo, los mismos se muestran en pantalla cada 1 segundo de forma independiente (evitando crear un código bloqueante) . Mediante un botón, el usuario puede resetear el contador de energía y el registro de máxima potencia. Un led indicará que el sistema está en funcionamiento.

![image](https://github.com/LukeV511/TP1/assets/130575845/94b8c5a4-beb4-4e01-a253-b734dfec2141)


Periféricos utilizados en esta instancia del trabajo TP1:
- USER BUTTON: resetea el contador de energía consumida y el registro de máxima potencia
- LED 1: Se encenderá para indicar que el sistema está en funcionamiento
- LED 2: Se encenderá para indicar el reseteo del contador de energía y registro de máxima potencia
- ANALOG IN 1: Se utiliza para leer el valor de la corriente instantánea
- ANALOG IN 2: Se utiliza para leer el valor de la tensión instantánea
- UART: Se utiliza para enviar la información de estado del sistema a la PC

Para alimentar los sensores, se utilizó una salida de 5V de la placa NUCLEO. Para acondicionar la señal saliente de los sensores y evitar que puedan
dañar la placa (que está preparada para recibir como máximo 3,3V) se utilizaron 3 resistencias de 10 Kohm para crear un divisor resistivo para cada señal.

Para que se puedan visualizar los valores en pantalla por comunicacion serial, se debió incluir el archivo mbed_app.json para que la combinación
%2.f sea correctamente interpretada en el compilador.

![image](https://github.com/LukeV511/TP1/assets/130575845/14039133-e906-4d69-9f93-270143cb3eea)

Para instancias futuras del proyecto, se espera poder implementar y presentar en los próximos trabajos prácticos:
- Que los valores que se muestren al usuario sean los valores RMS
- El cálculo del factor de potencia instantáneo
- Un relé que conecte y desconecte automáticamente capacitores para corregir el factor de potencia de la
instalación
- Un led cuya intensidad sea controlada por un PWM, proporcional a la potencia instantánea.
- Un buzzer que alerte cuando se exceda un valor de potencia predefinido
- Bloquear el botón de reseteo y habilitarlo mediante una contraseña introducida por keypad
- Un display LCD que permita visualizar los valores instantáneos de tensión, corriente, potencia y factor de
potencia
- Una app que permita ver los datos y el perfil de carga desde un smartphone/sitio web.






