#include "application.h"
#include "stm32f4xx_hal.h"
#include "TM1638QYF.h"
#include "string.h"
static View *summary_view;

extern RTC_HandleTypeDef hrtc;

static void enable_backup_sram(void){
    /*DBP : Enable access to Backup domain */
    HAL_PWR_EnableBkUpAccess();
    /*PWREN : Enable backup domain access  */
    __HAL_RCC_PWR_CLK_ENABLE();
    /*BRE : Enable backup regulator
      BRR : Wait for backup regulator to stabilize */
    HAL_PWREx_EnableBkUpReg();
   /*DBP : Disable access to Backup domain */
    HAL_PWR_DisableBkUpAccess();
}

static void init()
{
	enable_backup_sram();
	//first run
	if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) == RESET){
		TM1638QYF.init(true,0);
		TM1638QYF.setDisplayToString("init....",0);
	}
	gfxInit();
}

static u16 prompt_value(char* prompt, u16 max){
	char digits[4] = {0};
	u8 dCnt =0;
	TM1638QYF.setDisplayToString(prompt,0);
	while(true){
		u16 buttons = TM1638QYF.getButtons();
		char next = ' ';
		switch(buttons){
		case 1: //1
			next = '1';
			break;
		case 2: //2
			next = '2';
			break;
		case 4: //3
			next = '3';
			break;
		case 16: //4
			next = '4';
			break;
		case 32: //5
			next = '5';
			break;
		case 64: //6
			next = '6';
			break;
		case 256://7
			next = '7';
			break;
		case 512: //8
			next = '8';
			break;
		case 1024: //9
			next = '9';
			break;
		case 4096: //*
			next = '*';
			break;
		case 8192: //0
			next = '0';
			break;
		case 16384: //#
			next = '#';
			break;
		}
		if(buttons != 0){
			HAL_Delay(500);
			if(next == '#'){
				return atoi(digits);
			}
			else if (next == '*' && dCnt >= 0){
				digits[--dCnt] = ' ';
			}
			else if(dCnt < 4){
				char newDigits[4] = {0};
				memcpy(newDigits, digits,4);
				newDigits[dCnt] = next;
				u8 newVal = atoi(newDigits);
				if (newVal < max){
					digits[dCnt++] = next;
				}
			}
			char values [9];
			snprintf(values,9,"%s%s",prompt, digits);
			TM1638QYF.setDisplayToString(values,0);
		}
	}
}
static void set_wakeup(u32 wakeup_seconds){
//	HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
	u32 wakeup_counter = (wakeup_seconds*1000) / 0.448;
	if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, wakeup_counter, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK){
		Error_Handler();
	}
}

static void HW_EnterStandbyMode(){

	/* Clear the WU FLAG */
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);

	/* clear the RTC Wake UP (WU) flag */
	__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);


	HAL_PWR_EnterSTANDBYMode();

}

static void print_update(){
	u32 DAY_COUNTDOWN = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1);
	u32 HOUR_COUNTER = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
	if(DAY_COUNTDOWN > 0){
		HOUR_COUNTER++;
		if(HOUR_COUNTER > 23){
			DAY_COUNTDOWN--;
			HOUR_COUNTER = 0;
			summary_view = SummaryView.init(DAY_COUNTDOWN);
			summary_view->render();
		}
		HAL_PWR_EnableBkUpAccess();
		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, DAY_COUNTDOWN);
		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, HOUR_COUNTER);
		HAL_PWR_DisableBkUpAccess();

	}
}

static void run(void)
{
	//first run
	if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) == RESET){
		TM1638QYF.init(true,0);
		u32 HOUR_COUNTER = prompt_value("HOUR",23);
		u32 DAY_COUNTDOWN = prompt_value("DAYS", 999);
		TM1638QYF.setDisplayToString("",0);

		summary_view = SummaryView.init(DAY_COUNTDOWN);
		summary_view->render();

		HAL_PWR_EnableBkUpAccess();
		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, DAY_COUNTDOWN);
		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, HOUR_COUNTER);
		HAL_PWR_DisableBkUpAccess();
	}
	else{
		// clear the flag
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
	}
	print_update();
	HW_EnterStandbyMode();
}

const struct application Application = {
	.init = init,
	.run = run,

};
