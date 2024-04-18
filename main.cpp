#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <cstring>

const char* serialPortPath = "/dev/ttyACM0";


int main()
{
    std::fstream serialPort;
    serialPort.open(serialPortPath, std::ios::in | std::ios::out);

    //check if serial port is opened successfully
    if(!serialPort.is_open())
    {
        std::cerr << "Failed to open serial port" << std::endl;
        return 1;
    }

    //set baud rate dependending on arduino setbaud
    serialPort << "baud 9600" << std::endl;

    //clear existing data in serial port
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    serialPort.flush();

    for(size_t i = 0; i < 30; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::string dataTOSend = "hello arduino" + std::to_string(i);
        serialPort << dataTOSend << std::endl;
    }

    serialPort.close();
    return 0;
}
