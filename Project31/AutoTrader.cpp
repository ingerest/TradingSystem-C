
#include "StockBroker.cpp"
#include <iostream>

class AutoTrader {
public:
	AutoTrader(IStockBrocker* stockBroker) : m_stockBroker(stockBroker)
	{
	}

	void login(string id, string pass) {
		m_stockBroker->login(id, pass);
	}

protected:
	IStockBrocker* m_stockBroker;
};

