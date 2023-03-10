#include "SimpleFile.h"
#include "StringTools.h"


SimpleFile::SimpleFile(std::string file, char type)
{
	init(file, type);
}

void SimpleFile::init(std::string filename, char type)
{
	this->type = type&0x0F;
	this->dataType = type&0xF0;
	this->size = 0;
	switch (this->type)
	{
	case SimpleFile::READ:
		
		//try to open
		this->file = new std::fstream(filename, std::fstream::in | std::fstream::ate | std::fstream::binary);

		size = (size_t)file->tellg();
		file->close();

		this->file->open(filename, std::fstream::in | std::fstream::binary);

		//remove signifier
		if(dataType==WIDECHAR)
		{
			int c1 = file->get();
			int c2 = file->get();

			if(c1 == 0xFE && c2 == 0xFF)
			{
				//utf-16 file
			}
			else
			{
				//no header
				file->putback(c2);
				file->putback(c1);
			}
		}
		else if(dataType==UTF8)
		{
			int c1 = file->get();
			int c2 = file->get();
			int c3 = file->get();

			if(c1 == 0xEF && c2 == 0xBB && c3 == 0xBF)
			{
				//utf-8 file
			}
			else
			{
				//no header
				file->putback(c3);
				file->putback(c2);
				file->putback(c1);
			}
		}
		this->filename = filename;
		break;
	case SimpleFile::WRITE:
		//
		this->file = new std::fstream(filename, std::fstream::out | std::fstream::binary);
		this->filename = filename;

		break;
	case SimpleFile::WRITE_APPEND:
		//
		this->file = new std::fstream(filename, std::fstream::in | std::fstream::ate | std::fstream::binary);

		size = (size_t)file->tellg();
		file->close();

		this->file->open(filename, std::fstream::out | std::fstream::app | std::fstream::binary);

		this->filename = filename;
		break;
	default:
		break;
	}
}

SimpleFile::~SimpleFile()
{
	if(isOpen())
	{
		close();
	}
	
	delete file;
}

int SimpleFile::readInt()
{
	if (isOpen() && type == SimpleFile::READ && !isEndOfFile())
	{
		return file->get();
	}
	else
	{
		//File is not opened for reading
	}
	return 0;
}

char SimpleFile::readByte()
{
	if (isOpen() && type == SimpleFile::READ && !isEndOfFile())
	{
		return file->get();
	}
	else
	{
		//File is not opened for reading
	}
	return '\0';
}

void SimpleFile::readBytes(char* buffer, int size)
{
	if (isOpen() && type == SimpleFile::READ && !isEndOfFile())
	{
		file->read(buffer, size);
	}
	else
	{
		//File is not opened for reading
	}
}

wchar_t toWideChar(unsigned char p, unsigned char p2)
{
	wchar_t n;

	n = p;
	n = n << 8;
	n += p2;

	return n;
}

wchar_t SimpleFile::readWideChar()
{
	unsigned char p1;
	unsigned char p2;
	if (isOpen() && type == SimpleFile::READ && !isEndOfFile())
	{
		p1 = file->get();
		if(isEndOfFile())
			return -1;

		p2 = file->get();
		if(isEndOfFile())
			return -1;

		return toWideChar(p1, p2);
	}
	else
	{
	}
	return L'\0';
}

int SimpleFile::getChar()
{
	if(dataType==SimpleFile::ASCII)
		return readByte();
	else if(dataType==SimpleFile::WIDECHAR)
		return readWideChar();
	else if(dataType==SimpleFile::UTF8)
		return readUTF8Char();
	
	return 0;
}

std::string SimpleFile::readString()
{
	std::string p = "";
	int c = '\0';

	if (isOpen() && type == SimpleFile::READ)
	{
		while (!isEndOfFile())
		{
			c = getChar();
			if(isEndOfFile())
			{
				break;
			}

			if (c != LINE_BREAK_1)
			{
				p += c;
			}
			else
			{
				c = getChar();
				if(isEndOfFile())
				{
					break;
				}

				if (c == LINE_BREAK_2)
				{
					//Hit a line break
					break;
				}
				else
				{
					//Hit something else.
					//Fix later I guess.
					p += LINE_BREAK_1;
					p += c;
				}
				
			}
			
		}
	}
	else
	{
		//File is not opened for reading
	}

	return p;
}

