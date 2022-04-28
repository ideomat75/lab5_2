#include "Transaction.h"
#include "Account.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockAccount : public Account{
    public:
        MOCK_METHOD(int, GetBalance, (), (const, override));
        MOCK_METHOD(void, ChangeBalance, (int diff), (override));
        MOCK_METHOD(void, Lock, (), (override));
        MOCK_METHOD(void, Unlock, (), (override));
        MockAccount(int id, int balance) : Account(id, balance) {}
};

class MockTransaction : public Transaction{
    public:
        MOCK_METHOD(void, SaveToDataBase, (Account &from, Account &to, int sum), (override));
        MockTransaction() : Transaction() {}
};

TEST(Account, GetBalance){
    MockAccount a(13, 5000);

    EXPECT_CALL(a, GetBalance())
    .WillOnce(::testing::Return(5000));

    a.GetBalance();
}

TEST(Account, Lock){
    MockAccount a(13, 5000);

    EXPECT_NO_THROW(a.Account::Lock());
    EXPECT_THROW(a.Account::Lock(), std::runtime_error);
}

TEST(Account, Unlock){
    MockAccount a(13, 5000);

    EXPECT_CALL(a, Unlock)
    .Times(1);

    a.Unlock();
}

TEST(Account, ChangeBalance){
    MockAccount a(13, 5000);

    EXPECT_CALL(a, Lock);
    EXPECT_CALL(a, ChangeBalance);
    EXPECT_CALL(a, GetBalance)
    .Times(2)
    .WillOnce(::testing::Return(5000))
    .WillOnce(::testing::Return(5017));

    EXPECT_THROW(a.Account::ChangeBalance(17), std::runtime_error);
    a.Lock();
    a.GetBalance();
    a.ChangeBalance(17);
    a.GetBalance();
}

TEST(Transaction, SaveToDataBase){
    MockAccount a1(13, 5000), a2(20, 5000);
    MockTransaction t;

    EXPECT_CALL(t, SaveToDataBase)
    .Times(1);

    t.SaveToDataBase(a1, a2, 1000);
}

TEST(Transaction, Make){
    Account a1(13, 5000), a2(20, 5000);
    Transaction t;

    t.set_fee(500);

    EXPECT_EQ(t.fee(), 500);
    EXPECT_THROW(t.Make(a1, a1, 120), std::logic_error);
    EXPECT_THROW(t.Make(a1, a2, - 1), std::invalid_argument);
    EXPECT_THROW(t.Make(a1, a2, 90), std::logic_error);
    
    EXPECT_EQ(t.Make(a1, a2, 200000), false);
    EXPECT_EQ(t.Make(a1, a2, 1000), true);
    EXPECT_EQ(t.Make(a1, a2, 400), false);
}

int main (int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
