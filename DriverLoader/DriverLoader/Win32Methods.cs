namespace DriverLoader
{
    using Microsoft.Win32.SafeHandles;
    using System;
    using System.Runtime.InteropServices;

    [ComVisible(false), System.Security.SuppressUnmanagedCodeSecurity()]
    public class Win32Methods
    {
        public const int INVALID_HANDLE_VALUE = -1;
        public const int NULL = 0;
        public const int ERROR_SUCCESS = 0;
        public const int FILE_READ_DATA = (0x0001);
        public const int FILE_SHARE_READ = 0x00000001;
        public const int OPEN_EXISTING = 3;

        public const uint GENERIC_WRITE_U = 0x40000000;
        public const uint GENERIC_READ_U = 0x80000000;

        public const int GENERIC_WRITE = 0x40000000;
        public const int GENERIC_READ = unchecked((int)0x80000000);
        public const int METHOD_BUFFERED = 0;
        public const int METHOD_OUT_DIRECT = 2;
        public const int METHOD_NEITHER = 3;
        public const int FILE_ANY_ACCESS = 0;
        public const int FILE_DEVICE_VIRTUAL_DISK = 0x00000024;
        public const int FILE_DEVICE_UNKNOWN = 0x00000022;

        [DllImport("Kernel32.dll", ExactSpelling = true, CharSet = CharSet.Auto, SetLastError = true)]
        public static extern bool CloseHandle(int hHandle);
        
        [DllImport("Kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern int CreateFile(string lpFileName, int dwDesiredAccess, 
            int dwShareMode, IntPtr lpSecurityAttributes, int dwCreationDisposition, 
            int dwFlagsAndAttributes, int hTemplateFile);
            
        [DllImport("Kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern bool DeviceIoControl(
            int hDevice, int dwIoControlCode, byte[] InBuffer, int nInBufferSize,
            byte[] OutBuffer, int nOutBufferSize, ref int pBytesReturned, int pOverlapped);

        public static int CTL_CODE(int DeviceType, int Function, int Method, int Access)
        {
            return (((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method));
        }

        public int DEVICE_TYPE_FROM_CTL_CODE(int ctrlCode)
        {
            return (int)((ctrlCode & 0xffff0000) >> 16);
        }
    }
}