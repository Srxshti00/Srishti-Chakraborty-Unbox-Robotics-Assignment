# Srishti-Chakraborty-Unbox-Robotics-Assignment
# Embedded Drivers using ATmega328P

This repository contains my implementation of basic embedded drivers using the Arduino UNO (ATmega328P). The main idea was to understand how things work at register level instead of using Arduino built-in functions.

There are two separate branches in this repository. One contains the GPIO driver and the other contains the UART driver.

GPIO_dev branch contains the GPIO driver code.  
UART_dev branch contains the UART driver code.

---

GPIO Driver

In this part, I configured a GPIO pin as output and toggled the onboard LED. I used pin 13 which corresponds to PB5.

DDRB register is used to set the pin as output. PORTB is used to toggle the pin. Instead of using delay function, I used Timer1 in CTC mode to generate delay.

Timer counts down till a compare value stored in OCR1A. When the timer matches this value, a flag is set and I use that for generating delay.

The delay calculation is based on the formula:

$$
OCR1A = \frac{F_{CPU}}{\text{Prescaler} \times 1000} \times \text{Delay}_{ms} - 1
$$

For 500 ms delay:

$$
OCR1A = \frac{16{,}000{,}000}{1024 \times 1000} \times 500 \approx 7812
$$

---

UART Driver

In this part, I initialized UART and transmitted a string periodically.

UART is configured for 9600 baud rate and 8 data bits, no parity, 1 stop bit (8N1).

Baud rate is set using UBRR register. Transmitter is enabled using TXEN0 bit. Data is written into UDR0 register to transmit. Before writing, I check UDRE0 flag to ensure buffer is ready.

The baud rate calculation is:

$$
UBRR = \frac{F_{CPU}}{16 \times \text{Baud Rate}} - 1
$$

For 9600 baud:

$$
UBRR = \frac{16{,}000{,}000}{16 \times 9600} - 1 \approx 103
$$

Timer1 is reused here to generate a delay of 1000ms so that the string is printed periodically.

---

Datasheet Reference

I referred to the ATmega328P datasheet to understand the register configurations and bit settings.

<img width="1311" height="251" alt="Screenshot 2026-03-31 233452" src="https://github.com/user-attachments/assets/9ad47aa7-2997-47e0-b8fe-0c0ff1495ca5" />

GPIO section (DDRB, PORTB)  
Timer1 section (TCCR1A, TCCR1B, OCR1A)  
UART section (UCSR0A, UCSR0B, UCSR0C, UBRR)
