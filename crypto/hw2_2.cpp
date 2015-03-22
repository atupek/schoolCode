#include <iostream>
#include <math.h>
#include "BigInteger.hh"
using std::cout;
using std::endl;

int main()
{
	BigInteger n = 80554472984399121029342888775177585776235308806307568390965245448146494707389;
	int e = 65537;
	BigInteger encryptedMessage = 44468887044657086351700455622694120368068647331231730845337025255061837917088;

	//cout << pow(16, 4) << endl;
	for (int pin = 0; pin< 65536; pin++)
	{
		BigInteger trial = pow(pin, e) % n;
		if(trial == encryptedMessage)
			{
				cout << "The pin is: " << pin << endl;
			}
		//cout << pin << " " << bigIntegerToString(trial) << endl;
	}
}