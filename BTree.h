#pragma once
#include <iostream>
#include <queue>
using namespace std;

template<class T> class DSDB;  //declaring it ahead in order to declare it as a friend class later in the Bnode


//----------------------- elements --------------------------------------------------------------
template <typename T1, typename T2, typename T3>
struct elements
{
    T1 ID, year, Deaths;
    T2 CauseName_113, CauseName, State;
    T3 AgeAdjustedDeathRate;


    //default constructor
    elements()
    {
        ID = year = Deaths = 0;
        CauseName = CauseName_113 = State = "/0";
        AgeAdjustedDeathRate = 0.00;
    }

    //parameterised constructor
    elements(T1 id, T1 year, T2 Cause113, T2 Cause, T2 State, T1 Deaths, T3 DeathRate)
    {
        this->ID = id;
        this->year = year;
        this->Deaths = Deaths;
        this->CauseName_113 = Cause113;
        this->CauseName = Cause;
        this->State = State;
        this->AgeAdjustedDeathRate = DeathRate;


    }

    // = operator overloading
    void operator = (const elements<T1, T2, T3>& R)
    {
        this->ID = R.ID;
        this->year = R.year;
        this->Deaths = R.Deaths;
        this->CauseName = R.CauseName;
        this->CauseName_113 = R.CauseName;
        this->State = R.State;
        this->AgeAdjustedDeathRate = R.AgeAdjustedDeathRate;


    }

};

//-------------------------- elements implementation -------------------------

template <typename T1, typename T2, typename T3>
ostream& operator<<(ostream& output, const elements<T1, T2, T3>& R)
{
    output << R.ID << "," << R.year << "," << R.CauseName_113 << "," << R.CauseName << "," << R.State << "," << R.Deaths << "," << R.AgeAdjustedDeathRate << endl;
    return output;

}

template <typename T1, typename T2, typename T3>
istream& operator>>(istream& input, elements<T1, T2, T3>& R)
{
    input >> R.ID >> R.year >> R.CauseName_113 >> R.CauseName >> R.State >> R.Deaths >> R.AgeAdjustedDeathRate;
    return input;
}


//---------------------------- B tree Node -----------------------------------

template <typename T1, typename T2, typename T3>
struct Bnode
{

    elements<T1, T2, T3>* keys;  //a linked list/array of keys
    int minDegree;          //minimum keys
    int currentNoOfKeys; //checks if total number of keys has been reached
    bool leaf;        //check if Bnode is a leafnode or not
    Bnode<T1, T2, T3>** children; //pointer of pointers to store children
    //Bnode<T1,T2,T3>* next;
  //  Bnode<T1,T2,T3>* prev;

    Bnode()      //default constructor to initialize Bnode
    {

        //  prev = next = NULL;

    }

    Bnode(int _m, bool _leaf)      //default constructor to initialize Bnode
    {
        minDegree = _m;
        keys = new elements<T1, T2, T3>[2 * minDegree - 1];
        children = new Bnode<T1, T2, T3> *[2 * minDegree];
        currentNoOfKeys = 0;
        leaf = _leaf;
        //  prev = next = NULL;

    }

    //function to call to fill Bnode when keys aren't full
    void insertNotFull(T1 id, T1 year, T2 Cause113, T2 Cause, T2 State, T1 Deaths, T3 DeathRate, int choice);

    //when keys are full split the children
    void split(int i, Bnode<T1, T2, T3>* R);

    void travel();

    Bnode* seek(int id);

    Bnode* update(T1 oldId, T1 newId, T1 Newyear, T2 NewCause113, T2 NewCause, T2 NewState, T1 NewDeaths, T3 NewDeathRate, int choice);


    friend class BTree; //making Btrees a friend class
};

