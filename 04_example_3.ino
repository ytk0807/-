#define PIN_LED 13
unsigned int count;
unsigned int toggle;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  while (!Serial){
    ;
  }
  Serial.println("Hello World!");
  count = toggle = 0;
  digitalWrite(PIN_LED, toggle);
}

void loop() {
  Serial.println(++count);
  toggle = toggle_state(toggle);
  digitalWrite(PIN_LED, toggle);
  delay(1000);
  digitalWrite(PIN_LED, 1);
  delay(1000);
}

int toggle_state(int toggle) {
  return toggle;
}