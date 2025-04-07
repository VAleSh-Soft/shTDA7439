/**
 * @file TDA7439_test.ino
 * @author Vladimir Shatalov (valesh-soft@yandex.ru)
 * 
 * @brief демонстрационый пример возможностей библиотеки
 * 
 * @version 1.0
 * @date 03.04.2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <shTDA7439.h>

shTDA7439 tda;

void setup()
{
  tda.begin();

  tda.setInput(INPUT_1);   // выбор входа
  tda.setInputGain(0);     // 0..15 - предусиление на входе
  tda.setVolume(20);       // 0..47 - громкость
  tda.setTimbre(4, -1, 3); // установка тембра (низкие, средние, высокие частоты; -7..7)
  tda.setSpeakerAtt(4);    // 0..79 - приглушение звука на выходе
  tda.setBalance(0);       // -79..79 - установка баланса
}

void loop() {}
