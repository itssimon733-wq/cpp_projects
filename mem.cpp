#include <iostream>
#include <sqlite3.h>
using namespace std;
int callback(void* data, int cols, char** colValues, char** colNames){
	cout <<"ID: "<<colValues[0]<<
	" |Model: "<<colValues[1]<<
	" |Year: "<<colValues[2]<<endl;
	return 0;
}
void createTable(sqlite3* db){
	const char* query = "CREATE TABLE IF NOT EXISTS cars("
						 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
						 "model TEXT NOT NULL,"
						 "year INTEGER NOT NULL);";
	char* errMsg;
	sqlite3_exec(db, query, NULL, NULL, &errMsg);
	cout <<"Database ready!"<<endl;
}
void addCar(sqlite3* db){
	string model;int year;
	
	cout <<"Model: "<<endl;getline(cin, model);
	cout <<"Year: "<<endl;cin>>year;
	cin.ignore();
	string query = "INSERT INTO cars(model, year) VALUES('"+ model +"'," +to_string(year)+");";
	char* errMsg;
	sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
	cout <<"Car added!"<<endl;
}
void viewCars(sqlite3* db){
	const char* query = "SELECT * FROM cars;";
	char* errMsg;
	sqlite3_exec(db, query, callback, NULL, &errMsg);
}
void deleteCar(sqlite3* db){
	int id;
	cout << "Enter car ID to delete: "; cin >> id;
	string query = "DELETE FROM cars WHERE id=" + to_string(id) + ";";
	char* errMsg;
	sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
	cout << "Car deleted!" << endl;
}


int main(){
	sqlite3* db;
	sqlite3_open("garage.db", &db);
	createTable(db);
	int choice;
	do{
		cout <<"\n ===GARAGE MANAGER==="<<endl;
		cout <<"1: Add a car"<<endl;
		cout <<"2: View all cars"<<endl;
		cout <<"3: Delete car"<<endl;
		cout <<"4: Exit"<<endl;
		cout <<"Choice: "<<endl;
		cin >>choice;
		cin.ignore();
		switch(choice){
			case 1: addCar(db);break;
			case 2: viewCars(db);break;
			case 3: deleteCar(db);break;
			case 4: cout <<"Goodbye...."<<endl;break;
			default: cout <<"Invalid choice!"<<endl;
			
		}
	}while(choice != 4);
	sqlite3_close(db);
	return 0;
}
