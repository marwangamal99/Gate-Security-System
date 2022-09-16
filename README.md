# Gate-Security-System
The project was about constructing a software for a gate security system. The gate had a keypad for password and options entry, a buzzer for alarm, and the electrical 
system consisted of 2 ATmega328P microcontrollers.

- One mC acts as an HMI as taking commands from the keypad, sending and receiving both requests and responds from the other mC.
- The second mC acts as the main controller. It fetches the password entered, manage the NVM, sending commands and controls the decryption of the received password.
- There are 2 communcation protocols used on that project:
  1. UART communication protocol used between the 2 mCs.
  2. I2C communication protocol used between the main controller mC and the NVM (external EEPROM).
- There are some test cases are handled to convert the software from a simple project dilevery into a product that can be published to a customer as:
  1. Password encryption for the entered password at the HMI mC and then password decrypton at main controller to secure the data from any external password fetching
     throughout the communication exists between the 2 mCs.
  2. Sending alarm detection if the commuication was interrupted for any not ordered external interrupts for a certain number of times.
