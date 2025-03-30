#include "gmock/gmock.h"
#include "AutoTrader.cpp"

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

    EXPECT_CALL(mockBrocker, sell(stockCode, count, price))
        .Times(1)
        .WillOnce([&](const std::string& id, int count, int price) {
        std::cout << stockCode << " : Sell stock ( " << price << " * " << count << ")\n";
            });

    std::stringstream buffer;
    std::streambuf* originalCout = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    trader.sell(stockCode, count, price);

    std::cout.rdbuf(originalCout);

    std::string output = buffer.str();
    EXPECT_NE(output.find("TESLA : Sell stock ( 380000 * 100)"), std::string::npos);
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

TEST(APP2, BuyNiceTiming_Success) {
    MockStockBrocker mockBrocker;
    AutoTrader trader(&mockBrocker);
    std::string code = "AAPL";
    int totalMoney = 12000;

    EXPECT_CALL(mockBrocker, getPrice(code))
        .Times(3)
        .WillOnce(Return(100))
        .WillOnce(Return(110))
        .WillOnce(Return(120));

    EXPECT_CALL(mockBrocker, buy(code, 100, 120)).Times(1);

    trader.buyNiceTiming(code, totalMoney);
}

TEST(APP2, BuyNiceTiming_FAIL) {
    MockStockBrocker mockBrocker;
    AutoTrader trader(&mockBrocker);
    std::string code = "AAPL";

    // 추세 없음 (중간이 높음)
    EXPECT_CALL(mockBrocker, getPrice(code))
        .Times(3)
        .WillOnce(Return(100))
        .WillOnce(Return(150))
        .WillOnce(Return(120));

    // buy()는 호출되지 않아야 함
    EXPECT_CALL(mockBrocker, buy(testing::_, testing::_, testing::_)).Times(0);

    trader.buyNiceTiming(code, 10000);
}

TEST(APP2, SellNiceTiming_Success) {
    MockStockBrocker mockBrocker;
    AutoTrader trader(&mockBrocker);
    std::string code = "GOOG";
    int quantity = 5;

    // getPrice 3번: 하락 추세
    EXPECT_CALL(mockBrocker, getPrice(code))
        .Times(3)
        .WillOnce(Return(150))
        .WillOnce(Return(140))
        .WillOnce(Return(130));

    EXPECT_CALL(mockBrocker, sell(code, 130, quantity)).Times(1);

    trader.sellNiceTiming(code, quantity);
}

TEST(APP2, SellNiceTiming_FAIL) {
    MockStockBrocker mockBrocker;
    AutoTrader trader(&mockBrocker);
    std::string code = "GOOG";

    // 추세 없음
    EXPECT_CALL(mockBrocker, getPrice(code))
        .Times(3)
        .WillOnce(Return(150))
        .WillOnce(Return(160))
        .WillOnce(Return(140));

    EXPECT_CALL(mockBrocker, sell(testing::_, testing::_, testing::_)).Times(0);

    trader.sellNiceTiming(code, 5);
}

int main()
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
