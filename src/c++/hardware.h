#pragma once
using namespace std;
#include<iostream>
#include<map>

//Instruction class declaration
class Instruction {
//data memebers of the class
protected:
	string inst;
	string argument;
//methods of the class
public:
	//virtual execute method
	virtual void execute() = 0;
	//print method
	void print();
	//getting instruction
	string getinst() {
		return inst;
	}
	//getting argument
	string getargument() {
		return argument;
	}
};

//Hardware class
class Hardware {
//data members of the class
protected:
	static Instruction** instlist;
	static int valuelist[128];
	static int instptr;
	static int valueptr;
	static int a;
	static int b;
	static map<string, int> symbolmap;
	static int zbit;
	static int obit;
	static int pc;
//methods of the class
public:
	static Instruction* getinstindex(int index);
	static int getvalueindex(int index);
	static void setinst(Instruction* inst);
	static void setvalue(int value);
	static void setinstwithkey(int key, Instruction* value);
	static void setvaluewithkey(int key, int value);
	static int getinstptr();
	static int getvalueptr();
	static Instruction** getinstlist();
	static int* getvaluelist();
	static void valueptrinc();
	static void Aset(long long int value);
	static long long int Aget();
	static void Bset(long long int value);
	static long long int Bget();
	static void Sset(string key, int value);
	static int Sget(string key);
	static void printsymbol();
	static void Zset(int value);
	static int Zget();
	static void Oset(int value);
	static int Oget();
	static void Pset();
	static int Pget();
	static void Psetval(int value);
	static void printMemory();
	static void trashCleanUp();
	static void output();

};
//DEC class
class DEC : public Instruction{
public:
	//default constructor
	DEC() {
		inst = "DEC";
		/*argument = 0;*/
	}
	//normal constructor
	DEC(string argtype) {
		inst = "DEC";
		argument = argtype;
	}
	//execute method
	void execute(); 
	//print method
	void print() {
		cout << "hello" << endl;
	}
};
//LDI class
class LDI : public Instruction {
public:
	//Default constructor
	LDI() {
		inst = "LDI";
	}
	//normal constructor
	LDI(string argtype) {
		inst = "LDI";
		argument = argtype;
	}
	void execute(); 
};
//XCH class
class XCH : public Instruction {
public:
	//default constructor
	XCH() {
		inst = "XCH";
		
	}
	
	void execute(); 
};
//ADD class
class ADD : public Instruction {
public:
	//Default constructor
	ADD() {
		inst = "ADD";
		
	}
	
	void execute();
};
//STR class
class STR : public Instruction {
public:
	//Default constructor
	STR() {
		inst = "STR";
	
	}
	//constructor with argument
	STR(string argtype) {
		inst = "STR";
		argument = argtype;
	}
	void execute(); 
};
//JMP class
class JMP : public Instruction {
public:
	//Default constructor
	JMP() {
		inst = "JMP";
	
	}
	//constructor with argument
	JMP(string argtype) {
		inst = "JMP";
		argument = argtype;
	}
	void execute(); 
};
//JZS class
class JZS : public Instruction {
public:
	//Default constructor
	JZS() {
		inst = "JZS";
		
	}
	//construction with arguments
	JZS(string argtype) {
		inst = "JZS";
		argument = argtype;
	}
	void execute(); 
};
//JVS class
class JVS : public Instruction {
public:
	//Default constructor
	JVS() {
		inst = "JVS";
		
	}
	//constructor with argument
	JVS(string argtype) {
		inst = "JVS";
		argument = argtype;
	}
	void execute(); 
};
//LDA class
class LDA : public Instruction {
public:
	//Default constructor
	LDA() {
		inst = "LDA";
	
	}
	//construction with argument
	LDA(string argtype) {
		inst = "LDA";
		argument = argtype;
	}
	void execute(); 
};
//LDA class
class LDB : public Instruction {
public:
	//Default constructor
	LDB() {
		inst = "LDB";
		
	}
	//constructor with argument
	LDB(string argtype) {
		inst = "LDB";
		argument = argtype;
	}
	void execute(); 
};
//HLT class
class HLT : public Instruction {
public:
	//Default constructor
	HLT() {
		inst = "HLT";
	}
	void execute();
};