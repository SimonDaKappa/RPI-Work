class Time {
public:
	// Constructors
	Time();
	Time(int aHour, int aMinute, int aSecond);
	Time(const Time& aTime);

	// Accesors
	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	// Modifiers
	void setHour(int aHour);
	void setMinute(int aMinute);
	void setSecond(int aSecond);
	//void increment();

	// Member Functions
	bool isEqual(const Time& time2) const; //Same Hour/Minute/Second
	void print() const;
	void PrintAMPM() const;



private: //Member Variables
	int hour, minute, second;

};

bool IsEarlierThan(const Time& time1, const Time& tim2);