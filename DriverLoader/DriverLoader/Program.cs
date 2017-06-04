using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace DriverLoader
{
    class Program
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern bool ReadProcessMemory(IntPtr hProcess, long lpBaseAddress, byte[] lpBuffer, ulong dwSize, out IntPtr lpNumberOfBytesRead);

        static void Main(string[] args)
        {
            // 6520 4920
            var tslProc = Process.GetProcessesByName("TslGame");
            if (tslProc.Length > 0)
            {
                Console.WriteLine(tslProc[0].Id);
            }

            var driver = new Driver();
            Console.WriteLine("Enter ProcessId");
            var processId = int.Parse(Console.ReadLine());
            var result = driver.LoadProcess(processId);
            Console.WriteLine(result);
            var memoryVal = driver.GetBaseAddress();//.GetMemoryStringValue("14923948");
            Console.WriteLine(memoryVal);
            Console.ReadLine();
            //var procs = Process.GetProcessById(processId);
            //var baseAddress = procs.MainModule.BaseAddress.ToInt64();
            /*
            long sens = baseAddress + 0x33765E0;
            var sensOffset = new long[] { 0x1A0, 0x188 };

            ReadAddress(p, sens, sensOffset);
            //base : 3191048667116*/
        }

        static void ReadAddress(Process process, long address, long[] offsets)
        {
            unsafe
            {
                IntPtr outPtr;
                const uint size = 8;
                var str = new List<string>();
                str.Add(address.ToString("X"));
                byte[] lpBuffer = new byte[size];
                ReadProcessMemory(process.Handle, address, lpBuffer, size, out outPtr);
                var value = BitConverter.ToInt32(lpBuffer, 0);

                str.Add(value.ToString("X"));
                /*
                for (var x  = 0; x < offsets.Length; x++)
                {
                    lpBuffer = new byte[size];
                    ReadProcessMemory(process.Handle, value + offsets[x], lpBuffer, size, out outPtr);

                    if (x < offsets.Length - 1)
                    {
                        value = BitConverter.ToInt64(lpBuffer, 0);
                    }
                    else
                    {
                        var finalValue = BitConverter.ToSingle(lpBuffer, 0);
                    }

                    str.Add(value.ToString("X"));
                }*/
            }
        }
    }
}
