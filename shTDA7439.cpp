#include <Arduino.h>
#include <Wire.h>
#include "shTDA7439.h"

static uint8_t wire_data[3];

shTDA7439::shTDA7439() {}

void shTDA7439::begin(TwoWire *wire)
{
  _wire = wire;
  _wire->begin();
}

void shTDA7439::setInput(const TDA7439_input input)
{
  wire_data[0] = (uint8_t)input;
  writeWire(TDA7439_INPUT_SEL, 1);
}

void shTDA7439::setInputGain(uint8_t gain)
{
  if (gain > 15)
  {
    gain = 15;
  }

  wire_data[0] = gain;
  writeWire(TDA7439_INPUT_GAIN, 1);
}

void shTDA7439::setVolume(uint8_t volume)
{
  volume = (volume) ? ((volume <= 47) ? 47 - volume : 0) : TDA7439_MUTE;
  wire_data[0] = volume;
  writeWire(TDA7439_VOLUME, 1);
}

void shTDA7439::setEqRange(int8_t val, const TDA7439_bands range)
{
  checkEqData(val);
  wire_data[0] = val;
  writeWire((uint8_t)range, 1);
}

void shTDA7439::setTimbre(int8_t bass, int8_t middle, int8_t trebble)
{
  checkEqData(bass);
  checkEqData(middle);
  checkEqData(trebble);

  wire_data[0] = bass;
  wire_data[1] = middle;
  wire_data[2] = trebble;

  writeWire(TDA7439_BASS, 3);
}

void shTDA7439::mute()
{
  wire_data[0] = TDA7439_MUTE;
  writeWire(TDA7439_VOLUME, 1);
}

void shTDA7439::setBalance(const int8_t balance)
{
  _balance = (balance > 79) ? 79 : ((balance < -79) ? -79 : balance);

  uint8_t right = (_balance < 0) ? -1 * _balance + _spk_att : _spk_att;
  uint8_t left = (_balance > 0) ? _balance + _spk_att : _spk_att;

  if (right >= 79)
  {
    right = TDA7439_SP_MUTE;
  }
  if (left >= 79)
  {
    left = TDA7439_SP_MUTE;
  }

  wire_data[0] = right;
  wire_data[1] = left;

  writeWire(TDA7439_RATT, 2);
}

void shTDA7439::setSpeakerAtt(const int8_t spk_att)
{
  _spk_att = (spk_att >= 79) ? TDA7439_SP_MUTE : spk_att;
  setBalance(_balance);
}

void shTDA7439::writeWire(const uint8_t reg, const uint8_t size)
{
  _wire->beginTransmission(TDA7439_address);
  _wire->write(reg + 0x10);
  for (uint8_t i = 0; i < size; i++)
  {
    _wire->write(wire_data[i]);
  }
  _wire->endTransmission();
}

void shTDA7439::checkEqData(int8_t &val)
{
  val = (val < -7) ? -7 : ((val > 7) ? 7 : val);
  val = (val > 0) ? 15 - val : val + 7;
}
