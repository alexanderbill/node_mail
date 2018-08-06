/*******************************************************************************
 * Copyright(C):	Hulian
 * Author: 			hzh
 * Date: 			2018/03/16
 * Description:		Toon Rsa implemented by openssl
*******************************************************************************/


#ifndef __t_rsa_h__
#define __t_rsa_h__


#include <string>

#include <openssl/rsa.h>


#define PUBKEY_PATH     "pubkey"
#define PRIKEY_PATH     "privkey"
#define RSA_PATH(path, a) (path + "/" + a + ".txt")


class TRsa
{
protected:

	// RSA padding
	int							m_nPadding;

	// public key
	std::string					m_sPubKey;
	
	// private key
	std::string					m_sPriKey;

	// public RSA ptr
	RSA *						m_pPubRsa;
	
	// priate RSA ptr
	RSA *						m_pPriRsa;

public:

	TRsa();

	~TRsa();
 
    bool isValid();
	/* 
	 * Function: InitKey
	 * Description: generate key pair
	 * Parameter:
	 *		bits: key length, text max length = bits / 8
	 * 		method: RSA_3(3), RSA_F4(65537) etc
	 * Return: success | fail
	 */
	bool InitKey(int bits, int method = RSA_F4);
	
	/*
	 * Function: SetPadding
	 */
	void SetPadding(int padding);

	/*
	 * Function: SetPubKey
	 * Description: set public key
	 * Return: success | fail
	 */
	bool SetPubKey(const std::string & pub);

	/*
	 * Function: GetPubKey
	 * Return: RSA public key
	 */
	const std::string & GetPubKey() const;

	/*
	 * Function: SetPriKey
	 * Description: set private key
	 * Return: success | fail
	 */
	bool SetPriKey(const std::string & pri);

	/*
	 * Function: GetPriKey
	 * Return: RSA private key
	 */
	const std::string & GetPriKey() const;

	/*
	 * Function: Sign
	 * Description: generate signature
	 * Parameters:
	 *		text: input text
	 *		sign: output signature
	 * Return: success | fail
	 */
	bool Sign(const std::string & text, std::string & sign);

	/*
	 * Function: Verify
	 * Description: verify signature
	 * Parameters:
	 *		text: input text
	 *		sign: input signature
	 * Return: success | fail
	 */
	bool Verify(const std::string & text, const std::string & sign);

	/*
	 * Function: PubEncrypt
	 * Description: encrypt using public key
	 * Parameters:
	 *		text: input text
	 *		out: output encryption
	 * Return: success | fail
	 */
	bool PubEncrypt(const std::string & text, std::string & out);
	
	/*
	 * Function: PubDecrypt
	 * Description: decrypt using public key
	 * Parameters:
	 *		text: input encryption
	 *		out: output decryption
	 * Return: success | fail
	 */
	bool PubDecrypt(const std::string & text, std::string & out);

	/*
	 * Function: PriEncrypt
	 * Description: encrypt using private key
	 * Parameters:
	 *		text: input text
	 *		out: output encryption
	 * Return: success | fail
	 */
	bool PriEncrypt(const std::string & text, std::string & out);
	
	/*
	 * Function: PriDecrypt
	 * Description: decrypt using private key
	 * Parameters:
	 *		text: input encryption
	 *		out: output decryption
	 * Return: success | fail
	 */
	bool PriDecrypt(const std::string & text, std::string & out);

protected:

	void clear();

    bool create_pub_rsa(const std::string & key);
    bool create_pri_rsa(const std::string & key);

    void clear_pub_rsa();
    void clear_pri_rsa();

    bool sign_rsa(const std::string & text, std::string & sign);
    bool sign_evp(const std::string & text, std::string & sign);

    bool verify_rsa(const std::string & text, const std::string &sign);
    bool verify_evp(const std::string & text, const std::string &sign);
};

bool rsa_base64_encode(const char * data, size_t size, std::string & out);
bool rsa_base64_decode(const char * data, size_t size, std::string & out);


#endif//__t_rsa_h__
