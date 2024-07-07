
# Disney EINK Countdown Clock 

> A eink-based countdown clock to help get kids excited for a family vacation.

I have young kids, and every year we take a family Disney cruise. To help them get excited I built a eink-based countdown clock that we can put in the kitchen so they can watch the days tick down till their next cruise. It was a fun project to build, so I'm posting it here in case it inspires anyone else to build something similar. 

### Hardware
- [Waveshare 7.5 EINK Panel](https://www.waveshare.com/7.5inch-hd-e-paper.htm) <img src="https://github.com/dretay/stm32f401_disney_countdown/blob/master/img/countdown_example.png?raw=true" align="right" width="208">
- [STM32F401 Microcontroller](https://www.st.com/en/microcontrollers-microprocessors/stm32f401.html)
- [TM1638 LED Panel](https://www.ebay.com/itm/224781308879?itmmeta=01J27B08ERA8EC36Y067VHYF1K&hash=item34560293cf:g:b5EAAOSw2OJh2jgP&itmprp=enc%3AAQAJAAAA4NdzQCRXeUrPMbpv67Yk0F3fPrzfBWruXAdrMJaI%2F%2BMnKLvbgYV70h8y4Zb2TwJG%2BNwXOP%2F9U8ekfxmeiTVGI0D6ZXPtC3OOmtxkST59uzLJIWavLNvDe8fvhe10i46GSlPHlZcXXXILa9%2FFIYDxDgsOsjdrHWV1S0mj8zpEXXBjVmONWUjfbszjdA%2Bezi8k6xGS%2Bkac6N6NlwZ7YUPERwUoqXfd18hmPMUO0iHkcn3%2BltTcUpV%2BInnMgCj5xfmNYWq0noQfZIlaSXbTJ%2BlS6B%2BUhSzn7NAwtCFQ1rn0Y1WF%7Ctkp%3ABFBMuIeB65Fk)
- [Adafruit Powerboost 500](https://www.adafruit.com/product/1903)

### Libraries
- uGFX
- Modified version of [this](https://github.com/rjbatista/tm1638-library/tree/master) tm1638 Arduino library


### Notes
- This design could probably be made more efficient by powering 3.3v directly. Even though the uController deep sleeps, it still draws almost 1ma constantly because the powerboost converts to 5v just to be regulated down to 3.3v on the board itself. 
![](https://github.com/dretay/stm32f401_disney_countdown/blob/master/img/sleep_with_powerboost.png?raw=true)
- I tested powering 3.3v directly and disconnecting the tm1638 when not in use and was able to get the power down to 144uA. For the time being I just used a 2000mAH LIPO which should be good enough for months of runtime. A second version of this could definitely be more efficient. 
![](https://github.com/dretay/stm32f401_disney_countdown/blob/master/img/sleep_3v_direct.png?raw=true)
