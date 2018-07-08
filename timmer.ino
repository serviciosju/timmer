const int sensor = 8;
const int salida = 10;
const int sensor2 = 3;
const int salida2 = 12;
boolean activado = false;
boolean disparar = false;
unsigned int presento1 = 0;
unsigned int presento2 = 0;

unsigned long tiempo = 0; //Control del tiempo
unsigned long espera = 8000; //Tiempo a esperar o temporizar en milisegundos
unsigned long redisparo = 8000;  // durante este tiempo si hay nuevos disparos del PIR reinicio la temporización.

boolean presento = false;

void setup(){
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(salida, OUTPUT);
  pinMode(sensor2, INPUT);
  pinMode(salida2, OUTPUT);
  digitalWrite(salida, LOW); // Logica inversa de usarse la directa cambiar a LOW
  //digitalWrite(sensor, LOW); // Resistencias PullUp internas
  digitalWrite(salida2, LOW); 

}

void loop(){
  
  if ((digitalRead(sensor) == LOW)&&(digitalRead(sensor2) == HIGH)) {
    presento1++;
    if (presento1 == 1) {
      Serial.println("Disparo sensor.");
    }
    activado = true;
    tiempo = millis();
  } else presento1 = 0;   
  
  
  if (activado) { 
      
     if (((digitalRead(sensor) == LOW) && ( millis() - tiempo < redisparo))&&(digitalRead(sensor2) == HIGH) && ( millis() - tiempo < redisparo)) {
       tiempo = millis();
       presento2++;
       if (presento2 == 1) {
           Serial.print("Hubo redisparo. Tiempo =");
         Serial.println(tiempo);
           Serial.print("Faltan =");
           Serial.println(millis() - tiempo);
       }
     } else presento2 = 0;
       
     if (millis() - tiempo < espera) {
       digitalWrite(salida, LOW); // Para lagica inversa
       digitalWrite(salida2, LOW);
     } else {
       digitalWrite(salida, HIGH);
       digitalWrite(salida2, HIGH);
       activado = false;
     }
    }
}
