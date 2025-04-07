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
	BASS = TDA7439_BASS,			// низкие частоты
	MIDDLE = TDA7439_MIDDLE,	// средние частоты
	TREBBLE = TDA7439_TREBBLE // высокие частоты
};

#define TDA7439_MUTE 0x38
#define TDA7439_SP_MUTE 0x78

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
	 * @brief установка входного канала
	 *
	 * @param input выбранный канал - INPUT_4, INPUT_3, INPUT_2, INPUT_1
	 */
	void setInput(const TDA7439_input input);

	/**
	 * @brief установка усиления на входе
	 *
	 * @param gain 0..15
	 */
	void setInputGain(uint8_t gain);

	/**
	 * @brief установка громкости
	 *
	 * @param volume 0..47
	 */
	void setVolume(uint8_t volume);

	/**
	 * @brief установка полосы эквалайзера
	 *
	 * @param val -7..7
	 * @param range диапазон - BASS, MIDDLE, TREBBLE
	 */
	void setEqRange(int8_t val, const TDA7439_bands range);

	/**
	 * @brief установка тембра сразу по всем диапазонам
	 *
	 * @param bass низкие частоты; -7..7
	 * @param middle средние частоты; -7..7
	 * @param trebble высокие частоты; -7..7
	 */
	void setTimbre(int8_t bass, int8_t middle, int8_t trebble);

	/**
	 * @brief отключение звука
	 *
	 */
	void mute();

	/**
	 * @brief установка баланса
	 *
	 * @param att_r -79..79 (db)
	 */
	void setBalance(const int8_t balance);

	/**
	 * @brief установка значения уровня приглушения громкости на выходе
	 *
	 * @param spk_att 0..79 (db)
	 */
	void setSpeakerAtt(const int8_t spk_att);

private:
	TwoWire *_wire = nullptr;
	uint8_t _spk_att = 0; // уровень приглушения громкости на выходе; 0..79 (db)
	int8_t _balance = 0;	// баланс; -79..79 (db)

	void writeWire(const uint8_t reg, const uint8_t size);
	void checkEqData(int8_t &val);
};

#endif // TDA7439_H
