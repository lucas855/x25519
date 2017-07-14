/**
 * Copyright (c) 2017 Armando Faz <armfazh@ic.unicamp.br>.
 * Institute of Computing.
 * University of Campinas, Brazil.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU Lesser General Public License as   
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "bytes.h"
#include "random.h"
#include "fp448_x64.h"

void random_EltFp448_1w_x64(uint64_t *A)
{
	random_bytes((uint8_t*)A,SIZE_ELEMENT_BYTES);
}

int compare_EltFp448_1w_x64(uint64_t *A, uint64_t *B)
{
	return compare_bytes((uint8_t*)A,(uint8_t*)B,SIZE_ELEMENT_BYTES);
}

void print_EltFp448_1w_x64(uint64_t *A)
{
	print_bytes((uint8_t*)A,SIZE_ELEMENT_BYTES);
}

void mul_448x448_integer_x64(uint64_t * c, uint64_t * a, uint64_t * b)
{
#ifdef __BMI2__
#ifdef __ADX__
	__asm__ __volatile__(
		"movq  0(%1), %%rdx;"/* A[0] */
		"mulx  0(%2), %%r8, %%r9;"/* A[0]*B[0] */  "xorl %%r10d,%%r10d;" "mov  %%r8, 0(%0);"
		"mulx  8(%2),%%r10,%%r11;"/* A[0]*B[1] */  "adcx %%r10, %%r9;"   "mov  %%r9, 8(%0);"
		"mulx 16(%2),%%r12,%%r13;"/* A[0]*B[2] */  "adcx %%r12,%%r11;"   "mov %%r11,16(%0);"
		"mulx 24(%2),%%r14,%%rax;"/* A[0]*B[3] */  "adcx %%r14,%%r13;"   "mov %%r13,24(%0);"
		"mulx 32(%2),%%r10,%%rbx;"/* A[0]*B[4] */  "adcx %%r10,%%rax;"   "mov %%rax,32(%0);" "movq $0, %%r10;"
		"mulx 40(%2),%%r12,%%rcx;"/* A[0]*B[5] */  "adcx %%r12,%%rbx;"   "mov %%rbx,40(%0);"
		"mulx 48(%2),%%r14,%%rdx;"/* A[0]*B[6] */  "adcx %%r14,%%rcx;"   "mov %%rcx,48(%0);"
        /***************************************/  "adcx %%r10,%%rdx;"   "mov %%rdx,56(%0);"

        "movq  8(%1), %%rdx;"/* A[1] */
        "mulx  0(%2), %%r8, %%r9;"/* A[1]*B[0] */  "xorl %%r10d,%%r10d;" "adox  8(%0), %%r8;" "mov  %%r8, 8(%0);"
        "mulx  8(%2),%%r10,%%r11;"/* A[1]*B[1] */  "adcx %%r10, %%r9;"   "adox 16(%0), %%r9;" "mov  %%r9,16(%0);"
        "mulx 16(%2),%%r12,%%r13;"/* A[1]*B[2] */  "adcx %%r12,%%r11;"   "adox 24(%0),%%r11;" "mov %%r11,24(%0);"
        "mulx 24(%2),%%r14,%%rax;"/* A[1]*B[3] */  "adcx %%r14,%%r13;"   "adox 32(%0),%%r13;" "mov %%r13,32(%0);"
        "mulx 32(%2),%%r10,%%rbx;"/* A[1]*B[4] */  "adcx %%r10,%%rax;"   "adox 40(%0),%%rax;" "mov %%rax,40(%0);" "movq $0,%%r10;"
        "mulx 40(%2),%%r12,%%rcx;"/* A[1]*B[5] */  "adcx %%r12,%%rbx;"   "adox 48(%0),%%rbx;" "mov %%rbx,48(%0);"
        "mulx 48(%2),%%r14,%%rdx;"/* A[1]*B[6] */  "adcx %%r14,%%rcx;"   "adox 56(%0),%%rcx;" "mov %%rcx,56(%0);"
        /***************************************/  "adcx %%r10,%%rdx;"   "adox  %%r10,%%rdx;" "mov %%rdx,64(%0);"

        "movq 16(%1), %%rdx;"/* A[2] */
        "mulx  0(%2), %%r8, %%r9;"/* A[2]*B[0] */  "xorl %%r10d,%%r10d;" "adox 16(%0), %%r8;" "mov  %%r8,16(%0);"
        "mulx  8(%2),%%r10,%%r11;"/* A[2]*B[1] */  "adcx %%r10, %%r9;"   "adox 24(%0), %%r9;" "mov  %%r9,24(%0);"
        "mulx 16(%2),%%r12,%%r13;"/* A[2]*B[2] */  "adcx %%r12,%%r11;"   "adox 32(%0),%%r11;" "mov %%r11,32(%0);"
        "mulx 24(%2),%%r14,%%rax;"/* A[2]*B[3] */  "adcx %%r14,%%r13;"   "adox 40(%0),%%r13;" "mov %%r13,40(%0);"
        "mulx 32(%2),%%r10,%%rbx;"/* A[2]*B[4] */  "adcx %%r10,%%rax;"   "adox 48(%0),%%rax;" "mov %%rax,48(%0);" "movq $0,%%r10;"
        "mulx 40(%2),%%r12,%%rcx;"/* A[2]*B[5] */  "adcx %%r12,%%rbx;"   "adox 56(%0),%%rbx;" "mov %%rbx,56(%0);"
        "mulx 48(%2),%%r14,%%rdx;"/* A[2]*B[6] */  "adcx %%r14,%%rcx;"   "adox 64(%0),%%rcx;" "mov %%rcx,64(%0);"
        /***************************************/  "adcx %%r10,%%rdx;"   "adox  %%r10,%%rdx;" "mov %%rdx,72(%0);"

        "movq 24(%1), %%rdx;"/* A[3] */
        "mulx  0(%2), %%r8, %%r9;"/* A[3]*B[0] */  "xorl %%r10d,%%r10d;" "adox 24(%0), %%r8;" "mov  %%r8,24(%0);"
        "mulx  8(%2),%%r10,%%r11;"/* A[3]*B[1] */  "adcx %%r10, %%r9;"   "adox 32(%0), %%r9;" "mov  %%r9,32(%0);"
        "mulx 16(%2),%%r12,%%r13;"/* A[3]*B[2] */  "adcx %%r12,%%r11;"   "adox 40(%0),%%r11;" "mov %%r11,40(%0);"
        "mulx 24(%2),%%r14,%%rax;"/* A[3]*B[3] */  "adcx %%r14,%%r13;"   "adox 48(%0),%%r13;" "mov %%r13,48(%0);"
        "mulx 32(%2),%%r10,%%rbx;"/* A[3]*B[4] */  "adcx %%r10,%%rax;"   "adox 56(%0),%%rax;" "mov %%rax,56(%0);" "movq $0,%%r10;"
        "mulx 40(%2),%%r12,%%rcx;"/* A[3]*B[5] */  "adcx %%r12,%%rbx;"   "adox 64(%0),%%rbx;" "mov %%rbx,64(%0);"
        "mulx 48(%2),%%r14,%%rdx;"/* A[3]*B[6] */  "adcx %%r14,%%rcx;"   "adox 72(%0),%%rcx;" "mov %%rcx,72(%0);"
        /***************************************/  "adcx %%r10,%%rdx;"   "adox  %%r10,%%rdx;" "mov %%rdx,80(%0);"

        "movq 32(%1), %%rdx;"/* A[4] */
        "mulx  0(%2), %%r8, %%r9;"/* A[4]*B[0] */  "xorl %%r10d,%%r10d;" "adox 32(%0), %%r8;" "mov  %%r8,32(%0);"
        "mulx  8(%2),%%r10,%%r11;"/* A[4]*B[1] */  "adcx %%r10, %%r9;"   "adox 40(%0), %%r9;" "mov  %%r9,40(%0);"
        "mulx 16(%2),%%r12,%%r13;"/* A[4]*B[2] */  "adcx %%r12,%%r11;"   "adox 48(%0),%%r11;" "mov %%r11,48(%0);"
        "mulx 24(%2),%%r14,%%rax;"/* A[4]*B[3] */  "adcx %%r14,%%r13;"   "adox 56(%0),%%r13;" "mov %%r13,56(%0);"
        "mulx 32(%2),%%r10,%%rbx;"/* A[4]*B[4] */  "adcx %%r10,%%rax;"   "adox 64(%0),%%rax;" "mov %%rax,64(%0);" "movq $0,%%r10;"
        "mulx 40(%2),%%r12,%%rcx;"/* A[4]*B[5] */  "adcx %%r12,%%rbx;"   "adox 72(%0),%%rbx;" "mov %%rbx,72(%0);"
        "mulx 48(%2),%%r14,%%rdx;"/* A[4]*B[6] */  "adcx %%r14,%%rcx;"   "adox 80(%0),%%rcx;" "mov %%rcx,80(%0);"
        /***************************************/  "adcx %%r10,%%rdx;"   "adox  %%r10,%%rdx;" "mov %%rdx,88(%0);"

        "movq 40(%1), %%rdx;"/* A[5] */
        "mulx  0(%2), %%r8, %%r9;"/* A[5]*B[0] */  "xorl %%r10d,%%r10d;" "adox 40(%0), %%r8;" "mov  %%r8,40(%0);"
        "mulx  8(%2),%%r10,%%r11;"/* A[5]*B[1] */  "adcx %%r10, %%r9;"   "adox 48(%0), %%r9;" "mov  %%r9,48(%0);"
        "mulx 16(%2),%%r12,%%r13;"/* A[5]*B[2] */  "adcx %%r12,%%r11;"   "adox 56(%0),%%r11;" "mov %%r11,56(%0);"
        "mulx 24(%2),%%r14,%%rax;"/* A[5]*B[3] */  "adcx %%r14,%%r13;"   "adox 64(%0),%%r13;" "mov %%r13,64(%0);"
        "mulx 32(%2),%%r10,%%rbx;"/* A[5]*B[4] */  "adcx %%r10,%%rax;"   "adox 72(%0),%%rax;" "mov %%rax,72(%0);" "movq $0,%%r10;"
        "mulx 40(%2),%%r12,%%rcx;"/* A[5]*B[5] */  "adcx %%r12,%%rbx;"   "adox 80(%0),%%rbx;" "mov %%rbx,80(%0);"
        "mulx 48(%2),%%r14,%%rdx;"/* A[5]*B[6] */  "adcx %%r14,%%rcx;"   "adox 88(%0),%%rcx;" "mov %%rcx,88(%0);"
        /***************************************/  "adcx %%r10,%%rdx;"   "adox  %%r10,%%rdx;" "mov %%rdx,96(%0);"

        "movq 48(%1), %%rdx;"/* A[6] */
        "mulx  0(%2), %%r8, %%r9;"/* A[6]*B[0] */  "xorl %%r10d,%%r10d;" "adox 48(%0), %%r8;" "mov  %%r8,48(%0);"
        "mulx  8(%2),%%r10,%%r11;"/* A[6]*B[1] */  "adcx %%r10, %%r9;"   "adox 56(%0), %%r9;" "mov  %%r9,56(%0);"
        "mulx 16(%2),%%r12,%%r13;"/* A[6]*B[2] */  "adcx %%r12,%%r11;"   "adox 64(%0),%%r11;" "mov %%r11,64(%0);"
        "mulx 24(%2),%%r14,%%rax;"/* A[6]*B[3] */  "adcx %%r14,%%r13;"   "adox 72(%0),%%r13;" "mov %%r13,72(%0);"
        "mulx 32(%2),%%r10,%%rbx;"/* A[6]*B[4] */  "adcx %%r10,%%rax;"   "adox 80(%0),%%rax;" "mov %%rax,80(%0);" "movq $0,%%r10;"
        "mulx 40(%2),%%r12,%%rcx;"/* A[6]*B[5] */  "adcx %%r12,%%rbx;"   "adox 88(%0),%%rbx;" "mov %%rbx,88(%0);"
        "mulx 48(%2),%%r14,%%rdx;"/* A[6]*B[6] */  "adcx %%r14,%%rcx;"   "adox 96(%0),%%rcx;" "mov %%rcx,96(%0);"
        /***************************************/  "adcx %%r10,%%rdx;"   "adox  %%r10,%%rdx;" "mov %%rdx,104(%0);"
	:
	: "r" (c), "r" (a), "r" (b)
	: "memory", "cc", "%rax", "%rbx", "%rcx", "%rdx",
      "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14"
	);
