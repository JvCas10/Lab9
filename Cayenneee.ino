#include <CayenneMQTTSerial.h>
#include <Servo.h>
// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
/*
Este ejemplo muestra cómo conectarse a Cayenne mediante una conexión USB serie y enviar/recibir datos de muestra.

Se requiere la biblioteca CayenneMQTT para ejecutar este boceto. Si aún no lo ha hecho, puede instalarlo desde Arduino IDE Library Manager.

Esto requiere el uso de la conexión USB serie, por lo que no puede utilizar el dispositivo serie para
imprimiendo mensajes. Si necesita imprimir, puede usar SoftwareSerial y conectar otro dispositivo
para leer mensajes a través de los pines SoftwareSerial.

Para que esto funcione, debe ejecutar el script de conexión en la máquina a la que está conectado el Arduino.
Los scripts se encuentran en la carpeta extras\scripts en la carpeta de la biblioteca principal. Esto redirige el tráfico.
del Arduino al servidor Cayenne.

Pasos:
1. Configure la información de autenticación de Cayenne para que coincida con la información de autenticación del Tablero.
2. Compile y cargue este boceto.
3. Inicie el script de conexión como se describe a continuación para Windows o Linux/OSX.

Ventanas:
1. Abra la línea de comandos de Windows (cmd.exe)
2. Navegue a la carpeta de scripts escribiendo "cd [ruta]", p. "cd C:\Users\[Su nombre de usuario]\Documentos\Arduino\libraries\CayenneMQTT\extras\scripts"
3. Ejecute el script escribiendo "cayenne-ser.bat -c COM4" (donde COM4 es el puerto serial de Arduino) y presionando Enter
 
Linux y OSX:
    ./cayenne-ser.sh (es posible que deba ejecutarse con sudo)
    
Puede especificar el puerto, la velocidad en baudios y el punto final del servidor de esta manera:
    ./cayenne-ser.sh -c <puerto serie> -b <tasa de baudios> -s <dirección del servidor> -p <puerto del servidor>

    Por ejemplo :
      ./cayenne-ser.sh -c /dev/ttyACM0 -b 9600 -s mqtt.mydevices.com -p 1883

    Ejecute cayenne-ser.sh -h para obtener más información

    Asegúrese de seleccionar el puerto serie correcto (puede haber varios).

¡ATENCIÓN!
No use Serial para mostrar ninguna salida en este boceto. Interferirá con la serie.
Conexión USB. Al cargar bocetos, el IDE de Arduino puede quejarse con "el programador está
no responde" o "Acceso denegado". Deberá finalizar el script de conexión
antes de cargar nuevos bocetos ya que bloquea el acceso al puerto Serial. También asegúrese de
el Serial Monitor está deshabilitado en el IDE ya que eso puede evitar que Arduino
conectarse a la máquina Windows/Linux/OSX. Si usa Visual Micro para Visual Studio, haga
Asegúrese de que la depuración automática esté deshabilitada. De lo contrario, el monitor serie puede interferir con el
Conexión en serie.
*/

char username[] = "ec921e90-f5dd-11ed-9ab8-d511caccfe8c";
char password[] = "c55ab7b884520d7f2428bf340d6d7728e4222036";
char clientID[] = "f5b809d0-f5dd-11ed-8485-5b7d3ef089d0";

int vent = 3;
int led = 5;
int led2 = 9;
int led3 = 10;
int servo = 11; 


int value= 0;
int a=0;

Servo myservo;

void setup() {
  Cayenne.begin(username, password, clientID);
  pinMode(led, OUTPUT);
  pinMode(vent, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(servo, OUTPUT);

  digitalWrite(led, LOW);
  digitalWrite(vent, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  pinMode(servo, LOW);

  myservo.attach(11);
}

void loop() {
  Cayenne.loop();
}


CAYENNE_IN(0) {
  digitalWrite(led, getValue.asInt());
}

CAYENNE_IN(1) {
  digitalWrite(vent, getValue.asInt());
}

CAYENNE_IN(2){
  digitalWrite(led, getValue.asInt());
  digitalWrite(vent, getValue.asInt());
  digitalWrite(led2, getValue.asInt());
  digitalWrite(led3, getValue.asInt());
}

CAYENNE_IN(3)
{
	value = getValue.asInt(); // 0 to 255
  if (value==0){
	  //CAYENNE_LOG("Channel %d, pin %d, value %d", 3, 3, 255);
	  // Write the value received to the PWM pin. analogWrite accepts a value from 0 to 255.
	  analogWrite(led, 0);
    analogWrite(led2, 0);
    analogWrite(led3, 0);
    analogWrite(vent, 0);
    myservo.write(180);

  }
  if (value>=63){
	  CAYENNE_LOG("Channel %d, pin %d, value %d", 3, 3, 255);
	  // Write the value received to the PWM pin. analogWrite accepts a value from 0 to 255.
	  analogWrite(led, 0);
    analogWrite(led2, 0);
    analogWrite(led3, 255);
    analogWrite(vent, 0);
    myservo.write(120);
    
  }
  if (value>=126){
	  CAYENNE_LOG("Channel %d, pin %d, value %d", 3, 3, 255);
	  // Write the value received to the PWM pin. analogWrite accepts a value from 0 to 255.
	  analogWrite(led, 0);
    analogWrite(led2, 255);
    analogWrite(led3, 255);
    analogWrite(vent, 0);
    myservo.write(70);
  }
    if (value>=189){
	  CAYENNE_LOG("Channel %d, pin %d, value %d", 3, 3, 255);
	  // Write the value received to the PWM pin. analogWrite accepts a value from 0 to 255.
	  analogWrite(led, 255);
    analogWrite(led2, 255);
    analogWrite(led3, 255);
    analogWrite(vent, 0);
    myservo.write(30);
  }
    if (value==255){
	  //CAYENNE_LOG("Channel %d, pin %d, value %d", 3, 3, 255);
	  // Write the value received to the PWM pin. analogWrite accepts a value from 0 to 255.
	  analogWrite(led, 255);
    analogWrite(led2, 255);
    analogWrite(led3, 255);
    analogWrite(vent, 255);
    myservo.write(0);
  }
}

// This function is called at intervals to send data to Cayenne and keep the device online.
// Will create a temporary green widget on Channel 0, make it permanent by clicking on '+'. 
CAYENNE_OUT(3)
{
	CAYENNE_LOG("Send data for Virtual Channel 0");
	// This command writes the device's uptime in seconds to the Virtual Channel. 
	Cayenne.virtualWrite(3, millis() / 1000);
  Cayenne.virtualWrite(3, value, TYPE_TEMPERATURE, UNIT_CELSIUS);
}

CAYENNE_IN(4) {
  digitalWrite(led2, getValue.asInt());
}

CAYENNE_IN(5) {
  digitalWrite(led3, getValue.asInt());
}

