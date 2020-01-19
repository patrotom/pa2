#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */
#define InitialSize 100

class CTransaction {

public:	
	char * m_Sign;
	int m_Amount;
	char * m_OPaccID;
	/*Defaultny konstruktor*/
	CTransaction ( void ) {
		m_Sign = nullptr;
		m_Amount = 0;
		m_OPaccID = nullptr;
	}
	/*Defaultny destruktor*/
	~CTransaction ( void ) {	
		if ( m_Sign != nullptr ) 	
			delete [] m_Sign;
		if ( m_OPaccID != nullptr )
			delete [] m_OPaccID;
	}
	/*Operator =*/
	CTransaction & operator = ( const CTransaction & source ) { 

    	if ( &source == this ) return (*this);

		if ( m_Sign != nullptr ) 	
			delete [] m_Sign;
    	m_Sign = new char [strlen(source.m_Sign)+1];
    	strncpy ( m_Sign, source.m_Sign, strlen(source.m_Sign)+1 );

    	if ( m_OPaccID != nullptr )
			delete [] m_OPaccID;
    	m_OPaccID = new char [strlen(source.m_OPaccID)+1];
    	strncpy ( m_OPaccID, source.m_OPaccID, strlen(source.m_OPaccID)+1 );

    	m_Amount = source.m_Amount;

    	return (*this);		
    }
};

class CAccount {

private:
	int maxSize;
	int idx;

public:	
	CTransaction * TransactionField;
	char * m_accID;
	int m_initialBalance;
	int m_actualBalance;
	/*Defaultny konstruktor*/
	CAccount ( void ) {
		idx = 0;
		TransactionField = new CTransaction[InitialSize];
		maxSize = InitialSize;
		m_accID = nullptr;
		m_initialBalance = 0;
		m_actualBalance = 0;
	}
	/*Operator =*/
	CAccount & operator = ( const CAccount & source ) { 

    	if ( &source == this ) return (*this);

    	idx = source.idx;
    	maxSize = source.maxSize;
    	m_initialBalance = source.m_initialBalance;
    	m_actualBalance = source.m_actualBalance;
    	
		if ( m_accID != nullptr )
			delete [] m_accID;
    	m_accID = new char [strlen(source.m_accID) + 1];
    	strncpy ( m_accID, source.m_accID, strlen(source.m_accID) + 1 );

		if ( TransactionField != nullptr )
			delete [] TransactionField;

    	TransactionField = new CTransaction[maxSize];
    	
    	for ( int i = 0; i < source.idx; i++ )
    		TransactionField[i] = source.TransactionField[i];

    	return (*this);		
    }
    /*Defaultny destruktor*/
	~CAccount ( void ) {

		if ( m_accID != nullptr )
			delete [] m_accID;
		if ( TransactionField != nullptr )
			delete [] TransactionField;
	}
	/*Vlozenie transakcie do pola objektov*/
	void putTransaction ( const char * signature, int amount, const char * AnotherAccount ) { 

		if ( idx >= maxSize )
			Resize();		

		TransactionField[idx].m_Sign = new char [strlen (signature) + 1];
		strncpy ( TransactionField[idx].m_Sign, signature, strlen (signature) + 1 );
		TransactionField[idx].m_Amount = amount;
		TransactionField[idx].m_OPaccID = new char [strlen (AnotherAccount) + 1];
		strncpy ( TransactionField[idx].m_OPaccID, AnotherAccount, strlen (AnotherAccount) + 1 );
		idx++;

		m_actualBalance += amount;
	}
	/*Pretazeny operator <<*/
	friend ostream & operator << ( ostream & out, const CAccount & manager ) { 
		
		out << manager.m_accID << ":" << "\n";
		out << "   " << manager.m_initialBalance << "\n";

		for ( int i = 0; i < manager.idx; i++ ) { 
			if ( manager.TransactionField[i].m_Amount < 0 ) { 
				out << " - " << abs (manager.TransactionField[i].m_Amount) 
					<< ", to: " << manager.TransactionField[i].m_OPaccID << ", sign: "
					<< manager.TransactionField[i].m_Sign << "\n";  
				}
			else { 
				out << " + " << abs (manager.TransactionField[i].m_Amount) 
					<< ", from: " << manager.TransactionField[i].m_OPaccID << ", sign: "
					<< manager.TransactionField[i].m_Sign << "\n";  	
				}
			}
			out << " = " << manager.m_actualBalance << endl;
		return out;
	}
	/*Aktualny zostatok na ucte*/
	int Balance () { 
		return m_actualBalance;
	}
	/*Vymazanie vsetkych transakcii z pola objektov*/
	void removeTransactions () { 

		if ( TransactionField != nullptr )
			delete [] TransactionField;
		idx = 0;
		maxSize = InitialSize;
		TransactionField = new CTransaction[InitialSize];
		m_initialBalance = m_actualBalance;
	}
	/*Resize pola objektov*/
	void Resize () { 
    	maxSize *= 2;
    	CTransaction * newArr = new CTransaction[maxSize]();
		for ( int i = 0; i < idx; i++ ) 
    		newArr[i] = TransactionField[i];		    	
		delete [] TransactionField;
		TransactionField = newArr;
    }
};