#else
	__asm__ __volatile__(
		"movq  0(%1),%%rdx ;" /* A[0] */
		"mulx  0(%2), %%r8, %%r9;"/* A[0]*B[0] */  /*****************/  "movq  %%r8, 0(%0);"
		"mulx  8(%2),%%r10,%%r11;"/* A[0]*B[1] */  "addq %%r10, %%r9;"  "movq  %%r9, 8(%0);"
		"mulx 16(%2),%%r12,%%r13;"/* A[0]*B[2] */  "adcq %%r12,%%r11;"  "movq %%r11,16(%0);"
		"mulx 24(%2),%%r14,%%rax;"/* A[0]*B[3] */  "adcq %%r14,%%r13;"  "movq %%r13,24(%0);"
		"mulx 32(%2),%%r10,%%rbx;"/* A[0]*B[4] */  "adcq %%r10,%%rax;"  "movq %%rax,32(%0);"
		"mulx 40(%2),%%r12,%%rcx;"/* A[0]*B[5] */  "adcq %%r12,%%rbx;"  "movq %%rbx,40(%0);"
		"mulx 48(%2),%%r14,%%rdx;"/* A[0]*B[6] */  "adcq %%r14,%%rcx;"  "movq %%rcx,48(%0);"
		/***************************************/  "adcq    $0,%%rdx;"  "movq %%rdx,56(%0);"

		"movq  8(%1),%%rdx ;" /* A[1] */
		"mulx  0(%2), %%r8, %%r9;"/* A[1]*B[0] */
		"mulx  8(%2),%%r10,%%r11;"/* A[1]*B[1] */  "addq %%r10, %%r9;"
		"mulx 16(%2),%%r12,%%r13;"/* A[1]*B[2] */  "adcq %%r12,%%r11;"
		"mulx 24(%2),%%r14,%%rax;"/* A[1]*B[3] */  "adcq %%r14,%%r13;"
		"mulx 32(%2),%%r10,%%rbx;"/* A[1]*B[4] */  "adcq %%r10,%%rax;"
		"mulx 40(%2),%%r12,%%rcx;"/* A[1]*B[5] */  "adcq %%r12,%%rbx;"
		"mulx 48(%2),%%r14,%%rdx;"/* A[1]*B[6] */  "adcq %%r14,%%rcx;"
		/***************************************/  "adcq    $0,%%rdx;"

		"addq  8(%0), %%r8;" "movq  %%r8, 8(%0);"
		"adcq 16(%0), %%r9;" "movq  %%r9,16(%0);"
		"adcq 24(%0),%%r11;" "movq %%r11,24(%0);"
		"adcq 32(%0),%%r13;" "movq %%r13,32(%0);"
		"adcq 40(%0),%%rax;" "movq %%rax,40(%0);"
		"adcq 48(%0),%%rbx;" "movq %%rbx,48(%0);"
		"adcq 56(%0),%%rcx;" "movq %%rcx,56(%0);"
        "adcq     $0,%%rdx;" "movq %%rdx,64(%0);"

		"movq 16(%1), %%rdx ;" /* A[2] */
		"mulx  0(%2), %%r8, %%r9;"/* A[2]*B[0] */
		"mulx  8(%2),%%r10,%%r11;"/* A[2]*B[1] */  "addq %%r10, %%r9;"
		"mulx 16(%2),%%r12,%%r13;"/* A[2]*B[2] */  "adcq %%r12,%%r11;"
		"mulx 24(%2),%%r14,%%rax;"/* A[2]*B[3] */  "adcq %%r14,%%r13;"
		"mulx 32(%2),%%r10,%%rbx;"/* A[2]*B[4] */  "adcq %%r10,%%rax;"
		"mulx 40(%2),%%r12,%%rcx;"/* A[2]*B[5] */  "adcq %%r12,%%rbx;"
		"mulx 48(%2),%%r14,%%rdx;"/* A[2]*B[6] */  "adcq %%r14,%%rcx;"
		/***************************************/  "adcq    $0,%%rdx;"

        "addq 16(%0), %%r8;" "movq  %%r8,16(%0);"
        "adcq 24(%0), %%r9;" "movq  %%r9,24(%0);"
        "adcq 32(%0),%%r11;" "movq %%r11,32(%0);"
        "adcq 40(%0),%%r13;" "movq %%r13,40(%0);"
        "adcq 48(%0),%%rax;" "movq %%rax,48(%0);"
        "adcq 56(%0),%%rbx;" "movq %%rbx,56(%0);"
        "adcq 64(%0),%%rcx;" "movq %%rcx,64(%0);"
        "adcq     $0,%%rdx;" "movq %%rdx,72(%0);"

		"movq 24(%1), %%rdx ;" /* A[3] */
		"mulx  0(%2), %%r8, %%r9;"/* A[3]*B[0] */
		"mulx  8(%2),%%r10,%%r11;"/* A[3]*B[1] */  "addq %%r10, %%r9;"
		"mulx 16(%2),%%r12,%%r13;"/* A[3]*B[2] */  "adcq %%r12,%%r11;"
		"mulx 24(%2),%%r14,%%rax;"/* A[3]*B[3] */  "adcq %%r14,%%r13;"
		"mulx 32(%2),%%r10,%%rbx;"/* A[3]*B[4] */  "adcq %%r10,%%rax;"
		"mulx 40(%2),%%r12,%%rcx;"/* A[3]*B[5] */  "adcq %%r12,%%rbx;"
		"mulx 48(%2),%%r14,%%rdx;"/* A[3]*B[6] */  "adcq %%r14,%%rcx;"
        /***************************************/  "adcq    $0,%%rdx;"

        "addq 24(%0), %%r8;" "movq  %%r8,24(%0);"
        "adcq 32(%0), %%r9;" "movq  %%r9,32(%0);"
        "adcq 40(%0),%%r11;" "movq %%r11,40(%0);"
        "adcq 48(%0),%%r13;" "movq %%r13,48(%0);"
        "adcq 56(%0),%%rax;" "movq %%rax,56(%0);"
        "adcq 64(%0),%%rbx;" "movq %%rbx,64(%0);"
        "adcq 72(%0),%%rcx;" "movq %%rcx,72(%0);"
        "adcq     $0,%%rdx;" "movq %%rdx,80(%0);"

		"movq 32(%1), %%rdx ;" /* A[4] */
		"mulx  0(%2), %%r8, %%r9;"/* A[4]*B[0] */
		"mulx  8(%2),%%r10,%%r11;"/* A[4]*B[1] */  "addq %%r10, %%r9;"
		"mulx 16(%2),%%r12,%%r13;"/* A[4]*B[2] */  "adcq %%r12,%%r11;"
		"mulx 24(%2),%%r14,%%rax;"/* A[4]*B[3] */  "adcq %%r14,%%r13;"
		"mulx 32(%2),%%r10,%%rbx;"/* A[4]*B[4] */  "adcq %%r10,%%rax;"
		"mulx 40(%2),%%r12,%%rcx;"/* A[4]*B[5] */  "adcq %%r12,%%rbx;"
		"mulx 48(%2),%%r14,%%rdx;"/* A[4]*B[6] */  "adcq %%r14,%%rcx;"
        /***************************************/  "adcq    $0,%%rdx;"

        "addq 32(%0), %%r8;" "movq  %%r8,32(%0);"
        "adcq 40(%0), %%r9;" "movq  %%r9,40(%0);"
        "adcq 48(%0),%%r11;" "movq %%r11,48(%0);"
        "adcq 56(%0),%%r13;" "movq %%r13,56(%0);"
        "adcq 64(%0),%%rax;" "movq %%rax,64(%0);"
        "adcq 72(%0),%%rbx;" "movq %%rbx,72(%0);"
        "adcq 80(%0),%%rcx;" "movq %%rcx,80(%0);"
        "adcq     $0,%%rdx;" "movq %%rdx,88(%0);"

		"movq 40(%1), %%rdx ;" /* A[5] */
		"mulx  0(%2), %%r8, %%r9;"/* A[5]*B[0] */
		"mulx  8(%2),%%r10,%%r11;"/* A[5]*B[1] */  "addq %%r10, %%r9;"
		"mulx 16(%2),%%r12,%%r13;"/* A[5]*B[2] */  "adcq %%r12,%%r11;"
		"mulx 24(%2),%%r14,%%rax;"/* A[5]*B[3] */  "adcq %%r14,%%r13;"
		"mulx 32(%2),%%r10,%%rbx;"/* A[5]*B[4] */  "adcq %%r10,%%rax;"
		"mulx 40(%2),%%r12,%%rcx;"/* A[5]*B[5] */  "adcq %%r12,%%rbx;"
		"mulx 48(%2),%%r14,%%rdx;"/* A[5]*B[6] */  "adcq %%r14,%%rcx;"
        /***************************************/  "adcq    $0,%%rdx;"

        "addq 40(%0), %%r8;" "movq  %%r8,40(%0);"
        "adcq 48(%0), %%r9;" "movq  %%r9,48(%0);"
        "adcq 56(%0),%%r11;" "movq %%r11,56(%0);"
        "adcq 64(%0),%%r13;" "movq %%r13,64(%0);"
        "adcq 72(%0),%%rax;" "movq %%rax,72(%0);"
        "adcq 80(%0),%%rbx;" "movq %%rbx,80(%0);"
        "adcq 88(%0),%%rcx;" "movq %%rcx,88(%0);"
        "adcq     $0,%%rdx;" "movq %%rdx,96(%0);"

		"movq 48(%1), %%rdx ;" /* A[6] */
		"mulx  0(%2), %%r8, %%r9;"/* A[6]*B[0] */
		"mulx  8(%2),%%r10,%%r11;"/* A[6]*B[1] */  "addq %%r10, %%r9;"
		"mulx 16(%2),%%r12,%%r13;"/* A[6]*B[2] */  "adcq %%r12,%%r11;"
		"mulx 24(%2),%%r14,%%rax;"/* A[6]*B[3] */  "adcq %%r14,%%r13;"
		"mulx 32(%2),%%r10,%%rbx;"/* A[6]*B[4] */  "adcq %%r10,%%rax;"
		"mulx 40(%2),%%r12,%%rcx;"/* A[6]*B[5] */  "adcq %%r12,%%rbx;"
		"mulx 48(%2),%%r14,%%rdx;"/* A[6]*B[6] */  "adcq %%r14,%%rcx;"
        /***************************************/  "adcq    $0,%%rdx;"

        "addq 48(%0), %%r8;" "movq  %%r8,48(%0);"
        "adcq 56(%0), %%r9;" "movq  %%r9,56(%0);"
        "adcq 64(%0),%%r11;" "movq %%r11,64(%0);"
        "adcq 72(%0),%%r13;" "movq %%r13,72(%0);"
        "adcq 80(%0),%%rax;" "movq %%rax,80(%0);"
        "adcq 88(%0),%%rbx;" "movq %%rbx,88(%0);"
        "adcq 96(%0),%%rcx;" "movq %%rcx,96(%0);"
        "adcq     $0,%%rdx;" "movq %%rdx,104(%0);"
	:
	: "r" (c), "r" (a), "r" (b)
	: "memory", "cc", "%rax", "%rbx", "%rcx", "%rdx",
	  "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14"
	);
