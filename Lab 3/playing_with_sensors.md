# Lab 3 - Sensors
__Main Objective: experimenting with the potentiometer ("rotational sensor") and touch sensor components of the kits and their interactions with the ESP32__
## Methodology
- Code template was sourced from the Lab template
- Utilized PlatformIO via VSCode to interact with ESP32
- Stored all code in GitHub Lab 3 repository --> *contents of the repository are as follows*
     - **potentiometer.cpp** contains code for reading raw potentiometer analog outputs
     - **voltage.cpp** contains code for estimating the voltage across a potentiometer
     - **touch.cpp** contains code for a touch sensor apparatus
     - Videos for proof of voltage.cpp and touch.cpp operating can be found in the **videos** folder
## Touch sensor portion
*The touch sensor portion allowed us some more liberties with our code, so here are a few explanations of design decisions:*
- Decided to add a debug statement showing the raw analog output related to the touch sensor for debugging purposes
```
Serial.println(analogValue); //debug statement
```
- Chose a value of 2000 to divide the barrier between a touch being detected (usually outputting 4095) and a touch not being detected (usually outputting 0)
```
if(analogValue > 2000){ //ecs181 if the touch sensor is being touched
```

## Time reasoning and reflection
1. It took me around 3 hours to finish this assignment
2. I would associate a medium level of difficulty to this assignment
3. I had some difficulty that ended up being because I forgot to set the baude rate in the .ini file
4. I currently feel 4/5 comfortable with the course content. I'm still learning more about the ESP32
