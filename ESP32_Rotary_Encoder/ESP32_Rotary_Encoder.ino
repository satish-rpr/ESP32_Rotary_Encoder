/* ESP32 - Rotary Encoder using EZButton library */
#include <ezButton.h>

#define CLK_PIN   4
#define DT_PIN    5
#define SW_PIN    21

ezButton button(SW_PIN);  // create ezButton object

int counter = 0;
int currentStateCLK;
int lastStateCLK = 0;

void setup() {
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  
  button.setDebounceTime(50);  // debounce time 50ms
  
  lastStateCLK = digitalRead(CLK_PIN);
  Serial.begin(9600);
}

void loop() {
  // Read the button state
  button.loop();
  
  // Read CLK pin
  currentStateCLK = digitalRead(CLK_PIN);
  
  // If CLK changes, check DT for direction
  if (currentStateCLK != lastStateCLK) {
    if (digitalRead(DT_PIN) != currentStateCLK) {
      counter++;  // Clockwise
    } else {
      counter--;  // Counter-clockwise
    }
    Serial.print("Position: ");
    Serial.println(counter);
  }
  lastStateCLK = currentStateCLK;
  
  // Button press detection
  if (button.isPressed()) {
    Serial.println("Button pressed!");
  }
}
