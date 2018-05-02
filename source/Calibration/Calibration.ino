
/* Calibration.ino 
 *
 * Purpose: 
 *    To determine the logistic regression coefficients
 *  By:   Ashton Stephens
 *  Date: 3/8/18
 */
 
#define CALIBRATION_PIN 21
#define BLUE_LED_PIN 37
#define  RED_LED_PIN 39

#define   SENSOR_PIN A7

#define STABILIZATION_TIME 20

#include "regression2.h"
#include "csensor.h"

static double blueB[NPARAMS];
static double redB [NPARAMS];

void regression_print(
    double Ys[2][NSEEDS],
    double X [NSEEDS][NPARAMS]);

csensor sensor(
    SENSOR_PIN,
    RED_LED_PIN,
    BLUE_LED_PIN,
    STABILIZATION_TIME);
    
void calibrate () 
{
  int runs = 0;
  static int seed_count = -1;
  static unsigned long  counter = 0;
  static unsigned long  LastPress = 0;
  static const unsigned long debounce_delay = 250;
  static calibration_data c [NSEEDS]; 
  double Ys[2][NSEEDS];
  
  attachInterrupt(digitalPinToInterrupt(CALIBRATION_PIN), nothing, FALLING);
  interrupts();
   if (millis() - LastPress > debounce_delay) {
      LastPress = millis();
      // RUN TEST ----------------------------------
      if (seed_count == -1) {
         Serial.print("\n\n// #define NSEEDS ");
         Serial.print(NSEEDS);
         Serial.print("\ncalibration_data C1[NSEEDS]=");
         Serial.print("\n{");
         seed_count = 0;
         calib_print_color(c[seed_count]);
      } else {
          
          while (!sensor.sense_get(c[seed_count])){}
          calib_print_data(c[seed_count++]);
          
          if (seed_count != NSEEDS){
              Serial.print(",\n ");
              c[seed_count].col = choose_color(seed_count);
              calib_print_color(c[seed_count]);
          } else {
              Serial.print("};\n\n\n"); 
          }
      
          if (seed_count == NSEEDS) {
              Serial.println("Running Gradient Descent"); 
              run_regression(c);
              seed_count = -1;
          }
      }
      // RUN TEST ----------------------------------
   }
   attachInterrupt(digitalPinToInterrupt(CALIBRATION_PIN), calibrate, FALLING); 
}

void setup() {
  // put your setup code here, to run once:
    
    // ----- SETUP SERIAL COMM ----------- //
    Serial.begin(9600);
    while (!Serial)  {}
    Serial.println("Serial Port ready");
    Serial.println("Hit the button to begin calibration");
  
    // ----- Calibration Pin ------------- //
    pinMode(CALIBRATION_PIN, INPUT_PULLUP);
    pinMode(   BLUE_LED_PIN, OUTPUT);
    pinMode(    RED_LED_PIN, OUTPUT);
    pinMode(     SENSOR_PIN, INPUT);
    
    attachInterrupt(digitalPinToInterrupt(CALIBRATION_PIN), calibrate, FALLING);
    interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("hello world");
    while (true) {
      sensor.sense();
    }
}

void run_regression (calibration_data c [NSEEDS])
{
    int runs;
    static double Ys[2][NSEEDS ];
    static double X    [NSEEDS ][NPARAMS];

    // INITIALIZING REGRESSION VARIABLES TO 0
    for (int j = 0; j < NSEEDS; ++j) {
        Ys[(int)BLUE][j] = 0;
        Ys[(int)RED ][j] = 0;
        for (int i = 0; i < NPARAMS; ++i) {
            blueB[i] = 0;
            redB [i] = 0;
        }
    }
    
    split (c,Ys,X);
    regression_print(Ys,X);
    Serial.print("\n");
    gradient_descent(Ys[(int)BLUE],X,blueB,0.001,0.000001,runs);
    
    Serial.print(" blueB = {");
    for (int i = 0; i < NPARAMS; ++i) {
      Serial.print((double)blueB[i]);
      if (i+1 < NPARAMS)Serial.print(", ");
    }
    Serial.print("};\n");

    Serial.print(" runs:"); 
    Serial.print(runs);
    Serial.print("\n\n"); 

    gradient_descent(Ys[(int)RED],X,redB,0.001,0.000001,runs);

    Serial.print(" redB = {");
    for (int i = 0; i < NPARAMS; ++i) {
      Serial.print((double)redB[i]);
      if (i+1 < NPARAMS)Serial.print(", ");
    }
    Serial.print("};\n");

    Serial.print(" runs:"); 
    Serial.print(runs);
    Serial.print("\n");
  
}

// -------------------------------------------------------- //
//       helper functions                                   //
// -------------------------------------------------------- //

void regression_print(
    double Ys[2][NSEEDS],
    double X [NSEEDS][NPARAMS]) 
{
     for (int i = 0; i < NSEEDS; ++i) {
    Serial.print(" |");
    Serial.print((double)Ys[0][i]);
    Serial.print("|");
    Serial.print((double)Ys[1][i]);
    Serial.print("|");
    for (int j = 0; j < NPARAMS; ++j) {
        Serial.print((double)X[i][j]);
        if (j + 1 < NPARAMS) Serial.print(", ");
    }
    Serial.print("|\n");
} 
}

void calib_print_color(calibration_data cd)
{
    Serial.print("{");
    color_print(cd.col);
    Serial.print(",");
}

void calib_print_data(calibration_data cd)
{
    Serial.print(cd.none);
    Serial.print(",");
    Serial.print(cd.blue);
    Serial.print(",");
    Serial.print(cd.both);
    Serial.print(",");
    Serial.print(cd.red);
    Serial.print("}");
}

void color_print (color c)
{
    switch (c) {
        case BLUE:
            Serial.print("BLUE");
            break;
        case RED:
            Serial.print("RED");
            break;
        case YELLOW:
            Serial.print("YELLOW");
            break;
        case BLACK:
            Serial.print("BLACK");
            break;
        case NONE:
            Serial.print("NONE");
            break;
        case ERR:
            Serial.print("ERR");
            break;
        default:
            break;
    }
}



color choose_color (int choose) 
{
    switch (choose % 4) {
        case 0:
            return BLUE;
        case 1:
            return RED;
        case 2:
            return YELLOW;
        case 3:
            return BLACK;
        default:
            return ERR;
    }
}

void nothing () {}