/*Reference counting riesit cez strukturu pre CBank na pole uctov (objektov). 
x6 (x7) -> uplatnuje sa ref. counting
x6 = x7 -> uplatnuje sa ref. counting

Objekty x7 a x6 ukazuju na to iste miesto v pamati az do casu zmeny jedneho z nich, vtedy je potrebne vytvorit pre zmeneny objekt nove miesto v pamati.
*/

class CBank {
private:

	struct CData { 
		CAccount * AccountField;
		int m_Size;
		int maxSize;
		int m_RefCnt;
		CData ( int size );
		~CData ();
	};
	CData * m_Data;
	void attach ( CData * src );
	void detach ( int newMaxSize );
public:
    /*Default constructor*/
	CBank () { 
		m_Data = new CData (InitialSize);
	}
    /*Default destructor*/
    ~CBank () { 
    	if ( --m_Data->m_RefCnt == 0 )
			delete m_Data;
    }
    /*Copy constructor*/
    CBank ( const CBank & src ) { 
    	attach ( src.m_Data );
	}
    /*Operator =*/
    CBank & operator = ( const CBank & src ) { 
    	if ( &src != this ) { 
    		if ( --m_Data->m_RefCnt == 0 )
    			delete m_Data;
    		m_Data = src.m_Data;
    		m_Data->m_RefCnt++;
    	}
    	return *this;		
    }
    /*NewAccount*/
    bool NewAccount ( const char * accID, int initialBalance ) {

    	detach ( m_Data -> maxSize );	

    	for ( int i = 0; i < m_Data->m_Size; i++ ) { 
    		if ( strcmp ( m_Data->AccountField[i].m_accID, accID ) == 0 )
    			return false;
    	}

    	if ( m_Data->m_Size >= m_Data->maxSize )
    		Resize();

    	m_Data->AccountField[m_Data->m_Size].m_accID = new char [strlen (accID) + 1];

    	strncpy ( m_Data->AccountField[m_Data->m_Size].m_accID, accID, strlen (accID) + 1 );

    	m_Data->AccountField[m_Data->m_Size].m_initialBalance = initialBalance;
    	m_Data->AccountField[m_Data->m_Size].m_actualBalance = initialBalance;
    	m_Data->m_Size++;
    	return true;
    }
    /*Transaction*/
    bool Transaction ( const char * debAccID, const char * credAccID, 
    				   int amount, const char * signature ) { 

    	int index1 = 0, index2 = 0;
    	bool ind1 = false, ind2 = false;

    	detach ( m_Data -> maxSize );

    	if ( strcmp ( debAccID, credAccID ) == 0 ) {
    		return false;
    	}

    	for ( int i = 0; i < m_Data->m_Size; i++  ) { 

    		if ( strcmp ( m_Data->AccountField[i].m_accID, debAccID ) == 0 ) { 
    			index1 = i;
    			ind1 = true;
    		}
    		if ( strcmp ( m_Data->AccountField[i].m_accID, credAccID ) == 0 ) { 
    			index2 = i;
    			ind2 = true;
    		}

    		if ( ind1 == true && ind2 == true )
    			break;
    	}

    	if ( ind1 == false || ind2 == false ) {
    		return false;
    	}

    	m_Data->AccountField[index1].putTransaction ( signature, -amount, credAccID );
    	m_Data->AccountField[index2].putTransaction ( signature, amount, debAccID );

    	return true;
    }

