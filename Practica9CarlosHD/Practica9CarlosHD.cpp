// Practica9CarlosHD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IFile.h"


int main()
{
	int fileOpenResult = 1;
	char * buffer = nullptr;
	unsigned int bytesRead = 0;
	unsigned int bytesWritten = 0;

	TFile * file = new TFile();

	fileOpenResult = file->OpenFile("test.txt", TFile::FileOpenMode::ReadOnly);

	if (!fileOpenResult)
	{
		buffer = new char[14];
		bytesRead = file->ReadFile(buffer, 13);
		buffer[13] = '\0';

		printf("\n%d bytes read from file", bytesRead);
		printf("\nBytes read: %s", buffer);
		bytesRead = file->ReadFile(buffer, 13);
		buffer[13] = '\0';

		printf("\n%d bytes read from file", bytesRead);
		printf("\nBytes read: %s", buffer);
		bytesRead = file->ReadFile(buffer, 13);
		buffer[13] = '\0';

		printf("\n%d bytes read from file", bytesRead);
		printf("\nBytes read: %s", buffer);
		int file1Closed = file->CloseFile();
		printf("\nResult of CloseFile 1: %d", file1Closed);

		fileOpenResult = file->OpenFile("newfile.txt", TFile::FileOpenMode::ReadWrite);
		if (!fileOpenResult)
		{
			bytesWritten = file->WriteFile(buffer, 13);
			printf("\n\n%d bytes written in new file", bytesWritten);
			int file2Closed = file->CloseFile();
			printf("\nResult of CloseFile 2: %d", file2Closed);
		}
		else
			printf("\n\nFile couldn't be opened");

		delete[]buffer;
		buffer = nullptr;

		fileOpenResult = file->OpenFile("newfile.txt", TFile::FileOpenMode::ReadOnly);
		if (!fileOpenResult)
		{
			buffer = new char[14];

			printf("\n\nNew file opened");
			bytesRead = file->ReadFile(buffer, 13);
			buffer[13] = '\0';
			printf("\n%d bytes read from new file", bytesRead);
			printf("\nBytes read: %s", buffer);
			int file3Closed = file->CloseFile();
			printf("\nResult of CloseFile 3: %d", file3Closed);

			delete[]buffer;
			buffer = nullptr;
		}
		else
			printf("\n\nFile couldn't be opened");

	}
	else
		printf("\n\nFile couldn't be opened");

	delete file;

	printf("\n\nPress Enter to quit...");
	getchar();

	return 0;
}

