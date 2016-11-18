# Arduino Pumpkin Eyes

Code to make Adafruit 1.2" 8x8 Bright Square LED Matrix & backpack function as eyes for my decorative pumpkin.

![Pumpkin Photo](pumpkin-min.jpg?raw=true "Arduino Pumpkin Photo")

## How It Works

The start of the loop will select a random delay between 10-3000 ms.  After the delay a weighted random number is generated to select the next LED action.

- Blink
- Move pupil to a new location
- "Special Move"

If special move is selected, weighted random number is generated to indicate which special move:

- Eye spin
- Eye roll
- Eye twirl
- Flashing / pulsating
- Ping pong eyes back and forth

I started a snooze routine where it would display ZZZs across the LEDs for a period of time.  The plan was to have the pumpkin "fall asleep" and wake up using a PIR sensor.  For this first round I didn't use the PIR so I left the snooze out for now.

Inside of the pumpkin I added an RGB LED for an ambient glow, controlled by `setGlowColor()`.

