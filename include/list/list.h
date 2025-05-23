#ifndef __LIST_H__
#define __LIST_H__

#define ARRAYDATABLOCK 32

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cmath>
#include <string>

using namespace std;
/*
 * List - Interface for some basic feature 
*/
template <class T>
class List {
    public:
        List() {}
        virtual ~List() {}
        
        virtual int getSize() = 0;
        virtual bool isEmpty() = 0;
        virtual void clear() = 0;
        virtual List<T>* clone() = 0;

        virtual void insert(const T& val, const int indx) = 0;
        virtual void remove(const int indx) = 0;
        virtual int findIdx(const T& val) = 0;
        virtual T* findP(const T& val) = 0;
        virtual T& operator[](int indx) = 0;

        virtual List<T>& split(int indx, bool flag = true) = 0;
        virtual List<T>& merge(List<T>* aL) = 0;
        virtual void reverse() = 0;

        virtual void printList() = 0;
};

template <class T>
class ArrayList: public List<T> {
    protected:

        T* pD;
        int nE, cap;

    public:
        ArrayList();
        ArrayList(int N);
        ArrayList(int N, T E);
        ~ArrayList();

        void reSize(int N);

        int getSize();
        bool isEmpty();
        void clear();
        List<T>* clone();

        void insert(T& val, const int indx);
        void remove(const int indx);
        int findIdx(const T& val);
        T* findP(const T& val);
        T& operator[](int indx);
        
        ArrayList<T>& operator=(List<T>&);
        List<T>& split(int indx, bool flag = true);
        List<T>& merge(List<T>& aL);

        void printList();
};

template <class T>
class SinglyLinkedList: public List<T> {
    protected:

        struct SLNode {
            T value;
            SLNode* pNext;
        };
        
        SLNode* root;
        int size;

    public:

        
};
#endif //__LIST_H__