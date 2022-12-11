#include <iostream>
#include <string>
#include "AVL.h"
#include "BTree.h"
#include <fstream>
#include "RedBlack.h"

using namespace std;


void AVLinsertion(int choice, int num)
{
    string path = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv";
    string path2 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_2.csv";
    string path3 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_3.csv";
    string path4 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_4.csv";
    string path5 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_5.csv";
    string path6 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_6.csv";
    string path7 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_7.csv";
    string path8 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_8.csv";
    string path9 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_9.csv";
    string path10 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_10.csv";
    int linenum = 0;

    switch (num)
    {
    case 1:
        break;
    case 2:
        path = path2;
        break;
    case 3:
        path = path3; break;
    case 4:
        path = path4; break;
    case 5:
        path = path5; break;
    case 6:
        path = path6; break;
    case 7:
        path = path7; break;
    case 8:
        path = path8; break;
    case 9:
        path = path9; break;
    case 10:
        path = path10; break;
    }
    //AVL<int,string,double> obj;
    AVL<int> temp;
    fstream f;
    f.open(path, ios::in);
    int i = 1;
    string line, strobj, cause113, cause, state;
    double deathrate = 0;
    int death = 0, id = 0, year = 0;

    getline(f, line);
    //getline(f, strobj);
    //
    while (f.peek() != EOF)
    {
        //getline(f, strobj, ',');
        //getline(f, strobj, ',');

        getline(f, line, ',');
        //cout<<line;
        id = stoi(line);
        getline(f, line, ',');
        //cout<<line;
        year = stoi(line);
        getline(f, line, ',');
        strobj = line;
        if (line[0] == '\"')
        {
            getline(f, line, '\"');
            strobj += line;
            getline(f, line, ',');
            strobj += line;
            strobj += '\"';
        }
        //cout<<" "<<strobj<<" ";
        
        cause113 = strobj;
        //getline(f, strobj, '\"');


        getline(f, line, ',');
        //getline(f, strobj, ',');
        cause = line;
        getline(f, line, ',');
        //getline(f, strobj, ',');

        state = line;
        getline(f, line, ',');
        //getline(f, strobj, ',');
        //cout<<" "<<line;
        death = stoi(line);
        getline(f, line, '\n');
        //getline(f, strobj, '\n');

        deathrate = stod(line);

        temp.insertNode(id, year, cause113, cause, state, death, deathrate);
        /*std::cout << "\nid : " << id;
        std::cout << "\nyears : " << year;
        std::cout << "\ncause113 : " << cause113;
        std::cout << "\ncause : " << cause;
        std::cout << "\nstate: " << state;
        std::cout << "\ndeaths : " << death;
        std::cout << "\ndeathrate : " << deathrate;*/

        //obj.insertNode(id,year,cause113,cause,state,death,deathrate,1);

    }
    f.close();
    // inputs until it finds a comma

    //    can be used to store objects until a comma is reached

    //i++;
    //cout<<endl<<temp.root->data.ID<<endl;
    //temp.levelOrder();

    /*fstream f;
   / f.open("AVLfiles/AVL.dat", ios::out);*/
    temp.AVLprint(temp.root);
    //  readAVL(num);
     // temp.delNode(5);

  // --------------------------------------------------------------------------------------------\\
      Range Search, Point Search and Delete point and range functions

    cout << "\n---------------------------------------\n";
    cout << "Functionality Menu" << endl;
    cout << "---------------------------------------\n";
    int opt = 0;
    do
    {
        cout << "1- Point Search\n2- Range Search\n3- Point Update\n4- Point Delete\n";
        cout << "Select your choice( 1~4 ) : ";
        cin >> opt;
    } while (opt < 1 and opt>4);
    int idnum = 0, idnum2 = 0;
    node<int>* t2;
    switch (opt)
    {
    case 1:
        cout << "Enter the ID you want to search: ";
        cin >> idnum;
        t2 = temp.retrieve(idnum);
        cout << endl << t2->data << " " << t2->year << " \"" << t2->cause113 << "\" " << t2->cause << " " << t2->state << " " << t2->death << " " << t2->deathrate << endl;
        break;
    case 2:
        cout << "Enter the Lower Range: ";
        cin >> idnum;
        cout << "Enter the Upper Range: ";
        cin >> idnum2;
        while (idnum != (idnum2 + 1))
        {
            t2 = temp.retrieve(idnum);
            cout << endl << t2->data << " " << t2->year << " " << t2->cause113 << " " << t2->cause << " " << t2->state << " " << t2->death << " " << t2->deathrate << endl;
            idnum++;
        }
        break;
    case 3:
        cout << "Enter the ID you want to update: ";
        cin >> idnum;
        if (temp.retrieve(idnum))
        {
            temp.delNode(idnum);
            cout << "Enter new ID : ";
            cin >> id;
            cout << "Enter year: ";
            cin >> year;
            cout << "Enter Cause113: ";
            cin >> cause113;
            cout << "Enter cause: ";
            cin >> cause;
            cout << "Enter state: ";
            cin >> state;
            cout << "Enter deaths: ";
            cin >> death;
            cout << "Enter deathrate: ";
            cin >> deathrate;
            temp.insertNode(id, year, cause113, cause, state, death, deathrate);
            cout << "New node has been created" << endl;
            t2 = temp.retrieve(id);
            cout << endl << t2->data << " " << t2->year << " " << t2->cause113 << " " << t2->cause << " " << t2->state << " " << t2->death << " " << t2->deathrate << endl;
        }
        else {
            cout << "node not found" << endl;
        }
        break;
    case 4:
        cout << "Enter the ID you want to Delete: ";
        cin >> idnum;
        temp.delNode(idnum);
        break;
    }


}

