#include "TM1638QYF.h"

#define	GPIO_PINMODE_INPUT(x)		{LL_GPIO_SetPinMode(TM1638_##x##_GPIO_Port, TM1638_##x##_Pin,LL_GPIO_MODE_INPUT);}
#define	GPIO_PINMODE_OUTPUT(x)		{LL_GPIO_SetPinMode(TM1638_##x##_GPIO_Port, TM1638_##x##_Pin,LL_GPIO_MODE_OUTPUT);}
#define	GPIO_SET_PULLUP(x)			{LL_GPIO_SetPinPull(TM1638_##x##_GPIO_Port, TM1638_##x##_Pin,LL_GPIO_PULL_UP);}
#define	GPIO_UNSET_PULLUP(x)		{LL_GPIO_SetPinPull(TM1638_##x##_GPIO_Port, TM1638_##x##_Pin,LL_GPIO_PULL_NO);}
#define	GPIO_SET(x)					{HAL_GPIO_WritePin(TM1638_##x##_GPIO_Port, TM1638_##x##_Pin,GPIO_PIN_SET);}

#define	GPIO_RESET(x)				{HAL_GPIO_WritePin(TM1638_##x##_GPIO_Port, TM1638_##x##_Pin,GPIO_PIN_RESET);}
#define	GPIO_READ(x)				({HAL_GPIO_ReadPin(TM1638_##x##_GPIO_Port, TM1638_##x##_Pin);})


static void send(u8 data){
	for (int i = 0; i < 8; i++) {
		GPIO_RESET(CLK);

		if(data & 1){GPIO_SET(DIO);}
		else{GPIO_RESET(DIO);}
		data >>= 1;

		GPIO_SET(CLK);
	  }
}
static void sendCommand(u8 cmd)
{
	GPIO_RESET(STB);
	send(cmd);
	GPIO_SET(STB);
}

static void init(bool activateDisplay, u8 intensity){
	GPIO_SET(STB);
	GPIO_SET(CLK);


	sendCommand(0x40);
	sendCommand(0x80 | (activateDisplay ? 8 : 0) | MIN(7, intensity));

	GPIO_RESET(STB);
	send(0xC0);
	for (int i = 0; i < 16; i++) {
		send(0x00);
	}
	GPIO_SET(STB);

	sendCommand(0x80 | (activateDisplay ? 8 : 0) | MIN(7, intensity));
}
static void sendData(u8 address, u8 data){
  sendCommand(0x44);
  GPIO_RESET(STB);
  send(0xC0 | address);
  send(data);
  GPIO_SET(STB);
}
static void sendChar(u8 pos, u8 data, bool dot){
	sendData(pos << 1, data | (dot ? 0b10000000 : 0));
}
static void setDisplay(const u8 values[], u8 length)
{
	u8 displays=8;
	for (int i = 0; i < displays; i++) {
		int val = 0;

		for (int j = 0; j < length; j++) {
			val |= ((values[j] >> i) & 1) << (displays - j - 1);
		}

		sendData(i << 1, val);
	}
}
static void setDisplayToString(const char* string, const u8 dots){
	u8 displays=8;
	u8 values[displays];
	bool done = false;
//	u8 font = FONT_DEFAULT;

	memset(values, 0, displays * sizeof(u8));

	for (int i = 0; i < displays; i++) {
		if (!done && string[i] != '\0') {
		  values[i] = FONT_DEFAULT[string[i] - 32] | (((dots >> (displays - i - 1)) & 1) << 7);
		} else {
		  done = true;
		  values[i] = (((dots >> (displays - i - 1)) & 1) << 7);
		}
	}

	setDisplay(values, displays);
}
static u8 receive(){
  u8 temp = 0;

  // Pull-up on
  GPIO_PINMODE_INPUT(DIO);
  GPIO_SET_PULLUP(DIO);

  for (int i = 0; i < 8; i++) {
    temp >>= 1;

    GPIO_RESET(CLK);

    if (GPIO_READ(DIO)) {
      temp |= 0x80;
    }

    GPIO_SET(CLK);
  }

  // Pull-up off
  GPIO_PINMODE_OUTPUT(DIO);
  GPIO_UNSET_PULLUP(DIO);

  return temp;
}
static u16 getButtons(void){
	  u16 keys = 0;

	  GPIO_RESET(STB);
	  send(0x42); // B01000010 Read the key scan data
	  for (int i = 0; i < 4; i++) {
		  u8 rec = receive();

		  rec = (((rec & 0b1000000) >> 3 | (rec & 0b100)) >> 2) | (rec & 0b100000) | (rec & 0b10) << 3;

		  keys |= ((rec & 0x000F) << (i << 1)) | (((rec & 0x00F0) << 4) << (i << 1));
	  }
	  GPIO_SET(STB);

	  return keys;
}


const struct tm1638qyf TM1638QYF = {
	.init = init,
	.setDisplayToString = setDisplayToString,
	.getButtons = getButtons,
};
