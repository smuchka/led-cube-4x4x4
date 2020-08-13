#include <SPI.h>

// MODs
#define CUBE_COLUMN_CIRCLE 1
#define CUBE_COLUMN_CIRCLE_TIME 200

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
  currentEffect = CUBE_COLUMN_CIRCLE;
  
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
  }
}



// uint8_t column[] = {0, 0};
uint8_t columns[4][2] = {
 {0, 0},
 {3, 0},
 {3, 3},
 {0, 3},
};

uint8_t x; // 0-index
uint8_t z; // 1-index
bool dir;

void cubeColumnsCircle() {
  
  if (loading) {
    clearCube();
    loading = false;    

    x = 0;
    z = 0;
    dir = true;
  }

  timer++;
  if (timer > modeTimer) {
    timer = 0;
    clearCube();
    
    Serial.print(x);
    Serial.print(" ");
    Serial.println(z);
    
    if(dir) {
      
      if(x+1 < cube_size) {
        x++;
      } else {
        x = 3;
        z++;
      
        if(z+1 >= cube_size) {
          dir = !dir;
          Serial.print(" <- ");
        }
      }
    } else {
      if(x > 0) {
        x--;
      } else {
        x = 0;
        z--;
      
        if(z == 0) {
          dir = !dir;
          Serial.print(" -> ");
        }
      }
   }

   for (uint8_t y = 0; y < cube_size; y++) { 
      setVoxel(x, z, y);
   }

   Serial.print(".");
  }
}

