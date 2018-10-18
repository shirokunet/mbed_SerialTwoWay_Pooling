#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serial.h"
#include "unistd.h"

serial_t serial;

void read()
{
    const int data_size = 3;
    const int timeout_ms = 10;
    uint8_t buf[128];
    int ret;

    /* Read up to buf size or 2000ms timeout */
    if ((ret = serial_read(&serial, buf, sizeof(buf), timeout_ms)) < 0) {
        fprintf(stderr, "serial_read(): %s\n", serial_errmsg(&serial));
        exit(1);
    }
    // printf("read %d bytes: _%s_\n", ret, buf);

    if (ret == 0)
    {
        printf("Nothing\n");
        return;
    }

    /* convert */
    char c[128];
    snprintf(c, 128, "%s", buf);

    /* split */
    char* tp[data_size];
    for (int i = 0; i < data_size; ++i)
    {
        if (i == 0)
            tp[i] = strtok(c, ",");
        else
            tp[i] = strtok(NULL, ",");
    }

    /* check start signal */
    int data[data_size-1];
    if (c[0] == 's')
    {
        for (int i = 0; i < data_size-1; ++i)
        {
            data[i] = atoi(tp[i+1]);
            printf("tp%d:%d,", i, data[i]);
        }
    }
    printf("\n");
}

void write()
{
    uint8_t s[] = "123";

    /* Write to the serial port */
    serial_write(&serial, s, sizeof(s));
}

int main(void) {
    serial_open(&serial, "/dev/ttyACM0", 115200);

    while(1)
    {
        write();
        read();
        usleep(1000);
    }

    serial_close(&serial);
    return 0;
}