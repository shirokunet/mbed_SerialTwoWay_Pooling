#include "mbed.h" 
#include "TextLCD.h"

TextLCD lcd(PA_0, PA_1, PA_4, PB_0, PC_1, PC_0);  // rs, e, d4-d7
Serial pc(USBTX, USBRX, 115200); // tx, rx

void Serial_Tx(int i, int j)
{
    pc.printf("s");
    pc.printf(",");
    pc.printf("%d", i);
    pc.printf(",");
    pc.printf("%d", j);
    pc.printf(",");
    pc.printf("\r\n");
}

void Serial_Rx()
{
    char value[2][100];
    int index[2]={0};
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
     
    value[0][index[0]]='\x0';   // add un 0 to end the c string 
    value[1][index[1]]='\x0';   // add un 0 to end the c string 

    Serial_Tx(atoi(value[0]), atoi(value[1]));

    lcd.cls();
    lcd.printf(value[0]);
    lcd.printf(",");
    lcd.printf(value[1]);  
    lcd.printf("\n"); 
}

int main() {
    char ch;
    int i = 0;
    int j = 0;
    lcd.printf("hey");
    wait(1);
    while(1) {
        Serial_Rx();

        // pc.putc(pc.getc());
    }
}