// Name: Khushwant Singh Rao
// Seneca Student ID: 145931192
// Seneca email: ksrao1@myseneca.ca
// Date of completion: Dec 2, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"
namespace sdds
{
	char Utilities::m_delimiter = {};
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string tempStr = str.substr(next_pos);
		std::string token;
		if (str[next_pos] == m_delimiter)
		{
			more = false;
			throw "delimiter at next_pos";
		}
		else
		{
			token = str.substr(next_pos,tempStr.find_first_of(m_delimiter));
			if (!token.empty())
			{
				next_pos += tempStr.find_first_of(m_delimiter) + 1;
				if (tempStr.find_first_of(m_delimiter) == std::string::npos)
					more = false;
				else
					more = true;
				if (m_widthField < token.length())
					m_widthField = token.length();
			}
			else
				more = false;
		}
		return token;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}
