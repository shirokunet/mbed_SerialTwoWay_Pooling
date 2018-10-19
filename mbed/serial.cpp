#include "serial.h"

bool SerialTW::read(int data_rx[])
{
    char value[_data_size][100];
    int index[_data_size]={0};
    char ch;
    
    int num = -1;
    bool read_flag = false;
    do
    { 
       if (_pc.readable())
       {
            ch = _pc.getc();
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
    for (int i = 0; i < _data_size; ++i)
    {
        value[i][index[i]]='\x0';   // add un 0 to end the c string 
        data_rx[i] = atoi(value[i]);
    }

    return true;
}

void SerialTW::write(int data_tx[])
{
    _pc.printf("s,");
    for (int i = 0; i < _data_size; ++i)
    {
        _pc.printf("%d,", data_tx[i]);
    }
    _pc.printf("\r\n"); 
}