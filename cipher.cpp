#include <iostream>
#include <fstream>
#include <string>
#include "CipherInterface.h"
#include "Playfair.h"
#include "Railfence.h"
#include "Vigenere.h"
#include "Caesar.h"

using namespace std;

int main(int argc, char** argv)
{
	//// Parsing Command Line Arguments ////

	string cipherName = argv[1];
	string key = argv[2];
	string encDec = argv[3];
	string inputFile = argv[4];
	string outputFile = argv[5];


	//// Reading the File ////

	//Input and output files
	ifstream in (inputFile);
	ofstream out;
	out.open(outputFile);

	//Text from input file
	string inputText;

	//Check if file can be opened
	if(in.is_open())
	{
		//Read text from the input file
		getline(in, inputText);
	}

	else
	{
		cout << "Unable to open file \"" << inputFile << "\". File Does not exist.\n";
		exit(1);
	}


	//// Handling Cipher Interface ////

	// Interface Class
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


	//// Performing the Encryption/Decryption ////

	//Encryption process
	if(encDec == "ENC")
	{
		string ciphertext = cipher->encrypt(inputText);
		out << ciphertext;

	}
	//Decryption process
	else if(encDec == "DEC")
	{
		string plaintext = cipher->decrypt(inputText);
		out << plaintext;
	}
	//Unknown process
	else
	{
		cout << "Unknown Process: \"" << encDec << "\"\n";
		exit(1);
	}

	//// Close files ////

	in.close();
	out.close();

	return 0;
}
