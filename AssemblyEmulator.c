#include <stdio.h>

unsigned char PC;
unsigned char memory[256];
unsigned char regs[4]; //A,B,C,D
char iname[6]; // global variable for debugging

void doInstructionAdd(unsigned char rs, unsigned char rd) { // Adds

	unsigned char rdval=regs[rd];
	unsigned char rsval=regs[rs];

	unsigned char ans = rdval + rsval;
	regs[rd]=ans; // writes back
}

void doInstructionSubtract(unsigned char rs, unsigned char rd) { //Subtracts
    unsigned char rdval=regs[rd];
	unsigned char rsval=regs[rs];

	unsigned char ans = rdval - rsval;
	regs[rd]=ans; // writes back
}

void doInstructionLoad(unsigned char rs, unsigned char rd) {
	unsigned char rsval=regs[rs];
    unsigned char rdval=regs[rd];
    regs[rd] = memory[rsval];
}

void doInstructionStore(unsigned char rs, unsigned char rd) {
    unsigned char rdval=regs[rd];
    unsigned char rsval=regs[rs];
    memory[rsval] = rdval;
}

void doInstructionSLI(unsigned char rd, unsigned char imm) {
    unsigned char rdval=regs[rd];
    unsigned char upper4bit = (rdval & 0b1111); // first 4 bits which is actually your lower for SLI
    unsigned char holder = (upper4bit << 4) + imm;
    regs[rd] = holder;
}

void doInstructionSKIPNZ(unsigned char rd) {
    unsigned char rdval=regs[rd];
    if (rdval != 0) {
        PC++;
    }
}

void doInstructionSKIPZ(unsigned char rd) {
    unsigned char rdval=regs[rd];
    if (rdval == 0) {
        PC++;
    }
}

void doInstructionJALR(unsigned char rd, unsigned char rs) {
    unsigned char rsval=regs[rs];
    regs[rd] = PC;
    PC = rsval;
}

//Extended Instruction Set Functions
void doInstructionIncrement(unsigned char rd) { //Increments 
    unsigned char rdval=regs[rd];
    unsigned char ans = rdval + 1;
    regs[rd]=ans;
}

void doInstructionDecrement(unsigned char rd) { // Decrements
    unsigned char rdval=regs[rd];
    unsigned char ans = rdval - 1;
    regs[rd]=ans;
}

void doInstructionNAND(unsigned char rd, unsigned char rs) { // performs nand
    unsigned char rdval=regs[rd];
    unsigned char rsval=regs[rs];
    unsigned char ans = ~(rdval&rsval);
    regs[rd] = ans;
}

void doInstructionIN(unsigned char rd) {
//    unsigned char num;
//    num = getchar();
    regs[rd] = getchar();
}

void doInstructionOUT(unsigned char rd) {
    unsigned char rdval=regs[rd];
    printf("%c", rdval);
    if (regs[rd] == 0x0d) {
        printf("\n");
    }
}

void step2_function() { // function runs code for step 2
     int i = 0; //counter for loop
    //code for step 2 test
    unsigned char program[21] = {0xff,0xfe,0x23,0x15,0xc8,0xcb,0xcd,0xcd,0x49,0x5f,0x74,0xcc,0xcd,0x1b,0xcc,0xde,0x5f,0xff,0xff,0x37,0x01};
    for (i = 0; i < 21; i++) {
        memory[i] = program[i];
    }
    memory[0xfe] = 6;

    // emulator code translated to c
    //regs[0] = memory[0xfe];
    //regs[1] = 0;
    //regs[2] = 3;

    while(regs[2] != 0) {
        regs[1] += regs[0];
        regs[2]--;
    }
    memory[0xff] = regs[1];

    printf("%d this is the ouput", memory[0xff]);

}

void inamechanger(char input[], int length) { //length is the length of the input array
    int j = 0;
    for (j = 0; j < 6; j++) {
        iname[j] = '\0';
    }
    for (j = 0; j < length; j++) {
        iname[j] = input[j];
    }
}


