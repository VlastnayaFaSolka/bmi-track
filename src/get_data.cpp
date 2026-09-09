#include <iostream>
#include <windows.h>

int main() {
    // Открываем COM-порт (замените "COM3" на ваш порт)
    HANDLE hSerial = CreateFile("COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Oshibka otkritiya porta!\n";
        return 1;
    }

    // Настройка параметров порта
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600; // Скорость 9600
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    // Читаем данные в цикле
    char buffer[128];
    DWORD bytesRead;
    
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
            std::cout << buffer;
        }
    }

    CloseHandle(hSerial);
    return 0;
}