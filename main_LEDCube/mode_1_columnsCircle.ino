uint8_t column[] = {0, 0};
//uint8_t columns[4][2] = {
//  {0, 0},
//  {3, 0},
//  {3, 3},
//  {0, 3},
//};

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
