#include "pch.h"


class CircBuf
    {
    public:
        size_t capacity;  // maximum number of items in the buffer
        size_t count;     // number of items in the buffer
        size_t itemsize;        // size of each item in the buffer
        CircBuf();
        ~CircBuf();
        CircBuf(size_t capacity,size_t itemsize);
        void PushCircBuf(const void* item);
        void PopCircBuf(void* item);

    private:
        void* data;     // data buffer Just to function unit tests. 
                //After performing unit tests, this can go in the
                //private section to provide better protection
        void* data_end; // end of data buffer
        void* headpointer;       // pointer to head
        void* tailpointer;       // pointer to tail
    };



CircBuf::CircBuf() { //default constructor
    count = 0;
    capacity = 0;
    itemsize = 0;
    data=nullptr;     // data buffer
    data_end=nullptr; // end of data buffer
    headpointer= nullptr;       // pointer to head
    tailpointer= nullptr;       // pointer to tail
}

CircBuf::CircBuf(size_t capacity, size_t size) { //overloaded constructer, parameterised 
    this->data = malloc(capacity * size);
    this->data_end = (char*)this->data + capacity * size;
    this->capacity = capacity;
    this->count = 0;
    this->itemsize = size;
    this->headpointer = this->data;
    this->tailpointer = this->data;
}

CircBuf::~CircBuf() {
    delete data; //release back to heap
    delete data_end;
    delete headpointer;
    delete tailpointer;
}

void CircBuf::PushCircBuf(const void* item) //Push item to the buffer without overwriting
{
    if (this->count == this->capacity) {
        std::cout << "Push Fail" << std::endl;
        return;
    }
    else {
        memcpy(this->headpointer, item, this->itemsize);
        this->headpointer = (char*)this->headpointer + this->itemsize;
        if (this->headpointer == this->data_end)
            this->headpointer = this->data;
        this->count++;
    }
}

void CircBuf::PopCircBuf(void* item)
{
    if (this->count == 0) {
        std::cout << "Pull Fail" << std::endl;
        return;
    }
    memcpy(item, this->tailpointer, this->itemsize);
    this->tailpointer = (char*)this->tailpointer + this->itemsize;
    if (this->tailpointer == this->data_end)
        this->tailpointer = this->data;
    this->count--;
}


//Google Unit Test Code
//Test Params
#define bufsize 20
std::string injectstring = "abcdefghijklmnopqrstuvwzyz123456789";
TEST(CircBufTester, InitEmptySize) {
  CircBuf TCircBuf;
  EXPECT_EQ(0, (int)TCircBuf.count);
  EXPECT_EQ(0, (int)TCircBuf.itemsize);
  EXPECT_EQ(0, (int)TCircBuf.capacity);
}

TEST(CircBufTester, InitValidSizeChars) {
    std::cout << "Initializing Tests" << std::endl;
   
    CircBuf* CirBufDemo = new CircBuf(bufsize, sizeof(const char*));
    EXPECT_EQ(bufsize, (int)CirBufDemo->capacity);
    EXPECT_EQ(sizeof(const char*), sizeof(CirBufDemo->itemsize));
  
}


TEST(CircBufTester, PushPullItemsTest) {
    std::cout << "Pushing Items without Overwriting" << std::endl;
    CircBuf* CirBufDemo = new CircBuf(bufsize, sizeof(const char*));
    for (int i = 0; i < (int)injectstring.length(); i++) {
        CirBufDemo->PushCircBuf(&injectstring[i]);
        std::cout << "Push " << " " << injectstring[i] << std::endl;
    }
    EXPECT_EQ(bufsize, (int)CirBufDemo->capacity);
    EXPECT_EQ(bufsize, (int)CirBufDemo->count);
    
    char* g;
    g = (char*)malloc(sizeof(char));
    for (int i = 0; i < (int)CirBufDemo->count; i++) {
        CirBufDemo->PopCircBuf(g);
        EXPECT_TRUE(*g=injectstring[i]);
    }
}


/*
//Driver Code
int main(void) {
    std::cout << "Testing " << std::endl;
    CircBuf *CirBufDemo = new CircBuf(10, sizeof(const char*));
}
*/