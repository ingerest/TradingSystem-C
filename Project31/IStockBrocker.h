#pragma once
#pragma once

#include <iostream>
#include <string>


class IStockBrocker
{
public:
    virtual void login(const std::string& inId, const std::string& inPassword) = 0;
    virtual void buy(const std::string& stockCode, int count, int price) = 0;
    virtual void sell(const std::string& stockCode, int count, int price) = 0;
    virtual int getPrice(const std::string& stockCode) = 0;
};