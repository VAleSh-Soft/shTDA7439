#include <Arduino.h>
#include <Wire.h>
#include "shTDA7439.h"

shTDA7439::shTDA7439() {}

void shTDA7439::begin(TwoWire *wire)
{
  _wire = wire;
  _wire->begin();
}

void shTDA7439::setWire(TwoWire *wire)
{
  _wire = wire;
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
  volume = (volume) ? ((volume <= 48) ? 48 - volume : 0) : TDA7439_MUTE;
  writeWire(TDA7439_VOLUME, volume);
}

void shTDA7439::setTimbre(int8_t val, TDA7439_bands range)
{
  val = (val < -7) ? -7 : ((val > 7) ? 7 : val);
  val = (val > 0) ? 15 - val : val + 7;
  writeWire((uint8_t)range, val);
}

void shTDA7439::mute()
{
  writeWire(TDA7439_VOLUME, TDA7439_MUTE);
}

void shTDA7439::spkAtt(uint8_t att_r, uint8_t att_l)
{
  // Mainly used to override the default attenuation of mute at power up
  // can be used for balance with some simple code changes here.
  if (att_l > 79)
  {
    att_l = 79;
  }
  if (att_r > 79)
  {
    att_r = 79;
  }

  writeWire(TDA7439_RATT, att_r);
  writeWire(TDA7439_LATT, att_l);
}

void shTDA7439::writeWire(uint8_t reg, uint8_t data)
{
  _wire->beginTransmission(TDA7439_address);
  _wire->write(reg);
  _wire->write(data);
  _wire->endTransmission();
}
