#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project14/DeviceDriver.cpp"

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
    MOCK_METHOD(unsigned char, read, (long), (override));
    MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class DeviceDriverTestFixture : public testing::Test {
public:
    DeviceDriver* device;
    MockFlashMemoryDevice FLASHMEMORY;
    
    const long ADDRESS = 0;
    const int WRITE_DATA = 0x11;
    const char READ_DATA = 'A';
    const char ANOTHER_READ_DATA = 'B';
    const int EMPTY_DATA = 0xFF;
    
    void SetUp() {
        device = new DeviceDriver(&FLASHMEMORY);
    }
};

TEST_F(DeviceDriverTestFixture, readSucessTest) {
    EXPECT_CALL(FLASHMEMORY, read)
        .Times(5)
        .WillRepeatedly(testing::Return(READ_DATA));

    EXPECT_EQ(device->read(ADDRESS), READ_DATA);
}

TEST_F(DeviceDriverTestFixture, readFailTest) {
    EXPECT_CALL(FLASHMEMORY, read)
        .WillOnce(testing::Return(READ_DATA))
        .WillRepeatedly(testing::Return((ANOTHER_READ_DATA)));

    try {
        device->read(ADDRESS);
        FAIL();
    }
    catch (ReadFailException readFailException) {
        EXPECT_EQ(std::string("Read fail"), std::string(readFailException.what()));
    }
}

TEST_F(DeviceDriverTestFixture, writeSuccessTest) {
    EXPECT_CALL(FLASHMEMORY, read)
        .Times(1)
        .WillOnce(testing::Return(EMPTY_DATA));
    EXPECT_CALL(FLASHMEMORY, write).Times(1);

    device->write(ADDRESS, WRITE_DATA);
}

TEST_F(DeviceDriverTestFixture, writeFailTest) {
    EXPECT_CALL(FLASHMEMORY, read)
        .Times(1)
        .WillOnce(testing::Return(READ_DATA));
    EXPECT_CALL(FLASHMEMORY, write).Times(0);

    try {
        device->write(ADDRESS, WRITE_DATA);
        FAIL();
    }
    catch (WriteFailException writeFailException) {
        EXPECT_EQ(std::string("Write fail"), std::string(writeFailException.what()));
    }
}
