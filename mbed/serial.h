#ifndef SERIALTW_h
#define SERIALTW_h

#include "mbed.h"

class SerialTW
{
    public:
        SerialTW(int  data_size=2) : _pc(USBTX, USBRX, 115200)
        {
            _data_size = data_size;
        }
        bool read(int data_rx[]);
        void write(int data_tx[]);
    private:
        Serial _pc;
        int _data_size; 
};

#endif /* SERIALTW_h */
