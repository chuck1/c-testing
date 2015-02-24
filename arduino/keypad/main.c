

#define BUTTON_COUNT 10

// button data
int count[BUTTON_COUNT];
int state[BUTTON_COUNT];
int pin[BUTTON_COUNT];

// code data
// temporary storage for entering code
int code_tmp[4];
// actual code value
int code[4];
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

void onButtonPress(int i)
{
	if(cursor < 4) { // ready to accept next number
		code_tmp[cursor] = i;
		cursor++;

		if(cursor == 4) {
			
		}
	}
}
void updateButtonState()
{
	for(int i = 0; i < BUTTON_COUNT; i++) {
		int nstate = digitalRead(pin[i]);

		if(nstate != state[i]) {
			count[i]++;
			if(count[i] > threshold) {
				state[i] = nstate;

				if(nstate == HIGH) onButtonPress(i);

				count = 0;
			}
		} else {
			count = 0;
		}
	}
}

void loop()
{

}


