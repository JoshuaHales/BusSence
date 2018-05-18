#include <IRremote.h>

int RECV_PIN = 11;
int busVal;       //current val rec from IRBlaster
int currentBusVal;//the current bus
int busHasLeft; // is 1 when bus has left
int previousBusVal;//the previous bus

int myMeth(int busValIn){
  
  String busValueAsHex =  String(busValIn, HEX);       //save the bus number (now a Hex value) to a string   example -> "46a"
  char* busVal_char = &busValueAsHex[0];               //value as char
  
  // ----- compare two chars ------
  char *sent = busVal_char;             //check if this value . . .
  char *word = "f";                     //. . contains this value
 
  char *pch = strstr(sent, word); //cheked here

  //determmining what to do if that value IS within the first value
  if(pch)
  {
    // ---- Replace an instance of 'f' with 'x' ----
    int sizeOfChar = sizeof(busVal_char);
    String busValWith_f = busVal_char;
    int f_position = busValWith_f.indexOf('f');
    busValWith_f.setCharAt(f_position, 'x');
    
    currentBusVal = busVal;
    busHasLeft = 0;
    previousBusVal = busVal;
  }
    // and what to do if that value IS NOT within the first value
  else{
    return false;
  } // ----- end of if(pch) statement
}

//--- Method used to validate each incomming value (as a protocol) ---
bool isValidValue(int busValInHere){

  //save the bus number (now a Hex value) to a string   example -> "46a"
  String busValueAsHex =  String(busValInHere, HEX); 

  //value as char
  char* busVal_char = &busValueAsHex[0];

  //compare two chars
  char *sent = busVal_char;   //check if this value . . .
  char *word = "999";   //. . contains this value
 
  char *pch = strstr(sent, word); //cheked here

  //determmining what to do if that value IS within the first value
  if(pch)
  {
   return true;
  }
  // and what to do if that value IS NOT within the first value
  else{
   return false;
  }
}

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

//storing the return value from the myMeth function
bool containsF = myMeth(busVal);
void loop() {
  busVal = results.value;
  if (irrecv.decode(&results)) {

      /* -Runs method for every value that comes in
         -This method checks if each bus is prepended with the secret token (to verify source before proceeding)*/
      isValidValue(busVal);

      //capture the return type (from isValidValue method) and store it                  
      bool isItValid = isValidValue(busVal);

      //bus is valid
      if(isItValid == true){
         //Serial.println("Bus is valid)");
      }
      
      //bus is Not valid
      else if(isItValid == false){
         //Serial.println("Bus is not valid)");
      }
    
      switch(busVal) {

           case 1130  :
                if(currentBusVal != 1130 && containsF == false){
                    Serial.print(results.value, HEX);
                    Serial.println(" has arrived");
                  }
                currentBusVal = 1130;
                busHasLeft = 0;
                previousBusVal = 1130;
              break; 
          
           case 258  :
                if(currentBusVal != 258 && containsF == false){
                    Serial.print(results.value, HEX);
                    Serial.println(" has arrived");
                 }
                  currentBusVal = 258;
                  busHasLeft = 0;
                  previousBusVal = 258;
              break; 
        
           case 815  :
                if(currentBusVal != 815 && containsF == false){

                  String busValWith_f =  String(busVal, HEX); //save the bus number (now a Hex value) to a string   example -> "46a"
                  int f_position = busValWith_f.indexOf('f');
                  busValWith_f.setCharAt(f_position, 'x');

                  
                  Serial.print(busValWith_f);
                  Serial.println(" has arrived");
                }
                currentBusVal = 815;
                busHasLeft = 0;
                previousBusVal = 815;
              break; 

             //previous bus button 
             case 111  :
                Serial.print("LAST CALL FOR:");
                Serial.println(previousBusVal, HEX);
              break;
        }//end of switch
        
        //check if bus has left
        if(busVal != 1130 || busVal != 258 || busVal != 815){
          if(busHasLeft == 1){
            Serial.println("Bus has left");
          }
        }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
