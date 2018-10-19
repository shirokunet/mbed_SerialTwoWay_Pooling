#include "mbed.h" 
#include "TextLCD.h"

#define data_size 2

TextLCD lcd(PA_0, PA_1, PA_4, PB_0, PC_1, PC_0);  // rs, e, d4-d7
Serial pc(USBTX, USBRX, 115200); // tx, rx

bool read(int data_rx[])
{
    char value[data_size][100];
    int index[data_size]={0};
    char ch;
    
    int num = -1;
    bool read_flag = false;
    do
    { 
       if (pc.readable())
       {
            ch = pc.getc();
            if (ch == 's')
                read_flag = true;
            else if (ch == ','){
                num ++;
            }
            else if (index[num]<100 && read_flag)
                value[num][index[num]++] = ch;
      }
    } while (ch!='\n');

    /* char to int */
    for (int i = 0; i < data_size; ++i)
    {
        value[i][index[i]]='\x0';   // add un 0 to end the c string 
        data_rx[i] = atoi(value[i]);
    }

    return true;
}

void write(int data_tx[])
{
    pc.printf("s,");
    for (int i = 0; i < data_size; ++i)
    {
        pc.printf("%d,", data_tx[i]);
    }
    pc.printf("\r\n"); 
}

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
    int data_rx[data_size] = {0}; 

    while(1) {
        if (read(data_rx))
        {
            write(data_rx);
            lcd_write(data_rx);
        }
    }
}