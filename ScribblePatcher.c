#include <windows.h>

#define PATCH_OFFSET 0x136BF1
#define BYTE_EXPECTED 0x41
#define BYTE_NEW 0x21

#define EXIT_USER_CANCEL 4
#define EXIT_FILE_ERROR 3
#define EXIT_INCORRECT_VERSION 2
#define EXIT_ALREADY_PATCHED 1
#define EXIT_SUCCESS 0

int CALLBACK WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	// Configure and display the open file dialog
	LPSTR filename[1024];
	OPENFILENAME ofn;
	ofn.lStructSize =		sizeof(OPENFILENAME);
	ofn.hwndOwner =			NULL;
	ofn.hInstance =			hInst;
	ofn.lpstrFilter =		"Scribble.exe\0Scribble.exe\0Applications (*.exe)\0*.exe\0All Files (*.*)\0*.*\0\0";
	ofn.lpstrCustomFilter =	NULL;
	ofn.nFilterIndex =		0;
	ofn.lpstrFile =			filename;
	ofn.nMaxFile =			1024;
	ofn.lpstrFileTitle =	NULL;
	ofn.lpstrInitialDir =	"C:\\Program Files (x86)\\Steam\\SteamApps\\common\\Scribblenauts";
	ofn.lpstrTitle =		"Select your Scribblenauts Unlimited executable (Scribble.exe)";
	ofn.Flags =				OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	
	if (!GetOpenFileName(&ofn)) {
		// user hit Cancel; just quit without a message
		return EXIT_USER_CANCEL;
	}
	
	// Open the file and check patchability
	
	DWORD byteCount;
	HANDLE file = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if (file == INVALID_HANDLE_VALUE) {
		// Display an error message. Reuses the filename buffer as it's no longer needed.
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, filename, 1024, NULL);
		MessageBox(NULL, filename, "Error", MB_ICONERROR);
		return EXIT_FILE_ERROR;
	}
	
	BYTE byteBuf;
	SetFilePointer(file, PATCH_OFFSET, NULL, FILE_BEGIN);
	ReadFile(file, &byteBuf, 1, &byteCount, NULL);
	
	if (byteBuf == BYTE_EXPECTED) {
		// do nothing yet; all other cases will return
	} else if (byteBuf == BYTE_NEW) {
		MessageBox(NULL, "Patch unsuccessful.\nThe program has most likely already been patched.", "Error", MB_ICONEXCLAMATION);
		CloseHandle(file);
		return EXIT_ALREADY_PATCHED;
	} else {
		MessageBox(NULL, "Patch unsuccessful.\nUnfortunately, the patcher does not support this version.", "Error", MB_ICONERROR);
		CloseHandle(file);
		return EXIT_INCORRECT_VERSION;
	}
	
	// Apply the patch
	byteBuf = BYTE_NEW;
	SetFilePointer(file, PATCH_OFFSET, NULL, FILE_BEGIN);
	WriteFile(file, &byteBuf, 1, &byteCount, NULL);
	
	MessageBox(NULL, "Patch successful!\nYou should now be able to type numbers and special characters in Scribblenauts Unlimited.\nEnjoy!", "Success!", MB_ICONINFORMATION);
	
	CloseHandle(file);
	return EXIT_SUCCESS;
}
