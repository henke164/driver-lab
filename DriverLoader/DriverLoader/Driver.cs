using System;
using System.Text;
using static DriverLoader.Win32Methods;

namespace DriverLoader
{
    public class Driver
    {
        public void Load()
        {
            var driverPath = "\\\\.\\KMDFDriver1";/*@"C:\DriverTest\Drivers\KMDFDriver1.sys"*/
            var hFileHandle = CreateFile(driverPath, GENERIC_READ | GENERIC_WRITE, 0, (IntPtr)0, OPEN_EXISTING, 0, NULL);
            
            if (hFileHandle == INVALID_HANDLE_VALUE)
            {
                Console.WriteLine("Failed to open");
                return;
            }

            try
            {
                var functionCode = (int)0x800;
                var ioCtlCode = CTL_CODE(FILE_DEVICE_UNKNOWN, functionCode, METHOD_OUT_DIRECT, FILE_ANY_ACCESS);
                var output = new byte[64];
                var input = Encoding.ASCII.GetBytes("hejsaansassadsdadasdas");
                var bytesReturned = -1;
                var success = DeviceIoControl(hFileHandle, ioCtlCode, input, input.Length, output, output.Length, ref bytesReturned, 0);
                if (success)
                {
                    var response = Encoding.UTF8.GetString(output);
                    Console.WriteLine("Success");
                }
            }
            finally
            {
                CloseHandle(hFileHandle);
            }
        }
    }
}
