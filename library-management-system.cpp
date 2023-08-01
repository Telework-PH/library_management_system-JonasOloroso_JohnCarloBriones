#include <conio.h>
#include <bits/stdc++.h>

using namespace std;

void header(){
	cout << "\t\t  _______________________________________________________________  " << endl;
	cout << "\t\t[]                                                               []" << endl;
	cout << "\t\t[][][][][][][][][][] Library Management System [][][][][][][][][][]" << endl;
	cout << "\t\t[]                                                               []" << endl;
	cout << "\t\t[]_______________________________________________________________[]" << endl;
}

void choose(int* l, int s, int e, bool* valid){// unified function for getting user input for choices
	string chs;
	*valid = true;
	getline(cin>>ws,chs);

	if(chs == "-1"){
		*l = stoi(chs);
	}else{
		for(char c: chs)
			if(!isdigit(c)){
				cout << "\t\t\tInvalid input" << endl;
				*valid = false; break;
			}
		if(*valid){
			if(stoi(chs) >= s and stoi(chs) <= e){
				*l = stoi(chs);
			}else{
				cout << "\t\t\tInvalid input" << endl;
				*valid = false;
			}
		}

	}
}

bool ids(long* v){ // Function for getting user input for IDs (search ID/set ID)
	string id;
	getline(cin>>ws,id);
	for(char c: id)
		if(!isdigit(c)){
			cout << "\t\tInvalid input" << endl;
			return false;
		}
	if(id.at(0) == '-'){
		cout << "\t\tInvalid input" << endl;
		return false;
	}
	*v = stoul(id);
	return true;
}

