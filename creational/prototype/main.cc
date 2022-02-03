#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
//! Record is the base Prototype for classes that may be `expensive` to create
class Record {
public:
	virtual ~Record() {}
	virtual unique_ptr<Record> clone() = 0;
	virtual void print() = 0;
	//! Opaque record type, avoids exposing concrete implementations
	enum Type { CAR = 0, BIKE, PERSON };
};
////////////////////////////////////////////////////////////////////////////////
//! Three Concrete Prototype Implementations
class CarRecord : public Record {
private:
	string m_carName;
	int m_ID;
public:
	CarRecord(string carName, int ID) : m_carName(carName), m_ID(ID) { }
	unique_ptr<Record> clone() override { return make_unique<CarRecord>(*this); }
	void print() override { cout << "Car Record" << endl
		<< "Name  : "   << m_carName << endl
		<< "Number: "   << m_ID << endl << endl;
	}
};
class BikeRecord : public Record {
private:
	string m_bikeName;
	int m_ID;
public:
	BikeRecord(string bikeName, int ID) : m_bikeName(bikeName), m_ID(ID) { }
	unique_ptr<Record> clone() override { return make_unique<BikeRecord>(*this); }
	void print() override { cout << "Bike Record" << endl
		<< "Name  : " << m_bikeName << endl
		<< "Number: " << m_ID << endl << endl;
	}
};
class PersonRecord : public Record {
public:
	string m_personName;
	int m_age;
public:
	PersonRecord(string personName, int age) 
        : m_personName(personName), m_age(age) { }
	unique_ptr<Record> clone() override {
		return make_unique<PersonRecord>(*this);
	}
	void print() override { cout << "Person Record" << endl
		<< "Name : " << m_personName << endl
		<< "Age  : " << m_age << endl << endl;
	}
};
////////////////////////////////////////////////////////////////////////////////
//! Client class to initially create the expensive objects
class RecordFactory {
private:
	unordered_map<Record::Type, unique_ptr<Record>, hash<int> > m_records;
public:
	RecordFactory() {
		m_records[Record::CAR]    = make_unique<CarRecord>("Ferrari", 5050);
		m_records[Record::BIKE]   = make_unique<BikeRecord>("Yamaha", 2525);
		m_records[Record::PERSON] = make_unique<PersonRecord>("Tom", 25);
	}

	unique_ptr<Record> createRecord(Record::Type recordType) {
		return m_records[recordType]->clone();
	}
};
////////////////////////////////////////////////////////////////////////////////
int main() {
	RecordFactory recordFactory;

	auto record = recordFactory.createRecord(Record::CAR);
	record->print();

	record = recordFactory.createRecord(Record::BIKE);
	record->print();

	record = recordFactory.createRecord(Record::PERSON);
	record->print();
}