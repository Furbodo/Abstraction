// Justin Balogh

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

class emp // base class
{
private:

public:
	// Constructors
	emp() 
	{
		this->EmpName = '\0';
		this->EmpSSN = 0;
	}
	
	emp(string EmpName, long EmpSSN) 
	{
		this->EmpName = EmpName;
		this->EmpSSN = EmpSSN;
	}
	// Copy Constructor
	emp(const emp &emp) 
	{
		EmpName = emp.EmpName;
		EmpSSN = emp.EmpSSN;
	}
	// Getters
	string getEmpName()
	{
		return EmpName;
	}

	long getEmpSSN() 
	{
		return EmpSSN;
	}
	// Display output
	void display() 
	{
		cout << "Name: " << getEmpName() << " SSN: " << getEmpSSN() << endl;
	}

	~emp() 
	{
		
	}

protected:

	string EmpName;
	long EmpSSN;
};

class hourly_emp : public emp // hourly subclass
{
private:

	float EmpRate;
	int EmpHours;

public:
	// Constructors
	hourly_emp() : emp()
	{
		this->EmpRate = 0;
		this->EmpHours = 0;
	}

	hourly_emp(string name, long SSN, float EmpRate, int EmpHours) : emp(name, SSN)
	{
		this->EmpRate = EmpRate;
		this->EmpHours = EmpHours;
	}

	hourly_emp(const hourly_emp &hourly_emp) : emp(hourly_emp)
	{
		this->EmpRate = hourly_emp.EmpRate;
		this->EmpHours = hourly_emp.EmpHours;
	}
	// Getters
	float getPay()
	{
		return EmpRate * (float)EmpHours;
	}

	float getEmpRate()
	{
		return EmpRate;
	}

	int getEmpHours() 
	{
		return EmpHours;
	}
	// Display output
	void display() 
	{
		cout << "Name: " << getEmpName() << " SSN: " << getEmpSSN() << " Pay: " << getPay() << endl;
	}

	~hourly_emp()
	{

	}
protected:
	
};

class salaried_emp : public emp // salary subclass
{
private:

	float EmpSalary;

public:

	salaried_emp() : emp()
	{
		this->EmpSalary = 0;
	}

	salaried_emp(string name, long SSN, float EmpSalary) : emp(name, SSN) 
	{
		this->EmpSalary = EmpSalary;
	}

	salaried_emp(const salaried_emp &salaried_emp) : emp(salaried_emp) 
	{
		this->EmpSalary = salaried_emp.EmpSalary;
	}

	float getEmpSalary() 
	{
		return EmpSalary;
	}

	void display() 
	{
		cout << "Name: " << getEmpName() << " SSN: " << getEmpSSN() << " Pay: " << (EmpSalary / 52) << endl;
	}

	~salaried_emp()
	{

	}

protected:
	
};
// Prototypes
void input(string &name, long &ssn, float &rate, int &hours);
void input(string &name, long &ssn, float &salary);
void input(string &name, long &ssn);
void buildEmp(hourly_emp hourly[], salaried_emp salaried[], emp unclassified[], int &hourlyIndex, int &salariedIndex, int &unclassIndex);
void displayEmployees(hourly_emp hourly[], salaried_emp salaried[], emp unclassified[], int hourlyIndex, int salariedIndex, int unclassIndex);

int main()
{	// Object Arrays
	hourly_emp hourly[5];
	salaried_emp salaried[5];
	emp unclassified[5];

	// Array Indicies
	int hourlyIndex = 0, 
		salariedIndex = 0, 
		unclassIndex = 0;
	
	// Flag and Menu Loop
	int continueFlag = 0;
	while (continueFlag == 0)
	{		
		int menu = 0;
		// Input Hold Vars
		string name;
		long ssn = 0;
		float salary = 0;
		float rate = 0;
		int hours = 0;
		char classification = '\0';

		cout << "1. Create employee" << endl;
		cout << "2. Display employees" << endl;
		cout << "3. Quit" << endl;
		cin >> menu; cout << endl;

		switch (menu)
		{
		case 1: // creates and assigns employees to classifications and arrays
			buildEmp(hourly, salaried, unclassified, hourlyIndex, salariedIndex, unclassIndex);
			break;
		case 2: // Outputs and prints all the arrays of objects
			displayEmployees(hourly, salaried, unclassified, hourlyIndex, salariedIndex, unclassIndex);
			break;
		case 3: default: // Quit 
			continueFlag = 1;
			break;
		}
	}
}

