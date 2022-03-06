#include <Adafruit_CCS811.h>

#include <Wire.h> 
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // Устанавливаем дисплей

Adafruit_CCS811 ccs;

#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

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

  dht.begin();

  //calibrate temperature sensor
  while(!ccs.available());
  float tempDht = dht.readTemperature();
  float tempCcs = ccs.calculateTemperature();
  ccs.setTempOffset(tempCcs - tempDht);
}
void loop()
{
  // Выводим на экран количество секунд с момента запуска ардуины
  //lcd.print(millis()/1000);

  if(ccs.available()){

    float  hum = dht.readHumidity();
    float  temp= dht.readTemperature();
     Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    
    if(!ccs.readData()){
      lcd.setCursor(0, 0);
      lcd.print("CO2:");      
      lcd.print(ccs.geteCO2());
      lcd.print(" TVOC:");            
      lcd.print(ccs.getTVOC());
      // Устанавливаем курсор на вторую строку и нулевой символ.
      lcd.setCursor(0, 1);

      lcd.print("T:");
      lcd.print((int)temp);
      lcd.print("C");

      lcd.setCursor(8, 1);
      lcd.print("H:");
      lcd.print((int)hum);
      lcd.print("%");
    }
    else{
      lcd.print("ERROR!");
      while(1);
    }
  }
  delay(500);
}
