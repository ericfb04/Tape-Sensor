#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define REFLECTANCE PA0 // Input pin
#define THRESHOLD 100 // Black line detection threshold
void handle_state_change();

void setup() {
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display_handler.display();
  delay(2000);

  // Displays "Hello world!" on the screen
  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.println("Reflectance value:\n");
  display_handler.display();

  // Set up PA1 as input
  pinMode(REFLECTANCE, INPUT);
  // Set up interrupt function
  //attachInterrupt(digitalPinToInterrupt(REFLECTANCE), handle_state_change, CHANGE);
}

void loop() {
  int detection = analogRead(REFLECTANCE);
  display_handler.clearDisplay();
  display_handler.setCursor(0,0);
  display_handler.println("Reflectance value:\n");
  display_handler.println(detection);
  if (detection < 100) {
    display_handler.println("Line Detected");
  }
  else {
    display_handler.println("No Line Detected");
  }
  display_handler.display();
}

void handle_state_change() {
  display_handler.clearDisplay();
  display_handler.setCursor(0,0);
  display_handler.println("Reflectance value:\n");
  display_handler.println(analogRead(REFLECTANCE));
  display_handler.display();
}