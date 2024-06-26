#include <iostream>
#include "./Jacker/Jacker.h"
int main()
{
    auto handleInfo = Jacker::GetSysHandleInfo();

	if (!handleInfo)
		return -1;

	for (size_t i = 0; i < handleInfo->NumberOfHandles; i++)
	{
		
		auto currHandle = handleInfo->Handles[i];
		auto hijackedHandle = Jacker::DupHandle(currHandle);

		if (hijackedHandle) {
			
			if (currHandle.ObjectTypeIndex == 37) { // file handle
				auto ownerProcId = (DWORD)currHandle.UniqueProcessId;
				auto fileName = Jacker::GetFileName(hijackedHandle);

				if (fileName->FileNameLength == 0) {
					continue;
				}
				
				if (!wcscmp(fileName->FileName, L"Put Target Path Here")) {

					wprintf(L"[+] Found Target File Locked By %ls\n", Jacker::GetProcessNameFromId(ownerProcId));
					HANDLE procTm = OpenProcess(PROCESS_TERMINATE, FALSE, ownerProcId);

					if (TerminateProcess(procTm, 0)) {
						printf("[+] Terminated!\n");
					}

				}
				
			}

		}
		
	}
}
