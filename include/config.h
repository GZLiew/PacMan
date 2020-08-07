#pragma once

#define LEVEL_MATRIX_HEIGHT 36
#define LEVEL_MATRIX_WIDTH 28

struct Config {
  int windowX = LEVEL_MATRIX_WIDTH * 16;
  int windowY = LEVEL_MATRIX_HEIGHT * 16;
  int fullScreen = false;
  int frameRate = 60;
  double dt = 1;
};