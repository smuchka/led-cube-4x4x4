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

bool getVoxel(uint8_t x, uint8_t z, uint8_t y) {
  return bitRead(cube[y][z], x) == 1;
}

void clearVoxel(uint8_t x, uint8_t z, uint8_t y) {
  cube[cube_size - 1 - y][cube_size - 1 - z] ^= (0x01 << x);
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

void shift(uint8_t dir) {
  if (dir == SHIFT_NEG_Y) {
    for (uint8_t y = 0; y < cube_size-1; y++) {
      for (uint8_t z = 0; z < cube_size; z++) {
        cube[y][z] = cube[y + 1][z];
      }
    }
    for (uint8_t i = 0; i < cube_size; i++) {
      cube[cube_size-1][i] = 0;
    }
  }
}

void plane(uint8_t dir, uint8_t level) {
  switch(dir) {
    case SIDE_X: 
      for (uint8_t y = 0; y < cube_size; y++) {
        for (uint8_t z = 0; z < cube_size; z++) {
          cube[y][z] = 0x01 << level;
        }
      }
    break;
    
    case SIDE_Y: 
      for (uint8_t i = 0; i < cube_size; i++) {
        cube[level][i] = 0xFF;
      }
    break;
    
    case SIDE_Z: 
      for (uint8_t i = 0; i < cube_size; i++) {
        cube[i][level] = 0xFF;
      }
    break;
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