int main(){
    //set all registers to 0
    regs[0] = 0;
    regs[1] = 0;
    regs[2] = 0;
    regs[3] = 0;
    PC = 0;
	
    int i = 0; //counter for loop
    //Code For Step 2
    //unsigned char program[21] = {0xff,0xfe,0x23,0x15,0xc8,0xcb,0xcd,0xcd,0x49,0x5f,0x74,0xcc,0xcd,0x1b,0xcc,0xde,0x5f,0xff,0xff,0x37,0x01};
//    unsigned char program[29] = {0xc4, 0xc4, 0xc8, 0xc9, 0xff, 0xfe, 0x23, 0x1f, 0x1f, 0x7d, 0x7e, 0x15, 0x76, 0x1a, 0x7b, 0x1f, 0xcc, 0xcd, 0x13, 0x1f, 0xcc, 0xec,     0x40, 0x5f, 0x1f, 0xff, 0xff, 0x37, 0x01 };
//    unsigned char program[256] = {0xff, 0xff, 0x1a, 0x3b, 0xff, 0xff, 0x23, 0x20, 0xf7, 0xc4, 0x61, 0x60, 0xc5, 0xc4, 0xc8, 0xc8, 0xcd, 0xef, 0x41, 0x5f, 0x11, 0xcc, 0xcd, 0x7b, 0xcd, 0xcc, 0x5f, 0x10, 0x72, 0xcf, 0xfd, 0x5b, 0xff, 0xff, 0x23, 0x20, 0xc4, 0xf7, 0x61, 0x60, 0xcf, 0xfd, 0x5b, 0xc6, 0xc4, 0x86, 0xff, 0xff, 0x23, 0xc8, 0xc9, 0x72, 0x33, 0xcf, 0xfc, 0x41, 0x5f, 0xcc, 0xdc, 0x5f, 0x1, 0xc4, 0xe6, 0x11, 0x15, 0x74, 0xec, 0xcc, 0x67, 0x65, 0xdd, 0xcc, 0x45, 0x5f, 0xc7, 0xe6, 0x71, 0xdd, 0xcf, 0x5f, 0xd4, 0xc5, 0x71, 0x82, 0x5a}; 
unsigned char program[256] = {0xf0, 0xc1, 0xef, 0xde, 0x5b, 0x83, 0xcf, 0xcc, 0x13, 0xef, 0xff, 0x33, 0xf2, 0xc0, 0xc8, 0xe8, 0x24, 0xcd, 0xef, 0x44, 0x5f, 0xc6, 0xf6, 0x86, 0xcd, 0xfe, 0x5f, 0xd5, 0xe4, 0x86, 0x80, 0x89, 0xcd, 0xcc, 0x48, 0x5f, 0xc4, 0xf5, 0x86, 0xe8, 0x40, 0x5f, 0xc4, 0xf5, 0x86, 0xe3, 0xf1, 0xf6, 0xc4, 0x34, 0xe3, 0xf2, 0x15, 0x34, 0xe3, 0xf1, 0x20, 0xc4, 0xe5, 0x11, 0xee, 0xcc, 0x5b, 0x80, 0x5b, 0x80, 0x5b, 0xc4, 0xd6, 0x71, 0x5b, 0x80, 0x80, 0x5b, 0xc4, 0xd6, 0x71, 0x5b, 0x80, 0x5b, 0x80, 0x5b, 0xef, 0xfe, 0x27, 0xe3, 0xf1, 0x20, 0x20, 0xde, 0xdf, 0x40, 0x5f, 0xcc, 0xcf, 0x17, 0xdf, 0xcf, 0x45, 0x5f, 0xdf, 0xde, 0x5f, 0xdf, 0xcf, 0x85, 0x85, 0x45, 0x5f, 0x85, 0x45, 0x5f, 0xdf, 0xde, 0x5f, 0x15, 0x84, 0x45, 0x15, 0xfe, 0xcc, 0xf8, 0xc8, 0xe3, 0xf1, 0x20, 0x13, 0x78, 0x36, 0xe3, 0xf1, 0x24, 0x84, 0x34, 0xcf, 0xce, 0x44, 0x5f, 0xf2, 0xc0, 0xf4, 0xc4, 0xec, 0xfe, 0x29, 0x38, 0x80, 0x84, 0x40, 0x5f, 0xcc, 0xfc, 0xeb, 0xfb, 0x26, 0x85, 0x36, 0x44, 0x5f, 0x1, 0xf6, 0xc4, 0x64, 0x65, 0xfe, 0xcc, 0x17, 0xef, 0xcf, 0x44, 0x5f, 0x24, 0x45, 0x5f, 0xef, 0xfe, 0x27, 0x84, 0x37, 0xee, 0xcc, 0x5a, 0x24, 0x45, 0x5a, 0x86, 0x80, 0x57, 0x00, 0x0, 0x0, 0x0, 0x0, 0x67, 0x65, 0x6e, 0x73, 0x3f, 0x20, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (i = 0; i < sizeof(program); i++) { // change this to match program length
        memory[i] = program[i];
    }
    
    while(1) { //runs whole program multiple times

    unsigned char instruction = memory[PC];
    PC++;

    //Step 4 Code
    unsigned char rs = (instruction & 0b11); // rs is bits 7 and 8
    unsigned char rd = (instruction >> 2) & 0b11; // 5 and 6
    
    unsigned char imm = (((instruction >> 4) & 0b11) << 2) + rs; // imm is bits 3 and 4 and 7 and 8
    unsigned char opcode4bit = (instruction >> 4); // bits 1 to 4

    unsigned char opcodeSLI = (instruction >> 6); // bits 1 and 2 use this for SLI instruction
    unsigned char opcodeSKIP = (opcode4bit << 2) + rs; // gets first 4 bits plus last 2 which is used for opcode for SKIPS

    


    if (instruction == 00000001) { //this is HALT
        //inamechanger("HALT", 4);
        //printf("memory %x \n", memory[0xff]);
        return 0;
    }

    if (opcodeSLI == 0b11) { // for SLI instruction
        inamechanger("SLI", 3);
        doInstructionSLI(rd, imm);
    }

    else if (opcode4bit == 0b0100 && rs == 0b00) { // this is for SKIPZ
        inamechanger("SKIPZ", 5);
        doInstructionSKIPZ(rd);
    }

    else if (opcode4bit == 0b0100 && rs == 0b01) { // this is for SKIPNZ
         inamechanger("SKIPNZ", 6);
         doInstructionSKIPNZ(rd);
    }
    
    else if (opcode4bit == 0b0111) { //this is for ADD
        inamechanger("ADD", 3);
        doInstructionAdd(rs, rd);
    }
    else if (opcode4bit == 0b0001) { //this is for SUB
        inamechanger("SUB", 3);
        doInstructionSubtract(rs, rd);
    }
    else if (opcode4bit == 0b0010) { //this is LOAD
        inamechanger("LOAD", 4);
        doInstructionLoad(rs, rd);
    }
    else if (opcode4bit == 0b0011) { //this is STORE
        inamechanger("STORE", 5);
        doInstructionStore(rs, rd);
    }
    else if (opcode4bit == 0b0101) { //this is JALR
        inamechanger("JALR", 4);
        doInstructionJALR(rd, rs);
    }

    // Extended Instructions Below

    else if (opcode4bit == 0b0110) { //this is NAND
        inamechanger("NAND", 4);
        doInstructionNAND(rd, rs);
    }

    else if (opcode4bit == 0b1000 && rs == 0b00) {
        inamechanger("INC", 3);
        doInstructionIncrement(rd);
    }

    else if (opcode4bit == 0b1000 && rs == 0b01) {
        inamechanger("DEC", 3);
        doInstructionDecrement(rd);
    }

    else if (opcode4bit == 0b1000 && rs == 0b10) {
        inamechanger("OUT", 3);
        doInstructionOUT(rd);
    }
    
    else if (opcode4bit == 0b1000 && rs == 0b11) {
        inamechanger("IN", 2);
        doInstructionIN(rd);
    }

    //printf("PC=%x, inst=%x, op=%s, A=%x, B=%x, C=%x, D=%x\n",PC,instruction,iname, regs[0],regs[1],regs[2],regs[3]);  


    }

	return 0; 
}

