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

class Out_Of_Range : public Exception
{
public:
	Out_Of_Range()
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

typedef Max_Size_Reached MSR;
typedef Mem_Alloc_Error MAE;
typedef Out_Of_Range OoR;
typedef Container_Is_Empty CIE;
typedef Invalid_Type_Name ITN;