#endif
#else    /* Without BMI2 */
	/**
	* TODO: Multiplications using MULQ instruction.
	**/
#endif
}

void sqr_448x448_integer_x64(uint64_t * c, uint64_t * a)
{
#ifdef __BMI2__
#ifdef __ADX__
    __asm__ __volatile__(
        "movq   (%1), %%rdx        # A[0]   \n\t"
        "mulx  %%rdx, %%rax, %%rbx # A[0]^2 \n\t"
        "movq  8(%1), %%rdx        # A[1]   \n\t"
        "mulx  %%rdx,  %%r8, %%r9  # A[1]^2 \n\t"
        "movq  %%rax,   (%0) \n\t"
        "movq  %%rbx,  8(%0) \n\t"
        "movq   %%r8, 16(%0) \n\t"
        "movq   %%r9, 24(%0) \n\t"
        "movq 16(%1), %%rdx        # A[2]   \n\t"
        "mulx  %%rdx, %%r10, %%r11 # A[2]^2 \n\t"
        "movq 24(%1), %%rdx        # A[3]   \n\t"
        "mulx  %%rdx, %%r12, %%r13 # A[3]^2 \n\t"
        "movq  %%r10, 32(%0) \n\t"
        "movq  %%r11, 40(%0) \n\t"
        "movq  %%r12, 48(%0) \n\t"
        "movq  %%r13, 56(%0) \n\t"
        "movq 32(%1), %%rdx        # A[4]   \n\t"
        "mulx  %%rdx, %%rax, %%rbx # A[4]^2 \n\t"
        "movq 40(%1), %%rdx        # A[5]   \n\t"
        "mulx  %%rdx,  %%r8, %%r9  # A[5]^2 \n\t"
        "movq  %%rax, 64(%0) \n\t"
        "movq  %%rbx, 72(%0) \n\t"
        "movq   %%r8, 80(%0) \n\t"
        "movq   %%r9, 88(%0) \n\t"
        "movq 48(%1), %%rdx        # A[6]   \n\t"
        "mulx  %%rdx, %%r10, %%r11 # A[6]^2 \n\t"
        "movq  %%r10, 96(%0) \n\t"
        "movq  %%r11,104(%0) \n\t"

        "movq   (%1), %%rdx      # A[0]     \n\t"
        "mulx  8(%1), %%r8, %%r9 # A[0]A[1] \n\t"  "xorl %%r10d,%%r10d\n\t"  "adox  %%r8,  %%r8 \n\t"
        "mulx 16(%1),%%r10,%%r11 # A[0]A[2] \n\t"  "adcx %%r10,  %%r9 \n\t"  "adox  %%r9,  %%r9 \n\t"
        "mulx 24(%1),%%r12,%%r13 # A[0]A[3] \n\t"  "adcx %%r12, %%r11 \n\t"  "adox %%r11, %%r11 \n\t"
        "mulx 32(%1),%%r14,%%rax # A[0]A[4] \n\t"  "adcx %%r14, %%r13 \n\t"  "adox %%r13, %%r13 \n\t"
        "mulx 40(%1),%%r10,%%rbx # A[0]A[5] \n\t"  "adcx %%r10, %%rax \n\t"  "adox %%rax, %%rax \n\t"
        "mulx 48(%1),%%r12,%%rcx # A[0]A[6] \n\t"  "adcx %%r12, %%rbx \n\t"  "adox %%rbx, %%rbx \n\t"
        "movq 24(%1),%%rdx       # A[3]     \n\t"  "movq    $0, %%r12 \n\t"  "movq    $0, %%r10 \n\t"
        "mulx 32(%1),%%r14,%%rdx # A[3]A[4] \n\t"  "adcx %%r14, %%rcx \n\t"  "adox %%rcx, %%rcx \n\t"
        /***************************************/  "adcx %%r12, %%rdx \n\t"  "adox %%rdx, %%rdx \n\t"
        /*****************************************************************/  "adox %%r12, %%r10 \n\t"

        "addq  8(%0), %%r8\n\t" "movq  %%r8, 8(%0)\n\t"
        "adcq 16(%0), %%r9\n\t" "movq  %%r9,16(%0)\n\t"
        "adcq 24(%0),%%r11\n\t" "movq %%r11,24(%0)\n\t"
        "adcq 32(%0),%%r13\n\t" "movq %%r13,32(%0)\n\t"
        "adcq 40(%0),%%rax\n\t" "movq %%rax,40(%0)\n\t"
        "adcq 48(%0),%%rbx\n\t" "movq %%rbx,48(%0)\n\t"
        "adcq 56(%0),%%rcx\n\t" "movq %%rcx,56(%0)\n\t"
        "adcq 64(%0),%%rdx\n\t" "movq %%rdx,64(%0)\n\t"
        "adcq 72(%0),%%r10\n\t" "movq %%r10,72(%0)\n\t"

        "movq  8(%1),%%rdx        # A[1]    \n\t"
        "mulx 16(%1), %%r8,  %%r9 # A[1]A[2]\n\t"  "xorl %%r10d,%%r10d\n\t"  "adox  %%r8,  %%r8 \n\t"
        "mulx 24(%1),%%r10, %%r11 # A[1]A[3]\n\t"  "adcx %%r10,  %%r9 \n\t"  "adox  %%r9,  %%r9 \n\t"
        "mulx 32(%1),%%r12, %%r13 # A[1]A[4]\n\t"  "adcx %%r12, %%r11 \n\t"  "adox %%r11, %%r11 \n\t"
        "mulx 40(%1),%%r14, %%rax # A[1]A[5]\n\t"  "adcx %%r14, %%r13 \n\t"  "adox %%r13, %%r13 \n\t"
        "mulx 48(%1),%%r10, %%rbx # A[1]A[6]\n\t"  "adcx %%r10, %%rax \n\t"  "adox %%rax, %%rax \n\t"
        "movq 40(%1),%%rdx        # A[5]    \n\t"
        "mulx 24(%1),%%r12, %%rcx # A[5]A[3]\n\t"  "adcx %%r12, %%rbx \n\t"  "adox %%rbx, %%rbx \n\t"
        "mulx 32(%1),%%r14, %%rdx # A[5]A[4]\n\t"  "adcx %%r14, %%rcx \n\t"  "adox %%rcx, %%rcx \n\t"
        /***************************************/  "movq    $0, %%r12 \n\t"  "movq    $0, %%r10 \n\t"
        /***************************************/  "adcx %%r12, %%rdx \n\t"  "adox %%rdx, %%rdx \n\t"
        /*****************************************************************/  "adox %%r12, %%r10 \n\t"

        "addq 24(%0), %%r8\n\t" "movq  %%r8,24(%0)\n\t"
        "adcq 32(%0), %%r9\n\t" "movq  %%r9,32(%0)\n\t"
        "adcq 40(%0),%%r11\n\t" "movq %%r11,40(%0)\n\t"
        "adcq 48(%0),%%r13\n\t" "movq %%r13,48(%0)\n\t"
        "adcq 56(%0),%%rax\n\t" "movq %%rax,56(%0)\n\t"
        "adcq 64(%0),%%rbx\n\t" "movq %%rbx,64(%0)\n\t"
        "adcq 72(%0),%%rcx\n\t" "movq %%rcx,72(%0)\n\t"
        "adcq 80(%0),%%rdx\n\t" "movq %%rdx,80(%0)\n\t"
        "adcq 88(%0),%%r10\n\t" "movq %%r10,88(%0)\n\t"

        "movq 16(%1), %%rdx        # A[2]     \n\t"
        "mulx 24(%1),  %%r8,  %%r9 # A[2]A[3] \n\t"  "xorl %%r10d,%%r10d\n\t"  "adox  %%r8,  %%r8 \n\t"
        "mulx 32(%1), %%r10, %%r11 # A[2]A[4] \n\t"  "adcx %%r10,  %%r9 \n\t"  "adox  %%r9,  %%r9 \n\t"
        "mulx 40(%1), %%r12, %%r13 # A[2]A[5] \n\t"  "adcx %%r12, %%r11 \n\t"  "adox %%r11, %%r11 \n\t"
        "mulx 48(%1), %%r14, %%rax # A[2]A[6] \n\t"  "adcx %%r14, %%r13 \n\t"  "adox %%r13, %%r13 \n\t"
        "movq 48(%1), %%rdx        # A[6]     \n\t"
        "mulx 24(%1), %%r10, %%rbx # A[6]A[3] \n\t"  "adcx %%r10, %%rax \n\t"  "adox %%rax, %%rax \n\t"
        "mulx 32(%1), %%r12, %%rcx # A[6]A[4] \n\t"  "adcx %%r12, %%rbx \n\t"  "adox %%rbx, %%rbx \n\t"
        "mulx 40(%1), %%r14, %%rdx # A[6]A[5] \n\t"  "adcx %%r14, %%rcx \n\t"  "adox %%rcx, %%rcx \n\t"
        /*****************************************/  "movq    $0, %%r12 \n\t"  "movq    $0, %%r10 \n\t"
        /*****************************************/  "adcx %%r12, %%rdx \n\t"  "adox %%rdx, %%rdx \n\t"
        /*******************************************************************/  "adox %%r12, %%r10 \n\t"

        "addq  40(%0), %%r8\n\t" "movq  %%r8, 40(%0)\n\t"
        "adcq  48(%0), %%r9\n\t" "movq  %%r9, 48(%0)\n\t"
        "adcq  56(%0),%%r11\n\t" "movq %%r11, 56(%0)\n\t"
        "adcq  64(%0),%%r13\n\t" "movq %%r13, 64(%0)\n\t"
        "adcq  72(%0),%%rax\n\t" "movq %%rax, 72(%0)\n\t"
        "adcq  80(%0),%%rbx\n\t" "movq %%rbx, 80(%0)\n\t"
        "adcq  88(%0),%%rcx\n\t" "movq %%rcx, 88(%0)\n\t"
        "adcq  96(%0),%%rdx\n\t" "movq %%rdx, 96(%0)\n\t"
        "adcq 104(%0),%%r10\n\t" "movq %%r10,104(%0)\n\t"
    :
    : "r"  (c), "r" (a)
    : "memory", "cc", "%rax", "%rbx", "%rcx", "%rdx",
      "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14"
    );
#else
	__asm__ __volatile__(
		"movq   (%1), %%rdx        # A[0]   \n\t"
		"mulx  %%rdx, %%rax, %%rbx # A[0]^2 \n\t"
		"movq  8(%1), %%rdx        # A[1]   \n\t"
		"mulx  %%rdx,  %%r8, %%r9  # A[1]^2 \n\t"
		"movq  %%rax,   (%0) \n\t"
		"movq  %%rbx,  8(%0) \n\t"
		"movq   %%r8, 16(%0) \n\t"
		"movq   %%r9, 24(%0) \n\t"
		"movq 16(%1), %%rdx        # A[2]   \n\t"
		"mulx  %%rdx, %%r10, %%r11 # A[2]^2 \n\t"
		"movq 24(%1), %%rdx        # A[3]   \n\t"
		"mulx  %%rdx, %%r12, %%r13 # A[3]^2 \n\t"
		"movq  %%r10, 32(%0) \n\t"
		"movq  %%r11, 40(%0) \n\t"
		"movq  %%r12, 48(%0) \n\t"
		"movq  %%r13, 56(%0) \n\t"
		"movq 32(%1), %%rdx        # A[4]   \n\t"
		"mulx  %%rdx, %%rax, %%rbx # A[4]^2 \n\t"
		"movq 40(%1), %%rdx        # A[5]   \n\t"
		"mulx  %%rdx,  %%r8, %%r9  # A[5]^2 \n\t"
		"movq  %%rax, 64(%0) \n\t"
		"movq  %%rbx, 72(%0) \n\t"
		"movq   %%r8, 80(%0) \n\t"
		"movq   %%r9, 88(%0) \n\t"
		"movq 48(%1), %%rdx        # A[6]   \n\t"
		"mulx  %%rdx, %%r10, %%r11 # A[6]^2 \n\t"
		"movq  %%r10, 96(%0) \n\t"
		"movq  %%r11,104(%0) \n\t"

		"movq   (%1), %%rdx        # A[0]     \n\t"
		"mulx  8(%1),  %%r8,  %%r9 # A[0]A[1] \n\t"
		"mulx 16(%1), %%r10, %%r11 # A[0]A[2] \n\t"   "addq %%r10,  %%r9 \n\t"
		"mulx 24(%1), %%r12, %%r13 # A[0]A[3] \n\t"   "adcq %%r12, %%r11 \n\t"
		"mulx 32(%1), %%r14, %%rax # A[0]A[4] \n\t"   "adcq %%r14, %%r13 \n\t"
		"mulx 40(%1), %%r10, %%rbx # A[0]A[5] \n\t"   "adcq %%r10, %%rax \n\t"
		"mulx 48(%1), %%r12, %%rcx # A[0]A[6] \n\t"   "adcq %%r12, %%rbx \n\t"
		"movq 24(%1), %%rdx        # A[3]     \n\t"
		"mulx 32(%1), %%r14, %%rdx # A[3]A[4] \n\t"   "adcq %%r14, %%rcx \n\t"
        /*****************************************/   "adcq    $0, %%rdx \n\t"
		"xorq  %%r10, %%r10  \n\t"
		"shldq $1,%%rdx,%%r10\n\t"
		"shldq $1,%%rcx,%%rdx\n\t"
		"shldq $1,%%rbx,%%rcx\n\t"
		"shldq $1,%%rax,%%rbx\n\t"
		"shldq $1,%%r13,%%rax\n\t"
		"shldq $1,%%r11,%%r13\n\t"
		"shldq $1, %%r9,%%r11\n\t"
		"shldq $1, %%r8, %%r9\n\t"
		"shlq  $1, %%r8      \n\t"

		"addq  8(%0), %%r8\n\t"  "movq  %%r8, 8(%0)\n\t"
		"adcq 16(%0), %%r9\n\t"  "movq  %%r9,16(%0)\n\t"
		"adcq 24(%0),%%r11\n\t"  "movq %%r11,24(%0)\n\t"
		"adcq 32(%0),%%r13\n\t"  "movq %%r13,32(%0)\n\t"
		"adcq 40(%0),%%rax\n\t"  "movq %%rax,40(%0)\n\t"
		"adcq 48(%0),%%rbx\n\t"  "movq %%rbx,48(%0)\n\t"
		"adcq 56(%0),%%rcx\n\t"  "movq %%rcx,56(%0)\n\t"
		"adcq 64(%0),%%rdx\n\t"  "movq %%rdx,64(%0)\n\t"
		"adcq 72(%0),%%r10\n\t"  "movq %%r10,72(%0)\n\t"

		"movq  8(%1), %%rdx        # A[1]     \n\t"
		"mulx 16(%1),  %%r8,  %%r9 # A[1]A[2] \n\t"
		"mulx 24(%1), %%r10, %%r11 # A[1]A[3] \n\t"   "addq %%r10,  %%r9 \n\t"
		"mulx 32(%1), %%r12, %%r13 # A[1]A[4] \n\t"   "adcq %%r12, %%r11 \n\t"
		"mulx 40(%1), %%r14, %%rax # A[1]A[5] \n\t"   "adcq %%r14, %%r13 \n\t"
		"mulx 48(%1), %%r10, %%rbx # A[1]A[6] \n\t"   "adcq %%r10, %%rax \n\t"
		"movq 40(%1), %%rdx        # A[5]     \n\t"
		"mulx 24(%1), %%r12, %%rcx # A[5]A[3] \n\t"   "adcq %%r12, %%rbx \n\t"
		"mulx 32(%1), %%r14, %%rdx # A[5]A[4] \n\t"   "adcq %%r14, %%rcx \n\t"
	    /*****************************************/   "adcq    $0, %%rdx \n\t"

		"xorq  %%r10, %%r10  \n\t"
		"shldq $1,%%rdx,%%r10\n\t"
		"shldq $1,%%rcx,%%rdx\n\t"
		"shldq $1,%%rbx,%%rcx\n\t"
		"shldq $1,%%rax,%%rbx\n\t"
		"shldq $1,%%r13,%%rax\n\t"
		"shldq $1,%%r11,%%r13\n\t"
		"shldq $1, %%r9,%%r11\n\t"
		"shldq $1, %%r8, %%r9\n\t"
		"shlq  $1, %%r8      \n\t"

		"addq 24(%0), %%r8\n\t"  "movq  %%r8,24(%0)\n\t"
		"adcq 32(%0), %%r9\n\t"  "movq  %%r9,32(%0)\n\t"
		"adcq 40(%0),%%r11\n\t"  "movq %%r11,40(%0)\n\t"
		"adcq 48(%0),%%r13\n\t"  "movq %%r13,48(%0)\n\t"
		"adcq 56(%0),%%rax\n\t"  "movq %%rax,56(%0)\n\t"
		"adcq 64(%0),%%rbx\n\t"  "movq %%rbx,64(%0)\n\t"
		"adcq 72(%0),%%rcx\n\t"  "movq %%rcx,72(%0)\n\t"
		"adcq 80(%0),%%rdx\n\t"  "movq %%rdx,80(%0)\n\t"
		"adcq 88(%0),%%r10\n\t"  "movq %%r10,88(%0)\n\t"

		"movq 16(%1), %%rdx        # A[2]     \n\t"
		"mulx 24(%1),  %%r8,  %%r9 # A[2]A[3] \n\t"
		"mulx 32(%1), %%r10, %%r11 # A[2]A[4] \n\t"  "addq %%r10,  %%r9 \n\t"
		"mulx 40(%1), %%r12, %%r13 # A[2]A[5] \n\t"  "adcq %%r12, %%r11 \n\t"
		"mulx 48(%1), %%r14, %%rax # A[2]A[6] \n\t"  "adcq %%r14, %%r13 \n\t"
		"movq 48(%1), %%rdx        # A[6]     \n\t"
		"mulx 24(%1), %%r10, %%rbx # A[6]A[3] \n\t"  "adcq %%r10, %%rax \n\t"
		"mulx 32(%1), %%r12, %%rcx # A[6]A[4] \n\t"  "adcq %%r12, %%rbx \n\t"
		"mulx 40(%1), %%r14, %%rdx # A[6]A[5] \n\t"  "adcq %%r14, %%rcx \n\t"
		/*****************************************/  "adcq    $0, %%rdx \n\t"
		"xorq  %%r10, %%r10  \n\t"
		"shldq $1,%%rdx,%%r10\n\t"
		"shldq $1,%%rcx,%%rdx\n\t"
		"shldq $1,%%rbx,%%rcx\n\t"
		"shldq $1,%%rax,%%rbx\n\t"
		"shldq $1,%%r13,%%rax\n\t"
		"shldq $1,%%r11,%%r13\n\t"
		"shldq $1, %%r9,%%r11\n\t"
		"shldq $1, %%r8, %%r9\n\t"
		"shlq  $1, %%r8      \n\t"

		"addq  40(%0), %%r8\n\t"   "movq  %%r8, 40(%0)\n\t"
		"adcq  48(%0), %%r9\n\t"   "movq  %%r9, 48(%0)\n\t"
		"adcq  56(%0),%%r11\n\t"   "movq %%r11, 56(%0)\n\t"
		"adcq  64(%0),%%r13\n\t"   "movq %%r13, 64(%0)\n\t"
		"adcq  72(%0),%%rax\n\t"   "movq %%rax, 72(%0)\n\t"
		"adcq  80(%0),%%rbx\n\t"   "movq %%rbx, 80(%0)\n\t"
		"adcq  88(%0),%%rcx\n\t"   "movq %%rcx, 88(%0)\n\t"
		"adcq  96(%0),%%rdx\n\t"   "movq %%rdx, 96(%0)\n\t"
		"adcq 104(%0),%%r10\n\t"   "movq %%r10,104(%0)\n\t"
	:
	: "r"  (c), "r" (a)
	: "memory", "cc", "%rax", "%rbx", "%rcx", "%rdx", "%r8",
      "%r9", "%r10", "%r11", "%r12", "%r13", "%r14"
	);
#endif
#else    /* Without BMI2 */
	/**
	* TODO: Multiplications using MULQ instruction.
	**/
#endif
}

