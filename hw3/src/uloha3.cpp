#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cmath>
#include <cfloat>
#include <cassert>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

ios_base & dummy_polynomial_manipulator ( ios_base & x )
{ 
  return x;
}

ios_base & ( * ( polynomial_variable ( const string & varName ) ) ) ( ios_base & x )
{
  return dummy_polynomial_manipulator;
}
class CPolynomial {	

private:
	vector<double> m_Data;    

public:
	CPolynomial () { }
	//vector<double> m_Data;
	/*Operator []*/
	double & operator [] ( size_t idx ) {
	    if ( idx >= this->m_Data.size() ) {
		    this->m_Data.resize ( idx + 1, 0 );
	    }
	    return this->m_Data[idx];
    }
    double operator [] ( size_t idx ) const {
        if ( idx >= this->m_Data.size()) 
            return 0;
        return this->m_Data[idx];
    }

    /*Operator <<*/
    friend ostream & operator << ( ostream & out, const CPolynomial & pol ) { 
    	stringstream streamTest;   


        if ( pol . Degree () == 0 ) {
            return out << "0";
        }
        
        for ( int i = pol.Degree (); i >= 0; --i ) {
            
            if ( pol.m_Data[i] != 0 ) {
                if ( pol.m_Data[i] < 0 ) {
                    streamTest << "- ";
                    if ( pol.m_Data[i] != -1 ) {
                        streamTest << fabs( pol.m_Data[i] ) << "*";
                    }
                }     
                else {
                    if ( pol.m_Data[i] != 1 ) {
                        if ( i != (int)pol.Degree() )
                            streamTest << "+ ";
                        streamTest << pol.m_Data[i] << "*" ;
                    }
                }
                    streamTest << "x^" << i << " ";
            }
        }

      size_t locator = streamTest.str().find("*x^0");

      if ( locator && locator < streamTest.str().size() )
        out << streamTest.str().substr(0, locator); 
      else 
        out << streamTest.str().substr(0, streamTest.str().find_last_of(' '));
      return out;
    }
    /*Operator +*/
    CPolynomial operator + ( const CPolynomial & pol ) const { 

    	CPolynomial output;

        size_t s1 = this->m_Data.size();
        size_t s2 = pol.m_Data.size();
        size_t size1 = 0;
        size_t size2 = 0;

        for ( int i = 0; i < (int)s1; i++ )
        	if ( this->m_Data[i] != 0 )
        		size1 = (size_t)i + 1;

        for ( int i = 0; i < (int)s2; i++ )
        	if ( pol.m_Data[i] != 0 )
        		size2 = (size_t)i + 1;  


        bool ind = false;

    	if ( size1 > size2 )
    		ind = true;

    	if ( ind == true ) { 
    		output.m_Data.resize (size1);
    		for ( int i = 0; i < (int)size2; i++ ) 
    			output.m_Data[i] =  this->m_Data[i] + pol.m_Data[i];
    		for ( int i = size2; i < (int)size1; i++ ) 
    			output.m_Data[i] =  this->m_Data[i];
    	}
    	else
    	{	
    		output.m_Data.resize (size2);
    		for ( int i = 0; i < (int)size1; i++ ) 
    			output.m_Data[i] =  this->m_Data[i] + pol.m_Data[i];
    		for ( int i = size1; i < (int)size2; i++ ) 
    			output.m_Data[i] =  pol.m_Data[i];
    	}	
    	return output;
    }

    
    /*Operator -*/
    CPolynomial operator - ( const CPolynomial & pol ) const { 

    	CPolynomial output;

        size_t s1 = this->m_Data.size();
        size_t s2 = pol.m_Data.size();
        size_t size1 = 0;
        size_t size2 = 0;

        for ( int i = 0; i < (int)s1; i++ )
        	if ( this->m_Data[i] != 0 )
        		size1 = (size_t)i + 1;

        for ( int i = 0; i < (int)s2; i++ )
        	if ( pol.m_Data[i] != 0 )
        		size2 = (size_t)i + 1;  


        bool ind = false;

    	if ( size1 > size2 )
    		ind = true;

    	if ( ind == true ) { 
    		output.m_Data.resize (size1);
    		for ( int i = 0; i < (int)size2; i++ ) 
    			output.m_Data[i] =  this->m_Data[i] - pol.m_Data[i];
    		for ( int i = size2; i < (int)size1; i++ ) 
    			output.m_Data[i] =  - this->m_Data[i];
    	}
    	else
    	{	
    		output.m_Data.resize (size2);
    		for ( int i = 0; i < (int)size1; i++ ) 
    			output.m_Data[i] =  this->m_Data[i] - pol.m_Data[i];
    		for ( int i = size1; i < (int)size2; i++ ) 
    			output.m_Data[i] =  - pol.m_Data[i];
    	}	
    	return output;
    }

