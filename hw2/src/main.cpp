#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

unsigned int DEFAULT_TABLE_SIZE1 = 1000;

template <typename V>
class LinkedHashEntry { 
private:
	string key;
	V value;
	LinkedHashEntry *next;
public:
	LinkedHashEntry ( string key, V value ) { 
		this->key = key;
		this->value = value;
		this->next = nullptr;
	}
	string getKey () { return key; }
	V getValue () { return value; }
	void setValue ( V value ) { this->value = value; }
	LinkedHashEntry *getNext() { return next; }
	void setNext ( LinkedHashEntry *next ) { this->next = next; }
};

template <typename V>
class HashMap1 { 
private:
	float threshold;
	unsigned int maxSize;
	unsigned int tableSize;
	unsigned int size;
	LinkedHashEntry<V> **table;

	std::hash<std::string> hashFoo;
	
	void resize () { 
		unsigned int oldTableSize = tableSize;
		tableSize *= 2;
		maxSize = (unsigned int) ( tableSize * threshold );
		LinkedHashEntry<V> **oldTable = table;
		table = new LinkedHashEntry<V> * [tableSize];
		
		for ( unsigned int i = 0; i < tableSize; i++ )
			table[i] = nullptr;
		size = 0;

		for ( unsigned int hash = 0; hash < oldTableSize; hash++ )
			if ( oldTable[hash] != nullptr )
			{
				LinkedHashEntry<V> *oldEntry;
				LinkedHashEntry<V> *entry = oldTable[hash];
				while ( entry != nullptr ) { 
					put ( entry->getKey(), entry->getValue() );
					oldEntry = entry;
					entry = entry->getNext();
					delete oldEntry;
				}
			}
		delete[] oldTable;		
	}	
public:
	HashMap1 () { 
		threshold = 0.75f;
		maxSize = DEFAULT_TABLE_SIZE1 * threshold;
		tableSize = DEFAULT_TABLE_SIZE1;
		size = 0;
		table = new LinkedHashEntry<V>*[tableSize];

		for ( unsigned int i = 0; i < tableSize; i++ )
			table[i] = nullptr;
	}
	
	void setThreshold ( float threshold ) { 
		this->threshold = threshold;
		maxSize = (unsigned int) ( tableSize * threshold );
	}	

	V get ( string key ) const { 

		auto jozef = hashFoo ( key );
		auto hash = jozef % tableSize;

		if ( table[hash] == nullptr )
			throw false;
		else
		{
			auto entry = table[hash];
			while ( entry != nullptr && entry->getKey() != key )
				entry = entry->getNext();
			if ( entry == nullptr )
				throw false;
			else
				return entry->getValue();
		}	
	}

	void put ( string key, V value ) { 

		auto jozef = hashFoo ( key );
		auto hash = jozef % tableSize;

		if ( table[hash] == nullptr ) { 
			table[hash] = new LinkedHashEntry<V> ( key, value );
			size++;
		}
		else
		{
			auto entry = table[hash];
			while ( entry->getNext() != nullptr && entry->getKey() != key )
				entry = entry->getNext();

			if ( entry->getKey() == key )
				entry->setValue ( value );
			else
			{
				entry->setNext ( new LinkedHashEntry<V> ( key, value ) );
				size++;
			}				
		}
		if ( size >= maxSize )
			resize();	
	}

	void remove ( string key ) { 

		auto jozef = hashFoo ( key );
		auto hash = jozef % tableSize;

		if ( table[hash] != nullptr ) { 
			LinkedHashEntry<V> *prevEntry = nullptr;
			auto entry = table[hash];
			while ( entry->getNext() != nullptr && entry->getKey() != key ) { 
				prevEntry = entry;
				entry = entry->getNext();
			}
			if ( entry->getKey() == key ) 
			{
				if ( prevEntry == nullptr )
				{
					auto nextEntry = entry->getNext();
					delete entry;
					table[hash] = nextEntry;
				}
				else
				{
					auto next = entry->getNext();
					delete entry;
					prevEntry->setNext( next );
				}		
				size--;
			}	
		}
	}

	~HashMap1() { 
		for ( unsigned int hash = 0; hash < tableSize; hash++ )
			if ( table[hash] != nullptr ) 
			{ 
				LinkedHashEntry<V> *prevEntry = nullptr;
				auto entry = table[hash];
				while ( entry != nullptr ) { 
					prevEntry = entry;
					entry = entry->getNext();
					delete prevEntry;
				}
			}
		delete[] table;	
	}

};

