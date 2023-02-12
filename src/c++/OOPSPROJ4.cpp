#pragma once
using namespace std;
#include<iostream>
#include <string>
#include <cstring> 
#include <sstream>
#include <fstream>
#include "hardware.h"


int Hardware::instptr = 0;
int Hardware::valueptr = 0;
Instruction** Hardware::instlist = new Instruction * [128];
int Hardware::valuelist[128];
int Hardware::zbit = 0;
int Hardware::obit = 0;
int Hardware::pc = 0;
int Hardware::a = 0;
int Hardware::b = 0;
map<string, int> Hardware::symbolmap;

//printing the instruction
	void Hardware::printMemory() {
		//looping through the entire list and printing the instructions
		for (int i = 0; i <instptr;i++) {
			if (instlist[i] != NULL){
				cout << instlist[i] << endl;
			}
		}
	}

	//deallocating memory
	void Hardware::trashCleanUp() {
		for (int i = 0; i < instptr;i++) {
			if (instlist[i] != NULL) {
				delete instlist[i];
			}
		}
		delete[] instlist;
	}
	//getting the instruction present in particular index of the arry
	Instruction* Hardware::getinstindex(int index) {
		return instlist[index];
	}
	//getting tge value present in particular index of the array
	int Hardware::getvalueindex(int index) {
		return valuelist[index];
	}
	//setting the instruction into the instruction list
	void Hardware::setinst(Instruction* inst) {
		instlist[instptr] = inst;
		instptr += 1;
	}
	//setting the value in value list
	void Hardware::setvalue(int value) {
		valuelist[valueptr] = value;
	}
	//setting the instruction in particular index
	void Hardware::setinstwithkey(int key, Instruction* value) {
		instlist[key] = value;
	}
	//setting the value in particular index
	void Hardware::setvaluewithkey(int key, int value) {
		valuelist[key] = value;
	}
	//returning the instruction pointer
	int Hardware::getinstptr() {
		return instptr;
	}
	//returning the value pointer
	int Hardware::getvalueptr() {
		return valueptr;
	}
	//returning the entire instructionlist
	Instruction** Hardware::getinstlist() {
		return instlist;
	}
	//returning the entire value list
	int* Hardware::getvaluelist() {
		return valuelist;
	}
	//incrementing the value pointer
	void Hardware::valueptrinc() {
		valueptr += 1;
	}
	//setting the value into Aregister
	void Hardware::Aset(long long int value) {
		a = value;
	}
	//returning the value from A register
	long long int Hardware::Aget() {
		return a;
	}
	//setting the value into Bregister
	void Hardware::Bset(long long int value) {
		b = value;
	}
	//returning the value from B register
	long long int Hardware::Bget() {
		return b;
	}
	//setting the value into symbol dictionary
	void Hardware::Sset(string key, int value) {
		symbolmap[key] = value;
	}
	//returning the value of specific key from symbol dictionary
	int Hardware::Sget(string key) {
		return symbolmap[key];
	
	}
	//printing the entire symbol dictionary
	void Hardware::printsymbol() {
		map <string, int> ::iterator iter;
		cout << "keys" << "  &  " << "values" << endl;
		for (iter = symbolmap.begin(); iter != symbolmap.end(); iter++)
		{
			cout << (*iter).first << "    " << Hardware::getvalueindex((*iter).second) << "\n";
		}
	}
	//setting the z bit value
	void Hardware::Zset(int value) {
		zbit = value;
	}
	//returning the z bit value
	int Hardware::Zget() {
		return zbit;
	}
	//setting the o bit value
	void Hardware::Oset(int value) {
		obit = value;
	}
	//getting the o bit value
	int Hardware::Oget() {
		return obit;
	}
	//setting the p bit value
	void Hardware::Pset() {
		pc += 1;
	}
	//getting the p bit value
	int Hardware::Pget() {
		return pc;
	}
	//setting the p bit with particular value
	void Hardware::Psetval(int value) {
		pc = value;
	}

	void Hardware::output() {
		cout << "Zero bit : " << Hardware::Zget() << endl;
		cout << "Overflow bit : " << Hardware::Oget() << endl;
		cout << "Register A : " << Hardware::Aget() << endl;
		cout << "Register B : " << Hardware::Bget() << endl;
		cout << "Symbol Dictionary: " << endl;
		Hardware::printsymbol();
	}

	//DEC execute method for getting the instruction and value and storing it in symbol table
	void DEC::execute() {
		int value = Hardware::getvalueptr();
		Hardware::Sset(argument, value);
		Hardware::setvalue(0);
		Hardware::valueptrinc();
	}

	//LDI execute method for converting the argument to integer and storing in A register
	void LDI::execute() {
		Hardware::Aset(stoi(argument));
	}
	//XCH execute method for switching the values between A and B register
	void XCH::execute() {
		int temp = Hardware::Aget();
		Hardware::Aset(Hardware::Bget());
		Hardware::Bset(temp);
	}
	//ADD method for adding the values of A and B register and storing it in A register. setting the overflow bit if the
	//result is out of range whiel zero bit if the result is 0
	void ADD::execute() {
		long long int totalsum = Hardware::Aget() + Hardware::Bget();
		//if total sum is 0
			if (totalsum == 0) {
				Hardware::Zset(1);
			}
			//if total sum is greater than 2147483648
			if (totalsum > 2147483647) {
				Hardware::Aset(totalsum - 2147483647);
				Hardware::Oset(1);
			}
			//if total sum is less than -2147483647
			else if (totalsum < -2147483648) {
				Hardware::Aset(2147483648 + totalsum);
				Hardware::Oset(1);
			}
			else {
				Hardware::Aset(totalsum);
			}

	}
	//STR execute method for getting the value from symbol table and setting it in value array
	void STR::execute() {
		Hardware::setvaluewithkey(Hardware::Sget(argument), Hardware::Aget());
	}
	//jumping to the program counter to the particular index
	void JMP::execute() {
		Hardware::Psetval(stoi(argument));
	}
	//setting the program counter to partigular value if the instruction is JZS and zero bit is set to 1
	void JZS::execute() {
		if (Hardware::Zget() == 1) {
			Hardware::Psetval(stoi(argument));
		}
	}
	//JVS execute for setting program counter to the particular value if the overflow bit is set to 1
	void JVS::execute() {
		if (Hardware::Oget() == 1) {
			Hardware::Psetval(stoi(argument));
		}
	}
	//LDA execute for setting the value to A register by getting it from symbol table
	void LDA::execute() {
		int value = Hardware::Sget(argument);
		long long valuea = Hardware::getvalueindex(value);
		Hardware::Aset(valuea);
	}
	//LDB execute for setting the value to B register by getting it from symbol table
	void LDB::execute() {
		int value = Hardware::Sget(argument);
		long long valueb = Hardware::getvalueindex(value);
		Hardware::Bset(valueb);
	}
	//HLT execute
	void HLT::execute() {

	}
	//print instructions
	void Instruction::print() {
	
		cout << getinst()<<" " << getargument() << endl;
	}

	static int linesize = 0;
