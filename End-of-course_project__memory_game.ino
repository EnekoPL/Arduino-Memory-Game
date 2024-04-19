// Librerías necesarias para el funcionamiento de la pantalla LCD.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Nombrar la pantalla LCD.

#define ROWS 4
#define COLS 4

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
}; // Definir el teclado de matriz.

char ak = random(1, 10) + '0'; // Variable para generar un numero random del 1 al 9 que sustituya caracteres desconocidos por digitos.
long randomNum; // Variable para el primer nivel.
long randomNum2; // Variable para el segundo nivel.
long randomNum3; // Variable para el tercer nivel.
long randomNum4; // Variable para el cuarto nivel.

const int greenLed = 13; // LED verde conectada al pin 13.
const int redLed = 10;   // LED roja conectada al pin 10.

void setup() {
  randomSeed(analogRead(0)); // Inicializa el generador de números aleatorios (random()). Utiliza el valor de la entrada analógica 0 (analogRead(0)) como semilla para el generador de números aleatorios.
  Wire.begin(); // Inicia la comunicación I2C.
  lcd.begin(16, 2);
  lcd.backlight(); // Enciende la retroiluminación de la pantalla LCD.
  Serial.begin(9600);
  //  Configura los pines greenLed y redLed como salidas digitales para controlar los LEDs verde y rojo.
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  // Configuran los pines de las columnas (colPins) como salidas y los pines de las filas (rowPins) como entradas con resistencias pull-up internas activadas.
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
  for (int j = 0; j < ROWS; j++) {
    pinMode(rowPins[j], INPUT_PULLUP);
  }

  // Genera un número aleatorio de 6 dígitos (entre 100,000 y 999,999) y lo asigna a la variable randomNum2.
  randomNum2 = random(100000, 1000000);
 
  // Genera un número aleatorio de 7 dígitos (entre 1,100,000 y 9,999,999) y lo asigna a la variable randomNum3.
  randomNum3 = random(1000000, 10000000); 

  // Genera un número aleatorio de 8 dígitos (entre 1,000,000 y 9,999,999) y lo asigna a la variable randomNum4.
  randomNum4 = random(10000000, 100000000); 
}

