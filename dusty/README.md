# Dusty

Dusty is the nickname for the arduino codebase of the SparkyDuster project.

### Execution

Plug in the Arduino and install `arduino-cli`. Now you can do 

```
arduino-cli board list
```
Choose your serial port and do below:
```
arduino-cli compile --fqbn arduino:avr:mega .
arduino-cli upload -p <the serial port> -b arduino:avr:mega .
```
Or for an Uno:
```
arduino-cli compile --fqbn arduino:avr:uno .
arduino-cli upload -p <the serial port> -b arduino:avr:uno .
```

To tail logs you can do `screen <serial port>`.

To run a single command to compile and upload do:

```
SERIAL=$(arduino-cli board list | sed -n 's/.*\(\/dev\/cu.*[a-z]*[0-9]\).*/\1/p')
arduino-cli compile --fqbn arduino:avr:uno . ;
arduino-cli upload -p $SERIAL -b arduino:avr:uno .
```
