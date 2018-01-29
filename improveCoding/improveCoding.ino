void setup() {
	UBRR0L = 8; 	//115200 baud
//	UCSR0B = (1<<TXEN0);
}

void loop() {
	UDR0 = inputs; //replace serial.write()
}