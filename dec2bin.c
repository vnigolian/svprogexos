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

#define MAX_LENGTH 256

/* ======================================================================
 * This is the first algorithm of interest:
 * convertion from positive decimal to binary.
 */
void binary_nonnegative(int n, char* output)
{
  if (n <= 0) {
    strcpy(output, "0");
    return;
  }

  // here n >= 1
  while (n > 0) {
	  if (n%2 == 1) {
		  char temp[] ="1";
		  strcpy(output,strcat(temp,output));
      }else{
		  char temp[] = "0";
		  strcpy(output,strcat(temp,output));
      }
     
      n /= 2;
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

  /* There are more advanced way to iterate over a const string in C++ (crbegin(),
   * crend()). This is the very basic way for beginners in C++ programming.
   */
   if(strlen(binary)>0){
	   for(int i=strlen(binary)-1;i<strlen(binary);--i){
		   if(binary[i]=='1'){
			   output+= power;
		   }
		   power*=2;
	   }   
   }
   /*
  if (not binary.empty()) {
    for (size_t i(binary.size() - 1); i < binary.size(); --i) {
      if (binary[i] == '1') {
        output += power;
      }
      power *= 2;
    }
  }*/

  return output;
}

/* ======================================================================
 * This is the third algorithm of interest:
 * two's complement of binary string
 */
void twos_complement(const char* binary,char* output)
{
  strcpy(output,binary);
  if (strlen(binary)>0) {
    
    // invert all bits left to the least-signicant 1 (LS1)
    int i=strlen(output)-1;
    while(i<strlen(output) && (output[i] != '1')) {
		--i;
    }
    --i;
    
    while(i<strlen(output)){
		if(output[i] == '1'){
			output[i] = '0';
		}else{
			output[i] = '1';
		}
		--i;
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
	  char temp[] = "1";
      char nonnegative[MAX_LENGTH]="";
	  binary_nonnegative(-n,nonnegative);
	  twos_complement(nonnegative,output);
      strcat(temp,output );
      strcpy(output,temp);
      return;

  }
  char temp[] = "0";
  char nonnegative[MAX_LENGTH]="";
  binary_nonnegative(n,nonnegative);
  strcat(temp, nonnegative);
  strcpy(output,temp);
}

/* ======================================================================
 * This is the fifth algorithm of interest:
 * convertion from binary (with sign bit) to decimal.
 */
int decimal(char* binary)
{
  // test sign bit
  if (strlen(binary)>0 && (binary[0] == '1')) {
	  char* complement="";
	  twos_complement(binary,complement);
     return -decimal_nonnegative(complement);
  }

  return decimal_nonnegative(binary);
}

/* ======================================================================
 * All the rest below is not the core of the exercise but is just for
 * convenience.
 */

/* ======================================================================
 * Tool function: test an int value and its binary writing
 */
void test(int n)
{
  char result[]="";
  binary(n,result);
  printf("%i is %s\n",n,result);
  printf("and %s is indeed %i.\n",result,decimal(result));
  printf("done testing\n");
}

/* ======================================================================
 * Tool function: ask for some integer.
 */
int require_int()
{
  int value=0;
  printf("Enter some integer\n");
  scanf("%i",&value);
  
  return value;
}

/* ======================================================================
 * Tool function: ask to continue or not.
 * 0 = no, >0 = yes
 */
int go_ahead() {
  char read='x';
  do {
	  printf("Shall we continue (y/n)?\n");
      scanf("%c",&read);
  } while ((read != 'y') && (read != 'Y') &&
           (read != 'n') && (read != 'N'));
  return (read == 'y') || (read == 'Y');
}

// ======================================================================
int main()
{
  const int t=42;
  char bin[MAX_LENGTH]="";
  binary_nonnegative(t,bin);
  printf("conversion : %s\n",bin);
  
  test(t);
  
  printf("done first test\n");
  /*test(-t);
  
  printf("done second test\n");
  
  do {
    test(require_int());
  } while (go_ahead());

  return 0;
  * */
}