void RBinsertion(int choice, int num)
{
    string path = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv";
    string path2 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_2.csv";
    string path3 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_3.csv";
    string path4 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_4.csv";
    string path5 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_5.csv";
    string path6 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_6.csv";
    string path7 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_7.csv";
    string path8 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_8.csv";
    string path9 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_9.csv";
    string path10 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_10.csv";
    int linenum = 0;

    switch (num)
    {
    case 1:
        break;
    case 2:
        path = path2;
        break;
    case 3:
        path = path3; break;
    case 4:
        path = path4; break;
    case 5:
        path = path5; break;
    case 6:
        path = path6; break;
    case 7:
        path = path7; break;
    case 8:
        path = path8; break;
    case 9:
        path = path9; break;
    case 10:
        path = path10; break;
    }
    //AVL<int,string,double> obj;
    RedBlack<int> temp;
    fstream f;
    f.open(path, ios::in);
    int i = 1;
    string line, strobj, cause113, cause, state;
    double deathrate = 0;
    int death = 0, id = 0, year = 0;

    getline(f, line);
    //getline(f, strobj);
    //
    while (f.peek() != EOF)
    {
        //getline(f, strobj, ',');
        //getline(f, strobj, ',');

        getline(f, line, ',');
        //cout<<line;
        id = stoi(line);
        getline(f, line, ',');
        //cout<<line;
        year = stoi(line);
        getline(f, line, ',');
        strobj = line;
        if (line[0] == '\"')
        {
            getline(f, line, '\"');
            strobj += line;
            getline(f, line, ',');
            strobj += line;
            strobj += '\"';
        }
        
        //cout<<" "<<strobj<<" ";
        cause113 = strobj;
        //getline(f, strobj, '\"');


        getline(f, line, ',');
        //getline(f, strobj, ',');
        cause = line;
        getline(f, line, ',');
        //getline(f, strobj, ',');

        state = line;
        getline(f, line, ',');
        //getline(f, strobj, ',');
        //cout<<" "<<line;
        death = stoi(line);
        getline(f, line, '\n');
        //getline(f, strobj, '\n');

        deathrate = stod(line);

        temp.insertNode(id, year, cause113, cause, state, death, deathrate);

        
        /*std::cout << "\nid : " << id;
        std::cout << "\nyears : " << year;
        std::cout << "\ncause113 : " << cause113;
        std::cout << "\ncause : " << cause;
        std::cout << "\nstate: " << state;
        std::cout << "\ndeaths : " << death;
        std::cout << "\ndeathrate : " << deathrate;*/
        

        //obj.insertNode(id,year,cause113,cause,state,death,deathrate,1);

    }
    f.close();

    // inputs until it finds a comma

    //    can be used to store objects until a comma is reached

    i++;
    //cout<<endl<<temp.root->data.ID<<endl;
    //temp.levelOrder();

    temp.RBprint(temp.root);
    //readRB(num);

    // --------------------------------------------------------------------------------------------\\
    Range Search, Point Search and Delete point and range functions

    cout << "\n---------------------------------------\n";
    cout << "Functionality Menu" << endl;
    cout << "---------------------------------------\n";
    int opt = 0;
    do
    {
        cout << "1- Point Search\n2- Range Search\n3- Point Update\n4- Point Delete\n";
        cout << "Select your choice( 1~4 ) : ";
        cin >> opt;
    } while (opt < 1 and opt>4);
    int idnum = 0, idnum2 = 0;
    node<int>* t2;
    switch (opt)
    {
    case 1:
        cout << "Enter the ID you want to search: ";
        cin >> idnum;
        t2 = temp.retrieve(idnum);
        cout << endl << t2->data << " " << t2->year << " \"" << t2->cause113 << "\" " << t2->cause << " " << t2->state << " " << t2->death << " " << t2->deathrate << endl;
        break;
    case 2:
        cout << "Enter the Lower Range: ";
        cin >> idnum;
        cout << "Enter the Upper Range: ";
        cin >> idnum2;
        while (idnum != (idnum2 + 1))
        {
            t2 = temp.retrieve(idnum);
            cout << endl << t2->data << " " << t2->year << " " << t2->cause113 << " " << t2->cause << " " << t2->state << " " << t2->death << " " << t2->deathrate << endl;
            idnum++;
        }
        break;
    case 3:
        cout << "Enter the ID you want to update: ";
        cin >> idnum;
        if (temp.retrieve(idnum))
        {
            temp.delNode(idnum);
            cout << "Enter new ID : ";
            cin >> id;
            cout << "Enter year: ";
            cin >> year;
            cout << "Enter Cause113: ";
            cin >> cause113;
            cout << "Enter cause: ";
            cin >> cause;
            cout << "Enter state: ";
            cin >> state;
            cout << "Enter deaths: ";
            cin >> death;
            cout << "Enter deathrate: ";
            cin >> deathrate;
            temp.insertNode(id, year, cause113, cause, state, death, deathrate);
            cout << "New node has been created" << endl;
            t2 = temp.retrieve(id);
            cout << endl << t2->data << " " << t2->year << " " << t2->cause113 << " " << t2->cause << " " << t2->state << " " << t2->death << " " << t2->deathrate << endl;
        }
        else {
            cout << "node not found" << endl;
        }

        break;
    case 4:
        cout << "Enter the ID you want to Delete: ";
        cin >> idnum;
        temp.delNode(idnum);

        break;
    }

}


