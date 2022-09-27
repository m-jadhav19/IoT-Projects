const int Red = 9,Green = 10, Blue = 11;
int Ms = A1, relay = 8,dt= 1000, dtt = 50,value = 0,per,i;
 
void setup()
    {
    pinMode(Ms,INPUT);
    pinMode(relay,OUTPUT);
    pinMode(Red,OUTPUT);
    pinMode(Green,OUTPUT);
    pinMode(Blue,OUTPUT);
    Serial.begin(9600);
    }
 
void loop()
    {
    value = analogRead(Ms);
    per = map(value,0,1023,100,0);
    Serial.print("Percentage of Moisture= ");
    Serial.print(per);
    Serial.println("%     ");
    Serial.print("Analog value of Moisture= ");
    Serial.println(value);
    if (value >= 512)//water level is low
        {
        digitalWrite(relay,HIGH);
        Blueled();
        Serial.println("Relay is ON");
        }
    if (value < 512)//water level is high
        {
        digitalWrite(relay,LOW);
        Redled();
        Greenled();
        Serial.println("Relay is OFF");
        }
    delay(500);
    }
 
 
 
void Redled()
    {
    for (i=0;i<=255;i=i+15)
        {
        analogWrite(Red,i);
        delay(dtt);
        }
    for (i=255;i>=0;i=i-15)
        {
        analogWrite(Red,i);
        delay(dtt);
        }
    digitalWrite(Red,LOW);
    }
 
void Greenled()
    {
    for (i=0;i<=255;i=i+15)
        {
        analogWrite(Green,i);
        delay(dtt);
        }
    for (i=255;i>=0;i=i-15)
        {
        analogWrite(Green,i);
        delay(dtt);
        }
    digitalWrite(Green,LOW);
    }
 
void Blueled()
    {
    for (i=0;i<=255;i=i+15)
        {
        analogWrite(Blue,i);
        delay(dtt);
        }
    for (i=255;i>=0;i=i-15)
        {
        analogWrite(Blue,i);
        delay(dtt);
        }
    digitalWrite(Blue,LOW);
    }
 
void LightBlueled()
    {
    for (i=0;i<=255;i=i+15)
        {
        analogWrite(Blue,i);
        analogWrite(Green,i);
        delay(dtt);
        }
    for (i=255;i>=0;i=i-15)
        {
        analogWrite(Blue,i);
        analogWrite(Green,i);
        delay(dtt);
        }
    digitalWrite(Blue,LOW);
    digitalWrite(Green,LOW);
    }
 
void Pinkled()
    {
    for (i=0;i<=255;i=i+15)
        {
        analogWrite(Red,i);
        analogWrite(Blue,i);
        delay(dtt);
        }
    for (i=255;i>=0;i=i-15)
        {
        analogWrite(Red,i);
        analogWrite(Blue,i);
        delay(dtt);
        }
    digitalWrite(Red,LOW);
    digitalWrite(Blue,LOW);
    }
 
void Yellowled()
    {
    for (i=0;i<=255;i=i+15)
        {
        analogWrite(Red,i);
        analogWrite(Green,i);
        delay(dtt);
        }
    for (i=255;i>=0;i=i-15)
        {
        analogWrite(Red,i);
        analogWrite(Green,i);
        delay(dtt);
        }
    digitalWrite(Red,LOW);
    digitalWrite(Green,LOW);
}
