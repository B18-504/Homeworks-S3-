class Number
{
public:
	virtual void input() = 0;
	virtual void print() = 0;
	virtual Number *Clone() = 0;
	virtual double ValueAsDbl() = 0;
	~Number() = default;
};

class Int : public Number
{
public:
	int body;
	
	Int() = default;
	Int(int a);
	void input() override;
	void print() override;
	Number *Clone() override;
	double ValueAsDbl() override;
};

class Uint : public Number
{
public:
	uint body;
	
	Uint() = default;
	Uint(uint a);
	void input() override;
	void print() override;
	Number *Clone() override;
	double ValueAsDbl() override;
};

class Double : public Number
{
public:
	double body;
	
	Double() = default;
	Double(double a);
	void input() override;
	void print() override;
	Number *Clone() override;
	double ValueAsDbl() override;
};

class Bool : public Number
{
public:
	bool body;
	
	Bool() = default;
	Bool(bool a);
	void input() override;
	void print() override;
	Number *Clone() override;
	double ValueAsDbl() override;
};

#include "Number.cpp"
