#include <stdio.h>
#include <windows.h>
#include <Setupapi.h>
#include <devguid.h>
#include "conio.h"
#include "tchar.h"

#include <dbt.h>
#include <initguid.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char ** argv)
{
    HDEVINFO deviceInfoSet;
    //GUID *guidDev = (GUID*) &GUID_DEVCLASS_USB;
   // GUID GUID_DEVCLASS_USB = {0x36fc9e60, 0xc465, 0x11cf, {0x80, 0x56,0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};
   //GUID GUID_DEVCLASS_USB = {0xA5DCBF10L, 0x6530, 0x11D2, {0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED}};
//53D29EF7-377C-4D14-864B-EB3A85769359
//    GUID GUID_DEVCLASS_USB = {0x53f56307L, 0xb6bf, 0x11d0, {0x94, 0xf2,0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b}};
    //GUID GUID_DEVCLASS_USB = {0x53d29ef7L,0x377c,0x4d14,{0x86,0x4b,0xeb,0x3a,0x85,0x76,0x93,0x59}};
   // deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_USB, NULL, NULL, DIGCF_PRESENT | DIGCF_PROFILE);

   GUID GUID_DEVCLASS_USB = {0x53D29EF7L,0x377C,0x4D14,{0x86,0x4B,0xEB,0x3A,0x85,0x76,0x93,0x59}};

   deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_USB, NULL,0, DIGCF_PRESENT | DIGCF_PROFILE);


    TCHAR buffer [4000];
    DWORD buffersize =4000;
    int memberIndex = 0;

    while(TRUE)
    {
        SP_DEVINFO_DATA deviceInfoData;
        ZeroMemory(&deviceInfoData, sizeof(SP_DEVINFO_DATA));
        deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        if (SetupDiEnumDeviceInfo(deviceInfoSet, memberIndex, &deviceInfoData) == FALSE)
            {
                if (GetLastError() == ERROR_NO_MORE_ITEMS)
                {

                    break;

                }
            }
        DWORD nSize=0 ;
        SetupDiGetDeviceInstanceId (deviceInfoSet, &deviceInfoData, buffer, sizeof(buffer), &nSize);
        //SetupDiGetDeviceInterfaceDetail(deviceInfoSet,&deviceInterfaceData,NULL,0,NULL,NULL);

		SetupDiEnumDeviceInterfaces(deviceInfoSet, NULL, &GUID_DEVCLASS_USB, 0, &deviceInfoData);
        buffer [nSize] ='\0';
        _tprintf (_T("%s\n"), buffer);
        memberIndex++;
    }
    if (deviceInfoSet)
        {
            SetupDiDestroyDeviceInfoList(deviceInfoSet);
        }
    getch();
    return 0;
}
