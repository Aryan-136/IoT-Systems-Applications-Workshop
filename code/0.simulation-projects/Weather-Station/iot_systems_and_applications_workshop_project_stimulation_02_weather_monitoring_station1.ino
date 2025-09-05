#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_1(0);
int mode = 0;

void setup()
{
  lcd_1.begin(16, 2);
  pinMode(A0, INPUT); // temperature sensor
  pinMode(A1, INPUT); // gas sensor
  pinMode(A2, INPUT); // humidity sensor (potentiometer)
  
  pinMode(8, INPUT); // temperature mode pushbutton
  pinMode(9, INPUT); // air quality mode pushbutton
  pinMode(10, INPUT); // humidity mode pushbutton

  lcd_1.setCursor(0, 0);
  lcd_1.print("press pushbutton");
  lcd_1.setCursor(0, 1);
  lcd_1.print("to change mode");
}

void loop()
{
  // change to different modes if pushbuttons are pressed
  if (digitalRead(8) == HIGH) {
    lcd_1.clear();
    mode = 1;
  }
  
  if (digitalRead(9) == HIGH) {
    lcd_1.clear();
    mode = 2;
  }
  
  if (digitalRead(10) == HIGH) {
    lcd_1.clear();
    mode = 3;
  }
  
  // Mode 1: Temperature
  if (mode == 1) {
    float temp = (-40 + 0.878679 * (analogRead(A0) - 20));
    lcd_1.setCursor(0, 1);
    lcd_1.print(temp);
    lcd_1.print(" C    ");
    lcd_1.setCursor(0, 0);

    if (temp >= 120) lcd_1.print("volcanic        ");
    else if (temp > 100) lcd_1.print("really hot      ");
    else if (temp > 85)  lcd_1.print("hot             ");
    else if (temp > 70)  lcd_1.print("quite warm      ");
    else if (temp > 55)  lcd_1.print("pleasant        ");
    else if (temp > 40)  lcd_1.print("chill           ");
    else if (temp > 25)  lcd_1.print("cold            ");
    else if (temp > 10)  lcd_1.print("really cold     ");
    else lcd_1.print("arctic          ");
  }
  
  // Mode 2: Gas Sensor
  if (mode == 2) {
    int gasValue = analogRead(A1);
    lcd_1.setCursor(0, 1);
    lcd_1.print(gasValue);
    lcd_1.print(" ppm   ");
    lcd_1.setCursor(0, 0);
    lcd_1.print("Air Quality     ");
  }

  // Mode 3: Humidity (Potentiometer → %)
  if (mode == 3) {
    int humValue = analogRead(A2);
    int humidity = map(humValue, 0, 1023, 0, 100); // 0–100%

    lcd_1.setCursor(0, 1);
    lcd_1.print(humidity);
    lcd_1.print("%       ");
    lcd_1.setCursor(0, 0);
    lcd_1.print("Humidity        ");
  }

  delay(200);
}