template<typename T1, typename T2, typename T3>
Bnode<T1, T2, T3>* Bnode<T1, T2, T3>::update(T1 oldId, T1 newId, T1 Newyear, T2 NewCause113, T2 NewCause, T2 NewState, T1 NewDeaths, T3 NewDeathRate, int choice)
{
    // cout << "update!" << endl;
    int counter = 0;

    while (counter < currentNoOfKeys && keys[counter].ID < oldId)
        counter++;

    if (keys[counter].ID == oldId)
    {
        cout << "updated!" << endl;
        elements<T1, T2, T3> temp(newId, Newyear, NewCause113, NewCause, NewState, NewDeaths, NewDeathRate);
        keys[counter] = temp;
        cout << temp << endl;
        //keys[counter].ID = newId;
       // keys[counter].year = year;
       // keys[counter].Deaths = Deaths;
       // cout << keys[counter] << endl;
        return this;

    }


    if (leaf)
    {
        cout << oldId << "  does not exist!" << endl;
        return NULL;

    }

    //recursively call and go to child
    return children[counter]->update(oldId, newId, Newyear, NewCause113, NewCause, NewState, NewDeaths, NewDeathRate, choice);



}

template<typename T1, typename T2, typename T3>
Bnode<T1, T2, T3>* Bnode<T1, T2, T3>::seek(int id)
{
    int counter = 0;

    while (counter < currentNoOfKeys && keys[counter].ID < id)
        counter++;

    if (keys[counter].ID == id)
    {
        cout << keys[counter] << endl;
        return this;

    }


    if (leaf)
    {
        cout << id << "does not exist!" << endl;
        return NULL;

    }

    //recursively call and go to child
    return children[counter]->seek(id);



}

template<typename T1, typename T2, typename T3>
void Bnode<T1, T2, T3>::travel()
{
    int counter = 0;

    for (; counter < this->minDegree; counter++)
    {
        if (!leaf)
        {
            if (children[counter] != NULL)
                children[counter]->travel();

        }

        if (children[counter] != NULL)
            cout << keys[counter] << endl;

    }

    if (!leaf && children[counter] != NULL)
        children[counter]->travel();

}

template <typename T1, typename T2, typename T3>
void Bnode<T1, T2, T3>::insertNotFull(T1 id, T1 year, T2 Cause113, T2 Cause, T2 State, T1 Deaths, T3 DeathRate, int choice)
{
    elements<T1, T2, T3> temp(id, year, Cause113, Cause, State, Deaths, DeathRate);

    int current = currentNoOfKeys - 1; //initializing from rightmost number of keys

    //if leaf

    if (leaf)
    {
        while (current >= 0 && keys[current].ID > id)
        {

            keys[current + 1] = keys[current];
            current--;
        }


        keys[current + 1] = temp;

        currentNoOfKeys++;
    }



    //else not a leaf Bnode
    else
    {
        //find child 

        while (current >= 0 && keys[current].ID > id)
            current--;

        //if child is full -->split it
      //children[current + 1]->currentNoOfKeys
        if (children[current + 1]->currentNoOfKeys == (2 * minDegree - 1))
        {
            //splitting 

            split(current + 1, children[current + 1]);

            //check which one of the middle has the new key
            if (keys[current + 1].ID < id)
                current++;


        }

        //recursively call 
        children[current + 1]->insertNotFull(id, year, Cause113, Cause, State, Deaths, DeathRate, choice);



    }

}

