#ifndef BUTTON_UTILS_H
#define BUTTON_UTILS_H

#include "global_variables.h"

/* Macro to easily return from a running function if the button is pressed */
#define RETURN_IF_BUTTON_WAS_PRESSED() \
  if (button_pressed)\
  {\
    button_pressed = FALSE;\
    return;\
  }

#endif // BUTTON_UTILS_H
