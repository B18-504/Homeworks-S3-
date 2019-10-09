#pragma once

class Exception
{
protected:
	char *message;
	
public:
	unsigned int code;
	
	Exception()
	{
		code = 0;
		message = "What a wierd exception";
	}

private:
	Exception(unsigned char code, char *message)
	{
		this->code = code;
		this->message = message;
	}

public:
	void alert()
	{
		printf("%s\n", message);
	}
};

class Max_Size_Reached : public Exception
{
public:
	Max_Size_Reached()
	{
		Exception::code = 0x10;
		Exception::message = "Could not extend array - max size reached";
	}
};

class Mem_Alloc_Error : public Exception
{
public:
	Mem_Alloc_Error()
	{
		Exception::code = 0x11;
		Exception::message = "Malloc has fucked up";
	}
};

class Out_of_Range : public Exception
{
public:
	Out_of_Range()
	{
		Exception::code = 0x12;
		Exception::message = "Index is out of range";
	}
};

class Container_Is_Empty : public Exception
{
public:
	Container_Is_Empty()
	{
		Exception::code = 0x13;
		Exception::message = "Can't get data from an empty container";
	}
};

class Invalid_Type_Name : public Exception
{
public:
	Invalid_Type_Name()
	{
		Exception::code = 0x14;
		Exception::message = "Can't create object of an unknown type";
	}
};

class Invalid_Implementation_Subclass : public Exception
{
public:
	Invalid_Implementation_Subclass()
	{
		Exception::code = 0x15;
		Exception::message = "Polymorphyc argument is of wrong sublcass";
	}
};

class Bad_Console_Input : public Exception
{
public:
	Bad_Console_Input()
	{
		Exception::code = 0x16;
		Exception::message = "Console input has wrong syntax";
	}
};

class Bad_File_Input : public Exception
{
public:
	Bad_File_Input()
	{
		Exception::code = 0x17;
		Exception::message = "File input has wrong syntax";
	}
};

class Bad_String_Format : public Exception
{
public:
	Bad_String_Format()
	{
		Exception::code = 0x18;
		Exception::message = "String-to-type conversion failed: bad string format";
	}
};

class File_Stream_Error : public Exception
{
public:
	File_Stream_Error()
	{
		Exception::code = 0x19;
		Exception::message = "Error occured while working with file IO";
	}
};

typedef Max_Size_Reached MSR;
typedef Mem_Alloc_Error MAE;
typedef Out_of_Range OoR;
typedef Container_Is_Empty CIE;
typedef Invalid_Type_Name ITN;
typedef Invalid_Implementation_Subclass IIS;
typedef Bad_Console_Input BCI;
typedef Bad_File_Input BFI;
typedef Bad_String_Format BSF;
typedef File_Stream_Error FSE;
