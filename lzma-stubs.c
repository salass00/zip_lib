#include <interfaces/lzma.h>

asm("\t.section\t\".text\"\n"
	"\t.align\t2\n"
	"\t.globl\t__CallLZMA\n"
	"\t.type\t__CallLZMA, @function\n"
	"__CallLZMA:\n"
	"\tlis\t%r11,ILZMA@ha\n"
	"\tlwz\t%r0,ILZMA@l(%r11)\n"
	"\tlwzx\t%r11,%r12,%r0\n"
	"\tmtctr\t%r11\n"
	"\tbctr\n"
	"\t.size\t__CallLZMA, .-__CallLZMA");

#define LZMACall(function, offset) \
asm("\t.section\t\".text\"\n" \
	"\t.align\t2\n" \
	"\t.globl\t" #function "\n" \
	"\t.type\t" #function ", @function\n" \
	#function ":\n" \
	"\tli\t%r12," #offset "\n" \
	"\tb\t__CallLZMA\n" \
	"\t.size\t" #function ", .-" #function);

LZMACall(lzma_code, 76)
LZMACall(lzma_end, 80)
LZMACall(lzma_stream_encoder, 176)
LZMACall(lzma_alone_encoder, 180)
LZMACall(lzma_stream_decoder, 192)
LZMACall(lzma_alone_decoder, 200)
LZMACall(lzma_lzma_preset, 404)

