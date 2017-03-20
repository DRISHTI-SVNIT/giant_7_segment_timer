/* @author Kartik Nighania
 * @author Sarthak Shah
 * 
 *  we have 8 digits with 7 bulbs each which therefore takes a total of 56 pins.
 *  
 *  the code below takes -
 *  
 *  on start-up the time from the real-time clock module 
 *  
 *  starts its own timers and decrements the counter according to the initial time by the RTC clock
 *  
 *  provides necessary outputs through ports that switches the relays thus generating the numbers
 *  
 *  
 *  note-
 *  due to bulky hardware because of things like buck converter (to drive those many relays) and relays
 *  with constant 10000 switching cycle. 
 *  
 *  No timer interrupts and multiplexing was used which can also show data by the use of POV 
 *  (persistance of vision) and would require very less current. Was not implemented due to the relay
 *  limited cycles and slow operations. Also in future, it is advised not todo so. :)
 */
void setup() 
{
 

}

void loop() 
{


}
