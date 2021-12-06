#include <iostream>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

using namespace std;
namespace sdds
{
	LineManager::LineManager(const string& file, const vector<Workstation*>& stations)
	{
		try
		{
			ifstream fname(file);
			string fileRecord;
			Utilities obj;

			while (!fname.eof())
			{
				getline(fname, fileRecord);
				string firstStation, secondStation;
				size_t pos = 0;
				bool more = true;

				firstStation = obj.extractToken(fileRecord, pos, more);
				if (more)
					secondStation = obj.extractToken(fileRecord, pos, more);

				for_each(stations.begin(), stations.end(), [=](Workstation* ws)
					{
						if (ws->getItemName() == firstStation)
						{
							for_each(stations.begin(), stations.end(), [=](Workstation* nextws)
								{
									if (nextws->getItemName() == secondStation)
										ws->setNextStation(nextws);
								});
							activeLine.push_back(ws);
						}
					});
			}
			m_firstStation = activeLine.front();
			m_cntCustomerOrder = pending.size();
		}
		catch(...)
		{
			cerr << "Unexpected Error Occured";
		}
	}

	void LineManager::linkStations()
	{
		vector<Workstation*> tempWS{ m_firstStation };
		size_t i = 0;

		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws)
		{
			for_each(activeLine.begin(), activeLine.end(), [&](Workstation* nextws)
			{
				if (tempWS[i]->getNextStation())
				{
					if (tempWS[i]->getNextStation()->getItemName() == nextws->getItemName())
					{
						tempWS.push_back(nextws);
						++i;
					}
				}
			});
		});
		activeLine = tempWS;
	}

	bool LineManager::run(ostream& ostr)
	{
		static size_t itNum = 1;
		ostr << "Line Manager Iteration: " << itNum << endl;
		size_t totOrderBeforeRun = completed.size() + incomplete.size();

		if (!pending.empty())
		{
			*m_firstStation += move(pending.front());
			pending.pop_front();
		}

		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws)
		{
			ws->fill(ostr);
		});

		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws)
		{
			ws->attemptToMoveOrder();
		});

		size_t totOrderAfterRun = completed.size() + incomplete.size();
		m_cntCustomerOrder -= totOrderAfterRun - totOrderBeforeRun;
		itNum++;

		if (m_cntCustomerOrder <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void LineManager::display(ostream& ostr) const
	{
		for_each(activeLine.begin(), activeLine.end(), [&ostr](Workstation* ws)
		{
			ws->display(ostr);
		});
	}
}