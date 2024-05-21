#include "DeviceDriver.h"
#include "exceptions.cpp"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{  
    const int readCycle = 5;

    char firstReadValue = m_hardware->read(address);
    for (int cycle = 1; cycle < readCycle; cycle++) {
        if (firstReadValue != m_hardware->read(address))
            throw ReadFailException("Read fail");
    }

    return (int)firstReadValue;
}

void DeviceDriver::write(long address, int data)
{
    if (m_hardware->read(address) != 0xFF)
        throw WriteFailException("Write fail");

    m_hardware->write(address, (unsigned char)data);
}