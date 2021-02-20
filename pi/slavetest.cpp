#include <pigpio.h>
#include <iostream>
#include <iomanip>

#include <unistd.h>

// From : https://raspberrypi.stackexchange.com/questions/76109/raspberry-as-an-i2c-slave/91438#91438

using namespace std;

void runSlave();
void closeSlave();
int getControlBits(int, bool);

const int slaveAddress = 0x03; // <-- Your address of choice
bsc_xfer_t xfer;               // Struct to control data flow

int main()
{
    // Chose one of those two lines (comment the other out):
    runSlave();
    //closeSlave();

    return 0;
}

class SlaveStatus
{
    int *address;

public:
    SlaveStatus(int *status)
    {
        address = status;
    }
    int txCnt() const
    {
        return (*address) >> 16 && 0b11111;
    }
    int rxFifo() const
    {
        return (*address) >> 11 && 0b11111;
    }
    int txFifo() const
    {
        return (*address) >> 6 & 0b11111;
    }
    bool rxBusy() const
    {
        return (*address) >> 5 & 0b1;
    }
    bool txEmpty() const
    {
        return (*address) >> 4 & 0b1;
    }
    bool rxFull() const
    {
        return (*address) >> 3 & 0b1;
    }
    bool txFull() const
    {
        return (*address) >> 2 & 0b1;
    }
    bool rxEmpty() const
    {
        return (*address) >> 1 & 0b1;
    }
    bool txBusy() const
    {
        return (*address) >> 0 & 0b1;
    }
    friend ostream &operator<<(ostream &os, const SlaveStatus &ss);
};

ostream &operator<<(ostream &os, const SlaveStatus &ss)
{
    os << hex << *ss.address << dec;
    os << ' ' << ss.txCnt();
    os << ' ' << ss.rxFifo();
    os << ' ' << ss.txFifo();
    os << ' ' << (ss.rxBusy() ? "RB" : "  ")
       << ' ' << (ss.txEmpty() ? "TE" : "  ")
       << ' ' << (ss.rxFull() ? "RF" : "  ")
       << ' ' << (ss.txFull() ? "TF" : "  ")
       << ' ' << (ss.rxEmpty() ? "RE" : "  ")
       << ' ' << (ss.txBusy() ? "TB" : "  ");

    return os;
}

class XferControl
{
    uint32_t *address;

public:
    XferControl(uint32_t *control)
    {
        address = control;
    }
    int addr() const { return (*address) >> 16 & 0b1111111; }
    bool invertTransmit() const { return (*address) >> 13 & 0b1; }
    bool hostControl() const { return (*address) >> 12 & 0b1; }
    bool testFifo() const { return (*address) >> 11 & 0b1; }
    bool invertRx() const { return (*address) >> 10 & 0b1; }
    bool enableRx() const { return (*address) >> 9 & 0b1; }
    bool enableTx() const { return (*address) >> 8 & 0b1; }
    bool abortClear() const { return (*address) >> 7 & 0b1; }
    bool controlFirst() const { return (*address) >> 6 & 0b1; }
    bool statusFirst() const { return (*address) >> 5 & 0b1; }
    bool polarity() const { return (*address) >> 4 & 0b1; }
    bool phase() const { return (*address) >> 3 & 0b1; }
    bool i2c() const { return (*address) >> 2 & 0b1; }
    bool spi() const { return (*address) >> 1 & 0b1; }
    bool enable() const { return (*address) >> 0 & 0b1; }
    friend ostream &operator<<(ostream &os, const XferControl &xc);
};

ostream &operator<<(ostream &os, const XferControl &xc)
{
    os << hex << *xc.address << dec;
    os << ' ' << xc.addr();
    os << ' ' << (xc.invertTransmit() ? "IT" : "  ")
       << ' ' << (xc.hostControl() ? "HC" : "  ")
       << ' ' << (xc.testFifo() ? "TF" : "  ")
       << ' ' << (xc.invertRx() ? "IR" : "  ")
       << ' ' << (xc.enableRx() ? "RE" : "  ")
       << ' ' << (xc.enableTx() ? "TE" : "  ")
       << ' ' << (xc.abortClear() ? "BK" : "  ")
       << ' ' << (xc.controlFirst() ? "EC" : "  ")
       << ' ' << (xc.statusFirst() ? "ES" : "  ")
       << ' ' << (xc.polarity() ? "PL" : "  ")
       << ' ' << (xc.phase() ? "PH" : "  ")
       << ' ' << (xc.i2c() ? "I2" : "  ")
       << ' ' << (xc.spi() ? "SP" : "  ")
       << ' ' << (xc.enable() ? "EN" : "  ");

    return os;
}

