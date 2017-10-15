/* ======================================================================
 *
 * Decimal to binary and reverse conversions.
 *
 * Version: 1.0
 * Author: VZ Nigolian (EPFL, 2017)
 * Translated from a C++ exercise written by J-C Chappelier
 * ======================================================================
 */
#include "stdio.h"
#include "string.h"

#define MAX_SIZE 32

/* ======================================================================
 * This is the first algorithm of interest:
 * convertion from positive decimal to binary.
 */
void binary_nonnegative(int n, char* output)
{
	if (n <= 0) {
		strcpy(output, "0");
	}else{
		// here n >= 1
		while (n > 0) {
			if (n%2 == 1) {
				char new_bin[MAX_SIZE] ="1";
				strcat(new_bin,output);
				strcpy(output,new_bin);
			}else{
				char new_bin[MAX_SIZE] ="0";
				strcat(new_bin,output);
				strcpy(output,new_bin);
			} 
		n /= 2;
		}
	}
}

/* ======================================================================
 * This is the second algorithm of interest:
 * convertion from positive binary (no sign bit) to decimal.
 */
unsigned int decimal_nonnegative(char* binary)
{
  unsigned int output=0;
  unsigned int power=1;

   if(strlen(binary)>0){
	   for(int i=strlen(binary)-1;i>=0;--i){
		   if(binary[i]=='1'){
			   output+= power;
		   }
		   power*=2;
	   }   
   }

  return output;
}

/* ======================================================================
 * This is the third algorithm of interest:
 * two's complement of binary string
 */
void twos_complement(const char* binary, char* output)
{
  strcpy(output,binary);
  int size = strlen(output);
  if (size>0) {
    
    // invert all bits left to the least-signicant 1 (LS1)
    int i=size-1;
    while(i>1 && (output[i] != '1')) {
		i--;
    }

    while(i>0){
		i--;
		if(output[i] == '1'){
			output[i] = '0';
		}else{
			output[i] = '1';
		}
	}
  }  
}

/* ======================================================================
 * This is the forth algorithm of interest:
 * convertion from (signed) decimal to binary, making use of former algorithms.
 */
void binary(int n, char* output)
{
  // Add the bit sign to the corresponding "unsigned" representation
  if (n < 0) {
	  char temp[MAX_SIZE] = "1";
      char nonnegative[MAX_SIZE]="";
	  binary_nonnegative(-n,nonnegative);
	  twos_complement(nonnegative,output);
      strcat(temp,output );
      strcpy(output,temp);
      return;

  }else{
	char temp[MAX_SIZE] = "0";
	char nonnegative[MAX_SIZE] = "";
	binary_nonnegative(n,nonnegative);
	strcat(temp, nonnegative);
	strcpy(output,temp);
  }
}

/* ======================================================================
 * This is the fifth algorithm of interest:
 * convertion from binary (with sign bit) to decimal.
 */
int decimal(char* binary)
{
  // test sign bit
  if (strlen(binary)>0 && (binary[0] == '1')) {
	  char complement[MAX_SIZE]="";
	  twos_complement(binary,complement);
     return -decimal_nonnegative(complement);
  }

  return decimal_nonnegative(binary);
}


/* ======================================================================
 * Tool function: test an int value and its binary writing
 */
void test(int n)
{
  char result[MAX_SIZE]="";
  
  binary(n,result);
  int dec = decimal(result);
  if(dec==n){
	  printf("%i_10 is %s_2\n",n,result);
	  printf("and %s_2 is indeed %i_10.\n",result,dec);
  }else{
	  printf("%i_10 is %s_2\n",n,result);
	  printf("but %s_2 is %i_10...\n",result,dec);
  }
}


// ======================================================================
int main()
{
	int t=42;
	
	test(t);
	test(-t);
	test(10*t);

	return 0;
}