std::wstring SimpleFile::readWideString()
{
	std::wstring p = L"";
	wchar_t c = L'\0';
	// unsigned char p1; //Not used
	// unsigned char p2; //Not used
	wchar_t n;

	if (isOpen() && type == SimpleFile::READ && !isEndOfFile())
	{
		while (!isEndOfFile())
		{
			c = getChar();

			if(isEndOfFile())
			{
				break;
			}

			if (c != LINE_BREAK_1)
			{
				p += c;
			}
			else
			{
				n = getChar();

				if(isEndOfFile())
				{
					break;
				}

				if (n == LINE_BREAK_2)
				{
					//Hit a line break
					break;
				}
				else
				{
					//Hit something else.
					//Fix later I guess.
					p += c;
					p += n;
				}
			}
		}

	}
	else
	{
		//File is not opened for reading
		#ifdef USE_EXCEPTIONS
		
		//not open for reading. could be file access or the file may not exist.
		throw SimpleFile::FileReadException();

		#endif
	}

	return p;
}

int SimpleFile::readUTF8Char()
{
	if (isOpen() && type == SimpleFile::READ && !isEndOfFile())
	{
		std::vector<unsigned char> chars = std::vector<unsigned char>();
		unsigned char c1 = file->get();

		if(isEndOfFile())
			return -1;
		
		if(c1>>7 == 0)
		{
			return c1;
		}
		else if( ((c1 >> 5) & 0x01) == 0)
		{
			chars.push_back(c1);
			c1 = file->get();
			
			if(isEndOfFile())
				return -1;

			if( (c1 >> 7) == 1 && ((c1 >> 6) & 0x01) == 0)
			{
				//valid utf8
				chars.push_back( c1 );
				return StringTools::utf8ToChar(chars);
			}
			else
			{
				//invalid
				file->putback(c1);
				return chars[0];
			}
		}
		else if( ((c1 >> 4) & 0x01) == 0)
		{
			chars.push_back(c1);
			chars.push_back( (unsigned char)file->get() );
			if(isEndOfFile())
				return -1;

			chars.push_back( (unsigned char)file->get() );
			if(isEndOfFile())
				return -1;
			return StringTools::utf8ToChar(chars);
		}
		else if( ((c1 >> 3) & 0x01) == 0)
		{
			chars.push_back(c1);
			chars.push_back( (unsigned char)file->get() );
			if(isEndOfFile())
				return -1;

			chars.push_back( (unsigned char)file->get() );
			if(isEndOfFile())
				return -1;

			chars.push_back( (unsigned char)file->get() );
			if(isEndOfFile())
				return -1;
			return StringTools::utf8ToChar(chars);
		}
		else
		{
			//not utf8
			return c1;
		}
	}
	else
	{
		//File is not opened for reading
	}
	return 0;
}

std::vector<std::string> SimpleFile::readFullFileString()
{
	std::vector<std::string> info = std::vector<std::string>();

	if(isOpen() && type == SimpleFile::READ)
	{
		while (!isEndOfFile())
		{
			info.push_back(readString());
		}
	}
	else
	{
	}

	return info;
}

std::vector<std::wstring> SimpleFile::readFullFileStringWide()
{
	std::vector<std::wstring> info = std::vector<std::wstring>();

	// Sometimes contains a header that reads FF FE. 
	// unsigned char c1 = file->get();
	// unsigned char c2 = file->get();

	if(isOpen() && type == SimpleFile::READ)
	{
		while (!isEndOfFile())
		{
			//read
			info.push_back(readWideString());
		}
	}
	else
	{
	}


	return info;
}

std::vector<unsigned char> SimpleFile::readFullFileAsBytes()
{
	std::vector<unsigned char> info = std::vector<unsigned char>();

	if(isOpen() && type == SimpleFile::READ)
	{
		while (true)
		{
			//read
			unsigned char c = file->get();

			if(!file->eof())
				info.push_back(c);
			else
				break;
		}
	}
	else
	{
	}

	return info;
}

void SimpleFile::writeByte(char c)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			file->put(c);
		}
		else
		{
			//File is not opened for writing
		}
	}
	else
	{
		//File is not opened
	}
}

void SimpleFile::writeWideChar(wchar_t c)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			unsigned char c1 = c>>8;
			unsigned char c2 = c & 0xFF;
			file->put(c1);
			file->put(c2);
		}
		else
		{
			//File is not opened for writing
		}
	}
	else
	{
		//File is not opened
		#ifdef USE_EXCEPTIONS

		//not open for writing. could be file access or the file may not exist.
		throw SimpleFile::FileWriteException();

		#endif
	}
}

