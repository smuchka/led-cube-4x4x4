void cubeRain() {
  if (loading) {
    clearCube();
    loading = false;
  }
  
  timer++;
  if (timer > modeTimer) {
    timer = 0;

    shift(SHIFT_NEG_Y);
    uint8_t numDrops = random(0, 3);
    for (uint8_t i = 0; i < numDrops; i++) {
      setVoxel(random(0, cube_size), random(0, cube_size), cube_size - 1);
    }
  }
}