void red_EltFp448_1w_x64(uint64_t * c, uint64_t * a)
{
#if __ADX__
	__asm__ __volatile__ (
	    /* [c13,c12,c11,c10] mod p  */
		"movq  80(%1),  %%r8 ;"	"movq  %%r8, %%rax ;"
		"movq  88(%1),  %%r9 ;"	"movq  %%r9, %%rbx ;"
		"movq  96(%1), %%r10 ;"	"movq %%r10, %%rcx ;"
		"movq 104(%1), %%r11 ;"	"movq %%r11, %%rdx ;"
		"shrq $32, %%r8 ;"
		"shlq $32, %%r8 ;"
		"movl  $0, 84(%1) ;"

		"shrdq $32, %%rbx, %%rax ;"
		"shrdq $32, %%rcx, %%rbx ;"
		"shrdq $32, %%rdx, %%rcx ;"
		"shrq  $32, %%rdx ;"

		"clc ;"
		"adcx 24(%1),  %%r8 ;"	"movq   %%r8, 24(%0) ;"
		"adcx 32(%1),  %%r9 ;"	"movq   %%r9, 32(%0) ;"
		"adcx 40(%1), %%r10 ;"	"movq  %%r10, 40(%0) ;"
		"adcx 48(%1), %%r11 ;"	"movq  %%r11, 48(%0) ;"
		"adcx 56(%1), %%rax ;"	"movq  %%rax,   %%r8 ;"
		"adcx 64(%1), %%rbx ;"	"movq  %%rbx,   %%r9 ;"
		"adcx 72(%1), %%rcx ;"	"movq  %%rcx,  %%r10 ;"
		"adcx 80(%1), %%rdx ;"	"movq  %%rdx,  %%r11 ;"
	    /* [c10,c9,c8,c7] mod p  */
		"xorq  %%r12, %%r12 ;"
		"shldq  $32, %%rdx, %%r12 ;"
		"shldq  $32, %%rcx, %%rdx ;"
		"shldq  $32, %%rbx, %%rcx ;"
		"shldq  $32, %%rax, %%rbx ;"
		"shlq   $32, %%rax ;"

		"addq %%r11, %%rax ;"
		"adcq $0, 32(%0) ;"

		"clc ;"
		"xorq  %%r11, %%r11 ;"
		"adcx   (%1),  %%r8 ;"
		"adcx  8(%1),  %%r9 ;"
		"adcx 16(%1), %%r10 ;"
		"adcx 24(%0), %%rax ;"
		"adcx 32(%0), %%rbx ;"
		"adcx 40(%0), %%rcx ;"
		"adcx 48(%0), %%rdx ;"
		"adcx  %%r11, %%r12 ;"
	    /* [c7] mod p  */
		"addq %%r12,   %%r8 ;"
		"adcq    $0,   %%r9 ;"
		"shlq   $32,  %%r12 ;"
		"addq %%r12,  %%rax ;"
		"adcq    $0,  %%rbx ;"

		"movq  %%r8,   (%0) ;"
		"movq  %%r9,  8(%0) ;"
		"movq %%r10, 16(%0) ;"
		"movq %%rax, 24(%0) ;"
		"movq %%rbx, 32(%0) ;"
		"movq %%rcx, 40(%0) ;"
		"movq %%rdx, 48(%0) ;"
	:
	: "r" (c), "r" (a)
	: "memory", "cc", "%rax", "%rbx", "%rcx", "%rdx",
	  "%r8", "%r9", "%r10", "%r11", "%r12"
	);
#else
	__asm__ __volatile__ (
	    /* [c13,c12,c11,c10] mod p  */
		"movq  80(%1),  %%r8 ;"	"movq  %%r8, %%rax ;"
		"movq  88(%1),  %%r9 ;"	"movq  %%r9, %%rbx ;"
		"movq  96(%1), %%r10 ;"	"movq %%r10, %%rcx ;"
		"movq 104(%1), %%r11 ;"	"movq %%r11, %%rdx ;"
		"shrq $32, %%r8 ;"
		"shlq $32, %%r8 ;"
		"movl  $0, 84(%1) ;"

		"shrdq $32, %%rbx, %%rax ;"
		"shrdq $32, %%rcx, %%rbx ;"
		"shrdq $32, %%rdx, %%rcx ;"
		"shrq  $32, %%rdx ;"

		"addq 24(%1),  %%r8 ;"	"movq   %%r8, 24(%0) ;"
		"adcq 32(%1),  %%r9 ;"	"movq   %%r9, 32(%0) ;"
		"adcq 40(%1), %%r10 ;"	"movq  %%r10, 40(%0) ;"
		"adcq 48(%1), %%r11 ;"	"movq  %%r11, 48(%0) ;"
		"adcq 56(%1), %%rax ;"	"movq  %%rax,   %%r8 ;"
		"adcq 64(%1), %%rbx ;"	"movq  %%rbx,   %%r9 ;"
		"adcq 72(%1), %%rcx ;"	"movq  %%rcx,  %%r10 ;"
		"adcq 80(%1), %%rdx ;"	"movq  %%rdx,  %%r11 ;"
	    /* [c10,c9,c8,c7] mod p  */
		"xorq  %%r12, %%r12 ;"
		"shldq  $32, %%rdx, %%r12 ;"
		"shldq  $32, %%rcx, %%rdx ;"
		"shldq  $32, %%rbx, %%rcx ;"
		"shldq  $32, %%rax, %%rbx ;"
		"shlq   $32, %%rax ;"

		"addq %%r11, %%rax ;"
		"adcq $0, 32(%0) ;"

		"addq   (%1),  %%r8 ;"
		"adcq  8(%1),  %%r9 ;"
		"adcq 16(%1), %%r10 ;"
		"adcq 24(%0), %%rax ;"
		"adcq 32(%0), %%rbx ;"
		"adcq 40(%0), %%rcx ;"
		"adcq 48(%0), %%rdx ;"
		"adcq     $0, %%r12 ;"
	    /* [c7] mod p  */
		"addq %%r12,   %%r8 ;"
		"adcq    $0,   %%r9 ;"
		"shlq   $32,  %%r12 ;"
		"addq %%r12,  %%rax ;"
		"adcq    $0,  %%rbx ;"

		"movq  %%r8,   (%0) ;"
		"movq  %%r9,  8(%0) ;"
		"movq %%r10, 16(%0) ;"
		"movq %%rax, 24(%0) ;"
		"movq %%rbx, 32(%0) ;"
		"movq %%rcx, 40(%0) ;"
		"movq %%rdx, 48(%0) ;"
	:
	: "r" (c), "r" (a)
	: "memory", "cc", "%rax", "%rbx", "%rcx", "%rdx",
	  "%r8", "%r9", "%r10", "%r11", "%r12"
	);
#endif
}

