#include "stdafx.h"
#include "IFile.h"
#include <stdio.h>
#include <assert.h>


/************/
const unsigned int SIZEOF_CHAR = sizeof(char);
/************/


TFile::TFile()
{
	m_file = nullptr;
}


/**
Opens a file

@param fileName Name of the file
@param openMode The enum value of the open type

return The result of the operation (0 if properly opened)
*/
int TFile::OpenFile(const char * fileName, TFile::FileOpenMode openMode)
{
	assert(fileName);
	int result = 0;

	if (m_file && m_file->content) // Close the file if it was already opened
		result = CloseFile();

	if (!result)
	{
		char stdioOpenMode[2] = "r";
		switch (openMode)
		{
		case TFile::FileOpenMode::ReadOnly:
			stdioOpenMode[0] = 'r';
			break;
		case TFile::FileOpenMode::ReadWrite:
			stdioOpenMode[0] = 'w';
			break;
		}
		FILE * fopenFile = fopen(fileName, stdioOpenMode);

		if (fopenFile)
		{
			if (!m_file)
				m_file = new TFile::FileIdentifier();

			m_file->content = fopenFile;
			return 0;
		}
		else
			return 1;
	}
	else
		return 1;
}


/**
Closes a file

@return The result of the operation (0 if properly closed)
*/
int TFile::CloseFile()
{
	int result = 0;

	if (m_file) // m_file will be null if it was not opened
	{
		if (m_file->content)
			result = fclose(static_cast<FILE *>(m_file->content));

		// Releases the memory of FileIdentifier and set it to null as it won't be necessary until next call to Open
		delete m_file;
		m_file = nullptr;
	}

	return result;
}


/**
Reads a number of characters in a file and stores them in an output buffer

@param outputBuffer Buffer where the read characters will be stored
@charactersToRead Number of characters to read

@return The number of characters read
*/
unsigned int TFile::ReadFile(char * outputBuffer, unsigned int charactersToRead)
{
	assert(m_file);
	assert(m_file->content);
	assert(outputBuffer);

	return fread(outputBuffer, SIZEOF_CHAR, charactersToRead, static_cast<FILE *>(m_file->content));
}


/**
Writes the characters contained in an input buffer to the file passed as parameter.

@param inputBuffer which contains the characters to write
@param inputLength Length of the input buffer

@return The number of characters written
*/
unsigned int TFile::WriteFile(const char * inputBuffer, unsigned int inputLength)
{
	assert(m_file);
	assert(m_file->content);
	assert(inputBuffer);

	return fwrite(inputBuffer, SIZEOF_CHAR, inputLength, static_cast<FILE *>(m_file->content));
}

TFile::~TFile()
{
	if (m_file) // Closes and releases the file memory if necessary.
	{
		CloseFile();
	}
}