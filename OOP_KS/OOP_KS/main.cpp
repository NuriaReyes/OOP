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

typedef enum
{
	PLAY,
	EAT_TRASH,
	EAT_DOGFOOD,
	BARK,
	CHASE_TAIL,
	WIGGLE_TAIL,

	DOG_PLANS_COUNT
} t_dogPlans;

class Animal
{
private:
	std::string mName;
	int mAge;
	static int mAnimalCounter;

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
		++mAnimalCounter;
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

	virtual void printPlans() = 0;
	virtual void requestFood(bool giveFood) = 0;
	virtual void react(bool humanApproaching, bool isOwner) = 0;

	static int getAnimalsInstantiated() { return mAnimalCounter; }
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

public:
	Cat(const std::string &name, int age, int foodTotal) :
		Animal(name, age, foodTotal),
		livesLeft(7),
		mPlans(SLEEP)
	{
	}

	virtual void printPlans()
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
			std::cout << getName() << " has lost a life, remaining: " << --livesLeft << "\n";
			break;
		case NO_INTEREST:
			std::cout << getName() << " is not interested \n";
			break;
		default:
			std::cout << getName() << " is sleeping \n";
		}
	}

	virtual void requestFood(bool giveFood)
	{
		mPlans = MEOW;
		printPlans();
		
		if (giveFood)
		{
			std::cout << "Human is giving food... \n";
			mPlans = EAT;
		}
		else
		{
			std::cout << "Human refuses to feed... \n";
			mPlans = MEOW;
		}
		printPlans();
	}

	virtual void react(bool humanApproaching, bool isOwner)
	{
		if (humanApproaching)
		{
			if (isOwner)
			{
				std::cout << "Owner is approaching... \n";
				mPlans = NO_INTEREST;
			}
			else
			{
				std::cout << "Unknown human detected... \n";
				mPlans = ATTACK;
			}
		}
		else
		{
			mPlans = SLEEP;
		}

		printPlans();
	}
};

class Dog : public Animal
{
private:
	t_dogPlans mPlans;

public:
	Dog(const std::string &name, int age, int foodTotal) :
		Animal(name, age, foodTotal),
		mPlans(PLAY)
	{
	}

	virtual void printPlans()
	{
		switch (mPlans)
		{
		case PLAY:
			std::cout << getName() << " is playing \n";
			break;
		case EAT_TRASH:
			std::cout << getName() << " is eating trash \n";
			break;
		case EAT_DOGFOOD:
			std::cout << getName() << " is eating dog food \n";
			break;
		case BARK:
			std::cout << getName() << " is barking \n";
			break;
		case CHASE_TAIL:
			std::cout << getName() << " is chasing its own tail \n";
			break;
		case WIGGLE_TAIL:
			std::cout << getName() << " is wiggling its tail \n";
			break;
		default:
			std::cout << getName() << " is playing \n";
		}
	}

	virtual void requestFood(bool giveFood)
	{
		mPlans = BARK;
		printPlans();

		if (giveFood)
		{
			std::cout << "My human is the best!!! \n";
			mPlans = EAT_DOGFOOD;
		}
		else
		{
			std::cout << "My human does not have food, no problem... \n";
			mPlans = EAT_TRASH;
		}
		printPlans();
	}

	virtual void react(bool humanApproaching, bool isOwner)
	{
		if (humanApproaching)
		{
			if (isOwner)
			{
				std::cout << "OMG my human is home!!! \n";
				mPlans = WIGGLE_TAIL;
			}
			else
			{
				std::cout << "I do not know that human \n";
				mPlans = CHASE_TAIL;
			}
		}
		else
		{
			mPlans = PLAY;
		}

		printPlans();
	}
};

void simulateAnimal(Animal &animal, bool giveFood, bool humanApproaching, bool isOwner)
{
	std::cout << "Animal name: " << animal.getName() << "\n";
	std::cout << "Animal age: " << animal.getAge() << "\n";

	animal.requestFood(giveFood);
	animal.react(humanApproaching, isOwner);

	std::cout << "\n";
}

int Animal::mAnimalCounter(0); //Static members MUST be explicitly defined

int main()
{
	Cat cat("Tom", 2, 1);
	simulateAnimal(cat, true, true, false);

	Dog dog("Rufus", 1, 1);
	simulateAnimal(dog, false, true, true);

	Cat cat2("Misifus", 3, 1);
	simulateAnimal(cat2, false, true, true);

	std::cout << "Animals instantiated: " << Animal::getAnimalsInstantiated() << "\n";

	system("PAUSE");
	return 0;
}