void BTreeinsertion(int choice, int num)
{
    string path = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv";
    string path2 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_2.csv";
    string path3 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_3.csv";
    string path4 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_4.csv";
    string path5 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_5.csv";
    string path6 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_6.csv";
    string path7 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_7.csv";
    string path8 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_8.csv";
    string path9 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_9.csv";
    string path10 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_10.csv";
    int linenum = 0;

    switch (num)
    {
    case 1:
        break;
    case 2:
        path = path2;
        break;
    case 3:
        path = path3; break;
    case 4:
        path = path4; break;
    case 5:
        path = path5; break;
    case 6:
        path = path6; break;
    case 7:
        path = path7; break;
    case 8:
        path = path8; break;
    case 9:
        path = path9; break;
    case 10:
        path = path10; break;
    }
    //AVL<int,string,double> obj;
    Btree<int, string, double> btree;
    fstream f;
    f.open(path, ios::in);
    int i = 1;
    string line, strobj, cause113, cause, state;
    double deathrate = 0;
    int death = 0, id = 0, year = 0;

    getline(f, line);
    //getline(f, strobj);
    //
    while (f.peek() != EOF)
    {
        //getline(f, strobj, ',');
        //getline(f, strobj, ',');

        getline(f, line, ',');
        //cout<<line;
        id = stoi(line);
        getline(f, line, ',');
        //cout<<line;
        year = stoi(line);
        getline(f, line, ',');
        strobj = line;
        if (line[0] == '\"')
        {
            getline(f, line, '\"');
            strobj += line;
            getline(f, line, ',');
            strobj += line;
            strobj += '\"';
        }
        
        //cout<<" "<<strobj<<" ";
        cause113 = strobj;
        //getline(f, strobj, '\"');


        getline(f, line, ',');
        //getline(f, strobj, ',');
        cause = line;
        getline(f, line, ',');
        //getline(f, strobj, ',');

        state = line;
        getline(f, line, ',');
        //getline(f, strobj, ',');
        //cout<<" "<<line;
        death = stoi(line);
        getline(f, line, '\n');
        //getline(f, strobj, '\n');

        deathrate = stod(line);

        btree.insert(id, year, cause113, cause, state, death, deathrate);
        /*std::cout << "\nid : " << id;
        std::cout << "\nyears : " << year;
        std::cout << "\ncause113 : " << cause113;
        std::cout << "\ncause : " << cause;
        std::cout << "\nstate: " << state;
        std::cout << "\ndeaths : " << death;
        std::cout << "\ndeathrate : " << deathrate;*/

        //obj.insertNode(id,year,cause113,cause,state,death,deathrate,1);

    }
    f.close();
    // inputs until it finds a comma

    //    can be used to store objects until a comma is reached

    //i++;
    //cout<<endl<<temp.root->data.ID<<endl;
    //temp.levelOrder();

    /*fstream f;
   / f.open("AVLfiles/AVL.dat", ios::out);*/

   //  readAVL(num);
    // temp.delNode(5);

 // --------------------------------------------------------------------------------------------\\
      Range Search, Point Search and Delete point and range functions

    cout << "\n---------------------------------------\n";
    cout << "Functionality Menu" << endl;
    cout << "---------------------------------------\n";
    int opt = 0;
    int oldId = 0;
    do
    {
        cout << "1- Point Search\n2- Range Search\n3- Point Update\n";
        cout << "Select your choice( 1~4 ) : ";
        cin >> opt;
    } while (opt < 1 and opt>3);
    int idnum = 0, idnum2 = 0;
    Bnode<int, string, double>* t2;
    switch (opt)
    {
    case 1:
        cout << "Enter the ID you want to search: ";
        cin >> idnum;
        t2 = btree.seek(idnum);
        // cout << endl << t2->data << " " << t2->year << " \"" << t2->cause113 << "\" " << t2->cause << " " << t2->state << " " << t2->death << " " << t2->deathrate << endl;
        break;
    case 2:
        cout << "Enter the Lower Range: ";
        cin >> idnum;
        cout << "Enter the Upper Range: ";
        cin >> idnum2;
        while (idnum != (idnum2 + 1))
        {
            t2 = btree.seek(idnum);
            //  cout << endl << t2->data << " " << t2->year << " " << t2->cause113 << " " << t2->cause << " " << t2->state << " " << t2->death << " " << t2->deathrate << endl;
            idnum++;
        }
        break;
    case 3:
        cout << "Enter the ID you want to update: ";
        cin >> oldId;
        if (oldId > 0)
        {
            cout << "Enter new ID : ";
            cin >> id;
            cout << "Enter year: ";
            cin >> year;
            cout << "Enter Cause113: ";
            cin >> cause113;
            cout << "Enter cause: ";
            cin >> cause;
            cout << "Enter state: ";
            cin >> state;
            cout << "Enter deaths: ";
            cin >> death;
            cout << "Enter deathrate: ";
            cin >> deathrate;

            // t2 = btree.seek(oldId);
            t2 = btree.update(oldId, id, year, cause113, cause, state, death, deathrate, 1);
            t2 = btree.seek(oldId);
            t2 = btree.seek(id);

        }
        else {
            cout << "node not found" << endl;
        }
        break;
    }


}





