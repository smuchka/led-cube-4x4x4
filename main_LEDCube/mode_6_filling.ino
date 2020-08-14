uint8_t ix;
uint8_t iz;
uint8_t iy;
uint8_t xPos;
uint8_t zPos;
uint8_t yPos;
uint8_t randDir;

void cubeFilling() {
  if (loading) {
    clearCube();
    loading = false;

    // start point random corner
    ix = random(0, 2) * cube_size - 1;
    iy = random(0, 2) * cube_size - 1;
    iz = random(0, 2) * cube_size - 1;
    xPos = ix;
    yPos = iy;
    zPos = iz;
  }

  timer++;
  if (timer > modeTimer) {
    timer = 0;

    uint8_t count = 0;

    do {
      count++;
      randDir = random(0, 4);

      // dir=0
      switch(randDir) {
        case 0:
          xPos = random(
            xPos > 0  ? xPos - 1 : xPos,
            xPos < cube_size - 1 ? xPos + 1 : xPos
          );
        break;
        case 1:
          yPos = random(
            yPos > 0  ? yPos - 1 : yPos,
            yPos < cube_size - 1 ? yPos + 1 : yPos
          );
        break;
        case 2:
          zPos = random(
            zPos > 0  ? zPos - 1 : zPos,
              zPos < cube_size - 1 ? zPos + 1 : zPos
          );
        break;
      }
    } while (count < 15 && getVoxel(xPos, zPos, yPos));

//    Serial.print(xPos);
//    Serial.print(" ");
//    Serial.print(zPos);
//    Serial.print(" ");
//    Serial.println(yPos);
    
    if(count == 15) {
      loading = true;
    } else {
      ix = xPos;
      iy = yPos;
      iz = zPos;
      setVoxel(ix, iz, iy);
    }
  }
}
