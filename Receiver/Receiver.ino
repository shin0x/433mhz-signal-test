#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

//init counter for packages and time
int i = 0;
int starting_time = 0;

void setup()
{
  Serial.begin(9600);
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  //buffer for received messages
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);

  //when message is received
  if (driver.recv(buf, &buflen))
  {

    //reset time counter
    if (starting_time == 0)
      starting_time = millis();

    //convert message to char*
    char *msg = (char *)buf;


    Serial.print("Message: ");
    Serial.println((char *)buf);

    //check if test ended
    if (String(msg).indexOf("ended") >= 0) //check also works when package is slightly damaged -> it's just searching for a pattern instead the whole string
    {
      //print out results
      Serial.println("Received " + String(i) + "/100 packages");
      int needed_time = millis() - starting_time;
      Serial.println("It needed " + String(needed_time) + " milliseconds or " + String(needed_time / 1000.0) + " in seconds");
      
      //reset counter
      i = 0;
      starting_time = 0;
    }
    else
      i++;
  }
}
