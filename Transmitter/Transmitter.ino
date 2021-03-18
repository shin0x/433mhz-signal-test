#include <RH_ASK.h>
#include <SPI.h> 

RH_ASK driver;
int button_pin = 2;

//init function for testing
void send_test(int number_of_tests);

void setup()
{
  Serial.begin(9600); 
  pinMode(button_pin, OUTPUT); //I don't know why but the button doesn't work when I declare it as an input. So I just declared it as output

  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  //when button is pressed, run the test
  if (digitalRead(button_pin))
  {
    Serial.println("Starting test");
    send_test(100);
    delay(1000);
  }
}

void send_test(int number_of_tests)
{
  //send test messages
  for (int i = 0; i < number_of_tests; i++)
  {
    const char *test_msg = "test running";
    driver.send((uint8_t *)test_msg, strlen(test_msg));
    driver.waitPacketSent();
    Serial.println(test_msg);
  }

  //send end message
  const char *test_ended = "ended testok";  
  driver.send((uint8_t *)test_ended, strlen(test_ended));
  Serial.println("Test ended");
}

