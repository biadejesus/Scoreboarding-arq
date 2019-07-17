#include <stdio.h>
#include <stdlib.h>
#include "instrucoes.h"
#include "ula.c"

void decodificacao(unsigned int palavra[])
{

	int instrucao = palavra[0] << 24;
	instrucao += (palavra[1] << 16);
	instrucao += (palavra[2] << 8);
	instrucao += palavra[3];
	int tipo = instrucao >> 26 & MASCARA;

	switch (tipo)
	{

	case ESPECIAL:

		in.opcode = instrucao >> 26 & MASCARA;
		in.s_instrucao.rs = instrucao >> 21 & MASCARA;
		in.s_instrucao.rd = instrucao >> 16 & MASCARA;
		in.s_instrucao.rt = instrucao >> 11 & MASCARA;
		in.s_instrucao.shamt = instrucao >> 6 & MASCARA;
		in.s_instrucao.func = instrucao & 63;

		break;

	case ESPECIAL2:

		in.opcode = instrucao >> 26 & MASCARA;
		in.s2_instrucao.rs = instrucao >> 21 & MASCARA;
		in.s2_instrucao.rd = instrucao >> 16 & MASCARA;
		in.s2_instrucao.rt = instrucao >> 11 & MASCARA;
		in.s2_instrucao.shamt = instrucao >> 6 & MASCARA;
		in.s2_instrucao.func = instrucao & 63;

		break;

	case SALTO:

		in.opcode = instrucao >> 26 & MASCARA;
		in.j_instrucao.addr = instrucao & MASCARA;

		break;

	case REGIMM:

		in.opcode = instrucao >> 26 & MASCARA;
		in.r_instrucao.rs = instrucao >> 21 & MASCARA;
		in.r_instrucao.id = instrucao >> 16 & MASCARA;
		in.r_instrucao.offset = instrucao & MASCARA;
		break;

	default:

		in.opcode = instrucao >> 26 & MASCARA;
		in.i_instrucao.rs = instrucao >> 21 & MASCARA;
		in.i_instrucao.rt = instrucao >> 16 & MASCARA;
		in.i_instrucao.imediato = instrucao & MASCARA;

		break;
	}
}

void separarHILO(int in){

	bufferRegistradores[HI] = in >> 5;
	bufferRegistradores[LO] = (in << 5) / 32;
}