class CVATRegister {
public:
    CVATRegister ( void ){}
    ~CVATRegister ( void ){}
    /*******/
	bool NewCompany ( const string & name, const string & addr, const string & taxID ) { 
		string nameAdress = name + "´´^´ˇ´" + addr;
		std::transform ( nameAdress.begin(), nameAdress.end(), nameAdress.begin(), ::tolower );
		string companyID = taxID;

		try { 
			CompanyID.get ( companyID );
			return false;
		} catch ( bool e ) {};
		try { 
			CompanyAdr.get ( nameAdress );
			return false;
		} catch ( bool e ) {};
	
		InvoiceID.put ( companyID, 0 );
		CompanyAdr.put ( nameAdress, companyID );
		CompanyID.put ( companyID, nameAdress );
		return true;
    }
    /*******/
	bool CancelCompany ( const string & taxID ) { 
		string companyID = taxID;
		string state;

		try { 
			state = CompanyID.get ( companyID );
		} catch ( bool e ) { return false; }

		// try { 
		// 	CompanyAdr.get ( state );
		// } catch ( bool e ) { return false; }

		CompanyID.remove ( companyID );
		InvoiceID.remove ( companyID );
		CompanyAdr.remove ( state );
		return true;		
    }
    /*******/
	bool CancelCompany ( const string & name, const string & addr ) { 
		string nameAdress = name + "´´^´ˇ´" + addr;
		std::transform ( nameAdress.begin(), nameAdress.end(), nameAdress.begin(), ::tolower );
		string state;

		try { 
			state = CompanyAdr.get ( nameAdress );
		} catch ( bool e ) { return false; }

		// try { 
		// 	CompanyID.get ( state );
		// } catch ( bool e ) { return false; }

		CompanyID.remove ( state );
		InvoiceID.remove ( state );	
		CompanyAdr.remove ( nameAdress );
		return true;	
	}
	/*******/
	bool Invoice ( const string & taxID, unsigned int amount ) { 
		unsigned int sum;
		try {
			sum = InvoiceID.get ( taxID );
		} catch ( bool e ) { return false; }

		sum += amount;
		Median.push_back (amount);
		InvoiceID.put ( taxID, sum );
		return true;
	}
	/*******/
	bool Invoice ( const string & name, const string & addr, unsigned int amount ) { 
		string nameAdress = name + "´´^´ˇ´" + addr;
		std::transform ( nameAdress.begin(), nameAdress.end(), nameAdress.begin(), ::tolower );	
		string state;

		try {
			state = CompanyAdr.get ( nameAdress );
		} catch ( bool e ) { return false; }

		unsigned int sum;
		try {
			sum = InvoiceID.get ( state );
		} catch ( bool e ) { return false; }

		sum += amount;
		Median.push_back (amount);

		InvoiceID.put ( state, sum );
		return true;
		
	}
	/*******/
	bool Audit ( const string & name, const string & addr, unsigned int & sumIncome ) const { 
		string nameAdress = name + "´´^´ˇ´" + addr;
		std::transform ( nameAdress.begin(), nameAdress.end(), nameAdress.begin(), ::tolower );
		string state;

		try { 
			state = CompanyAdr.get ( nameAdress );
		} catch  ( bool e ) { return false; }

		try {
			sumIncome = InvoiceID.get ( state );
			return true;
		} catch ( bool e ) { 
			return false;	
		}
	}
	/*******/
	bool Audit ( const string & taxID, unsigned int & sumIncome ) const { 

		try {
			sumIncome = InvoiceID.get ( taxID );
			return true;
		} catch ( bool e ) { 
			return false;	
		}
	}
	/*******/
	unsigned int MedianInvoice ( void ) const {
		std::vector<unsigned int> Median_copy ( Median );
		std::sort ( Median_copy.begin(), Median_copy.end() );
		
		size_t size = Median_copy.size();
		unsigned int median = 0;

		if ( size != 0 )
			median = Median_copy[size / 2];
		else 
			median = 0;
		return median;
	}
	/*******/
 private:
 	HashMap1<string> CompanyAdr;
 	HashMap1<string> CompanyID;
 	HashMap1<unsigned int> InvoiceID;
	std::vector<unsigned int> Median;    
};