//main 
int main() {
	//declaring and taking input file
	string inputfile;
	cout << "Enter filename: " << endl;
	cin >> inputfile;
	ifstream newfile;
	//opening the file
	Hardware::printMemory();
	newfile.open(inputfile, ios::in); 
	if (newfile.is_open()) { 
		string tp;
		string* result = new string[3];
		//iterating the file line wise
		while (getline(newfile, tp)) { 
			istringstream iss(tp);
			string word;
			int i = 0;
			//taking every word of the line
			while (iss >> word) {
				//storing the words in the array
				result[i] = word.c_str();
				i += 1;
				if (i == 2) {
					break;
				}
			}
			//if the instruction is HLT, creating the object and setting that into the instruction table
			if (result[0] == "HLT") {
				Instruction* h = new HLT();
				Hardware::setinst(h);
			}
			//if the instruction is DEC, creating the object and setting that into the instruction table
			else if (result[0] == "DEC") {
				Instruction* d = new DEC(result[1]);
				Hardware::setinst(d);
			}
			//if the instruction is LDI, creating the object and setting that into the instruction table
			else if (result[0] == "LDI") {
				Instruction* l = new LDI(result[1]);
				Hardware::setinst(l);
			}
			//if the instruction is XCH, creating the object and setting that into the instruction table
			else if (result[0] == "XCH") {
				Instruction* x = new XCH();
				Hardware::setinst(x);
			}
			//if the instruction is ADD, creating the object and setting that into the instruction table
			else if (result[0] == "ADD") {
				Instruction* a = new ADD();
				Hardware::setinst(a);
			}
			//if the instruction is STR, creating the object and setting that into the instruction table
			else if (result[0] == "STR") {
				Instruction* s = new STR(result[1]);
				Hardware::setinst(s);
				
			}
			//if the instruction is JMP, creating the object and setting that into the instruction table
			else if (result[0] == "JMP") {
				Instruction* j = new JMP(result[1]);
				Hardware::setinst(j);
			
			}
			//if the instruction is JZS, creating the object and setting that into the instruction table
			else if (result[0] == "JZS") {
				Instruction* jz = new JZS(result[1]);
				Hardware::setinst(jz);
				
			}
			//if the instruction is JVS, creating the object and setting that into the instruction table
			else if (result[0] == "JVS") {
				Instruction* jv = new JVS(result[1]);
				Hardware::setinst(jv);
			
			}
			//if the instruction is LDA, creating the object and setting that into the instruction table
			else if (result[0] == "LDA") {
				Instruction* la = new LDA(result[1]);
				Hardware::setinst(la);
		
			}
			//if the instruction is LDB, creating the object and setting that into the instruction table
			else if (result[0] == "LDB") {
				Instruction* lb = new LDB(result[1]);
				Hardware::setinst(lb);

			}
			linesize += 1;
		}
		//deleting the result
		delete[] result;
		newfile.close(); 
		static int temp = 0;
		bool f = true;
		
		while (f) {
			//getting the input command from the user
			cout << "Enter command: " << endl;
			cout <<"-------------------------------------"<< endl;
			cout << "s : For executing single line " << endl;
			cout << "a : For executing the entire file" << endl;
			cout << "q : For quitting" << endl;
			cout << "------------------------------------"<< endl;
			char inputflow;
			cin >> inputflow;
			switch (inputflow) {
				//if the command is s 
			case 's': {
				//getting the instruction
				Instruction* o = Hardware::getinstindex(Hardware::Pget());
				//if the instruction is HLT
				if (o->getinst() == "HLT") {
					f = false;
					break;
				}
				//if the instruction is JMP or JZS or JVS
				if (o->getinst() == "JMP" || o->getinst() == "JZS" || o->getinst() == "JVS") {
					//setting the program counter with particular value
					if ((Hardware::Zget() == 1 && o->getinst() == "JZS") || (Hardware::Oget() == 1 && o->getinst() == "JVS") || (o->getinst() == "JMP")) {
						Hardware::Psetval(stoi(o->getargument()));
					}
					else {
						//setting the program counter with default value
						Hardware::Pset();
					}
				}
				else {
					//executing the instrution
					o->execute();
					Hardware::Pset();
				}
				//printing the table
				if (Hardware::Pget() >= linesize) {
					Hardware::output();
					f = false;
					break;
				}
				Hardware::output();
				cout << "Next Instruction: ";
				cout << Hardware::Pget() <<" ";
				Hardware::getinstindex(Hardware::Pget())->print();				//if all instructions are executed then hlt the program
				
				break;
			}
			//if the command is q, break the program
			case 'q': {
				f = false;
				break;
			}
			//if the command is a, execute all the commands at a time and print the result
			case 'a': {
				while (Hardware::Pget() < linesize) {
					Instruction* o = Hardware::getinstindex(Hardware::Pget());
					if (o->getinst() == "HLT") {
						f = false;
						break;
					}
					if (o->getinst() == "JMP" || o->getinst() == "JZS" || o->getinst() == "JVS") {
						if ((Hardware::Zget() == 1 && o->getinst() == "JZS") || (Hardware::Oget() == 1 && o->getinst() == "JVS") || (o->getinst()) == "JMP") {
							Hardware::Psetval(stoi(o->getargument()));
						}
						else {
							Hardware::Pset();
						}
					}
					else {
						o->execute();
						Hardware::Pset();
					}
					temp += 1;
					//Hardware::getinstindex(Hardware::Pget())->print();
					//o->print();
				}
				f = false;
				Hardware::output();
				break;
			}
			}
			
		}
		cout << "all commands got executed" << endl;
	}
	else{
		cout << "Incorrect file name" << endl;
	}
	Hardware::trashCleanUp();
	
	
}
