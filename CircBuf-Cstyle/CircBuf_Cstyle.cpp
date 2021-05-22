#define CirBuffSize 10

#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include <string>
#include<iostream>




typedef struct CircBuf
{
    void* data;     // data buffer
    void* data_end; // end of data buffer
    void* headpointer;       // pointer to head
    void* tailpointer;       // pointer to tail
    size_t capacity;  // maximum number of items in the buffer
    size_t count;     // number of items in the buffer
    size_t itemsize;        // size of each item in the buffer

}CircBuf;

void InitCircBuf(CircBuf* circbuf, size_t capacity, size_t sz)
{
    circbuf->data = malloc(capacity * sz);
    if (circbuf->data == NULL) {
        std::cout << "Buffer Init Fail" << std::endl;
        return;
    }
    else {
        circbuf->data_end = (char*)circbuf->data + capacity * sz;
        circbuf->capacity = capacity;
        circbuf->count = 0;
        circbuf->itemsize = sz;
        circbuf->headpointer = circbuf->data;
        circbuf->tailpointer = circbuf->data;
    }
}

void FreeCircBuf(CircBuf* circbuf)
{
    free(circbuf->data);

}

void PushCircBuf(CircBuf* circbuf, const void* item)
{
    if (circbuf->count == circbuf->capacity) {
        std::cout << "Push Fail" << std::endl;
        return;
    }
    else {
        memcpy(circbuf->headpointer, item, circbuf->itemsize);
        circbuf->headpointer = (char*)circbuf->headpointer + circbuf->itemsize;
        if (circbuf->headpointer == circbuf->data_end)
            circbuf->headpointer = circbuf->data;
        circbuf->count++;
    }
}

void PopCircBuf(CircBuf* circbuf, void* item)
{
    if (circbuf->count == 0) {
        std::cout << "Pull Fail" << std::endl;
        return;
    }
    memcpy(item, circbuf->tailpointer, circbuf->itemsize);
    circbuf->tailpointer = (char*)circbuf->tailpointer + circbuf->itemsize;
    if (circbuf->tailpointer == circbuf->data_end)
        circbuf->tailpointer = circbuf->data;
    circbuf->count--;
}


int main(int argc, char** argv) {


    std::string str = "abcdefghijklmnop";
    CircBuf CircularBufferDemo;
    InitCircBuf(&CircularBufferDemo, CirBuffSize, sizeof(const char*));
    //std::cout << "Size of the Buf " << buffer1.count << std::endl;



    for (int i = 0; i < 12; i++) {
        PushCircBuf(&CircularBufferDemo, &str[i]);
        std::cout << "Push " << " " << str[i] << std::endl;
    }

    char* g;
    g = (char*)malloc(sizeof(char));

    for (int i = 0; i < 12; i++) {
        PopCircBuf(&CircularBufferDemo, &g);
        std::cout << "Pull " << " " << (char)g << std::endl;
        g = NULL;
    }

    FreeCircBuf(&CircularBufferDemo); //Release

    return 0;
}

