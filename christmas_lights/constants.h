#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BUTTON_PIN     A1
#define DEBOUNCE_DELAY 250 // in ms

#define DATA_PIN       13
#define NO_OF_PIXELS   7

#define NO_OF_LAYERS   ((NO_OF_PIXELS + 1) / 2)
#define MIDDLE_PIXEL   (NO_OF_LAYERS - 1)
#define MIN_PIXEL      0
#define MAX_PIXEL      (NO_OF_PIXELS - 1)

#define TRUE           1
#define FALSE          0

#endif // CONSTANTS_H
