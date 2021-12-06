// Name: Khushwant Singh Rao
// Seneca Student ID: 145931192
// Seneca email: ksrao1@myseneca.ca
// Date of completion: Dec 2, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include<string>
namespace sdds
{
	class Station
	{
		size_t m_id;
		std::string m_item;
		std::string m_description;
		size_t m_serialNo;
		size_t m_noOfItems;
		static size_t m_widthField;
		static size_t id_generator;

	public:
		Station(const std::string str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};

}
#endif // !SDDS_STATION_H