inline void add_EltFp448_1w_x64(uint64_t * c, uint64_t * a, uint64_t * b)
{
#if __ADX__
	__asm__ __volatile__(
		"movq    (%2),  %%rax ;"
		"movq   8(%2),  %%rcx ;"
		"movq  16(%2),  %%rdx ;"
		"movq  24(%2),  %%r8  ;"
		"movq  32(%2),  %%r9  ;"
		"movq  40(%2),  %%r10 ;"
		"movq  48(%2),  %%r11 ;"
		"clc ;"
		"adcx    (%1),  %%rax ;"
		"adcx   8(%1),  %%rcx ;"
		"adcx  16(%1),  %%rdx ;"
		"adcx  24(%1),  %%r8  ;"
		"adcx  32(%1),  %%r9  ;"
		"adcx  40(%1),  %%r10 ;"
		"adcx  48(%1),  %%r11 ;"
        "setc    %%bl         ;"
        "movzx   %%bl,  %%rbx ;"
		"addq   %%rbx,  %%rax ;"
		"adcq   $0,     %%rcx ;"
		"shlq   $32,    %%rbx ;"
		"addq   %%rbx,  %%r8  ;"
		"adcq   $0,     %%r9  ;"
		"movq   %%rax,   (%0) ;"
		"movq   %%rcx,  8(%0) ;"
		"movq   %%rdx, 16(%0) ;"
		"movq   %%r8 , 24(%0) ;"
		"movq   %%r9 , 32(%0) ;"
		"movq   %%r10, 40(%0) ;"
		"movq   %%r11, 48(%0) ;"
	:
	: "r" (c), "r" (a), "r"  (b)
	: "memory", "cc", "%rax", "%rbx", "%rcx", "%rdx",
	  "%r8", "%r9", "%r10", "%r11"
	);
#else
	__asm__ __volatile__(
		"movq    (%2),  %%rax ;"
		"movq   8(%2),  %%rcx ;"
		"movq  16(%2),  %%rdx ;"
		"movq  24(%2),  %%r8  ;"
		"movq  32(%2),  %%r9  ;"
		"movq  40(%2),  %%r10 ;"
		"movq  48(%2),  %%r11 ;"
		"addq    (%1),  %%rax ;"
		"adcq   8(%1),  %%rcx ;"
		"adcq  16(%1),  %%rdx ;"
		"adcq  24(%1),  %%r8  ;"
		"adcq  32(%1),  %%r9  ;"
		"adcq  40(%1),  %%r10 ;"
		"adcq  48(%1),  %%r11 ;"
        "setc    %%bl         ;"
        "movzx   %%bl,  %%rbx ;"
		"addq   %%rbx,  %%rax ;"
		"adcq   $0,     %%rcx ;"
		"shlq   $32,    %%rbx ;"
		"addq   %%rbx,  %%r8  ;"
		"adcq   $0,     %%r9  ;"
		"movq   %%rax,   (%0) ;"
		"movq   %%rcx,  8(%0) ;"
		"movq   %%rdx, 16(%0) ;"
		"movq   %%r8 , 24(%0) ;"
		"movq   %%r9 , 32(%0) ;"
		"movq   %%r10, 40(%0) ;"
		"movq   %%r11, 48(%0) ;"
	:
	: "r" (c), "r" (a), "r"  (b)
	: "memory", "cc", "%rax", "%rbx", "%rcx", "%rdx",
	  "%r8", "%r9", "%r10", "%r11"
	);
#endif
}

