#include "iarduino_Wattmeter.h"
//		Объявление экземпляра класса			([адрес модуля])
		iarduino_Wattmeter::iarduino_Wattmeter	(uint8_t k){WTM_chip_ADDR=k;}

//		Инициация работы модуля					()
void	iarduino_Wattmeter::begin				(){
			I2C_func_BEGIN();														//	Инициируем работу по шине I2C
}

//		Установка режима работы вывода			()
void	iarduino_Wattmeter::read				()	{
			WTM_rgst_ADDR=WTM_REG_CONFIGURATION;
			I2C_func_READ();														//	Читаем данные из указанного регистра в переменные: WTM_data_MSB и WTM_data_LSB
			Serial.print("CONFIGURATION =\t0x");
			Serial.print((uint16_t)((WTM_data_MSB<<8)+WTM_data_LSB),HEX);
			Serial.print(";\t\tRESULT = ");
			Serial.println(I2C_mass_STATUS[2]?"Ok! :)":"No :(");
			WTM_rgst_ADDR=WTM_REG_VOLTAG_SHUNT;
			I2C_func_READ();														//	Читаем данные из указанного регистра в переменные: WTM_data_MSB и WTM_data_LSB
			Serial.print("VOLTAG_SHUNT =\t0x");
			Serial.print((uint16_t)((WTM_data_MSB<<8)+WTM_data_LSB),HEX);
			Serial.print(";\t\tRESULT = ");
			Serial.println(I2C_mass_STATUS[2]?"Ok! :)":"No :(");
			WTM_rgst_ADDR=WTM_REG_VOLTAGE_BUS;
			I2C_func_READ();														//	Читаем данные из указанного регистра в переменные: WTM_data_MSB и WTM_data_LSB
			Serial.print("VOLTAGE_BUS =\t0x");
			Serial.print((uint16_t)((WTM_data_MSB<<8)+WTM_data_LSB),HEX);
			Serial.print(";\t\tRESULT = ");
			Serial.println(I2C_mass_STATUS[2]?"Ok! :)":"No :(");
			WTM_rgst_ADDR=WTM_REG_POWER;
			I2C_func_READ();														//	Читаем данные из указанного регистра в переменные: WTM_data_MSB и WTM_data_LSB
			Serial.print("POWER =\t\t0x");
			Serial.print((uint16_t)((WTM_data_MSB<<8)+WTM_data_LSB),HEX);
			Serial.print(";\t\tRESULT = ");
			Serial.println(I2C_mass_STATUS[2]?"Ok! :)":"No :(");
			WTM_rgst_ADDR=WTM_REG_CURRENT;
			I2C_func_READ();														//	Читаем данные из указанного регистра в переменные: WTM_data_MSB и WTM_data_LSB
			Serial.print("CURRENT =\t0x");
			Serial.print((uint16_t)((WTM_data_MSB<<8)+WTM_data_LSB),HEX);
			Serial.print(";\t\tRESULT = ");
			Serial.println(I2C_mass_STATUS[2]?"Ok! :)":"No :(");
			WTM_rgst_ADDR=WTM_REG_CALIBRATION;
			I2C_func_READ();														//	Читаем данные из указанного регистра в переменные: WTM_data_MSB и WTM_data_LSB
			Serial.print("CALIBRATION =\t0x");
			Serial.print((uint16_t)((WTM_data_MSB<<8)+WTM_data_LSB),HEX);
			Serial.print(";\t\tRESULT = ");
			Serial.println(I2C_mass_STATUS[2]?"Ok! :)":"No :(");
			Serial.println("==============================================");
}

