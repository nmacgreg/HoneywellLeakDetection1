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
* The piezo speaker is a no-name that came in the kit from Freenove.com

## Software

* The initial version supports monitoring only a single channel. 
* When the channel signals a leak, it turns on the onboard LED, and the peizo speaker.
* When the water detection cable is dry, it turns off the onboard LED, and the speaker.

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