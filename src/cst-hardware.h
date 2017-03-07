#ifndef _CST_HARDWARE_H_
#define _CST_HARDWARE_H_

#define DYNAMIC_BIT    0x04
#define BELL_BIT       0x02
#define MENU_BIT       0x20
#define SELECT_BIT     0x10
#define UP_BIT         0x40
#define DOWN_BIT       0x80

#define LCD_POWER      PA6
#define LCD_BACKLIGHT  PA5

#define REVERSER_ENABLE PC0
#define POTS_ENABLE     PC1
#define LIGHTSW_ENABLES PD5
#define THROTTLE_ENABLE PD4

#define ANALOG_VREV     PA0
#define ANALOG_VBRAKE   PA1
#define ANALOG_VHORN    PA4
#define ANALOG_VLIGHT_R PA2
#define ANALOG_VLIGHT_F PA3
#define ANALOG_VBATT    PA7

#define LED_RED_PIN     PD6
#define LED_GREEN_PIN   PD7


typedef enum
{
	NEUTRAL = 0,
	FORWARD,
	REVERSE
} ReverserPosition;

extern ReverserPosition reverserPosition;

extern uint8_t brakePosition;
extern uint8_t hornPosition;

typedef enum
{
	LIGHT_OFF = 0,
	LIGHT_DIM = 1,
	LIGHT_BRIGHT = 2,	
	LIGHT_BRIGHT_DITCH = 3,	

} LightPosition;

extern uint8_t frontLightPot;
extern LightPosition frontLight;
extern uint8_t rearLightPot;
extern LightPosition rearLight;

extern uint8_t batteryVoltage;

void initADC();
void processADC();

void initPorts();

typedef enum
{
	LED_OFF = 0x00,
	LED_GREEN,
	LED_RED,
	LED_YELLOW,
	LED_GREEN_SLOWBLINK,
	LED_GREEN_FASTBLINK,
	LED_RED_SLOWBLINK,
	LED_RED_FASTBLINK,
	LED_YELLOW_SLOWBLINK,
	LED_YELLOW_FASTBLINK

} LEDStatus;

extern volatile LEDStatus led;

	//  PD6 - Output - LED Red
	//  PD7 - Output - LED Green
inline void ledGreenOff()
{
	PORTD &= ~_BV(LED_GREEN_PIN);
}
inline void ledGreenOn()
{
	PORTD |= _BV(LED_GREEN_PIN);
}
inline void ledRedOff()
{
	PORTD &= ~_BV(LED_RED_PIN);
}
inline void ledRedOn()
{
	PORTD |= _BV(LED_RED_PIN);
}

inline void switchesEnable()
{
	PORTB |= 0b00000110;  // Pullups on
}

inline void switchesDisable()
{
	PORTB &= ~(0b00000110);  // Pullups off
}

inline void buttonsEnable()
{
	PORTB |= 0b11110000;  // Pullups on
}

inline void buttonsDisable()
{
	PORTB &= ~(0b11110000);  // Pullups off
}

inline void lcdEnable()
{
	PORTA &= ~_BV(LCD_POWER);
}

inline void lcdDisable()
{
	PORTA |= _BV(LCD_POWER);
	PORTC &= ~(0xFC);  // Set LCD lines low  FIXME: use #define for LCD pins?
}

inline void lcdBacklightEnable()
{
	PORTA |= _BV(LCD_BACKLIGHT);
}

inline void lcdBacklightDisable()
{
	PORTA &= ~_BV(LCD_BACKLIGHT);
}

inline void enablePots()
{
	PORTC |= _BV(POTS_ENABLE);
}

inline void disablePots()
{
	PORTC &= ~_BV(POTS_ENABLE);
}

inline void enableReverser()
{
	PORTC |= _BV(REVERSER_ENABLE);
}

inline void disableReverser()
{
	PORTC &= ~_BV(REVERSER_ENABLE);
}

inline void enableLightSwitches()
{
	PORTD |= _BV(LIGHTSW_ENABLES);
}

inline void disableLightSwitches()
{
	PORTD &= ~_BV(LIGHTSW_ENABLES);
}

inline void enableThrottle()
{
	PORTD |= _BV(THROTTLE_ENABLE);
}

inline void disableThrottle()
{
	PORTD &= ~_BV(THROTTLE_ENABLE);
}

void ledUpdate();

#endif