void loop() {
  lcd.clear();
  randomNum = random(10000, 100000); // Generar número aleatorio entre 10000 y 99999.
  char key = getKey(); //  Lee la tecla presionada y la almacena en la variable key.
  char randomStr[6]; // Establece la longitud del código a 5 para el nivel 1.
  randomStr[5] = '\0';
  itoa(randomNum, randomStr, 10); // Convierte el número aleatorio (randomNum) en una cadena de caracteres (randomStr) utilizando la función itoa().
  if (key != '\0') { //Verifica si se ha presionado una tecla.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press A");
    while (getKey() != 'A'); // Espera hasta que se presione la tecla 'A'.

    // Nivel 1
    lcd.clear();
    lcd.print("Level 1");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Random code:");
    delay(2000);
    lcd.setCursor(1, 1);

   
    // Filtrar los caracteres no numéricos del código aleatorio.
    
    for (int i = 0; i < 5; i++) { //Este bucle for se utiliza para iterar sobre cada uno de los primeros cinco caracteres de la cadena randomStr.
      if (randomStr[i] < '0' || randomStr[i] > '9') { //verifica si el carácter en la posición i de la cadena randomStr no es un dígito numérico. Compara el valor ASCII del carácter en randomStr[i] con los valores ASCII de los dígitos numéricos ('0' a '9'). Si el carácter no es un dígito numérico, el if se evalúa como verdadero.
        ak = random(1, 10) + '0'; // Generar un nuevo valor de ak
    randomStr[i] = ak; // Reemplazar el carácter no numérico por ak
      }
    }

    // Mostrar el número aleatorio filtrado uno por uno, desvaneciéndose en la pantalla LCD.
    for (int i = 0; i < 5; i++) { //Este bucle for se utiliza para iterar sobre cada uno de los primeros cinco caracteres de la cadena randomStr.
      lcd.setCursor(i, 1); // Establece la posición del cursor en la pantalla LCD en la columna i (que varía de 0 a 4) y en la fila 1.
      lcd.print(randomStr[i]); 
      delay(1000);
      lcd.setCursor(i, 1);
      lcd.print(" "); // Imprime un espacio en blanco en la posición actual del cursor. Esto tiene el efecto de "borrar".
    }

    // Ingresar código
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Insert code:");
    Serial.println(randomStr);
    char numeros[6]; // Se declara un array de caracteres llamado numeros con capacidad para almacenar 6 caracteres. Este array se utilizará para almacenar el código ingresado por el jugador.
    numeros[5] = '\0'; // Se coloca el carácter nulo ('\0') en la posición 5 del array numeros. Esto se hace para garantizar que la cadena de caracteres esté correctamente terminada con un carácter nulo.
    for (int i = 0; i < 5; i++) { // Iterar 5 veces.
      char key2 = '\0'; // Se declara una variable key2 y se inicializa con el carácter nulo ('\0'). Esta variable se utilizará para almacenar el dígito ingresado por el jugador.
      while (key2 < '0' || key2 > '9') { // Este bucle while se ejecuta mientras el valor de key2 no esté en el rango de caracteres numéricos (es decir, entre '0' y '9', inclusive). Esto asegura que solo se acepten dígitos numéricos como entrada.
        key2 = getKey(); // Se llama a la función getKey() para obtener la tecla presionada por el jugador y se almacena en la variable key2.
        
        // Borrar dígito
        if (key2 == '#') { // Se verifica si la tecla presionada por el usuario es '#'. Si es así, se realiza una acción para permitir al usuario borrar el último dígito ingresado.
          if (i > 0) {
            lcd.setCursor(i - 1, 1);
            lcd.print(" ");
            lcd.setCursor(i - 1, 1);
            i -= 1; // Se decrementa el contador i en 1 para que el programa recuerde que se ha eliminado un dígito y que la siguiente entrada del jugador debe ser en la posición anterior.
          }
        }
      }
      
      numeros[i] = key2; // Se guarda el dígito ingresado por el jugador en la posición i del array numeros.
      lcd.setCursor(i, 1);
      lcd.print(key2); // Se coloca el cursor en la posición i de la fila 1 y se imprime el dígito ingresado por el jugador en esa posición, mostrandole lo que va escribiendo.
      delay(250);
    }

    // Comparar el código ingresado con el número aleatorio generado
    if (strcmp(numeros, randomStr) == 0) { // Compara el código ingresado por el jugador (almacenado en el array numeros) con el código aleatorio generado anteriormente (almacenado en el array randomStr). La función strcmp() devuelve 0 si las cadenas son idénticas.
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Correct!!");
      digitalWrite(greenLed, HIGH); // Enciende la LED verde.
      delay(3000);
      digitalWrite(greenLed, LOW); // Apaga la luz verde después de 3 segundos.

      // Nivel 2
      lcd.clear();
      lcd.print("Press B"); 
      while (getKey() != 'B'); // Se le pide al jugador que presione la tecla B cuando esté listo para continuar al nivel 2.

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

      // Filtrar los caracteres no numéricos del código aleatorio
      for (int i = 0; i < 6; i++) {
        if (randomStr2[i] < '0' || randomStr2[i] > '9') {
          ak = random(1, 10) + '0'; // Generar un nuevo valor de ak
    randomStr2[i] = ak; // Reemplazar el carácter no numérico por ak
        }
      }

      // Mostrar el número aleatorio filtrado uno por uno, desvaneciéndose en la pantalla LCD
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
        char randomStr3[8]; // Cambiar tamaño a 8 para el nivel 3
        randomStr3[7] = '\0';
        itoa(randomNum3, randomStr3, 10);

        // Filtrar los caracteres no numéricos del código aleatorio
        for (int i = 0; i < 7; i++) {
          if (randomStr3[i] < '0' || randomStr3[i] > '9') {
            randomStr3[i] = ak;
          }
        }

        // Mostrar el número aleatorio filtrado uno por uno, desvaneciéndose en la pantalla LCD
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
          char randomStr4[9]; // Cambiar tamaño a 9 para el nivel 4
          randomStr4[8] = '\0';
          itoa(randomNum4, randomStr4, 10);

          // Filtrar los caracteres no numéricos del código aleatorio
          for (int i = 0; i < 8; i++) {
            if (randomStr4[i] < '0' || randomStr4[i] > '9') {
              randomStr4[i] = ak;
            }
          }

          // Mostrar el número aleatorio filtrado uno por uno, desvaneciéndose en la pantalla LCD
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
          } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Incorrect!");
            digitalWrite(redLed, HIGH);
            delay(3000);
            digitalWrite(redLed, LOW);
            
            // Reiniciar loop para volver al nivel 1
            for (;;) loop();
          }
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Incorrect!");
          digitalWrite(redLed, HIGH);
          delay(3000);
          digitalWrite(redLed, LOW);
          // Reiniciar loop para volver al nivel 1
          for (;;) loop();
        }
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Incorrect!");
        digitalWrite(redLed, HIGH);
        delay(3000);
        digitalWrite(redLed, LOW);
      }
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Incorrect!");
      digitalWrite(redLed, HIGH);
      delay(3000);
      digitalWrite(redLed, LOW);
    }
  }
}

char getKey() {
  char key = '\0';
  for (int i = 0; i < ROWS; i++) { // Itera sobre las filas de la matriz de teclas.
    digitalWrite(colPins[i], LOW); 
    for (int j = 0; j < COLS; j++) { // itera sobre las columnas de la matriz de teclas, dentro de la fila previamente selecionada.
      if (digitalRead(rowPins[j]) == LOW) { // Se verifica si la fila está activada (es decir, si se ha presionado una tecla en esa fila). Se lee el estado del pin de la fila correspondiente.
        key = keys[j][i]; // Si se detecta que se ha presionado una tecla en la fila actual, se asigna el valor de la tecla correspondiente en la matriz keys a la variable key. La matriz keys almacena los caracteres asociados a cada tecla en el teclado.
        while (digitalRead(rowPins[j]) == LOW); // Después de detectar una tecla presionada, este bucle while espera hasta que la tecla se suelte.
      }
    }
    digitalWrite(colPins[i], HIGH); // Una vez que se ha completado la lectura de la fila actual, se restablece el pin de la columna correspondiente a alto para desactivar la lectura de la fila.
  }
  return key; // Se devuelve el valor de la tecla presionada almacenado en la variable key. Si no se ha presionado ninguna tecla, key sigue siendo el carácter nulo '\0'.
}
