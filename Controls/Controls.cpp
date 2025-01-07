#include "Controls.h"

Controls::Controls(int leftPin_, int rightPin_, int upPin_, int downPin_,
                   int APin_, int BPin_) {
  leftPin = leftPin_;
  rightPin = rightPin_;
  upPin = upPin;
  downPin = downPin_;
  APin = APin_;
}

void Controls::leftCallback(int gpio, int level, uint32_t tick,
                            void* userData) {
  // Cast the userData back to Controls* and call setLeft
  Controls* self = static_cast<Controls*>(userData);
  self->leftPin = level;
}

void Controls::rightCallback(int gpio, int level, uint32_t tick,
                             void* userData) {
  // Cast the userData back to Controls* and call setLeft
  Controls* self = static_cast<Controls*>(userData);
  self->rightPin = level;
}

void Controls::downCallback(int gpio, int level, uint32_t tick,
                            void* userData) {
  // Cast the userData back to Controls* and call setLeft
  Controls* self = static_cast<Controls*>(userData);
  self->downPin = level;
}

void Controls::upCallback(int gpio, int level, uint32_t tick, void* userData) {
  // Cast the userData back to Controls* and call setLeft
  Controls* self = static_cast<Controls*>(userData);
  self->upPin = level;
}

void Controls::ACallback(int gpio, int level, uint32_t tick, void* userData) {
  // Cast the userData back to Controls* and call setLeft
  Controls* self = static_cast<Controls*>(userData);
  self->APin = level;
}

void Controls::BCallback(int gpio, int level, uint32_t tick, void* userData) {
  // Cast the userData back to Controls* and call setLeft
  Controls* self = static_cast<Controls*>(userData);
  self->BPin = level;
}

// return -1 when initilization failed
int Controls::initilizeControls() {
  if (gpioInitialise() == PI_INIT_FAILED ||
      gpioSetMode(leftPin, PI_INPUT) != 0 ||
      gpioSetMode(rightPin, PI_INPUT) != 0 ||
      gpioSetMode(downPin, PI_INPUT) != 0 ||
      gpioSetMode(upPin, PI_INPUT) != 0 || gpioSetMode(APin, PI_INPUT) != 0 ||
      gpioSetMode(BPin, PI_INPUT) != 0 ||
      gpioSetAlertFuncEx(leftPin, leftCallback, this) != 0 ||
      gpioSetAlertFuncEx(rightPin, rightCallback, this) != 0 ||
      gpioSetAlertFuncEx(downPin, downCallback, this) != 0 ||
      gpioSetAlertFuncEx(upPin, upCallback, this) != 0 ||
      gpioSetAlertFuncEx(APin, ACallback, this) != 0 ||
      gpioSetAlertFuncEx(BPin, BCallback, this) != 0) {
    return -1;
  }

  return 0;
}

int Controls::getKeyPressed() {
  if (leftLevel) {
    return LEFT;
  } else if (rightLevel) {
    return RIGHT;
  } else if (downLevel) {
    return DOWN;
  } else if (upLevel) {
    return UP;
  } else if (ALevel) {
    return A;
  } else if (B) {
    return B;
  }

  return 0;
}
