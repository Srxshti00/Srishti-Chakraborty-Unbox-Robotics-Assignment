#define F_CPU 16000000UL   // clock freq 16Mhz
#define presc 1024         // prescaler
#define dly 500            // delay in ms given in PS
#define val ((F_CPU / presc / 1000) * dly - 1) // ((16x10^6/1024/1000) * 500-1)= 7812

//gpio
void setOut(volatile uint8_t *ddr, uint8_t p) {
    *ddr |= (1 << p);   // ddr write=1 ->pin is output
}

// toggle pin
void tog(volatile uint8_t *port, uint8_t p) {
    *port ^= (1 << p);  // xor to flip state
}

//tmr

// init timer1 in CTC
void t1_init(uint16_t cmp) {
    TCCR1A = 0x00;  // normal
    // WGM12 = CTC mode
    // CS12 + CS10 = prescaler 1024
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    OCR1A = cmp;   // compare value for delay
}

// wait till match happens
void t1_wait() {
    while (!(TIFR1 & (1 << OCF1A))); // looping till tmr int flag becomes 1
    TIFR1 |= (1 << OCF1A); // clear flag manually (write 1 to clear)
}

//m
void setup() {
    setOut(&DDRB, 5);   // pin 13 (PB5)
    t1_init(val);       // 500ms approx
}

void loop() {
    t1_wait();          // wait
    tog(&PORTB, 5);     // blink led
}