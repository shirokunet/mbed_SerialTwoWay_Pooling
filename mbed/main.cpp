#include "mbed.h" 
#include "TextLCD.h"
#include "serial.h"

#define data_size 2

TextLCD lcd(PA_0, PA_1, PA_4, PB_0, PC_1, PC_0);  // rs, e, d4-d7

void lcd_write(int data_tx[])
{
    lcd.cls();
    for (int i = 0; i < data_size; ++i)
    {
        lcd.printf("%d,", data_tx[i]);
    }
    lcd.printf("\n");
}

int main() {
    SerialTW stw(data_size);
    int data_rx[data_size] = {0}; 

    while(1) {
        if (stw.read(data_rx))
        {
            stw.write(data_rx);
            lcd_write(data_rx);
        }
    }
}