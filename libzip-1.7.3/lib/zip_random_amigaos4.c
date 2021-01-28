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

#include "zipint.h"

#ifdef HAVE_CRYPTO
#include "zip_crypto.h"
#endif

#include <devices/timer.h>
#include <proto/exec.h>
#include <proto/dos.h>

#include <stdlib.h>

#ifndef HAVE_SECURE_RANDOM
ZIP_EXTERN bool
zip_secure_random(zip_uint8_t *buffer, zip_uint16_t length) {
	BPTR fh;
	APTR window;
	bool result = false;

	/* Disable "Please insert disk ..." requesters */
	window = IDOS->SetProcWindow((APTR)-1);
	fh = IDOS->Open("RANDOM:", MODE_OLDFILE);
	IDOS->SetProcWindow(window);

	if (fh != ZERO) {
		if (IDOS->Read(fh, buffer, length) == length)
			result = true;

		IDOS->Close(fh);
	}

	if (!result) {
		/* Read directly from the timer.device entropy unit if the
		 * RANDOM: device is not available.
		 */
		struct MsgPort *mp;
		struct IOStdReq *io;

		mp = IExec->AllocSysObject(ASOT_PORT, NULL);
		io = IExec->AllocSysObjectTags(ASOT_IOREQUEST,
			ASOIOR_ReplyPort, mp,
			ASOIOR_Size,      sizeof(*io),
			TAG_END);
		if (io != NULL) {
			if (IExec->OpenDevice(TIMERNAME, UNIT_ENTROPY, (struct IORequest *)io, 0) == IOERR_SUCCESS) {
				io->io_Command = TR_READENTROPY;
				io->io_Data    = buffer;
				io->io_Length  = length;

				if (IExec->DoIO((struct IORequest *)io) == IOERR_SUCCESS)
					result = true;

				IExec->CloseDevice((struct IORequest *)io);
			}

			IExec->FreeSysObject(ASOT_IOREQUEST, io);
		}

		IExec->FreeSysObject(ASOT_PORT, mp);
	}

	return result;
}
#endif

#ifndef HAVE_RANDOM_UINT32
#define RNG_J   24
#define RNG_K   55
#define RNG_MAX UINT32_MAX;

struct rng_state {
	zip_uint32_t v[RNG_K + 1];
	zip_uint32_t x, j, k;
};

static zip_uint32_t __rand(struct rng_state *rng) {
	zip_uint32_t value;

	value = rng->v[rng->j] + rng->v[rng->k];

	rng->x = (rng->x + 1) % (RNG_K + 1);
	rng->j = (rng->j + 1) % (RNG_K + 1);
	rng->k = (rng->k + 1) % (RNG_K + 1);
	rng->v[rng->x] = value;

	return value;
}

static void __srand(struct rng_state *rng, zip_uint32_t seed) {
	int i;

	rng->v[0] = seed;

	for (i = 0; i <= RNG_K; i++) {
		rng->v[i] = 3 * rng->v[i - 1] + 257;
	}

	rng->x = RNG_K;
	rng->j = RNG_K - RNG_J;
	rng->k = 0;

	for (i = 0; i < 10000; i++) {
		__rand(rng);
	}
}

zip_uint32_t
zip_random_uint32(void) {
	static bool seeded = false;
	static struct rng_state rng;
	zip_uint32_t value;

	if (zip_secure_random((zip_uint8_t *)&value, sizeof(value))) {
		return value;
	}

	if (!seeded) {
		__srand(&rng, time(NULL));
	}

	return (zip_uint32_t)__rand(&rng);
}
#endif

