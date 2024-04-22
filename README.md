Memory Game

Memory Game is an Arduino-based project that challenges players to memorize and input sequences of numbers displayed on an LCD screen. The game consists of multiple levels, each increasing in difficulty, where players must correctly input the displayed sequence to progress.

Description
The game utilizes an Arduino Uno board along with a 16x2 LCD screen and a 4x4 matrix keypad. The LCD screen displays random sequences of numbers, and players must input these sequences using the keypad. If the input matches the displayed sequence, players advance to the next level. However, if the input is incorrect, players must retry the level.

Components: Arduino Uno, 16x2 LCD Screen, 4x4 Matrix Keypad, LEDs (for feedback).

Wiring Instructions

  - Matrix Keypad:
      - Connect the row pins (4 pins) to digital pins 6, 7, 8, and 9 on Arduino Uno
      - Connect the column pins (4 pins) to digital pins 2, 3, 4, and 5 on Arduino Uno
        
  - LCD Screen:
      - SDA pin to A4 on Arduino Uno
      - SCL pin to A5 on Arduino Uno
      - VCC pin to 5V on Arduino Uno
      - GND pin to GND on Arduino Uno

  - LEDs:
      - Connect the positive (longer) leg of the green LED to digital pin 13 on Arduino Uno
      - Connect the negative (shorter) leg of the green LED to GND on Arduino Uno
      - Connect the positive (longer) leg of the red LED to digital pin 10 on Arduino Uno
      - Connect the negative (shorter) leg of the red LED to GND on Arduino Uno

  - Libraries
      - To run the Memory Game project, you will need to install the following libraries:
          - Wire.h
        - LiquidCrystal_I2C.h
    These libraries provide the necessary functions to communicate with the LCD screen and handle I2C communication.

Usage
   - Once the hardware is set up and the necessary libraries are installed, upload the provided Arduino code to your Arduino Uno board. The game will start automatically once the code is uploaded.

   - Follow the on-screen instructions to progress through the levels. Use the keypad to input the displayed sequences of numbers. If your input matches the sequence, you will advance to the next level. If not, you will need to retry the level.

Have fun challenging your memory with Memory Game!

Contributors
This project was developed by Eneko Pardo.

Feel free to contribute to the project by submitting pull requests or opening issues on GitHub.
