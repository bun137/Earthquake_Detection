#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

int buzzerPin = D2; // Define the buzzer pin
int ledPin = D4;    // Define the LED pin
int pushButtonPin = D1; // Define the push button pin

Adafruit_MPU6050 mpu;

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

int melody[] = {
  NOTE_E7,-4, NOTE_E7,-4, 0,-4, NOTE_E7,-4, 0,-4, NOTE_E7,-4, 0,-4, NOTE_E7,-4, NOTE_G7,-4,
  0,-4, NOTE_C7,-4, 0,-4, NOTE_G6,-4, 0,-4, 0, 0, 0, 0,
  NOTE_G6,-4, 0,-4, 0,-4, 0, 0, NOTE_G6,-4, 0,-4, 0,-4, 0,-4,
  NOTE_G6,-4, 0,-4, 0,-4, 0, 0, NOTE_G6,-4, 0,-4, 0,-4, 0,-4,
  NOTE_G6,-4, NOTE_A6,-4, 0,-4, NOTE_B6,-4, 0,-4, NOTE_AS6,-4, NOTE_A6,-4, 0,-4, NOTE_G6,-4,
  NOTE_E7,-4, NOTE_G7,-4, NOTE_A7,-4, 0,-4, NOTE_F7,-4, NOTE_G7,-4, 0,-4, NOTE_E7,-4, 0,-4,
  NOTE_C7,-4, NOTE_D7,-4, NOTE_B6,-4, 0,-4, 0, 0, 0, 0
};

int noteDuration = 1200 / 16; // Set the tempo

void playMarioTheme() {
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote += 2) {
    int note = melody[thisNote];
    int duration = melody[thisNote + 1] * noteDuration;

    if (note == 0) {
      delay(duration);
    } else {
      tone(buzzerPin, note, duration);
      delay(duration);
      noTone(buzzerPin);
    }
    
    // Add a slight pause between notes
    delay(noteDuration / 10);
  }
}



float prevx = -0.5;
float prevy = 0.15;
float prevz = 10.9;


void setup(void) {
  Serial.begin(115200);
  Serial.begin(9600);

   // use Serial3 on TX3 and RX3 pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(pushi, INPUT_PULLUP);


  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void loop() {


  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float ax = a.acceleration.x;
  float ay = a.acceleration.y;
  float az = a.acceleration.z;
  float gx = g.gyro.x;
  float gy = g.gyro.y;
  float gz = g.gyro.z;

  float tx = temp.temperature;
  Serial.print("the lovely temp in IC is: ");
  Serial.println(tx);

  /* Print out the values */
  // Serial.print("Acceleration X: ");
  // Serial.print(ax);
  // Serial.print(", Y: ");
  // Serial.print(ay);
  // Serial.print(", Z: ");
  // Serial.print(az);
  // Serial.println(" m/s^2");

  // Serial.println(digitalRead(pushi));

  // Serial.print("Gyro X: ");
  // Serial.print(gx);
  // Serial.print(", Y: ");
  // Serial.print(gy);
  // Serial.print(", Z: ");
  // Serial.print(gz);
  // Serial.println("rad");

  float diffx = ax - prevx;
  float diffy = ay - prevy;
  float diffz = az - prevz;

  prevx = ax;
  prevy = ay;
  prevz = az;

  // Serial.print("diff  X: ");
  // Serial.print(abs(diffx));
  // Serial.print(", Y: ");
  // Serial.print(abs(diffy));
  // Serial.print(", Z: ");
  // Serial.print(abs(diffz));
  // Serial.println(" m/s^2");


  if((abs(diffx) > 0.5 || abs(diffy) > 0.5 || abs(diffz) > 0.5) && (!digitalRead(pushi))) {
    Serial.write("1");
    Serial.println("EARTHQUAKEEEE is heree, go under the table :sus:!");
    Serial.println("EARTHQUAKEEEE is heree, go under the table :sus:!");
    Serial.println("EARTHQUAKEEEE is heree, go under the table :sus:!");

       for (int i = 0; i <= 2000; i += 20) {
         analogWrite(led,(i/7.85));
         tone(buzzerPin, i);
         delay(10);
       }
       for (int i = 2000; i >= 0; i -= 20) {
         analogWrite(led,(i/7.85)); 
         tone(buzzerPin, i);
         delay(10);
       }
      noTone(buzzerPin);

      // playMarioTheme();
      delay(100);
      }
  

  delay(100);
 }
