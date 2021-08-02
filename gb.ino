
#include <SHT1x.h>

#define dataPin  10
#define clockPin 11
SHT1x sht1x(dataPin, clockPin);

#define  humidity_relay_Pin 8
#define  upper_gercon_Pin 2
#define  lower_gercon_Pin 3
#define  led_Pin 13
#define  relay_pomp_in 5
#define  relay_pomp_out 6
boolean pompa_in_flag = false;
//boolean pompa_out_flag = false;
boolean relay_flag = false;
uint32_t tmr;
boolean flag = true;
uint32_t myTimer_tmp_humi;

#define period2 20*1000L  //20 секунд
//#define period2 60*15*1000L  // 15 минут
#define period1 60*1000L  // 1 минутa




void setup() {
 // pinMode(upper_gercon_Pin, INPUT_PULLUP);
  pinMode(lower_gercon_Pin, INPUT);
  pinMode(upper_gercon_Pin, INPUT);
  pinMode(dataPin, INPUT);
  pinMode(clockPin, INPUT);
 
 // digitalWrite(led_Pin, HIGH);
 
  pinMode(led_Pin ,OUTPUT );
  pinMode(relay_pomp_in, OUTPUT);
  pinMode(relay_pomp_out, OUTPUT);
  pinMode(humidity_relay_Pin, OUTPUT);


  Serial.begin(9600);
Serial.println("ok");
Serial.println(flag);//
//boolean upper_gercon_Data = digitalRead(upper_gercon_Pin);
 //boolean lower_gercon_Data = digitalRead(lower_gercon_Pin);   
 
//замкнут 0. разомкнут 1
//digitalWrite(relay_Pin, HIGH);
}

void loop() {
   int temp_c;
 // float temp_f;
  int humidity;
 
 
  
//int upper_gercon_Data = digitalRead(upper_gercon_Pin);
//Serial.println(digitalRead(upper_gercon_Pin));
//Serial.println(digitalRead(lower_gercon_Pin));
 boolean upper_gercon_Data = digitalRead(upper_gercon_Pin);
 boolean lower_gercon_Data = digitalRead(lower_gercon_Pin);

 if (lower_gercon_Data==1  && upper_gercon_Data==0 && pompa_in_flag==0) {//бак пустой,включаем насос
    Serial.println("бак пустой включем насос"); //
   Serial.println(digitalRead(upper_gercon_Pin));
Serial.println(digitalRead(lower_gercon_Pin));
   // digitalWrite(led_Pin, HIGH);
    digitalWrite(relay_pomp_in, HIGH);//включаем насос
    pompa_in_flag = true; //сохраняем флаг
   
 } 
        
 if  (upper_gercon_Data == 1 && lower_gercon_Data == 0 && pompa_in_flag == 1 ){//бак заполнcен выключаем насос
          Serial.println("бак заполнен выключаем насос"); //
          Serial.println(digitalRead(upper_gercon_Pin));
         Serial.println(digitalRead(lower_gercon_Pin));
         // digitalWrite(led_Pin, LOW);
          digitalWrite(relay_pomp_in, LOW); //выключаем насос
          pompa_in_flag = false;
         // pompa_out_flag = true; //включаем насос на впрыск

 }    
     
 
   if (millis() - tmr == (flag ? period1 : period2)) { //включаем насос на вкачивание period1=1min period2=20sec
    tmr = millis();
   // flag = !flag;
    digitalWrite(relay_pomp_out, flag);
    digitalWrite(led_Pin, flag);
     Serial.println("насос на впрыск");
    Serial.println(flag);
     flag = !flag;
    // для переключения реле
   // pompa_out_flag == 0 
  }
 if (millis() - myTimer_tmp_humi >= 30000) {
  myTimer_tmp_humi = millis();  
  // Read values from the sensor
  temp_c = sht1x.readTemperatureC();
 // temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();
 // Print the values to the serial port
  Serial.print("Temperature: ");
  Serial.print(temp_c, DEC);
  Serial.print("C / ");
 // Serial.print(temp_f, DEC);
//  Serial.print("F. Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  
    if(humidity >= 53) {

       digitalWrite(humidity_relay_Pin, HIGH);
        Serial.print("humidity >= 53");

    }

    else

    {
       digitalWrite(humidity_relay_Pin, LOW);
        Serial.print("humidity <= 53");
 
      }
 }
   

      
      
      
      
      
      
      
    } 
 