const int monthDays[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
int countLeapYearDays(int d[]){ // check if the year is a leap year
   int years = d[2];
   if (d[1] <= 2)
      years--;
   return ( (years / 4) - (years / 100) + (years / 400) );
}
int countNoOfDays(int date1[], int date2[]){ // counts the number of days between two dates
   long int dayCount1 = (date1[2] * 365);
   dayCount1 += monthDays[date1[1]];
   dayCount1 += date1[0];
   dayCount1 += countLeapYearDays(date1);
   long int dayCount2 = (date2[2] * 365);
   dayCount2 += monthDays[date2[1]];
   dayCount2 += date2[0];
   dayCount2 += countLeapYearDays(date2);
   return ( abs(dayCount1 - dayCount2) );
}

struct BookPatron{ // will be the set data_type/variables for Books and Patrons
	long ID;
	string titleName;
	string authorEmail;
	string publisherContact;
	string statusAddress;

};
struct CheckOut{ // will be the set data_type/variables for checkout and returns
	long bID;
	long pID;
	string date;
	string status;
	string retDate = "0";
};

vector<string> alphabaticallySort(vector<string> a){ // function that sorts the lists alphabetically
	sort(a.begin(),a.end());
	return a;
}
string toLower(string search){ // converts characters into lowercases for mainly for better searching
	string temp = "";
	for(char c: search) temp += (c >= 65 and c <= 90 ? c+32 : c);
	return temp;
}

// functions for importing(get) data from bookFile.txt/patronFile.txt and exporting(set) data to them
void getFile(vector<BookPatron>* bookpatron,int i){
	BookPatron bk;
	fstream bpFile;
	if(i==1){ bpFile.open("bookFile.txt",ios::in);}
	else if(i==2){ bpFile.open("patronFile.txt",ios::in);}
	if(bpFile.is_open()){
		string print;
		int pos=0;
		while(getline(bpFile,print)){
			pos++;
			if(pos==1 and print.length() != 0) bk.ID = stoul(print);
			if(pos==2 and print.length() != 0) bk.titleName = print;
			if(pos==3 and print.length() != 0) bk.authorEmail = print;
			if(pos==4 and print.length() != 0) bk.publisherContact = print;
			if(pos==5 and print.length() != 0) {bk.statusAddress = print; (*bookpatron).push_back(bk);}

			if(print.length() == 0) pos =0 ;
		}
		bpFile.close();
	}
}
void setFile(vector<BookPatron>* bp,int i){
	fstream bpFl;
	if(i == 1) bpFl.open("bookFile.txt",ios::out);
	else if(i == 2) bpFl.open("patronFile.txt",ios::out);
	if(bpFl.is_open()){
		for(auto b : *bp){
			fstream bpF;
			if(i == 1) bpF.open("bookFile.txt",ios::app);
			else if(i == 2) bpF.open("patronFile.txt",ios::app);
			bpF<<b.ID<<"\n";
			bpF<<b.titleName<<"\n";
			bpF<<b.authorEmail<<"\n";
			bpF<<b.publisherContact<<"\n";
			bpF<<b.statusAddress<<"\n\n";
			bpF.close();
		}
	}
}
// functions for importing(get) data from checkoutFile.txt and exporting(set) data to it
void getFileC(vector<CheckOut>* checkout){
	CheckOut co;
	fstream coFile;
	coFile.open("checkoutFile.txt",ios::in);
	if(coFile.is_open()){
		string print;
		int pos=0;
		while(getline(coFile,print)){
			pos++;
			if(pos==1 and print.length() != 0) co.bID = stoul(print);
			if(pos==2 and print.length() != 0) co.pID = stoul(print);
			if(pos==3 and print.length() != 0) co.date = print;
			if(pos==4 and print.length() != 0) co.status = print;
			if(pos==5 and print.length() != 0) {co.retDate = print; (*checkout).push_back(co);}

			if(print.length() == 0) pos =0 ;
		}
		coFile.close();
	}
}
void setFileC(vector<CheckOut>* checkout){
	fstream cFl;
	cFl.open("checkoutFile.txt",ios::out);
	if(cFl.is_open()){
		for(auto c : *checkout){
			fstream coF;
			coF.open("checkoutFile.txt",ios::app);
			coF<<c.bID<<"\n";
			coF<<c.pID<<"\n";
			coF<<c.date<<"\n";
			coF<<c.status<<"\n";
			coF<<c.retDate<<"\n\n";
			coF.close();
		}
	}
}
// functions for importing(get) data from loginFile.txt and exporting(set) data to it
void getFilel(vector<string>* logins){
	fstream liFile;
	liFile.open("loginFile.txt",ios::in);
	if(liFile.is_open()){
		string print;
		while(getline(liFile,print)){
			(*logins).push_back(print);
		}
		liFile.close();
	}
}
void setFilel(vector<string>* logins){
	fstream lFl;
	lFl.open("loginFile.txt",ios::out);
	if(lFl.is_open()){
		for(auto l : *logins){
			fstream lFl;
			lFl.open("loginFile.txt",ios::app);
			lFl<<l<<"\n";
			lFl.close();
		}
	}
}

// function that mainly displays the list/information of either Books or Patrons
void displayInfosBookPatron(BookPatron bookpatron,int i,int z){
	cout << left << setw(68) << setfill('-') << "\t\t*"; cout << "*" << endl;
	cout << "\t\t| ID       : " << left << setw(53) << setfill(' ') << bookpatron.ID; cout << "|" << endl;
	int s;
	if(i==1){
		s = bookpatron.titleName.length();
		if(s > 52){
			cout << "\t\t| Title    : " << left << setw(53) << setfill(' ') << bookpatron.titleName.substr(0,51)+"-";  cout << "|" << endl;
			cout << "\t\t|            " << left << setw(53) << setfill(' ') << bookpatron.titleName.substr(51,(s-1));  cout << "|" << endl;
		} else{ cout << "\t\t| Title    : " << left << setw(53) << setfill(' ') << bookpatron.titleName;  cout << "|" << endl;}
		cout << "\t\t| Author   : " << left << setw(53) << setfill(' ') << bookpatron.authorEmail;  cout << "|" << endl;
		cout << "\t\t| Publisher: " << left << setw(53) << setfill(' ') << bookpatron.publisherContact;  cout << "|" << endl;
		if(z==1){
			cout << "\t\t| Status   : " << left << setw(53) << setfill(' ') << bookpatron.statusAddress;  cout << "|" << endl;
		}
	}
	if(i==2){
		cout << "\t\t| Name     : " << left << setw(53) << setfill(' ') << bookpatron.titleName;  cout << "|" << endl;
	    cout << "\t\t| Email    : " << left << setw(53) << setfill(' ') << bookpatron.authorEmail;  cout << "|" << endl;
	    cout << "\t\t| Contact  : " << left << setw(53) << setfill(' ') << bookpatron.publisherContact;  cout << "|" << endl;
		s = bookpatron.statusAddress.length();
		if(s > 52){
			cout << "\t\t| Address  : " << left << setw(53) << setfill(' ') << bookpatron.statusAddress.substr(0,51)+"-";  cout << "|" << endl;
			cout << "\t\t|            " << left << setw(53) << setfill(' ') << bookpatron.statusAddress.substr(51,(s-1));  cout << "|" << endl;
		}else{ cout << "\t\t| Address  : " << left << setw(53) << setfill(' ') << bookpatron.statusAddress;  cout << "|" << endl;}
	}
	cout << left << setw(68) << setfill('-') << "\t\t*"; cout << "*" << endl;
}
bool searching(string s,string m){
	m = toLower(m);
	bool match = 0;
	int ms = m.size();
	for(int i = 0; i <= (int)(s.size())-ms; i++){
		if(s.substr(i,ms)==m){
			match = 1;
		}
	}
	return match;
}


void addB(vector<BookPatron>* bkPt, int i){
	system("CLS");
	header();
	if(i==1) cout << "\t\tHOME > MANAGE BOOK > ADD BOOK" << endl << endl;
	if(i==2) cout << "\t\tHOME > MANAGE PATRON > ADD PATRON" << endl << endl;
	getFile(bkPt,i);
	bool isExisting = false, valid = false;
	BookPatron add;
	while(!valid){ cout << "\t\tID: "; valid = ids(&add.ID); }
	valid = false;
	if(i == 1) cout << "\t\tTitle: ";
	else if(i == 2) cout << "\t\tName: ";
	getline(cin>>ws,add.titleName);
	if(i == 1) cout << "\t\tAuthor: ";
	else if(i == 2) cout << "\t\tEmail: ";
	getline(cin>>ws,add.authorEmail);
	if(i == 1) cout << "\t\tPublisher: ";
	else if(i == 2)	cout << "\t\tContact: ";
	getline(cin>>ws,add.publisherContact);
	if(i == 1) add.statusAddress = "Available";
	else if(i == 2){ cout << "\t\tAddress: ";
		getline(cin>>ws,add.statusAddress);}
	for(int z = 0; z < (int)((*bkPt).size()); z++){
		if(add.ID == (*bkPt)[z].ID){
			isExisting = true;
			if(i==1) cout << "\t\tBook with this ID Already Exist!" << endl;
			if(i==2) cout << "\t\tPatron with this ID Already Exist!" << endl;
		}
		if(add.titleName == (*bkPt)[z].titleName && add.authorEmail == (*bkPt)[z].authorEmail){
			isExisting = true;
			if(i==1) cout << "\t\tBook Title with this Author Already Exist!" << endl;
			if(i==2) cout << "\t\tPatron Name with this Email Already Exist!" << endl;
		}
	}
	if(!isExisting){
		displayInfosBookPatron(add,i,0);
		cout << "\t\tAre you sure you want to add this?" << endl;
		cout << "\t\t1: Confirm | 2: Cancel" << endl;
		int c;
		while(!valid){ cout << "\t\t> "; choose(&c,1,2,&valid);}
		if(c==1){
			(*bkPt).push_back(add);
			if(i==1) cout << endl << "\t\tBook successfully added!" << endl << endl;
			if(i==2) cout << endl << "\t\tPatron successfully added!" << endl << endl;
		}
		else if(c==2) goto BACKADD;
	}
	setFile(bkPt,i);
	BACKADD:
	(*bkPt).clear();
	cout << "\t\t"; system("PAUSE");
}
void searchB(vector<BookPatron>* bkPt, int i){
	system("CLS");
	header();
	if(i==1) cout << "\t\tHOME > MANAGE BOOK > SEARCH BOOK" << endl << endl;
	if(i==2) cout << "\t\tHOME > MANAGE PATRON > SEARCH PATRON" << endl << endl;
	getFile(bkPt,i);
	cout << "\t\tSearch: ";
	string search;
	int pos = -1;
	getline(cin>>ws,search);
	for(auto a : *bkPt){
		bool id=0, tn=0, an=0, pc=0, sa=0;
		search = toLower(search);
		id = searching(to_string(a.ID),search);
		tn = searching(toLower(a.titleName),search);
		an = searching(toLower(a.authorEmail),search);
		pc = searching(toLower(a.publisherContact),search);
		sa = searching(toLower(a.statusAddress),search);
		if(tn or an or pc or id or sa){
			displayInfosBookPatron(a,i,1);
			pos = 1;
		}
	}
	if(pos == -1){
		if(i==1) cout << endl << "\t\tBook with this information did not exist!" << endl << endl;
		if(i==2) cout << endl << "\t\tPatron with this information did not exist!" << endl << endl;
	}
	(*bkPt).clear();
	cout << "\t\t"; system("PAUSE");
}
void updateB(vector<BookPatron>* bkPt, vector<CheckOut>* checkout, int i){
	system("CLS");
	header();
	if(i==1) cout << "\t\tHOME > MANAGE BOOK > UPDATE BOOK" << endl << endl;
	if(i==2) cout << "\t\tHOME > MANAGE PATRON > UPDATE PATRON" << endl << endl;
	getFile(bkPt,i);
	getFileC(checkout);
	BookPatron update;
	bool isExisting=false, valid = false,isSame = false, isCheckedOut = false;
	long idd,pos = 0;
	while(!valid){
		if(i==1) cout << "\t\tEnter Book ID to Update: ";
		if(i==2) cout << "\t\tEnter Patron ID to Update: ";
		valid = ids(&idd);
	}valid = false;
	for(auto a : *bkPt){
		if(a.ID == idd){
			isExisting = true;
			for(auto b: *checkout){
				if(i==1){
					if(idd == b.bID and b.status == "Checked-out"){
						isCheckedOut = true;
						cout << "\n\t\tSorry! You cannot update this book when it's currently checked out." << endl << endl;
						break;
					}
				}
				else if(i==2){
					if(idd == b.pID and b.status == "Checked-out"){
						isCheckedOut = true;
						cout << "\n\t\tSorry! You cannot update this patron when it's currently have an on-going check out." << endl << endl;
						break;
					}
				}
			}
			if(!isCheckedOut){
				displayInfosBookPatron(a,i,0);
				valid = false;
				while(!valid){cout << "\t\tID: "; valid = ids(&update.ID);}
				if(i == 1) cout << "\t\tTitle: ";
				else if(i == 2) cout << "\t\tName: ";
				getline(cin>>ws,update.titleName);
				if(i == 1) cout << "\t\tAuthor: ";
				else if(i == 2) cout << "\t\tEmail: ";
				getline(cin>>ws,update.authorEmail);
				if(i == 1) cout << "\t\tPublisher: ";
				else if(i == 2)	cout << "\t\tContact: ";
				getline(cin>>ws,update.publisherContact);
				if(i == 2){ cout << "\t\tAddress: ";
					getline(cin>>ws,update.statusAddress);}
				for(int z = 0; z < (int)(*bkPt).size(); z++){
					if(pos != z and (update.ID == (*bkPt)[z].ID or (update.titleName == (*bkPt)[z].titleName and
					update.authorEmail == (*bkPt)[z].authorEmail))){
						if(i == 1) cout << "\n\t\tBook information already exist" << endl << endl;
						if(i == 2) cout << "\n\t\tPatron information already exist" << endl << endl;
						isSame = true;
					}
				}
			}
			break;
		}
		pos++;
	}
	if(isExisting and !isSame and !isCheckedOut){
		int confirm;
		cout << "\t\tAre you sure you want to update the information?" << endl;
		cout << "\t\t1: Confirm | 2: Cancel" << endl;
		valid = 0;
		while(!valid){ cout << "\t\t> "; choose(&confirm,1,2,&valid);}
		if(confirm == 1){
			(*bkPt)[pos].ID = update.ID;
			(*bkPt)[pos].titleName = update.titleName;
			(*bkPt)[pos].authorEmail = update.authorEmail;
			(*bkPt)[pos].publisherContact = update.publisherContact;
			if(i==2) (*bkPt)[pos].statusAddress = update.statusAddress;
			cout << "\n\t\tUpdated Successfully!" << endl << endl;
			setFile(bkPt,i);
		}else goto BACKUPDATE;
	}
	if(!isExisting){
		if(i == 1) cout << "\n\t\tBook did not exist!" << endl << endl;
		if(i == 2) cout << "\n\t\tPatron did not exist!" << endl << endl;
	}
	BACKUPDATE:
	(*bkPt).clear();(*checkout).clear();
	cout <<"\t\t"; system("PAUSE");
}
void deleteB(vector<BookPatron>* bkPt, vector<CheckOut>* checkout, int i){
	system("CLS");
	header();
	if(i==1) cout << "\t\tHOME > MANAGE BOOK > DELETE BOOK" << endl << endl;
	if(i==2) cout << "\t\tHOME > MANAGE PATRON > DELETE PATRON" << endl << endl;
	getFile(bkPt,i);
	getFileC(checkout);
	bool isExisting = false, valid = false,isCheckedOut = false;
	long idd,pos = 0;
	while(!valid){
		if(i==1) cout << "\t\tEnter Book ID to Delete: ";
		if(i==2) cout << "\t\tEnter Patron ID to Delete: ";
		valid = ids(&idd);
	}
	valid = false;
	for(auto a : *bkPt){
		if(a.ID == idd){
			isExisting = true;
			displayInfosBookPatron(a,i,1);
			for(auto b: *checkout){
				if(i==1){
					if(idd == b.bID and b.status == "Checked-out"){
						isCheckedOut = true;
						cout << "\n\t\tSorry! You cannot delete this book when it's currently checked out." << endl << endl;
						break;
					}
				}
				else if(i==2){
					if(idd == b.pID and b.status == "Checked-out"){
						isCheckedOut = true;
						cout << "\n\t\tSorry! You cannot delete this patron when it's currently have an on-going check out." << endl << endl;
						break;
					}
				}
			}
			break;
		}
		pos++;
	}
	if(isExisting and !isCheckedOut){
		if(i==1)cout << "\n\t\tAre you sure you want to delete this book?" << endl;
		if(i==2)cout << "\n\t\tAre you sure you want to delete this patron?" << endl;
		cout << "\t\t1: Confirm | 2: Cancel" << endl;
		int confirm;
		while(!valid){cout << "\t\t> "; choose(&confirm,1,2,&valid);}
		if(confirm == 1){
			(*bkPt).erase((*bkPt).begin()+pos);
			cout << "\t\tSuccessfully deleted!" << endl;
		}else if(confirm == 2) goto BACKDELETE;
	}
	if(!isExisting)
		cout << endl << "\t\tBook did not exist!" << endl << endl;
	setFile(bkPt,i);
	BACKDELETE:
	(*bkPt).clear(); (*checkout).clear();
	cout << "\t\t"; system("PAUSE");
}
void displayB(vector<BookPatron>* bkPt, int i){
	getFile(bkPt,i);
	while(true){
		system("CLS");
		header();
		if(i==1)cout << "\t\tHOME > MANAGE BOOK > DISPLAY BOOKS" << endl << endl;
		if(i==2)cout << "\t\tHOME > MANAGE PATRON > DISPLAY PATRONS" << endl << endl;
		if((*bkPt).empty()){
			if(i==1)cout << "\t\tNo books found..." << endl << endl;
			if(i==2)cout << "\t\tNo patron found..." << endl << endl;
		}
		else{
			for(auto b : *bkPt){
				displayInfosBookPatron(b,1,1);
			}
		}
		int s,ss;
		if(!(*bkPt).empty()){
			bool valid = false;
			cout << "\n\t\t1: Sort\n\t\t2: Continue" << endl;
			while(!valid){ cout <<"\t\t> "; choose(&s,1,2,&valid);}
			valid = false;
			if(s == 1){
				cout << "\t\tSort by:" << endl;
				cout << "\t\t1: ID\n\t\t2: Title" << endl;
				while(!valid){ cout << "\t\t> "; choose(&ss,1,2,&valid);}
				if(ss==1){
					for(int i = 0; i < (int)(*bkPt).size();i++)
						for(int j = 0; j < (int)(*bkPt).size()-1; j++)
							if((*bkPt)[j].ID > (*bkPt)[j+1].ID)
								swap((*bkPt)[j],(*bkPt)[j+1]);
				}
				else if(ss==2){
					vector<string> s;
					vector<BookPatron> temp;
					for(auto a : (*bkPt)){
						s.push_back(toLower(a.titleName));
					}
					s = alphabaticallySort(s);
					for(int i = 0; i < (int)(s.size()); i++)
						for(int j = 0; j < (int)(s.size()); j++)
							if(s[i] == (*bkPt)[j].titleName)
								temp.push_back((*bkPt)[j]);
					(*bkPt).clear();
					for(auto en : temp) (*bkPt).push_back(en);
				}
			}else break;
		}else break;
	}
	(*bkPt).clear();
	cout << "\t\t"; system("PAUSE");
}

void manageBookPatron(vector<BookPatron>* bkPt, vector<CheckOut>* checkout, int i){
	while(true){
		system("CLS");
		header();
		if(i==1) cout << "\t\tHOME > MANAGE BOOK" << endl << endl;
		if(i==2) cout << "\t\tHOME > MANAGE PATRON" << endl << endl;
		cout << "\t\t\t 1: Add" << endl;
		cout << "\t\t\t 2: Search" << endl;
		cout << "\t\t\t 3: Update" << endl;
		cout << "\t\t\t 4: Delete" << endl;
		cout << "\t\t\t 5: Display" << endl;
		cout << "\t\t\t 0: Back " << endl;
		cout << "\t\t\t-1: Exit" << endl;
		int j;
		bool valid = false;
		while(!valid){
			cout << "\t\t\t> "; choose(&j,-1,5,&valid);
		}
		if(j == 1) addB(bkPt,i);
		if(j == 2) searchB(bkPt,i);
		if(j == 3) updateB(bkPt,checkout,i);
		if(j == 4) deleteB(bkPt,checkout,i);
		if(j == 5) displayB(bkPt,i);
		if(j == 0) break;
		if(j == -1) exit(0);
	}
}


void checkOut(vector<CheckOut>* checkret,vector<BookPatron>* bk,vector<BookPatron>* pt, int cdate[]){
	system("CLS");
	header();
	cout << "\t\tHOME > MANAGE CHECK-OUT/RETURNS > CHECK-OUT" << endl << endl;
	getFile(bk,1);
	getFile(pt,2);
	getFileC(checkret);
	int bpos = -1, ppos = -1,c;
	bool isExisting = false,isBook = false, isPatron = false, valid = false;
	CheckOut add;
	while(true){
		while(!valid){ cout << "\t\tBook ID: "; valid = ids(&add.bID);}
		valid = false;
		for(auto a: *bk){
			bpos++;
			if(add.bID == a.ID){
				isBook = true;
				displayInfosBookPatron(a,1,0);
				break;
			}
		}
		if(isBook){
			cout<<"\t\tConfirm if this is the book to be checked out."<<endl;
			cout<<"\t\t1: Yes\n\t\t2: No\n\t\t3: Cancel" << endl;
			while(!valid){ cout << "\t\t> "; choose(&c,1,3,&valid);}
			valid = false;
			if(c == 1) break;
			if(c == 2){ isBook = 0; continue;}
			if(c == 3){ goto BACK;}
		}
		else{
			cout << "\t\tBook not found..." << endl;
			cout << "\t\t1: Re-enter | 2: Back" << endl;
			while(!valid){ cout << "\t\t> "; choose(&c,1,2,&valid);}
			valid = false;
			if(c == 1) continue;
			if(c == 2) goto BACK;
		}
	}
	while(true){
		while(!valid){ cout << "\t\tPatron ID: "; valid = ids(&add.pID);}
		valid = false;
		for(int i = 0; i < (int)((*pt).size()); i++)
			if(add.pID == (*pt)[i].ID){
				isPatron = true; ppos = i;
			}
		if(!isPatron){
			cout << "\t\tPatron did not exist" << endl;
			cout << "\t\t1: Re-enter | 2: Back" << endl;
			while(!valid){ cout << "\t\t> "; choose(&c,1,2,&valid);}
			valid = false;
			if(c == 1) continue;
			if(c == 2) goto BACK;
		}
		if(isPatron){
			displayInfosBookPatron((*pt)[ppos],2,0);
			cout << "\t\tAre you sure this is the correct patron?" << endl;
			cout << "\t\t1: Yes\n\t\t2: No\n\t\t3: Cancel" << endl;
			while(!valid){ cout << "\t\t> "; choose(&c,1,3,&valid);}
			valid = false;
			if(c==1) break;
			else if(c==2) continue;
			else if(c==3) goto BACK;
		}
	}

	if(to_string(cdate[0]).length() == 1)
		add.date = "0"+to_string(cdate[0]);
	else add.date = to_string(cdate[0]);
	if(to_string(cdate[1]).length() == 1)
		add.date += "/0"+to_string(cdate[1]);
	else add.date += "/"+to_string(cdate[1]);
	add.date += "/"+to_string(cdate[2]);
	add.status = "Checked-out";

	for(int i = 0; i < (int)((*pt).size()); i++)
		if(add.pID == (*pt)[i].ID)
			isPatron = true;
	for(int i = 0; i < (int)((*checkret).size()); i++)
		if(add.bID == (*checkret)[i].bID and add.pID == (*checkret)[i].pID and (*checkret)[i].status == "Checked-out"){
			isExisting = true;
			cout << "\t\tThis book is currently unavailable!" << endl;
		}

	if(!isExisting and isBook and isPatron){
		(*checkret).push_back(add);
		(*bk)[bpos].statusAddress = "Unavailable";
		cout << endl << "\t\tChecked-out successfully!" << endl << endl;
		cout << endl << "\t\tPlease return book before 21 days to avoid fine." << endl << endl;
	}
	setFileC(checkret);
	setFile(bk,1);
	BACK:
	(*checkret).clear(); (*bk).clear(); (*pt).clear();
	cout << "\t\t"; system("PAUSE");

}
void returnBook(vector<CheckOut>* checkret,vector<BookPatron>* bk, int cdate[]){
	system("CLS");
	header();
	cout << "\t\tHOME > MANAGE CHECK-OUT/RETURNS > RETURN" << endl << endl;
	getFileC(checkret);
	getFile(bk,1);
	int pos = -1, confirm;
	long retID;
	bool valid = false;
	while(!valid){
		cout << "\t\tBook ID: "; valid = ids(&retID);
	}
	valid = false;
	for(auto a: *bk)
		if(a.ID == retID){
			displayInfosBookPatron(a,1,0);
			break;
		}
	cout << "\t\tAre you sure you want to return this book?" << endl;
	cout << "\t\t1: Confirm | 2: Cancel" << endl;
	while(!valid){ cout << "\t\t> "; choose(&confirm,1,2,&valid);}
	valid = false;
	if(confirm == 1){
		for(int i = 0; i < (int)((*checkret).size()); i++){
			if(retID == (*checkret)[i].bID and (*checkret)[i].status == "Checked-out")
				pos = i;
			else if(retID == (*checkret)[i].bID and (*checkret)[i].status == "Returned")
				pos = -2;
		}
	}else goto BACKRETURN;
	if(pos > -1){
		int dd = stoi((*checkret)[pos].date.substr(0,2));
		int mm = stoi((*checkret)[pos].date.substr(3,2));
		int yyyy = stoi((*checkret)[pos].date.substr(6,4));
		int date[3] = {dd,mm,yyyy};
		int days = countNoOfDays(date,cdate);
		if(to_string(cdate[0]).length() == 1)
			(*checkret)[pos].retDate = "0"+to_string(cdate[0]);
		else (*checkret)[pos].retDate = to_string(cdate[0]);
		if(to_string(cdate[1]).length() == 1)
			(*checkret)[pos].retDate += "/0"+to_string(cdate[1]);
		else (*checkret)[pos].retDate += "/"+to_string(cdate[1]);
		(*checkret)[pos].retDate += "/"+to_string(cdate[2]);

		if(days > 21){
			cout << "\t\tLate return fine: P15/day" << endl;
			cout << "\t\tDays Late: " << days-21 << endl;
			cout << "\t\tTotal Fine: P" << (days-21)*15 << ".00" << endl << endl;
		}
		for(int i = 0; i < (int)(*bk).size(); i++){
			if(retID == (*bk)[i].ID) (*bk)[i].statusAddress = "Available";
		}
		(*checkret)[pos].status = "Returned";
		cout << "\t\tReturned successfully!" << endl << endl;
	}
	else if(pos == -2) cout << "\t\tThis book has already been returned." << endl << endl;
	else cout << "\t\tCheck-out information did not exist." << endl << endl;

	setFileC(checkret); setFile(bk,1);
	BACKRETURN:
	(*checkret).clear();(*bk).clear();
	cout << "\t\t"; system("PAUSE");
}
void displayCheckout(vector<CheckOut>* checkret,int i){
	getFileC(checkret);
	while(true){
		system("CLS");
		header();
		if(i==1)cout << "\t\tHOME > MANAGE CHECK-OUT/RETURNS > CURRENT CHECK-OUTS" << endl << endl;
		if(i==2)cout << "\t\tHOME > MANAGE CHECK-OUT/RETURNS > CHECK-OUT HISTORY" << endl << endl;
		bool valid = false, notEmpty = false;
		if(!(*checkret).empty()){
			for(auto c : *checkret){
				if(i==1){
					if(c.status == "Checked-out"){
						cout << left << setw(68) << setfill('_') << "\t\t " << endl;
						cout << left << setw(68) << setfill(' ') << "\t\t|"; cout << "|" << endl;
						cout << "\t\t| Book ID       : " << left << setw(48) << setfill(' ') << c.bID; cout << "|" << endl;
						cout << "\t\t| Patron ID     : " << left << setw(48) << setfill(' ') << c.pID; cout << "|" << endl;
						cout << "\t\t| Check-out Date: " << left << setw(48) << setfill(' ') << c.date; cout << "|" << endl;
						cout << left << setw(68) << setfill('_') << "\t\t|";
						cout << "|"<< endl << endl;
						notEmpty = true;
					}else continue;
				}
				if(i == 2){
					cout << left << setw(68) << setfill('_') << "\t\t " << endl;
					cout << left << setw(68) << setfill(' ') << "\t\t|"; cout << "|" << endl;
					cout << "\t\t| Book ID       : " << left << setw(48) << setfill(' ') << c.bID; cout << "|" << endl;
					cout << "\t\t| Patron ID     : " << left << setw(48) << setfill(' ') << c.pID; cout << "|" << endl;
					cout << "\t\t| Check-out Date: " << left << setw(48) << setfill(' ') << c.date; cout << "|" << endl;
					cout << "\t\t| Status        : " << left << setw(48) << setfill(' ') << c.status; cout << "|" << endl;
					if(c.status == "Returned")
					{cout << "\t\t| Return Date   : " << left << setw(48) << setfill(' ') << c.retDate; cout << "|" << endl;}
					cout << left << setw(68) << setfill('_') << "\t\t|";
					cout << "|"<< endl << endl;
					notEmpty = true;
				}
			}
		}
		if(!notEmpty or (*checkret).empty()) cout << "\t\tNo on-going check-out found..." << endl << endl;
		int s,ss;
		if(!(*checkret).empty() and notEmpty){
			cout << "\n\t\t1: Sort\n\t\t2: Continue" << endl;
			while(!valid){ cout <<"\t\t> "; choose(&s,1,2,&valid);}
			valid = false;
			if(s == 1){
				cout << "\t\tSort by:" << endl;
				cout << "\t\t1: Book ID\n\t\t2: Patron ID\n\t\t3: Date" << endl;
				while(!valid){ cout <<"\t\t> "; choose(&ss,1,3,&valid);}
				if(ss==1){
					for(int i = 0; i < (int)(*checkret).size();i++)
						for(int j = 0; j < (int)(*checkret).size()-1; j++)
							if((*checkret)[j].bID > (*checkret)[j+1].bID)
								swap((*checkret)[j],(*checkret)[j+1]);
				}
				else if(ss==2){
					for(int i = 0; i < (int)(*checkret).size();i++)
						for(int j = 0; j < (int)(*checkret).size()-1; j++)
							if((*checkret)[j].pID > (*checkret)[j+1].pID)
								swap((*checkret)[j],(*checkret)[j+1]);
				}else if(ss==3){
					vector<int> d;
					for(auto a : *checkret){
						int x = 10000 * stoi(a.date.substr(6,4));
						x += 100 * stoi(a.date.substr(3,2));
						x += stoi(a.date.substr(0,2));
						d.push_back(x);
					}
					for(int i = 0; i < (int)(d.size()); i++)
						for(int j = 0; j < (int)(d.size())-1; j++)
							if(d[j] > d[j+1]){
								swap(d[j],d[j+1]);
								swap((*checkret)[j],(*checkret)[j+1]);
							}
					system("PAUSE");
				}
			}else break;
		}
		else break;
	}
	(*checkret).clear();
	cout << "\t\t"; system("PAUSE");
}

void manageCheckRet(vector<CheckOut>* checkret,vector<BookPatron>* bk,vector<BookPatron>* pt, int cdate[]){
	while(true){
		system("CLS");
		header();
		cout << "\t\tHOME > MANAGE CHECK-OUT/RETURNS" << endl << endl;
		cout << "\t\t\t 1: Check-out" << endl;
		cout << "\t\t\t 2: Return" << endl;
		cout << "\t\t\t 3: Current Check-outs" << endl;
		cout << "\t\t\t 4: Check-out History" << endl;
		cout << "\t\t\t 0: Back " << endl;
		cout << "\t\t\t-1: Exit" << endl;
		int j; bool valid = false;
		while(!valid){
			cout << "\t\t\t> "; choose(&j,-1,4,&valid);
		}
		if(j == 1) checkOut(checkret,bk,pt,cdate);
		else if(j == 2) returnBook(checkret,bk,cdate);
		else if(j == 3) displayCheckout(checkret,1);
		else if(j == 4) displayCheckout(checkret,2);
		else if(j == 0) break;
		else if(j == -1) exit(0);
	}
}

//function for entering password by masking the input
 //function for entering password by masking the input
void enterPassword(string* pass){
	char ch;
	ch = _getch();
	while(ch != 13){
		if(ch == 8){
			if((*pass).size() !=0){
				cout << "\b \b";
				(*pass).pop_back();
			}
		}
		else{
			(*pass).push_back(ch);
			cout << '*';
		}
		ch = _getch();
		if(ch == 10) break;
	}
}

void changepass(int* confirm, bool* valid){
	cout << "\n\t\t\tAre you sure you want to change password?" << endl;
	cout << "\t\t\t1: Confirm | 2: Cancel" << endl;
	while(!(*valid)){ cout << "\t\t\t> "; choose(confirm,1,2,valid);}
}

void login(vector<string>* logins, string dt){
	getFilel(logins);
	int repeat = 0;
	while(true){
		repeat++;
		system("CLS");
		header();
		int confirm;
		bool valid = 0;
		cout << endl << "\t\t                               LOGIN" << endl << endl;
		string pass = "", newP = "";
		if((*logins).empty()) {
			string retrive;
			cout << "\t\t\tSet password: "; enterPassword(&pass);
			cout << "\n\t\t\tEnter an information in case you forgot your password\n\t\t\t> ";
			getline(cin>>ws,retrive);
			cout << "\n\t\t\t1: Confirm | 2: Re-enter" << endl;
			while(!valid) {cout << "\t\t\t> "; choose(&confirm,1,2,&valid);}
			valid = false;
			if(confirm==1){
				cout << "\t\t\tPassword has been set!" << endl;
				(*logins).push_back(pass);
				(*logins).push_back(retrive);
				cout << "\t\t\t"; system("PAUSE");
				break;
			}
			else if(confirm==2) continue;
		}
		else{
			cout << "\t\t\tEnter password: "; enterPassword(&pass);
			if(pass == (*logins)[0]) break;
			else cout << endl << endl << "\t\t\tACCESS DENIED!!" << endl << endl;
			if(repeat >= 3){
				cout << "\t\t\tForgot password?" << endl;
				cout << "\t\t\t1: Yes | 2: Re-enter | 3: Exit" << endl;
				while(!valid) {cout << "\t\t\t> "; choose(&confirm,1,3,&valid);}
				valid = 0;
				if(confirm==1){
					string ret;
					cout << "\t\t\tEnter retrival data: "; getline(cin>>ws,ret);
					if(ret == (*logins)[1]){
						cout << "\n\t\t\tNew Password: "; enterPassword(&newP);
						changepass(&confirm,&valid);
						if(confirm==1){
							cout << "\n\t\t\tPassword successfuly changed!" << endl;
							(*logins)[0] = newP;
						}
					}else{
						cout << "\t\t\tIncorrect information..." << endl;
					}
				}
				else if(confirm==2) continue;
				else exit(0);
			}
			cout << "\t\t\t"; system("PAUSE");
		}

	}
	(*logins).push_back(dt);
	setFilel(logins);
	(*logins).clear();
}
void loginsettings(vector<string>* logins){
	getFilel(logins);
	while(true){
		BACKLOG:
		system("CLS");
		header();
		cout << "\t\tHOME > LOGIN SETTINGS" << endl << endl;
		cout << "\t\t\t 1: Change Password" << endl;
		cout << "\t\t\t 2: Login History" << endl;
		cout << "\t\t\t 3: Reset Login Settings" << endl;
		cout << "\t\t\t 0: Back " << endl;
		cout << "\t\t\t-1: Exit" << endl;
		int j; bool valid = false;
		while(!valid){ cout << "\t\t\t> "; choose(&j,-1,3,&valid);}
		valid = false;
		if(j == 1){
			int confirm;
			while(true){
				string oldP="",newP="";
				system("CLS");
				header();
				cout << "\t\tHOME > LOGIN SETTINGS > CHANGE PASSWORD" << endl << endl;
				cout << "\t\t\tCurrent Password : "; enterPassword(&oldP);
				cout << "\n\t\t\tNew Password     : "; enterPassword(&newP);
				if(oldP == (*logins)[0]){
					if(oldP != newP){
						changepass(&confirm,&valid);
						valid = false;
						if(confirm==1){
							(*logins)[0] = newP;
							cout << "\n\t\t\tPassword changed successfully!" << endl << endl << "\t\t\t";
							setFilel(logins);
							system("PAUSE");
							break;
						}else if(confirm==2) goto BACKLOG;
					}else cout << "\n\t\t\tNew password cannot be same as old password" << endl << endl;
				}else{
					cout << "\n\t\t\tIncorrect password. Try Again?" << endl;
					cout << "\t\t\t1: Yes | 2: No"<< endl;
					while(!valid){ cout << "\t\t\t> "; choose(&confirm,1,2,&valid);}
					if(confirm == 1) continue;
					else if(confirm == 2) break;
				}
				cout << "\t\t\t"; system("PAUSE");
			}
		}
		else if(j == 2){
			system("CLS");
			header();
			cout << "\t\tHOME > LOGIN SETTINGS > LOGIN HISTORY" << endl << endl;

			int q = 0;
			cout << left << setw(68) << setfill('-') << "\t\t*"; cout << "*" << endl;
			cout << "\t\t|                          LOGIN HISTORY                          |" << endl;
			for(auto a : *logins){
				if(q > 1){
					if(a.size() != 0){
						cout << "\t\t| " << left << setw(64) << setfill(' ') << a; cout << "|" << endl;
					}
				}
				q++;
			}
			cout << left << setw(68) << setfill('-') << "\t\t*"; cout << "*" << endl;
			cout << "\n\t\t"; system("PAUSE");
		}
		else if(j == 3){
            string sure;
            cout<<"\t\tThe System automatically close if you reset the LOGIN SETTING to Restart the System"<< endl;
            cout<<"\t\tAre you sure you want to reset LOGIN SETTING ?"<<endl;
            while(true){
            cout<<"\t\t1: Yes | 2: No \n\t\t> ";
            cin>>sure;
            if(sure == "1"){remove("loginFile.txt"); exit(0);}
            else if(sure == "2"){ break;}
            else {cout<<"\t\tInvalid Input.."<<endl;}}
		}
		else if(j == 0) break;
		else if(j == (-1)) exit(0);
	}
}

int main(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;
	int cdate[3] = {day,month,year};
	char* date_time = ctime(&now);
	string dt = date_time;

	vector<string> logins;
	login(&logins,dt);

	while(true){
		system("CLS");
		header();
		cout << "\t\tHOME" << endl << endl;
		vector<BookPatron> book;
		vector<BookPatron> patron;
		vector<CheckOut> checkret;

		cout << "\t\t\t1: MANAGE BOOKS" << endl;
		cout << "\t\t\t2: MANAGE PATRONS" << endl;
		cout << "\t\t\t3: CHECK-OUT/RETURNS" << endl;
		cout << "\t\t\t4: LOGIN SETTINGS" << endl;
		cout << "\t\t\t0: EXIT PROGRAM" << endl;
		int j; bool valid = false;
		while(!valid){ cout << "\t\t\t> "; choose(&j,0,4,&valid);}
		if(j == 1) manageBookPatron(&book,&checkret,1);
		if(j == 2) manageBookPatron(&patron,&checkret,2);
		if(j == 3) manageCheckRet(&checkret,&book,&patron,cdate);
		if(j == 4) loginsettings(&logins);
		if(j == 0) exit(0);
	}

	return 0;
}
