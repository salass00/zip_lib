/*
 * Copyright (C) 2014-2017 Fredrik Wikstrom <fredrik@a500.org>
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

#include <devices/timer.h>
#include <proto/exec.h>

/*
 * AmigaOS doesn't have /dev/urandom so we use the timer.device
 * entropy unit instead.
 *
 * There is also RANDOM: but many people probably don't have it
 * enabled as it's not mounted by default.
 */

bool
zip_random(zip_uint8_t *buffer, zip_uint16_t length)
{
	struct MsgPort *mp;
	struct IOStdReq *io;
	bool result = false;

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

	return result;
}