int main()
{

    bool esc = 1;
    cout << "\n______________________________________________________________________________________\n"
        << "\nData Structures project created by:\n1. Ahmad Hassan (21I-0403)\n2. Faraz Rashid (21I-0659)"
        << "\n______________________________________________________________________________________\n\n\n";

    while (esc)
    {
        string path;
        int option = 0, choice = 0;
        path = "";
        /*
        int linenum;
        cout << "\nEnter the path of file: ";
        cin >> path;
        cout << "\nEnter line you want to open: ";
        cin >> linenum;*/

        cout << "1 -> AVL trees\n2 -> RedBlack Trees\n3-> B-trees\n";
        cout << "\nSelect you choice of trees for indexing: (1~3)\t";
        std::cin >> option;
        cout << "\n1 -> id\n2 -> year\n3 -> Cause113\n4 -> Cause\n5 -> State\n6 -> Deaths\n7 -> DeathRate\n\nAlert! \aFor now it only indexes on IDS\n ";
        cout << "\nSelect the option to index the tree on: (1~7):\t";
        std::cin >> choice;
        int num = 0;
        switch (option)
        {
        case 1:
            //int num = 0;
            do {
                cout << "Enter the number of file you want to open   (1~10) : ";
                cin >> num;
            } while (num < 1 && num > 10);
            AVLinsertion(choice, num);

            break;
        case 2:
            //int num = 0;
            do {
                cout << "Enter the number of file you want to open   (1~10) : ";
                cin >> num;
            } while (num < 1 && num > 10);
            RBinsertion(choice, num);
            break;
        case 3:
            do {
                cout << "Enter the number of file you want to open   (1~10) : ";
                cin >> num;
            } while (num < 1 && num > 10);
            BTreeinsertion(choice, num);
            break;
        }

        cout << "\nEnter 1 to continue || 0 to exit\n";
        std::cin >> esc;
    }
    cout << "\n :) Good Bye (: \n";


    //AVL<int,string,double> avl;
    //avl.insertNode(9, 2006, "bruhe de momente", "bruhe de momente 2", "Alabama", 132, 123.21, 1);
    //avl.insertNode(2, 2006, "bruhe de momente", "bruhe de momente 2", "Alabama", 132, 123.21, 1);
    //avl.insertNode(5, 2006, "bruhe de momente", "bruhe de momente 2", "Alabama", 132, 123.21, 1);
    //avl.insertNode(10, 2006, "bruhe de momente", "bruhe de momente 2", "Alabama", 132, 123.21, 1);
    //avl.insertNode(3, 2006, "bruhe de momente", "bruhe de momente 2", "Alabama", 132, 123.21, 1);
    //avl.insertNode(6, 2006, "bruhe de momente", "bruhe de momente 2", "Alabama", 132, 123.21, 1);
    //avl.insertNode(7, 2006, "bruhe de momente", "bruhe de momente 2", "Alabama", 132, 123.21, 1);
    //avl.insertNode(8, 2006, "bruhe de momente", "bruhe de momente 2", "Alabama", 132, 123.21, 1);
    //avl.insertNode(1, 2006, "bruhe de momente", "bruhe de momente 2", "Alabama", 132, 123.21, 1);
    //avl.insertNode(4, 2006, "bruhe de momente", "bruhe de momente 2", "Alabama", 132, 123.21, 1);
    //    
    //avl.levelOrder();


    return 0;
}
