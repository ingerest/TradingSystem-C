#include "IStockBrocker.h"

class AutoTrader
{
public:
	AutoTrader(IStockBrocker* pStockBrocker) : m_pStockBrocker(pStockBrocker)
	{
	}

	void login(const std::string& inId, const std::string& inPassword)
	{
		m_pStockBrocker->login(inId, inPassword);
	}

	void buy(const std::string& stockCode, int count, int price)
	{
		m_pStockBrocker->buy(stockCode, count, price);
	}
	void sell(const std::string& stockCode, int count, int price) 
	{
		m_pStockBrocker->sell(stockCode, count, price);
	}
	int getPrice(const std::string& stockCode)
	{
		return m_pStockBrocker->getPrice(stockCode);
	}

private:
	IStockBrocker* m_pStockBrocker = nullptr;
};