#ifndef YODA_USER_TYPE_HPP
#define YODA_USER_TYPE_HPP

#include <vector>
#include <algorithm> // find()
#include <string>



class CalcValue;

class UserType {
public:

	// what a wonderful place I could have used an assiciative array...
	// ... if only I wasn't so lazy
	std::vector<std::string> members; // I have given up on performance.. :(
	std::vector<CalcValue>   values;

	UserType(){};

	UserType(const UserType& in){
		members = in.members;
		values = in.values;
	}


	// attempts to add a member, if already there, then change value
	UserType& addMember(std::string nMem, CalcValue nVal);
	UserType& addMember(std::vector<std::string> loc, const CalcValue nVal);

	bool hasMember(const std::string name) {
		return find(members.begin(), members.end(), name) != members.end();
	}

	// TODO: add removeMember()

	CalcValue* getMember(const std::string query);

	bool operator==(const UserType& vs);
	bool operator!=(const UserType& vs)
		{ return !operator==(vs); }

	UserType& operator=(const UserType& in) {
		members = in.members;
		values = in.values;
		return *this;
	}



};








#endif //YODA_USER_TYPE_HPP
