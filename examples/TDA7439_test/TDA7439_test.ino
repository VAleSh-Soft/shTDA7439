#include <Wire.h>
#include <shTDA7439.h>

shTDA7439 tda;

void setup()
{
  tda.begin();

  tda.setInput(INPUT_1);     // выбор входа
  tda.setInputGain(0);       // 0..15 - предусиление на входе
  tda.setVolume(48);         // 0..48 - громкость
  tda.setTimbre(0, BASS);    // -7..+7 - установка басов
  tda.setTimbre(0, MIDDLE);  // -7..+7 - установка средних частот
  tda.setTimbre(0, TREBBLE); // -7..+7 - установка высоких частот
  tda.setSpeakerAtt(4);      // 0..79 - приглушение звука на выходе
  tda.setBalance(0);         // -79..79 - установка баланса

  delay(1000);
}

void loop()
{
}
