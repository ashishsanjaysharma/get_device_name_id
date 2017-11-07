#include <stdio.h>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>

int main( int argc, char *argv[ ], char *envp[ ] )
{

    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA DeviceInfoData;
    DWORD i;

    GUID GUID_DEVCLASS_USB = {0x53D29EF7L,0x377C,0x4D14,{0x86,0x4B,0xEB,0x3A,0x85,0x76,0x93,0x59}};
       // Create a HDEVINFO with all present devices.
    hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_USB,NULL,0,DIGCF_PRESENT | DIGCF_PROFILE ); //Enumerator

    //hDevInfo = SetupDiGetClassDevs(NULL,0,0,DIGCF_PRESENT | DIGCF_ALLCLASSES );
    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        // Insert error handling here.
           //return 1;

           return 1;
    }

       // Enumerate through all devices in Set.

    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    for (i=0;SetupDiEnumDeviceInfo(hDevInfo,i,&DeviceInfoData);i++)
    {
           DWORD DataT;
           LPTSTR buffer = NULL;
           DWORD buffersize = 0;

           //
           // Call function with null to begin with,
           // then use the returned buffer size (doubled)
           // to Alloc the buffer. Keep calling until
           // success or an unknown failure.
           //
           //  Double the returned buffersize to correct
           //  for underlying legacy CM functions that
           //  return an incorrect buffersize value on
           //  DBCS/MBCS systems.
           //
           while (!SetupDiGetDeviceRegistryProperty(hDevInfo,&DeviceInfoData,SPDRP_DEVICEDESC,&DataT,(PBYTE)buffer,buffersize,&buffersize))
           {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                   // Change the buffer size.
                if (buffer) LocalFree(buffer);
                   // Double the size to avoid problems on
                   // W2k MBCS systems per KB 888609.
                buffer = LocalAlloc(LPTR,buffersize * 2);
            }
            else
            {

                //printf("NO DEVICE FOUND \n");
                   // Insert error handling here.
                break;

            }
        }

        printf("Result:[%s]\n",buffer);

        if (buffer) LocalFree(buffer);
    }


    if ( GetLastError()!=NO_ERROR && GetLastError()!=ERROR_NO_MORE_ITEMS )
    {

        // Insert error handling here.
        return 1;
    }

       //  Cleanup
    SetupDiDestroyDeviceInfoList(hDevInfo);

    getch();
    return 0;
}