    /*Operator * - polynom*/
	CPolynomial operator * ( const CPolynomial & pol ) const { 

    	CPolynomial output;    		

  		size_t s1 = this->m_Data.size();
        size_t s2 = pol.m_Data.size();
        size_t size1 = 0;
        size_t size2 = 0;

        for ( int i = 0; i < (int)s1; i++ )
        	if ( this->m_Data[i] != 0 )
        		size1 = (size_t)i + 1;

        for ( int i = 0; i < (int)s2; i++ )
        	if ( pol.m_Data[i] != 0 )
        		size2 = (size_t)i + 1;

    	output.m_Data.resize (size1+size2-1);

        for ( int i = 0; i < (int)size1; i++ )
            for ( int j = 0; j < (int)size2; j++ )
                output.m_Data[i+j] += this->m_Data[i] * pol.m_Data[j];                
        return output;	
    }
    /*Operator * - cislo*/
    CPolynomial operator * ( const double x ) const { 
        size_t s = this->m_Data.size();
        size_t size = 0;

        for ( int i = 0; i < (int)s; i++ )
        	if ( this->m_Data[i] != 0 )
        		size = (size_t)i + 1;

        CPolynomial output;
        output.m_Data = this->m_Data;    

        for ( int i = 0; i < (int)size; i++ )
            output.m_Data[i] *= x;           
        return output;
    }    
    /*Operator ()*/
    double operator () ( const double x ) const { 

        double sum = 0;
        size_t s = this->m_Data.size();
        size_t size = 0;

        for ( int i = 0; i < (int)s; i++ )
        	if ( this->m_Data[i] != 0 )
        		size = (size_t)i + 1;

        for ( int i = 0; i < (int)size; i++ ) { 
             sum += this->m_Data[i] * pow ( x, i );
        } 
        return sum;
    }
    /*Operator ==*/
    bool operator == ( const CPolynomial & pol ) const { 

        size_t s1 = this->m_Data.size();
        size_t s2 = pol.m_Data.size();
        size_t size1 = 0;
        size_t size2 = 0;

        for ( int i = 0; i < (int)s1; i++ )
        	if ( this->m_Data[i] != 0 )
        		size1 = (size_t)i + 1;

        for ( int i = 0; i < (int)s2; i++ )
        	if ( pol.m_Data[i] != 0 )
        		size2 = (size_t)i + 1;	          	

        if ( size1 == size2 ) { 
            for ( int i = 0; i < (int)size1; i++ )
                if ( this->m_Data[i] != pol.m_Data[i] )
                    return false;
        }
        else
            return false;
        return true;
    }
    /*Operator !=*/
    bool operator != ( const CPolynomial & pol ) const { 

    	size_t s1 = this->m_Data.size();
        size_t s2 = pol.m_Data.size();
        size_t size1 = 0;
        size_t size2 = 0;

        for ( int i = 0; i < (int)s1; i++ )
        	if ( this->m_Data[i] != 0 )
        		size1 = (size_t)i + 1;

        for ( int i = 0; i < (int)s2; i++ )
        	if ( pol.m_Data[i] != 0 )
        		size2 = (size_t)i + 1;	          	

        if ( size1 == size2 ) { 
            for ( int i = 0; i < (int)size1; i++ )
                if ( this->m_Data[i] != pol.m_Data[i] )
                    return true;
        }
        else
  	        return true;
        return false;
    }

