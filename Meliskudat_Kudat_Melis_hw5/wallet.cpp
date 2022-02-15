#include "wallet.h" 
#include <sstream>
#include "strutils.h" 
using namespace std;

Wallet :: Wallet ()
{
	size = 0 ; // initializing size to 0
	pinter = NULL ;
}

Wallet :: Wallet( const Wallet & copy) 
{
	pinter = copy.CreateClone(); // to prevent shallow copy we copy the rhs 
	size = copy.size ;
}


Wallet :: ~ Wallet() 
{
	delete [] pinter ; 
}


Money* Wallet:: CreateClone() const // to create the copy of the pinter of the wallet
{
	
	Money* tocopy ;
	tocopy = new Money [size] ;

	int i = 0 ;
	while ( i < size)
	{
		tocopy[i].amount = pinter[i].amount ; 
		tocopy[i].currency = pinter[i].currency ;
		i += 1 ;
	}
	return tocopy ;
}


int Wallet:: Size() const  
{
	return size ;
}




const Wallet & Wallet:: operator= (const Wallet &rhs)
{
	Wallet Temp( rhs) ;
	this -> size = Temp.size ; // equalizing  wallet's size to the rhs's size
	this ->pinter = Temp.CreateClone() ; // to make the wallet's pinter equal to temp's without shallow copy
	return *this ;
}


const Wallet & Wallet:: operator+= (const Wallet &rhs)
{
	for(int a = 0 ; a < rhs.size ; a++)
	{
		if( ifExists( rhs.pinter[a]) == false) // if the currency doesn't exist in the file already
			Change( rhs.pinter[a]) ; // add the name and the amount of the currency to the wallet
		else
			Add( rhs.pinter[a] ) ; // if it already exists then just update the amount
	}
	return *this ;
}

bool Wallet:: ifExists ( Money &rhs) const
{
	for(int i = 0 ; i < this -> size ; i++)
	{
		if( this ->pinter[i].currency == rhs.currency) // to check whether rhs's currency already exist in the wallet
			return true ;
	}
	return false ;
}


void Wallet :: Add( Money&rhs)  // add to the wallet when the added to be's currency already exist in the wallet
{
	for( int m = 0 ; m < this -> size ; m++)
	{
		if( this -> pinter[m].currency == rhs.currency)
			this ->pinter[m].amount += rhs.amount ;
	}


}



const Wallet & Wallet :: Change( Money&rhs)
{
	int new_size = size + 1 ; // since we are increasing the size of the wallet
	Money* temp ;
	temp = new Money[new_size] ; // creating new array to store the currencies and the amounts
	for( int x = 0 ; x < this ->size ; x++)
	{
		temp[x] = this->pinter[x] ; // in other words making temp's index values the same as the wallet
	}
	temp[new_size-1] = rhs ; // making the last element of the array equal to rhs
	delete [] pinter ;
	size += 1 ;
	pinter = new Money[new_size] ;
	for(int u = 0 ; u < new_size ; u++)
	{
		this ->pinter[u] = temp[u] ; // equalizing wallet's pinter values to temp's
	}
	delete [] temp ;
	return *this ;

}



const Wallet & Wallet:: DeleteCurrency (Money& rhs) // if the amount and the currency will be deleted from the wallet
{
	
    Money* ptr ;
	int currentsize = this ->size - 1 ;
	ptr = new Money[currentsize] ;
	int a = 0 ;
	for(int b = 0 ; b < this ->size ; b++)
	{
		if( this ->pinter[b].currency != rhs.currency)
		{
			ptr[a] = this -> pinter[b];
			a += 1 ;
		}
	}
	delete [] pinter ;
	this -> size -= 1 ;
	pinter =  new Money[ currentsize] ;
	for(int j = 0 ; j < currentsize ; j ++)
	{
		pinter[j] = ptr[j] ;
	}
	return *this ;


}


bool Wallet:: Equal ( const Wallet &rhs) const
{
	if( this -> size != rhs.size)
		return false ;
	int count_compare = 0 ; // will be increased when common currency is found
	for( int k = 0 ; k < this -> size ; k++)
	{
		for(int a = 0 ; a < this -> size ; a++)
		{
			if( this ->pinter[k].amount == rhs.pinter[a].amount && this ->pinter[k].currency == rhs.pinter[a].currency)
				count_compare += 1 ;
		}

	}
	if( count_compare == this ->size) // if all currencies and the amounts of each size are equal
		return true ;
	return false ;

}



