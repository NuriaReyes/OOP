#include <iostream>
#include <string>

class Animal
{
private:
	std::string mName;
	int mAge;

public:
	std::string getName() { return mName; }
	void setName(std::string name) { mName = name; }

	int getAge() { return mAge; }
	void setAge(int age) { mAge = age; }
};

int main()
{
	Animal cat; //instance of Animal

	cat.setName("Mike");
	cat.setAge(2);

	std::cout << "Animal name: " << cat.getName() << "\n";
	std::cout << "Animal age: " << cat.getAge() << "\n";

	system("PAUSE");
	return 0;
}