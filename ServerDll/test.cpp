#include <windows.h>
#include <stdio.h>

int main()
{
	char path[_MAX_PATH], *p = path;
	GetModuleFileNameA(NULL, path, sizeof(path));
	while (*p) ++p;
	while ('\\' != *p) --p;
	strcpy(p+1, "ServerDll.dll");
	HMODULE hDll = LoadLibraryA(path);
	typedef void (*TestRun)(char* strHost,int nPort );
	 TestRun run = hDll ? TestRun(GetProcAddress(hDll, MAKEINTRESOURCE(1))) : NULL;
	 if (run)
	 {
		 char ip[100];
		 strcpy(p+1, "remote.ini");
		 GetPrivateProfileStringA("remote", "ip", "127.0.0.1", ip, sizeof(ip), path);
		 int port = GetPrivateProfileIntA("remote", "port", 2356, path);
		 printf("[remote] %s:%d\n", ip, port);
		 run(ip, port);
		 return 0;
	 }
	 return -1;
}