bool Wallet:: isGreater( Money&rhs) const
{
	for( int a = 0 ; a < this -> size ; a++)
	{
		if( this -> pinter[a].currency == rhs.currency  && this -> pinter[a].amount >= rhs.amount) // if the amount of the currency of the wallet is greater than rhs
			return true ;
	}
	return false ;

}

bool Wallet :: OkeytoDecrease ( Money&rhs)
{
	for(int i = 0 ; i < this ->size ; i++)
	{
		if( this ->pinter[i].currency == rhs.currency)
		{
			if( pinter[i].amount > rhs.amount)
				return true ;
		}

	}
	return false;

}

void Wallet:: DecreaseFromWallet( Money&rhs) // if the currency still exists in the wallet but the amount is decreased
{
	int s = 0 ;

	while (s < this -> size)
	{
		if ( this ->pinter[s].currency == rhs.currency)
			break ;
		s += 1 ;
	}
	this -> pinter[s].amount -= rhs.amount ;
}

const Wallet & Wallet :: AddForTheFirstElement( Money &rhs)
{
	this -> size = 1 ;
	pinter = new Money[1]  ; // making pinter pointer to point an array with size 1
	this ->pinter[0] = rhs ;
	return *this ;
}


string Wallet:: toPrint() const
{
	string toprint = " " ;
	int i = 0 ;
	if( this -> size != 0 )
	{
		while( i < this ->size -1)
		{
			toprint += " " + pinter[i].currency + "  " + tostring(pinter[i].amount) + " - " ;
			i += 1 ;
		}
		toprint += " " + pinter[i].currency + "  " + tostring(pinter[i].amount)  ; // updating the string
	}
	return toprint ;
}



bool Wallet:: MoneyisMore ( Money&rhs)
{
	for( int i = 0 ; i < this -> size ; i++)
	{
		if( this -> pinter[i].currency == rhs.currency && rhs.amount > this ->pinter[i].amount )
			return true ;
	}
	return false ;
}







// free functions declaration -------------------------------------------------------------------

ostream & operator << (ostream & os, const Wallet & walletname) 
{
	string x = walletname.toPrint() ;
	os << x ; // to cout the amounts and the currencies of the wallet
    return os;
}

Wallet operator+ ( const Wallet& lhs , Money &rhs) 
{
	Wallet Temp2(lhs) ;
	if(lhs.Size() == 0 ) // if size is 0 then to create the array with size 1
	{
		return Temp2.AddForTheFirstElement(rhs);
	}

	else if( lhs.ifExists(rhs) == true) // if exists update the amount
	{
		Temp2.Add(rhs) ;
		return Temp2 ;
	}
	else
	{
	
	    return Temp2.Change(rhs) ; // if doesn't exist create a new currency in the wallet
	}
}

Wallet operator+ (const Wallet &lhs , const Wallet &rhs)
{
		Wallet Temp2(lhs) ; // calling copy constructor
		Temp2 += rhs;
		return Temp2 ;

}


	    
Wallet operator- (const Wallet &lhs , Money & rhs)
{
	Wallet copylhs(lhs) ;
	int t = 0 ;
	if( lhs.ifExists(rhs) == false)
		t = t ;
	else if( copylhs.OkeytoDecrease(rhs) == true ) // if we know that after decrease there will be still left in the wallet from that currency
	{
		copylhs.DecreaseFromWallet(rhs) ; 
	}
	else if( copylhs.OkeytoDecrease(rhs) == false && copylhs.MoneyisMore(rhs)== true) // if money to be deleted amount is more than the money in the wallet
		t = t ;
	else // after reducing the currency should be removed from the wallet
	{
		copylhs.DeleteCurrency(rhs) ;
		
	}

	return copylhs ;
}

bool operator == (const Wallet &lhs , const Wallet&rhs) 
{
	return lhs.Equal(rhs) ; // to check if lhs's currencies and amounts are the same as rhs's
}

bool operator >= (const Wallet &lhs , Money&rhs)
{
	if ( lhs.ifExists(rhs) == false) // if the currency of the rhs doesn't exist in the rhs
		return false ;
	else
	{
		if(lhs.isGreater(rhs) == true ) // if it exists and the lhs's amount is greater than rhs
			return true;
	}
	return false;
}

bool operator <= ( Money& lhs , const Wallet & rhs)
{
	 if( rhs.ifExists(lhs) == false)
		 return false ;
	 else
	 {
		 if( rhs.isGreater(lhs))
			 return true ;
	 }
	 return false ;
}
