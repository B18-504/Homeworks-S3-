#pragma once

class Number
{
public:
	virtual void SetRandVal() = 0;

	virtual Number *Clone() = 0;
	
	virtual double ValueAsDbl() = 0;
	virtual int ValueAsInt() = 0;
	virtual uint ValueAsUint() = 0;
	virtual char *ValueAsStr() = 0;
	
	~Number() = default;
};

class Int : public Number
{
public:
	int body;
	
	Int() = default;
	Int(int a);
	
	void SetRandVal() override;
	
	Number *Clone() override;
	
	double ValueAsDbl() override;
	int ValueAsInt() override;
	uint ValueAsUint() override;
	char *ValueAsStr() override;
};

class Uint : public Number
{
public:
	uint body;
	
	Uint() = default;
	Uint(uint a);
	
	void SetRandVal() override;
	
	Number *Clone() override;
	
	double ValueAsDbl() override;
	int ValueAsInt() override;
	uint ValueAsUint() override;
	char *ValueAsStr() override;
};

class Double : public Number
{
public:
	double body;
	
	Double() = default;
	Double(double a);
	
	void SetRandVal() override;
	
	Number *Clone() override;
	
	double ValueAsDbl() override;
	int ValueAsInt() override;
	uint ValueAsUint() override;
	char *ValueAsStr() override;
};

class Bool : public Number
{
public:
	bool body;
	
	Bool() = default;
	Bool(bool a);
	
	void SetRandVal() override;
	
	Number *Clone() override;
	
	double ValueAsDbl() override;
	int ValueAsInt() override;
	uint ValueAsUint() override;
	char *ValueAsStr() override;
};

#include "Number.cpp"
