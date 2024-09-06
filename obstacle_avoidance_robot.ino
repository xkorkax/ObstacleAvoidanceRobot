#include <Servo.h>
#include <Ultrasonic.h>


//definiowanie pinu diody LED
#define LED_PIN 12

//definiowanie pinów silnika 1 
#define m1_input1 13
#define m1_input2 11
#define m1_enablePin 4

//definiowanie pinów silnika 2
#define m2_input3 6
#define m2_input4 5
#define m2_enablePin 9

//definiowanie pinów czujnika i serwa
const int trigPin = 8;
const int echoPin = 7;
const int servoPin = 10;

int distance;
int distance_left;
int distance_right;

//definiowanie kątów obrotu dla serwa
const int leftAngle = 90 - 50;                //obrót w lewo o 50 stopni
const int rightAngle = 90 + 50;               //obrót w prawo o 50 stopni
const int initialAngle = 90;                  //początkowa pozycja serwa

//inicjalizacja obiektu serwa oraz czujnika ultradźwiękowego
Servo myservo;
Ultrasonic ultrasonic(trigPin, echoPin);

bool obstacleDetected = false;                //flaga informująca, czy przeszkoda została wykryta



//-----FUNCTIONS-----------

void stop()
{
  //wyłączenie zasilania mostka H
  digitalWrite(m1_enablePin, LOW);
  digitalWrite(m2_enablePin, LOW);
}

void go()
{
    //włączenie zasilania mostka H
    digitalWrite(m1_enablePin, HIGH);
    digitalWrite(m2_enablePin, HIGH);
}


void drive_forward()
{ 
    stop();
    //ustawienie silnika w tryb jazdy do przodu 
    digitalWrite(m1_input1, LOW);
    digitalWrite(m1_input2, HIGH);
    digitalWrite(m2_input3, HIGH);
    digitalWrite(m2_input4, LOW);
    go();
}

void go_backwards()
{
    stop();
    //ustawianie silnika w tryb jazdy do tylu
    digitalWrite(m1_input1, HIGH);
    digitalWrite(m1_input2, LOW);
    digitalWrite(m2_input3, LOW);
    digitalWrite(m2_input4, HIGH);
    go();
}

void turn_right()
{ 
    stop();
    digitalWrite(m1_input1, LOW); //P
    digitalWrite(m1_input2, HIGH);  //P
    digitalWrite(m2_input3, LOW); //L
    digitalWrite(m2_input4, HIGH);  //L
    go();
}

void turn_left()
{ 
    stop();
    digitalWrite(m1_input1, HIGH);
    digitalWrite(m1_input2, LOW);
    digitalWrite(m2_input3, HIGH);
    digitalWrite(m2_input4, LOW);
    go();
}


void setup() 
{
  pinMode(LED_PIN, OUTPUT);                 //inicjalizacja diody

  myservo.attach(servoPin);                 //inicjalizacja serwa
  myservo.write(initialAngle);              //ustawienie serwa na pozycję początkową 

  //ustawienie trybów pinów silnika 1
  pinMode(m1_enablePin, OUTPUT);
  pinMode(m1_input1, OUTPUT);
  pinMode(m1_input2, OUTPUT);
  digitalWrite(m1_enablePin, LOW);          //wyłącz mostek H na początku

  //ustawienie trybów pinów silnika 2
  pinMode(m2_enablePin, OUTPUT);
  pinMode(m2_input3, OUTPUT);
  pinMode(m2_input4, OUTPUT);
  digitalWrite(m2_enablePin, LOW);          //wyłącz mostek H na początku
  
  Serial.begin(9600);                       //inicjalizacja monitora szeregowego
}



void loop() 
{
  //sprawdzenie, czy przeszkoda została wykryta
  if (!obstacleDetected) {

    drive_forward();
    distance = ultrasonic.read();
    
    //wyświetlanie odległości na monitorze szeregowym
    Serial.print(distance);
    Serial.println(" cm");
    
    //sprawdzenie, czy odległość jest mniejsza niż 35 cm
    if (distance < 35) 
    {
      //jeśli tak --> ustaw flagę na true
      obstacleDetected = true;
    }

  } else  
  {
    //kod dla wykrycia kolizji
    digitalWrite(LED_PIN, HIGH);        //zapalenie diody sygnalizujacej wykrycie przeszkody

    stop();                             //zatrzymanie robota
    delay(500);                         //opoznienie

    //jeśli przeszkoda została wykryta, wykonaj obroty serwa, zdecyduj w ktora strone jechac dalej i zresetuj flagę

    go_backwards();                     //cofnij sie kawałek
    delay(400);                         //opoznienie
    //delay(200);

    stop();                             //zatrzymanie robota
    delay(500);                         //opoznienie

    myservo.write(leftAngle);
    delay(700);                         //opoznienie
    distance_left = ultrasonic.read();  //zmierz odleglosc w lewo
    Serial.print("lewo: ");
    Serial.print(distance_left);
    Serial.print("\n");

    myservo.write(rightAngle);
    delay(700);                         //poczekaj x sekundy
    distance_right = ultrasonic.read(); //zmierz odleglosc w prawo
    Serial.print("prawo: ");
    Serial.print(distance_right);
    Serial.print("\n");

    myservo.write(initialAngle);      //powrót do początkowej pozycji
    delay(500);                       //opoznienie



    if(distance_left >= distance_right)
    {
      turn_left();                    //skrec w lewo 
      delay(100);                     //opoznienie
    }
    else 
    {
      turn_right();                   //skrec w prawo
      delay(100);                     //opoznienie
    }

    obstacleDetected = false;         //resetowanie flagi
    digitalWrite(LED_PIN, LOW);       //wyłączenie diody sygnalizujacej wykrycie przeszkody
  }

  delay(100);                         //czekanie przed kolejnym pomiarem
}
