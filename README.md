# Honeywell Leak Detection

In summary, this is an Arduino sketch which monitors one analog pin, searching for a range of values indicating that a water leak has been detected.  Design details include turning on the onboard LED when a leak is detected. And I've added a piezo beeper, so it also makes noise when a leak is detected.

## Hardware

* This began life on an Arduino Uno from Freenove.com
* I'm using [Honeywell leak detection cable, RWD80](https://www.honeywellstore.com/store/products/honeywell-water-defense-leak-sensing-alarm-extension-cable.htm), originally purchased for a renovation in 2019.  
    * In 2024, I found this product is now discontinued.
    * [The Wayback Machine's first hit in Oct, 2011](http://web.archive.org/web/20111014084931/https://www.honeywellstore.com/store/products/honeywell-water-defense-leak-sensing-alarm-extension-cable.htm)
    * The Wayback Machine has hits in 2019, listing it "In-stock", but by Apr 2022, it's marked "DISCONTINUED". 
    * Why did it die?  I speculate:
        * It was pretty expensive, at $25 US for just 8 ft. ... I spent over $500 lining my basement walls & doing most sinks and appliances
        * It was designed around an alarm-sounding base unit that was battery-powered.  (That type of solution didn't appeal to me... maybe also not to other people.)
        * A problem I found: the cable come coiled, and retains that shape a lot, making it hard to secure to the ground so it can touch the water.  The retained shape makes it lift up. It came with plastic adhesive clips to secure it to the ground, but these are not a great solution.
* The piezo speaker is a no-name that came in the kit from Freenove.com

## Software

* The initial version supports monitoring only a single channel. 
* When the channel signals a leak, it turns on the onboard LED, and the peizo speaker.
* When the water detection cable is dry, it turns off the onboard LED, and the speaker.

### Surprising Physical Characteristics

* The Honeywell leak-detection cable didn't come with a hacker-friendly guide. This is a DIY project. 
* Honeywell sold this with a battery-powered base-station... I never bought that to tear down, to see how it worked.
* I was surprised that when the cable is dry, the analog pin measuring the voltage across the 2 black wires in the cable seems to follow a sinusoidal pattern, ranging from 0 to 1023 (on this Arduino), and back to 0, with a period of 3 to 4 seconds.
* Conversely, when the cable is wet, the analog voltage measurement shows much less variability
    * (in testing) If a part of the cable is submerged, it measures pretty consistently 670-680
    * (simulating real-world) if you place the cable on the ground, and drip 10 drops onto the cable where it touches the ground, it varies initially 580-710, settles 660-690
* The cable / this system is very responsive!  
    * If you drop the cable into a pot of water, the system is aware & alerting within 5 seconds! Ditto, a few drops of water on the ground
    * If you dry the wet area of the cable with a kitchen towel, the alarm is cancelled within 5 seconds!
    * The cable feels slightly waxy, as if it's water repellent, but it's not.  It's not a coating, it doesn't come off on your hands.
    

## Future Plans

* Expand this code so it can monitor up to 11 input channels "simultaneously" (it'll probably be serially) 
* Buy more robust Arduino that has 11 or more ADC channels, so I can physically connect all the channels
* I'll 3D print a panel with an LED for each of the 11 circuits, 
    * and expand the code to support a master "green" LED, meaning "All OK"
    * ... and support 11 more LED's, so it'll turn on an LED on the panel next to the label, describing where the leak is!

## Options

* Alerting - The tiny piezo speaker, and the onboard LED, are pretty weak in terms of alerting. This needs to be monitored from Nagios, and notify me that way.
* Metrics - It would be great to expose an API that Netdata can be adapted to integrate
* Thinking about the future 
    * One day, I'll want to sell this house, but I'll leave the Arduino behind; LED's and piezo speaker will be fine for this!
    * I've already got the Raspberry Pi monitoring the ultrasonic ToF sensor in the sump.  But that could probably be physically connected into this Arduino, and the software adapted to also monitor that hardware, which would make it more fulsome to leave behind.
    * 
