#pragma once

#include <pigpio.h>

#include <atomic>

#define LEFT 1
#define RIGHT 2
#define DOWN 3
#define UP 4
#define A 5
#define B 6

class Controls {
 private:
  int leftPin;
  int rightPin;
  int upPin;
  int downPin;
  int APin;
  int BPin;

  int leftLevel;
  int rightLevel;
  int upLevel;
  int downLevel;
  int ALevel;
  int BLevel;

  static void leftCallback(int gpio, int level, uint32_t tick, void* userData);
  static void rightCallback(int gpio, int level, uint32_t tick, void* userData);
  static void downCallback(int gpio, int level, uint32_t tick, void* userData);
  static void upCallback(int gpio, int level, uint32_t tick, void* userData);
  static void ACallback(int gpio, int level, uint32_t tick, void* userData);
  static void BCallback(int gpio, int level, uint32_t tick, void* userData);

 public:
  Controls(int leftPin_, int rightPin_, int upPin_, int downPin_, int APin_,
           int BPin_);
  int initilizeControls();
  int getKeyPressed();
};
