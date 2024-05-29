#include <list/list.h>

using namespace std;

/*
 * Implements for class ArrayList
*/
template <class T> ArrayList<T>::ArrayList(): pD(nullptr), nE(0), cap(0) {}

template <class T> ArrayList<T>::ArrayList(int N): nE(0), cap(N) { pD = new T[N]; }

template <class T> ArrayList<T>::ArrayList(int N, T E): nE(N), cap(N) {
    pD = new T[N];
    for (int i = 0; i < N; ++i) pD[i] = E;
}

template <class T> ArrayList<T>::~ArrayList() { this->clear(); }

template <class T> void ArrayList<T>::reSize(int N) {
    if (this->cap == N) {
        int newcap = (N + ARRAYDATABLOCK - 1)/(ARRAYDATABLOCK)*ARRAYDATABLOCK;
        T* newpD = new T[newcap];

        for (int i = 0; i < this->nE; ++i) newpD[i] = this->pD[i];

        delete [] pD;
        pD = newpD;
        this->cap = newcap;
        newpD = nullptr;
    }
    return;
}

template <class T> int ArrayList<T>::getSize() { return this->nE; }

template <class T> bool ArrayList<T>::isEmpty() { return this->nE == 0; }

template <class T> void ArrayList<T>::clear() {
    this->nE = 0;
    this->cap = 0;
    if (pD) {
        delete [] pD;
        pD = nullptr;
    }
}

template <class T> List<T>* ArrayList<T>::clone() {
    List<T>* CloneArr = new ArrayList<T>(this->nE);

    for (int i = 0; i < this->nE; ++i) CloneArr->pD[i] = this->pD[i];

    return CloneArr;
}

template <class T> void ArrayList<T>::insert(T& val, const int indx) {
    try {
        if (indx > nE || indx < 0) throw std::range_error("ArrayList::insert() -> Invalid index.\n");
        
        this->reSize(nE + 1);

        for (int i = nE; i > indx; --i) this->pD[i] = this->pD[i - 1];
        this->pD[indx] = val;
        ++this->nE;

        return;
    }
    catch (std::exception& e) {
        cerr << e.what();
    }
}

template <class T> void ArrayList<T>::remove(const int indx) {
    try {
        if (indx >= nE || indx < 0) throw std::range_error("ArrayList::remove() -> Invalid index.\n");

        for (int i = indx; i < nE; ++i) this->pD[i] = this->pD[i + 1];
        --this->nE;

        return;
    }
    catch (std::exception& e) {
        cerr << e.what();
    }
}

template <class T> int ArrayList<T>::findIdx(const T& val) {
    if (this->nE == 0) return -1;
    
    for (int i = 0; i < nE; ++i) if (this->pD[i] == val) return i;

    return -1;
}

template <class T> T* ArrayList<T>::findP(const T& val) {
    if (!pD) return nullptr;
    T* p = this->pD;

    while (p != (this->pD + nE)) {
        if ((*p) == val) return p;
        else p++;
    }

    return nullptr;
}

template <class T> T& ArrayList<T>::operator[](int indx) {
    try {
        if (indx < 0 || indx >= this->nE) throw range_error("ArrayList::operator[] -> Invalid index.\n");

        return *(this->pD[indx]);
    }
    catch (std::exception &e) {
        cerr << e.what();
    }
}

template <class T> ArrayList<T>& ArrayList<T>::operator=(List<T>& aL) {
    try {
        if (!aL) throw invalid_argument("ArrayList::operator= -> Can not assign to a null value.\n");
        
        this->clear();

        this->nE = aL.nE;
        this->cap = aL.cap;
        this->pD = new T[cap];

        for (T* p = this->pD, T* ap = aL.pD; ap != (aL.pD + aL.nE)) {
            (*p) = (*ap);
            p++;
            ap++;
        }

        return &(*this);
    }
    catch (std::exception& e) {
        cerr << e.what();
    }
}

template <class T> List<T>& ArrayList<T>::split(int indx, bool flag = true) {
    if (indx < 0 || indx >= this->nE) throw range_error("ArrayList::split() -> Invalid index.\n");
    if (flag) {
        for (int i = indx; i < this->nE) this->remove(this->nE - 1);

        return &(*this);
    }
    else {
        for (int i = 0; i < this->nE - indx; ++i) this->pD[i] = this->pD[indx + i];
        this->nE = this->nE - indx;

        return &(*this);
    }
}

template <class T> List<T>& ArrayList<T>::merge(List<T>& aL) {
    int size = aL.getSize();

    for (int i = 0; i < size; ++i) this->insert(aL[i], this->nE);

    aL->clear();

    return &(*this);
}

template <class T> void ArrayList<T>::printList() {
    if (this->isEmpty()) {
        cout << "<Empty list>\n";
        return;
    }
    
    for (int i = 0; i < this->nE - 1; ++i) cout << this->pD[i];
    cout << this->pD[this->nE - 1] << endl;

    return;
}