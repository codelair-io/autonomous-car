 int inputPinSensor=8; //ECHO pin 
 int outputPinSensor=7; //TRIG pin 

 int forwardPin=13;
 int backwardsPin=11;
 int leftPin=2;
 int rightPin=3;

 // CM
 int MAX_DIST=1000;

 void setup() 
 { 
   Serial.begin(9600); 
   pinMode(inputPinSensor, INPUT); 
   pinMode(outputPinSensor, OUTPUT); 

   pinMode(forwardPin, OUTPUT);
   pinMode(backwardsPin, OUTPUT);
   pinMode(leftPin, OUTPUT);
   pinMode(rightPin, OUTPUT);
   randomSeed(analogRead(0));
 }
 
 void loop() 
 {  
   driveForwards(true);
   bool isNear = isNearObsticle();

   if(isNear){
     Serial.write("I found some stuff!!!");
     int turnVal = random(1,99);
     Serial.write(turnVal);
     if(turnVal % 2 == 0){
      turn(true);
     }else {
      turn(false);
     }
     driveForwards(false);
     driveBackwards(true);
     delay(1500);
     driveBackwards(false);
     
     stopTurning(); 
   }
 } 

 void driveForwards(bool shouldDrive){
  if(shouldDrive) digitalWrite(forwardPin, HIGH);
  else digitalWrite(forwardPin, LOW);
 }

 void driveBackwards(bool shouldDrive){
  if(shouldDrive) digitalWrite(backwardsPin, HIGH);
  else digitalWrite(backwardsPin, LOW);
 }

 void turn(bool isLeft){
  if(isLeft){
    digitalWrite(leftPin, HIGH);
    digitalWrite(rightPin,LOW); 
  }else{
    digitalWrite(leftPin, LOW);
    digitalWrite(rightPin,HIGH);
  }
 }

 void stopTurning(){
    digitalWrite(leftPin, LOW);
    digitalWrite(rightPin,LOW);
 }
 
 bool isNearObsticle(){
   digitalWrite(outputPinSensor, LOW); //Trigger ultrasonic detection 
   delayMicroseconds(5);
   digitalWrite(outputPinSensor, HIGH); //Trigger ultrasonic detection 
   delayMicroseconds(10);
   digitalWrite(outputPinSensor, LOW); //Trigger ultrasonic detection 
   long distance = pulseIn(inputPinSensor, HIGH); //Read ultrasonic reflection
   Serial.println(distance); //Print distance 
  
   if (distance > MAX_DIST){
     return true;
   } else {
    return false;
   }

 }
