/*
 * Copyright (C) 2014-2018 Fredrik Wikstrom <fredrik@a500.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <interfaces/amisslmaster.h>
#include <interfaces/amissl.h>
#include "zip-internal.h"

#include <libraries/amisslmaster.h>

register APTR r13 __asm("r13");

/* AmiSSL is only opened when first needed */
struct AmiSSLIFace *get_IAmiSSL(void)
{
	struct ZipIData *id = (struct ZipIData *)r13;

	if (id->IAmiSSL == NULL)
	{
		id->IAmiSSLMaster = (struct AmiSSLMasterIFace *)open_interface("amisslmaster.library",
			AMISSLMASTER_MIN_VERSION);
		if (id->IAmiSSLMaster == NULL)
		{
			return NULL;
		}

		if (id->IAmiSSLMaster->OpenAmiSSLTags(AMISSL_CURRENT_VERSION,
			AmiSSL_UsesOpenSSLStructs, TRUE,
			AmiSSL_GetIAmiSSL,         &id->IAmiSSL,
			AmiSSL_ErrNoPtr,           __errno(),
			TAG_END) != 0)
		{
			close_interface((struct Interface *)id->IAmiSSLMaster);
			id->IAmiSSLMaster = NULL;
			return NULL;
		}
	}

	return id->IAmiSSL;
}

#define _IAMISSL get_IAmiSSL()

int RAND_bytes(unsigned char *buf, int num)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	if (IAmiSSL == NULL)
	{
		errno = ENOSYS;
		return -1;
	}

	return IAmiSSL->RAND_bytes(buf, num);
}

int PKCS5_PBKDF2_HMAC_SHA1(const char *pass, int passlen, const unsigned char *salt,
	int saltlen, int iter, int keylen, unsigned char *out)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	return IAmiSSL->PKCS5_PBKDF2_HMAC_SHA1(pass, passlen, salt,	saltlen, iter, keylen, out);
}

HMAC_CTX *HMAC_CTX_new(void)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	if (IAmiSSL == NULL)
	{
		errno = ENOSYS;
		return NULL;
	}

	return IAmiSSL->HMAC_CTX_new();
}

void HMAC_CTX_free(HMAC_CTX *ctx)
{
	if (ctx == NULL)
		return;

	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	return IAmiSSL->HMAC_CTX_free(ctx);
}

int HMAC_Init_ex(HMAC_CTX *ctx, const void *key, int len, const EVP_MD *md, ENGINE *impl)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	return IAmiSSL->HMAC_Init_ex(ctx, key, len, md, impl);
}

int HMAC_Update(HMAC_CTX *ctx, const unsigned char *data, size_t len)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	return IAmiSSL->HMAC_Update(ctx, data, len);
}

int HMAC_Final(HMAC_CTX *ctx, unsigned char *md, unsigned int *len)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	return IAmiSSL->HMAC_Final(ctx, md, len);
}

EVP_CIPHER_CTX *EVP_CIPHER_CTX_new(void)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	if (IAmiSSL == NULL)
	{
		errno = ENOSYS;
		return NULL;
	}

	return IAmiSSL->EVP_CIPHER_CTX_new();
}

void EVP_CIPHER_CTX_free(EVP_CIPHER_CTX *ctx)
{
	if (ctx == NULL)
		return;

	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	return IAmiSSL->EVP_CIPHER_CTX_free(ctx);
}

const EVP_MD *EVP_sha1(void)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	if (IAmiSSL == NULL)
	{
		errno = ENOSYS;
		return NULL;
	}

	return IAmiSSL->EVP_sha1();
}

const EVP_CIPHER *EVP_aes_128_ecb(void)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	if (IAmiSSL == NULL)
	{
		errno = ENOSYS;
		return NULL;
	}

	return IAmiSSL->EVP_aes_128_ecb();
}

const EVP_CIPHER *EVP_aes_192_ecb(void)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	if (IAmiSSL == NULL)
	{
		errno = ENOSYS;
		return NULL;
	}

	return IAmiSSL->EVP_aes_192_ecb();
}

const EVP_CIPHER *EVP_aes_256_ecb(void)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	if (IAmiSSL == NULL)
	{
		errno = ENOSYS;
		return NULL;
	}

	return IAmiSSL->EVP_aes_256_ecb();
}

int EVP_EncryptInit_ex(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *cipher, ENGINE *impl,
	const unsigned char *key, const unsigned char *iv)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	return IAmiSSL->EVP_EncryptInit_ex(ctx, cipher, impl, key, iv);
}

int EVP_EncryptUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl,
	const unsigned char *in, int inl)
{
	struct AmiSSLIFace *IAmiSSL = _IAMISSL;

	return IAmiSSL->EVP_EncryptUpdate(ctx, out, outl, in, inl);
}

