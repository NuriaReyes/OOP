#include <iostream>
#include <string>

class Animal
{
private:
	std::string mName;
	int mAge;
	std::string *mFavFood;
	int mFoodIndex;
	int mFoodTotal;

public:
	Animal(const std::string &name, int age, int foodTotal) : //initializer list:
		mName(name),
		mAge(age),
		mFoodIndex(0),
		mFoodTotal(foodTotal)
	{
		mFavFood = new std::string[foodTotal]; //dynamically allocated
	}

	~Animal()
	{
		delete[] mFavFood; //returning to OS allocated memory
	}

	std::string getName() { return mName; }
	void setName(std::string name) { mName = name; }

	int getAge() { return mAge; }
	void setAge(int age) { mAge = age; }

	void addFavFood(const std::string &food);
};

void Animal::addFavFood(const std::string &food)
{
	if (mFoodIndex < mFoodTotal)
	{
		mFavFood[mFoodIndex] = food;
		++mFoodIndex;

		std::cout << mName << " likes to eat " << food << "! \n";
	}
	else
	{
		std::cout << mName << " does not want to eat " << food << "! \n";
	}
}

int main()
{
	Animal cat("Tom", 2, 3); //instance of Animal

	std::cout << "Animal name: " << cat.getName() << "\n";
	std::cout << "Animal age: " << cat.getAge() << "\n";

	cat.addFavFood("Tuna");
	cat.addFavFood("Ham");
	cat.addFavFood("Whiskas");
	cat.addFavFood("rat in my house");

	system("PAUSE");
	return 0;
}