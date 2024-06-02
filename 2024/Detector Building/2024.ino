//constants
float condVal;
const int redPin = 13;
const int greenPin = 12;
const int bluePin = 11;

//ppm ranges:
const float redMin = 0;
const float redMax = 1000;

const float greenMin = 1001;
const float greenMax = 3000;

const float blueMin = 3001;
const float blueMax = 5000;

//samples
int sample = 0;
float voltageSum = 0;

void setup() {
  Serial.begin(9600); //establish connection with arduino
  pinMode(redPin, OUTPUT); //sets analog redPin as input pin
  pinMode(greenPin, OUTPUT); //sets analog greenPin as input pin
  pinMode(bluePin, OUTPUT); //sets analog bluePin as input pin
}


void loop() { //everything between these curly braces will loop
  sample = sample + 1; //keep track of iterations

  condVal = analogRead(A0); //read analog voltage
  float voltage = condVal * (5.0 / 1023.0); //calculate relative conductivity
  voltageSum = voltageSum + voltage; //sum of voltages to calculate average after iterations complete


  if (sample >= 100) { //once sample size reached
    float voltageAvg = voltageSum / sample; //calcualte average conductivity
    float ppm = 77.5 * exp(1.45 * voltage); //convert to ppm using equation

    Serial.println("voltage(V): " + String(voltage) + "\t\t" + "concentration(ppm): " + String(ppm)); //print to console


    if (ppm >= redMin && ppm <= redMax) { //if within red range
      digitalWrite(redPin, HIGH); //turn on red led
    } else { //or else
      digitalWrite(redPin, LOW); //turn off red led
    }

    if (ppm >= greenMin && ppm <= greenMax) { //if in green range
      digitalWrite(greenPin, HIGH); //turn on green led
    } else { //or else
      digitalWrite(greenPin, LOW); //turn off green led
    }

    if (ppm >= blueMin && ppm <= blueMax) { //if in blue range
      digitalWrite(bluePin, HIGH); //turn on blue led
    } else { //or else
      digitalWrite(bluePin, LOW); //turn off blue led
    }

    //reset values after sample size finishes
    sample = 0;
    voltageSum = 0;
  }

  delay(10); //delay before looping
}
