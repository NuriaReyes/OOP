#include <iostream>
#include <string>

typedef enum
{
	SLEEP,
	EAT,
	MEOW,
	ATTACK,
	NO_INTEREST,

	CAT_PLANS_COUNT
} t_catPlans;

class Animal
{
private:
	std::string mName;
	int mAge;

protected:
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

class Cat : public Animal
{
private:
	int livesLeft;
	t_catPlans mPlans;

	void printPlans() 
	{
		switch (mPlans)
		{
			case SLEEP:
				std::cout << getName() << " is sleeping \n";
				break;
			case EAT:
				std::cout << getName() << " is eating \n";
				break;
			case MEOW:
				std::cout << getName() << " is meowing \n";
				break;
			case ATTACK:
				std::cout << getName() << " is attacking \n";
				std::cout << getName() << " has lost a life, remaining: " << livesLeft << "\n";
				break;
			case NO_INTEREST:
				std::cout << getName() << " is not interested \n";
				break;
			default:
				std::cout << getName() << " is sleeping \n";
		}
	}

public:
	Cat(const std::string &name, int age, int foodTotal) :
		Animal(name, age, foodTotal),
		livesLeft(7),
		mPlans(SLEEP)
	{
	}

	void requestFood(bool giveFood)
	{
		mPlans = MEOW;
		printPlans();
		
		if (giveFood)
		{
			mPlans = EAT;
		}
		else
		{
			mPlans = MEOW;
		}
		printPlans();
	}

	void react(bool humanApproaching, bool isOwner)
	{
		if (humanApproaching)
		{
			if (isOwner)
			{
				mPlans = NO_INTEREST;
			}
			else
			{
				mPlans = ATTACK;
				--livesLeft;
			}
		}
		else
		{
			mPlans = SLEEP;
		}

		printPlans();
	}
};

int main()
{
	Cat cat("Tom", 2, 3); //instance of Animal

	std::cout << "Animal name: " << cat.getName() << "\n";
	std::cout << "Animal age: " << cat.getAge() << "\n";

	cat.addFavFood("Tuna");
	cat.addFavFood("Ham");
	cat.addFavFood("Whiskas");
	cat.addFavFood("rat in my house");

	cat.requestFood(true);
	cat.react(true, false);

	system("PAUSE");
	return 0;
}