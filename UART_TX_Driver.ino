
void setup() {
    uartInit();
    timer1_init(15625); // 1000 ms (1 sec, from fcpu / prescaler.)
}
void uartInit() {
    uint16_t ubrr = 103; // for 9600 baud. we take ubrr = fcpu / 16 * baud-rate -1 = 103
    UBRR0H = (ubrr >> 8); // high byte of baud rate
    UBRR0L = ubrr; // low byte of baud rate

    UCSR0B = (1 << TXEN0); // Enable transmitter using registre

    // 8 data bit. no parity bit. 1 stop bit. (8-n-1)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // from data sheet
}

//transmit one character
void uart_tx_char(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // UCSR0 - frame register. UDRE0 - flag register. 
    UDR0 = data; // put character into buffer.
}

// Transmit string
void uart_tx_string(const char *str) {
    while (*str) { //while string is not empty
        uart_tx_char(*str++); // send individual chars of string.
    }
}


void timer1_init(uint16_t compare_value) { //reused from led toggle code
    TCCR1A = 0x00;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC, 1024 prescaler
    OCR1A = compare_value;
}

void timer1_wait() { // wait until compared value is reached in OCR1A
    while (!(TIFR1 & (1 << OCF1A))); // flag for comparison, will set when value match.
    TIFR1 |= (1 << OCF1A);
}

void loop() {
    timer1_wait();  // wait 1 second
    uart_tx_string("Hello from UART.\r\n"); // \r is carriage-return. /n is new line. 
}