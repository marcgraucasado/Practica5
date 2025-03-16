# PR5-MarcGrau  

## PRÁCTICA 5: Buses de Comunicación I (Introducción y I2C)

#### Ejercicio Practico 1 ESCÁNER I2C
```
cpp
#include <Arduino.h>
#include <Wire.h>

void setup() {
    Wire.begin();
    Serial.begin(115200);
    while (!Serial) {
        // Leonardo: wait for serial monitor
    }
    Serial.println("\nI2C Scanner");
}

void loop() {
    byte error, address;
    int nDevices = 0;
    Serial.println("Scanning...");

    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            nDevices++;
            Serial.print("I2C device found at address 0x");
            if (address < 16) Serial.print("0");
            Serial.println(address, HEX);
        }
    }
}
```

Descripción y funcionamiento:

Este programa es un escáner o herramienta de reconocimiento de periféricos conectados a un bus I2C.

Para determinar la cantidad de periféricos conectados a nuestro bus (objetivo del escáner), enviaremos señales a las 128 direcciones posibles (ya que el bus I2C utiliza direcciones de 7 bits para los dispositivos esclavos) con el fin de recibir una respuesta en alguna de estas direcciones. Si recibimos una respuesta, sabremos que hay un dispositivo conectado al bus y también obtendremos su dirección para poder comunicarnos con él. Debido a las resistencias de pull-up que tiene el bus I2C, el circuito normalmente está en alta impedancia, así que si acertamos la dirección de un periférico, lo sabremos porque el periférico alterará esta alta impedancia. En el programa, interpretaremos esta variación como un '0'.

A continuación, explico cómo funciona el programa y la salida que obtenemos por el puerto serie tras su ejecución:

Al inicio del código, como es habitual, incluimos la librería Arduino.h (ya que estamos programando en un entorno tipo Arduino y esto puede prevenir problemas) y, como novedad, incluimos la librería Wire.h. Esta última librería nos permitirá comunicarnos sobre el bus I2C, iniciando y terminando transmisiones en diferentes direcciones.

Más adelante, en el void_setup(), inicializamos el puerto serie (como siempre) y el bus I2C usando la instancia "Wire.begin;". Luego encontramos un bucle while: "while (!Serial)". Este se ejecutará hasta que el puerto serie esté listo; después de esto, escribe "\nI2C Scanner" en el puerto serie, indicándonos que el puerto serie está operativo y que el escáner se está iniciando.

El escáner comienza en el void_loop(). Como mencioné al principio, necesitamos enviar señales a todas las direcciones posibles de dispositivos en el bus y ver si obtenemos respuesta de algún periférico. Esto lo haremos con un bucle for. Para que el bucle funcione, necesitamos declarar una serie de variables: nDevices (tipo int, que define la cantidad de periféricos conectados), error (tipo byte, que indicará si ha encontrado un dispositivo en una dirección dada) y address (tipo byte, donde almacenaremos las direcciones). El bucle terminará cuando haya comprobado todas las direcciones, es decir, empieza comprobando la dirección 00000000 y suma +1 en binario hasta llegar a la última, la 01111111 (el primer 0 se debe a que la variable byte es de 8 bits y las direcciones son de 7 bits).

La función Wire.beginTransmission(address), inicia una transmisión hacia un dispositivo en el bus I2C.
  Address: es el argumento que especifica la dirección del dispositivo al que se enviarán los datos

La función Wire.endTransmission(), finaliza la transmisión I2C y envía los datos almacenados. Devuelve un valor que indicará el estado de transmisión

0: éxito
1: error de datos
2: error de dirección
3: otro error

Iteramos a través de las direcciones de los dispositivos I2C del 1 al 127, inicializando nDevices en 0.
```
nDevices = 0;
for(address = 1; address < 127; address++)
```
Finalmente, se comprueba si hubo errores, si error == 0, significa que hay un dispositivo conectado a esa dirección. Si se detecta un dispositivo, se incrementa el contador nDevices.

### Ejercicio práctico 2