int juntarHILO(int hi, int lo){

	return hi << 5 + lo;
	
}
void execucao()
{
	int operacao = descobrirOperacao() int registrador;
	switch (operacao)
	{
	case ADD:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		bufferRegistradores[r1] = adicao(bancoRegistradores[r2], bancoRegistradores[r3]);
		break;
	case AND:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		bufferRegistradores[r1] = and(bancoRegistradores[r2], bancoRegistradores[r3]);
		break;
	case DIV:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		bufferRegistradores[r1] = divisao(bancoRegistradores[r2], bancoRegistradores[r3]);
		break;
	case JR:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		PC = bancoRegistradores[r2];
	case MFHI:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		bufferRegistradores[r1] = bancoRegistradores[HI];
		break;
	case MFLO:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		bufferRegistradores[r1] = bancoRegistradores[LO];
		break;
	case MOVN:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		if (not(igual(bancoRegistradores[r3], 0)))
			bufferRegistradores[r1] = bancoRegistradores[r2];
		break;
	case MOVZ:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		if (igual(bancoRegistradores[r3], 0))
			bufferRegistradores[r1] = bancoRegistradores[r2];
		break;
	case MTHI:
		r = in.s_instrucao.rs;
		bufferRegistradores[HI] = bancoRegistradores[r];
		break;
	case MTLO:
		r = in.s_instrucao.rs;
		bufferRegistradores[LO] = bancoRegistradores[r];
		break;
	case MULT:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		separarHILO(multiplicacao(bancoRegistradores[r2], bancoRegistradores[r3]))
		
		break;
	case NOP:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		bancoRegistradores[r1] = 0;
		bancoRegistradores[r2] = 0;
		bancoRegistradores[r3] = 0;
		break;
	case NOR:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		bancoRegistradores[r1] = nor(bancoRegistradores[r2], bancoRegistradores[r3]);
		break;
	case OR:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		bancoRegistradores[r1] = or(bancoRegistradores[r2], bancoRegistradores[r3]);
		break;
	case SUB:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		bancoRegistradores[r1] = subtracao(bancoRegistradores[r2], bancoRegistradores[r3]);
		break;
	case XOR:
		r1 = in.s_instrucao.rd;
		r2 = in.s_instrucao.rs;
		r3 = in.s_instrucao.rt;
		bancoRegistradores[r1] = xor(bancoRegistradores[r2], bancoRegistradores[r3]);
		break;
	case MADD:
		r2 = in.s2_instrucao.rs;
		r3 = in.s2_instrucao.rt;
		bufferResultado = multiplicacao(bancoRegistradores[r2], bancoRegistradores[r3]);
		juntarHILO()
		bufferResultado = adicao(bufferResultado, juntarHILO(bancoRegistradores[HI], bancoRegistradores[LO]));
	
		break;
	case MSUB:
		r2 = in.s2_instrucao.rs;
		r3 = in.s2_instrucao.rt;
		bancoRegistradores[HI] = subtracao(bancoRegistradores[HI], multiplicacao(bancoRegistradores[r2], bancoRegistradores[r3]));
		bancoRegistradores[LO] = subtracao(bancoRegistradores[LO], multiplicacao(bancoRegistradores[r2], bancoRegistradores[r3]));
		break;
	case MUL:
		r1 = in.s2_instrucao.rs;
		r2 = in.s2_instrucao.rs;
		r3 = in.s2_instrucao.rt;
		bancoRegistradores[HI] = subtracao(bancoRegistradores[HI], multiplicacao(bancoRegistradores[r2], bancoRegistradores[r3]));
		bancoRegistradores[LO] = subtracao(bancoRegistradores[LO], multiplicacao(bancoRegistradores[r2], bancoRegistradores[r3]));
		break;
	case ADDI:
		r1 = in.i_instrucao.rs;
		r2 = in.i_instrucao.rt;
		bancoRegistradores[r2] = adicao(bancoRegistradores[r1], in.i_instrucao.imediato);
		break;
	case ANDI:
		r1 = in.i_instrucao.rs;
		r2 = in.i_instrucao.rt;
		bancoRegistradores[r2] = and(bancoRegistradores[r1], in.i_instrucao.imediato);
		break;
	case B:
		r1 = in.i_instrucao.rs;
		r2 = in.i_instrucao.rt;
		PC += in.i_instrucao.imediato;
		break;
	case BEQ:
		r1 = in.i_instrucao.rs;
		r2 = in.i_instrucao.rt;
		if (igual(bancoRegistradores[r1], bancoRegistradores[r2]))
			PC += in.i_instrucao.imediato;
		break;
	case BEQL:
		r1 = in.i_instrucao.rs;
		r2 = in.i_instrucao.rt;
		if (igual(bancoRegistradores[r1], bancoRegistradores[r2]))
			PC += in.i_instrucao.imediato;
		break;
	case BGTZ:
		r1 = in.i_instrucao.rs;
		r2 = in.i_instrucao.rt;
		if (maior(bancoRegistradores[r1], 0))
			PC += in.i_instrucao.imediato;
		break;
	case BLEZ:
		r1 = in.i_instrucao.rs;
		r2 = in.i_instrucao.rt;
		if (menorIgual(bancoRegistradores[r1], 0))
			PC += in.i_instrucao.imediato;
		break;
	case BNE:
		r1 = in.i_instrucao.rs;
		r2 = in.i_instrucao.rt;
		if (not(igual(bancoRegistradores[r1], bancoRegistradores[r2])))
			PC += in.i_instrucao.imediato;
		break;
	case LUI:
		r2 = in.i_instrucao.rt;
		bancoRegistradores[r2] = shiftLeft(in.i_instrucao.imediato, 16);
		break;
	case ORI:
		r1 = in.i_instrucao.rs;
		r2 = in.i_instrucao.rt;
		bancoRegistradores[r2] = or (bancoRegistradores[r1], in.i_instrucao.imediato);
		break;
	case XORI:
		r1 = in.i_instrucao.rs;
		r2 = in.i_instrucao.rt;
		bancoRegistradores[r2] = xor(bancoRegistradores[r1], in.i_instrucao.imediato);
		break;
	case J:
		PC = in.j_instrucao.addr;
		break;
	case BGEZ:
		r1 = in.r_instrucao.rs;
		if (maiorIgual(bancoRegistradores[r1], 0))
			PC += in.r_instrucao.offset;

	case BLTZ:
		r1 = in.r_instrucao.rs;
		r2 = in.r_instrucao.offset;
		if (menor(bancoRegistradores[r1], 0))
			PC += in.r_instrucao.offset;
	default:
		printf("Operação não listada!");
		break;
	}
}