#ifndef __PROGTEST__
int main ( void )
{
	unsigned int sumIncome;

  CVATRegister b1;
	// for ( int i = 0; i < 1000000; i++ ) { 
	// 	assert ( b1.NewCompany ( to_string ( i ), to_string ( i + 1 ), to_string ( i + 2 ) ) );
	// 	assert ( b1.Invoice (to_string(i+2), 10) );	
	// }

	// for ( int i = 0; i < 500000; i++ ) { 
	// 	b1.Invoice (to_string(i), to_string(i + 1), 3);
	// 	assert ( b1.Audit ( to_string(i + 2)/*to_string ( i ), to_string ( i + 1 )*/, sumIncome ) && (sumIncome == 13 ));
	// 	assert ( b1.CancelCompany ( to_string ( i ), to_string ( i + 1 ) ) );
	// }	
	// for ( int i = 0; i < 500000; i++ ) { 
	// 	assert ( b1.NewCompany ( to_string ( i ), to_string ( i + 1 ), to_string ( i + 2 ) ) );	
	// }

	// for ( int i = 0; i < 1000000; i++ ) { 
	// 	assert ( b1.Audit ( to_string ( i ), to_string ( i + 1 ), sumIncome ) && (i < 500000 ? sumIncome == 0 : sumIncome == 10));
	// 	assert ( b1.CancelCompany ( to_string ( i ), to_string ( i + 1 ) ) );	
	// }

  	assert ( b1.NewCompany ( "adsasda;[];];';;';';';];;];';';';';'];;;';;;;';;;';;;sdas+38990+;/;/", "1234616sad;;", "='';'];']';==;';'=;='=;';='=|]]][[=" ) );
  	assert ( ! b1.NewCompany ( "adsasda;[];];';;';';';];;];';';';';'];;;';;;;';;;';;;sdas+38990+;/;/", "1234616sad;;", "='';'];']';==;';'=;='=;';='=|]]][[=" ) );
  	assert ( b1 . MedianInvoice () == 0 );
  	assert ( ! ( b1 . MedianInvoice () == 2000 ) );
  	assert ( b1 . Invoice ( "='';'];']';==;';'=;='=;';='=|]]][[=", 0 ) );
  	assert ( b1 . Invoice ( "='';'];']';==;';'=;='=;';='=|]]][[=", 0 ) );
  	assert ( b1 . Invoice ( "='';'];']';==;';'=;='=;';='=|]]][[=", 0 ) );
  	assert ( b1 . Invoice ( "adsasda;[];];';;';';';];;];';';';';'];;;';;;;';;;';;;sdas+38990+;/;/", "1234616sad;;", 0 ) );
  	assert ( b1 . Audit ( "='';'];']';==;';'=;='=;';='=|]]][[=", sumIncome ) && sumIncome == 0 );
	assert ( b1.CancelCompany ( "adsasda;[];];';;';';';];;];';';';';'];;;';;;;';;;';;;sdas+38990+;/;/", "1234616sad;;" ) );
	assert ( ! b1.CancelCompany ( "='';'];']';==;';'=;='=;';='=|]]][[=" ) );
  	assert ( ! b1 . Invoice ( "adsasda;[];];';;';';';];;];';';';';'];;;';;;;';;;';;;sdas+38990+;/;/", "1234616sad;;", 0 ) );
  	assert ( b1.NewCompany ( "adsasda;[];];';;';';';];;];';';';';'];;;';;;;';;;';;;sdas+38990+;/;/", "1234616sad;;", "='';'];']';==;';'=;='=;';='=|]]][[=" ) );
  	assert ( b1 . Audit ( "='';'];']';==;';'=;='=;';='=|]]][[=", sumIncome ) && sumIncome == 0 );
  	assert ( b1 . Audit ( "='';'];']';==;';'=;='=;';='=|]]][[=", sumIncome ) );
  	assert ( b1 . Invoice ( "='';'];']';==;';'=;='=;';='=|]]][[=", 0 ) );
  	assert ( b1 . Audit ( "='';'];']';==;';'=;='=;';='=|]]][[=", sumIncome ) && sumIncome == 0 );

 	// assert ( b1 . NewCompany ( "ACME", "Kolejni", "666/666/666" ) );
 	// assert ( b1 . Audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 0 );
 	// assert ( b1 . NewCompany ( "ACME", "Thakurova", "666/666" ) );
 	// assert ( b1 . NewCompany ( "Dummy", "Thakurova", "123456" ) );
 	// assert ( b1 . Invoice ( "666/666", 2000 ) );
 	// assert ( b1 . MedianInvoice () == 2000 );
 	// assert ( b1 . Invoice ( "666/666/666", 3000 ) );
 	// assert ( b1 . MedianInvoice () == 3000 );
 	// assert ( b1 . Invoice ( "123456", 4000 ) );
 	// assert ( b1 . MedianInvoice () == 3000 );
 	// assert ( b1 . Invoice ( "aCmE", "Kolejni", 5000 ) );
 	// assert ( b1 . MedianInvoice () == 4000 );
 	// assert ( b1 . Audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000 );
 	// assert ( b1 . Audit ( "123456", sumIncome ) && sumIncome == 4000 );
 	// assert ( b1 . CancelCompany ( "ACME", "KoLeJnI" ) );
 	// assert ( ! b1 . Audit ( "666/666/666", sumIncome ) );
 	// assert ( ! b1 . Audit ( "666/666/660", sumIncome ) );
 	// assert ( b1 . MedianInvoice () == 4000 );
 	// assert ( b1 . CancelCompany ( "666/666" ) );
 	// assert ( b1 . MedianInvoice () == 4000 );
 	// assert ( b1 . Invoice ( "123456", 100 ) );
 	// assert ( b1 . MedianInvoice () == 3000 );
 	// assert ( b1 . Invoice ( "123456", 300 ) );
 	// assert ( b1 . MedianInvoice () == 3000 );
 	// assert ( b1 . Invoice ( "123456", 200 ) );
 	// assert ( b1 . MedianInvoice () == 2000 );
 	// assert ( b1 . Invoice ( "123456", 230 ) );
 	// assert ( b1 . MedianInvoice () == 2000 );
 	// assert ( b1 . Invoice ( "123456", 830 ) );
 	// assert ( b1 . MedianInvoice () == 830 );
 	// assert ( b1 . Invoice ( "123456", 1830 ) );
 	// assert ( b1 . MedianInvoice () == 1830 );
 	// assert ( b1 . Invoice ( "123456", 2830 ) );
 	// assert ( b1 . MedianInvoice () == 1830 );
 	// assert ( b1 . Invoice ( "123456", 2830 ) );
 	// assert ( b1 . MedianInvoice () == 2000 );
 	// assert ( b1 . Invoice ( "123456", 3200 ) );
 	// assert ( b1 . MedianInvoice () == 2000 );
 	// CVATRegister b2;
 	// assert ( b2 . NewCompany ( "ACME", "Kolejni", "abcdef" ) );
 	// assert ( b2 . NewCompany ( "Dummy", "Kolejni", "123456" ) );
 	// assert ( ! b2 . NewCompany ( "AcMe", "kOlEjNi", "1234" ) );
 	// assert ( b2 . NewCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
 	// assert ( b2 . MedianInvoice () == 0 );
 	// assert ( b2 . Invoice ( "ABCDEF", 1000 ) );
 	// assert ( b2 . MedianInvoice () == 1000 );
 	// assert ( b2 . Invoice ( "abcdef", 2000 ) );
 	// assert ( b2 . MedianInvoice () == 2000 );
 	// assert ( b2 . Invoice ( "aCMe", "kOlEjNi", 3000 ) );
 	// assert ( b2 . MedianInvoice () == 2000 );
 	// assert ( ! b2 . Invoice ( "1234567", 100 ) );
 	// assert ( ! b2 . Invoice ( "ACE", "Kolejni", 100 ) );
 	// assert ( ! b2 . Invoice ( "ACME", "Thakurova", 100 ) );
 	// assert ( ! b2 . Audit ( "1234567", sumIncome ) );
 	// assert ( ! b2 . Audit ( "ACE", "Kolejni", sumIncome ) );
 	// assert ( ! b2 . Audit ( "ACME", "Thakurova", sumIncome ) );
 	// assert ( ! b2 . CancelCompany ( "1234567" ) );
 	// assert ( ! b2 . CancelCompany ( "ACE", "Kolejni" ) );
 	// assert ( ! b2 . CancelCompany ( "ACME", "Thakurova" ) );
 	// assert ( b2 . CancelCompany ( "abcdef" ) );
 	// assert ( b2 . MedianInvoice () == 2000 );
 	// assert ( ! b2 . CancelCompany ( "abcdef" ) );
 	// assert ( b2 . NewCompany ( "ACME", "Kolejni", "abcdef" ) );
 	// assert ( b2 . CancelCompany ( "ACME", "Kolejni" ) );
 	// assert ( ! b2 . CancelCompany ( "ACME", "Kolejni" ) );

  return 0;
}
#endif /* __PROGTEST__ */