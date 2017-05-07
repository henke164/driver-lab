#include <stdio.h>
#include <Windows.h>

#define IOCTL_HELLO_WORLD CTL_CODE(FILE_DEVICE_UNKNOWN,0x900,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)
#define IOCTL_RESTART_SYSTEM CTL_CODE(FILE_DEVICE_UNKNOWN,0x901,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)
#define IOCTL_TERMINATE_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,0x902,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)
#define IOCTL_HIDE_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,0x903,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)

int main(int argc, char* argv[])
{
	SC_HANDLE hService;
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	SERVICE_STATUS ss;

	if (hSCManager)
	{
		printf("Create Service\n");

		hService = CreateService(hSCManager, L"KMDFService",
			L"KMDFService",
			SERVICE_START | DELETE | SERVICE_STOP,
			SERVICE_KERNEL_DRIVER,
			SERVICE_DEMAND_START,
			SERVICE_ERROR_IGNORE,
			L"C:\\DriverTest\\Drivers\\KMDFDriver1.sys",
			NULL, NULL, NULL, NULL, NULL);

		if (!hService)
		{
			hService = OpenService(hSCManager, L"KMDFService",
				SERVICE_START | DELETE | SERVICE_STOP);
		}

		if (hService)
		{
			printf("Start Service\n");

			StartService(hService, 0, NULL);
			printf("Press Enter to close service\r\n");
			getchar();
			ControlService(hService, SERVICE_CONTROL_STOP, &ss);

			DeleteService(hService);

			CloseServiceHandle(hService);
		}

		CloseServiceHandle(hSCManager);
	}
}