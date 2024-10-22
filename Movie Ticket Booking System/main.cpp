#include<iostream>
#include<mysql.h>
#include<mysqld_error.h>
#include<windows.h>
#include<sstream>
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "maakichu@1234";
const char* DB = "mydb";

class Seats{
private:
	int Seat[5][10]; // total seats = 50
public:
	Seats(){
		for(int i=0;i<5;i++){ // rows
			for(int j=0;j<10;j++){ // columns
				Seat[i][j] = 1; // 1 means seat is available and 0 means seat is not available
			}
		}
	}
	int getSeatStatus(int row,int seatNumber){
		if(row < 1 || row > 5 || seatNumber < 1 || seatNumber > 10){ // invalid row and seatNumber check
			return -1;
		}
		return Seat[row-1][seatNumber-1]; // array indexing starts from 0
	}
	void reserveSeat(int row,int seatNumber){
		if(row < 1 || row > 5 || seatNumber < 1 || seatNumber > 10){ // invalid row and seatNumber check
			return;
		}
		Seat[row-1][seatNumber-1] = 0; // seat is reserved
	}
	void display(){
		cout<<" "; // gap of one character for row numbers
		for(int i=0;i<10;i++){ // displaying the seat numbers(columns)
			cout<<" "<<i+1;
		}
		cout<<endl;
		
		for(int row=0;row<5;row++){
			cout<<row+1<<" "; // displaying the row numbers
			for(int col=0;col<10;col++){
				if(Seat[row][col]){ // seat is available
					cout<<"- ";
				}else{ // seat is not available
					cout<<"X ";
				}
			}
			cout<<"|"<<endl;
		}
		cout<<"-------------------------"<<endl;
	}
	
	
	void getDB(MYSQL* connection){
		string query = "SELECT RowNumber, SeatNumber, Seat FROM Ticket";
		if (mysql_query(connection, query.c_str())) { // checking for error
			cout<<"Error: "<<mysql_error(connection)<<endl;
		}
		
		MYSQL_RES* result;
		result = mysql_store_result(connection); // gets the result stored in database and assigns that to result pointer variable
		if(!result){ // if the result does not exist(contains garbage address value)
			cout<<"Error: "<<mysql_error(connection)<<endl; // printing the error
		}
		
		MYSQL_ROW row;
		while((row=mysql_fetch_row(result))){ // fetching the row from the result until the row is a valid row
			int rowNumber = atoi(row[0]); // atoi -> ascii to integer
			int seatNumber = atoi(row[1]);
			int seatStatus = atoi(row[2]);
			Seat[rowNumber-1][seatNumber-1] = seatStatus;
		}
		mysql_free_result(result); // freeing the pointer variable result
	}
};


int main() {
	Seats s;
	
	MYSQL* connection;
	connection = mysql_init(NULL);
	if(!mysql_real_connect(connection,HOST,USER,PW,DB,3306,NULL,0)){ // if connection is not established
		/*
		Here:
			Null -> means the connection pointer is not pointing to any object or any memory location as of now
			0 -> means there are no extra connections established as of now
		*/
		cout<<"Error: "<<mysql_error(connection)<<endl;
	}else{ // if connection is established successfully
		cout<<"Logged into Database!"<<endl;
	}
	Sleep(3000); // from windows.h header -> it will display the above establish status messages for 3 seconds
	
	
	// creating a table named ticket
	if (mysql_query(connection, "CREATE TABLE IF NOT EXISTS Ticket (RowNumber INT, SeatNumber INT, Seat INT)")) {
		cout << "Error: " << mysql_error(connection) << endl; // handling any kind of error which occurs while executing the query
	}
	// inserting data into the table ticket
	for(int row=1;row<=5;row++){
		for(int seatNumber=1;seatNumber<=10;seatNumber++){
			stringstream ss; // from sstream.h header
			ss<<"INSERT INTO Ticket(RowNumber,SeatNumber,Seat)" // inserting into the table
			<<"SELECT '"<<row<<"', '"<<seatNumber<<"','1'"
			<<"WHERE NOT EXISTS (SELECT * FROM Ticket WHERE RowNumber = '"<<row<<"' AND SeatNumber = '"<<seatNumber<<"')"; // to ensure data is not duplicate
			
			string insertQuery = ss.str();
			if(mysql_query(connection,insertQuery.c_str())){ // checking for errors in insertQuery(after converting it into const char*)
				cout<<"Error: "<<mysql_error(connection);
			}
		}
	}
	Sleep(3000); // displaying the error(if any) from above insertion code
	
	
	bool exit = false;
	while(!exit){ // user can use the program as many times as he wants before exiting
		system("cls"); // hides all the previous outputs and only allows the current output to be displayed
		cout<<endl;
		cout<<"Welcome To Movie Ticket Booking System"<<endl;
		cout<<"******************************************"<<endl;
		cout<<"1. Reserve A Ticket"<<endl;
		cout<<"2. Exit"<<endl;
		cout<<"Enter Your Choice: ";
		int val;
		cin>>val;
		if(val == 1){
			s.getDB(connection); // checking the seat status
			s.display(); // to display the status of all the seats in the theatre
			
			// taking input from the user
			int row,col;
			cout<<"Enter Row (1-5): ";
			cin>>row;
			cout<<"Enter Seat Number (1-10): ";
			cin>>col;
			
			// if user gives invalid input
			if (row < 1 || row > 5 || col < 1 || col > 10) {
				cout << "Invalid Row or Seat Number!" << endl;
				Sleep(3000);
				continue;
			}
 			
			int seatStatus = s.getSeatStatus(row,col); // getting the status of the seat
			if(seatStatus == -1){
				cout<<"Invalid Row or Seat Number!"<<endl;
				Sleep(3000);
				continue;
			}
			if(seatStatus == 0){
				cout<<"Sorry! The Seat is already Reserved ):"<<endl;
				Sleep(3000);
				continue;
			}
			
			// if seatStatus == 1 -> seat is available
			s.reserveSeat(row,col);
			stringstream ss;
			ss<<"UPDATE Ticket SET Seat = 0 WHERE RowNumber = "<<row<<" AND SeatNumber ="<< col; // reserving the seat
			string update = ss.str();
			if(mysql_query(connection,update.c_str())){  // checking for errors in update string variable
				cout<<"Error: "<< mysql_error(connection)<<endl;
			}
			else{
				cout<<"Seat Is Reserved Successfully in Row " <<row<<" and Seat Number "<<col<<endl;
			}
			Sleep(3000);
		}else if(val == 2){
			exit = true;
			cout<<"Thank you for using BookMyShow!"<<endl;
			Sleep(3000);
		}else{ // for input other than 1 or 2
			cout<<"Invalid Input!"<<endl;
			Sleep(3000);
		}
	}
	
	// closing the connection
	mysql_close(connection);
	return 0;
}