void runSlave()
{
    gpioInitialise();
    cout << "Initialized GPIOs\n";
    // Close old device (if any)
    xfer.control = getControlBits(slaveAddress, false); // To avoid conflicts when restarting
    cout << "CONTROL 0 =" << XferControl(&xfer.control) << endl;
    bscXfer(&xfer);
    // Set I2C slave Address to 0x0A
    xfer.control = getControlBits(slaveAddress, true);
    cout << "CONTROL 1 =" << XferControl(&xfer.control) << endl;
    int status = bscXfer(&xfer); // Should now be visible in I2C-Scanners
    cout << "CONTROL 2 =" << XferControl(&xfer.control) << endl;

    cout << "Status " << SlaveStatus(&status) << endl;

    if (status >= 0)
    {
        cout << "Opened slave\n";
        xfer.rxCnt = 0;
        while (1)
        {
            status = bscXfer(&xfer);

            if (xfer.rxCnt > 0)
            {
                cout << "STATUS-> " << SlaveStatus(&status) << endl;
                cout << "CONTROL =" << XferControl(&xfer.control) << " " << xfer.rxCnt << " " << xfer.txCnt << endl;
                // Received some data
                cout << "Received " << xfer.rxCnt << " bytes: ";
                cout << "0x";
                for (int i = 0; i < xfer.rxCnt; i++)
                    cout
                        << hex << setfill('0') << setw(2) << (int)xfer.rxBuf[i];
                cout << "\n";

                cout << "Control " << hex << setw(2) << setfill('0') << xfer.control << endl;
                cout << "txcount " << xfer.txCnt << ", Max = " << dec << BSC_FIFO_SIZE << endl;

                // printSlaveStatus(*reinterpret_cast<SlaveStatus_t *>(&status));
                cout << "Status:" << hex << status << endl;

                if (xfer.rxBuf[0] == 0x13)
                {
                    xfer.txBuf[0] = 0x11;
                    xfer.txBuf[1] = 0x22;
                    xfer.txBuf[2] = 0x33;
                    xfer.txBuf[3] = 0x44;
                    xfer.txCnt = 4;
                }
                else
                {
                    xfer.txCnt = 0;
                }
                // usleep(200);

                // xfer.txBuf[0] = xfer.rxBuf[0];
                // xfer.txCnt = 1;
                // bscXfer(&xfer); // Send back a single byte
                // xfer.txCnt = 0;
                // bscXfer(&xfer); // Set txCnt to 0
                // xfer.txCnt = 1;
                // cout << "sent a byte = " << hex << xfer.txBuf[0] << endl;
            }
            else if (SlaveStatus(&status).rxFifo() || SlaveStatus(&status).txFifo() || SlaveStatus(&status).txCnt())
            {
                cout << "XX" << SlaveStatus(&status) << endl;
                xfer.txCnt = 0;
                usleep(200);
            }
        }
    }
    else
        cout << "Failed to open slave!!!\n";
}

void closeSlave()
{
    gpioInitialise();
    cout << "Initialized GPIOs\n";

    xfer.control = getControlBits(slaveAddress, false);
    bscXfer(&xfer);
    cout << "Closed slave.\n";

    gpioTerminate();
    cout << "Terminated GPIOs.\n";
}

int getControlBits(int address /* max 127 */, bool open)
{
    /*
    Excerpt from http://abyz.me.uk/rpi/pigpio/cif.html#bscXfer regarding the control bits:

    22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
    a  a  a  a  a  a  a  -  -  IT HC TF IR RE TE BK EC ES PL PH I2 SP EN

    Bits 0-13 are copied unchanged to the BSC CR register. See pages 163-165 of the Broadcom 
    peripherals document for full details. 

    aaaaaaa defines the I2C slave address (only relevant in I2C mode)
    IT  invert transmit status flags
    HC  enable host control
    TF  enable test FIFO
    IR  invert receive status flags
    RE  enable receive
    TE  enable transmit
    BK  abort operation and clear FIFOs
    EC  send control register as first I2C byte
    ES  send status register as first I2C byte
    PL  set SPI polarity high
    PH  set SPI phase high
    I2  enable I2C mode
    SP  enable SPI mode
    EN  enable BSC peripheral
    */

    // Flags like this: 0b/*IT:*/0/*HC:*/0/*TF:*/0/*IR:*/0/*RE:*/0/*TE:*/0/*BK:*/0/*EC:*/0/*ES:*/0/*PL:*/0/*PH:*/0/*I2:*/0/*SP:*/0/*EN:*/0;

    int flags;
    if (open)
        flags = /*RE:*/ (1 << 9) | /*TE:*/ (1 << 8) | /*I2:*/ (1 << 2) | /*EN:*/ (1 << 0);
    else // Close/Abort
        flags = /*BK:*/ (1 << 7) | /*I2:*/ (0 << 2) | /*EN:*/ (0 << 0);

    return (address << 16 /*= to the start of significant bits*/) | flags;
}