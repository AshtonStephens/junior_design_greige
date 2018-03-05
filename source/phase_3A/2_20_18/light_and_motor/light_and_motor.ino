
static const int MOTOR1_PIN1   = 8;  // 
static const int MOTOR1_PIN2   = 9;  //
static const int MOTOR1_ENABLE = 32; //
                                  
static const int MOTOR2_PIN1   = 7;  //
static const int MOTOR2_PIN2   = 6;  //
static const int MOTOR2_ENABLE = 30; //
                                  
static const int CSENSOR_LED_RED  = 22; //
static const int CSENSOR_LED_BLUE = 24; //

static const int CSENSOR          = 26; //
//static const int CSENSOR          =  ; // 

// NOTE : 
//  CANNOT USE PWN PINS 13, 12, 11 because 
//  timer1 is overwritten

// time between changing the led color
// and reading in the data (milliseconds)
static const int color_delay_time = 100; // <-------- TIME BETWEEN WAITING FOR
static const int color_poll_freq  = 50;  // <-------- 

static const int TIMER1_ISR_COMPARE =
      ((float)(16000000)/((long long)color_poll_freq*1024)) - 1;

#define SENSOR_PIN A1 // Blue LED brightness

#define RED_SHINE  0
#define BLUE_SHINE 1

#define ERR -1
#define PROCESSING 0
#define BLUE   1
#define RED    2
#define BLACK  3
#define YELLOW 4

typedef struct mdata_S
{ 
  // TODO: !!!!!!!!!!!!!!!!!!!!!!!!!!
  int PLACEHOLDER; // 
} *mdata_T;

typedef struct csensor_S
{
  int current_color;
  int readings_left;
  int readings_per_decision;
  int color_readings[2];
  int color;
} *csensor_T;

struct BOT 
{
  struct csensor_S csensor;
//  struct hsensor_S  hsensor;
  struct mdata_S   mdata;
};

void csensor_init(csensor_T cs, int readings);
int csensor_get_reading      (csensor_T cs);
int csensor_reset_readings   (csensor_T cs);
int csensor_swap_led_color   (csensor_T cs);
int csensor_turn_led_off     (csensor_T cs);
int csensor_decide_color     (csensor_T cs);
int csensor_read_color       (csensor_T cs);

void bot_init(struct BOT *b);

void bot_init(struct BOT *b)
{
  csensor_init(&(b->csensor),3);
}

static struct BOT bot;

unsigned long start_timer () 
{return millis();}

bool wait_time(unsigned long timer, unsigned long wait_time)
{return millis() - timer > wait_time;}

void setup() 
{
    // ----- SETUP SERIAL COMM ----------- //
    
    Serial.begin(9600);
    while (!Serial)  {}
    Serial.print("printing ready\n");

    // ----- INITIALIZING BOT VALUES -----

    bot_init(&bot); 
    
    // ----- SETTING UP PINS ------------- 
    
       // MOTOR PINS ------------------
       pinMode(MOTOR1_PIN1,   OUTPUT); //
       pinMode(MOTOR1_PIN2,   OUTPUT); //
       pinMode(MOTOR1_ENABLE, OUTPUT); //
                                            
       pinMode(MOTOR2_PIN1,   OUTPUT); //
       pinMode(MOTOR2_PIN2,   OUTPUT); //
       pinMode(MOTOR2_ENABLE, OUTPUT); //
  
       // COLOR SENSOR PINS ----------------
       pinMode(CSENSOR_LED_RED,  OUTPUT); // 
       pinMode(CSENSOR_LED_BLUE, OUTPUT); // 
       pinMode(CSENSOR, INPUT); //     
       //pinMode(CSENSOR, INPUT); //
    
    // ----- SETTING UP TIMER INTERRUPT -- //

    cli(); // disable interrupts
    
    //set timer1 interrupt at 1Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR1A = TIMER1_ISR_COMPARE;
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12 and CS10 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);  
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    
    sei();//allow interrupts

}