    /*Account*/
    CAccount & Account ( const char * accID ) { 

    	int index = 0;	
    	bool ind = false;

    	for ( int i = 0; i < m_Data->m_Size; i++ ) { 
    		if ( strcmp ( m_Data->AccountField[i].m_accID, accID ) == 0 ) { 
    			index = i;
    			ind = true;
    			break;
    		}
    	}

    	if ( ind == false )
    		throw "Account not found !";

    	return m_Data->AccountField[index];	
    }
   
	/*TrimAccount*/
    bool TrimAccount ( const char * accID ) { 
    	int index = 0;	
    	bool ind = false;

    	detach ( m_Data -> maxSize );

    	for ( int i = 0; i < m_Data->m_Size; i++ ) { 
    		if ( strcmp ( m_Data->AccountField[i].m_accID, accID ) == 0 ) { 
    			index = i;
    			ind = true;
    			break;
    		}
    	}

    	if ( ind == false )
    		return false;
    	m_Data->AccountField[index].removeTransactions();
    	return true;
    }
    /*Resize pola uctov*/
    void Resize () { 
    	m_Data->maxSize *= 2;
    	CAccount * newArr = new CAccount[m_Data->maxSize];

    	for ( int i = 0; i < m_Data->m_Size; i++ ) 
    		newArr[i] = m_Data->AccountField[i];

    	delete [] m_Data->AccountField;
    	m_Data->AccountField = newArr;
    } 	
};

/*Default constructor for CData*/
CBank::CData::CData ( int size ) { 
	AccountField = new CAccount [size];
	maxSize = InitialSize;
	m_Size = 0;
	m_RefCnt = 1;
	//for ( int i = 0; i < m_Size; i++ ) AccountField[i] = nullptr;
} 
/*Default destructor for CData*/
CBank::CData::~CData () { 
	delete [] AccountField;
}
 /*Attach method for CData*/
void CBank::attach ( CData * src ) { 
	m_Data = src;
	m_Data->m_RefCnt++;
}
/*Detach method for CData*/
void CBank::detach ( int newMaxSize ) { 

	if ( m_Data->m_RefCnt > 1 ) { 
		CData * tmp = new CData ( m_Data->maxSize );
		
		for ( int i = 0; i < m_Data->m_Size; i++ ) 
			tmp->AccountField[i] = m_Data->AccountField[i];

		tmp->m_Size = m_Data->m_Size;
		tmp->maxSize = m_Data->maxSize;

		m_Data -> m_RefCnt --;
		m_Data = tmp;
	}
}

