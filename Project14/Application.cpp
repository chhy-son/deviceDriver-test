#include "DeviceDriver.h"
class Application {
public:
    Application(DeviceDriver& deviceDriver) : deviceDriver{ deviceDriver } {}

    void readAndPrint(long startAddr, long endAddr) {
        
    }

    void writeAll(char value) {

    }

private:
    DeviceDriver deviceDriver;
};