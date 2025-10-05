/*---------------------------------------
Program 5: Follow the Links, Escape the Labyrinth
The grid.h file defines the grid class, with private members
size_t NumRows, CELL array of pointers Rows, and
the Cell struct, which is effectively a node, in
addition to public functions. This file is included
in EscapeTheLabyrinth.h and both are used to create a
labyrinth game using gdb.
Course: CS 211, Spring 2025, UIC
Author: Jonathan Pabilic
---------------------------------------*/

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
private:
    struct CELL {
        CELL* Next;
        T Val;
        size_t NumCols;  // total columns in the grid
        CELL(CELL* _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
            Next = _Next;
            Val = _Val;
            NumCols = _NumCols;
        }
    };
    
    size_t NumRows;  // total rows in the grid
    CELL** Rows;     // array of pointers
public:
    /*
    The default constructor for a Grid object.

    Parameters: 
    -None

    Returns:
    -None
    */
    Grid() {
        // initialize 4 rows
        Rows = new CELL*[4];
        NumRows = 4;
        
        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r] = new CELL(nullptr, T(), 4);
            CELL* cur = Rows[r];
            
            // create the linked list for this row.
            for(size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
        
    }


    /*
    The parameterized constructor for a Grid object.

    Parameters: 
    -Size of rows
    -Size of columns

    Returns:
    -None
    */
    Grid(size_t R, size_t C) {
        // initialize R rows
        Rows = new CELL*[R];
        NumRows = R;
        
        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r] = new CELL(nullptr, T(), C);
            CELL* cur = Rows[r];
            
            // create the linked list for this row.
            for(size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
    }
    

    /*
    The destructor for a Grid object.

    Parameters: 
    -None

    Returns:
    -None
    */
    virtual ~Grid() {
      for (int i = 0; i < NumRows; ++i){
        CELL* curr = Rows[i];
        CELL* temp = nullptr;
        while (curr != nullptr){
            temp = curr->Next;
            delete curr;
            curr = temp;
        }
        Rows[i] = nullptr;
      }
        delete[] this->Rows;
    }
    
    
    /*
    The copy constructor for a Grid object.

    Parameters: 
    -A reference of the grid to copy from

    Returns:
    -None
    */
    Grid(const Grid<T>& other) {
        this->NumRows = other.NumRows;
        this->Rows = new CELL*[NumRows];

        for (int i = 0; i < other.NumRows; ++i){
            CELL* from = other.Rows[i];
            if (from == nullptr){
                Rows[i] = nullptr;
                continue;
            }

            Rows[i] = new CELL(nullptr, from->Val, from->NumCols);
            CELL* to = Rows[i];
            from = from->Next;

            while (from != nullptr){
                to->Next = new CELL(nullptr, from->Val);
                from = from->Next;
                to = to->Next;
            }
        }
    }
    

    /*
    The overloaded assignment operator for a Grid object.

    Parameters: 
    -A constant reference grid to copy from

    Returns:
    -The "new" grid
    */
    Grid& operator=(const Grid& other) {
        if (this == &other){
            return *this;
        }
        for (int i = 0; i < NumRows; ++i){
            if (Rows[i] == nullptr){
                continue;
            }
            CELL* curr = Rows[i];
            CELL* temp = nullptr;
            while (curr != nullptr){
                temp = curr->Next;
                delete curr;
                curr = temp;
            }
        }
        delete[] Rows;

        this->NumRows = other.NumRows;
        Rows = new CELL*[NumRows];
        for (int i = 0; i < other.NumRows; ++i){
            CELL* from = other.Rows[i];
            Rows[i] = new CELL(nullptr, from->Val, from->NumCols);
            CELL* to = Rows[i];
            from = from->Next;
            while (from != nullptr){
                to->Next = new CELL(nullptr, from->Val);
                from = from->Next;
                to = to->Next;
            }
        }
        return *this;
    }
    

    /*
    numrows returns the number of rows in the grid.
    Runs in O(1).

    Parameters: 
    -None

    Returns:
    -A size_t value of the number of rows
    */
    size_t numrows() const {
        return NumRows;
    }
    
    
    /*
    numcols returns the number of rows in the grid.

    Parameters: 
    -A size_t value of a row index

    Returns:
    -A size_t value of the number of columns
    */
    size_t numcols(size_t r) const {
        return Rows[r]->NumCols;
    }
    
    
    /*
    size returns the number of elements in the grid.

    Parameters: 
    -None

    Returns:
    -A size_t value of the number of elements
    */
    size_t size() const {
        return numrows() * numcols(0);
    }
    

    /*
    The overloaded () operator for a grid object. 
    Returns a reference to the element at location (r, c);
    this allows you to access the element or change it:
    grid(r, c) = ...
    cout << grid(r, c) << endl;

    Parameters: 
    -A size_t value of a row index
    -A size_t value of a column index

    Returns:
    -A reference to the element at location (r, c)
    */
    T& operator()(size_t r, size_t c) {
        if (r >= NumRows || c >= Rows[r]->NumCols){
            throw out_of_range("Out of range");
        }
        CELL* curr = Rows[r];
        for(size_t i = 0; i < c; ++i) {
                curr = curr->Next;
        }
        
        return curr->Val;
    }
    
    /*
    _output outputs the contents of the grid for
    testing purposes only.

    Parameters: 
    -None

    Returns:
    -None
    */
    void _output() {
        for (size_t r = 0; r < NumRows; ++r) {
            cout << "ROW " << r << ", ";
            int index = 0;
            CELL* curr = Rows[r];
            while (curr != nullptr){
                cout << "COL " << index << ": " << curr->Val << endl;
                curr = curr->next;
                index++;
            }
        }
    }  
};