/* POLLING TIMER INTERRUPT 
 * 
 */
ISR(TIMER1_COMPA_vect)
{
  TIMSK1 &= !(1 << OCIE1A); ///////// DISABLE TIMER1 INTERRUPT
  sei(); //////////////////////////// ENABLE ALL OTHER INTERRUPTS 
  //////////////////////////////////////////////////////////////
  csensor_read_color(&(bot.csensor));
 // moto_update_state(&(bot.motor));                                 
  
           
  ////////////////////////////////////////////////////////////// 
  TIMSK1 |= (1 << OCIE1A); /////////// ENABLE TIMER1 INTERRUPT
}




//------------------------------------------------------------------------ //
//                          ------- LOOP -------                        -- //
//------------------------------------------------------------------------ //

#define CORRECTION_TIME_BACK  100
#define CORRECTION_TIME_RIGHT 100
#define CORRECTION_TIME_LEFT  200

#define CORRECTION_SPEED_BACK  30
#define CORRECTION_SPEED_RIGHT 30
#define CORRECTION_SPEED_LEFT  30


void loop() 
{
  //  CODE DESCRIPTION:
  //    state 0:
  //      stay on color blue until ya reach red and go forward
  //    state 1: 
  //      turn right
  //    state 2: 
  //      stay on red until ya reach yella
  //    state 3:
  //      stahp
  //
  int state0_0 = 0;
  int timer = 0;

  // while we're not on RED
  while (bot.csensor.color != RED) {
    /* 
     *  GO FORWARD WHILE ON BLUE
     */
    if (bot.csensor.color == BLUE) {
      forward(40);
    // else
    
    } else if (bot.csensor.color != RED) {
        
        /* 
         *  GO BACK
         */
        timer = start_timer();
        while (wait_time(timer, CORRECTION_TIME_BACK)) {
          backward(CORRECTION_SPEED_BACK);   
        } 

        /* 
         *  TURN RIGHT
         */
        timer = start_timer();
        while (wait_time(timer,100, CORRECTION_TIME_RIGHT)) {
            turn_right(CORRECTION_SPEED_RIGHT);  
        }

        /* 
         * WHILE I'M TURNING LEFT STAHP IF I HIT
         * THE COLORS I'M LOOKING FOR OR RUN OUT OF TIME
         */
        timer = start_timer();
        while (wait_time(timer,CORRECTION_TIME_LEFT) &&
            bot.csensor.color != RED &&
            bot.csensor.color != BLUE) {
            turn_left(CORRECTION_SPEED_LEFT);  
        }
              
    } else {
      stahp();
    }
  }
  stahp();

  
}

void stahp()
{ 
  analogWrite (MOTOR2_PIN1, 0);
  analogWrite (MOTOR2_PIN2, 0);
  digitalWrite(MOTOR2_ENABLE, HIGH);

  // Right wheel backward
  analogWrite (MOTOR1_PIN1, 0);
  analogWrite (MOTOR1_PIN2, 0);
  digitalWrite(MOTOR1_ENABLE, HIGH);
}

void forward(int spd)
{
  analogWrite (MOTOR2_PIN1, spd);
  analogWrite (MOTOR2_PIN2, 0);
  digitalWrite(MOTOR2_ENABLE, HIGH); // L goes bw
  
  analogWrite (MOTOR1_PIN1, spd);
  analogWrite (MOTOR1_PIN2, 0);
  digitalWrite(MOTOR1_ENABLE, HIGH); // R goes fwd
}

void turn_left(int spd)
{
  analogWrite (MOTOR2_PIN1, 0);
  analogWrite (MOTOR2_PIN2, spd);
  digitalWrite(MOTOR2_ENABLE, HIGH); // L goes bw
  
  analogWrite (MOTOR1_PIN1, spd);
  analogWrite (MOTOR1_PIN2, 0);
  digitalWrite(MOTOR1_ENABLE, HIGH); // R goes fwds
}