inline void sub_EltFp448_1w_x64(uint64_t * c, uint64_t * a, uint64_t * b)
{
	__asm__ __volatile__(
		"movq   (%1),  %%rax ;"
		"movq  8(%1),  %%rcx ;"
		"movq 16(%1),  %%rdx ;"
		"movq 24(%1),  %%r8  ;"
		"movq 32(%1),  %%r9  ;"
		"movq 40(%1),  %%r10 ;"
		"movq 48(%1),  %%r11 ;"
		"subq   (%2),  %%rax ;"
		"sbbq  8(%2),  %%rcx ;"
		"sbbq 16(%2),  %%rdx ;"
		"sbbq 24(%2),  %%r8  ;"
		"sbbq 32(%2),  %%r9  ;"
		"sbbq 40(%2),  %%r10 ;"
		"sbbq 48(%2),  %%r11 ;"
		"setc   %%bl         ;"
        "movzx  %%bl,  %%rbx ;"
		"subq  %%rbx,  %%rax ;"
		"sbbq  $0,     %%rcx ;"
		"shlq  $32,    %%rbx ;"
		"subq  %%rbx,  %%r8  ;"
		"sbbq  $0,     %%r9  ;"
		"movq  %%rax,   (%0) ;"
		"movq  %%rcx,  8(%0) ;"
		"movq  %%rdx, 16(%0) ;"
		"movq  %%r8 , 24(%0) ;"
		"movq  %%r9 , 32(%0) ;"
		"movq  %%r10, 40(%0) ;"
		"movq  %%r11, 48(%0) ;"
	:
	: "r" (c), "r" (a), "r"  (b)
	: "memory", "cc", "%rax", "%rbx", "%rcx", "%rdx",
      "%r8", "%r9", "%r10", "%r11"
	);
}

