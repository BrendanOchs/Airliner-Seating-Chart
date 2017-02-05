//********************************************************************************
//*                                                                              *
//* PROGRAM FILE NAME: Program1.cpp  ASSIGNMENT#: 1         GRADE: _________     *
//*                                                                              *
//* PROGRAM AUTHOR:________________________________________________              *
//*                                 Brendan Ochs                                 *
//*                                                                              *
//* COURSE#: CSC 36000 SEC 11           DUE DATE: January 20th, 2017             *
//*                                                                              *
//********************************************************************************

//*****************************PROGRAM DESCRIPTION********************************
//*                                                                              *
//*  Purpose: This program is designed to read in any number of inputs from and  *
//*           incoming data file containing passenger boarding information.      *
//*           This program is designed to create a seating chart for 8 Southern  *
//*           Comfort Airline flights. There will be data from an input file and *
//*           entries will be processed one at a time. A waiting list for each   *
//*           of the 8 flights will also be created. The finished seating charts *
//*           will display the assigned boarding number for each person. The     *
//*           waiting list corresponding to each seating chart will also be      *
//*           printed out.
//*                                                                              *
//*  USER DEFINED                                                                *
//*  MODULES     :                                                               *
//*               Header       - Prints the output preamble.
//*               BuildSeating - Place empty passenger number into array seats.  *
//*               convertFlight- Convert the flight number into an index.        *
//*               convertColumn- Convert the column letter into an index.        *
//*               searchOne    - Search for the specific seat.                   *
//*               searchTwo    - Search for an empty seat in the row from        *
//*                              left to right.                                  *
//*               searchThree  - Search the column for the farthest forward seat.*
//*               searchFour   - search all seats in requested section until     *
//*                              an empty seat is found.                         *
//*               printChart   - Print out the specified seating chart.          *
//*               Footer       - Prints the output salutation.                   *
//*                                                                              *
//********************************************************************************

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct PassengerType
{
    int boardNum=0;
    int flightNum=0;
    string sec;
    int row=0;
    string col;
    int flight=0;
    int column=0;
};

struct WaitType
{
    int One=0;
    int Two=0;
    int Three=0;
    int Four=0;
    int Five=0;
    int Six=0;
    int Seven=0;
    int Eight=0;
    
};
//*********************************Prototypes*******************************************
void buildSeating(int [8][10][3]);
void convertFlight(PassengerType &);
void convertRow(PassengerType &);
void convertColumn(PassengerType &);
void searchOne(int [8][10][3], bool & , PassengerType);
void searchTwo(int [8][10][3], bool & , PassengerType);
void searchThree(int [8][10][3], bool &, PassengerType);
void searchFour(int [8][10][3], bool &, PassengerType);
void printChart(ofstream &, int [8][10][3],int);
void Header( ofstream &);
void Footer(ofstream &);


