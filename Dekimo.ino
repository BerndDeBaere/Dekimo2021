void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
}

int lastAngle = -45;
int lastSpeed = 4;

void loop() {
  String input = Serial.readStringUntil('\r');
  if(input.length() == 0)
  {
    return;
  }
  int value = input.toInt();
  if(value == 9999)
  {
    Serial.print("Bernd De Baere\r");
  }
  else
  {   
    Calculate(value);
  }
}

void Calculate(int input){
  String binary = intToBinaryString(input);
  int left = leftSpace(binary);
  int right = rightSpace(binary);

  int diff = absolute(left - right);

  if(left != right)
  {
      lastAngle = max(-45,min(45, lastAngle + (-right + left)*3));
  } 
  
  //Serial.println(binary);
  //Serial.println(left);
  //Serial.println(right);
  //Serial.println(lastAngle);
  //Serial.println(max(1, 12 - diff));

  lastSpeed = min(12, max(2, 16 - diff));

  Serial.print(String(lastAngle) + " " + String(lastSpeed) + "\r"); 
}

int angleToSpeed(int angle)
{
   int abs = absolute(angle);
   if(abs <= 1)
   {
      return 12;
   }
   else if(abs <= 2)
   {
      return 11;
   }
   else if(abs <= 5)
   {
      return 10;
   }
   else if(abs <= 10)
   {
      return 9;
   }
   else if(abs <= 15)
   {
      return 8;
   }
   else if(abs <= 20)
   {
      return 7;
   }
   else if(abs <= 25)
   {
      return 6;
   }
   else if(abs <= 30)
   {
      return 5;
   }
   else if(abs <= 35)
   {
      return 4;
   }
   else if(abs <= 40)
   {
      return 3;
   }
   else if(abs <= 45)
   {
      return 2;
   }
   
   return 1;

}

int min(int param1, int param2){
  if(param1>param2){
    return param2;
  }
  return param1;
}
int max(int param1, int param2){
  if(param1>param2){
    return param1;
  }
  return param2;
}
int absolute(int input){
  if (input < 0)
  {
    return input * -1;
  }
  return input;
}
int leftSpace(String input)
{
  if(input == "0")
  {
    return 16;
  }
  return 16 - input.length();

}
int rightSpace(String input)
{
  if(input == "0")
  {
    return 16;
  }
  int count = 0;
  for (int i = input.length() - 1; i >= 0; i--) 
  {
    if (input.charAt(i) == '0') {
      count++;
    } else {
      break;
    }
  }
  
  return count;
}

int max45(int input){
  if (input > 45)
  {
    return 45;
  }
  return input;
}

int min45(int input){
  if (input < -45)
  {
    return -45;
  }
  return input;
}

String intToBinaryString(int num) {
  return String(num, BIN); // Convert integer to binary string
}