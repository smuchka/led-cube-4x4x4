void cubeBlink() {
  if (loading) {
    clearCube();
    loading = false;
  }
  
  timer++;
  if (timer > modeTimer) {
    timer = 0;
    
    bool onLight = !getVoxel(0, 0, 0);
    clearCube();

    if(onLight) {
      for (uint8_t i = 0; i < cube_size; i++) {
        for (uint8_t j = 0; j < cube_size; j++) {
          cube[i][j] = 0xFF;
        }
      }
    }
  }
}
