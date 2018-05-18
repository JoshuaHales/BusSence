import processing.serial.*;
import processing.sound.*;
SoundFile file;  //bus arrived - 46a
SoundFile file2; //last call   - 46a
SoundFile file3; //bus arrived - 102
SoundFile file4; //last call - 102
SoundFile file5; //bus arrived - 32x
SoundFile file6; //last call   - 32x
int value = 0;

Serial myPort;  // our serial port
String val;     // Data received f rom the serial port

void setup(){
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
  
  file = new SoundFile(this, "../Sound Files/Female Voice Three/Track1.wav");
  file2 = new SoundFile(this, "../Sound Files/Female Voice Three/Track2.wav");
  file3 = new SoundFile(this, "../Sound Files/Female Voice Three/Track3.wav");
  file4 = new SoundFile(this, "../Sound Files/Female Voice Three/Track4.wav");
  file5 = new SoundFile(this, "../Sound Files/Female Voice Three/Track5.wav");
  file6 = new SoundFile(this, "../Sound Files/Female Voice Three/Track6.wav");
}
void serialEvent(Serial p) {
  String inString = p.readString(); // read in the string
  println (inString);
  
  String input = inString; //inputted value from arduino
  boolean find46a = input.indexOf("46A has") !=-1? true: false; //true if current bus is 46a
  boolean find46aLastCall = input.indexOf(":46A") !=-1? true: false; //true if current bus is 46a and btn pressed
  boolean find102 = input.indexOf("102 has") !=-1? true: false; //true if current bus is 102
  boolean find102LastCall = input.indexOf(":102") !=-1? true: false; //true if current bus is 102 and btn pressed
  boolean find32x = input.indexOf("32x has") !=-1? true: false; //true if current bus is 32x
  boolean find32xLastCall = input.indexOf(":32F") !=-1? true: false; //true if current bus is 102 and btn pressed
if(find46a){play46a();}
else if(find102){play102();}
else if(find46aLastCall){play46aLastCall();}
else if(find102LastCall){play102LastCall();}
else if(find32x){play32x();}
else if(find32xLastCall){play32xLastCall();}
}

void draw()
{
  
  if ( myPort.available() > 0) 
  {  // If data is available,
    val = myPort.readStringUntil('\n');         // read it and store it in val
  } 
  if(val != null){
    //println(val); //print it out in the console
    
    //value = 255;
    //file.play();
  }
  else {
    value = 0;
  }
}

void play46a(){
  value = 255;
  file.play();
}
void play46aLastCall(){
  value = 255;
  file2.play();
}
void play102(){
  value = 255;
  file3.play();
}
void play102LastCall(){
  value = 255;
  file4.play();
}
void play32x(){
  value = 255;
  file5.play();
}
void play32xLastCall(){
  value = 255;
  file6.play();
}

void keyPressed() {
  if (value == 0) { 
    //value = 255;
    //file.play();
    //System.out.println("value is => " +val);
    play46a();
  } else {
    value = 0;
  }
}