void mul_a24_EltFp448_1w_x64(uint64_t * c, uint64_t * a)
{
#ifdef __BMI2__
    /**
     * a24 = (A+2)/4 = (156326+2)/4 = 39082
     **/
    const uint64_t a24 = 39082;
    __asm__ __volatile__(
        "movq %2, %%rdx ;"
        "mulx   (%1), %%rax,  %%r8 ;"  "movq %%rax,   (%0) ;"
        "mulx  8(%1), %%rcx,  %%r9 ;"  "movq %%rcx,  8(%0) ;"
        "mulx 16(%1), %%rax, %%r10 ;"  "movq %%rax, 16(%0) ;"
        "mulx 24(%1), %%rcx, %%r11 ;"  "movq %%rcx, 24(%0) ;"
        "mulx 32(%1), %%rax, %%r12 ;"  "movq %%rax, 32(%0) ;"
        "mulx 40(%1), %%rcx, %%r13 ;"  "movq %%rcx, 40(%0) ;"
        "mulx 48(%1), %%rax, %%rdx ;"  "movq %%rax, 48(%0) ;"

        "movq %%rdx,  %%rcx ;"
        "shlq   $32,  %%rcx ;"
        "addq %%rcx,  %%r10 ;"
        "adcq    $0,  %%r11 ;"

        "addq %%rdx,   (%0) ;"
        "adcq  %%r8,  8(%0) ;"
        "adcq  %%r9, 16(%0) ;"
        "adcq %%r10, 24(%0) ;"
        "adcq %%r11, 32(%0) ;"
        "adcq %%r12, 40(%0) ;"
        "adcq %%r13, 48(%0) ;"
    :
    : "r" (c), "r" (a), "r" (a24)
    : "cc", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11", "%r12", "%r13"
    );
#else /* Without BMI2 */
    /**
	* TODO: Multiplications using MULQ instruction.
	**/
#endif
}

