#pragma once
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
	void sellNiceTiming(const std::string& stockCode, int count) {


	}

	void buyNiceTiming(const std::string& stockCode, int totalMoney)
	{
		int prevPrice = -1;
		bool isIncreasing = true;

		for (int i = 0; i < 3; i++)
		{
			int curPrice = getPrice(stockCode);

			if (curPrice <= prevPrice)
			{
				isIncreasing = false;
				break;
			}

			prevPrice = curPrice;
		}

		if (isIncreasing == true)
		{
			int count = totalMoney / prevPrice;
			buy(stockCode, count, prevPrice);
		}
		else
		{
			// buy(stockCode, count, prevPrice);
		}

	}

	void sellNiceTiming(const std::string& stockCode, int quantity)
	{

	}
private:
	IStockBrocker* m_pStockBrocker = nullptr;
};