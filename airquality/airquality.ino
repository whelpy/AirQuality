#include <Adafruit_CCS811.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // Устанавливаем дисплей

Adafruit_CCS811 ccs;

void setup()
{
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  //lcd.print("iarduino.ru");
  //lcd.setCursor(8, 1);
  //lcd.print("LCD 1602");

  if(!ccs.begin())
  {
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  //calibrate temperature sensor
  while(!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 23.0);
}
void loop()
{
  // Выводим на экран количество секунд с момента запуска ардуины
  //lcd.print(millis()/1000);

  if(ccs.available()){
    float temp = ccs.calculateTemperature();
    if(!ccs.readData()){
      lcd.setCursor(0, 0);
      lcd.print("CO2:");      
      lcd.print(ccs.geteCO2());
      lcd.print(" TVOC:");            
      lcd.print(ccs.getTVOC());
      // Устанавливаем курсор на вторую строку и нулевой символ.
      lcd.setCursor(0, 1);

      lcd.print("Temp:");
      lcd.print(temp);
    }
    else{
      lcd.print("ERROR!");
      while(1);
    }
  }
  delay(500);
}