//**************************************************************************************
int main()
{
        // Create an inoput stream for an incoming passenger file containing entries
    ifstream input ("data1.txt",ios::in);
        // Create and output stream for the finished seating chart
    ofstream output ("SeatingChart.txt",ios::out);
        // Create the array for the seating chart
    int Chart[8][10][3]={0};
        // Create the array for the waiting list
    int Wait[8][30]={0};
        // Build the initial seating chart
    buildSeating(Chart);
        // Create a program stopper
    bool go=true;
        // Create a passenger used for all incoming passengers
    PassengerType passenger;
        // Create a variable for searching
    bool searchAgain=false;
        // Create a wait for Waitlist count of all flight numbers
    WaitType wait;
    
    
    Header(output);
    while(go)
    {
        input >> passenger.boardNum;
            if(passenger.boardNum==-999)
            {
                go=false;
            }
            else
            {
                input >> passenger.flightNum;
                input >> passenger.sec;
                input >> passenger.row;
                input >> passenger.col;
                convertFlight(passenger);
                convertColumn(passenger);
                convertRow(passenger);
                    // Rule 1 part 1 search
                searchOne(Chart,searchAgain,passenger);
                if(searchAgain)
                {
                        // Rule 1 part 2 search
                    searchTwo(Chart,searchAgain,passenger);
                }
                if(searchAgain)
                {
                        // Rule 2
                    searchThree(Chart, searchAgain, passenger);
                }
                if(searchAgain)
                {
                    searchFour(Chart,searchAgain,passenger);
                }
                if(searchAgain)
                {
                    if(passenger.flight==0)
                        Wait[passenger.flight][wait.One++]=passenger.boardNum;
                    if(passenger.flight==1)
                        Wait[passenger.flight][wait.Two++]=passenger.boardNum;
                    if(passenger.flight==2)
                        Wait[passenger.flight][wait.Three++]=passenger.boardNum;
                    if(passenger.flight==3)
                        Wait[passenger.flight][wait.Four++]=passenger.boardNum;
                    if(passenger.flight==4)
                        Wait[passenger.flight][wait.Five++]=passenger.boardNum;
                    if(passenger.flight==5)
                        Wait[passenger.flight][wait.Six++]=passenger.boardNum;
                    if(passenger.flight==6)
                        Wait[passenger.flight][wait.Seven++]=passenger.boardNum;
                    if(passenger.flight==7)
                        Wait[passenger.flight][wait.Eight++]=passenger.boardNum;
                    
                }
                
            }
       
    }
    
    for(int i=0;i<8;i++)
    {
        if(i==0)
        {
            output << setw(40) << "SOUTHERN COMFORT AIRLINES" << endl << endl;
            output << "Flight 1010" << "             " << "FROM: Jackson, Mississippi" << endl;
            output << "                        " << "TO: Memphis, Tennessee" << endl << endl;
            
            printChart(output, Chart, i);
            output << endl;
            output << "WAITING LIST" << endl << endl;
            if(wait.One<1)
            {
                output << "THERE IS NO WAITING LIST" << endl << endl;
            }
            else
            {
                int next=0;
                for(int i=0;i<wait.One;i++)
                {
                    output << Wait[0][i] << "   ";
                    next++;
                    if(next==10)
                    {
                        output << endl;
                        next=0;
                    }
                }
                output << endl;
            }
        }
        if(i==1)
        {
            output << setw(40) << "SOUTHERN COMFORT AIRLINES" << endl << endl;
            output << "Flight 1015" << "             " << "FROM: Memphis, Tennessee" << endl;
            output << "                        " << "TO: Jackson. Mississippi" << endl << endl;
            
            printChart(output, Chart, i);
            output << endl;
            output << "WAITING LIST" << endl << endl;
            if(wait.Two<1)
            {
               output << "THERE IS NO WAITING LIST" << endl << endl;
            }
            else
            {
                int next=0;
                for(int i=0;i<wait.Two;i++)
                {
                    output << Wait[1][i] << "   ";
                    next++;
                    if(next==10)
                    {
                        output << endl;
                        next=0;
                    }
                }
                output << endl;
            }

        }
        if(i==2)
        {
            output << setw(40) << "SOUTHERN COMFORT AIRLINES" << endl << endl;
            output << "Flight 1020" << "             " << "FROM: Jackson, Mississippi" << endl;
            output << "                        " << "TO: Little Rock, Arkansas" << endl << endl;
            
            printChart(output, Chart, i);
            output << endl;
            output << "WAITING LIST" << endl << endl;
            if(wait.Three<1)
            {
               output << "THERE IS NO WAITING LIST" << endl << endl;
            }
            else
            {
                int next=0;
                for(int i=0;i<wait.Three;i++)
                {
                    output << Wait[2][i] << "   ";
                    next++;
                    if(next==10)
                    {
                        output << endl;
                        next=0;
                    }
                }
                output << endl;
            }

        }
        if(i==3)
        {
            output << setw(40) << "SOUTHERN COMFORT AIRLINES" << endl << endl;
            output << "Flight 1025" << "             " << "FROM: Little Rock, Arkansas" << endl;
            output << "                        " << "TO: Jackson. Mississippi" << endl << endl;
            
            printChart(output, Chart, i);
            output << endl;
            output << "WAITING LIST" << endl << endl;
            if(wait.Four<1)
            {
                output << "THERE IS NO WAITING LIST" << endl << endl;
                
            }
            else
            {
                int next=0;
                for(int i=0;i<wait.Four;i++)
                {
                    output << Wait[3][i] << "   ";
                    next++;
                    if(next==10)
                    {
                        output << endl;
                        next=0;
                    }
                }
                output << endl;
            }

        }
        if(i==4)
        {
            output << setw(40) << "SOUTHERN COMFORT AIRLINES" << endl << endl;
            output << "Flight 1030" << "             " << "FROM: Jackson, Mississippi" << endl;
            output << "                        " << "TO: Shreveport, Louisiana" << endl << endl;
            
            printChart(output, Chart, i);
            output << endl;
            output << "WAITING LIST" << endl << endl;
            if(wait.Five<1)
            {
                output << "THERE IS NO WAITING LIST" << endl << endl;
            }
            else
            {
                int next=0;
                for(int i=0;i<wait.Five;i++)
                {
                    output << Wait[4][i] << "   ";
                    next++;
                    if(next==10)
                    {
                        output << endl;
                        next=0;
                    }
                }
                output << endl;
            }

        }
        if(i==5)
        {
            output << setw(40) << "SOUTHERN COMFORT AIRLINES" << endl << endl;
            output << "Flight 1035" << "             " << "FROM: Shreveport, Louisiana" << endl;
            output << "                        " << "TO: Jackson, Mississippi" << endl << endl;
            
            printChart(output, Chart, i);
            output << endl;
            output << "WAITING LIST" << endl << endl;
            if(wait.Six<1)
            {
                output << "THERE IS NO WAITING LIST" << endl << endl;
            }
            else
            {
                int next=0;
                for(int i=0;i<wait.Six;i++)
                {
                    output << Wait[5][i] << "   ";
                    next++;
                    if(next==10)
                    {
                        output << endl;
                        next=0;
                    }
                }
                output << endl;
            }

        }
        if(i==6)
        {
            output << setw(40) << "SOUTHERN COMFORT AIRLINES" << endl << endl;
            output << "Flight 1040" << "             " << "FROM: Jackson, Mississippi" << endl;
            output << "                        " << "TO: Orlando, Florida" << endl << endl;
            
            printChart(output, Chart, i);
            output << endl;
            output << "WAITING LIST" << endl << endl;
            if(wait.Seven<1)
            {
                output << "THERE IS NO WAITING LIST" << endl << endl;
            }
            else
            {
                int next=0;
                for(int i=0;i<wait.Seven;i++)
                {
                    output << Wait[6][i] << "   ";
                    next++;
                    if(next==10)
                    {
                        output << endl;
                        next=0;
                    }
                }
                output << endl;
            }

        }
        if(i==7)
        {
            output << setw(40) << "SOUTHERN COMFORT AIRLINES" << endl << endl;
            output << "Flight 1045" << "             " << "FROM: Orlando, Florida" << endl;
            output << "                        " << "TO: Jackson, Mississippi" << endl << endl;
            
            printChart(output, Chart, i);
            output << endl;
            output << "WAITING LIST" << endl << endl;
            if(wait.Eight<1)
            {
                output << "THERE IS NO WAITING LIST" << endl << endl;
            }
            else
            {
                int next=0;
                for(int i=0;i<wait.Eight;i++)
                {
                    output << Wait[7][i] << "   ";
                    next++;
                    if(next==10)
                    {
                        output << endl;
                        next=0;
                    }
                }
                output << endl;
            }

        }
    }
   
    
    Footer(output);
    return 0;
}

