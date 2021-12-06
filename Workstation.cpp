// Name: Khushwant Singh Rao
// Seneca Student ID: 145931192
// Seneca email: ksrao1@myseneca.ca
// Date of completion: Dec 2, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Workstation.h"

using namespace std;

deque<sdds::CustomerOrder> pending {};
deque<sdds::CustomerOrder> completed {};
deque<sdds::CustomerOrder> incomplete {};

namespace sdds
{
	Workstation::Workstation(const std::string& str): Station(str)
	{}

	void Workstation::fill(ostream& os)
	{
		if (!m_orders.empty())
			m_orders.front().fillItem(*this, os);
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool moved = false;
		if (m_orders.size() > 0 && (getQuantity() == 0 || m_orders.front().isItemFilled(getItemName())))
		{
			if (m_orders.front().isFilled())
			{
				if (m_pNextStation == nullptr)
					completed.push_back(move(m_orders.front()));
				else
				{
					*m_pNextStation += move(m_orders.front());
					moved = true;
				}
			}
			else
			{
				if (m_pNextStation == nullptr)
					incomplete.push_front(move(m_orders.front()));
				else
				{
					*m_pNextStation += move(m_orders.front());
					moved = true;
				}
			}
			m_orders.pop_front();
		}

		return moved;
	}

	void Workstation::setNextStation(Workstation* station = nullptr)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(ostream& os) const
	{
		if (m_pNextStation)
		{
			os << getItemName() << " --> ";
			os << m_pNextStation->getItemName() << endl;
		}
		else
		{
			os << getItemName() << " --> ";
			os << "End of Line" << endl;
		}
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(move(newOrder));
		return *this;
	}
}