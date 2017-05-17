// variable defines
#define KEYPAD_BUTTON_COUNT 4
#define CODE_LEN 4


#define BUTTON_COUNT (KEYPAD_BUTTON_COUNT + 2)

#define BUTTON_LOCK   KEYPAD_BUTTON_COUNT
#define BUTTON_UNLOCK (KEYPAD_BUTTON_COUNT + 1)

// button data
int count[BUTTON_COUNT];
int state[BUTTON_COUNT];
int pin[BUTTON_COUNT];

// code data
// temporary storage for entering code
int code_tmp[CODE_LEN];
// actual code value
int code[CODE_LEN];
// cursor
int cursor;

// led data
#define LED_COUNT 2
#define TIMER_LED_LOCK 0
#define TIMER_LED_UNLOCK 1
int led_pin[LED_COUNT];
// time until LED should be turned off
int led_timer[LED_COUNT];

int led_lock_pin;
int led_unlock_pin;

// other data
// time after which code entry should be reset
int timeout;

int hold;

bool check_code()
{
	for(int i = 0; i < CODE_LEN; i++)
		if(code_tmp[i] != code[i])
			return false;
	return true;
}
void unlock_door()
{
	digitalWrite(led_lock_pin, LOW);
	digitalWrite(led_unlock_pin, HGIH);

	// servo
}
void lock_door()
{
	digitalWrite(led_lock_pin, HIGH);
	digitalWrite(led_unlock_pin, LOW);

	// servo
}
void update_leds()
{
	for(int i = 0; i < LED_COUNT; i++) {
		if(led_timer[i] > 0) {
			led_timer[i]--;
			if(led_timer[i] == 0) {
				// when the timer gets to 0, turn off LED
				digitalWrite(led_pin[i], LOW);
			}
		}
	}
}
void on_button_press(int i)
{
	// filter buttons
	if(i < KEYPAD_BUTTON_COUNT) {
		// keypad
		on_button_press_keypad(i);
	} else if(i == BUTTON_LOCK) {
		lock_door();
	} else if(i == BUTTON_UNLOCK) {
		unlock_door();
	}
}
void set_led_timer_and_hold(int led_index, int time)
{
	digitWrite(led_pin[led_index], HIGH);

	led_timer[led_index] = time;

	hold = time;
}
void on_button_press_keypad(int i)
{
	// ready to accept next number
	//if(cursor < CODE_LEN) { // this should be guaranteed

	// set timeout
	// this gives the user time to enter the next digit before the controller resets
	timeout = 10;
	
	// lock door here if not already locked
	// this is how you lock the door from the outside
	lock_door();

	// write number to code
	code_tmp[cursor] = i;
	cursor++;

	// turn on outdoor unlock LED
	set_led_timer_and_hold(1, 2);

	// ready to check code
	if(cursor == CODE_LEN) {
		// prepare to enter another code
		cursor = 0;
		timeout = 0;

		if(check_code()) {
			// unlock door
			unlock_door();

			set_led_timer_and_hold(TIMER_LED_UNLOCK, 10);
		} else {
			set_led_timer_and_hold(TIMER_LED_LOCK, 10);
		}
	}

	//}
}
void update_button_states()
{
	// debounce code for all buttons

	// for each button
	for(int i = 0; i < BUTTON_COUNT; i++) {
		int nstate = digitalRead(pin[i]);

		if(nstate != state[i]) { // state is different
			count[i]++;

			// if state is different for at least (threshold) cycles,
			// then actually change state
			if(count[i] > threshold) {
				state[i] = nstate;

				// button press callback
				if(nstate == HIGH) onButtonPress(i);

				count[i] = 0;
			}
		} else {
			count[i] = 0;
		}
	}
}
void setup()
{
	cursor = 0;
	timeout = 0;

	// set code
	code[0] = ;
	code[1] = ;
	code[2] = ;
	code[3] = ;

	// set button pins
	pin[0] = ;
	pin[1] = ;
	pin[2] = ;
	pin[3] = ;

	// setup servo

	// setup outdoor LED pins
	led_pin[0] = ; // lock
	led_pin[1] = ; // unlock

	// indoor LED pins
	int led_lock_pin = ;
	int led_unlock_pin = ;

	// on powerup, lock door
	lock_door();
}
void loop()
{
	update_leds();

	if(timeout > 0) {
		timeout--;
		if(timeout == 0) {
			// reset code entry
			cursor = 0;

			set_led_timer_and_hold(TIMER_LED_LOCK, 10);
		}
	}

	if(hold > 0) {
		hold--;
	} else {
		update_button_states();
	}
}






