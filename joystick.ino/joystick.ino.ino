int limitSwitch1 = 2;
int limitSwitch2 = 3;
int limitSwitch3 = 4;
int limitSwitch4 = 5;
int buttonPin = 7;
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(limitSwitch1, INPUT);
  pinMode(limitSwitch2, INPUT);
  pinMode(limitSwitch3, INPUT);
  pinMode(limitSwitch4, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  String jsonString = "{ \"currentPosition\": ";
  if (digitalRead(limitSwitch1) == 0) {
    jsonString += "\"do\"";
  } else if (digitalRead(limitSwitch2) == 0) {
    jsonString += "\"le\"";
  } else if (digitalRead(limitSwitch3) == 0) {
    jsonString += "\"up\"";
  } else if (digitalRead(limitSwitch4) == 0) {
    jsonString += "\"ri\"";
  } else {
    jsonString += "\"no\"";
  }
  jsonString += ", \"buttonStatus\": ";
  if (digitalRead(buttonPin) == 1) {
    jsonString += "\"pr\"";
  } else {
    jsonString += "\"xx\"";
  }
  jsonString += " }";
  Serial.println(jsonString);
}
