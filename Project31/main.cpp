#include "gmock/gmock.h"

#include <sstream>
#include <iostream>
#include "IStockBrocker.h"
#include "AutoTrader.cpp";

using namespace testing;

class MockStockBrocker : public IStockBrocker {
public:
    MOCK_METHOD(void, login, (const std::string&, const std::string&), (override));
    MOCK_METHOD(void, buy, (const std::string&, int, int), (override));
    MOCK_METHOD(void, sell, (const std::string&, int, int), (override));
    MOCK_METHOD(int, getPrice, (const std::string&), (override));
};

TEST(APP1, Login)
{
    MockStockBrocker mockBrocker;
    AutoTrader trader(&mockBrocker);

    std::string testId = "user123";
    std::string testPass = "pass123";

    EXPECT_CALL(mockBrocker, login(testId, testPass))
        .Times(1)
        .WillOnce([&](const std::string& id, const std::string& pass) {
                std::cout << id << " login success\n";
            });

    std::stringstream buffer;
    std::streambuf* originalCout = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    trader.login(testId, testPass);

    std::cout.rdbuf(originalCout);

    std::string output = buffer.str();
    EXPECT_NE(output.find("user123 login success"), std::string::npos);
}

TEST(APP1, Buy)
{
    MockStockBrocker mockBrocker;
    AutoTrader trader(&mockBrocker);

    std::string stockCode = "TESLA";
    int count = 100;
    int price = 380000;

    EXPECT_CALL(mockBrocker, buy(stockCode, count, price))
        .Times(1)
        .WillOnce([&](const std::string& id, int count, int price) {
             std::cout << stockCode << " : Buy stock ( " << price << " * " << count << " )\n";
            });

    std::stringstream buffer;
    std::streambuf* originalCout = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    trader.buy(stockCode, count, price);

    std::cout.rdbuf(originalCout);

    std::string output = buffer.str();
    EXPECT_NE(output.find("TESLA : Buy stock ( 380000 * 100 )"), std::string::npos);
}

TEST(APP1, Sell)
{
    MockStockBrocker mockBrocker;
    AutoTrader trader(&mockBrocker);

    std::string stockCode = "TESLA";
    int count = 100;
    int price = 380000;

    EXPECT_CALL(mockBrocker, buy(stockCode, count, price))
        .Times(1)
        .WillOnce([&](const std::string& id, int count, int price) {
        std::cout << stockCode << " : Sell stock ( " << price << " * " << count << ")\n";
            });

    std::stringstream buffer;
    std::streambuf* originalCout = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    trader.buy(stockCode, count, price);

    std::cout.rdbuf(originalCout);

    std::string output = buffer.str();
    EXPECT_NE(output.find("TESLA : Sell stock ( 380000 * 100 )"), std::string::npos);
}

TEST(APP1, getPrice)
{
    
    MockStockBrocker mockBrocker;
    AutoTrader trader(&mockBrocker);

    std::string stockCode = "TESLA";
    int expectedPrice = 5432;

    EXPECT_CALL(mockBrocker, getPrice(stockCode))
        .Times(1)
        .WillOnce(testing::Return(expectedPrice));

    int price = trader.getPrice(stockCode);

    EXPECT_EQ(price, expectedPrice);
}

int main()
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}