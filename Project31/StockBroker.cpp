#pragma once
#include <iostream>
#include <string>

using namespace std;

class IStockBrocker {
public:
	virtual void login(const string&, const string&) = 0;
};