/** внутренние функции для работы с шиной I2C **/
void	iarduino_Wattmeter::I2C_func_START		()										{int I2C_var_I=0;    I2C_mass_STATUS[2]=1; TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA); while(!(TWCR & _BV(TWINT))){I2C_var_I++; if(I2C_var_I>I2C_mass_STATUS[1]){I2C_mass_STATUS[2]=0; break;}} I2C_mass_STATUS[3] = TWSR & 0xF8; if(I2C_mass_STATUS[3]!=0x08){I2C_mass_STATUS[2]=0;}}
void	iarduino_Wattmeter::I2C_func_RESTART	()										{int I2C_var_I=0; if(I2C_mass_STATUS[2]){  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA); while(!(TWCR & _BV(TWINT))){I2C_var_I++; if(I2C_var_I>I2C_mass_STATUS[1]){I2C_mass_STATUS[2]=0; break;}} I2C_mass_STATUS[3] = TWSR & 0xF8; if(I2C_mass_STATUS[3]!=0x10){I2C_mass_STATUS[2]=0;}}}
void	iarduino_Wattmeter::I2C_func_SEND_ID	(uint8_t I2C_byte_ID, bool I2C_bit_RW)	{int I2C_var_I=0; if(I2C_mass_STATUS[2]){  TWDR = (I2C_byte_ID<<1)+I2C_bit_RW; TWCR = _BV(TWINT) | _BV(TWEN); while(!(TWCR & _BV(TWINT))){I2C_var_I++; if(I2C_var_I>I2C_mass_STATUS[1]){I2C_mass_STATUS[2]=0; break;}} I2C_mass_STATUS[3] = TWSR & 0xF8; if(I2C_bit_RW){ if(I2C_mass_STATUS[3]!=0x40){I2C_mass_STATUS[2]=0;}}else{if(I2C_mass_STATUS[3]!=0x18){I2C_mass_STATUS[2]=0;}}}}
void	iarduino_Wattmeter::I2C_func_WRITE_BYTE	(uint8_t I2C_byte_DATA)					{int I2C_var_I=0; if(I2C_mass_STATUS[2]){  TWDR = I2C_byte_DATA; TWCR = _BV(TWINT) | _BV(TWEN); while(!(TWCR & _BV(TWINT))){I2C_var_I++; if(I2C_var_I>I2C_mass_STATUS[1]){I2C_mass_STATUS[2]=0; break;}} I2C_mass_STATUS[3] = TWSR & 0xF8; if(I2C_mass_STATUS[3]!=0x28){I2C_mass_STATUS[2]=0;}}}
uint8_t	iarduino_Wattmeter::I2C_func_READ_BYTE	(bool I2C_bit_ACK)						{int I2C_var_I=0; if(I2C_mass_STATUS[2]){  TWCR = _BV(TWINT) | _BV(TWEN) | I2C_bit_ACK<<TWEA; while(!(TWCR & _BV(TWINT))){I2C_var_I++; if(I2C_var_I>I2C_mass_STATUS[1]){I2C_mass_STATUS[2]=0; break;}} I2C_mass_STATUS[3] = TWSR & 0xF8; if(I2C_bit_ACK){if(I2C_mass_STATUS[3]!=0x50){I2C_mass_STATUS[2]=0;}}else{if(I2C_mass_STATUS[3]!=0x58){I2C_mass_STATUS[2]=0;}} return TWDR;}else{return 0xFF;}}
void	iarduino_Wattmeter::I2C_func_STOP		()										{int I2C_var_I=0; TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO); while(!(TWCR & _BV(TWSTO))){I2C_var_I++; if(I2C_var_I>I2C_mass_STATUS[1]){I2C_mass_STATUS[2]=0; break;}} delayMicroseconds(20);}
void	iarduino_Wattmeter::I2C_func_BEGIN		()										{    I2C_mass_STATUS[2]=1; TWBR=((F_CPU/(I2C_mass_STATUS[0]*1000))-16)/2; if(TWBR<10){TWBR=10;} TWSR&=(~(_BV(TWPS1)|_BV(TWPS0)));}

void	iarduino_Wattmeter::I2C_func_READ(){										//	Читаем данные из модуля
//			I2C_func_START();														//	Отправляем команду START
//			I2C_func_SEND_ID(WTM_chip_ADDR, 0);										//	Отправляем адрес модуля и бит RW=0 (запись данных в датчик)
//			I2C_func_WRITE_BYTE(WTM_rgst_ADDR);										//	Отправляем адрес регистра, данные которого требуется прочитать
//			I2C_func_RESTART();														//	Отправляем команду RESTART
//			I2C_func_SEND_ID(WTM_chip_ADDR, 1);										//	Отправляем адрес модуля и бит RW=1 (чтение данных из датчика)
//			WTM_data_MSB=I2C_func_READ_BYTE(true);									//	Читаем старший байт данных с отправкой бита ACK
//			WTM_data_LSB=I2C_func_READ_BYTE(false);									//	Читаем младший байт данных с отправкой бита NACK
//			I2C_func_STOP();														//	Отправляем команду STOP
			
			
			I2C_func_START();														//	Отправляем команду START
			I2C_func_SEND_ID(WTM_chip_ADDR, 0);										//	Отправляем адрес модуля и бит RW=0 (запись данных в датчик)
			I2C_func_WRITE_BYTE(WTM_rgst_ADDR);										//	Отправляем адрес регистра, данные которого требуется прочитать
			I2C_func_STOP();														//	Отправляем команду STOP
			delay(2);
			I2C_func_START();														//	Отправляем команду START
			I2C_func_SEND_ID(WTM_chip_ADDR, 1);										//	Отправляем адрес модуля и бит RW=1 (чтение данных из датчика)
			WTM_data_MSB=I2C_func_READ_BYTE(true);									//	Читаем старший байт данных с отправкой бита ACK
			WTM_data_LSB=I2C_func_READ_BYTE(false);									//	Читаем младший байт данных с отправкой бита NACK
			I2C_func_STOP();														//	Отправляем команду STOP
			delay(2);
}

void	iarduino_Wattmeter::I2C_func_WRITE(){										//	Записываем данные в датчик
			I2C_func_START();														//	Отправляем команду START
			I2C_func_SEND_ID(WTM_chip_ADDR, 0);										//	Отправляем адрес модуля и бит RW=0 (запись данных в датчик)
			I2C_func_WRITE_BYTE(WTM_rgst_ADDR);										//	Отправляем адрес регистра, данные которому требуется передать
			I2C_func_WRITE_BYTE(WTM_data_MSB);										//	Отправляем старший байт данных
			I2C_func_WRITE_BYTE(WTM_data_LSB);										//	Отправляем младший байт данных
			I2C_func_STOP();														//	Отправляем команду STOP
}
