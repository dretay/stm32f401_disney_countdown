#pragma once

#include <stdbool.h>
#include <string.h>
#include "TM16XXFonts.h"
#include "minmax.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "stm32f4xx_ll_gpio.h"

struct tm1638qyf {
	void(*init)(bool activateDisplay, u8 intensity);
	void(*setDisplayToString)(const char* string, const u8 dots);
	u16(*getButtons)(void);
};

extern const struct tm1638qyf TM1638QYF;
