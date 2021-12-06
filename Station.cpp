// Name: Khushwant Singh Rao
// Seneca Student ID: 145931192
// Seneca email: ksrao1@myseneca.ca
// Date of completion: Dec 2, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<iostream>
#include<iomanip>
#include "Station.h"
#include "Utilities.h"
namespace sdds
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;
	Station::Station(const std::string str)
	{
		id_generator++;
		m_id = id_generator;
		Utilities obj;
		bool more;
		size_t pos = 0;
		m_item = obj.extractToken(str, pos, more);
		if(more)
			m_serialNo = stoi(obj.extractToken(str, pos, more));
		if (more)
			m_noOfItems = stoi(obj.extractToken(str, pos, more));
		if (Station::m_widthField < obj.getFieldWidth())
			Station::m_widthField = obj.getFieldWidth();
		if (more)
			m_description = obj.extractToken(str, pos, more);
	}
	const std::string& Station::getItemName() const
	{
		return m_item;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_serialNo++;
	}
	size_t Station::getQuantity() const
	{
		return m_noOfItems;
	}
	void Station::updateQuantity()
	{
		if (m_noOfItems >= 0)
		{
			m_noOfItems--;
		}
	}
	void Station::display(std::ostream& os, bool full) const
	{
		if (full)
		{
			os << "[";
			os << std::setw(3) << std::setfill('0')<<std::right << m_id;
			os << "] Item: ";
			os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_item << " [";
			os << std::setw(6) << std::right << std::setfill('0') << m_serialNo;
			os << "] Quantity: "<< std::setw(m_widthField)<< std::setfill(' ') << std::left << m_noOfItems;
			os << " Description: " << m_description << "\n";
		}
		else
		{
			os << "[" << std::setw(3) << std::setfill('0') << m_id;
			os << "] Item: " << std::left << std::setfill(' ') << std::setw(m_widthField) << m_item << " [";
			os << std::setw(6) << std::right << std::setfill('0') << m_serialNo << "]\n";
		}
	}
}