void input(string &name, long &ssn, float &rate, int &hours) // hourly input
{
	cout << "What is the name of the person?" << endl;
	cin >> name; cout << endl;

	cout << "What is the SSN of the person?" << endl;
	cin >> ssn; cout << endl;

	cout << "What is the rate of pay for the person?" << endl;
	cin >> rate; cout << endl;

	cout << "What hours were worked for the person?" << endl;
	cin >> hours; cout << endl;
}

void input(string &name, long &ssn, float &salary) // salary input
{
	cout << "What is the name of the person?" << endl;
	cin >> name; cout << endl;

	cout << "What is the SSN of the person?" << endl;
	cin >> ssn; cout << endl;

	cout << "What is the salary of the person?" << endl;
	cin >> salary; cout << endl;
}

void input(string &name, long &ssn) // unclassified input
{
	cout << "What is the name of the person?" << endl;
	cin >> name; cout << endl;

	cout << "What is the SSN of the person?" << endl;
	cin >> ssn; cout << endl;
}

void buildEmp(hourly_emp hourly[], salaried_emp salaried[], emp unclassified[], int &hourlyIndex, int &salariedIndex, int &unclassIndex)
{
	// Input var initializations
	string name;
	long ssn = 0;
	float salary = 0;
	float rate = 0;
	int hours = 0;
	char classification = '\0';
	// Error validation
	while (classification != 'h' && classification != 's' && classification != 'u')
	{
		cout << "What kind of employee? Hourly = h, Salary = s, Unclassified = u" << endl;
		cin >> classification;
	}

	classification = tolower(classification);

	if (classification == 'h') // takes input and uses a constructor with inputs, does so for all three cases. then ticks up indicies used
	{
		input(name, ssn, rate, hours);
		hourly_emp* EMP = new hourly_emp(name, ssn, rate, hours);
		hourly[hourlyIndex] = *EMP;
		hourlyIndex++;
	}

	if (classification == 's') 
	{
		input(name, ssn, salary);
		salaried_emp emp(name, ssn, salary);
		salaried[salariedIndex] = emp;
		//salaried_emp* EMP = new salaried_emp(name, ssn, salary);
		//salaried[salariedIndex] = *EMP;
		salariedIndex++;
	}

	if (classification == 'u') 
	{
		input(name, ssn);
		emp* EMP = new emp(name, ssn);
		unclassified[unclassIndex] = *EMP;
		unclassIndex++;
	}
}

void displayEmployees(hourly_emp hourly[], salaried_emp salaried[], emp unclassified[], int hourlyIndex, int salariedIndex, int unclassIndex) // prints out employee arrays
{
	if (hourlyIndex > 0) // checks if the array contain anything before attempting to print anything out of them, then uses For loops to cycle through elements
	{
		cout << "--------Hourly-----------" << endl;
		for (int i = 0; i < (hourlyIndex); i++)
		{
			hourly[i].display();
		}
	}

	if (salariedIndex > 0)
	{
		cout << "--------Salary-----------" << endl;
		for (int i = 0; i < (salariedIndex); i++)
		{
			salaried[i].display();
		}
	}

	if (unclassIndex > 0) 
	{
		cout << "----Unclassified---------" << endl;
		for (int i = 0; i < (unclassIndex); i++)
		{
			unclassified[i].display();
		}
	}
}
