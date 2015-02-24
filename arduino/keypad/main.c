

#define BUTTON_COUNT 10
#define CODE_LEN 4

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

void setup()
{
	cursor = 0;
	// set code
	// set button pins
	// setup servo
	// setup LED pins
}

bool check_code()
{
	for(int i = 0; i < CODE_LEN; i++)
		if(code_tmp[i] != code[i])
			return false;

	return true;
}
void unlock_door()
{
}
void lock_door()
{
}
void onButtonPress(int i)
{
	// ready to accept next number
	if(cursor < 4) {
		code_tmp[cursor] = i;
		cursor++;
		
		if(cursor == 4) {
			// prepare to enter another code
			cursor = 0;

			if(check_code()) {
				// unlock door
				unlock_door()
				// turn on green LED
			} else {
				// turn on red LED
			}
		}
	}
}
void updateButtonStates()
{
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

void loop()
{
	
	updateButtonStates();

}


