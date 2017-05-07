using System;
using System.Runtime.InteropServices;

namespace DriverLoader
{
    class Program
    {
        static void Main(string[] args)
        {
            var driver = new Driver();
            driver.Load();
        }
    }
}
