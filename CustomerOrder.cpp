// Name: Khushwant Singh Rao
// Seneca Student ID: 145931192
// Seneca email: ksrao1@myseneca.ca
// Date of completion: Dec 2, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder(): m_name{},m_product{},m_cntItem{},m_lstItem{}
	{
	}
	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities local;
		bool more = true;
		size_t pos = 0;

		m_name = local.extractToken(str, pos, more);
		if (more)
			m_product = local.extractToken(str, pos, more);
		size_t itemPos = pos;
		while (more)
		{
			local.extractToken(str, pos, more);
			m_cntItem++;
		}
		delete[] m_lstItem;
		m_lstItem = new Item* [m_cntItem];
		for (auto i = 0u; i < m_cntItem; i++)
		{
			m_lstItem[i] = new Item (local.extractToken(str, itemPos, more));
		}

		if (CustomerOrder::m_widthField < local.getFieldWidth())
			CustomerOrder::m_widthField = local.getFieldWidth();
	}
	CustomerOrder::CustomerOrder(const CustomerOrder&)
	{
		throw "Cannot make copies.";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept
	{
		*this = std::move(order);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& order) noexcept
	{
		if (this != &order)
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
				m_lstItem[i] = nullptr;
			}
			
			delete[] m_lstItem;
			m_lstItem = nullptr;

			m_name = order.m_name;
			m_product = order.m_product;
			m_cntItem = order.m_cntItem;
			m_lstItem = order.m_lstItem;
			m_widthField = order.m_widthField;

			order.m_lstItem = nullptr;
			order.m_cntItem = 0;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isFilled() const
	{
		bool fill = true;
		for (size_t i = 0; i < m_cntItem && fill; i++)
		{
			if (m_lstItem[i]->m_isFilled == false)
				fill = false;
		}
		return fill;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool fill = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if (m_lstItem[i]->m_isFilled == false)
					fill = false;
			}
		}
		return fill;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() > 0)
				{
					m_lstItem[i]->m_isFilled = true;
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					station.updateQuantity();
					os << std::setw(11) << std::right << "Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]\n";
				}
				else
				{
					os << std::setw(19) << "Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]\n";
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << std::setfill('0') << std::right << std::setw(6) << m_lstItem[i]->m_serialNumber << "] ";
			os << std::setfill(' ');
			os << std::left;
			os << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";

			if (m_lstItem[i]->m_isFilled)
				os << "FILLED\n";
			else
				os << "TO BE FILLED\n";
		}
	}
}