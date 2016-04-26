#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;
//we will write functions to obtain file (building off previous code) and to probe
//we will write extraction purposes inside mainfile that involves converting our file to type string, locating the specific numbers we
//wish to use, and converting them back to an integer so we can thus compare better for collisions
bool getFile (char* filepath, int *& my_array);
bool quadratic_probing(int key, int *&hash_list, int M);


//getFile function to get file from a certain path
bool getFile (char* filepath, int *& my_array)
{
    if(my_array!=NULL) delete my_array;
    my_array = new int[65000];                   //creates integer array to place our file into
    char lineData[50];
    int number;
    ifstream in;
    in.open(filepath);                        //opens file
    if(!in.is_open())
    {
        cout << "I cannot find the file.\n";
        return false;
    }
    int i=0;
    while(in.peek()!=EOF)
    {
        in.getline(lineData,50,' ');
        number=atoi(lineData);
        my_array[i]=number;
        i++;
    }
    in.clear();
    in.close();
    return true;
}

//this is our quadratic probing function
bool quadratic_probing(int key, int *&hash_list, int M)
{
    int key_remains = key % 65000; //first we need to make sure our key is in the right range of values
    int position = key_remains+1; //next we set ur position
    int j=1;
    while (hash_list[position]!=0)
    {
        position = (position + j^2) % M; //if our bucket is filled, we have to find a new one. this should find an empty value
        j++;
    }
    return true;
}

int main ()
{
    //im guessing we choose 45 million because we know its greater than 9*10!, which is the total possibilities for SSN
    int rand;
    ofstream out;
    out.open("hashed_socials.txt");
    cout <<"Please enter in a number between 1 and 45 million"<<endl;
    cin >> rand;
    if (rand >0 && rand<45000000)
    {
        cout <<"Thank you for the proper entry!"<<endl;
    }
    else
    {
        cout <<"Please try again:"<<endl;
        cin >> rand;
    }
    int *social_security_list = NULL;   //set up where we read info into
    getFile ("everybodys_socials.txt", social_security_list);
    int *hash_list = new int[65000];      //set up table to hash to
    for (int i=0; i<65000; i++)
    {
        hash_list[i]=0;     //initialize hash table to 0
    }
    string *conversion_hash_string = new string [65000];
    for (int j=0; j<65000; j++)
    {
        string my, social, security, number;
        string convert = to_string(social_security_list[j]); //this converts each social securtiy number to string so we can inspect it
        my = convert[2]; //this denotes third number
        social = convert[4];
        security = convert[6];
        number = convert [7];
        convert = my + social + security + number;
        //this is essentially our hashing action
        //put these hashed values into a string array
        conversion_hash_string[j]= convert;
        //put each element of string array to int at given address
        int key = stoi(conversion_hash_string[j]);
        if (hash_list[key]==0)
        {
            hash_list[key]= social_security_list[j];
        }
        else
        {
            cout<< "We have a collision. Time to probe"<< endl;
            quadratic_probing(key, hash_list, rand);
        }

    }
    for (int z=0;z<65000; z++)
    {
        out<< social_security_list[z]<<  "is stored at" << hash_list[z];
    }
    out.close();

}
