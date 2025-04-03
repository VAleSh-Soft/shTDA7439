#ifndef TDA7439_H
#define TDA7439_H

#include <Wire.h>

#define TDA7439_address 0x44

// Sub addresses
#define TDA7439_INPUT_SEL 0x00
#define TDA7439_INPUT_GAIN 0x01
#define TDA7439_VOLUME 0x02
#define TDA7439_BASS 0x03
#define TDA7439_MIDDLE 0x04
#define TDA7439_TREBBLE 0x05

#define TDA7439_RATT 0x06
#define TDA7439_LATT 0x07

// выбор входного канала
enum TDA7439_input : uint8_t
{
	INPUT_4, // вход 4
	INPUT_3, // вход 3
	INPUT_2, // вход 2
	INPUT_1	 // вход 1
};

// диапазон регулировки тембра
enum TDA7439_bands : uint8_t
{
	BASS = 0x03,	 // низкие частоты
	MIDDLE = 0x04, // средние частоты
	TREBBLE = 0x05 // высокие частоты
};

#define TDA7439_MUTE 0x38

#include <Arduino.h>
class shTDA7439
{
public:
	/**
	 * @brief конструктор класса
	 *
	 */
	shTDA7439();

	/**
	 * @brief инициализация shTDA7439
	 *
	 */
	void begin(TwoWire *wire = &Wire);

	/**
	 * @brief установка объекта Wire для работы с shTDA7439
	 *
	 * @param wire
	 */
	void setWire(TwoWire *wire);

	/**
	 * @brief установка входного канала
	 *
	 * @param input выбранный канал - INPUT_4, INPUT_3, INPUT_2, INPUT_1
	 */
	void setInput(TDA7439_input input);

	/**
	 * @brief установка усиления на входе
	 *
	 * @param gain уровень усиления; 0..15
	 */
	void setInputGain(uint8_t gain);

	/**
	 * @brief установка громкости
	 *
	 * @param volume уровень громкости; 0..48
	 */
	void setVolume(uint8_t volume);

	/**
	 * @brief установка тембра
	 *
	 * @param val устанавливаемое значение; -7..7
	 * @param range диапазон - BASS, MIDDLE, TREBBLE
	 */
	void setTimbre(int8_t val, TDA7439_bands range);

	/**
	 * @brief отключение звука
	 *
	 */
	void mute();

	/**
	 * @brief установка баланса
	 *
	 * @param att_r данные баланса; -79..79 (db)
	 */
	void setBalance(int8_t _balance);

	/**
	 * @brief установка значения уровня приглушения громкости на выходе
	 *
	 * @param _spk_att // 0..79 (db)
	 */
	void setSpeakerAtt(int8_t _spk_att);

private:
	TwoWire *_wire = nullptr;
	uint8_t spk_att = 0; // уровень приглушения громкости на выходе; 0..79 (db)
	int8_t balance = 0;  // баланс; -79..79 (db)

	void writeWire(uint8_t reg, uint8_t data);
};

#endif // TDA7439_H