    /*Metoda Degree*/
    unsigned int Degree ( ) const { 
    	unsigned int s = this->m_Data.size();
    	unsigned int size = 0;

    	for ( int i = 0; i < (int)s; i++ )
        	if ( this->m_Data[i] != 0 )
        		size = (unsigned int)i;   
     
        return size;
    }
};

#ifndef __PROGTEST__

bool smallDiff ( double a, double b ) {            
    if ( a == b )
        return true;
    else
        return false;
}

bool dumpMatch ( const CPolynomial & x, const vector<double> & ref ) {

    vector<double> temp (x.m_Data);
    bool isEmpty = true;

    for ( int i = 0; i < (int)temp.size(); i++ )
        if ( temp[i] != 0 )
            isEmpty = false;

    if ( isEmpty == true && ref.size() == 1 && ref[0] == 0 )
        return true;    

    if ( temp.capacity() == ref.capacity() )
    {
        for ( int i = 0; i < (int)temp.capacity(); i++ ) { 
            if ( temp[i] != ref[i] )
                return false;
        }
    }
    else
        return false;
    return true;        
}

int main ( void ) {

	/*CPolynomial a, b, c, d;
	int cnt = 0;*/

	/*for ( double i = 0; i < 10; i+=2.37 ) { 
		cnt++;
		if ( cnt % 2 == 0 )
			a[i] = i;
		else
			a[i] = -i;	 	
	}

	for ( double i = 0; i < 10; i+=3.25 ) { 
		cnt++;
		if ( cnt % 2 == 0 )
			b[i] = i;
		else
			b[i] = -i;	 	
	}

	cout << a << endl;
	cout << b << endl;
	c = a * b;
	cout << c << endl;*/

	/*a[5] = 2.354;

	b[5] = 2.354;	

	cout << a+b << endl;
	cout << a*b << endl;
	cout << a-b << endl;*/

  CPolynomial a, b, c;
  ostringstream out;

  a[0] = -10;
  a[1] = 3.5;
  a[3] = 1;
  assert ( smallDiff ( a ( 2 ), 5 ) );
  out . str ("");
  out << a;
  assert ( out . str () == "x^3 + 3.5*x^1 - 10" );
  a = a * -2;
  //assert ( a . Degree () == 3
  //         && dumpMatch ( a, vector<double>{ 20.0, -7.0, -0.0, -2.0 } ) );

  out . str ("");
  out << a;
  assert ( out . str () == "- 2*x^3 - 7*x^1 + 20" );
  out . str ("");
  out << b;
  assert ( out . str () == "0" );
  b[5] = -1;
  out . str ("");
  out << b;
  assert ( out . str () == "- x^5" );
  c = a + b;
  assert ( c . Degree () == 5
          && dumpMatch ( c, vector<double>{ 20.0, -7.0, 0.0, -2.0, 0.0, -1.0 } ) );

  out . str ("");
  out << c;
  assert ( out . str () == "- x^5 - 2*x^3 - 7*x^1 + 20" );
  c = a - b;
  assert ( c . Degree () == 5
           && dumpMatch ( c, vector<double>{ 20.0, -7.0, -0.0, -2.0, -0.0, 1.0 } ) );

  out . str ("");
  out << c;
  assert ( out . str () == "x^5 - 2*x^3 - 7*x^1 + 20" );
  c = a * b;
  assert ( c . Degree () == 8
           && dumpMatch ( c, vector<double>{ 0.0, -0.0, 0.0, -0.0, -0.0, -20.0, 7.0, 0.0, 2.0 } ) );

  out . str ("");
  out << c;
  assert ( out . str () == "2*x^8 + 7*x^6 - 20*x^5" );
  assert ( a != b );
  b[5] = 0;
  assert ( !(a == b) );
  a = a * 0;

  assert ( a . Degree () == 0
           && dumpMatch ( a, vector<double>{ 0.0 } ) );

  assert ( a == b );

	return 0;
}
#endif /* __PROGTEST__ */
