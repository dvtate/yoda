#ifndef USER_VARIABLES_H
#define USER_VARIABLES_H

#include <stdlib.h>
#include <string.h>

#include "calc_value.h"

// variable names longer than 20chars will be called by their first 19 chars




// the node for my linked list of user defined variables
class UserVar {
public:

	char name[USERVAR_NAME_MAXLENGHT]; // USERVAR_NAME_MAXLENGHT defined in calc_value.h

	CalcValue val;

	UserVar *first, *next;

	UserVar(UserVar* firstn, const char* const identifier, double contents):
		val(contents), first(firstn), next((UserVar*) NULL)
	{
	  	strncpy(name, identifier, USERVAR_NAME_MAXLENGHT - 1);
	  	val.type = CalcValue::NUM;
	}

	UserVar(UserVar* firstn, const char* const identifier, const char* const contents):
		val(contents), first(firstn), next((UserVar*) NULL)
	{
	  	strncpy(name, identifier, USERVAR_NAME_MAXLENGHT - 1);
	  	val.type = CalcValue::NUM;
	}

	UserVar(UserVar* firstn, const char* const identifier, CalcValue contents):
		first(firstn), next((UserVar*) NULL)
  	{

	  	strncpy(name, identifier, USERVAR_NAME_MAXLENGHT);

	  	if (contents.type == CalcValue::NUM) {
			val.type = CalcValue::NUM;
		  	val.number = contents.number;
		} else {
			val.type = CalcValue::STR;
	  	  	val.string = (char*) malloc(strlen(contents.string) + 1);
		  	strcpy(val.string, contents.string);
		}
	}


	// geting the values
	double getNumber()
		{ return val.getNum(); }

	char* getString()
		{ return val.getStr(); }

	// recursive method of accessing Values of CalcValue::REF type
	CalcValue getValue(){

		if (val.type == CalcValue::REF) {
			CalcValue* value = val.valAtRef(first);

			while (value != NULL && value->type == CalcValue::REF)
				value = value->valAtRef(first);

			// broken reference (should I tell them???)
			return value ? *value : NULL_CALCVAL_OBJECT;

		}

		return val;

	}

	// recursive method of accessing Values of CalcValue::REF type
	CalcValue* getValPtr(){

		if (val.type == CalcValue::REF) {
			CalcValue* value = val.valAtRef(first);

			while (value != NULL && value->type == CalcValue::REF)
				value = value->valAtRef(first);

			return value;
		}

		return &val;

	}

	CalcValue& getVal()
		{ return val; }


	// changing the values
	void setValue(double in){
		val.setValue(in);
	}

	void setValue(const char* in){

	  	CalcValue* value = getValPtr();
		value->setValue(in);

	}

	void setValue(UserVar* in)
		{ val = CalcValue().setRef(in->name); }

	void setValue(CalcValue in)
		{ val.setValue(in); }


};




namespace vars {
	
	extern UserVar* first_node;

  	// the last element on the linked list
  	extern UserVar* lastVar(UserVar* first);

	// to be called after reset
	extern void wipeAll(UserVar*& first);

	// to make a  new variable, or change it's value
	//extern void assignVar(UserVar* first, char name[USERVAR_NAME_MAXLENGHT], double value);
	extern void assignVar(UserVar* first, char name[USERVAR_NAME_MAXLENGHT], CalcValue value);

	// to remove an individial variable
	extern void removeVar(UserVar* first, char name[USERVAR_NAME_MAXLENGHT]);

	// returns a pointer to the variable
	extern UserVar* findVar(UserVar* first, char name[USERVAR_NAME_MAXLENGHT]);

	extern bool varExists(UserVar* first, char name[USERVAR_NAME_MAXLENGHT]);

	extern CalcValue* valueAtVar(UserVar* first, char name[USERVAR_NAME_MAXLENGHT]);
}



#endif