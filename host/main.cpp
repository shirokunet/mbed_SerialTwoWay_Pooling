#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serial.h"
#include "unistd.h"

serial_t serial;

bool read()
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
    printf("read %d bytes: _%s_\n", ret, buf);

    if (ret == 0)
    {
        printf("Nothing\n");
        return false;
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
        printf("\n");
    }

    return true;
}

const uint8_t* ctoui8(char c)
{
    char a[] = {c, '\0'};                   // char -> char*
    const uint8_t *buf = (unsigned char*)a; // char* -> unsigned char*
    return buf;
}

const uint8_t* itoui8(int num)
{
    char c[128] = {0};
    sprintf(c, "%d", num);                  // int -> char*
    const uint8_t *buf = (unsigned char*)c; // char* -> unsigned char*
    return buf;
}

void write()
{
    const uint8_t s[] = "s,123,-456,\r\n";
    serial_write(&serial, s, sizeof(s));

    // serial_write(&serial, ctoui8('s'), sizeof(ctoui8('s')));
    // serial_write(&serial, ctoui8(','), sizeof(ctoui8(',')));
    // serial_write(&serial, itoui8(1234), sizeof(itoui8(1234)));
    // serial_write(&serial, ctoui8(','), sizeof(ctoui8(',')));
    // serial_write(&serial, itoui8(-6789), sizeof(itoui8(-6789)));
    // serial_write(&serial, ctoui8(','), sizeof(ctoui8(',')));
    // serial_write(&serial, ctoui8('\n'), sizeof(ctoui8('\n')));
}

int main(void) {
    serial_open(&serial, "/dev/ttyACM1", 115200);

    write();
    while(1)
    {
        if (read())
        {
            write();
        }
        // usleep(1000*1);
    }

    serial_close(&serial);
    return 0;
}