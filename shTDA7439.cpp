#include <Arduino.h>
#include <Wire.h>
#include "shTDA7439.h"

shTDA7439::shTDA7439() {}

void shTDA7439::begin(TwoWire *wire)
{
  _wire = wire;
  _wire->begin();
}

void shTDA7439::setInput(TDA7439_input input)
{
  writeWire(TDA7439_INPUT_SEL, (uint8_t)input);
}

void shTDA7439::setInputGain(uint8_t gain)
{
  if (gain > 15)
  {
    gain = 15;
  }
  writeWire(TDA7439_INPUT_GAIN, gain);
}

void shTDA7439::setVolume(uint8_t volume)
{
  volume = (volume) ? ((volume <= 47) ? 47 - volume : 0) : TDA7439_MUTE;
  writeWire(TDA7439_VOLUME, volume);
}

void shTDA7439::setEqRange(int8_t val, TDA7439_bands range)
{
  checkEqData(val);
  writeWire((uint8_t)range, val);
}

void shTDA7439::setTimbre(int8_t bass, int8_t middle, int8_t trebble)
{
  checkEqData(bass);
  checkEqData(middle);
  checkEqData(trebble);

  writeWire(TDA7439_BASS, bass);
  writeWire(TDA7439_MIDDLE, middle);
  writeWire(TDA7439_TREBBLE, trebble);
}

void shTDA7439::mute()
{
  writeWire(TDA7439_VOLUME, TDA7439_MUTE);
}

void shTDA7439::setBalance(int8_t balance)
{
  _balance = (balance > 79) ? 79 : ((balance < -79) ? -79 : balance);

  uint8_t right = (_balance < 0) ? -1 * _balance + _spk_att : _spk_att;
  uint8_t left = (_balance > 0) ? _balance + _spk_att : _spk_att;

  if (right > 79)
  {
    right = 79;
  }
  if (left > 79)
  {
    left = 79;
  }

  writeWire(TDA7439_RATT, right);
  writeWire(TDA7439_LATT, left);
}

void shTDA7439::setSpeakerAtt(int8_t spk_att)
{
  _spk_att = (spk_att > 79) ? 79 : spk_att;
  setBalance(_balance);
}

void shTDA7439::writeWire(uint8_t reg, uint8_t data)
{
  _wire->beginTransmission(TDA7439_address);
  _wire->write(reg);
  _wire->write(data);
  _wire->endTransmission();
}

void shTDA7439::checkEqData(int8_t &val)
{
  val = (val < -7) ? -7 : ((val > 7) ? 7 : val);
  val = (val > 0) ? 15 - val : val + 7;
}