template <typename T1, typename T2, typename T3>
void Bnode<T1, T2, T3>::split(int i, Bnode<T1, T2, T3>* R)
{
    //create a new Bnode with t-1 children(parent)

    Bnode<T1, T2, T3>* parent = new Bnode <T1, T2, T3>(R->minDegree, R->leaf);


    int r = minDegree - 1;
    parent->currentNoOfKeys = r;

    //copying keys from R to Z




    for (int i = 0; i < r; i++)
        parent->keys[i] = R->keys[i + minDegree];

    //copy last children

    if (!R->leaf)
    {
        for (int i = 0; i < r + 1; i++)
            parent->children[i] = R->children[i + minDegree];

    }

    //reduce number of keys
    R->currentNoOfKeys = r;

    //creating space for new children
    for (int l = currentNoOfKeys; l >= i + 1; l--)
        children[l + 1] = children[l];

    //linking child

    children[i + 1] = parent;

    //find location of key and move it

    for (int j = currentNoOfKeys - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    //copy middle
    keys[i] = R->keys[r];




    currentNoOfKeys++;




}




//---------------------------- B tree -----------------------------------

template <typename T1, typename T2, typename T3>
class Btree {
private:


    Bnode<T1, T2, T3>* root;
    int m;


public:

    //Btree constructor, asks user for order of keys they wish
    Btree();
    void insert(T1 id, T1 year, T2 Cause113, T2 Cause, T2 State, T1 Deaths, T3 DeathRate);
    void travel()
    {
        if (root)
            root->travel();
    }

    Bnode<T1, T2, T3>* seek(int id)
    {
        if (root)
        {

            root->seek(id);

        }
        else
            cout << "tree does not exist yet!" << endl;
        return NULL;
    }

    Bnode<T1, T2, T3>* update(T1 oldId, T1 newId, T1 Newyear, T2 NewCause113, T2 NewCause, T2 NewState, T1 NewDeaths, T3 NewDeathRate, int choice)
    {
        if (root)
        {
            Bnode<T1, T2, T3>* temp = root->seek(oldId);
            elements<T1, T2, T3>temp2 = temp->keys[0];

            for (int i = 0; i < temp->minDegree; i++)
            {

                if (temp->keys[i].ID == oldId)
                {
                    //cout << "hello" << endl;
                    temp2 = temp->keys[i];

                    cout << temp2 << endl;
                }

            }
            root->update(oldId, newId, Newyear, NewCause113, NewCause, NewState, NewDeaths, NewDeathRate, choice);
            root->insertNotFull(temp2.ID, temp2.year, temp2.CauseName_113, temp2.CauseName, temp2.State, temp2.Deaths, temp2.AgeAdjustedDeathRate, 1);



        }
        else
            cout << "tree does not exist yet!" << endl;
        return NULL;


    }


};

//---------------------------- B tree Implementations-----------------------------------

template <typename T1, typename T2, typename T3>
Btree<T1, T2, T3>::Btree() {


    cout << "Enter Order of B-tree you wish to form:";
    cin >> m;

    while (m <= 3)
    {
        cout << "Order of b-tree must be greater than 3. Please enter a new value again" << endl;
        cin >> m;


    }

    root = NULL;
}


template <typename T1, typename T2, typename T3>
void Btree<T1, T2, T3>::insert(T1 id, T1 year, T2 Cause113, T2 Cause, T2 State, T1 Deaths, T3 DeathRate)
{
    elements<T1, T2, T3> temp(id, year, Cause113, Cause, State, Deaths, DeathRate);
    // cout << temp << endl;

    if (root == NULL)       //the tree has nothing inside of it
    {
        // Allocating root
        root = new Bnode<T1, T2, T3>(m, true);
        root->keys[0] = temp;  // Insert key



        root->currentNoOfKeys++;  // Update number of keys in root
    }
    //if tree isn't empty
    else
    {
        //if root full-> increase height

        if (root->currentNoOfKeys == 2 * m - 1)
        {
            //make a new root 
            Bnode<T1, T2, T3>* newRoot = new Bnode<T1, T2, T3>(m, false);

            newRoot->children[0] = root;

            //split old root and move key
            newRoot->split(0, root);

            int counter = 0;
            //decide which child will have key
            if (newRoot->keys[0].ID < id)
                counter++;


            newRoot->children[counter]->insertNotFull(id, year, Cause113, Cause, State, Deaths, DeathRate, 1);

            //change root
            root = newRoot;


        }

        //if root isn't full then fill the Bnode
        else
        {
            root->insertNotFull(id, year, Cause113, Cause, State, Deaths, DeathRate, 1);
            //             <--------------uncomment

        }





    }


}