/* ======================================================================
 *
 * Decimal to binary and reverse conversions.
 *
 * Version: 1.0
 * Author: VZ Nigolian (EPFL, 2017)
 *
 * ======================================================================
 */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"


void printTab(int size, char tab[size]){
	for(int i=0;i<size;i++){
		printf("%c",tab[i]);
	}
	printf("\n");
	
}


/* ======================================================================
 * This is the first algorithm of interest:
 * convertion from positive decimal to binary.
 */

void binary_nonnegative(int n, int size, char output[size])
{
  if (n <= 0) {
    strcpy(output, "0");
    return;
  }

  // here n >= 1
  int i=size-1;
  while (n > 0 && i<size ) {
	  if (n%2 == 1) {
		  output[i]='1';
      }else{
		  output[i]='0';
      }
     
      n /= 2;
      i--;
  }
  
}

/* ======================================================================
 * This is the second algorithm of interest:
 * convertion from positive binary (no sign bit) to decimal.
 */
unsigned int decimal_nonnegative(int size, char binary[size])
{
  unsigned int output=0;
  unsigned int power=1;

  /* There are more advanced way to iterate over a const string in C++ (crbegin(),
   * crend()). This is the very basic way for beginners in C++ programming.
   */
   if(size>0){
	   for(int i=strlen(binary)-1;i>0;--i){
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
void twos_complement(int size, const char binary[size], char output[size])
{
  strcpy(output,binary);
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
void binary(int n, int size, char output[size])
{
  // Add the bit sign to the corresponding "unsigned" representation
  if (n < 0) {
	  char temp[] = "1";
      char nonnegative[size-1];
	  binary_nonnegative(-n,size-1,nonnegative);
	  twos_complement(size-1,nonnegative,output);
      strcat(temp,output );
      strcpy(output,temp);
      return;

  }else{
	char temp[] = "0";
	char nonnegative[size-1];
	binary_nonnegative(n,size-1,nonnegative);
	strcat(temp, nonnegative);
	strcpy(output,temp);
  }
}

/* ======================================================================
 * This is the fifth algorithm of interest:
 * convertion from binary (with sign bit) to decimal.
 */
int decimal(int size, char binary[size])
{
  // test sign bit
  if (size>0 && (binary[0] == '1')) {
	  char complement[size];
	  twos_complement(size,binary,complement);
     return -decimal_nonnegative(size,complement);
  }

  return decimal_nonnegative(size,binary);
}



/* ======================================================================
 * Tool function: test an int value and its binary writing
 */
void test(int n)
{
  int size = ceil(log2(abs(n)))+1;
  char result[size];
  
  for(int i=0;i<size;i++){
	  result[i]='0';
  }
  
  binary(n,size,result);
  int dec = decimal(size,result);
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
  test(42);
  test(-42);
  test(12314);
  test(-(pow(2,5)-1));
  return 0;
  
}