void turn_right(int spd)
{
  analogWrite (MOTOR2_PIN1, spd);
  analogWrite (MOTOR2_PIN2, 0);
  digitalWrite(MOTOR2_ENABLE, HIGH); // L goes bw
  
  analogWrite (MOTOR1_PIN1, 0);
  analogWrite (MOTOR1_PIN2, spd);
  digitalWrite(MOTOR1_ENABLE, HIGH); // R goes fwd
}




void do_nothing (void) {}


// COLOR SENSOR --------------------------------------------------------------
//
// csensor_T -----------------------------------------------------------------


void csensor_init(csensor_T cs, int readings)
{
  cs-> readings_per_decision = readings*2;
  cs-> current_color = RED;
  csensor_reset_readings(cs);
}
  
int csensor_read_color       (csensor_T cs)
{
  int color = PROCESSING;
  csensor_get_reading    (cs);
  csensor_swap_led_color (cs);
  if (!(cs-> readings_left)) {
    color = csensor_decide_color(cs);
    csensor_reset_readings(cs);
  }
  
  return color;
}

int csensor_get_reading      (csensor_T cs)
{
  cs->readings_left --;
  cs->color_readings[cs->current_color - 1] += digitalRead(CSENSOR);
  return 0;
}

int csensor_reset_readings   (csensor_T cs)
{
  cs->color_readings[RED  - 1] = 0;
  cs->color_readings[BLUE - 1] = 0;
  cs-> readings_left = cs-> readings_per_decision;
  return 0;
}

int csensor_swap_led_color   (csensor_T cs)
{
  if (cs->current_color == BLUE) {
     cs->current_color = RED;
     digitalWrite(CSENSOR_LED_BLUE, LOW);
     digitalWrite(CSENSOR_LED_RED, HIGH);
  } else if (cs-> current_color == RED) {
     cs->current_color = BLUE;
     digitalWrite(CSENSOR_LED_BLUE, HIGH);
     digitalWrite(CSENSOR_LED_RED,  LOW);
  } else {
     digitalWrite(CSENSOR_LED_BLUE, LOW);
     digitalWrite(CSENSOR_LED_RED,  LOW);
     if (cs-> current_color != BLACK) {
      Serial.write("invalid Csensor color state\n");
     }
  }
  return 0;
}

int csensor_turn_led_off     (csensor_T cs)
{
  cs-> current_color = BLACK;
  csensor_swap_led_color(cs);
}

int csensor_decide_color     (csensor_T cs)
{

  // TEMPORARY DEBUG CODE
  float red_reads  = (((float)cs->color_readings[RED -1]))/cs->readings_per_decision;
  float blue_reads = (((float)cs->color_readings[BLUE-1]))/cs->readings_per_decision;
  Serial.print("[B: ");
  Serial.print(blue_reads);
  Serial.print(" R: ");
  Serial.print(red_reads);
  Serial.println("]");
  
  
  /* TODO: return the color being sensed 
  int valid_on = (cs-> readings_per_decision >> 1);
  static const int valid_off = 0;
  
  if (cs->color_readings[RED-1] == valid_on) {
      if (cs->color_readings[BLUE-1] == valid_on) {
        Serial.println("YELLOW");
        cs-> color = YELLOW;
        return YELLOW;
      } else if (cs->color_readings[BLUE-1] == valid_off) {
        Serial.println("RED");
        cs-> color = RED;
        return RED;
      }
  } else if (cs->color_readings[RED-1] == valid_off) {
      if (cs->color_readings[BLUE-1] == valid_on) {
        Serial.println("BLUE");
        cs-> color = BLUE;
        return BLUE;
      } else if (cs->color_readings[BLUE-1] == valid_off) {
        Serial.println("BLACK");
        cs-> color = BLACK;
        return BLACK;
      }
  }
  */
  
  Serial.println("ERR");
  return ERR;
}



