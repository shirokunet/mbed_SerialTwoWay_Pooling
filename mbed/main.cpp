#include <mbed.h>

DigitalOut led1(LED3);

Serial pc(USBTX, USBRX, 115200);

// volatile bool flag = false;
// volatile char data;

// void ISR_Serial_Rx()
// {
//     flag = true;
//     data = pc.getc();
// }

int main()
{
    // pc.attach(ISR_Serial_Rx, Serial::RxIrq);
    led1 = 1;
    int i = 0;
    int j = 0;
    while(1) {
        led1 = !led1;

        i++;
        j--;
        pc.printf("s");
        pc.printf(",");
        pc.printf("%d", i);
        pc.printf(",");
        pc.printf("%d", j);
        pc.printf(",");
        // pc.printf("e");
        // pc.printf(",");
        pc.printf("\r\n");

        // if (flag)
        //     pc.printf("%s", data);

        wait(0.01);
    }
}