/**
 *
 * @param pC
 * @param pA
 * @param only_inverse
 */
void inv_EltFp448_1w_x64(uint64_t * __restrict pC, uint64_t * __restrict pA)
{
#define sqrn_EltFp448_1w_x64(a,times)\
    counter = times;\
    while(counter-- > 0)\
    {\
        sqr_EltFp448_1w_x64(a);\
    }

	EltFp448_1w_x64 x0,x1;
	uint64_t * T[4];
	unsigned int counter=0;
	EltFp448_1w_Buffer_x64 buffer_1w;

	T[0] = x0;
	T[1] = pC;
	T[2] = x1;
	T[3] = pA;

	copy_EltFp448_1w_x64(T[1],T[3]);
	sqrn_EltFp448_1w_x64(T[1],1);
	mul_EltFp448_1w_x64(T[1],T[1],T[3]);

	copy_EltFp448_1w_x64(T[0],T[1]);
	sqrn_EltFp448_1w_x64(T[0],1);
	mul_EltFp448_1w_x64(T[0],T[0],T[3]);

	copy_EltFp448_1w_x64(T[1],T[0]);
	sqrn_EltFp448_1w_x64(T[1],3);
	mul_EltFp448_1w_x64(T[1],T[1],T[0]);

	copy_EltFp448_1w_x64(T[2],T[1]);
	sqrn_EltFp448_1w_x64(T[2],6);
	mul_EltFp448_1w_x64(T[2],T[2],T[1]);

	copy_EltFp448_1w_x64(T[1],T[2]);
	sqrn_EltFp448_1w_x64(T[1],12);
	mul_EltFp448_1w_x64(T[1],T[1],T[2]);

	sqrn_EltFp448_1w_x64(T[1],3);
	mul_EltFp448_1w_x64(T[1],T[1],T[0]);

	copy_EltFp448_1w_x64(T[2],T[1]);
	sqrn_EltFp448_1w_x64(T[2],27);
	mul_EltFp448_1w_x64(T[2],T[2],T[1]);

	copy_EltFp448_1w_x64(T[1],T[2]);
	sqrn_EltFp448_1w_x64(T[1],54);
	mul_EltFp448_1w_x64(T[1],T[1],T[2]);
	
	sqrn_EltFp448_1w_x64(T[1],3);
	mul_EltFp448_1w_x64(T[1],T[1],T[0]);
	
	copy_EltFp448_1w_x64(T[2],T[1]);
	sqrn_EltFp448_1w_x64(T[2],111);
	mul_EltFp448_1w_x64(T[2],T[2],T[1]);
	
	copy_EltFp448_1w_x64(T[1],T[2]);
	sqrn_EltFp448_1w_x64(T[1],1);
	mul_EltFp448_1w_x64(T[1],T[1],T[3]);
	
	sqrn_EltFp448_1w_x64(T[1],223);
	mul_EltFp448_1w_x64(T[1],T[1],T[2]);

	sqrn_EltFp448_1w_x64(T[1],2);
	mul_EltFp448_1w_x64(T[1],T[1],T[3]);

#undef sqrn_EltFp448_1w_x64
}

void fred_EltFp448_1w_x64(uint64_t * c)
{
	EltFp448_1w_x64 p = {
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xfffffffeffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff,
			0xffffffffffffffff
	};
	sub_EltFp448_1w_x64(c,c,p);
}
