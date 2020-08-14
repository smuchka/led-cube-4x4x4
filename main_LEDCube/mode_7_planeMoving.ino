uint8_t planeLevel;
uint8_t planeDirection;
void cubePlaneMoving() {
  if (loading) {
    clearCube();
    loading = false;

    planeLevel = 0;
    planeDirection = SIDE_X;
  }
  
  timer++;
  if (timer > modeTimer) {
    timer = 0;
    clearCube();
    plane(planeDirection, planeLevel++);

    if(planeLevel >= cube_size) {
      if(planeLevel) {
        switch(planeDirection) {
          case SIDE_X: planeDirection = SIDE_Y; break;
          case SIDE_Y: planeDirection = SIDE_Z; break;
          case SIDE_Z: planeDirection = SIDE_X; break;
        }
      }
      planeLevel = 0;
    }
  }
}
