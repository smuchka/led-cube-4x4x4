#include <SPI.h>

// MODs
#define CUBE_COLUMN_CIRCLE 1
#define CUBE_COLUMN_CIRCLE_TIME 200

#define CUBE_LIGHT 2
#define CUBE_LIGHT_TIME 200

#define CUBE_BLINK 3
#define CUBE_BLINK_TIME 300

#define CUBE_RAIN 4
#define CUBE_RAIN_TIME 260

#define CUBE_GLOWING 5
#define CUBE_GLOWING_TIME 240

#define CUBE_FILLING 6
#define CUBE_FILLING_TIME 540

#define CUBE_PLANE_MOVING 7
#define CUBE_PLANE_MOVING_TIME 550

// DIRS
#define SHIFT_NEG_Y 1

#define SIDE_X 1
#define SIDE_Y 2
#define SIDE_Z 3

// VARS
const int cube_size = 4;
uint8_t cube[cube_size][cube_size];
int8_t currentEffect;
bool loading;
uint16_t timer;
String modeTitle = "-";
uint16_t modeTimer;

void setup() {
  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, LSBFIRST, SPI_MODE0)); // MSBFIRST

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  loading = true;
  currentEffect = CUBE_PLANE_MOVING;
  changeMode();

  Serial.println("\n  * * * * * * * * * * * * ");
  Serial.print("  * Mode: [");
  Serial.print(currentEffect);
  Serial.print("] ");
  Serial.println(modeTitle);
  Serial.println("  * * * * * * * * * * * * ");
}

void loop() {
   switch (currentEffect) {
    case CUBE_COLUMN_CIRCLE: cubeColumnsCircle(); break;
    case CUBE_LIGHT: cubeLight(); break;
    case CUBE_BLINK: cubeBlink(); break;
    case CUBE_RAIN: cubeRain(); break;
    case CUBE_GLOWING: cubeGlowing(); break;
    case CUBE_FILLING: cubeFilling(); break;
    case CUBE_PLANE_MOVING: cubePlaneMoving(); break;
   }
 
  renderCube();
}

void changeMode() {
  clearCube();
  loading = true;
  timer = 0;

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);

  switch(currentEffect) {
    case CUBE_COLUMN_CIRCLE: 
      modeTimer = CUBE_COLUMN_CIRCLE_TIME; 
      modeTitle = "CUBE_COLUMN_CIRCLE";
    break;
    case CUBE_LIGHT: 
      modeTimer = CUBE_LIGHT_TIME;
      modeTitle = "CUBE_LIGHT";
    break;
    case CUBE_BLINK:
      modeTimer = CUBE_BLINK_TIME;
      modeTitle = "CUBE_BLINK";
    break;
    case CUBE_RAIN:
      modeTimer = CUBE_RAIN_TIME;
      modeTitle = "CUBE_RAIN";
    break;
    case CUBE_GLOWING:
      modeTimer = CUBE_GLOWING_TIME;
      modeTitle = "CUBE_GLOWING";
    break;
    case CUBE_FILLING:
      modeTimer = CUBE_FILLING_TIME;
      modeTitle = "CUBE_FILLING";
    break;
    case CUBE_PLANE_MOVING:
      modeTimer = CUBE_PLANE_MOVING_TIME;
      modeTitle = "CUBE_PLANE_MOVING";
    break;
  }
}
