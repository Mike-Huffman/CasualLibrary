#include <iostream>

#include "Memory.h"

inline const char* const BoolToString(bool b) {
    return b ? "OK" : "Failed";
}


int main() {
    std::cout << "Running tests ...\n\n";

    External::Memory memory = External::Memory("ZombieWar.exe");
    Address modulePtr = memory.getModule("ZombieWar.exe");

    Address namePtr = memory.getAddress(modulePtr + 0x00003648, { 0x40 }).get();

    std::cout << "Status readString(addToBeRead):       ";
    std::cout << BoolToString(memory.readString(namePtr) == "CasualGamer") << std::endl;

    std::cout << "Status readString(addToBeRead, size): ";
    std::cout << BoolToString(memory.readString(namePtr, 5) == "Casua") << std::endl;

    std::cout << "Status memory.read<T>(addToBeRead):   ";
    std::cout << BoolToString(memory.read<int>(namePtr) == 1970495811) << std::endl;

    Address address = memory.findSignature(modulePtr, "BA ? ? ? ? CD", 100);
    std::cout << "Status findSignature(...):            ";
    std::cout << BoolToString(address.get()) << std::endl;

    std::cin.get();
}