//************************************FUNCTIONS*****************************************

void buildSeating(int Chart[8][10][3])
{
        // Receives- Chart array
        // Task    - put empty passenger numbers into array
        // Returns - populated Chart array
    for(int i=0; i<8; i++)
        for(int j=0; j<10; j++)
            for(int k=0; k<3; k++)
            {
                Chart[i][j][k]=-999;
            }
}

void convertRow(PassengerType & passenger)
{
    passenger.row-=1;
}

void convertFlight(PassengerType & passenger)
{
        // Receives- Passenger
        // Task    - Convert the flight number into an index for use in the Chart array
        // Returns - Passenger
    if (passenger.flightNum==1010)
        passenger.flight=0;
    if (passenger.flightNum==1015)
        passenger.flight=1;
    if (passenger.flightNum==1020)
        passenger.flight=2;
    if (passenger.flightNum==1025)
        passenger.flight=3;
    if (passenger.flightNum==1030)
        passenger.flight=4;
    if (passenger.flightNum==1035)
        passenger.flight=5;
    if (passenger.flightNum==1040)
        passenger.flight=6;
    if (passenger.flightNum==1045)
        passenger.flight=7;
}
void convertColumn(PassengerType & passenger)
{
        // Receives- passenger
        // Task    - Convert the column letter into an index for use in the Chart array
        // Returns - passenger
    if (passenger.col=="L")
        passenger.column=0;
    if (passenger.col=="M")
        passenger.column=1;
    if (passenger.col=="R")
        passenger.column=2;
}

