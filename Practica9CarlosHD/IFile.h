#pragma once

class TFile
{

public:

	typedef struct _fileId
	{
		void *content;
	} FileIdentifier;

	enum FileOpenMode
	{
		ReadOnly,
		ReadWrite,
	};

	TFile();

	int OpenFile(const char * fileName, FileOpenMode openMode);
	int CloseFile();
	unsigned int ReadFile(char * outputBuffer, unsigned int charactersToRead);
	unsigned int WriteFile(const char * inputBuffer, unsigned int inputLength);

	~TFile();

private:
	FileIdentifier * m_file;
};