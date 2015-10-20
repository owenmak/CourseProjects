#include <stdio.h>
#include <wiringPi.h>

#define PIN0 0
#define PIN1 1
#define RECEIVE 2

int main() {
	char gates[][5] = {"AND","NAND", "OR", "XOR", "NOR"};
	// since the results of 10, 01 are the same, we only take one to determine.
	char chips[][4] = {"001","110","011","010","100"};
	char input[4];
	wiringPiSetup();
	pinMode(PIN0, OUTPUT);
	pinMode(PIN1, OUTPUT);
	pinMode(RECEIVE, INPUT);
	digitalWrite(PIN0, LOW);
	digitalWrite(PIN1, LOW);
	delay(500);
	if(digitalRead(RECEIVE) == LOW)
		input[0] = '0';
	else
		input[0] = '1';
	digitalWrite(PIN0, LOW);
	digitalWrite(PIN1, HIGH);
	delay(500);
	if(digitalRead(RECEIVE) == LOW)
		input[1] = '0';
	else
		input[1] = '1';
	digitalWrite(PIN0, LOW);
	digitalWrite(PIN1, HIGH);
	delay(500);
	if(digitalRead(RECEIVE) == LOW)
		input[2] = '0';
	else
		input[2] = '1';
	input[3] = '\0';
	for(int i = 0 ; i < 4; i++) {
		if(strcmp(chips[i], input) == 0) {
			printf(gates[i]);
		}
	}
}