void searchOne(int Chart[8][10][3], bool & searchAgain, PassengerType passenger)
{
        // Receives- Chart array, searchAgain, passenger
        // Task    - Search for the specific seat and place them in the spot
        // Returns - Chart, searchAgain
    if (Chart[passenger.flight][passenger.row][passenger.column]==-999)
        Chart[passenger.flight][passenger.row][passenger.column]=passenger.boardNum;
    else
    {
        searchAgain=true;
    }
}


void searchTwo(int Chart[8][10][3], bool & searchAgain, PassengerType passenger)
{
        // Receives- Chart array, searchAgain, passenger
        // Task    - Search for an empty seat in the row from left to right
        //           place the passenger in the first available seat
        // Returns - Chart array, searchAgain
    for(int i=0; i<3; i++)
    {
        if(Chart[passenger.flight][passenger.row][i]==-999)
        {
            Chart[passenger.flight][passenger.row][i]=passenger.boardNum;
            passenger.column=i;
            searchAgain=false;
            return;
        }
        else
        {
            searchAgain=true;
        }
    }
}

void searchThree(int Chart[8][10][3], bool & searchAgain, PassengerType passenger)
{
        // Receives- Chart array, searchAgain, passenger
        // Task    - search the column for the farthest forward seat
        //           places the passenger in the seat
        // returns - Chart array, searchAgain
    if (passenger.sec=="F")
    {
        for (int i=0; i<3; i++)
            if(Chart[passenger.flight][i][passenger.column]==-999)
            {
                Chart[passenger.flight][i][passenger.column]=passenger.boardNum;
                passenger.row=i;
                searchAgain=false;
                return;
            }
            else
            {
                searchAgain=true;
            }
    }
    if (passenger.sec=="C")
    {
        for (int i=3; i<10; i++)
            if(Chart[passenger.flight][i][passenger.column]==-999)
            {
                Chart[passenger.flight][i][passenger.column]=passenger.boardNum;
                passenger.row=i;
                searchAgain=false;
                return;
            }
            else
            {
                searchAgain=true;
            }
    }
}


void searchFour(int Chart[8][10][3], bool & searchAgain, PassengerType passenger)
{
        // Receives- Chart array, searchAgain, passenger
        // Task    - search all seats in requested section until and empty seat is found
        //           place passenger in empty seat
        // Returns - Chart array, searchAgain
    if(passenger.sec=="F")
    {
            //row
        for(int i=0;i<3;i++)
            //col
            for(int j=0;j<3;j++)
                if(Chart[passenger.flight][i][j]==-999)
                {
                    Chart[passenger.flight][i][j]=passenger.boardNum;
                    passenger.row=i;
                    passenger.col=j;
                    searchAgain=false;
                    return;
                }
                else
                {
                    searchAgain=true;
                }
    }
    if(passenger.sec=="C")
    {
        //row
        for(int i=3;i<10;i++)
            //col
            for(int j=0;j<3;j++)
                if(Chart[passenger.flight][i][j]==-999)
                {
                    Chart[passenger.flight][i][j]=passenger.boardNum;
                    passenger.row=i;
                    passenger.col=j;
                    searchAgain=false;
                    return;
                }
                else
                {
                    searchAgain=true;
                }
    }
    
    
    
}


void printChart(ofstream & output, int Chart[8][10][3], int which)
{
        // Receives- Output file, Chart array, which
        // Task    - Print out the specified seating chart
        // Returns - Output file, Chart array
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<3;j++)
        {
            output << Chart[which][i][j] << "    ";
        }
        output << endl;
    }
    
    
    
}


//********************************** HEADER & FOOTER ****************************************
//*******************************************************************************************

void Header( ofstream &outFile)
{
    // Receives- output file
    // Task    - prints the output preamble
    // Returns - nothing
    outFile << setw(30) << "Brendan Ochs";
    outFile << setw(17) << "CSC 36000";
    outFile << setw(15) << "Section 11" << endl;
    outFile << setw(30) << "Spring 2017";
    outFile << setw(20) << "Assignment #1" << endl;
    outFile << setw(35) << "-----------------------------------";
    outFile << setw(35) << "-----------------------------------" << endl << endl;
    return;
}

//***************************************FOOTER*******************************************
//****************************************************************************************

void Footer(ofstream &outFile)
{
    // Receives- the output file
    // Task    - prints the output salutation
    // Returns - nothing
    outFile << endl;
    outFile << setw(35) << "---------------------------------" << endl;
    outFile << setw(35) << "|------END OF PROGRAM OUTPUT-------|" << endl;
    outFile << setw(35) << "---------------------------------" << endl;
    
    return;
}










