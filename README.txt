The GetNotepadFileInfo, UDPClient, and UDPServer folders contain code written
in C++ to perform process (DLL) injection into the Notepad.exe process space.
Compiled/linked using Microsoft Visual Studio Community 2022 (64-bit) Edition.
Builds the following binary modules:

GetNotepadFileInfo.exe

	Spins in an infinite loop searching for a 'Notepad' or 'Save As' window
	owned by a thread running in the foreground. When a window is found,
	SetWindowsHookEx is called to install a corresponding WH_GETMESSAGE or
	WH_CALLWNDPROC windows message hook procedure.

UDPCient.dll

	Contains the payload code to be injected into the Notepad.exe process
	space. Utilizes UDP socket communication to send data (file path and
	size of the saved file) to the server process. The project file
	contains a Post-Build Event command to copy UDPCient.dll to the system
	root folder. Visual Studio must be run with 'Administrator' priviledges
	in order for this to work.

UDPServer.exe

	Server process that receives the saved file data from Notepad.exe and
	writes it to the standard output.