void SimpleFile::writeUTF8Char(int c)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			std::vector<unsigned char> bytes = StringTools::toUTF8(c);
			file->write((char*)bytes.data(), bytes.size());
		}
		else
		{
			//File is not opened for writing
		}
	}
	else
	{
		//File is not opened
	}
}

void SimpleFile::writeBytes(unsigned char* data, int size)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			file->write((char*)data, size);
		}
		else
		{
			//File is not opened for writing
		}
	}
	else
	{
		//File is not opened
		#ifdef USE_EXCEPTIONS

		//not open for writing. could be file access or the file may not exist.
		throw SimpleFile::FileWriteException();

		#endif
	}
}

void SimpleFile::writeString(std::string line)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			if(dataType == ASCII)
			{
				file->write(line.c_str(), line.size());
			}
			else if(dataType == WIDECHAR)
			{
				for (size_t i = 0; i < line.size(); i++)
				{
					file->put(0);
					file->put(line[i]);
				}
			}
			else
			{
				for (size_t i = 0; i < line.size(); i++)
				{
					std::vector<unsigned char> bytes = StringTools::toUTF8(line[i]);
					file->write((char*)bytes.data(), bytes.size());
				}
			}
		}
		else
		{
			//File is not opened for writing
			#ifdef USE_EXCEPTIONS
			
			throw SimpleFile::FileWriteException();

			#endif
		}
	}
	else
	{
		//File is not opened
		#ifdef USE_EXCEPTIONS

		//not open for writing. could be file access or the file may not exist.
		throw SimpleFile::FileWriteException();

		#endif
	}
}

void SimpleFile::writeWideString(std::wstring line)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			if(dataType == ASCII)
			{
				for (size_t i = 0; i < line.size(); i++)
				{
					file->put(line[i]);
				}
			}
			else if(dataType == WIDECHAR)
			{
				for (size_t i = 0; i < line.size(); i++)
				{
					unsigned char c1 = line[i]>>8;
					unsigned char c2 = line[i] & 0xFF;
					file->put(c1);
					file->put(c2);
				}
			}
			else
			{
				for (size_t i = 0; i < line.size(); i++)
				{
					std::vector<unsigned char> bytes = StringTools::toUTF8(line[i]);
					file->write((char*)bytes.data(), bytes.size());
				}
			}
		}
		else
		{
			//File is not opened for writing
			#ifdef USE_EXCEPTIONS
			
			throw SimpleFile::FileWriteException();

			#endif
		}
	}
	else
	{
		//File is not opened
		#ifdef USE_EXCEPTIONS

		//not open for writing. could be file access or the file may not exist.
		throw SimpleFile::FileWriteException();

		#endif
	}
}

void SimpleFile::writeLineBreak()
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			if(dataType == ASCII || dataType == UTF8)
			{
				file->put(LINE_BREAK_1);
				file->put(LINE_BREAK_2);
			}
			else
			{
				file->put(0);
				file->put(LINE_BREAK_1);
				
				file->put(0);
				file->put(LINE_BREAK_2);
			}
		}
		else
		{
			//File is not opened for writing
			#ifdef USE_EXCEPTIONS
			
			throw SimpleFile::FileWriteException();

			#endif
		}
	}
	else
	{
		//File is not opened
		#ifdef USE_EXCEPTIONS

		//not open for writing. could be file access or the file may not exist.
		throw SimpleFile::FileWriteException();

		#endif
	}
}

bool SimpleFile::isOpen()
{
	if(file != nullptr)
	{
		return file->is_open();
	}
	else
	{
		return false;
	}
}

void SimpleFile::close()
{
	if(file != nullptr)
	{
		file->close();
	}
}

bool SimpleFile::isEndOfFile()
{
	if(file != nullptr)
	{
		return !file->good();
	}
	else
	{
		return true;
	}
}

std::string SimpleFile::getFileName()
{
	return filename;
}

size_t SimpleFile::getSize()
{
	return size;
}

size_t SimpleFile::getBytesLeft()
{
	if(isOpen() && type == READ)
	{
		return (size - file->tellg());
	}
	else
	{
		return 0;
	}
}

void SimpleFile::seek(size_t index)
{
	if(type == READ)
	{
		file->seekg(index);
	}
	else
	{
		file->seekp(index);
	}
}