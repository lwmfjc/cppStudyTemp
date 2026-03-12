#ifdef LY_EP100

#include <iostream>  
#include <map>
#include <unordered_map>
#include <string>

struct CityRecord
{
	std::string Name;
	uint64_t Population;
	double Latitude, Longitude;

};

 std::ostream& operator<<(std::ostream& stream,
	const CityRecord& cityRecord)
{ 
	std::cout << "Name: " << cityRecord.Name << ","
		<< "Population: " << cityRecord.Population << ","
		<< "Latitude: " << cityRecord.Latitude << ","
		<< "Longitude: " << cityRecord.Longitude << std::endl;
	return stream;
}

namespace std {

	template<>
	struct hash<CityRecord>
	{
		size_t operator()(const CityRecord& key)
		{
			//hash<std::string>()这是调用构造函数，
			//然后构造了std::hash<CityRecord> 类型的对象，
			//之后调用了该对象的()重载方法
			return hash<std::string>()(key.Name);
		}
	};
}
int main()
{

	//计算City
	CityRecord cityRecord = { "name1",10000,2.3,4.5 };
	auto hashcode=std::hash<CityRecord>()(cityRecord);
	if (hashcode)
	{
		std::cout << "hashcode: " << hashcode << std::endl;
		std::cout << cityRecord << std::endl;
	}
	std::cin.get();
	return 0;
}

#endif