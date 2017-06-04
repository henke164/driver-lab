using System;
using System.Linq;
using System.Text;
using static DriverLoader.Win32Methods;

namespace DriverLoader
{
    public class Driver
    {
        public string LoadProcess(int processId)
            => IOCTLRequest(IOCTLCodes.InitializeProcess, processId.ToString());
        
        public string GetBaseAddress()
            => IOCTLRequest(IOCTLCodes.GetBaseAddress, string.Empty);

        public string GetMemoryStringValue(string memoryAddress)
            => IOCTLRequest(IOCTLCodes.GetMemory, memoryAddress);

        private string IOCTLRequest(IOCTLCodes code, string input)
        {
            var bytesReturned = -1;
            var output = new byte[64];
            var inputBytes = Encoding.ASCII.GetBytes(input);
            var fileHandle = CreateFileHandle("\\\\.\\KMDFDriver1");
            try
            {
                var ioCtlCode = CTL_CODE(FILE_DEVICE_UNKNOWN, code, METHOD_OUT_DIRECT, FILE_ANY_ACCESS);
                var success = DeviceIoControl(fileHandle, ioCtlCode, inputBytes, inputBytes.Length, output, output.Length, ref bytesReturned, 0);
                if (success)
                {
                    var trimmedBytes = output.ToList().Where(o => o != '\0').ToArray();
                    return Encoding.UTF8.GetString(trimmedBytes);
                }
            }
            finally
            {
                CloseHandle(fileHandle);
            }
            return null;
        }

        private int CreateFileHandle(string path)
        {
            var fileHandle = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, (IntPtr)0, OPEN_EXISTING, 0, NULL);

            if (fileHandle == INVALID_HANDLE_VALUE)
            {
                Console.WriteLine("Failed to open");
            }
            return fileHandle;
        }
    }
}
