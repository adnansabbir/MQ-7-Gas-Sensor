/*
 Testing F-22 harmful gas sensor with arduino in serial monitor.
 This code is written by Adnan Sabbir
 For more sensor testing code visit www.robogearsbd.com
*/

const int gasPin = A0;
int sensorMinValue=1024;
int sensorMaxValue=0;

void setup() {
  // We write codes here which runs only once
  Serial.begin(9600);     //We are starting the Serial with 9600 Baud

  // Getting values taken from suitable enviroment. later it will help us to detect harmful values.
  while (millis()<5000)    //Checking whether time is less than 5 sec since arduino started.
    {
      int sensorValue=analogRead(gasPin);   //Storing the sensor value in a temporary variable.
        if(sensorValue>sensorMaxValue)
          {
            sensorMaxValue=sensorValue;       //Here at the end of five second we will get the maximum value taken from your enviroment.
            }else if(sensorValue<sensorMinValue)
              {
                sensorMinValue=sensorValue;   ////Here at the end of five second we will get the minimum value taken from your enviroment.
                }
      }

  // Here we are reducing sensor min value but 100 and opposite for Max bacause, the other enviroment may be less suitable but still it's not harmful. 
      sensorMinValue = sensorMinValue - 100;
      sensorMaxValue = sensorMaxValue + 100;

}

byte Status=1;
void loop() {
  int sensorValue=analogRead(gasPin);
  //Serial.println(sensorValue);
  if(sensorValue>sensorMaxValue)   //Comparing the value that we are recieving in new enviroment. 
    {
        Serial.println("Unusual amount of CO gas detected");
         Serial.println(sensorValue);

         double deff = 0.0+(sensorValue-sensorMaxValue);
         double difference = (deff/sensorMaxValue)*100.0;
         Serial.print(difference);
         Serial.println("% of extra gas detected");
         Status=1;
      }else if (Status==1)
        {
          Serial.println("The enviroment has moderate amount of CO is suitable for Human Being");
          Status=0;
          }
  delay(500);
}
