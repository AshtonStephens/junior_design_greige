


#define COMMS_READ A0
#define COMMS_SEND 48
#define COMMS_THRESHOLD 100

#define COMMS_BUTTON_200 18 
#define COMMS_BUTTON_300 19
#define COMMS_BUTTON_400 20

#define INTERRUPT_DEBOUNCE_DELAY 250

static unsigned long stahp_sending_time = 0;
static unsigned long last_reading = 0;
bool  reading_in = false;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    while (!Serial)  {}
    Serial.println("Serial Port ready");
    
    pinMode(COMMS_BUTTON_400, INPUT_PULLUP);
    pinMode(COMMS_BUTTON_300, INPUT_PULLUP);
    pinMode(COMMS_BUTTON_200, INPUT_PULLUP);
    pinMode(COMMS_SEND, OUTPUT);
    
    attachInterrupt(digitalPinToInterrupt(COMMS_BUTTON_400), comms_send_400, FALLING);
    attachInterrupt(digitalPinToInterrupt(COMMS_BUTTON_300), comms_send_300, FALLING);
    attachInterrupt(digitalPinToInterrupt(COMMS_BUTTON_200), comms_send_200, FALLING);
    interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:
  readme_daddy();
  send_mystuff();
}

////-----------------------------------------------------------------------------
////-----------------------------------------------------------------------------

void readme_daddy ()
{
  static unsigned long reading_start_time = 0;
  int reading = analogRead(COMMS_READ);
  
  /*
  if (reading != 0){
    Serial.print("serial RAW [");
    Serial.print(reading);
    Serial.println("]");
  }
  */
  
  if (!reading_in && reading > 300){
      reading_in = true;
      Serial.println("READING STARTED");
      reading_start_time = millis();
  } else if ( reading_in && reading < 100){
      Serial.println("READING ENDED");
      reading_in = false;
      last_reading = millis() - reading_start_time;
      Serial.print("serial read [");
      Serial.print(last_reading);
      Serial.println("]");
  }
  
  return;
}

void send_mystuff()
{
 
  if (stahp_sending_time > millis()) {
    digitalWrite(COMMS_SEND,HIGH);
  } else {
    digitalWrite(COMMS_SEND,LOW);
  }
}

void add_sending_time (int a) 
{
  Serial.print("comms sending ");
  Serial.println(a);
  stahp_sending_time = millis() + a;  
}

////// --------------------------------------------------------------------
////// ------------------- interupts --------------------------------------
////// --------------------------------------------------------------------

void comms_send_400 () 
{
  static unsigned long  LastPress = 0;
  static const unsigned long debounce_delay = INTERRUPT_DEBOUNCE_DELAY;
  
  attachInterrupt(digitalPinToInterrupt(COMMS_BUTTON_400), nothing, FALLING);
  interrupts();
   if (millis() - LastPress > debounce_delay) {
      LastPress = millis();
      // RUN TEST ----------------------------------
      add_sending_time(400);
      // RUN TEST ----------------------------------
   }
   attachInterrupt(digitalPinToInterrupt(COMMS_BUTTON_400), comms_send_400, FALLING); 
}

void comms_send_300 () 
{
  static unsigned long  LastPress = 0;
  static const unsigned long debounce_delay = INTERRUPT_DEBOUNCE_DELAY;
  
  attachInterrupt(digitalPinToInterrupt(COMMS_BUTTON_300), nothing, FALLING);
  interrupts();
   if (millis() - LastPress > debounce_delay) {
      LastPress = millis();
      // RUN TEST ----------------------------------
      add_sending_time(300);
      // RUN TEST ----------------------------------
   }
   attachInterrupt(digitalPinToInterrupt(COMMS_BUTTON_300), comms_send_300, FALLING); 
}

void comms_send_200 () 
{
  static unsigned long  LastPress = 0;
  static const unsigned long debounce_delay = INTERRUPT_DEBOUNCE_DELAY;
  
  attachInterrupt(digitalPinToInterrupt(COMMS_BUTTON_200), nothing, FALLING);
  interrupts();
   if (millis() - LastPress > debounce_delay) {
      LastPress = millis();
      // RUN TEST ----------------------------------
      add_sending_time(200);
      // RUN TEST ----------------------------------
   }
   attachInterrupt(digitalPinToInterrupt(COMMS_BUTTON_200), comms_send_200, FALLING); 
}

////// --------------------------------------------------------------------
////// --------------------------------------------------------------------
////// --------------------------------------------------------------------

void nothing () {};


