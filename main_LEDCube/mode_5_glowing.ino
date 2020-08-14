bool glowing;
uint16_t glowCount = 0;

uint8_t selX = 0;
uint8_t selY = 0;
uint8_t selZ = 0;

void cubeGlowing() {
  if (loading) {
    clearCube();
    glowCount = 0;
    glowing = true;
    loading = false;
  }

  timer++;
  if (timer > modeTimer) {
    timer = 0;
    if (glowing) {
      if (glowCount < 32) {
        do {
          selX = random(0, cube_size);
          selY = random(0, cube_size);
          selZ = random(0, cube_size);
        } while (getVoxel(selX, selZ, selY));
        setVoxel(selX, selZ, selY);
        glowCount++;
      } else if (glowCount < 64) {
        lightCube();
        glowCount++;
      } else {
        glowing = false;
        glowCount = 0;
      }
    } else {
      if (glowCount < 32) {
        do {
          selX = random(0, cube_size);
          selY = random(0, cube_size);
          selZ = random(0, cube_size);
        } while (!getVoxel(selX, selZ, selY));
        clearVoxel(selX, selZ, selY);
        glowCount++;
      } else {
        clearCube();
        glowing = true;
        glowCount = 0;
      }
    }
  }
}
