#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Change this constant if you are using another pin to read button status */
#define BUTTON_PIN     A1
/* Change this constant if you are using another pin to communicate with the leds */
#define DATA_PIN       13
/* The number of leds used. Currently the program expects this value to be an odd number*/
#define NO_OF_PIXELS   7


#define DEBOUNCE_DELAY 250 // in ms

#define NO_OF_LAYERS   ((NO_OF_PIXELS + 1) / 2)
#define MIN_LAYER      0
#define MAX_LAYER      (NO_OF_LAYERS - 1)
#define MIDDLE_PIXEL   (NO_OF_LAYERS - 1)
#define MIN_PIXEL      0
#define MAX_PIXEL      (NO_OF_PIXELS - 1)

#define TRUE           1
#define FALSE          0

#endif // CONSTANTS_H