/*--------------------------------------------------------*/
#ifndef __PROGTEST__
//#include <string>
int main ( void ) {

 	ostringstream os;
 	char accCpy[100], debCpy[100], credCpy[100], signCpy[100];
 	CBank x0;

 	/*Vlastne testovacie asserty - medzne hodnoty*/
 	/*size_t ROUNDS = 10000;
 	for (size_t i = 0; i < ROUNDS; i++) {
 		assert(x0.NewAccount(std::to_string(i).c_str(), 0));
 		os << x0.Account ( std::to_string(i).c_str() );
 		os . str ( "" );
 	}
 	std::cout << "Inserted" << std::endl;
 	for (size_t i = 0; i < ROUNDS; i++) {
 		assert((x0.Transaction(std::to_string(i).c_str(), std::to_string(ROUNDS - i - 1).c_str(), ROUNDS, std::to_string(i).c_str()) && i != ROUNDS - i - 1) || (std::cout << i << std::endl && false));
 		os << x0.Account ( std::to_string(i).c_str() );
 		os . str ( "" );
 		os << x0.Account ( std::to_string(ROUNDS - i - 1).c_str() );
 		os . str ( "" );
 	}

 	std::cout << "T1" << std::endl;
 	CBank x1 = x0 ;
 	for (size_t i = 0; i < ROUNDS; i++) {
 		assert((x1.Account(std::to_string(i).c_str()).Balance() == 0) || (std::cout << i << " " <<  x1.Account(std::to_string(i).c_str()).Balance() << std::endl && false));
 		
 	}
 	std::cout << "Copy T2" << std::endl;
 	
 	for (size_t i = 0; i < ROUNDS / 2; i++) {
 		assert((x1.Transaction(std::to_string(i).c_str(), std::to_string(ROUNDS - i - 1).c_str(), ROUNDS, std::to_string(i).c_str()) && i != ROUNDS - i - 1) || (std::cout << i << std::endl && false));
 		assert(x1.TrimAccount(std::to_string(i).c_str()));
 	}
 	std::cout << "Trim" << std::endl;
 	for (size_t i = 0; i < ROUNDS / 2; i++) {
 		if (i < ROUNDS / 2) {
 			assert((x1.Account(std::to_string(i).c_str()).Balance() == (int)-ROUNDS) || (std::cout << i << " " <<  x1.Account(std::to_string(i).c_str()).Balance() << std::endl && false));
 		} else {
 			assert((x1.Account(std::to_string(i).c_str()).Balance() == (int)ROUNDS) || (std::cout << i << " " <<  x1.Account(std::to_string(i).c_str()).Balance() << std::endl && false));
 		}
 	}
 	std::cout << "Done" << std::endl;*/

 	/***************/
  	assert ( x0 . NewAccount ( "123456", 1000 ) );
  	assert ( x0 . NewAccount ( "987654", -500 ) );
  	assert ( x0 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
  	assert ( x0 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
  	assert ( x0 . NewAccount ( "111111", 5000 ) );
  	assert ( x0 . Transaction ( "111111", "987654", 290, "Okh6e+8rAiuT5=" ) );
  	assert ( x0 . Account ( "123456" ). Balance ( ) ==  -2190 );
  	assert ( x0 . Account ( "987654" ). Balance ( ) ==  2980 );
  	assert ( x0 . Account ( "111111" ). Balance ( ) ==  4710 );
  	os . str ( "" );
  	os << x0 . Account ( "123456" );
  	assert ( ! strcmp ( os . str () . c_str (), "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n" ) );
  	os . str ( "" );
  	os << x0 . Account ( "987654" );
  	assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 290, from: 111111, sign: Okh6e+8rAiuT5=\n = 2980\n" ) );
  	os . str ( "" );
  	os << x0 . Account ( "111111" );
  	assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 290, to: 987654, sign: Okh6e+8rAiuT5=\n = 4710\n" ) );
  	assert ( x0 . TrimAccount ( "987654" ) );
  	assert ( x0 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
  	os . str ( "" );
  	os << x0 . Account ( "987654" );
  	assert ( ! strcmp ( os . str () . c_str (), "987654:\n   2980\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 3103\n" ) );
  	/***************/
	CBank x2;
	strncpy ( accCpy, "123456", sizeof ( accCpy ) );
	assert ( x2 . NewAccount ( accCpy, 1000 ));
	strncpy ( accCpy, "987654", sizeof ( accCpy ) );
	assert ( x2 . NewAccount ( "987654", -500 ));
	strncpy ( debCpy, "123456", sizeof ( debCpy ) );
	strncpy ( credCpy, "987654", sizeof ( credCpy ) );
	strncpy ( signCpy, "XAbG5uKz6E=", sizeof ( signCpy ) );
	assert ( x2 . Transaction ( debCpy, credCpy, 300, signCpy ) );
	strncpy ( debCpy, "123456", sizeof ( debCpy ) );
	strncpy ( credCpy, "987654", sizeof ( credCpy ) );
	strncpy ( signCpy, "AbG5uKz6E=", sizeof ( signCpy ) );
	assert ( x2 . Transaction ( debCpy, credCpy, 2890, signCpy ) );
	strncpy ( accCpy, "111111", sizeof ( accCpy ) );
	assert ( x2 . NewAccount ( accCpy, 5000 ));
	strncpy ( debCpy, "111111", sizeof ( debCpy ) );
	strncpy ( credCpy, "987654", sizeof ( credCpy ) );
	strncpy ( signCpy, "Okh6e+8rAiuT5=", sizeof ( signCpy ) );
	assert ( x2 . Transaction ( debCpy, credCpy, 2890, signCpy ) );
	assert ( x2 . Account ( "123456" ). Balance ( ) ==  -2190 );
	assert ( x2 . Account ( "987654" ). Balance ( ) ==  5580 );
	assert ( x2 . Account ( "111111" ). Balance ( ) ==  2110 );
	os . str ( "" );
	os << x2 . Account ( "123456" );
	assert ( ! strcmp ( os . str () . c_str (), "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n" ) );
	os . str ( "" );
	os << x2 . Account ( "987654" );
	assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n = 5580\n" ) );
	os . str ( "" );
	os << x2 . Account ( "111111" );
	assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n = 2110\n" ) );
	assert ( x2 . TrimAccount ( "987654" ) );
	strncpy ( debCpy, "111111", sizeof ( debCpy ) );
	strncpy ( credCpy, "987654", sizeof ( credCpy ) );
	strncpy ( signCpy, "asdf78wrnASDT3W", sizeof ( signCpy ) );
	assert ( x2 . Transaction ( debCpy, credCpy, 123, signCpy ) );
	os . str ( "" );
	os << x2 . Account ( "987654" );
	assert ( ! strcmp ( os . str () . c_str (), "987654:\n   5580\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n" ) );
	/***************/
	CBank x4;
	assert ( x4 . NewAccount ( "123456", 1000 ) );
	assert ( x4 . NewAccount ( "987654", -500 ) );
	assert ( !x4 . NewAccount ( "123456", 3000 ) );
	assert ( !x4 . Transaction ( "123456", "666", 100, "123nr6dfqkwbv5" ) );
	assert ( !x4 . Transaction ( "666", "123456", 100, "34dGD74JsdfKGH" ) );
	assert ( !x4 . Transaction ( "123456", "123456", 100, "Juaw7Jasdkjb5" ) );
	try
	{
	  x4 . Account ( "666" ). Balance ( );
	  assert ( "Missing exception !!" == NULL );
	}
	catch ( ... )
	{
	}
	try
	{
	  os << x4 . Account ( "666" ). Balance ( );
	  assert ( "Missing exception !!" == NULL );
	}
	catch ( ... )
	{
	}
	assert ( !x4 . TrimAccount ( "666" ) );
	/***************/
	CBank x6;
	assert ( x6 . NewAccount ( "123456", 1000 ) );
	assert ( x6 . NewAccount ( "987654", -500 ) );
	assert ( x6 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
	assert ( x6 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
	assert ( x6 . NewAccount ( "111111", 5000 ) );
	assert ( x6 . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" ) );
	CBank x7 ( x6 );
	assert ( x6 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
	assert ( x7 . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" ) );
	assert ( x6 . NewAccount ( "99999999", 7000 ) );
	assert ( x6 . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" ) );
	assert ( x6 . TrimAccount ( "111111" ) );
	assert ( x6 . Transaction ( "123456", "111111", 221, "Q23wr234ER==" ) );
	os . str ( "" );
	os << x6 . Account ( "111111" );
	assert ( ! strcmp ( os . str () . c_str (), "111111:\n   -1802\n + 221, from: 123456, sign: Q23wr234ER==\n = -1581\n" ) );
	os . str ( "" );
	os << x6 . Account ( "99999999" );
	assert ( ! strcmp ( os . str () . c_str (), "99999999:\n   7000\n + 3789, from: 111111, sign: aher5asdVsAD\n = 10789\n" ) );
	os . str ( "" );
	os << x6 . Account ( "987654" );
	assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n" ) );
	os . str ( "" );
	os << x7 . Account ( "111111" );
	assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n" ) );
	try
	{
	  os << x7 . Account ( "99999999" ). Balance ( );
	  assert ( "Missing exception !!" == NULL );
	}
	catch ( ... )
	{
	}
	os . str ( "" );
	os << x7 . Account ( "987654" );
	assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 789, from: 111111, sign: SGDFTYE3sdfsd3W\n = 6369\n" ) );
	/***************/
	CBank x8;
	CBank x9;
	assert ( x8 . NewAccount ( "123456", 1000 ) );
	assert ( x8 . NewAccount ( "987654", -500 ) );
	assert ( x8 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
	assert ( x8 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
	assert ( x8 . NewAccount ( "111111", 5000 ) );
	assert ( x8 . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" ) );
	x9 = x8;
	assert ( x8 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
	assert ( x9 . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" ) );
	assert ( x8 . NewAccount ( "99999999", 7000 ) );
	assert ( x8 . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" ) );
	assert ( x8 . TrimAccount ( "111111" ) );
	os . str ( "" );
	os << x8 . Account ( "111111" );
	assert ( ! strcmp ( os . str () . c_str (), "111111:\n   -1802\n = -1802\n" ) );
	os . str ( "" );
	os << x9 . Account ( "111111" );
	assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n" ) );
	return 0;
}
#endif /* __PROGTEST__ */
