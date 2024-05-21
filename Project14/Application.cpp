#include<string>
#include "DeviceDriver.h"

class Application {
public:
    Application(DeviceDriver& deviceDriver) : deviceDriver{ deviceDriver } {}

    std::string readAndPrint(long startAddr, long endAddr) {
        std::string result ="";
        
        for (int i = startAddr; i <= endAddr; i++)
            result += deviceDriver.read(i);
    
        return result;
    }

    void writeAll(char value) {
        for (long i = 0x00; i < 0x05; i++) {
            deviceDriver.write(i, value);
        }
    }

private:
    DeviceDriver deviceDriver;
};