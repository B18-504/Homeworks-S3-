#pragma once

class Exception
{
public:
	unsigned int code;
	char *message;
	
	Exception()
	{
		code = 0;
		message = "What a wierd exception";
	}

	Exception(unsigned char code, char *message)
	{
		this->code = code;
		this->message = message;
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

class Slider_Is_Unbound : public Exception
{
public:
	Slider_Is_Unbound()
	{
		Exception::code = 0x1a;
		Exception::message = "Slider is not bound to a sequence. The referred sequence was deleted, critically changed or initialisation went wrong";
	}
};

class Null_Ptr_Exception : public Exception
{
public:
	Null_Ptr_Exception()
	{
		Exception::code = 0x1b;
		Exception::message = "Tried to access by nullptr";
	}
};

class Strong_Name_Redefinition : public Exception
{
public:
	Strong_Name_Redefinition()
	{
		Exception::code = 0x1c;
		Exception::message = "Can't redefine strong names (weak names are in To Be Done)";
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
typedef Slider_Is_Unbound SIU;
typedef Null_Ptr_Exception NPE;
typedef Strong_Name_Redefinition SNR;
