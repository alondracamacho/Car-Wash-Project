//CSC 326 Car Wash Team Project
//Alondra Camacho & Marc Flores

//This program simulates a car wash running during a certain time frame while arrival time, waiting time, and time of completion is tracked. 
//The total number of customers and the average wait time is also calculated

#ifndef WASHING_H
#define WASHING_H

#include <cstddef> // For size_t
#include <cassert> // For assert
using namespace std;

    // Class for probabilistic events
    class bool_source {
    public:
        // Constructor
        bool_source(double p = 0.5);

        // Constant member function
        bool query() const;

    private:
        double probability; // Probability of query() returning true
    };

    // Class to compute averages
    class averager {
    public:
        // Constructor
        averager();

        // Modification member function
        void next_number(double value);

        // Constant member functions
        std::size_t how_many_numbers() const 
            { return count; }
        
        double average() const;

    private:
        std::size_t count; // Number of values added to the averager
        double sum;        // Sum of all values added
    };

    // Class to simulate the washer
    class washer {
    public:
        // Constructor
        washer(unsigned int s = 60);

        // Modification member functions
        void one_second();
        void start_washing();

        // Constant member function
        bool is_busy() const 
            { return (wash_time_left > 0); }

    private:
        unsigned int seconds_for_wash; // Duration of a single wash cycle in seconds
        unsigned int wash_time_left;   // Time left for the current wash cycle
    };

//template Que class based on linked nodes
template <class ItemType>
struct NodeType;

template <class ItemType>
class Que {
public:
    Que();
    ~Que();
    // user-defined copy constructor
    Que(const Que<ItemType>& original);
    // user-defined assignment operator
    void operator=(Que <ItemType> &otherQueue);
    void makeEmpty();
    bool empty() const;
    bool full() const;
    void addQ(ItemType newItem);
    void removeQ(ItemType& item);
    void print( ) const;
private:
    NodeType<ItemType>* qFront;
    NodeType<ItemType>* qRear;
};

template <class ItemType>
struct NodeType {
    ItemType info;
    NodeType* next;
};

template <class ItemType>
Que<ItemType>::Que() {// Class constructor.
// Post: qFront and qRear are set to nullptr.
    qFront = nullptr;
    qRear = nullptr;
}

template <class ItemType> // Class destructor.
Que<ItemType>::~Que() {
    makeEmpty();
}

template<class ItemType> // user-defined copy constructor
Que<ItemType>:: Que( const Que <ItemType>& original ) { 
    NodeType<ItemType>* tempPtr ;
    NodeType<ItemType>* newPtr ;
    if (original.qFront == nullptr)
        qFront=qRear= nullptr;
    else {// allocate memory for first node
        tempPtr= original.qFront;
        newPtr = new NodeType<ItemType> ;
        newPtr ->info = tempPtr ->info ;
        tempPtr= tempPtr ->next ;
        qFront = newPtr ;
        while (tempPtr!= nullptr ) {// deep copy other nodes
            newPtr->next = new NodeType< ItemType >;
            newPtr = newPtr ->next;
            newPtr->info = tempPtr->info ;
            tempPtr = tempPtr ->next ;
        }
        newPtr->next = nullptr ;
        qRear=newPtr;
    }
}

template <class ItemType>
void Que<ItemType>::makeEmpty() {
// Post: Queue is empty; all elements have been deallocated.
    NodeType<ItemType>* tempPtr;
    while (qFront != nullptr) {
        tempPtr = qFront;
        qFront = qFront->next;
        delete tempPtr;
    }
    qRear = nullptr;
}

template <class ItemType> // user-defined assignment operator
void Que <ItemType>::operator=( Que <ItemType> &otherQueue) {
    if (this != & otherQueue) {
        NodeType<ItemType>* tempPtr ;
        NodeType<ItemType>* newPtr ;
        if (otherQueue.empty( ))
            empty( );
        else {// allocate memory for first node
            tempPtr= otherQueue.qFront;
            newPtr = new NodeType<ItemType> ;
            newPtr ->info = tempPtr ->info ;
            tempPtr= tempPtr ->next ;
            qFront = newPtr ;
            while (tempPtr!= nullptr ) {// deep copy other nodes
                newPtr->next = new NodeType< ItemType >;
                newPtr = newPtr ->next;
                newPtr->info = tempPtr->info ;
                tempPtr = tempPtr ->next ;
            }
            newPtr->next = nullptr;
            qRear=newPtr;
        }
    }
}

template <class ItemType>
bool Que<ItemType>::full() const {
// Returns true if there is no memory for another ItemType in the heap;
// false otherwise.
    NodeType<ItemType>* ptr;
    ptr = new NodeType<ItemType>;
    if (ptr == nullptr)
        return true;
    else {
    delete ptr;
    return false;
    }
}

template <class ItemType>
bool Que<ItemType>::empty() const {
// Returns true if there are no elements in the queue; false otherwise.
    return (qFront == nullptr);
}

template <class ItemType>
void Que<ItemType>::addQ(ItemType newItem) {
// Adds newItem to the rear of the queue.
// Pre: Queue has been initialized and is not full.
// Post: newItem is at rear of queue.
    NodeType<ItemType>* newNode;
    newNode = new NodeType<ItemType>;
    newNode->info = newItem;
    newNode->next = nullptr;
    if (qRear == nullptr)
        qFront = newNode;
    else
        qRear->next = newNode;
    qRear = newNode;
}

template <class ItemType>
void Que<ItemType>::removeQ(ItemType& item) {
// Removes front item from the queue and returns it in item.
// Pre: Queue has been initialized and is not empty.
// Post: Front element has been removed from queue.
// item is a copy of removed element.
    NodeType<ItemType>* tempPtr;
    tempPtr = qFront;
    item = qFront->info;
    qFront = qFront->next;
    if (qFront == nullptr)
        qRear = nullptr;
    delete tempPtr;
}

template <class ItemType>
void Que<ItemType>::print() const {
    NodeType<ItemType> *tempPtr;
    tempPtr = qFront;
    while ( tempPtr != nullptr ) {
        cout << tempPtr->info<< ' ';
        tempPtr = tempPtr->next;
    }
    cout << endl;
}

#endif // WASHING_H