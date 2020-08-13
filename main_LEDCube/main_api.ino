/**
 * x, z, y
 * x - bit в ячейке 
 * z - полоса от края до меня 
 * y - layer 
 */
void setVoxel(uint8_t x, uint8_t z, uint8_t y) {
  // y - layer
  // z - полоса от края до меня
  // x - bit в ячейке
  cube[y][z] |= (0x01 << x);
}

void renderCube() {
  //  Serial.println("");
  for (uint8_t y = 0; y < cube_size; y++) {
    // 0 layer => 4 bit
    // 1 layer => 5 bit
    // 2 layer => 6 bit
    // 3 layer => 7 bit
    digitalWrite(SS, LOW);
    SPI.transfer(0x01 << y + (8 - cube_size));
    debugTransferBit(0x01 << y + (8 - cube_size));

    for (uint8_t z = 0; z <= 2; z += 2) {
      SPI.transfer(
        getPullFourBits(cube[y][z], cube[y][z + 1])
      );
      //      SPI.transfer(cube[y][z]);
    }
    digitalWrite(SS, HIGH);
    //    delayMicroseconds(50);
    //    delay(150);
  }
}

void clearCube() {
  for (uint8_t i = 0; i < cube_size; i++) {
    for (uint8_t j = 0; j < cube_size; j++) {
      cube[i][j] = 0;
    }
  }
}

void lightCube() {
  for (uint8_t i = 0; i < cube_size; i++) {
    for (uint8_t j = 0; j < cube_size; j++) {
      cube[i][j] = 0xFF;
    }
  }
}


byte getPullFourBits(byte firstValue, byte secondValue) {
  byte value = 0;
  // 0x xxxx____
  for (int i = 7; i >= 4; i--) {
    bitWrite(value, i, bitRead(secondValue, i - cube_size));
  }
  // 0x ____xxxx
  for (int i = 3; i >= 0; i--) {
    bitWrite(value, i, bitRead(firstValue, i));
  }

  return value;
}

uint8_t debugTransferBit(uint8_t value) {
  //  Serial.println(value);
  return value;
}
