// Librerías
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Nombro la pantalla LCD
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define ROWS 4
#define COLS 4

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

// Definir el teclado de matriz
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Variable para generar un numero random, la he llamado ak
char ak = random(1, 10) + '0';

// Variables para cada nivel
long randomNum;
long randomNum2;
long randomNum3;
long randomNum4;

// Leds
const int greenLed = 13;
const int redLed = 10;

void setup() {
  // Generador de números random
  randomSeed(analogRead(0));
  Wire.begin();

  // Inicializa la pantalla
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(9600);

  //  Configura los pines de los led
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  // Resistencias interactivas para el teclado 4x4
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
  for (int j = 0; j < ROWS; j++) {
    pinMode(rowPins[j], INPUT_PULLUP);
  }

  // Genera un número aleatorio para los niveles
  randomNum = random(10000, 100000);
  randomNum2 = random(100000, 1000000);
  randomNum3 = random(1000000, 10000000); 
  randomNum4 = random(10000000, 100000000); 
}

void loop() {
  lcd.clear();
  // Lee la tecla presionada
  char key = getKey();

  // Establece la longitud del código a 5, pero deja un sexto espacio para introducir un valor nulo. Sin ese valor nulo la función itoa no funcionaría
  char randomStr[6]; 
  randomStr[5] = '\0';

  // Convierte el numero en un string, una cadena de caracteres
  itoa(randomNum, randomStr, 10);

  // Verifica si se ha presionado una tecla
  if (key != '\0') { 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press A");
    while (getKey() != 'A'); // Espera hasta que se presione la tecla 'A'

    // Nivel 1
    lcd.clear();
    lcd.print("Level 1");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Random code:");
    delay(2000);
    lcd.setCursor(1, 1);

    // Filtra los caracteres no numéricos del código aleatorio. Todos esos caracteres los transforma en dígitos
    for (int i = 0; i < 5; i++) {
      if (randomStr[i] < '0' || randomStr[i] > '9') {
        ak = random(1, 10) + '0'; // Generar un nuevo valor de ak
    randomStr[i] = ak;
      }
    }

    // Mostrar el número aleatorio filtrado uno por uno, desvaneciéndose en la pantalla LCD
    for (int i = 0; i < 5; i++) {
      lcd.setCursor(i, 1);
      lcd.print(randomStr[i]); 
      delay(1000);
      lcd.setCursor(i, 1);
      lcd.print(" ");
    }

    // Ingresar código
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Insert code:");
    Serial.println(randomStr);

    // Establece la longitud del código que el jugador introduce a 5, pero deja un sexto espacio para introducir un valor nulo. Sin ese valor nulo la función itoa no funcionaría
    char numeros[6];
    numeros[5] = '\0';

    for (int i = 0; i < 5; i++) {
      char key2 = '\0';
      while (key2 < '0' || key2 > '9') {
        key2 = getKey(); 
        
        // Borrar dígito
        if (key2 == '#') { // Se verifica si la tecla presionada por el usuario es '#', si es así borra el último dígito.
          if (i > 0) {
            lcd.setCursor(i - 1, 1);
            lcd.print(" ");
            lcd.setCursor(i - 1, 1);
            i -= 1;
          }
        }
      }

      numeros[i] = key2; 
      lcd.setCursor(i, 1);
      lcd.print(key2);
      delay(250);
    }

    // Comparar el código ingresado con el número aleatorio generado
    if (strcmp(numeros, randomStr) == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Correct!!");

      // Enciende la LED verde.
      digitalWrite(greenLed, HIGH);
      delay(3000);
      digitalWrite(greenLed, LOW);

      // Nivel 2
      lcd.clear();
      lcd.print("Press B"); 
      while (getKey() != 'B');

      lcd.clear();
      lcd.print("Level 2");
      delay(4000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Random code:");
      delay(2000);

      char key3 = getKey();
      char randomStr2[7];
      randomStr2[6] = '\0';
      itoa(randomNum2, randomStr2, 10);

      for (int i = 0; i < 6; i++) {
        if (randomStr2[i] < '0' || randomStr2[i] > '9') {
          ak = random(1, 10) + '0';
          randomStr2[i] = ak;
        }
      }

      for (int i = 0; i < 6; i++) {
        lcd.setCursor(i, 1);
        lcd.print(randomStr2[i]);
        delay(1000);
        lcd.setCursor(i, 1);
        lcd.print(" ");
      }

      // Ingresar código
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Insert code:");

      Serial.println(randomStr2);
      char numeros2[7];
      numeros2[6] = '\0';
      
      for (int i = 0; i < 6; i++) {
        char key4 = '\0';
        while (key4 < '0' || key4 > '9') {
          key4 = getKey();
          
          if (key4 == '#') {
            if (i > 0) {
              lcd.setCursor(i - 1, 1);
              lcd.print(" ");
              lcd.setCursor(i - 1, 1);
              i -= 1;
            }
          }

        }

        numeros2[i] = key4;
        lcd.setCursor(i, 1);
        lcd.print(key4);
        delay(250);
      }

      // Comparar el código ingresado con el número aleatorio generado
      if (strcmp(numeros2, randomStr2) == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Correct!!");
        digitalWrite(greenLed, HIGH);
        delay(3000);
        digitalWrite(greenLed, LOW);

        // Nivel 3
        lcd.clear();
        lcd.print("Press C");
        while (getKey() != 'C');

        lcd.clear();
        lcd.print("Level 3");
        delay(4000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Random code:");
        delay(2000);

        char key5 = getKey();
        char randomStr3[8];
        randomStr3[7] = '\0';
        itoa(randomNum3, randomStr3, 10);

        for (int i = 0; i < 7; i++) {
          if (randomStr3[i] < '0' || randomStr3[i] > '9') {
            randomStr3[i] = ak;
          }
        }

        for (int i = 0; i < 7; i++) {
          lcd.setCursor(i, 1);
          lcd.print(randomStr3[i]);
          delay(1000);
          lcd.setCursor(i, 1);
          lcd.print(" ");
        }

        // Ingresar código
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Insert code:");
        Serial.println(randomStr3);

        char numeros3[8];
        numeros3[7] = '\0';

        for (int i = 0; i < 7; i++) {
          char key6 = '\0'; 

          while (key6 < '0' || key6 > '9') {
            key6 = getKey();

            if (key6 == '#') {
              if (i > 0) {
                lcd.setCursor(i - 1, 1);
                lcd.print(" ");
                lcd.setCursor(i - 1, 1);
                i -= 1;
              }
            }

          }
          numeros3[i] = key6;
          lcd.setCursor(i, 1);
          lcd.print(key6);
          delay(250);
        }

        // Comparar el código ingresado con el número aleatorio generado
        if (strcmp(numeros3, randomStr3) == 0) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Correct!!");
          digitalWrite(greenLed, HIGH);
          delay(3000);
          digitalWrite(greenLed, LOW);
          
          // Nivel 4
          lcd.clear();
          lcd.print("Press D");
          while (getKey() != 'D');

          lcd.clear();
          lcd.print("Level 4");
          delay(4000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Random code:");
          delay(2000);

          char key7 = getKey();
          char randomStr4[9];
          randomStr4[8] = '\0';
          itoa(randomNum4, randomStr4, 10);

          for (int i = 0; i < 8; i++) {
            if (randomStr4[i] < '0' || randomStr4[i] > '9') {
              randomStr4[i] = ak;
            }
          }

          for (int i = 0; i < 8; i++) {
            lcd.setCursor(i, 1);
            lcd.print(randomStr4[i]);
            delay(1000);
            lcd.setCursor(i, 1);
            lcd.print(" ");
          }

          // Ingresar código
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Insert code:");
          Serial.println(randomStr4);

          char numeros4[9];
          numeros4[8] = '\0';

          for (int i = 0; i < 8; i++) {
            char key8 = '\0'; 

            while (key8 < '0' || key8 > '9') {
              key8 = getKey();

              if (key8 == '#') {
                if (i > 0) {
                  lcd.setCursor(i - 1, 1);
                  lcd.print(" ");
                  lcd.setCursor(i - 1, 1);
                  i -= 1;
                }
              }
              
            }
            numeros4[i] = key8;
            lcd.setCursor(i, 1);
            lcd.print(key8);
            delay(250);
          }

          // Comparar el código ingresado con el número aleatorio generado
          if (strcmp(numeros4, randomStr4) == 0) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Correct!!");
            digitalWrite(greenLed, HIGH);
            delay(3000);
            digitalWrite(greenLed, LOW);
           
            // Reiniciar loop para volver al nivel 1
            for (;;) loop();
          }
          // En caso de error, se vuelve al menú principal, se reinicia el loop
          else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Incorrect!");
            digitalWrite(redLed, HIGH);
            delay(3000);
            digitalWrite(redLed, LOW);
            
            for (;;) loop();
          }
        }
        else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Incorrect!");
          digitalWrite(redLed, HIGH);
          delay(3000);
          digitalWrite(redLed, LOW);

          for (;;) loop();
        }
      }
      else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Incorrect!");
        digitalWrite(redLed, HIGH);
        delay(3000);
        digitalWrite(redLed, LOW);

        for (;;) loop();
      }
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Incorrect!");
      digitalWrite(redLed, HIGH);
      delay(3000);
      digitalWrite(redLed, LOW);

      for (;;) loop();
    }
  }
}

// Se nombra la variable getKey para registrar lo que el jugador pulsa en el teclado
char getKey() {
  char key = '\0';
  for (int i = 0; i < ROWS; i++) { 
    digitalWrite(colPins[i], LOW);
     
    for (int j = 0; j < COLS; j++) {

      if (digitalRead(rowPins[j]) == LOW) {
        key = keys[j][i];
        while (digitalRead(rowPins[j]) == LOW);
      }

    }
    digitalWrite(colPins[i], HIGH);
  }
  return key;
}
