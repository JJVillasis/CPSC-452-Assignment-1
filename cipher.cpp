#include <iostream>
#include <string>
#include "CipherInterface.h"
#include "Playfair.h"
#include "Railfence.h"
#include "Vigenere.h"
#include "Caesar.h"

using namespace std;

int main(int argc, char** argv)
{
	// Parsing Command Line Arguments //

	string cipherName = argv[1];
	string key = argv[2];
	string encDec = argv[3];
	string inputFile = argv[4];
	string outputFile = argv[5];


	// Handling Cipher Interface //

	CipherInterface* cipher = NULL;

	//If the Cipher is Playfair
	if(cipherName == "PLF")
	{
		cipher = new Playfair();
		cipher->setKey(key);
	}
	//If the cipher is Railfence
	else if(cipherName == "RFC")
	{
		cipher = new Railfence();
		cipher->setKey(key);
	}
	//If the cipher is Vigenere
	else if(cipherName == "VIG")
	{
		cipher = new Vigenere();
		cipher->setKey(key);
	}
	//If the cipher is Caesar
	else if(cipherName == "CES")
	{
		cipher = new Caesar();
		cipher->setKey(key);
	}
	//If the cipher is unknown/unimplemented
	else
	{
		cout << "The Cipher \"" << cipherName << "\" is unknown.\n";
		exit(1);
	}


	// Performing the Encryption/Decryption //

	//Encryption process
	if(encDec == "ENC")
	{

	}
	//Decryption process
	else if(encDec == "DEC")
	{

	}
	//Unknown process
	else
	{
		cout << "Unknown Process: \"" << encDec << "\"\n";
		exit(1);
	}


	return 0;
}
